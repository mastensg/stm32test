#include <stdint.h>
#include <stdio.h>

#include "mastensg.h"
#include "stm32f103x8.h"

#include "breathe.h"

//////////////////////////////////////////////////////////////////////////////

__attribute__((always_inline)) static inline void delay_nops(u32 n) {
  for (u32 i = 0; i < n; ++i) {
    __asm__ __volatile__("nop\n");
  }
}

//////////////////////////////////////////////////////////////////////////////

static void chirp_init() {
  RCC_APB2ENR |= IOPCEN;

  gpio_configure(GPIOC_BASE, 13, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
}

static void chirp() {
  for (u32 i = 0; i < 4; ++i) {
    GPIOC_ODR = (0 << 13);
    delay_nops(30000);

    GPIOC_ODR = (1 << 13);
    delay_nops(30000);
  }
}

//////////////////////////////////////////////////////////////////////////////

static void uart_init() {
  RCC_APB2ENR |= IOPAEN;
  gpio_configure(GPIOA_BASE, 9, GPIO_OUTPUT_50M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB2ENR |= USART1EN;
  // USART_BRR = (52 << 4) | (1); // 9600 baud
  USART_BRR = (4 << 4) | (5);  // 115200 baud
  USART_CR1 = USART_TE | USART_RE;
  USART_CR1 |= USART_UE;
}

static void uart_sendchar(u8 c) {
  for (; !(USART_SR & USART_TXE);) {
  }
  USART_DR = c;
}

//////////////////////////////////////////////////////////////////////////////

#if 0
static void spi_init() {
  // SPI1: SCLK PA5, MOSI PA7
  RCC_APB2ENR |= IOPAEN;

  // PA5 push-pull
  // GPIOA_CRL = (GPIOA_CRL & (~(0b1111 << (4 * 5)))) | (0b0000 << (4 * 5));
  gpio_configure(GPIOA_BASE, 5, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB2ENR |= SPI1EN;
}

static void spi_sendchar(u8 c) {}
#endif

//////////////////////////////////////////////////////////////////////////////

void rst_handler() {
  chirp_init();
  chirp();

  uart_init();

  u8 i = 0;
  for (;;) {
    u16 dut = breathe[i] >> 8;

    for (u8 k = 0; k < 3; ++k) {
      for (u8 j = 0; j < 40; ++j) {
        uart_sendchar(j < dut ? 'A' : ' ');
        GPIOC_ODR = ((!(j < dut)) << 13);
      }

      uart_sendchar('\n');
      uart_sendchar('\r');
    }

    ++i;
  }
}

void nmi_handler() { return; }

void hardfault_handler() {
  for (;;) {
  }
}

// Vectors  //////////////////////////////////////////////////////////////////

__attribute__((section(".vectors"))) void (*vector_table[4])(void) = {
    (void *)(STACK_TOP),  //
    &rst_handler,         //
    &nmi_handler,         //
    &hardfault_handler,   //
};

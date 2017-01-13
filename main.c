#include <stdint.h>
#include <stdio.h>

#include "mastensg.h"
#include "stm32f103x8.h"

#include "breathe.h"

__attribute__((always_inline)) static inline void delay_nops(u32 n) {
  for (u32 i = 0; i < n; ++i) {
    __asm__ __volatile__("nop\n");
  }
}

static void uart_init(){
}

static void uart_sendchar(u8 c){
}

void rst_handler() {
  RCC_APB2ENR |= IOPCEN;
  GPIOC_CRH = 0x44344444;

  for (u32 i = 0; i < 4; ++i) {
    GPIOC_ODR = (0 << 13);
    delay_nops(30000);
    GPIOC_ODR = (1 << 13);
    delay_nops(30000);
  }

  RCC_APB2ENR |= IOPAEN;
  RCC_APB2ENR |= AFIOEN;
  GPIOA_CRH = 0x444444b4;

  RCC_APB2ENR |= USART1EN;
  // USART_BRR = (52 << 4) | (1);
  USART_BRR = (4 << 4) | (5);
  USART_CR1 = USART_TE | USART_RE;
  USART_CR1 |= USART_UE;

  u8 i = 0;
  for (;;) {
    u16 dut = breathe[i] >> 8;

    for (u8 k = 0; k < 3; ++k) {
      for (u8 j = 0; j < 40; ++j) {
        for (; !(USART_SR & USART_TXE);) {
        }
        USART_DR = j < dut ? 'A' : ' ';
        GPIOC_ODR = ((!(j < dut)) << 13);
      }

      for (; !(USART_SR & USART_TXE);) {
      }
      USART_DR = '\n';

      for (; !(USART_SR & USART_TXE);) {
      }
      USART_DR = '\r';
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

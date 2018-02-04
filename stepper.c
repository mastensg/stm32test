#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
  RCC_APB2ENR |= RCC_IOPCEN;

  gpio_configure(GPIOC_BASE, 13, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
}

static void chirp() {
  for (u32 i = 0; i < 2; ++i) {
    GPIOC_ODR = (0 << 13);
    delay_nops(30000);

    GPIOC_ODR = (1 << 13);
    delay_nops(30000);
  }
}

//////////////////////////////////////////////////////////////////////////////

// stepper
// tb6612fng
//
// b0   a1
// b1   a2
// b10  b1
// b11  b2

volatile uint32_t the_delay;
volatile uint32_t the_times;

void rst_handler() {
  chirp_init();
  chirp();

  the_delay = 1000;
  the_times = 400;

  RCC_APB2ENR |= RCC_IOPBEN;
  gpio_configure(GPIOB_BASE, 0, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 1, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 10, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 11, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);

  for (;;) {
    // chirp();

    for (uint32_t i = 0; i < the_times; ++i) {
      GPIOB_ODR = (1 << 11) | (0 << 10) | (0 << 1) | (0 << 0);
      delay_nops(the_delay);
      GPIOB_ODR = (0 << 11) | (0 << 10) | (1 << 1) | (0 << 0);
      delay_nops(the_delay);

      GPIOB_ODR = (0 << 11) | (1 << 10) | (0 << 1) | (0 << 0);
      delay_nops(the_delay);
      GPIOB_ODR = (0 << 11) | (0 << 10) | (0 << 1) | (1 << 0);
      delay_nops(the_delay);
    }

    for (uint32_t i = 0; i < the_times; ++i) {
      GPIOB_ODR = (1 << 11) | (0 << 10) | (0 << 1) | (0 << 0);
      delay_nops(the_delay);
      GPIOB_ODR = (0 << 11) | (0 << 10) | (0 << 1) | (1 << 0);
      delay_nops(the_delay);

      GPIOB_ODR = (0 << 11) | (1 << 10) | (0 << 1) | (0 << 0);
      delay_nops(the_delay);
      GPIOB_ODR = (0 << 11) | (0 << 10) | (1 << 1) | (0 << 0);
      delay_nops(the_delay);
    }

    // GPIOB_ODR = (0 << 11) | (0 << 10) | (0 << 1) | (0 << 0);
    // delay_nops(3000000);
  }
}

void nmi_handler() { return; }

void hardfault_handler() {
  for (;;) {
  }
}

// Vectors  //////////////////////////////////////////////////////////////////

__attribute__((section(".vectors"))) void (*vector_table[])(void) = {
    (void *)(STACK_TOP),
    [0x04 / 4] = &rst_handler,
    [0x08 / 4] = &nmi_handler,
    [0x0c / 4] = &hardfault_handler,
    [VECTOR_USB_HP_CAN_TX] = &hardfault_handler,
    [VECTOR_USB_LP_CAN_RX0] = &hardfault_handler,
};

#include <stdint.h>
#include <stdio.h>

#include "mastensg.h"
#include "stm32f103x8.h"

#include "breathe.h"

// static const u32 period = 1 << 13;
static const u32 period = 13350;

__attribute__((always_inline)) static inline void delay_nops(u32 n) {
  for (u32 i = 0; i < n; ++i) {
    __asm__ __volatile__("nop\n");
  }
}

#if 0
void rst_handler() {
  RCC_APB2ENR |= USART1EN;

  for (;;) {
    delay_nops(300000);
  }
}
#else
void rst_handler() {
  RCC_APB2ENR |= IOPCEN;

  // Configure port A:
  //    PA0
  //        CNF0  = 00  General purpose output push-pull
  //        CNF0  = 01  General purpose output Open-drain
  //        MODE0 = 11  Output mode, max speed 50 MHz
  GPIOC_CRH = 0x44344444;

  u8 i = 0;
  for (;;) {
#if 0
    const u32 duty = breathe[i];
#else
    const u32 duty = period - 6 * period / 4 / 20;
#endif

    GPIOC_ODR = 0x00000000;
    delay_nops(duty);

    GPIOC_ODR = 0xffffffff;
    delay_nops(period - duty);

    ++i;
    // i = (i + 1) % 128;
  }
}
#endif

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

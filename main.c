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

static void uart_init() {
  RCC_APB2ENR |= RCC_IOPAEN;
  gpio_configure(GPIOA_BASE, 9, GPIO_OUTPUT_50M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB2ENR |= RCC_USART1EN;

  // USART_BRR = (52 << 4) | (1); // 9600 baud
   USART_BRR = (4 << 4) | (5);  // 115200 baud / 8 MHz
  //USART_BRR = (39 << 4) | (1);  // 115200 baud / 72 MHz

  USART_CR1 = USART_TE | USART_RE;
  USART_CR1 |= USART_UE;
}

static void uart_putchar(u8 c) {
  for (; !(USART_SR & USART_TXE);) {
  }
  USART_DR = c;
}

static void uart_writes(const void *str) {
  u8 *p = (u8 *)str;

  for (;;) {
    u8 c = *p++;

    if (!c) {
      break;
    }

    uart_putchar(c);
  }
}

static void uart_puts(const void *str) {
  uart_writes(str);
  uart_putchar('\n');
  uart_putchar('\r');
}

#define putchar uart_putchar
#define writes uart_writes
#define puts uart_puts

//////////////////////////////////////////////////////////////////////////////

static void print_rcc_cr() {
  puts("RCC_CR");

#define X(x)            \
  writes("\t" #x "\t"); \
  puts((RCC_CR & RCC_##x) ? "yes" : "no");

  X(PLLRDY)
  X(PLLON)
  X(CSSON)
  X(HSEBYP)
  X(HSERDY)
  X(HSEON)
  X(HSICAL7)
  X(HSICAL6)
  X(HSICAL5)
  X(HSICAL4)
  X(HSICAL3)
  X(HSICAL2)
  X(HSICAL1)
  X(HSICAL0)
  X(HSITRIM4)
  X(HSITRIM3)
  X(HSITRIM2)
  X(HSITRIM1)
  X(HSITRIM0)
  X(HSIRDY)
  X(HSION)

#undef X
}

static void print_rcc_cfgr() {
  puts("RCC_CFGR");

#define X(x)            \
  writes("\t" #x "\t"); \
  puts((RCC_CFGR & RCC_##x) ? "yes" : "no");

  X(MCO2)
  X(MCO1)
  X(MCO0)
  X(USBPRE)
  X(PLLMUL3)
  X(PLLMUL2)
  X(PLLMUL1)
  X(PLLMUL0)
  X(PLLXTPRE)
  X(PLLSRC)
  X(ADCPRE1)
  X(ADCPRE0)
  X(PPRE2_2)
  X(PPRE2_1)
  X(PPRE2_0)
  X(PPRE1_2)
  X(PPRE1_1)
  X(PPRE1_0)
  X(HPRE3)
  X(HPRE2)
  X(HPRE1)
  X(HPRE0)
  X(SWS1)
  X(SWS0)
  X(SW1)
  X(SW0)

#undef X
}

static void print_usb_cntr() {
  puts("USB_CNTR");

#define X(x)            \
  writes("\t" #x "\t"); \
  puts((USB_CNTR & USB_##x) ? "yes" : "no");

  X(CTRM)
  X(PMAOVRM)
  X(ERRM)
  X(WKUPM)
  X(SUSPM)
  X(RESETM)
  X(SOFM)
  X(ESOFM)
  X(RESUME)
  X(FSUSP)
  X(LP_MODE)
  X(PDWN)
  X(FRES)

#undef X
}

static void print_usb_istr() {
  puts("USB_ISTR");

#define X(x)            \
  writes("\t" #x "\t"); \
  puts((USB_ISTR & USB_##x) ? "yes" : "no");

  X(CTR)
  X(PMAOVR)
  X(ERR)
  X(WKUP)
  X(SUSP)
  X(RESET)
  X(SOF)
  X(ESOF)
  X(DIR)

#undef X
}

static void print_usb_ep0r() {
  puts("USB_EP0R");

#define X(x)            \
  writes("\t" #x "\t"); \
  puts((USB_EP0R & USB_##x) ? "yes" : "no");

  X(CTR_RX)
  X(DTOG_RX)
  X(STAT_RX1)
  X(STAT_RX0)
  X(SETUP)
  X(EP_TYPE1)
  X(EP_TYPE0)
  X(EP_KIND)
  X(CTR_TX)
  X(DTOG_TX)
  X(STAT_TX1)
  X(STAT_TX0)
  X(EA3)
  X(EA2)
  X(EA1)
  X(EA0)

#undef X
}

#define print_bit(r, b)         \
  do {                          \
    writes(#r " -> " #b " = "); \
    puts((r & b) ? "1" : "0");  \
  } while (0);

static void print_usb() {
  print_usb_cntr();
  puts("");
  print_usb_istr();
  puts("");
  print_usb_ep0r();
  puts("");
  print_bit(USB_DADDR, USB_EF);
}

//////////////////////////////////////////////////////////////////////////////

static void usb_init() {
  RCC_APB1ENR |= RCC_USBEN;

  // RCC_APB1RSTR &= ~RCC_USBRST;

  print_bit(RCC_APB1ENR, RCC_USBEN);
  print_bit(RCC_APB1RSTR, RCC_USBRST);

  // Clear ISTR
  USB_ISTR = 0;

  USB_CNTR = USB_FRES;
  USB_CNTR = USB_CTRM | USB_RESETM;
  return;

  // PDWN in CNTR
  print_bit(USB_CNTR, USB_PDWN);
  USB_CNTR &= ~USB_PDWN;

  // t_STARTUP (1 us)
  delay_nops(10000);

  print_bit(USB_CNTR, USB_PDWN);
  return;

  //~FRES in CNTR

  print_bit(USB_DADDR, USB_EF);
  USB_DADDR |= USB_EF;
  print_bit(USB_DADDR, USB_EF);
}

//////////////////////////////////////////////////////////////////////////////

void rst_handler() {
#if 1
  chirp_init();
  chirp();
#endif

  // clock
  // 8 MHz * 9 = 72 MHz

  // RCC_CFGR = RCC_USBPRE | RCC_PLLMUL2 | RCC_PLLMUL1 | RCC_PLLMUL0 |
  // RCC_PLLSRC |
  // RCC_SW0;

  //RCC_CFGR = RCC_PLLMUL2 | RCC_PLLMUL1 | RCC_PLLMUL0 | RCC_PLLSRC | RCC_SW0;

  // RCC_CR = RCC_PLLON;

  RCC_CR = RCC_PLLON | RCC_HSEON;
  //RCC_CFGR = RCC_SW0;
  RCC_CFGR = RCC_PLLMUL2 | RCC_PLLMUL1 | RCC_PLLMUL0 | RCC_PLLSRC | RCC_SW0;

  for (; !(RCC_CR & RCC_HSEON);) {
  }
  for (; !(RCC_CR & RCC_PLLON);) {
  }
  for (; !(RCC_CFGR & RCC_SWS0);) {
  }

  uart_init();

  puts("");
  puts("========================================");

  usb_init();
  puts("----------------------------------------");
  puts("usb_init'd");
  print_rcc_cr();
  print_rcc_cfgr();

  for (;;) {
    chirp();
  print_rcc_cr();
    delay_nops(300000);
  }

  // print_usb();
  for (;;) {
  }

  ////////////////////////////////////////

  ////////////////////////////////////////

  for (;;) {
    puts("----------------------------------------");
    puts("");
    print_usb();

    puts("");
    delay_nops(800000);
    puts("");
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

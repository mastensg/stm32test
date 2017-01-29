#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mastensg.h"
#include "stm32f103x8.h"

#include "breathe.h"

static const u8 black[] = {
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

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
  for (u32 i = 0; i < 2; ++i) {
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

static void spi_init() {
  RCC_APB2ENR |= IOPAEN;

  gpio_configure(GPIOA_BASE, 5, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);
  gpio_configure(GPIOA_BASE, 7, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB2ENR |= SPI1EN;

  SPI_CR1 |= SPI_SSM | SPI_SSI | SPI_SPE | (0 << 3) | SPI_MSTR;
}

static void spi_sendchar(u8 c) {
  for (; !(SPI_SR & SPI_TXE);) {
  }
  SPI_DR = c;
}

//////////////////////////////////////////////////////////////////////////////

#define OLED_ACTIVATE_SCROLL 0x2F
#define OLED_CHARGE_PUMP 0x8D
#define OLED_COM_SCAN_DEC 0xC8
#define OLED_COM_SCAN_INC 0xC0
#define OLED_DEACTIVATE_SCROLL 0x2E
#define OLED_DISPLAY_ALL_ON 0xA5
#define OLED_DISPLAY_ALL_ON_RESUME 0xA4
#define OLED_DISPLAY_OFF 0xAE
#define OLED_DISPLAY_ON 0xAF
#define OLED_INVERT_DISPLAY 0xA7
#define OLED_LEFT_HORIZ_SCROLL 0x27
#define OLED_NORMAL_DISPLAY 0xA6
#define OLED_RIGHT_HORIZ_SCROLL 0x26
#define OLED_SEG_REMAP 0xA0
#define OLED_SET_COL_ADDRESS 0x21
#define OLED_SET_COM_PINS 0xDA
#define OLED_SET_CONTRAST 0x81
#define OLED_SET_DISPLAY_CLOCK_DIV 0xD5
#define OLED_SET_DISPLAY_OFFSET 0xD3
#define OLED_SET_HIGH_COLUMN 0x10
#define OLED_SET_LOW_COLUMN 0x00
#define OLED_SET_MEMORY_MODE 0x20
#define OLED_SET_MULTIPLEX 0xA8
#define OLED_SET_PAGE_ADDRESS 0x22
#define OLED_SET_PRECHARGE 0xD9
#define OLED_SET_START_LINE 0x40
#define OLED_SET_VCOM_DETECT 0xDB
#define OLED_SET_VERT_SCROLL_AREA 0xA3
#define OLED_VERT_AND_LEFT_HORIZ_SCROLL 0x2A
#define OLED_VERT_AND_RIGHT_HORIZ_SCROLL 0x29

#define OLED_MEMORY_MODE_HORIZ 0x00
#define OLED_MEMORY_MODE_VERT 0x01
#define OLED_MEMORY_MODE_PAGE 0x02

static void oled_init() {
  spi_init();

  RCC_APB2ENR |= IOPBEN;
  gpio_configure(GPIOB_BASE, 0, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);  // d/c
  gpio_configure(GPIOB_BASE, 1, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);  // rst

  GPIOB_ODR &= ~(0 << 0);
  GPIOB_ODR |= (1 << 1);
}

static void oled_reset() {
  GPIOB_ODR &= ~(1 << 1);
  delay_nops(6000);  // ~10ms
  GPIOB_ODR |= (1 << 1);
}

static void oled_command(u8 c) { spi_sendchar(c); }

static void oled_data(const u8 *data, size_t size) {
  delay_nops(1000);
  for (; (SPI_SR & SPI_BSY);) {
  }
  GPIOB_ODR |= (1 << 0);

  delay_nops(1000);
  for (size_t i = 0; i < size; ++i) {
    spi_sendchar(data[i]);
    // spi_sendchar(0);
  }

  delay_nops(1000);
  GPIOB_ODR &= ~(0 << 0);
}

static void oled_begin() {
  // delay_nops(600);  // ~1ms
  oled_reset();

  oled_command(OLED_DISPLAY_OFF);

  // 128x64
  oled_command(OLED_SET_MULTIPLEX);
  oled_command(0x3f);

  oled_command(OLED_SET_DISPLAY_OFFSET);
  oled_command(0x00);

  oled_command(OLED_SET_START_LINE | 0x00);

  oled_command(OLED_SEG_REMAP | 0x01);

  oled_command(OLED_COM_SCAN_DEC);

  oled_command(OLED_SET_COM_PINS);
  oled_command(0x12);

  oled_command(OLED_SET_CONTRAST);
  oled_command(0x8f);

  oled_command(OLED_DISPLAY_ALL_ON_RESUME);

  oled_command(OLED_SET_DISPLAY_CLOCK_DIV);
  oled_command(0x80);

  oled_command(OLED_CHARGE_PUMP);
  oled_command(0x14);

  oled_command(OLED_SET_MEMORY_MODE);
  oled_command(0x00);

  oled_command(OLED_SET_PRECHARGE);
  oled_command(0xf1);

  oled_command(OLED_SET_VCOM_DETECT);
  oled_command(0x40);
  oled_command(OLED_NORMAL_DISPLAY);
  oled_command(OLED_DISPLAY_ON);
}

//////////////////////////////////////////////////////////////////////////////

void rst_handler() {
#if 0
  chirp_init();
  chirp();
#endif

  uart_init();

  oled_init();
  oled_begin();

  u32 t = 0;
  u8 l = 0;
  for (;;) {
    GPIOC_ODR = (l << 13);

#if 0
    if (l) {
      oled_command(OLED_NORMAL_DISPLAY);
    } else {
      oled_command(OLED_INVERT_DISPLAY);
    }
#endif

    oled_command(OLED_SET_COL_ADDRESS);
    oled_command(0);
    oled_command(127);
#if 1
    oled_command(OLED_SET_PAGE_ADDRESS);
    oled_command(0);
    oled_command(7);
#else
    oled_command(0xb0);
#endif
    // delay_nops(1000);
    oled_data(black, 1024);

#if 0
    oled_command(OLED_INVERT_DISPLAY);
    delay_nops(10000);
    oled_command(OLED_NORMAL_DISPLAY);
    delay_nops(10000);
#endif

    ++t;
    l = !l;
    delay_nops(1000000);
  }

  u8 i = 0;
  for (;;) {
    u16 dut = breathe[i] >> 8;

    for (u8 k = 0; k < 3; ++k) {
      for (u8 j = 0; j < 40; ++j) {
        u8 c = j < dut ? 'A' : ' ';
        uart_sendchar(c);
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
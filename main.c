#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mastensg.h"
#include "stm32f103x8.h"

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

#if 0   // no i2c
static void i2c_init() {
  RCC_APB2ENR |= RCC_IOPBEN;

  gpio_configure(GPIOB_BASE, 6, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 7, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB1ENR |= RCC_I2C1EN;

  I2C1_CR2 = 8;  // 8 MHz peripheral clock frequency
  I2C1_OCR = 0x08;
  // I2C1_TRISE = 0x09;
  I2C1_CR1 |= I2C_PE;
}

static void i2c_sendchar(u8 a, u8 d) {
  u32 sr2;

  // start
  I2C1_CR1 |= I2C_START;
  for (; !(I2C1_SR1 & I2C_SB);) {
  }

  // address
  I2C1_DR = (a << 1) | 0;  // transmitter mode
  for (; !(I2C1_SR1 & I2C_ADDR);) {
  }
  sr2 = I2C1_SR2;
  (void)sr2;
  for (; !(I2C1_SR1 & I2C_TXE);) {
  }

  // data
  I2C1_DR = d;
  for (; !(I2C1_SR1 & I2C_TXE);) {
  }
  for (; !(I2C1_SR1 & I2C_BTF);) {
  }

  // stop
  I2C1_CR1 |= I2C_STOP;
}
#endif  // no i2c

//////////////////////////////////////////////////////////////////////////////

static void spi_init() {
  RCC_APB2ENR |= RCC_IOPAEN;

  gpio_configure(GPIOA_BASE, 5, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);
  gpio_configure(GPIOA_BASE, 7, GPIO_OUTPUT_2M, GPIO_ALTERNATE_PUSH_PULL);

  RCC_APB2ENR |= RCC_SPI1EN;

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

// SCK  PA5     SPI1_SCK
// SDA  PA7     SPI1_MOSI
// RES  PB10
// DC   PB0
// CS   PB1

#define OLED_RESET (1 << 10)
#define OLED_DC (1 << 0)
#define OLED_CS (1 << 1)

static void oled_init() {
  spi_init();

  RCC_APB2ENR |= RCC_IOPBEN;

  gpio_configure(GPIOB_BASE, 0, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 1, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
  gpio_configure(GPIOB_BASE, 10, GPIO_OUTPUT_2M, GPIO_GENERAL_PUSH_PULL);
}

static void oled_command(u8 c) {
  GPIOB_ODR |= OLED_CS;
  GPIOB_ODR &= ~OLED_DC;
  GPIOB_ODR &= ~OLED_CS;

  spi_sendchar(c);

  GPIOB_ODR |= OLED_CS;
}

static void oled_data(const u8 *data, size_t size) {
  GPIOB_ODR |= OLED_CS;
  GPIOB_ODR |= OLED_DC;
  GPIOB_ODR &= ~OLED_CS;

  for (size_t i = 0; i < size; ++i) {
    spi_sendchar(data[i]);
  }

  GPIOB_ODR |= OLED_CS;
}

static void oled_begin() {
  GPIOB_ODR |= OLED_RESET;
  delay_nops(600);  // ~1ms
  GPIOB_ODR &= ~OLED_RESET;
  delay_nops(6000);  // ~10ms
  GPIOB_ODR |= OLED_RESET;

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

static void fb_clear(uint8_t *fb, uint8_t color) {
  for (int i = 0; i < 1024; ++i) {
    fb[i] = color ? 0xff : 0x00;
  }
}

static void fb_point(uint8_t *fb, uint8_t x, uint8_t y, uint8_t color) {
  uint32_t byte = (y / 8) * 128 + x;
  uint8_t bit = y % 8;

  if (color) {
    fb[byte] |= (1 << bit);
  } else {
    fb[byte] &= ~(1 << bit);
  }
}

//////////////////////////////////////////////////////////////////////////////

#define CARPET_WIDTH 300

static const uint16_t carpet_start_state = 0xACE1u;

struct carpet {
  uint16_t lfsr;
  uint8_t world[CARPET_WIDTH];
  uint8_t new_world[CARPET_WIDTH];
};

static void carpet_init(struct carpet *c) {
  c->lfsr = carpet_start_state;

  for (int i = 0; i < CARPET_WIDTH; ++i) {
    uint16_t bit =
        ((c->lfsr >> 0) ^ (c->lfsr >> 2) ^ (c->lfsr >> 3) ^ (c->lfsr >> 5)) & 1;

    c->lfsr = (c->lfsr >> 1) | (bit << 15);
    c->new_world[i] = (c->lfsr >> 1) & 1;
  }
}

static void carpet_line(struct carpet *c) {
  for (int x = 0; x < CARPET_WIDTH - 1; ++x) {
    c->world[x] = c->world[x] ^ c->world[x + 1];
  }
}

//////////////////////////////////////////////////////////////////////////////

static u8 the_fb[1024];

void rst_handler() {
  chirp_init();

  oled_init();
  oled_begin();

  struct carpet carpet;
  carpet_init(&carpet);

  for (;;) {
    fb_clear(the_fb, 0);

    {
      struct carpet *c = &carpet;

      for (int x = 0; x < CARPET_WIDTH; ++x) {
        c->world[x] = c->new_world[x];
      }
      c->world[CARPET_WIDTH - 1] = 0;

      for (int y = 0; y < 64; ++y) {
        for (int x = 0; x < CARPET_WIDTH - 1; ++x) {
          c->world[x] = c->world[x] ^ c->world[x + 1];

          if (x < 128) {
            fb_point(the_fb, x, y, c->world[x]);
          }
        }
      }

      for (int i = 0; i < 3; ++i) {
        for (int x = 0; x < CARPET_WIDTH - 1; ++x) {
          c->new_world[x] = c->new_world[x] ^ c->new_world[x + 1];
        }
        c->new_world[CARPET_WIDTH - 1] = 0;
      }
    }

    oled_data(the_fb, 1024);
    {
      GPIOC_ODR = (0 << 13);
      delay_nops(10000);

      GPIOC_ODR = (1 << 13);
      delay_nops(10000);
    }
    // delay_nops(100000);
  }
}

void nmi_handler() {
  return;
}

void hardfault_handler() {
  for (;;) {
    GPIOC_ODR = (0 << 13);
    delay_nops(300000);

    GPIOC_ODR = (1 << 13);
    delay_nops(300000);
  }
}

// Vectors  //////////////////////////////////////////////////////////////////

__attribute__((section(".vectors"))) void (*vector_table[4])(void) = {
    (void (*)(void))(STACK_TOP),  //
    &rst_handler,                 //
    &nmi_handler,                 //
    &hardfault_handler,           //
};

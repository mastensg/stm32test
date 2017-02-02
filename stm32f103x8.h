#define RAM_BASE 0x20000000

#define STACK_TOP (RAM_BASE + 10 * 1024)
// TODO(mastensg): if my stack takes up all of ram, does that preclude any
// statically allocated ram?

// Reset and clock control (RCC)  ////////////////////////////////////////////

#define RCC_BASE ((volatile void *)0x40021000)

#define RCC_CR (*(volatile u32 *)(RCC_BASE + 0x00))  // Clock control

/* Bit 31: Reserved */
/* Bit 30: Reserved */
/* Bit 29: Reserved */
/* Bit 28: Reserved */
/* Bit 27: Reserved */
/* Bit 26: Reserved */
#define RCC_PLLRDY (1 << 25)
#define RCC_PLLON (1 << 24)
/* Bit 23: Reserved */
/* Bit 22: Reserved */
/* Bit 21: Reserved */
/* Bit 20: Reserved */
#define RCC_CSSON (1 << 19)
#define RCC_HSEBYP (1 << 18)
#define RCC_HSERDY (1 << 17)
#define RCC_HSEON (1 << 16)
#define RCC_HSICAL7 (1 << 15)
#define RCC_HSICAL6 (1 << 14)
#define RCC_HSICAL5 (1 << 13)
#define RCC_HSICAL4 (1 << 12)
#define RCC_HSICAL3 (1 << 11)
#define RCC_HSICAL2 (1 << 10)
#define RCC_HSICAL1 (1 << 9)
#define RCC_HSICAL0 (1 << 8)
#define RCC_HSITRIM4 (1 << 7)
#define RCC_HSITRIM3 (1 << 6)
#define RCC_HSITRIM2 (1 << 5)
#define RCC_HSITRIM1 (1 << 4)
#define RCC_HSITRIM0 (1 << 3)
/* Bit 2: Reserved */
#define RCC_HSIRDY (1 << 1)
#define RCC_HSION (1 << 0)

#define RCC_CFGR (*(volatile u32 *)(RCC_BASE + 0x04))  // Clock configuration

/* Bit 31: Reserved */
/* Bit 30: Reserved */
/* Bit 29: Reserved */
/* Bit 28: Reserved */
/* Bit 27: Reserved */
#define RCC_MCO2 (1 << 25)
#define RCC_MCO1 (1 << 25)
#define RCC_MCO0 (1 << 24)
/* Bit 23: Reserved */
#define RCC_USBPRE (1 << 22)
#define RCC_PLLMUL3 (1 << 21)
#define RCC_PLLMUL2 (1 << 20)
#define RCC_PLLMUL1 (1 << 19)
#define RCC_PLLMUL0 (1 << 18)
#define RCC_PLLXTPRE (1 << 17)
#define RCC_PLLSRC (1 << 16)
#define RCC_ADCPRE1 (1 << 15)
#define RCC_ADCPRE0 (1 << 14)
#define RCC_PPRE2_2 (1 << 13)
#define RCC_PPRE2_1 (1 << 12)
#define RCC_PPRE2_0 (1 << 11)
#define RCC_PPRE1_2 (1 << 10)
#define RCC_PPRE1_1 (1 << 9)
#define RCC_PPRE1_0 (1 << 8)
#define RCC_HPRE3 (1 << 7)
#define RCC_HPRE2 (1 << 6)
#define RCC_HPRE1 (1 << 5)
#define RCC_HPRE0 (1 << 4)
#define RCC_SWS1 (1 << 3)
#define RCC_SWS0 (1 << 2)
#define RCC_SW1 (1 << 1)
#define RCC_SW0 (1 << 0)

#define RCC_APB1RSTR (*(volatile u32 *)(RCC_BASE + 0x10))  // APB1 reset

/* Bit 31: Reserved */
/* Bit 30: Reserved */
#define RCC_DACRST (1 << 29)
#define RCC_PWRRST (1 << 28)
#define RCC_BKPRST (1 << 27)
/* Bit 26: Reserved */
#define RCC_CANRST (1 << 25)
/* Bit 24: Reserved */
#define RCC_USBRST (1 << 23)
#define RCC_I2C2RST (1 << 22)
#define RCC_I2C1RST (1 << 21)
#define RCC_UART5RST (1 << 20)
#define RCC_UART4RST (1 << 19)
#define RCC_USART3RST (1 << 18)
#define RCC_USART2RST (1 << 17)
/* Bit 16: Reserved */
#define RCC_SPI3RST (1 << 15)
#define RCC_SPI2RST (1 << 14)
/* Bit 13: Reserved */
/* Bit 12: Reserved */
#define RCC_WWDGRST (1 << 11)
/* Bit 10: Reserved */
/* Bit 9: Reserved */
#define RCC_TIM14RST (1 << 8)
#define RCC_TIM13RST (1 << 7)
#define RCC_TIM12RST (1 << 6)
#define RCC_TIM7RST (1 << 5)
#define RCC_TIM6RST (1 << 4)
#define RCC_TIM5RST (1 << 3)
#define RCC_TIM4RST (1 << 2)
#define RCC_TIM3RST (1 << 1)
#define RCC_TIM2RST (1 << 0)

#define RCC_APB2ENR (*(volatile u32 *)(RCC_BASE + 0x18))  // APB2 clock enable

/* Bit 31: Reserved */
/* Bit 30: Reserved */
/* Bit 29: Reserved */
/* Bit 28: Reserved */
/* Bit 27: Reserved */
/* Bit 26: Reserved */
/* Bit 25: Reserved */
/* Bit 24: Reserved */
/* Bit 23: Reserved */
/* Bit 22: Reserved */
#define RCC_TIM11EN (1 << 21)
#define RCC_TIM10EN (1 << 20)
#define RCC_TIM9EN (1 << 19)
/* Bit 18: Reserved */
/* Bit 17: Reserved */
/* Bit 16: Reserved */
#define RCC_ADC3EN (1 << 15)
#define RCC_USART1EN (1 << 14)
#define RCC_TIM8EN (1 << 13)
#define RCC_SPI1EN (1 << 12)
#define RCC_TIM1EN (1 << 11)
#define RCC_ADC2EN (1 << 10)
#define RCC_ADC1EN (1 << 9)
#define RCC_IOPGEN (1 << 8)
#define RCC_IOPFEN (1 << 7)
#define RCC_IOPEEN (1 << 6)
#define RCC_IOPDEN (1 << 5)
#define RCC_IOPCEN (1 << 4)
#define RCC_IOPBEN (1 << 3)
#define RCC_IOPAEN (1 << 2)
/* Bit 1: Reserved */
#define RCC_AFIOEN (1 << 0)

#define RCC_APB1ENR (*(volatile u32 *)(RCC_BASE + 0x1c))  // APB1 clock enable

/* Bit 31: Reserved */
/* Bit 30: Reserved */
#define RCC_DACEN (1 << 29)
#define RCC_PWREN (1 << 28)
#define RCC_BKPEN (1 << 27)
/* Bit 26: Reserved */
#define RCC_CANEN (1 << 25)
/* Bit 24: Reserved */
#define RCC_USBEN (1 << 23)
#define RCC_I2C2EN (1 << 22)
#define RCC_I2C1EN (1 << 21)
#define RCC_UART5EN (1 << 20)
#define RCC_UART4EN (1 << 19)
#define RCC_USART3EN (1 << 18)
#define RCC_USART2EN (1 << 17)
/* Bit 16: Reserved */
#define RCC_SPI3EN (1 << 15)
#define RCC_SPI2EN (1 << 14)
/* Bit 13: Reserved */
/* Bit 12: Reserved */
#define RCC_WWDGEN (1 << 11)
/* Bit 10: Reserved */
/* Bit 9: Reserved */
#define RCC_TIM14EN (1 << 8)
#define RCC_TIM13EN (1 << 7)
#define RCC_TIM12EN (1 << 6)
#define RCC_TIM7EN (1 << 5)
#define RCC_TIM6EN (1 << 4)
#define RCC_TIM5EN (1 << 3)
#define RCC_TIM4EN (1 << 2)
#define RCC_TIM3EN (1 << 1)
#define RCC_TIM2EN (1 << 0)

// General purpose input/output port A  //////////////////////////////////////

#define GPIOA_BASE ((volatile u32 *)0x40010800)

#define GPIOA_CRL (GPIOA_BASE[0])   // Port A configuration register low
#define GPIOA_CRH (GPIOA_BASE[1])   // Port A control register high
#define GPIOA_IDR (GPIOA_BASE[2])   // Port A input data register
#define GPIOA_ODR (GPIOA_BASE[3])   // Port A output data register
#define GPIOA_BSRR (GPIOA_BASE[4])  // Port A bit set/reset register
#define GPIOA_BRR (GPIOA_BASE[5])   // Port A bit reset register
#define GPIOA_LCKR (GPIOA_BASE[6])  // Port A configuration lock register

// General purpose input/output port B  //////////////////////////////////////

#define GPIOB_BASE ((volatile u32 *)0x40010c00)

#define GPIOB_CRL (GPIOB_BASE[0])   // Port B configuration register low
#define GPIOB_CRH (GPIOB_BASE[1])   // Port B control register high
#define GPIOB_IDR (GPIOB_BASE[2])   // Port B input data register
#define GPIOB_ODR (GPIOB_BASE[3])   // Port B output data register
#define GPIOB_BSRR (GPIOB_BASE[4])  // Port B bit set/reset register
#define GPIOB_BRR (GPIOB_BASE[5])   // Port B bit reset register
#define GPIOB_LCKR (GPIOB_BASE[6])  // Port B configuration lock register

// General purpose input/output port C  //////////////////////////////////////

#define GPIOC_BASE ((volatile u32 *)0x40011000)

#define GPIOC_CRL (GPIOC_BASE[0])   // Port C configuration register low
#define GPIOC_CRH (GPIOC_BASE[1])   // Port C control register high
#define GPIOC_IDR (GPIOC_BASE[2])   // Port C input data register
#define GPIOC_ODR (GPIOC_BASE[3])   // Port C output data register
#define GPIOC_BSRR (GPIOC_BASE[4])  // Port C bit set/reset register
#define GPIOC_BRR (GPIOC_BASE[5])   // Port C bit reset register
#define GPIOC_LCKR (GPIOC_BASE[6])  // Port C configuration lock register

// Serial Peripheral Interface  //////////////////////////////////////////////

// TODO(mastensg): support SPI1, SPI2, ...

#define SPI_BASE ((volatile void *)0x40013000)

#define SPI_CR1 (*(volatile u32 *)(SPI_BASE + 0x00))  // Control register 1
#define SPI_BIDIMODE (1 << 15)  // Bidirectional data mode enable
#define SPI_BIDIOE (1 << 14)    // Output enable in bidirectional mode
#define SPI_CRCEN (1 << 13)     // Hardware CRC calculation enable
#define SPI_CRCNEXT (1 << 12)   // CRC transfer next
#define SPI_DFF (1 << 11)       // Data frame format
#define SPI_RXONLY (1 << 10)    // Receive only
#define SPI_SSM (1 << 9)        // Software slave management
#define SPI_SSI (1 << 8)        // Internal slave select
#define SPI_LSBFIRST (1 << 7)   // Frame format
#define SPI_SPE (1 << 6)        // SPI enable
#define SPI_BR2 (1 << 5)  // Baud rate control: SPI_CLK = f_PCLK / (2 << SPI_BR)
#define SPI_BR1 (1 << 4)  // Baud rate control
#define SPI_BR0 (1 << 3)  // Baud rate control
#define SPI_MSTR (1 << 2)  // Master selection
#define SPI_CPOL (1 << 1)  // Clock polarity
#define SPI_CPHA (1 << 0)  // Clock phase

#define SPI_CR2 (*(volatile u32 *)(SPI_BASE + 0x04))  // Control register 2
/* Bit 15: Reserved */
/* Bit 14: Reserved */
/* Bit 13: Reserved */
/* Bit 12: Reserved */
/* Bit 11: Reserved */
/* Bit 10: Reserved */
/* Bit 9: Reserved */
/* Bit 8: Reserved */
#define SPI_TXEIE (1 << 7)   // Tx buffer empty interrupt enable
#define SPI_RXNEIE (1 << 6)  // Rx buffer not empty interrupt enable
#define SPI_ERRIE (1 << 5)   // Error interrupt enable
/* Bit 4: Reserved */
/* Bit 3: Reserved */
#define SPI_SSOE (1 << 2)     // SS output enable
#define SPI_TXDMAEN (1 << 1)  // Tx buffer DMA enable
#define SPI_RXDMAEN (1 << 0)  // Rx buffer DMA enable

#define SPI_SR (*(volatile u32 *)(SPI_BASE + 0x08))  // Status register
/* Bit 15: Reserved */
/* Bit 14: Reserved */
/* Bit 13: Reserved */
/* Bit 12: Reserved */
/* Bit 11: Reserved */
/* Bit 10: Reserved */
/* Bit 9: Reserved */
/* Bit 8: Reserved */
#define SPI_BSY (1 << 7)     // Busy flag
#define SPI_OVR (1 << 6)     // Overrun flag
#define SPI_MODF (1 << 5)    // Mode fault
#define SPI_CRCERR (1 << 4)  // CRC error flag
#define SPI_UDR (1 << 3)     // Underrun flag
#define SPI_CHSIDE (1 << 2)  // Channel side
#define SPI_TXE (1 << 1)     // Transmit buffer empty
#define SPI_RXNE (1 << 0)    // Receive buffer not empty

#define SPI_DR (*(volatile u32 *)(SPI_BASE + 0x0c))  // Data register

/* Bits 8~0 */  // Data value

#define SPI_CRCPR (*(volatile u32 *)(SPI_BASE + 0x10))
#define SPI_RXCRCR (*(volatile u32 *)(SPI_BASE + 0x14))
#define SPI_TXCRCR (*(volatile u32 *)(SPI_BASE + 0x18))
#define SPI_I2SCFGR (*(volatile u32 *)(SPI_BASE + 0x1c))
#define SPI_I2SPR (*(volatile u32 *)(SPI_BASE + 0x20))

// Universal (A)synchronous Receiver Transmitter  ////////////////////////////

// TODO(mastensg): support USART1, USART2, ...

#define USART_BASE ((volatile void *)0x40013800)

#define USART_SR (*(volatile u32 *)(USART_BASE + 0x00))  // Status register
/* Bit 15: Reserved */
/* Bit 14: Reserved */
/* Bit 13: Reserved */
/* Bit 12: Reserved */
/* Bit 11: Reserved */
/* Bit 10: Reserved */
#define USART_CTS (1 << 9)   // CTS flag
#define USART_LBD (1 << 8)   // LIN break detection flag
#define USART_TXE (1 << 7)   // Transmit data register empty
#define USART_TC (1 << 6)    // Transmission complete
#define USART_RXNE (1 << 5)  // Read data register not empty
#define USART_IDLE (1 << 4)  // Idle line detected
#define USART_ORE (1 << 3)   // Overrun error
#define USART_NE (1 << 2)    // Noise error
#define USART_FE (1 << 1)    // Framing error
#define USART_PE (1 << 0)    // Parity error

#define USART_DR (*(volatile u32 *)(USART_BASE + 0x04))  // Data register
/* Bits 8~0: Data value */

#define USART_BRR (*(volatile u32 *)(USART_BASE + 0x08))  // Baud rate register
/* Bits 15~4: Mantissa */
/* Bits 3~0: Fraction */

// USART_DIV = f_CLK / (16 * Baudrate)
// 8000000 / (16 * 9600) = 52.0833...
// 8000000 / (16 * 115200) = 4.3402777...
// 72000000 / (16 * 115200) = 4.3402777...

#define USART_CR1 (*(volatile u32 *)(USART_BASE + 0x0c))  // Control register 1
/* Bit 15: Reserved */
/* Bit 14: Reserved */
#define USART_UE (1 << 13)     // USART enable
#define USART_M (1 << 12)      // Word length
#define USART_WAKE (1 << 11)   // Wakeup method
#define USART_PCE (1 << 10)    // Parity control enable
#define USART_PS (1 << 9)      // Parity selection
#define USART_PEIE (1 << 8)    // PE interrupt enable
#define USART_TXEIE (1 << 7)   // TXE interrupt enable
#define USART_TCIE (1 << 6)    // Transmission complete interrupt enable
#define USART_RXNEIE (1 << 5)  // RXNE interrupt enable
#define USART_IDLEIE (1 << 4)  // IDLE interrupt enable
#define USART_TE (1 << 3)      // Transmitter enable
#define USART_RE (1 << 2)      // Receiver enable
#define USART_RWU (1 << 1)     // Receiver wakeup
#define USART_SBK (1 << 0)     // Send break

#define USART_CR2 (*(volatile u32 *)(USART_BASE + 0x10))  // Control register 2
/* Bit 15: Reserved */
#define USART_LINEN (1 << 14)  // LIN mode enable
#define USART_STOP1 (1 << 13)  // STOP bits
#define USART_STOP0 (1 << 12)  // -
#define USART_CLKEN (1 << 11)  // Clock enable
#define USART_CPOL (1 << 10)   // Clock polarity
#define USART_CPHA (1 << 9)    // Clock phase
#define USART_LBCL (1 << 8)    // Last bit clock pulse
/* Bit 7: Reserved */          //
#define USART_LBDIE (1 << 6)   // LIN break detection interrupt enable
#define USART_LBDL (1 << 5)    // LIN break detection length
/* Bit 4: Reserved */          //
#define USART_ADD3 (1 << 3)    // Address of the USART node
#define USART_ADD2 (1 << 2)    // -
#define USART_ADD1 (1 << 1)    // -
#define USART_ADD0 (1 << 0)    // -

#define USART_CR3 (*(volatile u32 *)(USART_BASE + 0x14))  // Control register 3
/* Bit 15: Reserved */
/* Bit 14: Reserved */
/* Bit 13: Reserved */
/* Bit 12: Reserved */
/* Bit 11: Reserved */
#define USART_CTSIE (1 << 10)  // CTS interrupt enable
#define USART_CTSE (1 << 9)    // CTS enable
#define USART_RTSE (1 << 8)    // RTS enable
#define USART_DMAT (1 << 7)    // DMA enable transmitter
#define USART_DMAR (1 << 6)    // DMA enable receiver
#define USART_SCEN (1 << 5)    // Smartcard mode enable
#define USART_NACK (1 << 4)    // Smartcard NACK enable
#define USART_HDSEL (1 << 3)   // Half-duplex selection
#define USART_IRLP (1 << 2)    // IrDA low-power
#define USART_IREN (1 << 1)    // IrDA mode enable
#define USART_EIE (1 << 0)     // Error interrupt enable

#define USART_GTPR \
  (*(volatile u32 *)(USART_BASE + 0x18))  // Guard time and prescaler register
/* Bits 15~8: Guard time value */
/* Bits 7~0: Prescaler value */

// Universal Serial Bus  /////////////////////////////////////////////////////

#define USB_BASE ((volatile u32 *)0x40005c00)

// NOTE: USB registers are 16 bits wide, but are 32-bit aligned because APB1
// requires word-aligned access.

// USB control register  //////////////

#define USB_CNTR (*(USB_BASE + 0x40))

// Reset value: 0x0003

#define USB_CTRM (1 << 15)     // Correct transfer interrupt mask
#define USB_PMAOVRM (1 << 14)  // Packet over/underrun interrupt mask
#define USB_ERRM (1 << 13)     // Error interrupt mask
#define USB_WKUPM (1 << 12)    // Wakeup interrupt mask
#define USB_SUSPM (1 << 11)    // Suspend mode interrupt mask
#define USB_RESETM (1 << 10)   // USB reset interrupt mask
#define USB_SOFM (1 << 9)      // Start of frame interrupt mask
#define USB_ESOFM (1 << 8)     // Expected start of frame interrupt mask
/* Bits 7~5: Reserved */       //
#define USB_RESUME (1 << 4)    // Resume request
#define USB_FSUSP (1 << 3)     // Force suspend
#define USB_LP_MODE (1 << 2)   // Low-power mode
#define USB_PDWN (1 << 1)      // Power down
#define USB_FRES (1 << 0)      // Force USB reset

// USB interrupt status register  /////

#define USB_ISTR (*(USB_BASE + 0x44))

// Reset value: 0x0000

// NOTE: Clear bits by writing a word with zeroes for the bits you want to
// clear, and ones for the bits you want to stay the same. Do not
// read-modify-write.

#define USB_CTR (1 << 15)     // Correct transfer
#define USB_PMAOVR (1 << 14)  // Packet memory over / underrun
#define USB_ERR (1 << 13)     // Error
#define USB_WKUP (1 << 12)    // Wakeup
#define USB_SUSP (1 << 11)    // Suspend mode request
#define USB_RESET (1 << 10)   // USB reset request
#define USB_SOF (1 << 9)      // Start of frame
#define USB_ESOF (1 << 8)     // Expected start of frame
// Bits 7~5: Reserved
#define USB_DIR (1 << 4)  // Direction of transaction
// Bits 3~0: Endpoint Identifier

#define USB_FNR (*(USB_BASE + 0x48))  // USB frame number register

#define USB_RXDP (1 << 15)   // Receive data + line status
#define USB_RXDM (1 << 14)   // Receive data - line status
#define USB_LCK (1 << 13)    // Locked
#define USB_LSOF1 (1 << 12)  // Lost SOF, number of consecutive SOF packets lost
#define USB_LSOF0 (1 << 11)  // Lost SOF
/* Bits 10~0 */              // Frame number

#define USB_DADDR (*(USB_BASE + 0x4c))  // USB device address

/* Bits 15~8: Reserved */
#define USB_EF (1 << 7)  // Enable function
/* Bits 6~0 ADD[6:0] */  // Device address

#define USB_BTABLE (*(USB_BASE + 0x50))  // Buffer table address

/* Bits 15~3 BTABLE[15:3] */  // Buffer table
/* Bits 2~0: Reserved, forced 0 */

#define USB_EP0R (*(USB_BASE + 0x00))  // USB endpoint 0 register
#define USB_EP1R (*(USB_BASE + 0x04))  // USB endpoint 1 register
#define USB_EP2R (*(USB_BASE + 0x08))  // USB endpoint 2 register
#define USB_EP3R (*(USB_BASE + 0x0c))  // USB endpoint 3 register
#define USB_EP4R (*(USB_BASE + 0x10))  // USB endpoint 4 register
#define USB_EP5R (*(USB_BASE + 0x14))  // USB endpoint 5 register
#define USB_EP6R (*(USB_BASE + 0x18))  // USB endpoint 6 register
#define USB_EP7R (*(USB_BASE + 0x1c))  // USB endpoint 7 register

#define USB_CTR_RX (1 << 15)    // Correct transfer for reception
#define USB_DTOG_RX (1 << 14)   // Data toggle for reception
#define USB_STAT_RX1 (1 << 13)  // Status bits for reception
#define USB_STAT_RX0 (1 << 12)  // Status bits for reception
#define USB_SETUP (1 << 11)     // Setup transaction completed
#define USB_EP_TYPE1 (1 << 10)  // Endpoint type
#define USB_EP_TYPE0 (1 << 9)   // Endpoint type
#define USB_EP_KIND (1 << 8)    // Endpoint kind
#define USB_CTR_TX (1 << 7)     // Correct transfer for transmission
#define USB_DTOG_TX (1 << 6)    // Data toggle for transmission
#define USB_STAT_TX1 (1 << 5)   // Status bits for transmission
#define USB_STAT_TX0 (1 << 4)   // Status bits for transmission
#define USB_EA3 (1 << 3)        // Endpoint address
#define USB_EA2 (1 << 2)        // Endpoint address
#define USB_EA1 (1 << 1)        // Endpoint address
#define USB_EA0 (1 << 0)        // Endpoint address

// Vector table  /////////////////////////////////////////////////////////////

#define VECTOR_USB_HP_CAN_TX (0x8c / 4)   // USB high priority or CAN TX
#define VECTOR_USB_LP_CAN_RX0 (0x90 / 4)  // USB low priority or CAN RX0

// GPIO  /////////////////////////////////////////////////////////////////////

// GPIO MODE bits
#define GPIO_INPUT 0b00
#define GPIO_OUTPUT_10M 0b01
#define GPIO_OUTPUT_2M 0b10
#define GPIO_OUTPUT_50M 0b11

// GPIO input configuration bits
#define GPIO_ANALOG 0b00
#define GPIO_FLOATING 0b01
#define GPIO_PULLED 0b10

// GPIO output configuration bits
#define GPIO_GENERAL_PUSH_PULL 0b00
#define GPIO_GENERAL_OPEN_DRAIN 0b01
#define GPIO_ALTERNATE_PUSH_PULL 0b10
#define GPIO_ALTERNATE_OPEN_DRAIN 0b11

static void gpio_configure(volatile u32 *base, u8 pin, u8 mode, u8 cnf) {
  u8 is_high = 7 < pin;
  volatile u32 *cr = base + is_high;
  u8 bits = (cnf << 2) | mode;
  u8 left_shift = (pin & 7) << 2;

  *cr = (*cr & (~(0xf << left_shift))) | (bits << left_shift);
}

//////////////////////////////////////////////////////////////////////////////

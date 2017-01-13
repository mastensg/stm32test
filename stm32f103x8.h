#define RAM_BASE 0x20000000
#define STACK_TOP (RAM_BASE + 20 * 1024)

// Reset and clock control (RCC)  ////////////////////////////////////////////

#define RCC_BASE ((volatile u32 *)0x40021000)

#define RCC_APB2ENR (RCC_BASE[6])  // APB2 peripheral clock enable register
/* Bit 15: Reserved */
#define USART1EN (1 << 14)
/* Bit 13: Reserved */
#define SPI1EN (1 << 12)
#define TIM1EN (1 << 11)
#define ADC2EN (1 << 10)
#define ADC1EN (1 << 9)
/* Bit 8: Reserved */
/* Bit 7: Reserved */
#define IOPEEN (1 << 6)
#define IOPDEN (1 << 5)
#define IOPCEN (1 << 4)
#define IOPBEN (1 << 3)
#define IOPAEN (1 << 2)
/* Bit 1: Reserved */
#define AFIOEN (1 << 0)

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

// Universal (A)synchronous Receiver Transmitter  ////////////////////////////

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

#define CTRM (1 << 15)     // Correct transfer interrupt mask
#define PMAOVRM (1 << 14)  // Packet memory area over / underrun interrupt mask
#define ERRM (1 << 13)     // Error interrupt mask
#define WKUPM (1 << 12)    // Wakeup interrupt mask
#define SUSPM (1 << 11)    // Suspend mode interrupt mask
#define RESETM (1 << 10)   // USB reset interrupt mask
#define SOFM (1 << 9)      // Start of frame interrupt mask
#define ESOFM (1 << 8)     // Expected start of frame interrupt mask
/* Bits 7~5: Reserved */   //
#define RESUME (1 << 4)    // Resume request
#define FSUSP (1 << 3)     // Force suspend
#define LP_MODE (1 << 2)   // Low-power mode
#define PDWN (1 << 1)      // Power down
#define FRES (1 << 0)      // Force USB reset

// USB interrupt status register  /////

#define USB_ISTR (*(USB_BASE + 0x44))

// Reset value: 0x0000

// NOTE: Clear bits by writing a word with zeroes for the bits you want to
// clear, and ones for the bits you want to stay the same. Do not
// read-modify-write.

#define CTR (1 << 15)     // Correct transfer
#define PMAOVR (1 << 14)  // Packet memory over / underrun
#define ERR (1 << 13)     // Error
#define WKUP (1 << 12)    // Wakeup
#define SUSP (1 << 11)    // Suspend mode request
#define RESET (1 << 10)   // USB reset request
#define SOF (1 << 9)      // Start of frame
#define ESOF (1 << 8)     // Expected start of frame
// Bits 7~5: Reserved
#define DIR (1 << 4)  // Direction of transaction
// Bits 3~0: Endpoint Identifier

// USB frame number register  /////////

#define USB_FNR (*(USB_BASE + 0xNN))
#define USB_DADDR (*(USB_BASE + 0xNN))
#define USB_BTABLE (*(USB_BASE + 0xNN))

#define USB_EP0R (*(USB_BASE + 0xNN))
#define USB_EP1R (*(USB_BASE + 0xNN))
#define USB_EP2R (*(USB_BASE + 0xNN))
#define USB_EP3R (*(USB_BASE + 0xNN))
#define USB_EP4R (*(USB_BASE + 0xNN))
#define USB_EP5R (*(USB_BASE + 0xNN))
#define USB_EP6R (*(USB_BASE + 0xNN))
#define USB_EP7R (*(USB_BASE + 0xNN))

#define USB_ (*(USB_BASE + 0xNN))

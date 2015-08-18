/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */
#include "../../include/init.h"
// =============================
// USARTD1 initialization
void usartd1_init(void)
{
  // Transmitter is enabled
  // Set TxD=1
  PORTD.OUTSET=0x80;

  //8N1
  USARTD1.CTRLC=USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

  USARTD1.CTRLA=(USARTD1.CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) |
    USART_RXCINTLVL_OFF_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

  // Required Baud rate: 115200
  USARTD1.BAUDCTRLA=0x2E;
  USARTD1.BAUDCTRLB=((0x09 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x08;

  USARTD1.CTRLB=(USARTD1.CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) |
    USART_RXEN_bm | USART_TXEN_bm;
}

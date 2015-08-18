/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include "../../include/init.h"

// Disable counter 1
void tc1_disable(TC1_t *ptc)
{
  ptc->CTRLA=TC_CLKSEL_OFF_gc;
  ptc->CTRLFSET=TC_CMD_RESET_gc;
}

// Disable counter 2
void tc0_disable(TC0_t *ptc)
{
  ptc->CTRLA=TC_CLKSEL_OFF_gc;
  ptc->CTRLFSET=TC_CMD_RESET_gc;
}

// Initialization of Counter D1
// Used for LCD backlight
void tcd1_init(void)
{
  unsigned char s;
  s=SREG;
  cli();

  tc1_disable(&TCD1);
  TCD1.CTRLA=TC_CLKSEL_DIV8_gc;
  TCD1.CTRLB=(1<<TC1_CCBEN_bp) | (0<<TC1_CCAEN_bp) |
    TC_WGMODE_DS_T_gc;
  TCD1.CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

  TCD1.CTRLE=TC_BYTEM_BYTEMODE_gc;
  TCD1.INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_OFF_gc;

  TCD1.INTCTRLB=TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

  HIRESD.CTRLA&= ~HIRES_HREN1_bm;

  TCD1.INTFLAGS=TCD1.INTFLAGS;
  TCD1.CNT=0x0000;
  TCD1.PER=0x00C8;
  TCD1.CCA=0x0000;
  TCD1.CCB=0x0000;

  SREG=s;
}

// Initialization of Counter E0
// Used for buzzer
void tce0_init(void)
{
  unsigned char s;

  s=SREG;
  cli();
  tc0_disable(&TCE0);

  TCE0.CTRLA=TC_CLKSEL_DIV64_gc;

  TCE0.CTRLB=(0<<TC0_CCDEN_bp) | (0<<TC0_CCCEN_bp) | (0<<TC0_CCBEN_bp) |
    (1<<TC0_CCAEN_bp) | TC_WGMODE_DS_T_gc;
  TCE0.CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

  TCE0.CTRLE=TC_BYTEM_BYTEMODE_gc;

  TCE0.INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_OFF_gc;

  TCE0.INTCTRLB=TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

  HIRESE.CTRLA&= ~HIRES_HREN0_bm;

  TCE0.INTFLAGS=TCE0.INTFLAGS;
  TCE0.CNT=0x0000;
  TCE0.PER=0x00C8;
  TCE0.CCA=0x0000;
  TCE0.CCB=0x0000;
  TCE0.CCC=0x0000;
  TCE0.CCD=0x0000;

  SREG=s;
}

// Initialization of D0 timer
// Used for LCD clock
void tcd0_init(void)
{
  unsigned char s;

  s=SREG;
  cli();
  
  tc0_disable(&TCD0);
  TCD0.CTRLA=TC_CLKSEL_DIV256_gc;
  TCD0.CTRLB=(0<<TC0_CCDEN_bp) | (0<<TC0_CCCEN_bp) | (0<<TC0_CCBEN_bp) |
    (0<<TC0_CCAEN_bp) | TC_WGMODE_NORMAL_gc;

  TCD0.CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

  TCD0.CTRLE=TC_BYTEM_NORMAL_gc;

  TCD0.INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_OFF_gc;

  TCD0.INTCTRLB=TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

  HIRESD.CTRLA&= ~HIRES_HREN0_bm;

  TCD0.INTFLAGS=TCD0.INTFLAGS;
  TCD0.CNT=0x0000;
  TCD0.PER=0xffff;
  TCD0.CCA=0x0000;
  TCD0.CCB=0x0000;
  TCD0.CCC=0x0000;
  TCD0.CCD=0x0000;

  SREG=s;
}

/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include "../../include/init.h"

// =============================
// RTC initialization
void rtcxm_init(void)
{
  unsigned char s;

  // RTC clock source: 32.768 kHz from internal RC Oscillator
  // Select the clock source and enable the RTC clock
  CLK.RTCCTRL=(CLK.RTCCTRL & (~CLK_RTCSRC_gm)) | CLK_RTCSRC_RCOSC32_gc | CLK_RTCEN_bm;
  // Make sure that the RTC is stopped before initializing it
  RTC.CTRL=RTC_PRESCALER_OFF_gc;
  
  // Save interrupts enabled/disabled state
  s=SREG;
  // Disable interrupts
#asm("cli")

  // Wait until the RTC is not busy
  while (RTC.STATUS & RTC_SYNCBUSY_bm);
  // Set the RTC period register
  RTC.PER=0x0148;
  // Set the RTC count register
  RTC.CNT=0x0000;
  // Set the RTC compare register
  RTC.COMP=0x0000;

  // Restore interrupts enabled/disabled state
  SREG=s;

  // Set the clock prescaler: RTC Clock/1
  // and start the RTC
  RTC.CTRL=RTC_PRESCALER_DIV1_gc;

  // RTC Clock output disabled
  PORTCFG.CLKEVOUT&= ~PORTCFG_RTCOUT_bm;

  // RTC overflow interrupt: Medium Level
  // RTC compare interrupt: Disabled
  RTC.INTCTRL=RTC_OVFINTLVL_MED_gc | RTC_COMPINTLVL_OFF_gc;
}

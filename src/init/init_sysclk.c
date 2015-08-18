/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include "../init.h"

//System clocks
void system_clocks_init(void)
{
  unsigned char n,s;

  s=SREG;
  cli();

  OSC.CTRL |= OSC_RC32KEN_bm;
  while ((OSC.STATUS & OSC_RC32KRDY_bm) == 0);

  OSC.CTRL |= OSC_RC32MEN_bm;

  n=(CLK.PSCTRL & (~(CLK_PSADIV_gm |
		     CLK_PSBCDIV1_bm |
		     CLK_PSBCDIV0_bm))) |
    CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
  
  CCP=CCP_IOREG_gc;
  CLK.PSCTRL=n;

  
  OSC.DFLLCTRL=(OSC.DFLLCTRL & (~(OSC_RC32MCREF_gm | OSC_RC2MCREF_bm))) | OSC_RC32MCREF_RC32K_gc;
  DFLLRC32M.CTRL|=DFLL_ENABLE_bm;

  while ((OSC.STATUS & OSC_RC32MRDY_bm)==0);

  n=(CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC32M_gc;
  CCP=CCP_IOREG_gc;
  CLK.CTRL=n;

  OSC.CTRL&= ~(OSC_RC2MEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm);

  PORTCFG.CLKEVOUT&= ~(PORTCFG_CLKOUTSEL_gm | PORTCFG_CLKOUT_gm);
  SREG=s;
}

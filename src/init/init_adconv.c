/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include "../init.h"

#define ADC_CURRLIMIT_NO_gc (0x00 << 5)

// =============================
// ADCA initialization
// note - most of this code is generated with CodeVision
void adca_init(void)
{
  // ADCA is enabled
  // Resolution: 8 Bits
  // Free Running mode: Off
  // Gain stage impedance mode: High-impedance sources
  // Current consumption: No limit
  // Conversion mode: Signed
  ADCA.CTRLB=(0<<ADC_IMPMODE_bp) | ADC_CURRLIMIT_NO_gc | (1<<ADC_CONMODE_bp) | ADC_RESOLUTION_8BIT_gc;

  // Clock frequency: 4000.000 kHz
  ADCA.PRESCALER=ADC_PRESCALER_DIV8_gc;

  // Reference: AREF pin on PORTA
  // Temperature reference: Off
  ADCA.REFCTRL=ADC_REFSEL_AREFA_gc | (0<<ADC_TEMPREF_bp) | (0<<ADC_BANDGAP_bp);

  // Initialize the ADC Compare register
  ADCA.CMPL=0x00;
  ADCA.CMPH=0x00;

  // ADC channel 0 gain: 1
  // ADC channel 0 input mode: Differential input signal with gain
  ADCA.CH0.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;

  // ADC channel 0 positive input: ADC5 pin
  // ADC channel 0 negative input: ADC4 pin
  ADCA.CH0.MUXCTRL=ADC_CH_MUXPOS_PIN5_gc | ADC_CH_MUXNEG_PIN4_gc;

  // ADC channel 1 gain: 1
  // ADC channel 1 input mode: Differential input signal with gain
  ADCA.CH1.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;

  // ADC channel 1 positive input: ADC3 pin
  // ADC channel 1 negative input: ADC4 pin
  ADCA.CH1.MUXCTRL=ADC_CH_MUXPOS_PIN3_gc | ADC_CH_MUXNEG_PIN4_gc;

  // ADC channel 2 gain: 1
  // ADC channel 2 input mode: Differential input signal with gain
  ADCA.CH2.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;

  // ADC channel 2 positive input: ADC2 pin
  // ADC channel 2 negative input: ADC4 pin
  ADCA.CH2.MUXCTRL=ADC_CH_MUXPOS_PIN2_gc | ADC_CH_MUXNEG_PIN4_gc;

  // ADC channel 3 gain: 1
  // ADC channel 3 input mode: Differential input signal with gain
  ADCA.CH3.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;

  // ADC channel 3 positive input: ADC1 pin
  // ADC channel 3 negative input: ADC4 pin
  ADCA.CH3.MUXCTRL=ADC_CH_MUXPOS_PIN1_gc | ADC_CH_MUXNEG_PIN4_gc;

  // AD conversion is started by software
  ADCA.EVCTRL=ADC_EVACT_NONE_gc;

  // Channel 0 interrupt: Disabled
  ADCA.CH0.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
  // Channel 1 interrupt: Disabled
  ADCA.CH1.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
  // Channel 2 interrupt: Disabled
  ADCA.CH2.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
  // Channel 3 interrupt: Disabled
  ADCA.CH3.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;

  // Enable the ADC
  ADCA.CTRLA|=ADC_ENABLE_bm;
  // Insert a delay to allow the ADC common mode voltage to stabilize
  delay_us(2);
}

// ADCA channel data read function using polled mode
signed char adca_read(unsigned char channel)
{
  ADC_CH_t *pch=&ADCA.CH0+channel;
  signed char data;

  // Start the AD conversion
  pch->CTRL|= 1<<ADC_CH_START_bp;
  // Wait for the AD conversion to complete
  while ((pch->INTFLAGS & ADC_CH_CHIF_bm)==0);
  // Clear the interrupt flag
  pch->INTFLAGS=ADC_CH_CHIF_bm;
  // Read the AD conversion result
  data=pch->RESL;
  return data;
}

// ADCA sweeped channel(s) data read function
// for software triggered mode
void adca_sweep_read(unsigned char nch, signed char *pdata)
{
  ADC_CH_t *pch=&ADCA.CH0;
  unsigned char i,j,m;

  // Sweep starts with channel 0
  j=ADC_CH0START_bm;
  // Prepare the AD conversion start mask for the sweeped channel(s)
  m=0;
  i=0;
  do
    {
      m|=j;
      j<<=1;
    }
  while (++i<nch);
  // Ensure the interrupt flags are cleared
  ADCA.INTFLAGS=ADCA.INTFLAGS;
  // Start the AD conversion for the sweeped channel(s)
  ADCA.CTRLA=(ADCA.CTRLA & (ADC_DMASEL_gm | ADC_FLUSH_bm | ADC_ENABLE_bm)) | m;
  // Read and store the AD conversion results for all the sweeped channels
  for (i=0; i<nch; i++)
    {
      // Wait for the AD conversion to complete
      while ((pch->INTFLAGS & ADC_CH_CHIF_bm)==0);
      // Clear the interrupt flag
      pch->INTFLAGS=ADC_CH_CHIF_bm;
      // Read the AD conversion result
      *pdata=pch->RESL;
      pdata++;
      pch++;
    }
}

// DACB initialization
void dacb_init(void)
{
  // Operating mode: 
  // Channel 0 triggered by the event system: Off
  DACB.CTRLB=(DACB.CTRLB & (~(DAC_CHSEL_gm | DAC_CH0TRIG_bm | DAC_CH1TRIG_bm))) |
    DAC_CHSEL_SINGLE_gc;

  // Reference: 
  // Left adjust value: Off
  DACB.CTRLC=(DACB.CTRLC & (~(DAC_REFSEL_gm | DAC_LEFTADJ_bm))) |
    DAC_REFSEL_AREFA_gc;

  // DACB is enabled
  // Low power mode: Off
  // Channel 0 output: On
  // Channel 1 output: Off
  // Internal output connected to the ADCB and Analog Comparator MUX-es: Off
  DACB.CTRLA=(DACB.CTRLA & (~(DAC_IDOEN_bm | DAC_CH0EN_bm | DAC_CH1EN_bm | DAC_LPMODE_bm))) |
    DAC_CH0EN_bm | DAC_ENABLE_bm;
}

// =============================
// Function used to write data to a DACB channel ch
void dacb_write(unsigned char ch, unsigned int data)
{
  register unsigned char m=ch ? DAC_CH1DRE_bm : DAC_CH0DRE_bm;
  // Wait for the channel data register to be ready for new data
  while ((DACB.STATUS & m)==0);
  // Write new data to the channel data register
  if (m==DAC_CH1DRE_bm) DACB.CH1DATA=data;
  else DACB.CH0DATA=data;
}

/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>

//Configuration
#include "init.h"
#include "defines.h"
#include "allocations.h"

//UI modules
#include "comm.h"
//#include "ui/ks0713.h"
//#include "ui/lcd_lib.h"
//#include "ui/font5x7.h"

//Oscilloscope modules

//Main thing happens here

int main(){

  //Initializations

  //Load eeprom variables
  load_eeprom();
  
  //System clocks initialization
  system_clocks_init()
  
  //Ports initialization
  ports_init();
  vports_init();

  //Timer/counters TCD0, TCD1 and TCE0 init
  tcd0_init();
  tcd1_init();
  tce0_init();

  //Events initialization
  event_system_init();
  
  //USARTD1 initialization
  usartd1_init();

  //ADC and DAC initialization
  adc_init();
  dac_init();

  //LCD-related stuff
  power_ON;
  myglcd_init();
  myglcd_set_font(font5x7);
  test_battery();
  _delay_ms(3000);
  myglcd_clear();

  //Program initialization
  
  while(1){
    

  }
  
  return 0;
}

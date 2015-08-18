/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#include "../init.h"
#include "../allocations.h"

// =============================
// Variable initialization

void read_eeprom(void){
  backlight  = eeprom_read_byte(ADDR_BACKLT);
  volume     = eeprom_read_byte(ADDR_VOLUME);
  battery    = eeprom_read_byte(ADDR_BATTERY);
  freq_wave  = eeprom_read_word(ADDR_FREQWV);
  level_wave = eeprom_read_byte(ADDR_LEVELWV);
  type_wave  = eeprom_read_byte(ADDR_TYPEWV);
  wave_out   = eeprom_read_byte(ADDR_STATEWV);
}

void write_eeprom(void){
  eeprom_write_byte(ADDR_BACKLT, backlight);
  eeprom_write_byte(ADDR_VOLUME, volume);
  eeprom_write_byte(ADDR_BATTERY, battery);
  eeprom_write_word(ADDR_FREQWV, freq_wave);
  eeprom_write_byte(ADDR_LEVELWV, level_wave);
  eeprom_write_byte(ADDR_TYPEWV, type_wave);
  eeprom_write_byte(ADDR_STATEWV, wave_out);

}

void variable_init(void)
{  
  if(volume>100){volume=100;}
  mode=mode_stop;
  smode=0;
  if(freq_wave>=704){freq_wave=124;} //1000hz
  if(level_wave>=30){level_wave=8;}// 300mv
  if(type_wave>=4){etype_wave=0;} // sinus ,
  if(wave_out>200){ewave_out=0;}
  adc_rate=6;
  adc_gain=1;
  act_cur_x=47;
  act_cur_y=31;
}

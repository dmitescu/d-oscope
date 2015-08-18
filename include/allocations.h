/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#ifndef _ALLOCATIONS_
#define _ALLOCATIONS_

#include <stdint.h>

//Adresses for EEPROM constants

#define ADDR_BACKLT  (uint8_t *) 0x00
#define ADDR_VOLUME  (uint8_t *) 0x01
#define ADDR_BATTERY (uint8_t *) 0x02
#define ADDR_FREQWV  (uint16_t *) 0x03
#define ADDR_LEVELWV (uint8_t *) 0x05
#define ADDR_TYPEWV  (uint8_t *) 0x06
#define ADDR_STATEWV (uint8_t *) 0x07

//Global variables which will be used 

uint8_t backlight;
uint8_t volume;

uint8_t battery;

uint16_t freq_wave;
uint8_t level_wave;
uint8_t type_wave;
uint8_t wave_out;

uint8_t mode, smode;
uint8_t fwave[256];

uint8_t act_cur_x, old_cur_x, act_cur_y,
  old_cur_y, act_cur_trig, old_cur_trig,
  adc_gain, old_gain, adc_rate, old_rate;

uint8_t nrbeep, lenbeep, len_beep;

#endif

/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

// This file contains functions which
// initialize the board with all the
// required functions, ports, etc.

#ifndef _BOARD_CONF_
#define _BOARD_CONF_

#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdint.h>

//ADC or DAC conversions
void adca_init(void);
char adca_read(uint8_t channel);
void adca_sweep_read(uint8_t nch, int8_t *pdata);
void dacb_init(void);
void dacb_write(uint8_t ch, uint16_t data);

//Event system
void event_system_init(void);

//Port/Vport configuration
void ports_init(void);
void vports_init(void);

//RTC initialization
void rtcxm_init(void);

//System clocks init
void system_clocks_init(void);

//Timer init
void tc1_disable(TC1_t *ptc);
void tc0_disable(TC0_t *ptc);
void tcd0_init(void);
void tcd1_init(void);
void tce0_init(void);

//Init USART
void usartd1_init(void);
char getchar(void);
void putchar(char c);

//Init global variables
void read_eeprom(void);
void write_eeprom(void);
void variable_init(void);

#endif

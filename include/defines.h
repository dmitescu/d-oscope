/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

#ifndef _BASIC_DEFINES_
#define _BASIC_DEFINES_

//Interrupt functions
#define cli() #asm("cli")
#define sei() #asm("sei")

//Basic control over LCD, LEDs, LCD backlight and buzzer
#define power_ON  PORTR_OUT=PORTR_OUT | 0x01
#define power_OFF PORTR_OUT=PORTR_OUT & 0xFE

#define led_ON  PORTE_OUT=PORTE_OUT | 0x02
#define led_OFF PORTE_OUT=PORTE_OUT & 0xFD

#define backlight TCD1.CCB
#define ocr       TCE0.CCA

//Global variables

#endif

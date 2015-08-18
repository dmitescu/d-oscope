/*
 * Copyright (c) 2015
 * Mitescu George Dan <mitescugeorgedan @ gmail.com>
 * Distributed under MIT license
 */

/*
 * This file contains all functions defined in order for a
 * decent UI to exist. It contains the functions used by
 * USART and the LCD to display any kind of information.
 * 
 * NOTE: USB protocol is to be implemented
 */

#ifndef _COMMANDS_
#define _COMMANDS_

#define u_prompt printf("\r\n>");
#define u_ok     printf("\r\nOk\r\n");
#define i_param  printf("\r\nInvalid parameter\r\n>");

char getchar(void);
void putchar(char);

char get_usart(void);

inline void put_number(uint32_t);
uint32_t get_number(void);


//Main command functions
void USART_cmd(void);

#define _COMMANDS_

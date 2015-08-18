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

//These defines represent some functions which will
//be used frequently in the program

#include "../comm.h"

//USARTD1 getchar function
char getchar(void)
{
  char data;
  unsigned char status;

  while (1){
      while (((status = USARTD1.STATUS) & USART_RXCIF_bm) == 0);
      data = USARTD1.DATA;
      if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm))
	  == 0) return data;
    }
}

//USARTD1 putchar function
void putchar(char c){
  while ((USARTD1.STATUS & USART_DREIF_bm) == 0);
  USARTD1.DATA = c;
}

//USARTD1 USART data function
//This does the same thing as getchar,
//but without waiting for input
char get_usart(void){
  char data;
  unsigned char status;
  
  if (((status = USARTD1.STATUS) & USART_RXCIF_bm) == 0)
    return 254;
  data = USARTD1.data
  if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) != 0)
    return 255;
  return data;
}

//USARTD1 number reading/writing functions
inline void put_number(uint32_t t){
  printf("%ld", t);
}

uint32_t get_number(void){
  uint32_t t;
  char c;
  uflag = false;
  t = 0;
  while(1){
    c = getchar();
    if (c==13 || c==10){
      uflag = true;
      return t;
    }
    if (c<0x30 || c>0x39){
      uflag = false;
      return t;
    }
    c = c - 0x30;
    t = t * 10 + c;
  }
}


//Main USART COMMAND function

void USART_cmd(void){
  char c;
  int16_t t16;
  uint32_t t32;
  
  c = get_usart();
  if(c >= 255) return;

  switch (c){
  case 'v':
    printf("D-oscope, V=0.1\r\n>");
    break;
  case 'V':
    printf("Copyright (c) Mitescu George Dan 2015\r\n>");
    break;
  }
}

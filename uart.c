#include <msp430.h>
#include "uart.h"

#define TXDATA
#define RXDATA
#define BITTIME (1000000/19200)

void uartInit(){

	P1SEL |= TXDATA;
	P1DIR |= TXDATA;
	
	P1IES |= RXDATA;
	P1IFG &= ~RXDATA;
	P1IE |= RXDATA;

}


void uartPutChar(uint8_t ch) {

	TACCTL0 = OUT;
	TACTL = TASSEL2 + MC_2;
	TACCR0 = TAR;
	TACCR0 += (BITTIME);
	TXBYTE |= 0x100; //0b1_0000_0000
	TACCTL0 = CCIS_0 | OUTMOD_0 | CCIE | OUT;
	
	

}

void uartPuts(char * str) {

	while(*str != '\0'){
		uartPutChar();
	}

}


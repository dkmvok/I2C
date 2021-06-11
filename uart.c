#include <msp430.h>
#include "uart.h"

#define TXDATA
#define RXDATA
#define BITTIME (1000000/19200)

unsigned int txByte;
unsigned int rxByte;
unsigned char bitCounter;


void uartInit(){

	P1SEL |= TXDATA;
	P1DIR |= TXDATA;
	
	P1IES |= RXDATA;
	P1IFG &= ~RXDATA;
	P1IE |= RXDATA;

}


void uartPutChar(uint8_t ch) {

	txByte |= 0x100; //0b1_0000_0000
	txByte = txByte << 1;	//0b10_0000_0000
	bitCounter = 0x0A;    
	TACCTL0 = OUT;
	TACTL = TASSEL2 + MC_2;
	TACCR0 = TAR;
	TACCR0 += (BITTIME);
	TACCTL0 = CCIS_0 | OUTMOD_0 | CCIE | OUT;	
	
	while(TACCTL0 & CCIE);	

}

void uartPuts(char * str) {

	while(*str != '\0'){
		uartPutChar();
	}
}


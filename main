#include <msp430.h>
#include "i2c.h"
#include "uart.h"

#define TIME_REG_ADDR 0x00
#define CONTROL_REG_ADDR 0x0E

#define SLAVE_I2C_ADDRESS 0x68

typedef struct {
	
  unsigned char second;
  unsigned char minute; 
  unsigned char hour; 

} Date;

Date dateTime;

void stopWatchDogTimer() {
    WDTCTL = WDTPW + WDTHOLD;
}


unsigned char decToBCD(unsigned char val) {
	
  return ((val/10*16) + (val%10));
  
}


unsigned char bcdToDEC(unsigned char val) {
	
  return ((val/16*10) + (val%16));
  
}


void getDateRTC() { 

    char test;
 
	i2cStart();
	i2cWrite(SLAVE_I2C_ADDRESS << 1);
	i2cWrite(TIME_REG_ADDR);
	i2cStop();

	i2cStart();
	i2cWrite(SLAVE_I2C_ADDRESS << 1 | 1);

	dateTime.second  = bcdToDEC(i2cRead(0x00));
	dateTime.minute  = bcdToDEC(i2cRead(0x00));
	dateTime.hour    = bcdToDEC(i2cRead(0x00)); 
	
	test = dateTime.second;

	i2cStop();
}

void setDateRTC() {
	
	i2cStart();
	i2cWrite(SLAVE_I2C_ADDRESS << 1);
	i2cWrite(TIME_REG_ADDR);

	i2cWrite(decToBCD(00)); 
	i2cWrite(decToBCD(43)); 
	i2cWrite(decToBCD(20)); 

	i2cStop();
}

void setRegisters() {
	
  i2cStart();
	i2cWrite(SLAVE_I2C_ADDRESS << 1);
	i2cWrite(CONTROL_REG_ADDR); 
	i2cWrite(0x00);
	i2cStop();
	
}

void setUpRTC() {
	
	i2cInit();
	setRegisters();
	
}

void init() {
	stopWatchDogTimer();
	setUpRTC();
}
void prettyPrint(unsigned char hour,unsigned char minute){
	
	printf("Date & Time\n");
	printf(dateTime.hour);
	printf(dateTime.minute);
	
}

void main(void) {
	
	init();
	
	while(1){
		getDateRTC();
		prettyPrint(dateTime.hour, dateTime.minute);
	}
}

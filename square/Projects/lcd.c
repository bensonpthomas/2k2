#include "lcd.h"

//void delay(unsigned long int x) {
//	unsigned long int i, j;

//	for (i = x; i > 0; i--) {
//		for (j = 100; j > 0; j--)
//			_nop();
//		_nop();
//	}
//}
//void init() {
//	command(0x30);
//	command(0x30);
//	command(0x30);
//	command(0X20);
//	command(0X28);
//	command(0X0C);
//	command(0X06);
//	command(0X01);
//	command(0x80);
//	__delay_cycles(1000);
//	delay(100);
//}

//void lcd_puts(const char *s) {
//	while (*s)
//		data(*s++);
//	delay(100);
//}

//void command(unsigned int com) {
//	unsigned char temp;
//	RS0;
//	P1OUT &= 0xF0;
//	temp = com;
//	P1OUT |= com >> 4;	//SENDING UPPER MSB COMMAND BITS
//	EN1;
//	EN0;
//	P1OUT &= 0xF0;
//	P1OUT |= (temp & 0x0F);	//SHIFTING LOWER NIBBLE TO UPPER NIBBLE
//	EN1;
//	EN0;
//	__delay_cycles(3000);
//	delay(100);
//}
//////////////////////////////////////////////////
//void data(unsigned char data) {
//	unsigned char temp;
//	RS1;
//	P1OUT &= 0xF0;
//	temp = data;
//	P1OUT |= data >> 4;	//SENDING UPPER MSB COMMAND BITS
//	EN1;
//	EN0;
//	P1OUT &= 0xF0;
//	P1OUT |= (temp & 0x0F);	//SHIFTING LOWER NIBBLE TO UPPER NIBBLE
//	EN1;
//	EN0;
//	__delay_cycles(3000);
//}


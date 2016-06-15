#ifndef LCD_H_
#define LCD_H_

void init();
void lcd_puts(const char *s);
void command(unsigned int com);
void data(unsigned char data);
void delay(unsigned long int x);


#define EN0 P1OUT &= ~BIT5
#define EN1 P1OUT |= BIT5
#define RS0 P1OUT &= ~BIT4
#define RS1 P1OUT |= BIT4

#endif /* LCD_H_ */

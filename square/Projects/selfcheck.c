#include "selfcheck.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"
#include "battery_measure.h"
#include "adc.h"
#include "display.h"


void self_check (void)
{
		      relay=0;		//TEST_OFF();
					Backlight_ON();
					FAN_ON();
					BUZZER_ON();
					shift_reg(0xFFF);
	
										while(second<19900)
										{
											adc_read();
										}
					shift_reg(0x000);
					FAN_OFF();
					Backlight_OFF();
					BUZZER_OFF();
					second=0;


					do
					{
						adc_read(); //optional 
						batt_volt_measure();
						
						IWDG_ReloadCounter();  /* Reload IWDG counter */
						
						 if(one_sec)
							 {
							  one_sec=0;
							  BUZZER_TOGGLE();
							 }
					}while((batt_vltg_final>180)|(batt_vltg_final<80));
					BUZZER_OFF();
					low_batt_flag=0;
					if(fb_vltg_final>100)
					wiring_fault=1;
					else if((temperature>1680)|(temperature<200))
					thermal_fault=1;


					protection_flag=0;


}
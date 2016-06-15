/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx.h"
#include "utility.h"
#include "variable.h"
#include "adc.h"
#include "measure_mains.h"
#include "feedback.h"
#include "key.h"
#include "battery_measure.h"
#include "timer.h"
#include "changeover.h"
#include "protection.h"
#include "display.h"
#include "charger.h"
#include "selfcheck.h"

int main(void)
{
	unsigned int i;
 	i=0xFFFFFF;
	while(i--);   							//DELAY FOR DEBUGGING MODULE TO CONNECT//
	int_data();
	swt_pos=0x00;
	Port_Config();   
	ADC_Config();
	DMA_Config();
	TIM_Config();
	
	Fwrite_enable=0xFFFF;
  comm_enable=0xFFFF;
	
	EXTI4_15_Config();
	
	boot_check();
	if(boot_flag!=0xD220)
	{
		shut_down();
		shut_dwn_dly=0;
		Erase_Page_Flash();
		EEPROM_INIT();
	}
	
		Memory_Read(); 
    USART_Config(); 
	while(data_array[7]!=0x1F0F)
	{
		shut_down();
		shut_dwn_dly=0;
		BUZZER_ON();
		shift_reg(0xFFF);
		IWDG_ReloadCounter();  /* Reload IWDG counter */
	}
self_check();
User_IWDG_Init();
	
chk_key();
	User_IWDG_Init();
	relay=0;
	mains_boot=1;
	inv_boot=1;
	charger_boot=1;
	Total_AH=2000;
	display_data1=0xFFFF;
 dp[2]=0;
	while(1)
	{
		
	if(Fwrite_enable==0xFACE)
	 {
		  shut_down();
			shut_dwn_dly=0;
	    Erase_Page_Flash();
		  EEPROM_INIT();
			User_IWDG_Init();
      while(1);
   }

		chk_key();
	 		IWDG_ReloadCounter();
		adc_read();
	 		IWDG_ReloadCounter();
		gain_correction();		
	  batt_volt_measure();
	 		IWDG_ReloadCounter();
		batt_amp_measure();
	 		IWDG_ReloadCounter();
	  mains_calc();
	  mains_control();
	 		IWDG_ReloadCounter();
		protection_chk();
		change_over();
	 		IWDG_ReloadCounter();
		display_1();
				IWDG_ReloadCounter();
	if(second>20000){ one_sec=1; second=0; }	
	if(one_sec)
	{
		  process_time();
  IWDG_ReloadCounter(); 
		
			one_sec=0;
	  }
	if(display_time>5000){
				  if(swt_pos_old!=swt_pos)
		  ups_mode_buzz=1;		  	   
		  swt_pos_old=swt_pos;
		indication();
		display_time=0;
  	ups_mode_buzz=0;
	}
	}
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */



void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


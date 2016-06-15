#include "stm32f0xx_it.h"
#include "utility.h"
#include "variable.h"
#include "pwm.h"
#include "changeover.h"
#include "scom.h"




/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/





void TIM1_BRK_UP_TRG_COM_IRQHandler(void ) ////50 micro second interrupt////
{	
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
		RLY_OFF();

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		
		if(DMA_GetITStatus(DMA1_IT_TC1))
		{ 

    Mains_input=RegularConvData_Tab[0];
		Chrg_current=RegularConvData_Tab[1];
		Discha_current=RegularConvData_Tab[2];
		Batt_voltage=RegularConvData_Tab[3];
		Feedback=RegularConvData_Tab[4];
		Ntc_input=RegularConvData_Tab[5];
		Mode_selction=RegularConvData_Tab[6];
		solar_current=RegularConvData_Tab[7];
		read_ad=1;
		second++;
		display_time++;
		fivemsec_counter++;
		mains_ok_offcnt++;
		i2m_counter++;
		display_clk++;
		half_cycle_freq++;
			mains_vltg=Mains_input;       
			sample_counter_mns++; 
			
			//////////////   mains_vltg=3030-mains_vltg;   /////for 5 volts ref ///
			mains_vltg=2075-mains_vltg;  ////for 3.3 volt ref///
			
			if(mains_vltg>250)		
			{
					zc_new_mns=0;    ////////////change this for sync purspose
			}
			else if(mains_vltg<-250) 
			{
					zc_new_mns=1;  
			}
			

			if(mains_vltg<0)
			mains_vltg=-mains_vltg;
			
		
		
			if(mains_vltg>250) 
			{
							counte=0;
							hc_cycle=1;
			}
			else 
			{ 
							counte++;
							hc_cycle=0;
			}

			
			
			

			mains_total_temp = mains_vltg + mains_total_temp;
			
		

    ADC_StartOfConversion(ADC1);
    DMA_ClearITPendingBit(DMA1_IT_GL1);
		}
		
	
		gen_samp();
		
		if(charger_on){
//			TIM_SetCompare1(TIM1,500);
//			TIM_SetCompare2(TIM1,500);
				TIM_SetCompare1(TIM1,1200-charger_dutycycle);
				TIM_SetCompare2(TIM1,1200-charger_dutycycle);
		}
		else
		{		
      TIM_SetCompare1(TIM1,duty_cly);
			TIM_SetCompare2(TIM1,duty_cly1);
		}
		if(relay) RLY_ON();
  }	
}





void DMA1_Channel1_IRQHandler(void)
{
	while(1);
}

void EXTI4_15_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line7) != RESET)  //optional
  {
		///////////GPIOB->ODR ^= 0x20;
		 
		  char i;
      i = 10;
			do 
			{
				  __NOP();
			    __NOP();
			} while(--i);
			

    if((GPIO_ReadInputDataBit(GPIOB,EXT_interrupt))!=1)
    {	  
			TEST_ON();
			shut_down();
			shut_dwn_dly=0;
			inv_boot=1;
			shut_down_flag=1;
      interupt_flag=1;
      interupt_dly=0;
  	  if(mains_on_flag) mains_int_flag=1;
    }   
			
    EXTI_ClearITPendingBit(EXTI_Line7);
		 
  }
 
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		scomm();
		
	}
	
}



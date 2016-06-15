#include "changeover.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"
#include "charger.h"


void change_over (void)
{
     if((interupt_flag)&(interupt_dly>1))
     {
					if(mains_int_flag){
						TEST_OFF();
						shut_down_flag=0;
						interupt_flag=0;
						cond=0;
						mains_on_cntr=1;
						soft_start();
					}
					if((!on_mains)  & (!mains_int_flag))
					{
					if(fb_vltg_final>300)
					wiring_fault=1;
					else{
					sht_ckt_flag=1; counter_sht=0;}
					}
					mains_int_flag=0;
					interupt_flag=0;
     }
    if((wiring_fault)|(wiring_fail))
    {
      	wiring_fail=1;
       	on_mains=0;
      	mns_entry_dly=0;
      	if(fb_vltg_final<250)
      	{
      	wiring_fault=0;
      	wiring_fail=1;   
      	}
	      else
	      wiring_fail=1;
    }
    else if(!mains_on_flag)    ///no mains 
    {
			if(!mains_boot) shut_dwn_dly=0;
			mains_boot=1;
			if(!charger_boot)
			{
				charger_boot =1;
				shut_down();
			}
			cond=0;
			charger_on = 0;
			charger_enable=0;
			on_mains=0;
			fuse_blow_flag=0;
			chg_current_final=0;
			
			rly_pos_old=relay;  
			if(Feedback1<100)
			relay=0;
			if(rly_pos_old!= relay){
				fivemsec_counter=100; freq_coeff+=32768;}
			
			if((!relay)&(swt_pos)&(!protection_flag)&(!battery_open)&(!shut_down_flag)&(!wiring_fault)&(!thermal_fault)) 
			{
				if(fivemsec_counter>200)
				{		
					if(inv_boot)
					{
						inv_on_flag=1;
						switch_sine();
						mains_boot=1;
						inv_boot=0;
						first_pulse=1;
					}
				}
		  }
		  else
		  {
				if(!inv_boot)
				{
					shut_down();
					shut_dwn_dly=0;
					inv_boot=1;
				}
				if(fb_vltg_final>300 & shut_dwn_dly>3) wiring_fault=1; else wiring_fault=0;
				
			}
		}
		
		else              ///////////mains
		{
			on_mains=1;
				if(mains_boot)
				{
					freq_code=155;
					if(start_sync)
					{
						start_sync=0;
						if(((freq_coeff<3000+32768+18000)&&(freq_coeff>1000+32768+18000))||(inv_boot)||(shut_down_flag)||(thermal_fault))
						{
							shut_down();
							shut_dwn_dly=0;
							i2m_counter=0;
							mains_boot=0;
							inv_boot=1;	
							freq_code = 164;
							mains_on_cntr=1;
						}
					}
				}
				else if( i2m_counter>5)
				{
//					RLY_OFF();
					if(Feedback1<100)
					{relay = 1;//	TEST_ON();
					i2m_counter =6;
				  charger_enable=1;
					swich_softstart=0;
					gain_code = 700;
					}
				}
			
		
			if(charger_enable&&(!battery_open)&&(!shut_down_flag)&&(!thermal_fault))
			{
				if(mains_on_cntr==1)
				{

						charge_side=0;
						soft_start();
				}
				if(mains_on_cntr>3)
						fuse_blow_chk();
				if(mains_on_cntr>4)  
				{
					if(mains_final>charger_on_vol)
						charger_on=1;
					else if(mains_final<charger_off_vol)
					{
						shut_down();
						charger_on = 0;
						mains_on_cntr=1;
					}
				}
				if(mains_on_cntr>6)    
				{
					if(charger_boot && charger_on)
					{
						 if(charge_side)
								switch_lower();
						 else
								switch_lower();
						 
						 charge_arm_swap_counter=0;
						 charger_boot=0;
						 if(!swap)
							 soft_start();
						 else
							 swap=0;
					}
					else if(charge_arm_swap_counter>29)
					{
						charge_arm_swap_counter=0;
						charge_side^=1; 
//						mains_on_cntr=6;
						charger_boot=1;
						shut_down();
						swap=1;
					}
					else
					mains_on_cntr=11;
				}
				else
				{
					charger_on=0;
					charger_boot=1;
				}			
		}
	}		
}
		
			
			
			
			
			
//			
//			/////////////////////////////////////////////////////////////////////////////
//						mains_boot=1;
//	//	      battery_open=0;
//		//      chg_current_final=0;
//		     // charger_fail_flag=0;
//		    //  counter_scr_retry=0;
//		     // SCR_FAIL=0;
//		    // RLY_ON();
//		if(charger_on)
//			{
//			charger_on=0;
//			shut_down();
//			charger_boot=1;
//			}


//		on_mains=0;
//		rly_pos_old=(GPIOF->ODR & 0x02);   /////////////////////////rly_pos_old= MAINS_RLY;  
//  //		RLY_ON();
//	//		CHG_RLY_ON();
//			
//		if(rly_pos_old!= (GPIOF->ODR & 0x02))        //////////////////////////if(rly_pos_old!= MAINS_RLY)
//		fivemsec_counter=0;
//		
//		

//					
//		    //  mains_sync_wait=0;
//		    //  mains_sync_flag=0;
//		    //  charger_on=0;
//		    //  fuse_blow_flag=0;
//		   //   cond=0;
//		      
//		      if((swt_pos)&(!protection_flag)&(!shut_down_flag)&(!wiring_fault)) ///////no mains & inverter on
//			    {
//					charger_on=0;
//		      inverter_on();
//		      
//		      mains_off_cntr=0;
//		   
//		      }
//					else
//					{
//						if(!inv_boot){
//							  shut_down();
//								inv_boot=1;
//								}			
//								if((swt_pos)|(!mains_on_flag))
//								{
//									RLY_ON(); 
//									on_mains=0;

//										
//										if(mains_off_cntr>6)
//										{
//											 mains_off_cntr=10;
//											 if(fb_vltg_final>500) 
//											 wiring_fault=1;
//											 
//										}
//								}
//								else
//								mains_off_cntr=2;
//		       }

//   }
//   else          ///AC mains present and charging
//   {
//							on_mains=1;
//							if(swt_pos)
//							mains_off_cntr=0;  //27-02-15 sud changed spelling
//							else
//							mains_off_cntr=5; //27-02-15 sud changed spelling

//							if(mains_boot)
//							{
//								TEST_ON();
//								freq_code=155;
//								if(start_sync)
//								{
//									start_sync=0;
//									
//									if(((freq_coeff<3000)&&(freq_coeff>1000))||(inv_boot))
//									{
//										shut_down();
//										i2m_counter=0;
//										on_mains =1;
//										mains_boot=0;
//										inv_boot=1;	
//										freq_code = 164;
//										mains_on_cntr=1;
//										charger_boot=1;
//										charger_on=0;
//										charge_side=0;
//										TEST_OFF();
//									 
//						}}}
//						else if( i2m_counter>200 )
//						{
//							RLY_OFF();
//							i2m_counter =201;
//							
//						
//						}
////					if((mains_final<charger_off_vol)&&(!charger_boot))    //20-03-15 sandeep hysterisis
////					{
////							shut_down();
////							charger_boot=1;
////							charger_on=0;
////							mains_on_cntr=1;
////												
//////					  zc_charging_count=0;
//////					  soft_start();
////					}
////									
////									
//if(mains_on_cntr==1){									
//						soft_start();
////					charger_fail_flag=0;
////					counter_scr_retry=0;
////					ups_buzz=0;
//						Total_chg_crnt=0;

//										}
////			
////									
//									if(mains_on_cntr>4)  
//									{
//										if((mains_final>charger_on_vol))     // && mains_charger        //20-03-15 sandeep hysterisis
//										charger_on=1;
//									}
//////											
//										if(mains_on_cntr>6)     ///////charger delay reduced 1 seconds
//										{

//											if(charger_boot && charger_on)
//											{
//												if(charge_side)
//													switch_higher();
//												else
//													switch_lower();
//												charge_arm_swap_counter=0;
//												charger_boot=0;
//												charger_dutycycle=0;
//											}
////											else if(charge_arm_swap_counter>29)
////											{
////												charge_side^=1; 
////												mains_on_cntr=5;
////												charger_boot=1;
////												shut_down();
////											}
//											else
//											mains_on_cntr=11;
//										}
//										else
//										{
//											charger_on=0;
//											charger_boot=1;
//										}
////										

////	    
////	    
////	             }  
//    
//    }}
//   



void shut_down (void)
{
			TIM_OCInitTypeDef  TIM_OCInitStructure;
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
			TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
		  TIM_OCInitStructure.TIM_Pulse = 0x00;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC2Init(TIM1, &TIM_OCInitStructure);
			inv_on_flag=0;
//inv_on_flag=0;
//PWM1_OFF();
//PWM2_OFF();
//pwm_stop();
//duty_cycle=0;
//inv_boot=1;
//ups_buzz=0;
dischg_current_final=0;
dischg_current_avg=0;
//ld_counter=0;

}

void fuse_blow_chk (void)
{
		if((fb_vltg_final<100)&(on_mains & mains_on_flag))
		{      
			fuseflag_counter++;
			
					if(fuseflag_counter >10000)
					{
					fuseflag_counter=10002;	
					shut_down();
					fuse_blow_flag=1;
					charger_on=0; 
					soft_start();
					mains_on_cntr =1;
					}
			
		}
		else
		{fuse_blow_flag=0; fuseflag_counter=0;}

}

void inverter_on(void) 
{  
		if(fivemsec_counter>200)//24-03-15 sandeep value made 50 
		 {		
			 if(inv_boot)
						{
								//freq_coeff=0;
								switch_sine();
//							if(!zc_old_mns)
//							mode=3;
//							else
//							mode=1;
//							
//							if((!INV_UPS)&&(mains_off_cntr<4))  
//							duty_cycle=16000; ///28000 old value sandeep 24-3-15
//							else
//							duty_cycle=3000;  ///10000
//									
//							if(swich_softstart)duty_cycle=100;
//							
//							swich_softstart=0;
							mains_boot=1;
							inv_boot=0;
//							inv_on_flag=1;
//							pwm_start();
//							TIM1->ARR=30000;  ////edited to 30000  sandeep 24-3-15/////

//						}

		 }
	

}}


void mains_sync(void) 
 {   
//       if((inv_on_flag)&(swt_pos))
//         {     
//           
//							 if((zc_new_mns)&(zc_upr_half)&(half_cycle_freq>37)&(half_cycle_freq<41))
//							 {
//										mains_sync_flag=1;
//										mains_on_cntr  =1;
//				
//							 }    
//							else
//							{
//										if(mains_sync_wait>0)
//										{
//					 
//													 mains_sync_wait=0;
//													 if(sync_cond)
//													 duty_cycle=duty_cycle+100;
//													 else
//													 duty_cycle=duty_cycle-100;
//													 
//													 if(duty_cycle>61000)
//													 sync_cond=0;
//													 
//													 if(duty_cycle<57000)
//													 sync_cond=1;
//													 
//										}
//							}	
//		     }
//         else
//         {
//	
//         mains_sync_flag=1;
//         mains_on_cntr  =1;
//         }
       
 }
 void switch_sine (void)
 {
	 		TIM_OCInitTypeDef  TIM_OCInitStructure;
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
			TIM_OCInitStructure.TIM_Pulse = 0x00;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC2Init(TIM1, &TIM_OCInitStructure);
 }
  void switch_lower (void)
 {	
	 		TIM_DeInit(TIM1);
			TIM_Config3();
 }
  void switch_higher (void)
 {
	 	 	TIM_DeInit(TIM1);
			TIM_Config2();		
 
 }






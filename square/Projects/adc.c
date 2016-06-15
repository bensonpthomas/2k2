	#include "variable.h"
	#include "adc.h"
	#include "charger.h"
	#include "changeover.h"
	#include "utility.h"
	#include "stm32f0xx.h"
	#include "feedback.h"



	unsigned int lpf(unsigned int new_val,unsigned int old_val,unsigned char hp,unsigned char lp)
	{
			unsigned int y;
			y=(new_val*hp+(old_val*lp))/100;
			return   y;
	}  
	int lpf1(int new_val,int old_val,unsigned char hp,unsigned char lp)
	{
			int y;
			y=(new_val*hp+(old_val*lp))/100;
			return   y;
	}  
	void adc_read (void) 
	{  
			
			if(read_ad)
				{ 
					Total_chg_crnt=Total_chg_crnt+Chrg_current;
					sample_counter_amp++;
					
					fb_chk();
					mns_zero_chk();
					sample++;
					if(sample>1)
					sample=0;
					switch (sample)
					{
				 

							case(0): 
										 if(Batt_voltage > 3470)  ///added on 10/3/15 for battery removal durng chrging @ 17.1 v
											{ 
												batt_open_counter=0;
												battery_open=1;
												mains_on_cntr=0;
												cond=0;
												charger_on = 0;
												charger_enable=0;
												charger_boot=1;
												shut_down();
												shut_dwn_dly=0;
												
											}
											if(Batt_voltage < 3100 && batt_open_counter >10)
											{												
												battery_open=0;
												batt_open_counter=12;
											}
											batt_vltg=lpf(Batt_voltage,batt_vltg,90,10);
											chk_batt=1;                     
												 
									 
							break;

							case(1): 
											temperature_final = lpf(Ntc_input,temperature_final,10,90);
											//temper_old=Ntc_input+temper_old;
											//temper_final=temper_old/2;
											//temperature_final=(4095-temper_final)*150/1024; //data_array[5];   ///////////////////////edited data_array[5] as 50
											//temperature = temperature_final; 
											//temper_old=Ntc_input;  
												
											Mode_selction_old = Mode_selction + Mode_selction_old;	
											Mode_selction_avg = Mode_selction_old/2 ;
											Mode_selction_old = Mode_selction ; 
											
							break;
										
							default:
							sample=0;
							break;
					}
				
				read_ad=0;
				
				
				
				
			} 
	}

	void mns_zero_chk (void)
	{    
			
    if((!INV_UPS)&&(counte>50)&&(swt_pos)&&(inv_boot))
    {
			
    	mains_ok=0;
    	counte=100;
    	mains_final=0;
	    mains_on_flag=0; 
			mns_entry_dly=0;
//    	RLY_ON();
			if(Feedback1<100){
			relay=0;		//TEST_OFF();
    	if(on_mains)
				fivemsec_counter=100;
    	change_over();
		}
    }
    else
    {
				 

			
					 if(zc_new_mns!=zc_old_mns)
					 {
							
								chg_update_flag=1;
						    
								zc_old_mns=zc_new_mns;
								Total_chg_crnt_Final=Total_chg_crnt;
								sample_counter_amp_final=sample_counter_amp;
							//	if(sample_counter_amp_final>5)
							//	{
//											Total_chg_crnt_Final+=(sample_counter_amp_final*50);
											if(Total_chg_crnt_Final<0) Total_chg_crnt_Final=0;
											Avg_chg_crnt_temp = Total_chg_crnt_Final/sample_counter_amp_final;
											Avg_chg_crnt_temp_mul = (Avg_chg_crnt_temp *data_array[6]);
											chg_current_final =lpf((Avg_chg_crnt_temp_mul >> 17),chg_current_final,20,80);
											
											
								sample_counter_amp=0;
								Total_chg_crnt=0;
		
				
		 
								 if(zc_new_mns)
								 {
									start_sync = 1;
									half_cycle_freq_final=half_cycle_freq;
									sample_counter_mns_final=sample_counter_mns;   ///removed /10 sandeep 20-3-15    
									mains_total=mains_total_temp;	
									if(inv_boot)
										freq_coeff=500+32768;
									mains_total_temp=0;
									sample_counter_mns=0;
									half_cycle_freq=0;
								 }

							
								
						
								 
					}   
					if(sample_counter_mns>500)//for mains fail in inveryer mmode  indication
					{
								 
								sample_counter_mns=501;//New Added
								half_cycle_freq_final=0;
					}
					
		 }
			
		if(chg_update_flag && counte==0){
	    charging();		chg_update_flag=0;}
	 
	}






#include "battery_measure.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"
#include "charger.h"
#include "adc.h"


void batt_volt_measure (void)
{
	if(chk_batt)   ////400 micro seconds
	{       
  	chk_batt=0;
	  batt_counter++;
	  batt_vltg_avg=batt_vltg_avg+batt_vltg;
		if(batt_counter==100)
		{
	  batt_final=batt_vltg_avg/batt_counter; 
		batt_vltg_final_mul=(batt_final *data_array[1]); // );	
		batt_vltg_final =	(batt_vltg_final_mul >> 16)+3;		//diode
	 	
		if(dischg_current_avg>100 && (dischg_current_filt/100)<30)                         //for equilizing the effect of load on battery voltage
		batt_vltg_final=batt_vltg_final;
		batt_vltg_final2=batt_vltg_final*battery_count;
		
		batt_counter=0;
		batt_vltg_avg=0;
	
		}
		
		//////////////////////battery flag delay routine 24-3-15 sandeep//////////
		if(!low_batt_buzz)low_batt_buzz_1=(batt_vltg_final<107|batt_vltg_final>180)?1:0;
		else low_batt_buzz_1=(batt_vltg_final<108|batt_vltg_final>180)?1:0;
		low_batt_bit_1=(batt_vltg_final<104|batt_vltg_final>180)?1:0;
		
		
		if(low_batt_buzz_1)batt_counter_1++;  else  batt_counter_1=0; 
		if(low_batt_bit_1) batt_counter_2++;  else  batt_counter_2=0;
		
		if(batt_counter_1>500) ///200 milli seconds delay
		{low_batt_buzz=1;batt_counter_1=502;} 
		else 
		{low_batt_buzz=0;}
				
		if(batt_counter_2>5000 ) /////400 millisecons delay
		{low_batt_bit=1;batt_counter_2=5002;} 
		else
		{low_batt_bit=0;}
		///////////////////////////////////////////////////////////////////////////	
		
		
		if(low_batt_bit)
		{
			low_batt_flag=1;counter_lb=0;
		}
		else{}
			
	}
		
	
	
}


void batt_amp_measure (void)
{
	
	
	
	
	

	dischg_current_filt=lpf(dischg_current_filt,dischg_current_avg,90,10);
	
	if(dischg_current_filt>batt_power*100/(battery_count*batt_vltg_final))  ///44 amp
	{ 
		over_load_counter++;
		if(over_load_counter>10000){
			over_load_counter=11;
	   over_load_start=1;
	   ovr_ld_buzz=1;}
	}
	else if((dischg_current_filt<batt_power*98/(battery_count*batt_vltg_final))&&over_load_start)
		{
			over_load_counter=0;
			over_load_start=0;
	   ovr_ld_buzz=0;
	   surge_counter_load=20;
	   surge_counter=0;
		}
		
	else if(!over_load_start)
	{
		over_load_counter=0;
	   over_load_start=0;
	   ovr_ld_buzz=0;
	   surge_counter_load=20;
	   surge_counter=0;
	
	}
	
	if(dischg_current_avg>batt_power*200/(battery_count*batt_vltg_final))  //for 200% load 1 sec
	surge_counter_load=1;
	else if(dischg_current_avg>batt_power*150/(battery_count*batt_vltg_final))//for 150% load 2 sec
	surge_counter_load=2;
	else if(dischg_current_avg>batt_power*110/(battery_count*batt_vltg_final))//for 110% load 10 sec
	surge_counter_load=10; 
	  
	  if(over_load_start)
	  {
	  if(surge_counter>surge_counter_load)
	  {
	     overload_flag=1;
	     counter_ol=0;
	  }
	  }
	   
		       if((dischg_current_final>220)|(temperature_final<800)|(chg_current_final>80))// greater then 60 Degree Centi.
           FAN_ON();
           else if((dischg_current_final<190)&(temperature_final>850)&(chg_current_final<60))//  Less then 50 Degree Cent
           FAN_OFF();  


            if((temperature_final<400)|(temperature_final>3000))//   greater then 80--(560) Degree Centi or thermistor open.  500 - 90 degC         
            {
                FAN_ON();
                thermal_fault_flag=1;
                shut_down_flag=1; 
                thermal_fault=1; 
                soft_start();
            }
            else if (temperature_final>680) //  Less then 70 Degree Cent
            {
                thermal_fault_flag=0;
                if ((!swt_cond))
                    thermal_fault=0;
            }                             
//	 

//}

}

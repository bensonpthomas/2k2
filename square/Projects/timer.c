#include "timer.h"
#include "variable.h"


void process_time(void)
{
	 
//   display_one_second++;
//	 display_one_second_1++;
//	 display_one_second_2++;
	 surge_counter++;
	 mns_recovery_counter++;
	 mains_off_cntr++;
	 mains_on_cntr++;
	 mns_entry_dly++;
//	 mains_sync_wait++;
//	 By_pass_counter++;
	 counter_lb++;
	 counter_ol++;
	 counter_sht++;
	 charge_arm_swap_counter++;
	 counter++;
   current_set=chg_ref[chg_mode]; 

 temp_counter++;
	 hr_counter++;
   interupt_dly++;
	 shut_dwn_dly++;
	 tic=1;
//	 scr_fail_counter++;
//	 charger_fail_counter++;
	 count_sec++;
//	 cntr1++;
//         
batt_open_counter++;
	 scom_timeout++;
				 if(count_sec>59)
          {
		  
              timer++;
              if((charger_on)&(Total_AH>0))
              {
                  Total_AH=Total_AH-(chg_current_final/10);
              } 
              else if(inv_on_flag)
              {
                  dis_current_total=((dischg_current_final/10)*120);
                  dis_current_total=dis_current_total/100;
                  Total_AH=dis_current_total+Total_AH;   //for 120% AH
                  
              }
							if(count_min > 9 )   // one hour//   
							{
								
								if(inv_on_flag) DR_ups_time++;
								if(mains_on_flag) { DR_mains_time++; DR_avgAC =mains_final;}
								if(charger_on) DR_charger_time++;
								
								DR_avgDC = batt_vltg_final;
								
								count_min=0;
							}
							count_min++;
							
              count_sec=0;
              
          }     
	  
	      if(hr_counter>18000)                   //if counter is greater then 5 hrs reset it
         {
             day_counter++;                
             hr_counter=0;

            if(day_counter>19)                 // if 100 hr is complete then set voltage ref
           {
             full_charging_vltg=(BATTREY_SELECTOR)?boost_vltg_tubler:boost_vltg_flat_plate;    // set boost vltg =14.2 vltg
             day_counter=0;
           }
         }
////////////////////////snooz counter///////////////////
      if(hr_counter1>43200)                   //if counter is 43200 greater then 12 hrs
      {
				 hr_counter1=0;
				
				if(snooz ==2 ) snooz=1;
				else           snooz=0;
			
			}
			
			if(scom_timeout > 4)scom_ptr=0;
      ////////////////////////////////////////////////////////					 
}


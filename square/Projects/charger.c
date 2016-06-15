#include "charger.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"
#include "adc.h"

#ifndef __charger_H
#define __charger_H


#define CHRG_MAX_WIDTH 900
#define CHRG_MIN_WIDTH 0    /////29000

void soft_start(void)
{
    dischg_current_final=0;
 
    charger_dutycycle=CHRG_MIN_WIDTH;//48000
    charger_dutycycle_old=CHRG_MIN_WIDTH;//48000
    error_old=error=0;
    temp_counter=0;
    counter=0;
    trickle=0;
    current_ref1=0;
    inc_volt=0;
    chg_current_final=0;
   
}

void charger_correction(void)
{
	if(chg_update_flag && (counte ==0))
	{
		chg_update_flag = 0;
		if(chg_current_final>101) charger_dutycycle-=2;
		else if (chg_current_final<99) charger_dutycycle+=2;
		if(charger_dutycycle>800) charger_dutycycle=800;
		if(charger_dutycycle<50) charger_dutycycle = 50;
	}

}

/* MODULE charger */
//void chk_charger(void)
//{       
//   
//            if(chg_current_final_1>300)                 //if(current>750)//   ////  //750->
//             { 
//		           cntr++;
//							 cntr1=0;
//							 if(cntr>1000)
//							 {
//											 SCR_FAIL=1;
//											 scr_fail_counter=0;
//							 }
//             }
//	
//             if(SCR_FAIL)
//             {   
//                 charger_fail_counter=0; 
//                 CHG_RLY_ON();      //////////////////CHG_RLY=1; 
//                 if(scr_fail_counter>4)
//                 {
//                   counter_scr_retry++; 
//                    if(counter_scr_retry<3)
//                     {
//                      soft_start();
//                      cond=0;
//                      SCR_FAIL=0;
//                     }
//                    else
//                    {
//                     if(counter_scr_retry==3)
//                        {temp_counter=900; charger_fail_flag_first=1; }      /////edited 17-3-15 for charger fail indication sandeep
//                     
//                     counter_scr_retry=4;
//                     charger_fail_flag=1;
//                    }
//                 } 
//              }  
//              else
//              {
//               CHG_RLY_OFF();                    ////////////////////CHG_RLY=0;
//              }
//      
//	           if(cntr1>2)
//              cntr=0;
//        
//               
//        
//          if(charger_fail_counter>10)   
//             counter_scr_retry=0;
//           if(charger_fail_counter>100) 
//            charger_fail_counter=100; 
//          
//          


//} 

//************************************************************************
//*                charger function
//************************************************************************//
void chg_calc(unsigned int ref,unsigned int present)
{
    ref_value=ref; 
    present_value=present;
    error=present_value-ref_value;
		//		if(error_old>512){ charger_dutycycle--;error_old=512;} else if (error_old<-512){error_old=-510; charger_dutycycle++;}
		//		if(error) error=1+error/2;
    charger_dutycycle=charger_dutycycle_old-(error+error_old)/4;
		if(error_old<2&&error_old>-2&&tic){ if(error_old>0)charger_dutycycle--; else if(error_old<0)charger_dutycycle++; tic=0;}
                                                                                
           if(charger_dutycycle<CHRG_MIN_WIDTH)
            charger_dutycycle=CHRG_MIN_WIDTH;

           
           if(charger_dutycycle>CHRG_MAX_WIDTH)   // 48000-> 47000 26-02-15 sud //Date April 30 2013 31500 to 30500 
            charger_dutycycle = CHRG_MAX_WIDTH;											 
	      if(chg_current_final> 200+40)         //////charger surge raised to +10 AMP
      {  
        cond=0;
        soft_start();    // Date April 30 2013    Added 
      }
   
			charger_dutycycle_old=charger_dutycycle;
			error_old=error;
					 
			
  }  

//***************************************************************************************************//
//                 MODULE FOR CHARGING CONDITIONS        called at 3Khz(327u SEC)
//***************************************************************************************************//

void charging(void)
{
	  if((charger_on)&(!thermal_fault)&(!battery_open))
    {
					  current_ref1++;
						current_ref=current_ref1/4;     /////charger climb rate increased  30-6-15
            temp_counter_compare=7200;   //////2 hours///
         
	          boost_vltg_set=full_charging_vltg;
	          batt_trickle_vltg_flp=boost_vltg_set-8;   ///// edited added -6 16/3/15 sandeep
	    
            switch(cond)
            {    
	                  case(0):        
                    batt_charging_flag=1;
                    batt_charged_flag=0;
                    batt_gravity_flag=0;
                    if(current_ref>current_set)
										{
											current_ref=current_set;
											current_ref1=current_set*4;
										}
		    
                    chg_calc(current_ref,chg_current_final);
                   
                   
                    if(batt_vltg_final_old<batt_vltg_final)
                    {
                        counter=0;
                        batt_vltg_final_old=batt_vltg_final+2;
                        if(batt_vltg_final_old>boost_vltg_set)
                          batt_vltg_final_old=boost_vltg_set;
                    }
                   
               
                    if(batt_vltg_final>batt_vltg_final_old)           
                    {
                        cond=1;                         //if batt voltage is greater then batt ref voltage then jump to gravity mode
                        voltage_ref=boost_vltg_set;
                        temp_counter=0;
                        counter=0;
                        
                    }     
                    if(counter>14400)     /// 14400 measn 4 hour 
                    {
                     full_charging_vltg=batt_vltg_final;
		                 day_counter=0;                       /////added for day counter reset 19-3-15 sandeep
                     hr_counter=0;
		                 cond=1;
		                 voltage_ref=boost_vltg_set;
		                 temp_counter=0;
		                 counter=0;
                    }
                    
                    break;
										
		                case(1):
                    if(chg_current_final>current_set)
                    voltage_ref=voltage_ref--;
                    else
                    voltage_ref=voltage_ref++;
										
                    if(trickle)
                    {   
                      if((Total_AH>10)&(timer>=30))   ///>30 edited
                      {
                      
                            if(Total_AH_old!=Total_AH)
                               Total_AH_old=Total_AH;
                             else
                              Total_AH=0;
                             
                             timer=0;
                             cond=2;
                             trickle=0;
                             soft_start();
                             voltage_ref=boost_vltg_set;
                             counter_equ++;
                             if(counter_equ>7)     ///edited for testing 7
                             {
                             	soft_start();
                             	trickle=1;
                             	counter_equ=8;
                             	cond=1;
                             	Total_AH=0;
                             }

                             
                             
                             break;
                      }
                      else
                      {
                              
                              trickle_vltg=batt_trickle_vltg_flp;
                              if(trickle_vltg>boost_vltg_set)
                                  trickle_vltg=boost_vltg_set-2;
                              if(voltage_ref>trickle_vltg)
                                  voltage_ref=trickle_vltg; 
                      }
                       batt_charged_flag=1; 
                       batt_gravity_flag=0;
                        
                    }
                    else
                    { 
                        if(voltage_ref>boost_vltg_set)
                            voltage_ref=boost_vltg_set;
                         batt_charging_flag=0;
                         batt_gravity_flag=1;
                        if(chg_current_final<40)   //// trickel current 4AMP
                        {
                            if(counter>10)
                              {
                                
                              trickle=1;
                              timer=0;
                              
                              }
                        }
                        else
                            counter=0;
                    }
	
		                 chg_calc(voltage_ref,batt_vltg_final);
                    
		                if(temp_counter>temp_counter_compare)
                    {
                        soft_start();//if batt voltage is greater then batt ref voltage then jump to trickle mode
                        cond=1;
                        trickle=1;
                        timer=0;
                                                
                    }
                    break;
                    
										case(2):
                    if(chg_current_final<40)
                    inc_volt++;
                    if(chg_current_final>current_set)
                    inc_volt=0;
                    voltage_ref=boost_vltg_set+inc_volt; 
                    if(voltage_ref>boost_vltg_set+3)
                    voltage_ref=boost_vltg_set+3;
                        
                    if(timer>=30)  ///30 edited
                    {
                     timer=0;
                     trickle=1;
                     cond=1;
                    }
                        
                       
                        chg_calc(voltage_ref,batt_vltg_final);
                        if(Total_AH<10)
                        {
                             trickle=1;
                             cond=1;
                             soft_start();
                                                      

                         }
                     break;
                    default:
                    cond=0;
				            break;
            }
        
    }
    else
    {
				charger_on=0;
	      charger_dutycycle=CHRG_MIN_WIDTH;
  	    charger_dutycycle_old=CHRG_MIN_WIDTH;
   	    batt_charging_flag=0;
   	    batt_charged_flag=0;
   	    batt_gravity_flag=0;
        chg_current_final=0;
         

    }
}


#endif

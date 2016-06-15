#include "key.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"

	void chk_key(void)
	{
			
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////	
 if( Mode_selction_avg > 4000)                              { INV_UPS=1; chg_mode=0; BATTREY_SELECTOR=0; }		//UHT 000
 
 if( Mode_selction_avg > 2200 && Mode_selction_avg < 2230 ) { INV_UPS=0; chg_mode=1; BATTREY_SELECTOR=1; }
 if( Mode_selction_avg > 2250 && Mode_selction_avg < 2300 ) { INV_UPS=0; chg_mode=2; BATTREY_SELECTOR=1; }
 if( Mode_selction_avg > 2120 && Mode_selction_avg < 2160 ) { INV_UPS=0; chg_mode=0; BATTREY_SELECTOR=1; }
 
 if( Mode_selction_avg > 1780 && Mode_selction_avg < 1820 ) { INV_UPS=0; chg_mode=1; BATTREY_SELECTOR=0; }
 if( Mode_selction_avg > 1850 && Mode_selction_avg < 1890 ) { INV_UPS=0; chg_mode=2; BATTREY_SELECTOR=0; }
 if( Mode_selction_avg > 1660 && Mode_selction_avg < 1700 ) { INV_UPS=0; chg_mode=0; BATTREY_SELECTOR=0; }
 
 if( Mode_selction_avg > 1320 && Mode_selction_avg < 1360 ) { INV_UPS=1; chg_mode=1; BATTREY_SELECTOR=1; }
 if( Mode_selction_avg > 1430 && Mode_selction_avg < 1470 ) { INV_UPS=1; chg_mode=2; BATTREY_SELECTOR=1; }
 if( Mode_selction_avg > 1150 && Mode_selction_avg < 1190 ) { INV_UPS=1; chg_mode=0; BATTREY_SELECTOR=1; }
 
 if( Mode_selction_avg > 300 && Mode_selction_avg < 340 ) 	{ INV_UPS=1; chg_mode=1; BATTREY_SELECTOR=0; }
 if( Mode_selction_avg > 500 && Mode_selction_avg < 550 ) 	{ INV_UPS=1; chg_mode=2; BATTREY_SELECTOR=0; }
 if( Mode_selction_avg < 100 ) 															{ INV_UPS=1; chg_mode=0; BATTREY_SELECTOR=0; }
 
 full_charging_vltg=(BATTREY_SELECTOR)?boost_vltg_tubler:boost_vltg_flat_plate;
 
	if( ( GPIO_ReadInputDataBit(GPIOC,SWITCH)) != 1)
 	{
				    switch_cntr++;
					
						if((swt_status_chg==1) && (switch_cntr > 2500))
						{
							
						swt_pos^=1;					
						swt_cond=swt_pos;        /////edited 1-4-15
						swich_softstart=1; 
						vout_ref=200;
						softstart_counter=0;
						gain_code =10;feed_fwd_gain=0; prop_gain=0; int_gain=0; int_error =0;
						gain_extra=0;
						swt_status_chg=0;
						switch_cntr=0;
						mute_cnt=0;
						
						}
						
						if(switch_cntr >10000) switch_cntr=0;
						
					}
					else
					{
					swt_status_chg=1;
					switch_cntr=0;
				  }
//					
//				
//				
				if ((!swt_pos)||(mains_on_flag))
				    {
				        overload_flag=0;
				       
				       sht_ckt_flag=0;
				        shut_down_flag=0;
				        rst_counter_ol=0;
								rst_counter_sht=0;
				  
				        protection_flag=0;
				       wiring_fail=0;
							sw_sht_cnt=10;
			        fb_open=0;
				    }
				    
					if(mains_on_flag||batt_vltg_final>134)
					{
					rst_counter_lb=0;
					}
	}		
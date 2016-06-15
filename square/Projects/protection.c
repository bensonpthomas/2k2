#include "protection.h"
#include "variable.h"

void protection_chk (void)
{
	if(overload_flag)
	{
		protection_flag=1;
	//	mains_off_cntr=2;
		if(counter_ol>5)
		{
		   counter_ol=0;
		   rst_counter_ol++;
		   if(rst_counter_ol<6)
		   {
		     protection_flag=0;
		     overload_flag=0;
				 swich_softstart=1; 
				 vout_ref=200;
				 softstart_counter=0;
				 gain_code =10;feed_fwd_gain=0; prop_gain=0; int_gain=0; int_error =0;
				 gain_extra=0;
		   }
		   else
		   rst_counter_ol=8;
		
		}
			
        }
	if(low_batt_flag)
	{
	  protection_flag=1;
	//	mains_off_cntr=2;
		if(counter_lb>5)
		{
		   counter_lb=0;
		   rst_counter_lb++;
		   if(rst_counter_lb<4)
		   {
				 if(batt_vltg_final<104) counter_lb=0;
				 else{
		     protection_flag=0;
		     low_batt_flag=0;
				 swich_softstart=1; 
				 vout_ref=200;
				 softstart_counter=0;
				 gain_code =10;feed_fwd_gain=0; prop_gain=0; int_gain=0; int_error =0;
				 gain_extra=0;
				 }
		   }
		   else
		   rst_counter_lb=8;
	
	  }
   }
//	if(sht_ckt_flag){
//		shut_down_flag =1;
//		if(counter_sht>5)
//		{
//			counter_sht=0;
//			rst_counter_sht++;
//			if(rst_counter_sht<5)
//			{
//				shut_down_flag=0;
//				sht_ckt_flag=0;
//				swich_softstart=1;
//				vout_ref=200;
//				softstart_counter=0;
//				gain_code =10;feed_fwd_gain=0; prop_gain=0; int_gain=0; int_error =0;
//				gain_extra=0;
//		   }
//		   else
//		   rst_counter_sht=8;
//	
//	         }
//        }
	}


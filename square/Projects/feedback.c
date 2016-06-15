#include "feedback.h"
#include "variable.h"
#include "adc.h"
#include "changeover.h"



void gain_correction (void)
{

 if(gain_update_flag)
 {
		gain_update_flag=0;
		if(!inv_boot){	
		if((swich_softstart) && (Feedback_avg < 2200)&& (gain_code<1200)){
			gain_code+=16;fb_avg_slow=Feedback_avg;}
		else
		{
			swich_softstart=0;

			
			fb_avg_slow = lpf(fb_avg_slow,Feedback_avg,90,10);
			fb_error_slow = 2200 - fb_avg_slow;
			fb_error = 2200 - Feedback_avg;	
			if(fb_error<50&&fb_error>-50)
					gain_code+=fb_error_slow/5;
			else if(fb_error>0)
					gain_code +=fb_error/5;
			else
					gain_code +=fb_error/3;
			
			
			if((Feedback_avg>1940)||(gain_code<1200))
					gain_extra-=4;
			else if(Feedback_avg<1800)
					gain_extra+=4;
		}
		if(first_pulse){ first_pulse=0;gain_code-=(prop_gain+int_gain)/2;int_error=0;gain_extra=0;}
		else if(gain_code>1400) gain_code=1400;
		if(gain_code<0) gain_code=0;
		if(gain_extra>160) gain_extra=160;
		if(gain_extra<0) gain_extra=0;
		
		softstart_counter++;
					if(gain_code>800&&Feedback_avg<400&&!inv_boot&&sw_sht_cnt==10){fb_open_cnt++;
if(fb_open_cnt>4){			fb_open=1; shut_down_flag=1;}}
else fb_open_cnt=0;

		//		if(gain_code>800&&Feedback_avg<400&&!inv_boot){ /*fb_fail=1*/; shut_down_flag=1;} 
	//	gain_code=1000;
	//	gain_extra=0;
}
}}




//void gain_correction (void)
//{

// if(gain_update_flag)
// {
//		gain_update_flag=0;
//		if(!inv_boot){
//				if(!swich_softstart) vout_ref=2200;
//		if(swich_softstart && gain_code<1200 &&vout_ref <2200 ) vout_ref+=40;
//		
//		
//			
//			
//			feed_fwd_gain = vout_ref/3; 
//			
//			fb_error = vout_ref - Feedback_avg;
//			if(fb_error>1600) fb_error =1600; else if(fb_error<-1600) fb_error =-1600;
//			if(fb_error>30&&fb_error<-30) fb_error =0;
//				prop_gain = fb_error/4;
//			
//			
//			
//			fb_error = vout_ref - Feedback_avg;
//			int_error+=fb_error<<10;
//			int_gain =(int_error>>16)&0x0000ffff;
//			if(int_gain<0) int_gain=0; else if (int_gain>600){ int_gain =600; int_error -=fb_error<<12;}
//			gain_code = feed_fwd_gain + prop_gain+ int_gain;
//			
//			
//			if(first_pulse){ first_pulse=0;gain_code-=(prop_gain+int_gain)/2;int_error=0;gain_extra=0;}
//			else if(((Feedback_avg>1820)||(gain_code<1200))&&(!swich_softstart))
//			gain_extra-=4;
//			else if(Feedback_avg<1800)
//			gain_extra+=4;
//			
//		
//		if(vout_ref >=2200) swich_softstart=0;
//		
//		if(gain_code>1400) gain_code=1400;
//		if(gain_code<0) gain_code=0;
//		if(gain_extra>160) gain_extra=160;
//		if(gain_extra<0) gain_extra=0;

////	gain_code=gain_code_dummy; gain_extra=0;
//		softstart_counter++;
//		if(gain_code>800&&Feedback_avg<400&&!inv_boot){ /*fb_fail=1*/; shut_down_flag=1;} 
//}
//}}
void fb_chk (void)
{    
	  
		Feedback1=2075 - Feedback;
		if(Feedback1<0) Feedback1 = -Feedback1; 
		Feedback_acc+=Feedback1;
		fb_cntr++;
		
		if(sample_no ==0) test1 = Feedback_acc;
		if(sample_no ==32) test2 =Feedback_acc;
	  
		
		current_acc += Discha_current;
		if(dis_current_peak<Discha_current) dis_current_peak=Discha_current;
		
		if(sample_no==0/*||sample_no==32*/)
			fb_flag=1;
		else if(fb_flag)
		{
			fb_flag=0;
			fb_flag1=1;
			gain_update_flag=1;
	
		}
			
		if(fb_flag1){
			Feedback_avg = ((Feedback_acc*data_array[3])/(fb_cntr*1024));//-((dischg_current_final*3)/10);
			fb_vltg_final = Feedback_avg; 
			dischg_current_avg = lpf(dischg_current_avg,((current_acc*data_array[4])/(fb_cntr*32768)),80,20);
			current_acc=0;
			dischg_current_final = dischg_current_avg;
			fb_cntr=0;
			Feedback_acc=0;
			fb_flag1=0;
			chk_load=1;
			
			if((dis_current_peak/(Batt_voltage>>4))>15){ sw_sht_cnt++; gain_code-=fb_error/5;}
			else sw_sht_cnt--;
			if(sw_sht_cnt<10) sw_sht_cnt=10;
			if(sw_sht_cnt>30)
				{
				shut_down();
				shut_dwn_dly=0;
				inv_boot=1;
				shut_down_flag=1;
				sht_ckt_flag=1;
				softstart_counter=0;
				}
				dis_current_peak=0;
		}
}

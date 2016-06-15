#include "pwm.h"
#include "variable.h"
#include "utility.h"
#include "stm32f0xx.h"




void pwm_gen(void)
{
		thre_thetausn=(e_degree & 0xf);	
	
		sample_no=(e_degree/16);
	
		sample_present=cos64_ary[sample_no];
		sample_post=cos64_ary[sample_no+1];
		if(sample_no==31) sample_post =0x0000; if(sample_no==63) sample_post =0xFFFF;
//	if(((sample_present - sample_post)>0x7FFF)||((sample_post- sample_present)>0x7FFF)) sample_post= sample_present;
	  if(sample_post>sample_present){
	  angle=sample_post-sample_present;
	  multipication= ((angle/4) * thre_thetausn)/4;  
		sample_present+=multipication;}
		else if(sample_post<sample_present)
		{
			angle=sample_present-sample_post;
			multipication= ((angle/4) * thre_thetausn)/4;
			sample_present-=multipication;
		}
}

void gen_samp(void)
{

		freq_coeff=freq_coeff+freq_code;
	  e_degree=(freq_coeff>>6) & 0x03FF;  ///masking maximum value 1023 
		pwm_gen();
		mod_ary=sample_present;
		e_degree=(e_degree+phase_shift)&0x03FF;
		pwm_gen();
		mod_ary1=sample_present;

	
/*###############################################################################################*/
//	  Gain calculation
/*###############################################################################################*/	
             
	  pwm_ptrs3=gain_code+gain_extra;
	//	pwm_ptrs3=260;

		pwm_ptrs = mod_ary*pwm_ptrs3;	

        
		pwm_ptrs2 = mod_ary1*pwm_ptrs3;	

	
		if(pwm_ptrs < -(REF_INDEX<<16))
			pwm_ptrs = -(REF_INDEX<<16);
		if(pwm_ptrs>REF_INDEX<<16)
			pwm_ptrs = REF_INDEX<<16;
		
		if(pwm_ptrs2<-(REF_INDEX<<16))
			pwm_ptrs2 = -(REF_INDEX<<16);
		if(pwm_ptrs2>REF_INDEX<<16)
			pwm_ptrs2 = REF_INDEX<<16;

  duty_cly1	=(pwm_ptrs)/65536+REF_INDEX;
	duty_cly =(pwm_ptrs2)/65536+REF_INDEX;
					 
	
		
}
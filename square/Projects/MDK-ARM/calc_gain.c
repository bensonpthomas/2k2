#include "calc_gain.h"
#include "variable.h"


void CNTRL_GAIN_CODE(void)	
{
			v_out_err=v_out_ref-Feedback_avg;
			prop_gain();		
			intgrl_gain();
			feed_frd();
			
}

//////////////////////////////////////////////////////////////////////////
void CALC_GAIN_CODE(void)
{			
		
			gain_code=feed_frd_off+intgrl_off_gain+prop_off_gain;
//			if(gain_code>=0xB000)
//			gain_code=1;
//			else
//			gain_code=mask(1,32767,gain_code);
		
}


///////////////proportonial gain calculation///////////////////////////////

void prop_gain(void)
{
	//	v_out_err_temp=L_abs(v_out_err);
		if(v_out_err_temp>20&&v_out_err_temp<-20)			
		{
		    
//		    v_out_err_temp=s_mask(-511,511,v_out_err);
//		    
//		 //   var11=v_out_err_temp*8;
//				
//			v_out_err_temp=__extract_h(L_mult(0x7000,(v_out_err_temp<<3)));//7000
//		
//			v_out_err_temp=s_mask(-8191,4096,v_out_err_temp);
								
			prop_off_gain=v_out_err_temp;	
		 }

}
///////////////intergral gain calculation///////////////////////////////

void intgrl_gain(void)
{

			v_out_err_temp=v_out_err;
			//v_out_err_temp1=L_abs(v_out_err_temp);
			
			if(v_out_err_temp1<10)
			v_out_err_temp1=0;	
		    else 
		    {
		    v_out_err_temp1=mask(20,300,v_out_err_temp1);
		    if(v_out_err_temp<0)
			v_out_err_temp1=__negate(v_out_err_temp1);
		    }
		        
			int_gain_err=v_out_err_temp1;	
			int_gain=int_gain_err;
			int_gain=L_mult(int_gain,0x6000);
		//	int_gain=int_gain*0x8000;
			int_gain_1=int_gain_msw;
			int_gain_1=(int_gain_1<<16)+int_gain_lsw+int_gain;
			int_gain_msw=int_gain_1>>16;
			int_gain_msw=s_mask(-8191,12287,int_gain_msw);       //25000
			int_gain_lsw=int_gain_1&0x0000ffff;
			intgrl_off_gain=int_gain_msw;
			
		/*	int_gain_1=int_gain_1+int_gain;
		    intgrl_off_gain=__extract_h(int_gain_1);*/
			
			
			
}
///////////////feed_frd gain calculation////////86///////////////////////
void feed_frd(void)
{

			v_out_ref=mask(0,volt_high_mask,v_out_ref);
		    v_out_ref=(v_out_ref<<3);    //3                         //2300*8=18400
 	   		feed_frd_off=__extract_h(L_mult(v_out_ref,data_array19)); //29175   //NEED 16383 FOR 50 % GAIN
 	       
 /*   		v_out_ref=uns_mask(2047,0,v_out_ref);
			v_out_ref=v_out_ref<<4;
			feed_frd_off=__extract_h(L_mult(v_out_ref,0x5F00));
*/
}
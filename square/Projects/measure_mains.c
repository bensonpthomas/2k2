#include "measure_mains.h"
#include "variable.h"
#include "adc.h"

	    void check_L_H(unsigned short low_vltg,unsigned short high_vltg,unsigned short low_freq,unsigned short high_freq)
        {
       
         mains_ok=(mains_final<low_vltg| mains_final>high_vltg | freq_final<low_freq | freq_final>high_freq )?0:1;                 
        }

       void check_H_L(unsigned short low_vltg,unsigned short high_vltg,unsigned short low_freq,unsigned short high_freq)
          {
            
           mains_ok=(mains_final>low_vltg & mains_final<high_vltg& freq_final>low_freq & freq_final<high_freq)?1:0;        
          }
					
					
					
					
					
					
void mains_calc (void)     
{   
				 half_freq_final=(half_cycle_freq_final);
         freq_final=200000/half_freq_final;
	
         mains_final_new=mains_total/sample_counter_mns_final;
				 mains_total_mul=(mains_final_new * data_array[2]);
				 mains_final_old = mains_total_mul >> 12;
				 mains_final=lpf(mains_final_old,mains_final,50,50);
				// mains_final = mains_final_old; 
	
	
				 if(half_cycle_freq > 600)     
	  {
	   half_cycle_freq=605;
	   mains_final=0;
	  }
	  
	   if(!INV_UPS) 
	   Slide_inups=1;////ups mode///
	   else 
	   Slide_inups=0;////inv mode///
	 
	
	  
	            if(swt_pos && Slide_inups) 
							{ 
		                if(mains_ok)
	                  check_L_H(ups_low_cut,ups_hi_cut,470,530);     
	                  else
	             	    check_H_L(ups_low_cut_rec,ups_hi_cut_rec,490,510);
	              
							}
							else if(swt_pos && !(Slide_inups))       
							{
							      if(mains_ok)
	                  check_L_H(inv_low_cut,inv_hi_cut,430,570);
	                  else
	             	    check_H_L(inv_low_cut_rec,inv_hi_cut_rec,450,550);
	               
							}
	            else 
							{
										if(mains_ok)
	                  check_L_H(extra_low_cut,inv_hi_cut,430,570);      
	                  else
	              	  check_H_L(extra_low_cut_rec,inv_hi_cut_rec,450,550);  
							}
	  
	
	   
              if(!mains_ok)
              {
                if((!INV_UPS)&(swt_cond))
                 check_H_L(1850,2550,470,530);       //(68,48,98,74);
                 else
                 check_H_L(1050,2850,430,570);      //(73,28,105,70);
                
                if(mains_ok)
                 mains_ok_temp=1;
                else
                 mains_ok_temp=0;
          
                  mains_ok=0;

                   
                   if(mains_ok_temp)
                   {
                      if(mns_recovery_counter>60)   ///1 minute delay
                        mains_ok=1;
                   }
                   else
                        mns_recovery_counter=0;
             }
			
}
    
void mains_control(void)
{
	if(mains_ok)
	{
		mns_recovery_counter=0; mains_ok_offcnt=0;
		
		if(Slide_inups) mns_entry_dly_checkvalue=2; else mns_entry_dly_checkvalue=1;
		
		if(mns_entry_dly > mns_entry_dly_checkvalue )   /////////////////////edited 30-6-15 upgrade
		{
			mns_entry_dly=5;
			mains_on_flag=1;  
		}
		else
		{
			if(Slide_inups)
			{      mains_on_flag=0;  on_mains=0; }
		}
	}
	else
	{      
		 
	     
	          mns_entry_dly=0;
		        mains_on_flag=0;
	      
		 
	}
}            
    

#include "display.h"
#include "utility.h"
#include "stm32f0xx.h"
#include "variable.h"

unsigned char cntr,cntr1;

void indication (void)
{
	if(swt_pos) Backlight_ON();
	else Backlight_OFF();
	
		disp_cnt++;
	if(mains_on_flag) display_data|=0x20; else display_data&=~0x20; 
		
	if(thermal_fault){  									//hOt
			display_data3[0]=0x78;
			display_data3[1]=0x5C;
			display_data3[2]=0x74;
			}
	
	else if(wiring_fail|sht_ckt_flag){		//FLt
			display_data3[1]=0x38;
			display_data3[0]=0x78;
			display_data3[2]=0x71;
	}
	
	else if(fuse_blow_flag){          		//CbO
			display_data3[1]=0x7C;
			display_data3[0]=dig[0];
			display_data3[2]=0x39;
	}
	else if(battery_open){								//btO
			display_data3[1]=0x78;
			display_data3[0]=dig[0];
			display_data3[2]=0x7C;
	}
	else if(fb_open){								//FbO
			display_data3[1]=0x7C;
			display_data3[0]=dig[0];
			display_data3[2]=0x71;
	}
	
	else if(low_batt_buzz||low_batt_flag)  							//LO
		{
			display_data3[0]=dig[0];
			display_data3[1]=0x38;
			display_data3[2]=0x00;				
		}
		else if(ovr_ld_buzz){    						//OL
			display_data3[1]=dig[0];
			display_data3[0]=0x38;
			display_data3[2]=0x00;
		}
	
	else if(mains_on_flag){
		if(disp_cnt<6) {										//IP-
				display_data3[0] =0x40;
				display_data3[1] = 0x73;
				display_data3[2] = dig[1];
				
		}
		else if(disp_cnt<15)
		{
		display_data3[0]=dig[(mains_final/10)%10];
		display_data3[1]=dig[(mains_final/100)%10];
		display_data3[2]=dig[mains_final/1000];
		}
		
		else if(disp_cnt<21) {							//bAt
			  
				display_data3[2] = 0x7C;
				display_data3[1] = 0x77;
				display_data3[0] = 0x78;
		}
		else if(disp_cnt<30)
		{
		display_data3[0]=dig[(batt_vltg_final/5)%10];
		display_data3[1]=dig[(batt_vltg_final/50)%10];
		display_data3[2]=dig[0];
		}
		else disp_cnt=0;
	}
	else
		{
			if(!swt_pos&&disp_cnt<15) disp_cnt=15; 
		if(disp_cnt<6) {											//OP-
				display_data3[0] = 0x40;
				display_data3[1] = 0x73;
				display_data3[2] = dig[0];
				fb_vltg_copy=Feedback_avg;
				if(fb_vltg_copy<200) fb_vltg_copy =0;
		}
		else if(disp_cnt<15)
		{
		display_data3[0]=dig[(fb_vltg_copy/10)%10];
		display_data3[1]=dig[(fb_vltg_copy/100)%10];
		display_data3[2]=dig[fb_vltg_copy/1000];
		}
	
		else if(disp_cnt<21) {									//bAt
			  
				display_data3[2] = 0x7C;
				display_data3[1] = 0x77;
				display_data3[0] = 0x78;
		}
		else if(disp_cnt<30)
		{
		display_data3[0]=dig[(batt_vltg_final/5)%10];
		display_data3[1]=dig[(batt_vltg_final/50)%10];
		display_data3[2]=dig[0];
		}

		else disp_cnt=0;
	}
//////////////////////////////////buzzer/////////////////////////////////////////
	  if(!swt_pos && !ups_mode_buzz)  /// ups mode buzzer during switch On /OFF
   	BUZZER_OFF();
    else
    {
			if((low_batt_bit)|(overload_flag)|ups_mode_buzz|(sht_ckt_flag)|(fuse_blow_flag)|(wiring_fault)|(thermal_fault_flag)|(fb_open))
			{
				if(mute_cnt<120) BUZZER_ON(); else {BUZZER_OFF(); mute_cnt=121;} mute_cnt++;
			}
			else if((low_batt_buzz)|(ovr_ld_buzz))
				{BUZZER_ON(); mute_cnt=0;}
	   else
		 {
	   BUZZER_OFF(); mute_cnt=0;
		 }
		
     }
		
		 
		 
		if(snooz==0) hr_counter1=0;
		else         BUZZER_OFF();




		 	   Display_var=0x0000;
///////////////////////////////warning indiactions updated/////////////////////////////////////////
		 
		 if(ovr_ld_buzz)Display_var = (Display_var | 0x0001);         else       Display_var = (Display_var | 0x0000);
		 
		 if(sht_ckt_flag) Display_var = (Display_var | 0x0002);       else       Display_var = (Display_var | 0x0000);
		 
		 if(low_batt_buzz) Display_var = (Display_var | 0x0004);      else       Display_var = (Display_var | 0x0000);
		 
		 if(on_mains) Display_var = (Display_var | 0x0008);           else       Display_var = (Display_var | 0x0000);
				 
		 if(batt_charging_flag) Display_var = (Display_var | 0x0010); else       Display_var = (Display_var | 0x0000);
		 
		 if(swt_pos) Display_var = (Display_var | 0x0020);            else       Display_var = (Display_var | 0x0000);
		 
		 if(fuse_blow_flag)Display_var = (Display_var | 0x0040);      else       Display_var = (Display_var | 0x0000);
		 
		 if(thermal_fault) Display_var = (Display_var | 0x0100);      else       Display_var = (Display_var | 0x0000);
		 
		 if(wiring_fail)   Display_var = (Display_var | 0x0080);      else       Display_var = (Display_var | 0x0000);
		 


		 if(battery_open)        Display_var = (Display_var | 0x0400);      else       Display_var = (Display_var | 0x0000);
		 
		 if(batt_charged_flag)   Display_var = (Display_var | 0x0800);      else       Display_var = (Display_var | 0x0000);
		 
		 if((sht_ckt_flag != sht_ckt_flag_old) && (sht_ckt_flag==1))    DR_WF_ST=DR_WF_ST + 0x0001;
     if((wiring_fail != wiring_fail_old) && (wiring_fail==1))       DR_WF_ST=DR_WF_ST + 0x0100;		
		 
//		 if((charger_fail_flag != charger_fail_flag_old) && (sht_ckt_flag==1))   DR_FB_SF=DR_FB_SF + 0x0001;
     if((fuse_blow_flag != fuse_blow_flag_old) && (fuse_blow_flag==1))       DR_FB_SF=DR_FB_SF + 0x0100;
		

		 if((batt_charged_flag != batt_charged_flag_old) && (batt_charged_flag==1))    DR_TF_FC=DR_TF_FC + 0x0001;
     if((thermal_fault != thermal_fault_old) && (thermal_fault==1))                DR_TF_FC=DR_TF_FC + 0x0100;
		
		sht_ckt_flag_old=sht_ckt_flag;
		wiring_fail_old= wiring_fail;
//		charger_fail_flag_old=charger_fail_flag;
		fuse_blow_flag_old=fuse_blow_flag;
		batt_charged_flag_old=batt_charged_flag;
		thermal_fault_old=thermal_fault;
		 
//////////////////////////////upson  ////////////////////////////////////////////////
 if(inv_boot)
        {
					UPS_BLINK=0;

             if((swt_pos)&&(inv_boot)&&(on_mains))
	           display_data = (display_data | 0x02);
	           else
	           display_data &=~(0x02);
        }
        else
					UPS_BLINK=1;

				
if((batt_charged_flag&&charger_enable&&(mains_on_cntr>4))||low_batt_buzz||low_batt_flag) display_data|=0x01; else display_data&=~0x01;
if(batt_charged_flag&&charger_enable&&(mains_on_cntr>4)) {display_data|=0x40;} else display_data&=~0x40;

if(charger_enable&&(mains_on_cntr>4)){CHARGE_BLINK=1;}
else {CHARGE_BLINK=0; display_data&=~0x04;}



cntr++;	
if(cntr>3) { cntr=0;
if(UPS_BLINK) display_data ^= 0x02;
if(CHARGE_BLINK) display_data ^= 0x04;
if(MAINS_BLINK) display_data ^=0x20;
}

display_data3[3]=display_data;
}

void display(void)
{


}

void display_1(void)
{
	if(display_clk>19){
				display_data1=display_data3[digit]|0x100<<digit;				
		digit++; if(digit>3) digit=0;
		display_clk=0;
		shift_reg(display_data1);
	}	
}

void shift_reg(unsigned int data)
{
	if(data&0x01) SEG_A_PORT->BSRR = SEG_A; else SEG_A_PORT->BRR = SEG_A;
	if(data&0x02) SEG_B_PORT->BSRR = SEG_B; else SEG_B_PORT->BRR = SEG_B;
	if(data&0x04) SEG_C_PORT->BSRR = SEG_C; else SEG_C_PORT->BRR = SEG_C;
	if(data&0x08) SEG_D_PORT->BSRR = SEG_D; else SEG_D_PORT->BRR = SEG_D;
	if(data&0x10) SEG_E_PORT->BSRR = SEG_E; else SEG_E_PORT->BRR = SEG_E;
	if(data&0x20) SEG_F_PORT->BSRR = SEG_F; else SEG_F_PORT->BRR = SEG_F;
	if(data&0x40) SEG_G_PORT->BSRR = SEG_G; else SEG_G_PORT->BRR = SEG_G;
	if(data&0x80) SEG_dp_PORT->BSRR = SEG_dp; else SEG_dp_PORT->BRR = SEG_dp;
	if(data&0x100) DIG_1_PORT->BSRR = DIG_1; else DIG_1_PORT->BRR = DIG_1;
	if(data&0x200) DIG_2_PORT->BSRR = DIG_2; else DIG_2_PORT->BRR = DIG_2;
	if(data&0x400) DIG_3_PORT->BSRR = DIG_3; else DIG_3_PORT->BRR = DIG_3;
	if(data&0x800) LED_PORT->BSRR = LED; else LED_PORT->BRR = LED;
	
}
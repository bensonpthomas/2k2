#include "variable.h"

 status_flags1 STATUS_FLAG;

 unsigned short cos64_ary[] = {
					0x0000, 0x0C8B, 0x18F8, 0x2527, 0x30FB, 0x3C56, 0x471C, 0x5133, 0x5A81, 0x62F1, 0x6A6C, 
					0x70E1, 0x7640, 0x7A7C, 0x7D89, 0x7F61, 0x7FFF, 0x7F61, 0x7D89, 0x7A7C, 0x7640, 0x70E1, 
					0x6A6C, 0x62F1, 0x5A81, 0x5133, 0x471C, 0x3C56, 0x30FB, 0x2527, 0x18F8, 0x0C8B,
	         
					0xFFFF,0xF374, 0xE707, 0xDAD8, 0xCF04, 0xC3A9, 0xB8E3, 0xAECC, 0xA57E, 0x9D0E, 0x9593, 0x8F1E, 
					0x89BF, 0x8583, 0x8276, 0x809E, 0x8100, 0x809E, 0x8276, 0x8583, 0x89BF, 0x8F1E, 0x9593, 
					0x9D0E, 0xA57E, 0xAECC, 0xB8E3, 0xC3A9, 0xCF04, 0xDAD8, 0xE707, 0xF374
				  };
				  
					
					
	
void int_data(void)           //        ADDRESS LOCATION 
{
	
	data_array[0]=0xD220;		  //PWD	  	0x20000BB0
	data_array[1]=3180;		    //BATT_V	0x20000BB2    ////  20200															//3360
	data_array[2]=11700;		//MAINS_V 	0x20000BB4  // 278																		//11250           
	data_array[3]=2918;		//OUTPUT_V	0x20000BB6   				2950
	data_array[4]=18112;		//DIS_CRNT	0x20000BB8   //45000																	//13200
	data_array[5]=50;		 //TEMPERATURE	0x20000BBA
	data_array[6]=24100;		//CHG_CRNT	0x20000BBC   // 22500																	//23500
	data_array[7]=0xFFFF;		//unlokcode	0x20000BBE    make 0x1F0F as 0xFFFF befor production 
	data_array[8]=500;		 // FREQ	  	0x20000BC0
	data_array[9]=0xFFFF;		//Time	  	0x20000BC2
	data_array[10]=100;			//Date	  	0x20000BC4
	data_array[11]=100;			//serial  	0x20000BC6
	data_array[12]=0xFFFF;	//vendor  	0x20000BC8
	data_array[13]=0xFFFF;	//progver  	0x20000BCA
	data_array[14]=15500;		//solar  	  0x20000BCC  FCAE end adress
	DR_WF_ST=0;
	DR_TF_FC=0;
	DR_FB_SF=0;
	DR_ups_time=0;
	DR_mains_time=0;
	DR_charger_time=0;
	DR_avgAC=0;
	DR_avgDC=0;
	Dummy=0;	
}
					
					
unsigned short gain_code_dummy=0;				
					
//////variable declaration///////
	unsigned short data_array[15] __attribute__((at(0x20000BB0)));
 unsigned short boot_flag __attribute__((at(0x20000BCE)));;
 unsigned short Fwrite_enable __attribute__((at(0x20000BD0)));
 unsigned short comm_enable __attribute__((at(0x20000BD2)));
 
 unsigned short batt_vltg_final2 __attribute__((at(0x20000BD4)));
 unsigned short mains_final __attribute__((at(0x20000BD6)));
 unsigned short fb_avg_slow __attribute__((at(0x20000BD8)));
 unsigned short dischg_current_final __attribute__((at(0x20000BDA)));
 unsigned short temperature __attribute__((at(0x20000BDC)));
 unsigned short chg_current_final __attribute__((at(0x20000BDE)));
 unsigned short freq_final __attribute__((at(0x20000BE0)));
 unsigned short Total_AH __attribute__((at(0x20000BE2)));
 char swt_pos __attribute__((at(0x20000BE4)));
 char Slide_inups __attribute__((at(0x20000BE6)));
 char chg_mode __attribute__((at(0x20000BE8)));
 char BATTREY_SELECTOR __attribute__((at(0x20000BEA)));
 unsigned short Display_var __attribute__((at(0x20000BEC)));

 char snooz __attribute__((at(0x20000BEE)));
 unsigned short DR_WF_ST __attribute__((at(0x20000BF0)));
 unsigned short DR_TF_FC __attribute__((at(0x20000BF2)));
 unsigned short DR_FB_SF __attribute__((at(0x20000BF4)));
 unsigned short DR_ups_time __attribute__((at(0x20000BF6)));
 unsigned short DR_mains_time __attribute__((at(0x20000BF8))); 
 unsigned short DR_charger_time __attribute__((at(0x20000BFA)));
 unsigned short DR_avgAC __attribute__((at(0x20000BFC)));
 unsigned short DR_avgDC __attribute__((at(0x20000BFE)));
 unsigned char count_min;
unsigned short hr_counter,sec_counter,hr_counter1;
 unsigned short i;

 char INV_UPS;				

 unsigned short mains_final;
  unsigned short Dummy __attribute__((at(0x20000C00))); 
 char BB_reset __attribute__((at(0x20000C02)));
 
  unsigned short scom_ary[8]; 
 unsigned short scom_ptr,scom_ptr_temp,tx_hbyte;
 unsigned short data_temp,data_read;
 unsigned int address_temp,address_temp_fin;
 char reminder,scom_timeout;
 unsigned short batt_vltg_final;
 
 

////////////////////////////////////////////////////////////
 unsigned int batt_vltg_avg,batt_vltg_final_mul;
 unsigned int dischg_current_avg,dischg_current_fin_mul, dischg_current_filt;
 unsigned int mains_total_temp,mains_total,mains_total_mul;
 int Total_chg_crnt,Total_chg_crnt_Final,Avg_chg_crnt_temp_mul;	 
////////////////////////////////////////////////////////////

///////////////ADC temp tregsiter///////////////////////////////////
unsigned short Mode_selction,Discha_current,Ntc_input,Chrg_current,Mains_input,Feedback,Batt_voltage,solar_current;
unsigned short RegularConvData_Tab[8];
 ////////////////////		SWITCH REGISTERS ///////////////
unsigned short  switch_cntr;

////////////////mode selection///////////////////
unsigned short Mode_selction_avg;
unsigned int Mode_selction_old;

////////////////   PWM VARIABLES ///////////////////

////////////////////////ADC VARIABLES //////////////////////////////
unsigned char sample;

///////////////////////// DISCHARGING VARIABLES /////////////////////////
unsigned char ld_counter,surge_counter_load,surge_counter,counter_ol,rst_counter_ol;
unsigned int current_acc;//dischg_amp,
//unsigned short  dischg_final;

////////////////////////////solar////////////////////////////////////////
short gain_extra=0;
///////////////////////////CHARGING VARIABLES //////////////////////////////////////

unsigned char sample_counter_amp,sample_counter_amp_final;
unsigned short Avg_chg_crnt_temp;
unsigned short temp_counter_compare,timer,temp_counter,counter;
unsigned short current_ref,inc_volt,ref_value,current_set,current_set1;
unsigned short current_ref1;
short charger_dutycycle = 0,charger_dutycycle_old,charger_dutycycle_temp;
unsigned char cond,count_sec;
unsigned short dis_current_total;
int error_old,error,fuseflag_counter;
unsigned short present_value;


//////////////////////////// BATTERY VOLT VARIABLES /////////////
 unsigned char batt_counter,counter_lb,rst_counter_lb,ampcounter;
 unsigned short batt_counter_1,batt_counter_2;
 unsigned short batt_vltg;
 unsigned short batt_final,batt_v,batt_vltg_final_old; 
 unsigned short  boost_vltg_set,voltage_ref,trickle_vltg,batt_trickle_vltg_flp;
 unsigned short  full_charging_vltg;
 unsigned short  Total_AH,Total_AH_old;
 
 unsigned short batt_open_counter=12;
//////////////////FEEDBACK VOLTAGE VARIABLES//////////////////////

 unsigned short fb_cntr=0;
 int Feedback_acc=0;
 unsigned short Feedback_avg=0, fb_vltg_final=0;
 unsigned short fb_vltg_copy;
 short Feedback1;
 
///////////////Temperature VARIABLES//////////////////
unsigned short temper_final;   
unsigned int temper_old;
unsigned int temperature_final=800;

////////////////////////common VARIABLES//////////////////

unsigned char rly_pos_old,day_counter,interupt_dly,shut_dwn_dly;
unsigned short hr_counter,sec_counter;
unsigned short counter_equ;

///////////////////////////////LINE VOLTAGE VARIABLES //////////////////////


 unsigned char counte,mns_recovery_counter,mns_entry_dly_checkvalue,mns_entry_dly;
 unsigned short fivemsec_counter;
 unsigned char i2m_counter;
 
 unsigned short mains_final_old,mains_final_new;
 unsigned short half_freq_final;
 int sample_counter_mns,half_cycle_freq,half_cycle_freq_final,sample_counter_mns_final,mains_ok_offcnt;

 int mains_vltg, magnetisation;

   unsigned char mains_off_cntr,mains_on_cntr; 
      

///////////////////////           TIMER VARIABLES //////////////
unsigned short second,display_time;
///////////////////////////////////////////////////

unsigned short freq_coeff =0;  
unsigned short freq_code=164;
unsigned short e_degree;
 int pwm_ptrs=0,pwm_ptrs1=0,pwm_ptrs2,pwm_ptrs3;
 signed short mod_ary=0,mod_ary1=0,duty_cly=0,duty_cly1=0;
 int phase_shift=0x200;
 int over_mod_coeff = 1;
 unsigned short thre_thetausn=0; 
 int gain_code =200;
 int fb_error =0,fb_error_slow=0;
 int fb_diff =0;
 long  fb_error_acc =0;
 unsigned short sample_no,sample_post,sample_present;
 unsigned short angle;

unsigned long int multipication;


//////////temp///////////////

unsigned int counte_max=0;
unsigned char softstart_counter=0;


////////display//////////


unsigned char disp_cnt;
//const unsigned char dig[10]={0x3F,0x18,0x76,0x7A,0x59,0x6B,0x6F,0x38,0x7F,0x7B};
//const unsigned char dig[10]={0xD7,0x11,0xCD,0x5D,0x1B,0x5E,0xDE,0x15,0xDF,0x5F};
const unsigned char dig[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char digit=0;
unsigned short display_clk;
unsigned char shift_count;
unsigned short display_data;
unsigned short display_data1;unsigned short display_data3[4];
///////////////////
unsigned char counter_sht,rst_counter_sht,charge_arm_swap_counter;

unsigned short test;
int test1,test2;





///////////calc_gain variables///////////
unsigned short vout_ref=0,feed_fwd_gain=0,int_gain=0;
short prop_gain=0;

int int_error=0;

////////////////////////////////////////////////////

unsigned short dis_current_peak=0;
short sw_sht_cnt=10;

unsigned short over_load_counter=0;



char dp[3]={0,0,0};
unsigned char mute_cnt=0;


////////////////

const unsigned char chg_ref[3]={100,200,150};
unsigned short fb_open_cnt=0;
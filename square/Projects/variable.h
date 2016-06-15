#define 	batt_power 							 2000
#define  	battery_count					 2

#define  high_chg         	     200		    //for 12 amp
#define  low_chg          	     150		    //for 10 amp

#define  boost_vltg_tubler       148
#define  boost_vltg_flat_plate   144

#define  ups_low_cut             1750   ///180 V
#define  ups_low_cut_rec         1850   ///190 V

#define  ups_hi_cut              2600   ///260 V
#define  ups_hi_cut_rec		       2500   ///250 V

#define  inv_low_cut             950   		///actual 100 V
#define  inv_low_cut_rec         1050   	///actual 110 V

#define  inv_hi_cut              2900   ///290 V           
#define  inv_hi_cut_rec		       2800   ///280 V

#define  charger_on_vol          1100   ///140 V
#define  charger_off_vol	       1000   ///125 V

#define  extra_low_cut           400   ///40 V
#define  extra_low_cut_rec	     500   ///50 V

extern unsigned short gain_code_dummy;				


extern unsigned short cos64_ary[];

void int_data(void);
typedef union 
{
	 unsigned int all;
	 struct
	{
		
	unsigned int V1:1;		
	unsigned int V2:1;          
	unsigned int V3:1;	
	unsigned int V4:1;	
	unsigned int V5:1;		
	unsigned int V6:1;	
	unsigned int V7:1;	
	unsigned int V8:1;	
	unsigned int V9:1;	
	unsigned int V10:1;	
	unsigned int V11:1;	
	unsigned int V12:1;
  unsigned int V13:1;
	unsigned int V14:1;
	unsigned int V15:1;
	unsigned int V16:1;	
	unsigned int V17:1;
  unsigned int V18:1;
	unsigned int V19:1;
	unsigned int V20:1;
	unsigned int V21:1;
	unsigned int V22:1;
	unsigned int V23:1;
	unsigned int V24:1;
	unsigned int V25:1;
	unsigned int V26:1;
	unsigned int V27:1;
	unsigned int V28:1;
	unsigned int V29:1;
	unsigned int V30:1;
	unsigned int V31:1;
	unsigned int V32:1;
	unsigned int V33:1;
	unsigned int V34:1;
	unsigned int V35:1;
	unsigned int V36:1;
	unsigned int V37:1;
	unsigned int V38:1;
	unsigned int V39:1;
	unsigned int V40:1;
	unsigned int V41:1;
	unsigned int V42:1;
	unsigned int V43:1;
	unsigned int V44:1;
	unsigned int V45:1;
	unsigned int V46:1;
	unsigned int V47:1;
	unsigned int V48:1;
	unsigned int V49:1;
	unsigned int V50:1;
	unsigned int V51:1;
	unsigned int V52:1;
	unsigned int V53:1;
	unsigned int V54:1;
	unsigned int V55:1;
	unsigned int V56:1;
	unsigned int V57:1;
	unsigned int V58:1;
	unsigned int V59:1;
	unsigned int V60:1;
	unsigned int V61:1;
	unsigned int V62:1;
	unsigned int V63:1;
	unsigned int V64:1;
	unsigned int V65:1;
	unsigned int V66:1;
	unsigned int V67:1;
	unsigned int V68:1;
	unsigned int V69:1;
	unsigned int V70:1;
	unsigned int V71:1;
	unsigned int V72:1;
	unsigned int V73:1;
	}bt;
}status_flags1;

extern  status_flags1 STATUS_FLAG;

#define  read_ad              STATUS_FLAG.bt.V1


#define  zc_new_mns           STATUS_FLAG.bt.V2
#define  zc_old_mns           STATUS_FLAG.bt.V3
#define  hc_cycle             STATUS_FLAG.bt.V4


#define fb_flag                 STATUS_FLAG.bt.V5
#define fb_flag1                 STATUS_FLAG.bt.V6
#define fb_flag2                 STATUS_FLAG.bt.V7
#define gain_update_flag         STATUS_FLAG.bt.V8
#define chg_update_flag						STATUS_FLAG.bt.V9

#define  swt_cond             STATUS_FLAG.bt.V10
#define  swt_status_chg       STATUS_FLAG.bt.V11
//#define  swt_pos              STATUS_FLAG.bt.V12

#define  chk_load              STATUS_FLAG.bt.V13

#define  battery_open         STATUS_FLAG.bt.V14
#define  chk_batt             STATUS_FLAG.bt.V15

#define  low_batt_buzz        STATUS_FLAG.bt.V16
#define  low_batt_flag        STATUS_FLAG.bt.V17
#define  low_batt_bit         STATUS_FLAG.bt.V18
#define  low_batt_buzz_1      STATUS_FLAG.bt.V19
#define  low_batt_bit_1       STATUS_FLAG.bt.V20

#define  mains_ok             STATUS_FLAG.bt.V21
#define  mains_ok_temp        STATUS_FLAG.bt.V22
#define  mains_on_flag        STATUS_FLAG.bt.V23
#define  on_mains             STATUS_FLAG.bt.V24

#define  one_sec              STATUS_FLAG.bt.V25

#define  inv_boot             STATUS_FLAG.bt.V26
#define  mains_boot           STATUS_FLAG.bt.V27
#define  start_sync           STATUS_FLAG.bt.V28


#define  swich_softstart      STATUS_FLAG.bt.V29
#define  protection_flag      STATUS_FLAG.bt.V30
#define  swt_pos_old          STATUS_FLAG.bt.V31
#define  ups_mode_buzz        STATUS_FLAG.bt.V32

#define  overload_flag        STATUS_FLAG.bt.V33
#define  ovr_ld_buzz					STATUS_FLAG.bt.V34
#define  over_load_start      STATUS_FLAG.bt.V35
#define  ready								STATUS_FLAG.bt.V36

#define  BATT_BLINK						STATUS_FLAG.bt.V37
#define  OVER_LOAD_BLINK			STATUS_FLAG.bt.V38
#define  UPS_BLINK						STATUS_FLAG.bt.V39
#define  CHARGE_BLINK					STATUS_FLAG.bt.V40
#define  MAINS_BLINK					STATUS_FLAG.bt.V41


#define blink_all							STATUS_FLAG.bt.V42

#define thermal_fault					STATUS_FLAG.bt.V43

#define wiring_fail						STATUS_FLAG.bt.V44
#define sht_ckt_flag					STATUS_FLAG.bt.V45
#define fuse_blow_flag				STATUS_FLAG.bt.V46
#define shut_down_flag				STATUS_FLAG.bt.V47
#define mains_int_flag				STATUS_FLAG.bt.V48
#define interupt_flag				  STATUS_FLAG.bt.V49

#define wiring_fault				  STATUS_FLAG.bt.V50
#define charger_on						STATUS_FLAG.bt.V51
#define LO_hi									STATUS_FLAG.bt.V52
#define charger_boot          STATUS_FLAG.bt.V53
#define charge_side           STATUS_FLAG.bt.V54
#define charger_enable        STATUS_FLAG.bt.V55

#define  batt_charging_flag   STATUS_FLAG.bt.V56
#define  batt_charged_flag    STATUS_FLAG.bt.V57
#define  batt_gravity_flag    STATUS_FLAG.bt.V58

#define  inv_on_flag          STATUS_FLAG.bt.V59
#define  trickle 		          STATUS_FLAG.bt.V60
#define  swap		 		          STATUS_FLAG.bt.V61

#define thermal_fault_flag		STATUS_FLAG.bt.V62

#define  OPEN_BLINK						STATUS_FLAG.bt.V63

#define  thermal_shut_down_flag						STATUS_FLAG.bt.V64
#define tic  STATUS_FLAG.bt.V65
#define relay  STATUS_FLAG.bt.V66
#define first_pulse  STATUS_FLAG.bt.V67

#define sht_ckt_flag_old      STATUS_FLAG.bt.V70
#define wiring_fail_old      STATUS_FLAG.bt.V71
#define fuse_blow_flag_old      STATUS_FLAG.bt.V72
#define batt_charged_flag_old      STATUS_FLAG.bt.V68
#define thermal_fault_old      STATUS_FLAG.bt.V69
#define  fb_open						STATUS_FLAG.bt.V73


 extern unsigned short mains_final,chg_current_final;

 extern unsigned short data_array[15];	

 extern unsigned short scom_ary[8];
 extern unsigned short boot_flag;// __attribute__((at(0x20001000)));
 extern unsigned short Fwrite_enable;// __attribute__((at(0x20001004)));
 extern unsigned short comm_enable;// __attribute__((at(0x20001008)));

 extern unsigned short batt_vltg_final,batt_vltg_final2,mains_final,fb_vltg_final,dischg_current_final,temperature,freq_final,solar_current_final;
 extern unsigned short scom_ptr,scom_ptr_temp,tx_hbyte,Display_var;
 extern unsigned int address_temp,address_temp_fin;
 extern unsigned short data_temp,data_read;
 extern char INV_UPS,Slide_inups,HC_NC,BATTREY_SELECTOR;
 
 extern unsigned short i;
 
  
extern unsigned short scom_ary[8]; 
extern unsigned short scom_ptr,scom_ptr_temp,tx_hbyte;
extern unsigned short data_temp,data_read;
extern unsigned int address_temp,address_temp_fin;
 
 /////////////////////////////////////////////////////////
 extern unsigned int batt_vltg_avg,batt_vltg_final_mul;
 extern unsigned int dischg_current_avg,dischg_current_fin_mul,dischg_current_filt;
 extern unsigned int mains_total_temp,mains_total,mains_total_mul;
 extern int Total_chg_crnt,Total_chg_crnt_Final,Avg_chg_crnt_temp_mul;
 ////////////////////////////////////////////////////////////


///////////////ADC temp tregsiter///////////////////////////////////
extern unsigned short Mode_selction,Discha_current,Ntc_input,Chrg_current,Mains_input,Feedback,Batt_voltage,solar_current;
extern unsigned short RegularConvData_Tab[8];
 ////////////////////		SWITCH REGISTERS ///////////////
extern unsigned short  switch_cntr;

////////////////mode selection///////////////////
extern unsigned short Mode_selction_avg;
extern unsigned int Mode_selction_old;

////////////////   PWM VARIABLES ///////////////////


////////////////////////ADC VARIABLES //////////////////////////////
extern unsigned char sample;


///////////////////////// DISCHARGING VARIABLES /////////////////////////
extern unsigned char ld_counter,surge_counter_load,surge_counter,counter_ol,rst_counter_ol;//,sol_counter,sol_counter_1;
extern unsigned int current_acc;//dischg_amp,
//extern unsigned short  dischg_final;

////////////////////////////solar////////////////////////////////////////
extern short gain_extra;
///////////////////////////CHARGING VARIABLES //////////////////////////////////////

extern unsigned char sample_counter_amp,sample_counter_amp_final;
extern unsigned short Avg_chg_crnt_temp;
extern short charger_dutycycle,charger_dutycycle_old, charger_dutycycle_temp;
extern unsigned short temp_counter_compare,timer,temp_counter,counter;
extern unsigned char cond,count_sec;
extern unsigned short dis_current_total;
extern unsigned short current_ref, inc_volt,ref_value,current_set,current_set1;
extern int error_old,error,fuseflag_counter;
extern unsigned short present_value;
extern unsigned short current_ref1;
//////////////////////////// BATTERY VOLT VARIABLES /////////////
extern unsigned char batt_counter,counter_lb,rst_counter_lb,ampcounter;
extern unsigned short batt_counter_1,batt_counter_2;
extern unsigned short batt_vltg;
extern unsigned short batt_final,batt_v,batt_vltg_final_old; 
extern unsigned short  boost_vltg_set,voltage_ref,trickle_vltg,batt_trickle_vltg_flp;
extern unsigned short  full_charging_vltg;
extern unsigned short  Total_AH,Total_AH_old;

extern unsigned short batt_open_counter;
//////////////////FEEDBACK VOLTAGE VARIABLES//////////////////////

extern unsigned short fb_cntr;

extern int Feedback_acc;
extern unsigned short Feedback_avg,fb_avg_slow;
extern unsigned short fb_vltg_copy;
extern short Feedback1;
///////////////Temperature VARIABLES//////////////////
extern unsigned short temper_final;   
extern unsigned int temper_old;
extern unsigned int temperature_final;
////////////////////////common VARIABLES//////////////////

extern unsigned short hr_counter,sec_counter;
extern unsigned char rly_pos_old, day_counter, interupt_dly, shut_dwn_dly;
extern unsigned short counter_equ;
///////////////////////////////LINE VOLTAGE VARIABLES //////////////////////


extern unsigned char counte,mns_recovery_counter,mns_entry_dly_checkvalue,mns_entry_dly;
extern unsigned short fivemsec_counter;
extern unsigned char i2m_counter;

extern unsigned short mains_final_old,mains_final_new;
extern unsigned short half_freq_final;
extern int sample_counter_mns,half_cycle_freq,half_cycle_freq_final,sample_counter_mns_final,mains_ok_offcnt;

extern int mains_vltg, magnetisation;
extern unsigned char mains_off_cntr, mains_on_cntr;

    
      

///////////////////////           TIMER VARIABLES //////////////
    	
/////////////////////////////////////////////////////////////////////////////////////////////////
   extern unsigned short second,display_time;
   //////////////////////flags//////////////////////////////// 
         
				 
				 
				 
	#define REF_INDEX               600			 
extern unsigned short freq_coeff; 
extern unsigned short freq_code;
extern unsigned short e_degree;

extern  int pwm_ptrs,pwm_ptrs1,pwm_ptrs2,pwm_ptrs3;
extern signed short mod_ary,mod_ary1,duty_cly,duty_cly1;
extern int phase_shift;
extern int over_mod_coeff;
extern unsigned short thre_thetausn; 
extern int gain_code;
extern int fb_error,fb_error_slow;
extern int fb_diff;
extern long  fb_error_acc;
extern unsigned short sample_no,sample_post,sample_present;
extern unsigned short angle;
extern unsigned long int multipication;
extern char BB_reset;
extern char reminder,scom_timeout;


/////////////////temp///////////
extern unsigned int counte_max;
extern unsigned char softstart_counter;

////////////////display/////////////
extern unsigned char disp_cnt;
extern const unsigned char dig[10];
extern unsigned char digit;
extern unsigned short display_clk;
extern unsigned char shift_count;
extern unsigned short display_data3[4];
extern unsigned short display_data;

extern unsigned short display_data1;

 extern char snooz;
 extern unsigned short DR_WF_ST,DR_TF_FC,DR_FB_SF,DR_ups_time,DR_mains_time,DR_charger_time,DR_avgAC,DR_avgDC;
 extern unsigned short Dummy;


///////////////////
extern unsigned char counter_sht,rst_counter_sht,charge_arm_swap_counter;

extern unsigned short test;
extern int test1,test2;

extern char swt_pos;

extern unsigned char count_min;
extern unsigned short hr_counter,sec_counter,hr_counter1;








///////////calc_gain variables///////////

extern unsigned short vout_ref,feed_fwd_gain,int_gain;
extern short prop_gain;

extern int int_error;


////////////////

extern unsigned short dis_current_peak;
extern short sw_sht_cnt;
extern unsigned short over_load_counter;
extern char dp[3];

extern unsigned char mute_cnt;


extern const unsigned char chg_ref[3];
extern char chg_mode;
extern unsigned short fb_open_cnt;
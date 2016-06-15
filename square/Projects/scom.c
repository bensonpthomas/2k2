/*

#include "scom.h"
#include "variable.h"
#include "stm32f0xx.h"

void scomm(void)
{
        scom_timeout=0;
    scom_ptr_temp = scom_ptr & 0x0007;
    scom_ary[scom_ptr_temp]=USART_ReceiveData(USART1);
    if(scom_ptr_temp>=6)
    {
        if(scom_ptr_temp==6)
        {
	  
            process_cmd();
        }
        else
        USART_SendData(USART1, tx_hbyte);  
				 
				
    } 
    else         
    	USART_SendData(USART1, scom_ary[scom_ptr_temp]);
		
    scom_ptr++;	
    
}

void process_cmd(void)
{    

    data_temp=(scom_ary[2]<<8);
    data_temp=0xFF00& data_temp;
    data_temp=data_temp|scom_ary[1];

    address_temp=(scom_ary[4]<<8);
    address_temp=0xFF00 & address_temp;
    address_temp=address_temp|scom_ary[3];
	
	  /////start add 0BB0    end add 0C02 ///
		          reminder=(address_temp & 0x0001);
						if(	reminder == 1 || address_temp < 0x0BB0 ||  address_temp > 0x0C02)

						{ 
							address_temp= 0x0C00;  scom_ary[5]=3;
						}
    if(	address_temp > 0x0BAF &&  address_temp < 0x0BED)
		{ 
		
						address_temp_fin= 0x20000000 | address_temp ;
					
						if(scom_ary[5]==1)
						{
							
								data_read=(*((volatile unsigned short *)(address_temp_fin)));
								USART_SendData(USART1, (data_read & 0x00FF));  
								tx_hbyte=(data_read>>8) & 0x00FF;
						} 
						else if(scom_ary[5]==0)
						{
                   if(address_temp == 0x0BE4) 
									 {     
										 if(scom_ary[1]==0x01) {swt_pos=1;swich_softstart=1;vout_ref=0;} else if(scom_ary[1]==0x00) swt_pos=0; 
									 }	
							 else if(address_temp == 0x0C02)
									 {
										 BB_reset=1;
									 }
									 
									 
									 									 
									 else
									 (*((volatile unsigned short *)(address_temp_fin))) = data_temp;
									 
								tx_hbyte=0x55;
								USART_SendData(USART1, 0xAA);
						} 
						else
						{     
								tx_hbyte=0x55;
								USART_SendData(USART1, 0xAA);
						}
		}			
    
		
}              
*/




#include "scom.h"
#include "variable.h"
#include "stm32f0xx.h"

void scomm(void)
{
    
    scom_timeout=0;
    scom_ptr_temp = scom_ptr & 0x0007;
    scom_ary[scom_ptr_temp]=USART_ReceiveData(USART1);
    if(scom_ptr_temp>=6)
    {
        if(scom_ptr_temp==6)
        {
	  
            process_cmd();
        }
        else
        USART_SendData(USART1, tx_hbyte);  
				 
				
    } 
    else         
    	USART_SendData(USART1, scom_ary[scom_ptr_temp]);
		
    scom_ptr++;	
    
}

void process_cmd(void)
{    

    data_temp=(scom_ary[2]<<8);
    data_temp=0xFF00& data_temp;
    data_temp=data_temp|scom_ary[1];

    address_temp=(scom_ary[4]<<8);
    address_temp=0xFF00 & address_temp;
    address_temp=address_temp|scom_ary[3];
	

	  /////start add 0BB0    end add 0C02 ///
	          reminder=(address_temp & 0x0001);
						if(	reminder == 1 || address_temp < 0x0BB0 ||  address_temp > 0x0C02)

						{ 
							address_temp= 0x0C00;  scom_ary[5]=3;
						}
						    if(	address_temp > 0x0BAF &&  address_temp < 0x0BED)
								{ 
		
						address_temp_fin= 0x20000000 | address_temp ;
					
						if(scom_ary[5]==1)
						{
							
								data_read=(*((volatile unsigned short *)(address_temp_fin)));
								USART_SendData(USART1, (data_read & 0x00FF));  
								tx_hbyte=(data_read>>8) & 0x00FF;
						} 
						else if(scom_ary[5]==0)
						{
                   if(address_temp == 0x0BE4) 
									 {     
										 if(scom_ary[1]==0x01) {swt_pos=1;swich_softstart=1;vout_ref=0;} else if(scom_ary[1]==0x00) swt_pos=0; 
									 }	 
							 else if(address_temp == 0x0C02)
									 {
										 BB_reset=1;
									 }
									 
									 
									 
									 else

									 (*((volatile unsigned short *)(address_temp_fin))) = data_temp;
									 
								tx_hbyte=0x55;
								USART_SendData(USART1, 0xAA);
						} }
						else
						{     
								tx_hbyte=0x55;
								USART_SendData(USART1, 0xAA);
						}


}             




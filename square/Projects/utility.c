#include "utility.h"
#include "stm32f0xx.h"
#include "variable.h"


uint16_t TimerPeriod;
uint32_t Address ;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0;

extern void Port_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_AHBPeriphClockCmd( SHIFT_REG_ST_CP_PORT_CLK , ENABLE);									//| SOL_PWM_PORT_CLK 
	RCC_AHBPeriphClockCmd(PWM1_PORT_CLK | PWM2_PORT_CLK  | RLY_PORT_CLK , ENABLE);
	RCC_AHBPeriphClockCmd(BUZZER_PORT_CLK |Backlight_PORT_CLK| FAN_PORT_CLK | SWITCH_PORT_CLK  , ENABLE);						//| PV_Present_PORT_CLK
	
//	GPIO_InitStructure.GPIO_Pin = SHIFT_REG_ST_CP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(SHIFT_REG_ST_CP_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = SHIFT_REG_SH_CP;
//	GPIO_Init(SHIFT_REG_SH_CP_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = SHIFT_REG_DATA;
//	GPIO_Init(SHIFT_REG_DATA_PORT, &GPIO_InitStructure);

	
/////////////////////////////////////////Display pins//////////////
	GPIO_InitStructure.GPIO_Pin = SEG_A;
	GPIO_Init(SEG_A_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_B;
	GPIO_Init(SEG_B_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_C;
	GPIO_Init(SEG_C_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_D;
	GPIO_Init(SEG_D_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_E;
	GPIO_Init(SEG_E_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_F;
	GPIO_Init(SEG_F_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_G;
	GPIO_Init(SEG_G_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SEG_dp;
	GPIO_Init(SEG_dp_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DIG_1;
	GPIO_Init(DIG_1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DIG_2;
	GPIO_Init(DIG_2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DIG_3;
	GPIO_Init(SEG_A_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Backlight;
	GPIO_Init(Backlight_PORT, &GPIO_InitStructure);
	
////////////////////////////////////////////////////////////////////////////


//	GPIO_InitStructure.GPIO_Pin = SOL_PWM;
//	GPIO_Init(SOL_PWM_PORT, &GPIO_InitStructure);

	
	GPIO_InitStructure.GPIO_Pin = PWM1_PIN;
	GPIO_Init(PWM1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM2_PIN;
	GPIO_Init(PWM2_PORT, &GPIO_InitStructure);
	

	
	GPIO_InitStructure.GPIO_Pin = RLY_PIN;
	GPIO_Init(RLY_PORT, &GPIO_InitStructure);
	

	
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = FAN_PIN;
	GPIO_Init(FAN_PORT, &GPIO_InitStructure);
	 
	 
	GPIO_InitStructure.GPIO_Pin = TEST;
	GPIO_Init(TEST_PORT, &GPIO_InitStructure);
	
	//////////////////////////////////////////////////////////

	 /* ON-OFF switchConfigure PB1 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = SWITCH;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SWITCH_PORT, &GPIO_InitStructure);
  
//  GPIO_InitStructure.GPIO_Pin = PV_Present;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(PV_Present_PORT, &GPIO_InitStructure);

}
extern void TIM_Config(void)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  /* GPIOA and GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	 /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
                         
  /* GPIOA Configuration:
      - TIM1_CH1  pin (PA.08)  
      - TIM1_CH2  pin (PA.09)  
       */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    

  /* GPIOB Configuration:
      - TIM1_CH1N pin (PA.7)  
			- TIM1_CH2N pin (PB.0)
      */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  
  /* Connect TIM pins to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_2);
  


 /* Compute the value to be set in ARR register to generate signal frequency at 20.00 Khz */
  TimerPeriod = (SystemCoreClock / 40000) - 1;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 1;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	//Enable Auto Preload Enable for Capture compare Register	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable);
	
  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 47;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	
	 /* TIM Interrupts enable */
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

extern void TIM_Config2(void)
{
	TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  /* GPIOA and GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	 /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
                         
  /* GPIOA Configuration:
      - TIM1_CH1  pin (PA.08)  
      - TIM1_CH2  pin (PA.09)  
       */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    

  /* GPIOB Configuration:
      - TIM1_CH1N pin (PA.7)  
			- TIM1_CH2N pin (PB.0)
      */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  
  /* Connect TIM pins to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_2);
  


  /* Compute the value to be set in ARR register to generate signal frequency at 20.00 Khz */
  TimerPeriod = (SystemCoreClock / 40000) - 1;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 1;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	//Enable Auto Preload Enable for Capture compare Register	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable);
	
  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 47;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	
	 /* TIM Interrupts enable */
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);


//	TIM1->CNT=0;

	
	  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,1200);
	TIM_SetCompare2(TIM1,1200);
}






extern void TIM_Config3(void)
{
	TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  /* GPIOA and GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	/* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
                         
  /* GPIOA Configuration:
      - TIM1_CH1  pin (PA.08)  
      - TIM1_CH2  pin (PA.09)  
       */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    

  /* GPIOB Configuration:
      - TIM1_CH1N pin (PA.7)  
			- TIM1_CH2N pin (PB.0)
      */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  
  /* Connect TIM pins to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_2);
  


  /* Compute the value to be set in ARR register to generate signal frequency at 20.00 Khz */
  TimerPeriod = (SystemCoreClock / 40000) - 1;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 1;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	//Enable Auto Preload Enable for Capture compare Register	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable);
	
  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 47;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	
	 /* TIM Interrupts enable */
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);


//	TIM1->CNT=0;

	
	  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,1200);
	TIM_SetCompare2(TIM1,1200);
}






extern void ADC_Config(void)
{
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
   /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode withe a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  /* Convert the ADC1 Channel0 and channel10 with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SampleTime_55_5Cycles); 
  ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_55_5Cycles); 
  ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SampleTime_55_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_3 , ADC_SampleTime_55_5Cycles); 
  ADC_ChannelConfig(ADC1, ADC_Channel_4 , ADC_SampleTime_55_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_5 , ADC_SampleTime_55_5Cycles); 
  ADC_ChannelConfig(ADC1, ADC_Channel_6 , ADC_SampleTime_55_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_7 , ADC_SampleTime_55_5Cycles); 

   /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}




extern void DMA_Config(void)
{
  DMA_InitTypeDef   DMA_InitStructure;
//
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
}

extern void EXTI4_15_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
  /* Enable GPIOC clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PC9 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = EXT_interrupt;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Connect EXTI7 Line to PB7 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
  
  /* Configure EXTI9 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI4_15 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}



extern void USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	
	  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
		  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource14, GPIO_AF_1);  ///chane PinSource9 to PinSource14

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10 , GPIO_AF_1);
	
	  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 
	
/* USARTx configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - Two Stop Bit
  - Odd parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	////USART_InitStructure.USART_Mode = USART_Mode_Rx ;
	
    /* USART configuration */
  USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
		
		  /* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  USART_ITConfig(USART1,USART_IT_RXNE ,ENABLE );

	
}

extern void USART_Stop(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE); 
	USART_Cmd(USART1, DISABLE);  
	USART_ITConfig(USART1,USART_IT_RXNE ,DISABLE );
}

extern void User_IWDG_Init(void)
{
	/* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: LSI/32 */
  IWDG_SetPrescaler(IWDG_Prescaler_32);

  /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
   */
  IWDG_SetReload(40000/128);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();

	
}


extern void boot_check(void)
{
	unsigned int * ptr = (unsigned int *) FLASH_USER_START_ADDR ;
	boot_flag = *ptr;
	
}

extern void EEPROM_INIT(void)
{
	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	Address = FLASH_USER_START_ADDR;
	
	for(i=0;i<15;i++)
	{
	
				if(FLASH_ProgramWord(Address, data_array[i]) == FLASH_COMPLETE)   
				{
					Address = Address + 4;  
				}
				else
				{ 		
							while (1)
							{
							}
				}
	
  }	
	
	  FLASH_Lock();


}

extern void Memory_Read (void)
{
	unsigned int * ptr = (unsigned int *) FLASH_USER_START_ADDR ;
	
	for(i=0;i<15;i++)
	{
		data_array[i]=*ptr++;
		
	}
	
}



extern void Erase_Page_Flash(void)
{
	/* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	 
	if (FLASH_ErasePage(FLASH_USER_START_ADDR)!= FLASH_COMPLETE)
    {
     /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
      while (1)
      {
      }
    }	
				
		 /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock();
}



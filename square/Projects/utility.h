
#define ADC1_DR_Address    			 0x40012440
#define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08006000)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((uint32_t)0x08006400)   /* End @ of user Flash area */

//////////////////////////////OUTPUT LED INDICATION///////////////////////////////////////////////////

#define SEG_B				  			GPIO_Pin_11
#define SEG_B_PORT				  GPIOB
#define SEG_B_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define SEG_F				  			GPIO_Pin_12
#define SEG_F_PORT				  GPIOB
#define SEG_F_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define SEG_A				  			GPIO_Pin_15
#define SEG_A_PORT				  GPIOB
#define SEG_A_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define SEG_G				  			GPIO_Pin_11
#define SEG_G_PORT				  GPIOA
#define SEG_G_PORT_CLK		  RCC_AHBPeriph_GPIOA

#define SEG_C				  			GPIO_Pin_12
#define SEG_C_PORT				  GPIOA
#define SEG_C_PORT_CLK		  RCC_AHBPeriph_GPIOA

#define SEG_dp				  			GPIO_Pin_15							//dp in final
#define SEG_dp_PORT				  GPIOA
#define SEG_dp_PORT_CLK		  RCC_AHBPeriph_GPIOA

#define SEG_D				  			GPIO_Pin_3
#define SEG_D_PORT				  GPIOB
#define SEG_D_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define SEG_E					  		GPIO_Pin_4							//E in final
#define SEG_E_PORT				  GPIOB
#define SEG_E_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define DIG_1				  			GPIO_Pin_8
#define DIG_1_PORT				  GPIOB
#define DIG_1_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define DIG_2				  			GPIO_Pin_6
#define DIG_2_PORT				  GPIOB
#define DIG_2_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define DIG_3				  			GPIO_Pin_5
#define DIG_3_PORT				  GPIOB
#define DIG_3_PORT_CLK		  RCC_AHBPeriph_GPIOB

#define LED				  				GPIO_Pin_9
#define LED_PORT				  	GPIOB
#define LED_PORT_CLK		  	RCC_AHBPeriph_GPIOB

/////////////////////////////////////////////////////////////////////////////////////////////////////////


#define PWM1_PIN				  GPIO_Pin_9
#define PWM1_PORT				  GPIOA
#define PWM1_PORT_CLK		  RCC_AHBPeriph_GPIOA 

#define PWM2_PIN					GPIO_Pin_14												//B0
#define PWM2_PORT					GPIOB
#define PWM2_PORT_CLK			RCC_AHBPeriph_GPIOB 


#define RLY_PIN			    GPIO_Pin_15													
#define RLY_PORT		    GPIOC
#define RLY_PORT_CLK		RCC_AHBPeriph_GPIOC 


#define BUZZER_PIN				GPIO_Pin_1
#define BUZZER_PORT				GPIOF
#define BUZZER_PORT_CLK		RCC_AHBPeriph_GPIOF 

#define FAN_PIN				    GPIO_Pin_0
#define FAN_PORT				  GPIOF
#define FAN_PORT_CLK		  RCC_AHBPeriph_GPIOF

 
#define SWITCH				    GPIO_Pin_13
#define SWITCH_PORT				GPIOC
#define SWITCH_PORT_CLK		RCC_AHBPeriph_GPIOC 

#define TEST			  				GPIO_Pin_2
#define TEST_PORT				  	GPIOB
#define TEST_PORT_CLK		  	RCC_AHBPeriph_GPIOB


////////////////////////////////////////////////////
//#define SHIFT_REG_DATA					    GPIO_Pin_5
//#define SHIFT_REG_DATA_PORT				  GPIOB
//#define SHIFT_REG_DATA_PORT_CLK		  RCC_AHBPeriph_GPIOB 

//#define SHIFT_REG_SH_CP		          GPIO_Pin_3
//#define SHIFT_REG_SH_CP_PORT				GPIOB
//#define SHIFT_REG_SH_CP_PORT_CLK		RCC_AHBPeriph_GPIOB 

//#define SHIFT_REG_ST_CP					    GPIO_Pin_4
//#define SHIFT_REG_ST_CP_PORT				GPIOB
//#define SHIFT_REG_ST_CP_PORT_CLK		RCC_AHBPeriph_GPIOB 

//#define SOL_PWM						          GPIO_Pin_6
//#define SOL_PWM_PORT						    GPIOB
//#define SOL_PWM_PORT_CLK				    RCC_AHBPeriph_GPIOB 

#define Backlight        						GPIO_Pin_14
#define Backlight_PORT						  GPIOC
#define Backlight_PORT_CLK				  RCC_AHBPeriph_GPIOC

#define EXT_interrupt								GPIO_Pin_7
#define EXT_interrupt_PORT					GPIOB
#define EXT_interrupt_PORT_CLK      RCC_AHBPeriph_GPIOB
///////////////////////////////////////////////////////////////////////

//#define SHIFT_REG_DATA_ON()				   SHIFT_REG_DATA_PORT->BSRR = SHIFT_REG_DATA
//#define SHIFT_REG_DATA_OFF()			   SHIFT_REG_DATA_PORT->BRR  = SHIFT_REG_DATA
//#define SHIFT_DATA_TOGGLE() 					GPIOB->ODR ^= 0x010;

//#define SHIFT_REG_SH_CP_ON()				 SHIFT_REG_SH_CP_PORT->BSRR = SHIFT_REG_SH_CP
//#define SHIFT_REG_SH_CP_OFF()				 SHIFT_REG_SH_CP_PORT->BRR  = SHIFT_REG_SH_CP
//#define SHIFT_CLK_TOGGLE() 					GPIOA->ODR ^= 0x8000;

//#define SHIFT_REG_ST_CP_ON()				SHIFT_REG_ST_CP_PORT->BSRR = SHIFT_REG_ST_CP
//#define SHIFT_REG_ST_CP_OFF()				SHIFT_REG_ST_CP_PORT->BRR  = SHIFT_REG_ST_CP


//#define SOL_PWM_ON()				SOL_PWM_PORT->BSRR = SOL_PWM
//#define SOL_PWM_OFF()				SOL_PWM_PORT->BRR  = SOL_PWM

/////////////////////////////////////////pwm///////////////////////////////////////////////////////////////////////
#define TEST_ON()				TEST_PORT->BSRR = TEST
#define TEST_OFF()			TEST_PORT->BRR  = TEST


#define PWM1_ON()				PWM1_PORT->BSRR = PWM1_PIN
#define PWM1_OFF()			PWM1_PORT->BRR  = PWM1_PIN

#define PWM2_ON()				PWM2_PORT->BSRR = PWM2_PIN
#define PWM2_OFF()			PWM2_PORT->BRR  = PWM2_PIN

//#define TEST_ON()				TEST_PORT->BSRR = TEST_PIN
//#define TEST_OFF()				TEST_PORT->BRR  = TEST_PIN
//#define TEST_TOGGLE()		GPIOB->ODR ^= 0x08;

////////////////////////////////////relay buzz fan/////////////////////////////////////////////

#define CHG_RLY_ON()			CHG_RLY_PORT->BSRR = CHG_RLY_PIN
#define CHG_RLY_OFF()			CHG_RLY_PORT->BRR  = CHG_RLY_PIN

#define RLY_ON()		RLY_PORT->BSRR = RLY_PIN
#define RLY_OFF()		RLY_PORT->BRR  = RLY_PIN
#define RLY_TOGGLE()   GPIOC->ODR ^= 0x8000;

#define Backlight_ON()		Backlight_PORT->BSRR = Backlight
#define Backlight_OFF()		Backlight_PORT->BRR  = Backlight

#define BUZZER_ON()				BUZZER_PORT->BSRR = BUZZER_PIN
#define BUZZER_OFF()			BUZZER_PORT->BRR  = BUZZER_PIN
#define BUZZER_TOGGLE()   GPIOF->ODR ^= 0x0002;

#define FAN_ON()				  FAN_PORT->BSRR = FAN_PIN
#define FAN_OFF()			    FAN_PORT->BRR  = FAN_PIN
#define FAN_TOGGLE()      GPIOF->ODR ^= 0x001;

extern void pwm_start(void);
extern void pwm_stop(void);
extern void Port_Config(void);
extern void TIM_Config(void);
extern void TIM_Config2(void);
extern void TIM_Config3(void);
extern void ADC_Config(void);
extern void DMA_Config(void);
extern void Erase_Page_Flash(void);
//extern void Write_Flash(void);
extern void USART_Config(void);
extern void EXTI4_15_Config(void);
extern void User_IWDG_Init(void);
extern void boot_check(void);
extern void EEPROM_INIT(void);
extern void Memory_Read (void);
extern void SPI_init(void);

extern void User_IWDG_Init(void);
extern void USART_Stop(void);
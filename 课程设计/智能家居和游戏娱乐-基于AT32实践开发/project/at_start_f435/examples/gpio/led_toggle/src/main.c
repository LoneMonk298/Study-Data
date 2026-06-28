/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes */
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
//#include "i2c_application.h"
#include "bsp.eep_lm75.h"
#include "bsp.h"
#include "bsp_uart.h"
/** @addtogroup AT32F435_periph_examples
  * @{
  */
//#define time_after(a, b) ((s32)((s32)(b) - (s32)(a)) < 0)
//#define Timer_PassedDelay(startTime, msDelay) (time_after(Timer_GetTickCount(), (startTime + msDelay)))
//#define interval(a, b) ((S32)((S32)(b) - (S32)(a))) // systick decount

//#define Timer_GetTickCount() (systick_ms)
//#define I2C_TIMEOUT                      0xFFFFFFF

////#define I2Cx_CLKCTRL                   0xB170FFFF   //10K
////#define I2Cx_CLKCTRL                   0xC0E06969   //50K
//#define I2Cx_CLKCTRL                     0x80504C4E   //100K
////#define I2Cx_CLKCTRL                   0x30F03C6B   //200K

//#define I2Cx_ADDRESS                     0xA0

//#define I2Cx_PORT                        I2C2
//#define I2Cx_CLK                         CRM_I2C2_PERIPH_CLOCK
//#define I2Cx_DMA                         DMA1
//#define I2Cx_DMA_CLK                     CRM_DMA1_PERIPH_CLOCK

//#define I2Cx_SCL_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK
//#define I2Cx_SCL_GPIO_PIN                GPIO_PINS_10
//#define I2Cx_SCL_GPIO_PinsSource         GPIO_PINS_SOURCE10
//#define I2Cx_SCL_GPIO_PORT               GPIOB
//#define I2Cx_SCL_GPIO_MUX                GPIO_MUX_4

//#define I2Cx_SDA_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK
//#define I2Cx_SDA_GPIO_PIN                GPIO_PINS_11
//#define I2Cx_SDA_GPIO_PinsSource         GPIO_PINS_SOURCE11
//#define I2Cx_SDA_GPIO_PORT               GPIOB
//#define I2Cx_SDA_GPIO_MUX                GPIO_MUX_4

//volatile unsigned int systick_ms; 

/** @addtogroup 435_GPIO_led_toggle GPIO_led_toggle
  * @{
  */

//void TMR1_OVF_TMR10_IRQHandler(void)
//{
//  if(tmr_interrupt_flag_get(TMR1, TMR_OVF_FLAG) == SET)
//  {
//    /* add user code... */
//		systick_ms++;
//    tmr_flag_clear(TMR1, TMR_OVF_FLAG);
//  }
//}
//crm_clocks_freq_type crm_clocks_freq_struct={0};
//void timer_init(void)
//{
//	crm_clocks_freq_type crm_clocks_freq_struct={0};
//	crm_clocks_freq_get(&crm_clocks_freq_struct);
//	/* enable tmr1 clock */
//  crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

//  /* tmr1 configuration */
//  /* time base configuration */
//  tmr_base_init(TMR1, 9, (crm_clocks_freq_struct.apb2_freq * 2 / 10000) - 1);
//  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

//  /* overflow interrupt enable */
//  tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);

//  /* tmr1 hall interrupt nvic init */
//  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
//  nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 1, 0);

//  /* enable tmr1 */
//  tmr_counter_enable(TMR1, TRUE);
//}

tmr_output_config_type tmr_oc_init_structure;
void PWM_init(void){
	crm_clocks_freq_type crm_clocks_freq_struct={0};
	int prescalervalue;
	gpio_init_type gpio_init_struct;
	crm_periph_clock_enable(CRM_TMR8_PERIPH_CLOCK, TRUE);

  /* gpioa gpiob clock enable */
  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
  crm_clocks_freq_get(&crm_clocks_freq_struct);

  gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOC, &gpio_init_struct);

  gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE6, GPIO_MUX_3);
  gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE7, GPIO_MUX_3);
  gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE8, GPIO_MUX_3);

	prescalervalue = (uint16_t) ((crm_clocks_freq_struct.apb1_freq * 2) / 24000000) - 1;

  /* TMR8 time base configuration */
  tmr_base_init(TMR8, 665, prescalervalue);
  tmr_cnt_dir_set(TMR8, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR8, TMR_CLOCK_DIV1);

  tmr_output_default_para_init(&tmr_oc_init_structure);
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_oc_init_structure.oc_idle_state = FALSE;
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_oc_init_structure.oc_output_state = TRUE;
  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_1, 666);
  tmr_output_channel_buffer_enable(TMR8, TMR_SELECT_CHANNEL_1, TRUE);

  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_2, 0);
  tmr_output_channel_buffer_enable(TMR8, TMR_SELECT_CHANNEL_2, TRUE);

  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_3, &tmr_oc_init_structure);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_3, 666);
  tmr_output_channel_buffer_enable(TMR8, TMR_SELECT_CHANNEL_3, TRUE);


  tmr_period_buffer_enable(TMR8, TRUE);
	tmr_output_enable(TMR8,TRUE);
  /* tmr enable counter */
  tmr_counter_enable(TMR8, TRUE);
}



void tlink_init(void)
{
	unsigned char testStr[] = "XFA3UT9ZE00S9S2K";
	comSendBuf(COM3, "+++", 3);
	delay_ms(1000);
	
	ESP12_SendAT("AT");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n AT fail!\r\n");
		delay_ms(3000);
	}else{
		printf("\r\n AT OK!\r\n");
	}
	ESP12_SendAT("ATE0");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n ATE0 fail\r\n");
	}else{
		printf("\r\n AT OK!\r\n");
	}	
	
	ESP12_SendAT("AT+CWMODE=1");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n CWMODE fail\r\n");
	}else{
		printf("\r\n AT OK!\r\n");
	}
	ESP12_SendAT("AT+CWJAP=\"CC\",\"123456789\"");
	if (ESP12_WaitResponse("OK", 10000) != 1)
	{
		printf("\r\n CWJAP fail\r\n");
		delay_ms(1000);
	}else{
		printf("\r\n AT OK!\r\n");
	}
	ESP12_SendAT("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n CIPSTART fail\r\n");
	}else{
		printf("\r\n AT OK!\r\n");
	}
	
	ESP12_SendAT("AT+CIPMODE=1");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n CIPMODE fail\r\n");
	}else{
		printf("\r\n AT OK!\r\n");
	}
	
	ESP12_SendAT("AT+CIPSEND");
	if (ESP12_WaitResponse("OK", 5000) != 1)
	{
		printf("\r\n CIPMODE fail\r\n");
	}else{
		printf("\r\n AT OK!\r\n");
	}
	printf("\r\n server connected!\r\n");
	comSendBuf(COM3, testStr, strlen(testStr));
	delay_ms(4000);
}
/**
  * @brief  main function.
  * @param  none
  * @retval none
  */

//
int temValue,adcValue,airCtrl=0,lightCtrl=0;
uint8_t heartbeat_sent = 0;
char command_buffer[20];
int command_index,command_ready;
void send_heartbeat(void) {
    char heartbeat[20];
    // ??????,?????????
    static int Tlinktimer32 = 0;
    
    // ???????????
    if (Tlinktimer32 == 0) {
        Tlinktimer32 = Timer_GetTickCount();
        return; // ???????
    }
    
    // ??20???????(???????20000,???20?)
    if (Timer_PassedDelay(Tlinktimer32, 2000)){
				adcValue = analogRead();
			  temValue = lm75_read();
        // ?????????
        sprintf(heartbeat, "#%d,%d,%d,%d#",adcValue,temValue,airCtrl,lightCtrl);
        
        // ?COM3?????
			  printf(heartbeat);
        comSendBuf(COM3, heartbeat, strlen(heartbeat));
        printf("succeed: %s\n", heartbeat);
        
        // ????????
        heartbeat_sent = 1;
        Tlinktimer32 = Timer_GetTickCount(); // ??????????
    }
}

// ???????????

void parse_command(char *cmd) {
    if(strstr(cmd,"[1]")!=NULL){
			airCtrl=1;
		 at32_led_on(LED2);
	}
	if(strstr(cmd,"[2]")!=NULL){
			airCtrl=0;
		at32_led_off(LED2);
	}
	if(strstr(cmd,"[3]")!=NULL){
			lightCtrl=1;
		at32_led_on(LED3);
	}
	if(strstr(cmd,"[4]")!=NULL){
			lightCtrl=0;
		at32_led_off(LED3);
	}
}
void process_received_data(void) {
    uint8_t received_data;

    while (comGetChar(COM3, &received_data)) {
        // ??????
        if (heartbeat_sent){
            printf("OK,have heart");
        }

        // ??JSON??
        if (received_data == '[') {             
            command_index = 0;
            command_buffer[command_index++] = received_data;
            command_ready = 0;
        } else if (received_data == ']' && command_index > 0) {  // ???????
            command_buffer[command_index++] = received_data;
            command_buffer[command_index] = '\0';  
            command_ready = 1;
        } else if (command_index > 0 && command_index < sizeof(command_buffer) - 1) {
            
            command_buffer[command_index++] = received_data;
        }

        // ????????,???
        if (command_ready) {
            parse_command(command_buffer);
            command_ready = 0;
            command_index = 0;
        }
    }
}

int main(void)
{
	char testStr[] =  "4SHXXEA8J21SC8G7";
	unsigned int ledtimer;
	unsigned int ledtimer2;
	unsigned int rgbtimer;
	unsigned int buttontimer;
	int flag = 0;
  uint8_t keyvalue;
	int qvalue;
	int ledTimer;
	//int adcValue,airCtrl=1,lightCtrl=1,temValue=1;
	char TlinkCommandStr[20];
  uint8_t ucKeyCode;
	ucKeyCode = bsp_GetKey();
  system_clock_config();
		 bsp_Init();
//  at32_board_init();
	ledtimer = Timer_GetTickCount();
	ledtimer2 = Timer_GetTickCount();
	rgbtimer = Timer_GetTickCount();
//  timer_init();
	PWM_init();
	//buzz_init();
	tmr_counter_enable(TMR5,FALSE);
	ic2_init();
	eep_write(0,eep_write_buf,16);
	delay_ms(5);
	eep_read(0,eep_read_buf,16);
	
	oledInit();
	oledShowString(0,0,"2023030101045");
	tlink_init();
  while(1)
  {
		  send_heartbeat();
		  process_received_data();
//		if(Timer_PassedDelay(ledtimer,200))
//		{
//			at32_led_toggle(LED2);
//			ledtimer = Timer_GetTickCount();
//		}
//    if(Timer_PassedDelay(ledtimer2,100))
//		{
//			at32_led_toggle(LED3);
//			ledtimer2 = Timer_GetTickCount();
//		}
//		if(Timer_PassedDelay(rgbtimer,1000)){
//			qvalue++;
//			if(qvalue > 666) qvalue = 0;
//			tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_2, qvalue);
//			rgbtimer = Timer_GetTickCount();

		//	printf("The temp is %d\r\n " , lm75_read());
//		}
//		keyvalue = bsp_GetKey();
//		if(keyvalue == KEY_1_DOWN){
//			BEEP_KeyTone();
//		}
//		if(at32_button_press() == RESET){
//			flag = 1;
//			buttontimer = Timer_GetTickCount();
//				tmr_counter_enable(TMR5,TRUE);
//		}
//		if(flag){
//			if(Timer_PassedDelay(buttontimer,50)) 
//			{
//				flag = 0;
//				tmr_counter_enable(TMR5,FALSE);
//			}
//		}
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:
					BEEP_KeyTone();
				  airCtrl ^=0x01;
				  at32_led_toggle(LED2);
					break;				
				
				case KEY_DOWN_K2:
					BEEP_KeyTone();
				  lightCtrl ^= 0x01;
				  at32_led_toggle(LED3);
					break;	
				
				default:                     
					break;
			}
		}
//		if (Timer_PassedDelay(ledTimer, 20000))
//		{
//			ledTimer = Timer_GetTickCount();
//			at32_led_toggle(LED3);
//			adcValue = analogRead();
//			//printf("The adc value is%d",adcValue);
//			sprintf(TlinkCommandStr, "#%d,%d,%d,%d#",temValue,adcValue,airCtrl,lightCtrl);
//			printf(TlinkCommandStr);
//			comSendBuf(COM3, TlinkCommandStr, strlen(TlinkCommandStr));
//		}
  }
}

/**
  * @}
  */

/**
  * @}
  */

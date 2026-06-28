/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.0
  * @date     2020-11-02
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

#include "at32f435_437_clock.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
//#include "at_surf_f437_board_delay.h"
//#include "at_surf_f437_board_touch.h"
//#include "at32f435_437_board_qspi_flash.h"
//#include "at_surf_f437_board_sdram.h"
#include "at32f435_437_board.h"

#include "lv_tick_custom.h"
#include <stdint.h>
#include <string.h>
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
//#include "events_init.h"
#include "custom.h"
#include "bsp.h"
#include "bsp_gt911.h"
#include "tlink.h"
#include "time_manager.h"
#define USING_EXT_FLASH 1
lv_ui guider_ui;
static uint32_t last_time_update = 0;
// 添加界面更新标志
volatile uint8_t screen_update_needed = 0;
lv_ui *global_ui = NULL;

// 设置全局UI指针
void set_global_ui(lv_ui *ui) {
    global_ui = ui;
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
// 在主循环或定时器中添加界面刷新

int main(void)
{
	uint16_t i;
  int LVGLTimer, ledTimer;
  uint8_t ucKeyCode;	
	unsigned int counter = 0;
	char buf[4];
	int temp;
	//bsp init
  bsp_Init();

 #if USING_EXT_FLASH
  ext_flash_init();
 #endif

 	ESP12_SendAT("AT");
	if (ESP12_WaitResponse("OK", 50) == 1)
	{
		printf("\r\n ESP12 resp OK\r\n");
		delay_ms(1000);
	}
  
	
  // driver init 
  tmr7_int_init(287, 999);  //1 micro second interrupt  	
  lcd_init(LCD_DISPLAY_HORIZONTAL_180);
  touch_init(LCD_DISPLAY_HORIZONTAL_180);
  
	//lvgl init
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
	
	//ui init
  setup_ui(&guider_ui);

//  events_init(&guider_ui);
  custom_init(&guider_ui);
	  tlink_init();
	//no-block timer 
  LVGLTimer = Timer_GetTickCount();
  ledTimer = Timer_GetTickCount();
	
  while(1)
  {
		//LGVL
    if(Timer_PassedDelay(LVGLTimer, 25)){
      LVGLTimer = Timer_GetTickCount();
      lv_task_handler();  
			lv_timer_handler();  // 这行必须要有，且要定期调用！			
    }
        if(lv_tick_elaps(last_time_update) > 1000) {
            last_time_update = lv_tick_get();
            
            // 统一增加秒数
            time_manager_increment_seconds();
            
            // 更新主界面显示（如果正在显示主界面）
            lv_obj_t *active_screen = lv_scr_act();
            if(active_screen == guider_ui.main_screen) {
                update_main_screen_time(&guider_ui);
            }
        }
		music_process();                    // 音乐处理
			//check_key1_single_click();          // 按键检测
			send_heartbeat();
     process_received_data();
		  check_and_update_screen();
		   

     update_screen_task();
    //Key
    ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:
					printf("KEY1 is short pressed\r\n");
					break;				
				
				case KEY_DOWN_K2:
					printf("KEY2 is short pressed\r\n");

					break;
				
				case KEY_LONG_K1:
					printf("KEY1 is long pressed\r\n");
					break;	
				
				default:                     
					break;
			}
		}
		
		//other process
		if (Timer_PassedDelay(ledTimer, 2000))
		{

			//ledTimer = Timer_GetTickCount();
			//at32_led_toggle(LED3);
			//temp = (long)analogRead()*3300/4095;
			//sprintf(buf,"%d",temp);
			//lv_label_set_text(guider_ui.mainscreen_label_3,buf);

		}
    
  }
}


//only display one picture
  //  LV_IMG_DECLARE(img_1);
   // lv_obj_t * img = lv_img_create(lv_scr_act());
  //  lv_img_set_src(img, &img_1);
  //  lv_obj_set_pos(img, 0, 0);
  //  lv_img_set_angle(img, 0);

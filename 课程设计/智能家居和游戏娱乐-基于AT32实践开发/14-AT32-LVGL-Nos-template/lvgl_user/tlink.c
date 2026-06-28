#include "tlink.h"
#include <stdio.h>
#include <string.h>
#include "bsp_uart.h"  // 包含您的BSP头文件
#include "bsp.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "bsp.eep_lm75.h"
#include "at32f435_437_clock.h"
// 全局变量定义
int temValue = 26;        // 默认温度值
int adcValue = 2600;      // 默认ADC值  
int airCtrl = 0;          // 空调控制状态
int lightCtrl = 0;        // 灯光控制状态
uint8_t heartbeat_sent = 0;
char command_buffer[20];
int command_index = 0, command_ready = 0;
static volatile uint8_t screen_update_flag = 0;
static uint32_t tick_counter = 0;
extern lv_ui *global_ui;
volatile uint8_t air_state_changed = 0;
volatile uint8_t light_state_changed = 0;
// 获取tick count的函数
uint32_t get_tick_count(void) {

    tick_counter++;
    return tick_counter;
}

// TLINK初始化函数
void tlink_init(void) {
    unsigned char testStr[] = "9B708XA59MS3A3V1";
    
    printf("Initializing TLINK...\n");
    
    // 使用正确的comSendBuf参数
    comSendBuf(COM3, (uint8_t *)"+++", 3);
    delay_ms(1000);
    
    ESP12_SendAT("AT");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("AT fail!\n");
        delay_ms(3000);
    } else {
        printf("AT OK!\n");
    }
    
    ESP12_SendAT("ATE0");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("ATE0 fail\n");
    } else {
        printf("ATE0 OK!\n");
    }	
    
    ESP12_SendAT("AT+CWMODE=1");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("CWMODE fail\n");
    } else {
        printf("AT+CWMODE OK!\n");
    }
    
    ESP12_SendAT("AT+CWJAP=\"cxy\",\"12345679\"");
    if (ESP12_WaitResponse("OK", 10000) != 1) {
        printf("AT+CWJAP fail\n");
        delay_ms(1000);
    } else {
        printf("AT+CWJAP OK!\n");
    }
    
    ESP12_SendAT("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("AT+CIPSTART fail\n");
    } else {
        printf("AT+CIPSTART OK!\n");
    }
    
    ESP12_SendAT("AT+CIPMODE=1");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("AT+CIPMODE fail\n");
    } else {
        printf("AT+CIPMODE OK!\n");
    }
    
    ESP12_SendAT("AT+CIPSEND");
    if (ESP12_WaitResponse("OK", 5000) != 1) {
        printf("AT+CIPSEND fail\n");
    } else {
        printf("AT+CIPSEND OK!\n");
    }
    
    printf("TLINK server connected!\n");
    comSendBuf(COM3, testStr, strlen(testStr));
    delay_ms(4000);
    
    printf("TLINK initialization completed!\n");
}

// 发送心跳数据到TLINK平台
void send_heartbeat(void) {
    char heartbeat[20];

    static int Tlinktimer32 = 0;

    if (Tlinktimer32 == 0) {
        Tlinktimer32 = Timer_GetTickCount();
        return; 
    }

    if (Timer_PassedDelay(Tlinktimer32, 2000)){
				adcValue = analogRead();
			  temValue = lm75_read();
        sprintf(heartbeat, "#%d,%d,%d,%d#",adcValue,temValue,airCtrl,lightCtrl);
        

			  printf(heartbeat);
        comSendBuf(COM3, heartbeat, strlen(heartbeat));
        printf("succeed: %s\n", heartbeat);
       
        heartbeat_sent = 1;
        Tlinktimer32 = Timer_GetTickCount(); // ??????????
    }
}

// 修改 parse_command 函数
void parse_command(char *cmd) {
    printf("Received TLINK command: %s\n", cmd);
    
    int old_airCtrl = airCtrl;
    int old_lightCtrl = lightCtrl;
    
    if(strstr(cmd, "[1]") != NULL) {
        airCtrl = 1;
        at32_led_on(LED2);
        air_state_changed = 1;  // 设置状态变化标志
        printf("Air conditioner turned ON from TLINK\n");
    }
    else if(strstr(cmd, "[2]") != NULL) {
        airCtrl = 0;
        at32_led_off(LED2);
        air_state_changed = 1;  // 设置状态变化标志
        printf("Air conditioner turned OFF from TLINK\n");
    }
    else if(strstr(cmd, "[3]") != NULL) {
        lightCtrl = 1;
        at32_led_on(LED3);
        light_state_changed = 1;  // 设置状态变化标志
        printf("Light turned ON from TLINK\n");
    }
    else if(strstr(cmd, "[4]") != NULL) {
        lightCtrl = 0;
        at32_led_off(LED3);
        light_state_changed = 1;  // 设置状态变化标志
        printf("Light turned OFF from TLINK\n");
    }
    
    // 立即标记需要界面更新
    screen_update_flag = 1;
    
    printf("State changed: Air=%d->%d, Light=%d->%d\n", 
           old_airCtrl, airCtrl, old_lightCtrl, lightCtrl);
}

// 检查并更新界面
void check_and_update_screen(void) {
    if(screen_update_flag && global_ui && global_ui->screen_2) {
        // 直接设置开关状态，不涉及事件回调
        if(airCtrl) {
            lv_obj_add_state(global_ui->screen_2_sw_1, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(global_ui->screen_2_sw_1, LV_STATE_CHECKED);
        }
        
        if(lightCtrl) {
            lv_obj_add_state(global_ui->screen_2_sw_2, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(global_ui->screen_2_sw_2, LV_STATE_CHECKED);
        }
        
        printf("Screen updated from TLINK: Air=%d, Light=%d\n", airCtrl, lightCtrl);
        screen_update_flag = 0;
    }
}

// 处理接收到的数据
void process_received_data(void) {
    uint8_t received_data;

    // 使用正确的comGetChar函数
    while (comGetChar(COM3, &received_data)) {
        // 如果是心跳响应
        if (heartbeat_sent) {
            printf("Heartbeat acknowledged\n");
        }

        // 解析JSON格式命令
        if (received_data == '[') {             
            command_index = 0;
            command_buffer[command_index++] = received_data;
            command_ready = 0;
        } else if (received_data == ']' && command_index > 0) {
            command_buffer[command_index++] = received_data;
            command_buffer[command_index] = '\0';  
            command_ready = 1;
        } else if (command_index > 0 && command_index < sizeof(command_buffer) - 1) {
            command_buffer[command_index++] = received_data;
        }

        // 处理完整命令
        if (command_ready) {
            parse_command(command_buffer);
            command_ready = 0;
            command_index = 0;
        }
    }
}


#ifndef __TLINK_H
#define __TLINK_H

#include <stdint.h>
#include "bsp_uart.h"

// 全局变量声明
extern int temValue;
extern int adcValue;
extern int airCtrl;
extern int lightCtrl;
// 添加状态变化标志
extern volatile uint8_t air_state_changed;
extern volatile uint8_t light_state_changed;
// 函数声明
void tlink_init(void);
void send_heartbeat(void);
void process_received_data(void);
uint32_t get_tick_count(void);
void update_screen_from_tlink(void);
void check_and_update_screen(void);


#endif /* __TLINK_H */
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <stdint.h>

// 时间管理函数
uint32_t time_manager_get_seconds(void);
void time_manager_set_seconds(uint32_t seconds);
void time_manager_increment_seconds(void);
uint8_t time_manager_get_hour(void);
uint8_t time_manager_get_minute(void);
uint8_t time_manager_get_second(void);
void time_manager_get_time_string(char *buffer, uint16_t buffer_size);
void time_manager_get_date_string(char *buffer, uint16_t buffer_size);
int time_manager_get_days_in_month(int year, int month);

#endif
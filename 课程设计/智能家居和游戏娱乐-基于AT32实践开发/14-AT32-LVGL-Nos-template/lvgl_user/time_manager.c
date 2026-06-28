#include "time_manager.h"
#include <stdio.h>

static uint32_t g_system_seconds = 20 * 3600 + 20 * 60; // 初始时间 20:20:00

uint32_t time_manager_get_seconds(void) {
    return g_system_seconds;
}

// 设置系统时间（用于调试）
void time_manager_set_seconds(uint32_t seconds) {
    g_system_seconds = seconds;
}

// 增加秒数（在主循环中调用）
void time_manager_increment_seconds(void) {
    g_system_seconds++;
}

// 获取当前小时
uint8_t time_manager_get_hour(void) {
    return (g_system_seconds / 3600) % 24;
}

// 获取当前分钟  
uint8_t time_manager_get_minute(void) {
    return (g_system_seconds / 60) % 60;
}

// 获取当前秒
uint8_t time_manager_get_second(void) {
    return g_system_seconds % 60;
}

// 获取格式化的时间字符串
void time_manager_get_time_string(char *buffer, uint16_t buffer_size) {
    uint8_t hour = time_manager_get_hour();
    uint8_t minute = time_manager_get_minute();
    snprintf(buffer, buffer_size, "%02d:%02d", hour, minute);
}

// 获取格式化的日期字符串
void time_manager_get_date_string(char *buffer, uint16_t buffer_size) {
    uint32_t total_days = g_system_seconds / 86400;
    
    // 从2025年11月27日开始计算
    int year = 2025;
    int month = 11;
    int day = 27;
    
    // 日期计算
    day += total_days;
    while(day > time_manager_get_days_in_month(year, month)) {
        day -= time_manager_get_days_in_month(year, month);
        month++;
        if(month > 12) {
            month = 1;
            year++;
        }
    }
    
    snprintf(buffer, buffer_size, "%d-%d-%d", year, month, day);
}

// 获取月份天数
int time_manager_get_days_in_month(int year, int month) {
    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if(month == 2) {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
    }
    
    if(month >= 1 && month <= 12) {
        return days_in_month[month - 1];
    }
    
    return 30;
}
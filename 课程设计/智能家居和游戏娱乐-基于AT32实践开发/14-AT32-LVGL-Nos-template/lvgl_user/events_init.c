/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "gomoku.h"
#include "music.h"
#include "bsp.h"
extern lv_obj_t *status_label;
extern lv_obj_t *game_canvas;
extern int gobang_board[15][15];
extern bool current_player;
extern void draw_board(void);
extern int check_win(int x, int y, int player);
extern int temValue;
extern int adcValue;
extern int airCtrl;
extern int lightCtrl;
extern lv_ui *global_ui;
extern volatile uint8_t air_state_changed;
extern volatile uint8_t light_state_changed;
void events_init(lv_ui *ui)
{
}

static void main_screen_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.screen_1_del == true)
				setup_scr_screen_1(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_1, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.main_screen_del = true;
		}
	}
		break;
	default:
		break;
	}
}

static void main_screen_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.screen_2_del == true)
				setup_scr_screen_2(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.main_screen_del = true;
		}
	}
		break;
	default:
		break;
	}
}

static void main_screen_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.screen_3_del == true)
				setup_scr_screen_3(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_3, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.main_screen_del = true;
		}
	}
		break;
	default:
		break;
	}
}

static void main_screen_btn_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.screen_4_del == true)
				setup_scr_screen_4(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_4, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.main_screen_del = true;
		}
	}
		break;
	default:
		break;
	}
}

void events_init_main_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main_screen_btn_1, main_screen_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_screen_btn_2, main_screen_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_screen_btn_3, main_screen_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_screen_btn_8, main_screen_btn_8_event_handler, LV_EVENT_ALL, ui);
}

// 五子棋重新开始按钮事件
static void screen_1_restart_btn_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        gomoku_reset_game(&guider_ui);
    }
}

// 五子棋退出按钮事件
static void screen_1_exit_bt_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        lv_obj_t * act_scr = lv_scr_act();
        lv_disp_t * d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
            lv_obj_clean(act_scr);
            guider_ui.main_screen_del = true;
            if (guider_ui.main_screen_del == true) {
                setup_scr_main_screen(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
            guider_ui.screen_1_del = true;
        }
    }
}

// 五子棋悔棋按钮事件
static void screen_1_undo_btn_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        gomoku_undo_move(&guider_ui);
    }
}

// 修改 events_init_screen_1 函数
void events_init_screen_1(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_1_restart_btn, screen_1_restart_btn_event_handler, LV_EVENT_CLICKED, ui);
    lv_obj_add_event_cb(ui->screen_1_undo_btn, screen_1_undo_btn_event_handler, LV_EVENT_CLICKED, ui);
    lv_obj_add_event_cb(ui->screen_1_exit_bt, screen_1_exit_bt_event_handler, LV_EVENT_CLICKED, ui);
    
    // 开始游戏
    gomoku_start_game(ui);
}
/**
 * @brief Event callback for Gobang board click
 */

// screen_2 空调开关事件处理
static void screen_2_sw_1_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *sw = lv_event_get_target(e);
    
    if(code == LV_EVENT_VALUE_CHANGED) {
        bool state = lv_obj_has_state(sw, LV_STATE_CHECKED);
        airCtrl = state ? 1 : 0;
        
        if(state) {
            at32_led_on(LED2);
        } else {
            at32_led_off(LED2);
        }
        
        // 只在状态变化时打印
        static bool last_air_state = false;
        if(state != last_air_state) {
            printf("Air %s\n", state ? "ON" : "OFF");
            last_air_state = state;
        }
    }
}

// screen_2 灯光开关事件处理
static void screen_2_sw_2_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *sw = lv_event_get_target(e);
    
    if(code == LV_EVENT_VALUE_CHANGED) {
        bool state = lv_obj_has_state(sw, LV_STATE_CHECKED);
        lightCtrl = state ? 1 : 0;
        
        if(state) {
            at32_led_on(LED3);
        } else {
            at32_led_off(LED3);
        }
        
        // 只在状态变化时打印
        static bool last_light_state = false;
        if(state != last_light_state) {
            printf("Light %s\n", state ? "ON" : "OFF");
            last_light_state = state;
        }
    }
}

// 专门的TLINK状态更新函数
void update_switch_states_from_tlink(void) {
    if(global_ui && global_ui->screen_2) {
        static int last_air_state = -1;
        static int last_light_state = -1;
        
        // 检查空调状态变化
        if(air_state_changed || airCtrl != last_air_state) {
            printf("Updating air switch state to: %d\n", airCtrl);
            
            // 直接设置开关状态，不操作事件回调
            if(airCtrl) {
                lv_obj_add_state(global_ui->screen_2_sw_1, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(global_ui->screen_2_sw_1, LV_STATE_CHECKED);
            }
            
            air_state_changed = 0;
            last_air_state = airCtrl;
        }
        
        // 检查灯光状态变化
        if(light_state_changed || lightCtrl != last_light_state) {
            printf("Updating light switch state to: %d\n", lightCtrl);
            
            // 直接设置开关状态，不操作事件回调
            if(lightCtrl) {
                lv_obj_add_state(global_ui->screen_2_sw_2, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(global_ui->screen_2_sw_2, LV_STATE_CHECKED);
            }
            
            light_state_changed = 0;
            last_light_state = lightCtrl;
        }
    }
}

// 修改 update_screen_task
void update_screen_task(void) {
    static uint32_t last_update_time = 0;
    uint32_t current_time = lv_tick_get();
    
    // 每100ms检查一次状态变化（更频繁）
    if(current_time - last_update_time > 100) {
        // 处理TLINK状态更新
        update_switch_states_from_tlink();
        
        // 更新其他显示数据
        if(global_ui && global_ui->screen_2) {
            // 更新温度显示
            char temp_str[20];
            sprintf(temp_str, "%d°", temValue);
            lv_label_set_text(global_ui->screen_2_label_4, temp_str);
            
            // 更新AD采集显示
            char adc_str[20];
            sprintf(adc_str, "%d", adcValue);
            lv_label_set_text(global_ui->screen_2_label_6, adc_str);
        }
        
        last_update_time = current_time;
    }
}


// screen_2 返回按钮事件处理
static void screen_2_btn_5_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        lv_obj_t * act_scr = lv_scr_act();
        lv_disp_t * d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
            lv_obj_clean(act_scr);
            guider_ui.main_screen_del = true;
            if (guider_ui.main_screen_del == true) {
                setup_scr_main_screen(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
            guider_ui.screen_2_del = true;
        }
    }
}

// 更新screen_2显示数据
void update_screen_2_display(lv_ui *ui) {
    if(!ui || !ui->screen_2) {
        printf("Warning: Cannot update screen - UI or screen_2 is NULL\n");
        return;
    }
    
    // 更新温度显示
    char temp_str[20];
    sprintf(temp_str, "%d°", temValue);
    lv_label_set_text(ui->screen_2_label_4, temp_str);
    
    // 更新AD采集显示
    char adc_str[20];
    sprintf(adc_str, "%d", adcValue);
    lv_label_set_text(ui->screen_2_label_6, adc_str);
    
    // 更新开关状态
    if(airCtrl) {
        lv_obj_add_state(ui->screen_2_sw_1, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(ui->screen_2_sw_1, LV_STATE_CHECKED);
    }
    
    if(lightCtrl) {
        lv_obj_add_state(ui->screen_2_sw_2, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(ui->screen_2_sw_2, LV_STATE_CHECKED);
    }
    
    printf("Screen updated: Air=%d, Light=%d, Temp=%d, ADC=%d\n", 
           airCtrl, lightCtrl, temValue, adcValue);
}

// 初始化screen_2事件
void events_init_screen_2(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_2_sw_1, screen_2_sw_1_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui->screen_2_sw_2, screen_2_sw_2_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui->screen_2_btn_5, screen_2_btn_5_event_handler, LV_EVENT_CLICKED, ui);
    
    // 初始化开关状态
    update_screen_2_display(ui);
}

static void screen_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.main_screen_del == true)
				setup_scr_main_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.screen_3_del = true;
		}
	}
		break;
	default:
		break;
	}
}

static void screen_3_btn_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t * act_scr = lv_scr_act();
        lv_disp_t * d = lv_obj_get_disp(act_scr);
        
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            // 清理当前屏幕
            lv_obj_clean(act_scr);
            
            // 如果需要重新创建主屏幕
            if (guider_ui.main_screen_del == true) {
                setup_scr_main_screen(&guider_ui);
                events_init_main_screen(&guider_ui);
            }
            
            // 使用动画加载主屏幕
            lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
            
   
            guider_ui.screen_3_del = true;
            
            printf("成功返回主屏幕\n");
        }
        break;
    }
    default:
        break;
    }
}
// 播放控制按钮事件处理
static void play_control_event_cb(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    
    if(code == LV_EVENT_CLICKED) {
        uint32_t func = (uint32_t)lv_event_get_user_data(e);
        
        printf("按钮点击: 功能=%d\n", func);
        
        switch(func) {
            case 0: // 上一首 (screen_3_img_2)
                printf("上一首\n");
                music_prev_song();
                break;
            case 1: // 暂停 (screen_3_img_3)
                printf("暂停\n");
                music_toggle_pause();
                break;
            case 2: // 开始播放 (screen_3_img_4)
                printf("开始播放\n");
                if(!music_playing) {
                    printf("当前未播放，开始播放\n");
                    music_play_song(current_song);
                } else if(music_pause) {
                    printf("当前暂停，恢复播放\n");
                    music_toggle_pause();
                } else {
                    printf("已经在播放中\n");
                }
                break;
            case 3: // 下一首 (screen_3_img_5)
                printf("下一首\n");
                music_next_song();
                break;
        }
    }
}


// 退出按钮事件处理 - 返回主屏幕
static void exit_btn_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        printf("返回主屏幕\n");
        music_stop();
        
        // 跳转到主屏幕
        if(guider_ui.main_screen != NULL) {
            lv_scr_load(guider_ui.main_screen);
        } else {
            printf("错误: 主屏幕未定义\n");
        }
    }
}

void events_init_screen_3(lv_ui *ui) {
    // 绑定播放控制按钮事件
    // screen_3_img_2 (上一首)
    lv_obj_add_event_cb(ui->screen_3_img_2, play_control_event_cb, LV_EVENT_CLICKED, (void*)0);
    
    // screen_3_img_3 (暂停)
    lv_obj_add_event_cb(ui->screen_3_img_4, play_control_event_cb, LV_EVENT_CLICKED, (void*)1);
    
    // screen_3_img_4 (开始播放)
    lv_obj_add_event_cb(ui->screen_3_img_3, play_control_event_cb, LV_EVENT_CLICKED, (void*)2);
    
    // screen_3_img_5 (下一首)
    lv_obj_add_event_cb(ui->screen_3_img_5, play_control_event_cb, LV_EVENT_CLICKED, (void*)3);
    
    // 绑定退出按钮事件
    lv_obj_add_event_cb(ui->screen_3_btn_6, screen_3_btn_6_event_handler, LV_EVENT_CLICKED, NULL);
    
}

static void screen_4_btn_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * act_scr = lv_scr_act();
		lv_disp_t * d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			lv_obj_clean(act_scr);
			if (guider_ui.main_screen_del == true)
				setup_scr_main_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true);
			guider_ui.screen_4_del = true;
		}
	}
		break;
	default:
		break;
	}
}

void events_init_screen_4(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_4_btn_9, screen_4_btn_9_event_handler, LV_EVENT_ALL, ui);
}

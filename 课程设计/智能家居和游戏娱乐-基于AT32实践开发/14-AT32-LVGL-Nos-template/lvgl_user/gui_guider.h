/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_label_1;
	lv_obj_t *main_screen_label_2;
	lv_obj_t *main_screen_btn_1;
	lv_obj_t *main_screen_btn_1_label;
	lv_obj_t *main_screen_btn_2;
	lv_obj_t *main_screen_btn_2_label;
	lv_obj_t *main_screen_btn_3;
	lv_obj_t *main_screen_btn_3_label;
	lv_obj_t *main_screen_btn_8;
	lv_obj_t *main_screen_btn_8_label;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_board_area;
	lv_obj_t *screen_1_current_player_label;
	lv_obj_t *screen_1_status_label;
	lv_obj_t *screen_1_restart_btn;
	lv_obj_t *screen_1_restart_btn_label;
	lv_obj_t *screen_1_exit_bt;
	lv_obj_t *screen_1_exit_bt_label;
	lv_obj_t *screen_1_undo_btn;
	lv_obj_t *screen_1_undo_btn_label;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_btn_5;
	lv_obj_t *screen_2_btn_5_label;
	lv_obj_t *screen_2_img_1;
	lv_obj_t *screen_2_img_2;
	lv_obj_t *screen_2_img_3;
	lv_obj_t *screen_2_label_3;
	lv_obj_t *screen_2_label_4;
	lv_obj_t *screen_2_sw_1;
	lv_obj_t *screen_2_sw_2;
	lv_obj_t *screen_2_label_5;
	lv_obj_t *screen_2_label_6;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_btn_6;
	lv_obj_t *screen_3_btn_6_label;
	lv_obj_t *screen_3_img_1;
	lv_obj_t *screen_3_img_2;
	lv_obj_t *screen_3_img_3;
	lv_obj_t *screen_3_img_4;
	lv_obj_t *screen_3_img_5;
	lv_obj_t *screen_4;
	bool screen_4_del;
	lv_obj_t *screen_4_calendar_2;
	lv_obj_t *screen_4_btn_9;
	lv_obj_t *screen_4_btn_9_label;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void setup_scr_screen_3(lv_ui *ui);
void setup_scr_screen_4(lv_ui *ui);
static lv_calendar_date_t today;
static lv_calendar_date_t highlihted_days[1];
void update_screen_2_display(lv_ui *ui);
void set_global_ui(lv_ui *ui);
void update_screen_task(void);
LV_IMG_DECLARE(_33_alpha_100x100);
LV_IMG_DECLARE(_22_alpha_100x100);
LV_IMG_DECLARE(_104_alpha_50x50);
LV_IMG_DECLARE(_11_alpha_100x100);
LV_IMG_DECLARE(_105_alpha_60x50);
LV_IMG_DECLARE(_1_alpha_284x226);
LV_IMG_DECLARE(_102_alpha_60x50);
LV_IMG_DECLARE(_106_alpha_50x50);

#ifdef __cplusplus
}
#endif
#endif
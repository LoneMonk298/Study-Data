/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

static lv_obj_t * g_kb_screen_3;
static void kb_screen_3_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
__attribute__((unused)) static void ta_screen_3_event_cb(lv_event_t *e)
{

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}

void setup_scr_screen_3(lv_ui *ui){

	//Write codes screen_3
	ui->screen_3 = lv_obj_create(NULL);

	//Create keyboard on screen_3
	g_kb_screen_3 = lv_keyboard_create(ui->screen_3);
	lv_obj_add_event_cb(g_kb_screen_3, kb_screen_3_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(g_kb_screen_3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(g_kb_screen_3, &lv_font_simsun_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->screen_3, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_3, lv_color_make(0xff, 0x00, 0x27), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_btn_6
	ui->screen_3_btn_6 = lv_btn_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_btn_6, 369, 21);
	lv_obj_set_size(ui->screen_3_btn_6, 90, 45);
	lv_obj_set_scrollbar_mode(ui->screen_3_btn_6, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_btn_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_3_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_3_btn_6, lv_color_make(0xff, 0x00, 0x27), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_3_btn_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_3_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_3_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_3_btn_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_3_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_3_btn_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_3_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_3_btn_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_3_btn_6, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_3_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_3_btn_6_label = lv_label_create(ui->screen_3_btn_6);
	lv_label_set_text(ui->screen_3_btn_6_label, "返回");
	lv_obj_set_style_pad_all(ui->screen_3_btn_6, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_3_btn_6_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_3_img_1
	ui->screen_3_img_1 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_1, 1, 11);
	lv_obj_set_size(ui->screen_3_img_1, 284, 226);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_1, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_3_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_3_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_3_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_1,&_1_alpha_284x226);
	lv_img_set_pivot(ui->screen_3_img_1, 50,50);
	lv_img_set_angle(ui->screen_3_img_1, 0);

	//Write codes screen_3_img_2
	ui->screen_3_img_2 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_2, 276, 167);
	lv_obj_set_size(ui->screen_3_img_2, 60, 50);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_2, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_3_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_3_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_2,&_102_alpha_60x50);
	lv_img_set_pivot(ui->screen_3_img_2, 50,50);
	lv_img_set_angle(ui->screen_3_img_2, 0);

	//Write codes screen_3_img_3
	ui->screen_3_img_3 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_3, 355, 167);
	lv_obj_set_size(ui->screen_3_img_3, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_3, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_3_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_3_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_3_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_3,&_104_alpha_50x50);
	lv_img_set_pivot(ui->screen_3_img_3, 50,50);
	lv_img_set_angle(ui->screen_3_img_3, 0);

	//Write codes screen_3_img_4
	ui->screen_3_img_4 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_4, 355, 167);
	lv_obj_set_size(ui->screen_3_img_4, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_4, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_3_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_3_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_4, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_4,&_106_alpha_50x50);
	lv_img_set_pivot(ui->screen_3_img_4, 50,50);
	lv_img_set_angle(ui->screen_3_img_4, 0);

	//Write codes screen_3_img_5
	ui->screen_3_img_5 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_5, 415, 167);
	lv_obj_set_size(ui->screen_3_img_5, 60, 50);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_5, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_3_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_3_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_3_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_5, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_5,&_105_alpha_60x50);
	lv_img_set_pivot(ui->screen_3_img_5, 50,50);
	lv_img_set_angle(ui->screen_3_img_5, 0);

	//Init events for screen
	events_init_screen_3(ui);
}
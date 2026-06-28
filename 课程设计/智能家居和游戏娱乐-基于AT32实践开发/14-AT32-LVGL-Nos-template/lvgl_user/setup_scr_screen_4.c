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

static void screen_4_calendar_2draw_part_begin_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
	if(dsc->part == LV_PART_ITEMS) {
		if(dsc->id < 7) {
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_montserratMedium_12;
		}	else if (lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_DISABLED)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 0;
			dsc->label_dsc->color = lv_color_make(0xA9, 0xA2, 0xA2);
			dsc->label_dsc->font = &lv_font_montserratMedium_12;
		}		else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_1)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 255;
			dsc->rect_dsc->border_color = lv_color_make(0xc0, 0xc0, 0xc0);
			dsc->rect_dsc->border_width = 1;
			dsc->rect_dsc->border_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_montserratMedium_12;
		}
		else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_2)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_montserratMedium_12;
		}	else {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 0;
			dsc->rect_dsc->border_color = lv_color_make(0xc0, 0xc0, 0xc0);
			dsc->rect_dsc->border_width = 1;
			dsc->rect_dsc->border_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_montserratMedium_12;
		}
	}
}

static lv_calendar_date_t date;
static void screen_4_calendar_2_event_handler(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED) {
		lv_obj_t * obj =lv_event_get_current_target(e);
		lv_calendar_get_pressed_date(obj,&date);
		lv_calendar_set_highlighted_dates(obj, &date, 1);
	}
}
static lv_obj_t * g_kb_screen_4;
static void kb_screen_4_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
__attribute__((unused)) static void ta_screen_4_event_cb(lv_event_t *e)
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

void setup_scr_screen_4(lv_ui *ui){

	//Write codes screen_4
	ui->screen_4 = lv_obj_create(NULL);

	//Create keyboard on screen_4
	g_kb_screen_4 = lv_keyboard_create(ui->screen_4);
	lv_obj_add_event_cb(g_kb_screen_4, kb_screen_4_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(g_kb_screen_4, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(g_kb_screen_4, &lv_font_simsun_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->screen_4, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->screen_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_4_calendar_2
	ui->screen_4_calendar_2 = lv_calendar_create(ui->screen_4);
	lv_obj_set_pos(ui->screen_4_calendar_2, 107, 31);
	lv_obj_set_size(ui->screen_4_calendar_2, 280, 210);
	lv_obj_set_scrollbar_mode(ui->screen_4_calendar_2, LV_SCROLLBAR_MODE_OFF);
	today.year = 2025;
	today.month = 11;
	today.day = 11;
	lv_calendar_set_today_date(ui->screen_4_calendar_2, today.year, today.month, today.day);
	lv_calendar_set_showed_date(ui->screen_4_calendar_2, today.year, today.month);
	highlihted_days[0].year = 2025;
	highlihted_days[0].month = 11;
	highlihted_days[0].day = 12;
	lv_calendar_set_highlighted_dates(ui->screen_4_calendar_2, highlihted_days, 1);
	lv_obj_t *screen_4_calendar_2_header = lv_calendar_header_arrow_create(ui->screen_4_calendar_2);
	lv_calendar_t * screen_4_calendar_2 = (lv_calendar_t *)ui->screen_4_calendar_2;
	lv_obj_add_event_cb(screen_4_calendar_2->btnm, screen_4_calendar_2draw_part_begin_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
	lv_obj_add_event_cb(ui->screen_4_calendar_2, screen_4_calendar_2_event_handler, LV_EVENT_ALL, NULL);

	//Set style for screen_4_calendar_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_4_calendar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_4_calendar_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_4_calendar_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_4_calendar_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_4_calendar_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_4_calendar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_4_calendar_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_4_calendar_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_4_calendar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_4_calendar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_4_calendar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_4_calendar_2, lv_color_make(0xc0, 0xc0, 0xc0), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_4_calendar_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_4_calendar_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_screen_4_calendar_2_extra_header_main_default
	static lv_style_t style_screen_4_calendar_2_extra_header_main_default;
	ui_init_style(&style_screen_4_calendar_2_extra_header_main_default);
	lv_style_set_bg_color(&style_screen_4_calendar_2_extra_header_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_4_calendar_2_extra_header_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_4_calendar_2_extra_header_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_4_calendar_2_extra_header_main_default, 255);
	lv_style_set_text_color(&style_screen_4_calendar_2_extra_header_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_4_calendar_2_extra_header_main_default, &lv_font_montserratMedium_12);
	lv_obj_add_style(screen_4_calendar_2_header, &style_screen_4_calendar_2_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_4_btn_9
	ui->screen_4_btn_9 = lv_btn_create(ui->screen_4);
	lv_obj_set_pos(ui->screen_4_btn_9, 11, 205);
	lv_obj_set_size(ui->screen_4_btn_9, 68, 36);
	lv_obj_set_scrollbar_mode(ui->screen_4_btn_9, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_4_btn_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_4_btn_9, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_4_btn_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_4_btn_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_4_btn_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_4_btn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_4_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_4_btn_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_4_btn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_4_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_4_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_4_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_4_btn_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_4_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_4_btn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_4_btn_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_4_btn_9, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_4_btn_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_4_btn_9_label = lv_label_create(ui->screen_4_btn_9);
	lv_label_set_text(ui->screen_4_btn_9_label, "back");
	lv_obj_set_style_pad_all(ui->screen_4_btn_9, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_4_btn_9_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_screen_4(ui);
}
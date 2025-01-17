//this is the screen3 where vibrationData.vibrationY will be print on the chart2

// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
extern lv_coord_t ui_Chart2_series_1_array[200];

void ui_Screen3_screen_init(void)
{
    ui_Screen3 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen3, lv_color_hex(0x71BEA3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Screen3);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -196);
    lv_obj_set_y(ui_Label3, -206);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Ventilateur: Donnees Vibrations...");
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button5 = lv_btn_create(ui_Screen3);
    lv_obj_set_width(ui_Button5, 197);
    lv_obj_set_height(ui_Button5, 55);
    lv_obj_set_x(ui_Button5, -288);
    lv_obj_set_y(ui_Button5, 195);
    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label5 = lv_label_create(ui_Screen3);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, -289);
    lv_obj_set_y(ui_Label5, 194);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Retourner a l'accueil ");

    ui_Chart2 = lv_chart_create(ui_Screen3);
    lv_obj_set_width(ui_Chart2, 711);
    lv_obj_set_height(ui_Chart2, 290);
    lv_obj_set_align(ui_Chart2, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart2, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_obj_set_style_size(ui_Chart2, 0, LV_PART_INDICATOR); // Do not display points on the data


    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);

}

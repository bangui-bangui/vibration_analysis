// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen4_screen_init(void)
{
    ui_Screen4 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen4, lv_color_hex(0x997341), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chart3 = lv_chart_create(ui_Screen4);
    lv_obj_set_width(ui_Chart3, 711);
    lv_obj_set_height(ui_Chart3, 290);
    lv_obj_set_align(ui_Chart3, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart3, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_Chart3, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
    lv_chart_set_axis_tick(ui_Chart3, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart3, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart3, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_obj_set_style_size(ui_Chart3, 0, LV_PART_INDICATOR); // Do not display points on the data



    ui_Button6 = lv_btn_create(ui_Screen4);
    lv_obj_set_width(ui_Button6, 172);
    lv_obj_set_height(ui_Button6, 50);
    lv_obj_set_x(ui_Button6, -307);
    lv_obj_set_y(ui_Button6, 199);
    lv_obj_set_align(ui_Button6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_Screen4);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, -302);
    lv_obj_set_y(ui_Label6, 197);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Retourner a l'accueil ");

    ui_Label7 = lv_label_create(ui_Screen4);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, -232);
    lv_obj_set_y(ui_Label7, -215);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "Vibrant: Donnees Vibrations...");
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);

}
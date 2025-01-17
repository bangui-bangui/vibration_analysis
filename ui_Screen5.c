// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen5_screen_init(void)
{
    ui_Screen5 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen5, lv_color_hex(0x466F11), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_Screen5);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, -252);
    lv_obj_set_y(ui_Label8, -201);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "Vis A: Donnees Vibrations...");
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chart4 = lv_chart_create(ui_Screen5);
    lv_obj_set_width(ui_Chart4, 711);
    lv_obj_set_height(ui_Chart4, 290);
    lv_obj_set_align(ui_Chart4, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart4, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_Chart4, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
    lv_chart_set_axis_tick(ui_Chart4, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart4, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart4, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_obj_set_style_size(ui_Chart4, 0, LV_PART_INDICATOR); // Do not display points on the data


    ui_Button9 = lv_btn_create(ui_Screen5);
    lv_obj_set_width(ui_Button9, 168);
    lv_obj_set_height(ui_Button9, 50);
    lv_obj_set_x(ui_Button9, -299);
    lv_obj_set_y(ui_Button9, 206);
    lv_obj_set_align(ui_Button9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button9, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label9 = lv_label_create(ui_Screen5);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, -296);
    lv_obj_set_y(ui_Label9, 207);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "Retourner a l'accueil ");

    lv_obj_add_event_cb(ui_Button9, ui_event_Button9, LV_EVENT_ALL, NULL);

}

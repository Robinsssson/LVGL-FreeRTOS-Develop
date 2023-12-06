#include "page4.h"
#include "page2.h"
#define DEBUG 0

extern int prepage;

const char *text_stop = "stop";
extern const char *text_mode_name_1;
extern const char *text_mode_name_2;
// extern lv_obj_t * main_windows_page2_1;

static lv_style_t style_sub_windows;

uint16_t temperature_initarrary[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t water_initarrary[]       = {2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                                     2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
#if DEBUG
LV_IMG_DECLARE(img_pagebackground1)
#endif

extern linklist page_list;

static lv_obj_t *label_mode_name;
static lv_obj_t *btn_stop;
static lv_obj_t *label_sub_btn;
static lv_obj_t *label_count;
static lv_obj_t *sub_windows_temperature;
static lv_obj_t *sub_windows_water;
static lv_obj_t *label_temperature;
static lv_obj_t *label_water;
static lv_obj_t *btn_backforward;
static lv_obj_t *label_backforward;
static lv_obj_t *chart_temperature;
static lv_obj_t *chart_water;
static lv_obj_t *sub_windows_water;
static lv_chart_series_t *temperature;
static lv_chart_series_t *water;

static void event_btn_backforward(lv_event_t *e)
{
    page_callback(page_list, PAGE4_INIT, PAGE1_INIT, LV_SCR_LOAD_ANIM_NONE, true);
}

static void event_btn_stop(lv_event_t *e)
{
    uint32_t color = lv_color_to32(lv_obj_get_style_bg_color(btn_stop, LV_PART_MAIN));

    if (color != lv_color_to32(lv_color_hex(0xb7191b))) {
        lv_obj_set_style_bg_color(btn_stop, lv_color_hex(0xb7191b), LV_STATE_DEFAULT);
        lv_label_set_text(label_sub_btn, text_stop);
    } else {
        lv_obj_set_style_bg_color(btn_stop, lv_color_hex(0x22cb6a), LV_STATE_DEFAULT);
        lv_label_set_text(label_sub_btn, "start");
    }
}

void page4_init(lv_obj_t *root)
{
    // set_this_page(PAGE2_1);
    lv_style_set_bg_color(&style_sub_windows, lv_color_hex(0xe7e9e1));
#if DEBUG
    lv_obj_t *img_pagebg1 = lv_img_create(main_windows);
    lv_img_set_src(img_pagebg1, &img_pagebackground1);
    lv_img_set_size_mode(img_pagebg1, LV_IMG_SIZE_MODE_REAL);
    lv_img_set_zoom(img_pagebg1, 40);
    lv_obj_update_layout(img_pagebg1);
    lv_obj_align(img_pagebg1, LV_ALIGN_BOTTOM_LEFT, 0, 0);
#endif

    label_mode_name = lv_label_create(root);
    if (prepage == 1) {
        lv_label_set_text(label_mode_name, text_mode_name_1);
    } else if (prepage == 2) {
        lv_label_set_text(label_mode_name, text_mode_name_2);
    } else {
        lv_label_set_text(label_mode_name, "Error!");
    }

    lv_obj_align_to(label_mode_name, root, LV_ALIGN_TOP_MID, 0, 20);

    btn_stop = lv_btn_create(root);
    lv_obj_set_size(btn_stop, 150, 50);
    lv_obj_align_to(btn_stop, root, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_style_bg_color(btn_stop, lv_color_hex(0xb7191b), LV_STATE_DEFAULT);
    // lv_obj_add_style(btn_stop, fn_btn_stop_style(), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_stop, event_btn_stop, LV_EVENT_RELEASED, 0);

    label_sub_btn = lv_label_create(btn_stop);
    lv_label_set_text(label_sub_btn, text_stop);
    lv_obj_align_to(label_sub_btn, btn_stop, LV_ALIGN_CENTER, 0, 0);

    label_count = lv_label_create(root);
    lv_label_set_long_mode(label_count, LV_LABEL_LONG_TXT_HINT);
    lv_obj_set_size(label_count, 150, 20);
    lv_label_set_text_fmt(label_count, "count:  %2d min %2d snd", 1, 1);
    lv_obj_set_style_text_align(label_count, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_align_to(label_count, btn_stop, LV_ALIGN_OUT_TOP_MID, 0, -10);

    sub_windows_temperature = lv_obj_create(root);
    lv_obj_set_size(sub_windows_temperature, 350, 240);
    lv_obj_align_to(sub_windows_temperature, root, LV_ALIGN_TOP_MID, -180, 50);
    lv_obj_add_style(sub_windows_temperature, &style_sub_windows, LV_STATE_DEFAULT);

    sub_windows_water = lv_obj_create(root);
    lv_obj_set_size(sub_windows_water, 350, 240);
    lv_obj_align_to(sub_windows_water, root, LV_ALIGN_TOP_MID, 180, 50);
    lv_obj_add_style(sub_windows_water, &style_sub_windows, LV_STATE_DEFAULT);

    label_temperature = lv_label_create(root);
    lv_label_set_long_mode(label_temperature, LV_LABEL_LONG_WRAP);
    lv_obj_set_size(label_temperature, 300, 20);
    lv_label_set_text_fmt(label_temperature, "temperature:  %2d degree", 11);
    lv_obj_set_style_text_align(label_temperature, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_align_to(label_temperature, sub_windows_temperature, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    label_water = lv_label_create(root);
    lv_label_set_long_mode(label_water, LV_LABEL_LONG_WRAP);
    lv_obj_set_size(label_water, 300, 20);
    lv_label_set_text_fmt(label_water, "water:  %2d ml", 11);
    lv_obj_set_style_text_align(label_water, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_align_to(label_water, sub_windows_water, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    btn_backforward = lv_btn_create(root);
    lv_obj_align_to(btn_backforward, root, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(btn_backforward, btn_start_style(), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_backforward, event_btn_backforward, LV_EVENT_RELEASED, 0);

    label_backforward = lv_label_create(btn_backforward);
    lv_label_set_text(label_backforward, LV_SYMBOL_LEFT);
    lv_obj_align_to(label_backforward, btn_backforward, LV_ALIGN_CENTER, 0, 0);

    chart_temperature = lv_chart_create(root);
    lv_obj_set_size(chart_temperature, 320, 210);
    lv_obj_align_to(chart_temperature, sub_windows_temperature, LV_ALIGN_CENTER, 0, -5);
    lv_chart_set_div_line_count(chart_temperature, 10, 20);
    lv_chart_set_point_count(chart_temperature, 20);
    lv_chart_set_update_mode(chart_temperature, LV_CHART_UPDATE_MODE_SHIFT);
    temperature = lv_chart_add_series(chart_temperature, lv_color_hex(0xf5574b), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_ext_y_array(chart_temperature, temperature, (lv_coord_t *)temperature_initarrary);

    chart_water = lv_chart_create(root);
    lv_obj_set_size(chart_water, 320, 210);
    lv_obj_align_to(chart_water, sub_windows_water, LV_ALIGN_CENTER, 0, -5);
    lv_chart_set_div_line_count(chart_water, 10, 20);
    lv_chart_set_point_count(chart_water, 20);
    lv_chart_set_update_mode(chart_water, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_range(chart_water, LV_CHART_AXIS_PRIMARY_Y, 0, 2000);
    water = lv_chart_add_series(chart_water, lv_color_hex(0xf5574b), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_ext_y_array(chart_water, water, (lv_coord_t *)water_initarrary);
}
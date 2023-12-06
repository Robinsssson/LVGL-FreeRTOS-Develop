#include "page2.h"

#define DEBUG 0
const char *text_mode_name_1  = "local mode: Normal Mode";
const char *text_mode_name_2  = "local mode: Fry first and then serve mode";
const char *text_start      = "start";
const char *text_min        = "min";
const char *text_sec        = "snd";
const char *text_time1      = "time1";
const char *text_time2      = "time2";
const char *text_unitwater  = "ml";
const char *text_startinput = "input";
const char *text_finalget   = "final";

extern int prepage;

static lv_style_t btn_style;
static lv_style_t all_tmp_style;
static lv_style_t btn_stop_style;

#if DEBUG
LV_IMG_DECLARE(img_pagebackground1)
#endif
extern linklist page_list;
static lv_obj_t *sub_windows;
static lv_obj_t *label_mode_name;
static lv_obj_t *btn_start;
static lv_obj_t *label_sub_btn;
static lv_obj_t *textarea_waiting_min1;
static lv_obj_t *textarea_waiting_sec1;
static lv_obj_t *textarea_waiting_min2;
static lv_obj_t *textarea_waiting_sec2;
static lv_obj_t *textarea_waterset1;
static lv_obj_t *textarea_waterset2;
static lv_obj_t *label_time1;
static lv_obj_t *label_min1;
static lv_obj_t *label_sec1;
static lv_obj_t *label_time2;
static lv_obj_t *label_min2;
static lv_obj_t *label_sec2;
static lv_obj_t *label_startinput;
static lv_obj_t *label_unit1;
static lv_obj_t *label_finalget;
static lv_obj_t *label_unit2;
static lv_obj_t *btn_backforward;
static lv_obj_t *label_backforward;

static void event_btn_backforward(lv_event_t *e)
{
    page_callback(page_list, PAGE2_INIT, PAGE1_INIT, LV_SCR_LOAD_ANIM_NONE, true);
}

static void event_btn_start(lv_event_t *e)
{
    prepage = 1;
    page_callback(page_list, PAGE2_INIT, PAGE4_INIT, LV_SCR_LOAD_ANIM_NONE, true);
}

void page2_init(lv_obj_t *root)
{
    // set_this_page(PAGE2);
    sub_windows = lv_obj_create(root);
    lv_obj_set_size(sub_windows, 400, 300);
    lv_obj_align_to(sub_windows, root, LV_ALIGN_CENTER, 0, -20);
    lv_obj_add_style(sub_windows, sub_windows_style(), LV_STATE_DEFAULT);
    // label
    label_mode_name = lv_label_create(root);
    lv_label_set_text(label_mode_name, text_mode_name_1);
    lv_obj_align_to(label_mode_name, root, LV_ALIGN_TOP_MID, 0, 20);

    // btn
    btn_start = lv_btn_create(root);
    lv_obj_set_size(btn_start, 150, 50);
    lv_obj_align_to(btn_start, root, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_style(btn_start, btn_start_style(), LV_STATE_DEFAULT);

    lv_obj_add_event_cb(btn_start, event_btn_start, LV_EVENT_RELEASED, 0);
    // btn_sub_label
    label_sub_btn = lv_label_create(btn_start);
    lv_label_set_text(label_sub_btn, text_start);
    lv_obj_align_to(label_sub_btn, btn_start, LV_ALIGN_CENTER, 0, 0);

    // textarea
    textarea_waiting_min1 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min1, 100, 40);
    lv_obj_align_to(textarea_waiting_min1, sub_windows, LV_ALIGN_CENTER, -50, -100);
    lv_textarea_set_accepted_chars(textarea_waiting_min1, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min1, true);
    lv_textarea_set_max_length(textarea_waiting_min1, 2);
    lv_textarea_set_align(textarea_waiting_min1, LV_TEXT_ALIGN_CENTER);

    textarea_waiting_sec1 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_sec1, 100, 40);
    lv_obj_align_to(textarea_waiting_sec1, sub_windows, LV_ALIGN_CENTER, 90, -100);
    lv_textarea_set_accepted_chars(textarea_waiting_sec1, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_sec1, true);
    lv_textarea_set_max_length(textarea_waiting_sec1, 2);
    lv_textarea_set_align(textarea_waiting_sec1, LV_TEXT_ALIGN_CENTER);

    textarea_waiting_min2 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min2, 100, 40);
    lv_obj_align_to(textarea_waiting_min2, sub_windows, LV_ALIGN_CENTER, -50, -35);
    lv_textarea_set_accepted_chars(textarea_waiting_min2, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min2, true);
    lv_textarea_set_max_length(textarea_waiting_min2, 2);
    lv_textarea_set_align(textarea_waiting_min2, LV_TEXT_ALIGN_CENTER);

    textarea_waiting_sec2 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_sec2, 100, 40);
    lv_obj_align_to(textarea_waiting_sec2, sub_windows, LV_ALIGN_CENTER, 90, -35);
    lv_textarea_set_accepted_chars(textarea_waiting_sec2, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_sec2, true);
    lv_textarea_set_max_length(textarea_waiting_sec2, 2);
    lv_textarea_set_align(textarea_waiting_sec2, LV_TEXT_ALIGN_CENTER);

    textarea_waterset1 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waterset1, 120, 40);
    lv_obj_align_to(textarea_waterset1, sub_windows, LV_ALIGN_CENTER, 20, 30);
    lv_textarea_set_accepted_chars(textarea_waterset1, "0123456789");
    lv_textarea_set_one_line(textarea_waterset1, true);
    lv_textarea_set_max_length(textarea_waterset1, 3);
    lv_textarea_set_align(textarea_waterset1, LV_TEXT_ALIGN_CENTER);

    textarea_waterset2 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waterset2, 120, 40);
    lv_obj_align_to(textarea_waterset2, sub_windows, LV_ALIGN_CENTER, 20, 90);
    lv_textarea_set_accepted_chars(textarea_waterset2, "0123456789");
    lv_textarea_set_one_line(textarea_waterset2, true);
    lv_textarea_set_max_length(textarea_waterset2, 3);
    lv_textarea_set_align(textarea_waterset2, LV_TEXT_ALIGN_CENTER);
    // label
    label_time1 = lv_label_create(sub_windows);
    lv_label_set_text(label_time1, text_time1);
    lv_obj_align_to(label_time1, textarea_waiting_min1, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_min1 = lv_label_create(sub_windows);
    lv_label_set_text(label_min1, text_min);
    lv_obj_align_to(label_min1, textarea_waiting_min1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_sec1 = lv_label_create(sub_windows);
    lv_label_set_text(label_sec1, text_sec);
    lv_obj_align_to(label_sec1, textarea_waiting_sec1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_time2 = lv_label_create(sub_windows);
    lv_label_set_text(label_time2, text_time2);
    lv_obj_align_to(label_time2, textarea_waiting_min2, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_min2 = lv_label_create(sub_windows);
    lv_label_set_text(label_min2, text_min);
    lv_obj_align_to(label_min2, textarea_waiting_min2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_sec2 = lv_label_create(sub_windows);
    lv_label_set_text(label_sec2, text_sec);
    lv_obj_align_to(label_sec2, textarea_waiting_sec2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_startinput = lv_label_create(sub_windows);
    lv_label_set_text(label_startinput, text_startinput);
    lv_obj_align_to(label_startinput, textarea_waterset1, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_unit1 = lv_label_create(sub_windows);
    lv_label_set_text(label_unit1, text_unitwater);
    lv_obj_align_to(label_unit1, textarea_waterset1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_finalget = lv_label_create(sub_windows);
    lv_label_set_text(label_finalget, text_finalget);
    lv_obj_align_to(label_finalget, textarea_waterset2, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_unit2 = lv_label_create(sub_windows);
    lv_label_set_text(label_unit2, text_unitwater);
    lv_obj_align_to(label_unit2, textarea_waterset2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
#if DEBUG
    // image
    lv_obj_t *img_pagebg1 = lv_img_create(main_windows);
    lv_img_set_src(img_pagebg1, &img_pagebackground1);
    lv_img_set_size_mode(img_pagebg1, LV_IMG_SIZE_MODE_REAL);
    lv_img_set_zoom(img_pagebg1, 40);
    lv_obj_update_layout(img_pagebg1);
    lv_obj_align(img_pagebg1, LV_ALIGN_BOTTOM_LEFT, 0, 0);
#endif
    btn_backforward = lv_btn_create(root);
    lv_obj_align_to(btn_backforward, root, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(btn_backforward, btn_start_style(), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_backforward, event_btn_backforward, LV_EVENT_RELEASED, 0);

    label_backforward = lv_label_create(btn_backforward);
    lv_label_set_text(label_backforward, LV_SYMBOL_LEFT);
    lv_obj_align_to(label_backforward, btn_backforward, LV_ALIGN_CENTER, 0, 0);
}

lv_style_t *btn_start_style()
{
    lv_style_reset(&btn_style);
    lv_style_set_bg_color(&btn_style, lv_color_make(0xd5, 0xb1, 0x7b));
    return &btn_style;
}

lv_style_t *sub_windows_style()
{
    lv_style_reset(&all_tmp_style);
    lv_style_set_bg_color(&all_tmp_style, lv_color_hex(0xe7e9e1));
    return &all_tmp_style;
}

lv_style_t *fn_btn_stop_style()
{
    lv_style_reset(&btn_stop_style);
    lv_style_set_bg_color(&btn_stop_style, lv_color_hex(0xb7191b));
    return &btn_stop_style;
}
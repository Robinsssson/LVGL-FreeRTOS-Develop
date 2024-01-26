#include "page3_1.h"

static lv_obj_t* sub_windows;
static lv_obj_t* label_mode_name;
static lv_obj_t* btn_start;
static lv_obj_t* label_sub_btn;
static lv_obj_t* textarea_waiting_min1;
static lv_obj_t* textarea_waiting_min2;
static lv_obj_t* textarea_waiting_min3;
static lv_obj_t* textarea_waiting_min4;
static lv_obj_t* label_medicinal1;
static lv_obj_t* label_medicinal2;
static lv_obj_t* label_medicinal3;
static lv_obj_t* label_medicinal4;
static lv_obj_t* label_add1;
static lv_obj_t* label_add2;
static lv_obj_t* label_add3;
static lv_obj_t* label_add4;
static lv_obj_t* btn_backforward;
static lv_obj_t* label_backforward;

extern linklist page_list;

static lv_style_t btn_style;
static lv_style_t all_tmp_style;

// #define UNFOCUSED_TEST

static void event_textarea_input_number_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
#ifndef UNFOCUSED_TEST
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
#endif
    }

    if (code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static void event_btn_start(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    cJSON** tmp_json = (cJSON**)lv_event_get_user_data(e);
    if (code == LV_EVENT_RELEASED) {
        Page3_1_refresh_cJSON(tmp_json);
        page_callback(page_list, PAGE3_1_INIT, PAGE4_INIT, LV_SCR_LOAD_ANIM_NONE);
    }
}

static void event_btn_backforward(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_RELEASED) {
        page_callback(page_list, PAGE3_1_INIT, PAGE3_INIT, LV_SCR_LOAD_ANIM_NONE);
    }
}
void page3_1_init(lv_obj_t* root, cJSON** message)
{
    static _Bool ok = false;
    if (ok == false) {
        lv_style_init(&btn_style);
        lv_style_init(&all_tmp_style);
        ok = true;
    } else {
        lv_style_reset(&btn_style);
        lv_style_reset(&all_tmp_style);
    }

    

    lv_style_set_bg_color(&btn_style, lv_color_make(0xd5, 0xb1, 0x7b));
    lv_style_set_bg_color(&all_tmp_style, lv_color_hex(0xe7e9e1));
    sub_windows = lv_obj_create(root);
    lv_obj_set_size(sub_windows, 400, 300);
    lv_obj_align_to(sub_windows, root, LV_ALIGN_CENTER, 0, -20);
    lv_obj_add_style(sub_windows, &all_tmp_style, LV_STATE_DEFAULT);

    label_mode_name = lv_label_create(root);
    lv_label_set_text(label_mode_name, "Fry first and then serve mode");
    lv_obj_align_to(label_mode_name, root, LV_ALIGN_TOP_MID, 0, 20);

    btn_start = lv_btn_create(root);
    lv_obj_set_size(btn_start, 150, 50);
    lv_obj_align_to(btn_start, root, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_style(btn_start, &btn_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_start, event_btn_start, LV_EVENT_RELEASED, message);

    label_sub_btn = lv_label_create(btn_start);
    lv_label_set_text(label_sub_btn, "start");
    lv_obj_align_to(label_sub_btn, btn_start, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* keyboard_input = lv_keyboard_create(root);
    lv_keyboard_set_mode(keyboard_input, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_add_flag(keyboard_input, LV_OBJ_FLAG_HIDDEN);

    textarea_waiting_min1 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min1, 80, 40);
    lv_obj_align_to(textarea_waiting_min1, sub_windows, LV_ALIGN_CENTER, 20, -100);
    lv_textarea_set_accepted_chars(textarea_waiting_min1, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min1, true);
    lv_textarea_set_max_length(textarea_waiting_min1, 2);
    lv_textarea_set_align(textarea_waiting_min1, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_event_cb(textarea_waiting_min1, event_textarea_input_number_cb, LV_EVENT_ALL, keyboard_input);

    textarea_waiting_min2 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min2, 80, 40);
    lv_obj_align_to(textarea_waiting_min2, sub_windows, LV_ALIGN_CENTER, 20, -35);
    lv_textarea_set_accepted_chars(textarea_waiting_min2, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min2, true);
    lv_textarea_set_max_length(textarea_waiting_min2, 2);
    lv_textarea_set_align(textarea_waiting_min2, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_event_cb(textarea_waiting_min2, event_textarea_input_number_cb, LV_EVENT_ALL, keyboard_input);

    textarea_waiting_min3 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min3, 80, 40);
    lv_obj_align_to(textarea_waiting_min3, sub_windows, LV_ALIGN_CENTER, 20, 30);
    lv_textarea_set_accepted_chars(textarea_waiting_min3, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min3, true);
    lv_textarea_set_max_length(textarea_waiting_min3, 3);
    lv_textarea_set_align(textarea_waiting_min3, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_event_cb(textarea_waiting_min3, event_textarea_input_number_cb, LV_EVENT_ALL, keyboard_input);

    textarea_waiting_min4 = lv_textarea_create(sub_windows);
    lv_obj_set_size(textarea_waiting_min4, 80, 40);
    lv_obj_align_to(textarea_waiting_min4, sub_windows, LV_ALIGN_CENTER, 20, 90);
    lv_textarea_set_accepted_chars(textarea_waiting_min4, "0123456789");
    lv_textarea_set_one_line(textarea_waiting_min4, true);
    lv_textarea_set_max_length(textarea_waiting_min4, 3);
    lv_textarea_set_align(textarea_waiting_min4, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_event_cb(textarea_waiting_min4, event_textarea_input_number_cb, LV_EVENT_ALL, keyboard_input);

    // label
    label_medicinal1 = lv_label_create(sub_windows);
    lv_label_set_text(label_medicinal1, "medicinal 1");
    lv_obj_align_to(label_medicinal1, textarea_waiting_min1, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_medicinal2 = lv_label_create(sub_windows);
    lv_label_set_text(label_medicinal2, "medicinal 2");
    lv_obj_align_to(label_medicinal2, textarea_waiting_min2, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_medicinal3 = lv_label_create(sub_windows);
    lv_label_set_text(label_medicinal3, "medicinal 3");
    lv_obj_align_to(label_medicinal3, textarea_waiting_min3, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_medicinal4 = lv_label_create(sub_windows);
    lv_label_set_text(label_medicinal4, "medicinal 4");
    lv_obj_align_to(label_medicinal4, textarea_waiting_min4, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    label_add1 = lv_label_create(sub_windows);
    lv_label_set_text(label_add1, "min add");
    lv_obj_align_to(label_add1, textarea_waiting_min1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_add2 = lv_label_create(sub_windows);
    lv_label_set_text(label_add2, "min add");
    lv_obj_align_to(label_add2, textarea_waiting_min2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_add3 = lv_label_create(sub_windows);
    lv_label_set_text(label_add3, "min add");
    lv_obj_align_to(label_add3, textarea_waiting_min3, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    label_add4 = lv_label_create(sub_windows);
    lv_label_set_text(label_add4, "min add");
    lv_obj_align_to(label_add4, textarea_waiting_min4, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    btn_backforward = lv_btn_create(root);
    lv_obj_align_to(btn_backforward, root, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(btn_backforward, &btn_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_backforward, event_btn_backforward, LV_EVENT_RELEASED, message);

    label_backforward = lv_label_create(btn_backforward);
    lv_label_set_text(label_backforward, LV_SYMBOL_LEFT);
    lv_obj_align_to(label_backforward, btn_backforward, LV_ALIGN_CENTER, 0, 0);
}

static void Page3_1_refresh_cJSON(cJSON** cjson)
{
    if (cJSON_GetObjectItem(*cjson, "page3_1")) {
        cJSON_DeleteItemFromObject(*cjson, "page3_1");
    }
    const char* min1 = lv_textarea_get_text(textarea_waiting_min1);
    const char* min2 = lv_textarea_get_text(textarea_waiting_min2);
    const char* min3 = lv_textarea_get_text(textarea_waiting_min3);
    const char* min4 = lv_textarea_get_text(textarea_waiting_min4);

    cJSON* modeName = cJSON_CreateArray();
    cJSON_AddItemToArray(modeName, cJSON_CreateNumber(atoi(min1)));
    cJSON_AddItemToArray(modeName, cJSON_CreateNumber(atoi(min2)));
    cJSON_AddItemToArray(modeName, cJSON_CreateNumber(atoi(min3)));
    cJSON_AddItemToArray(modeName, cJSON_CreateNumber(atoi(min4)));
    cJSON_AddItemToObject(*cjson, "page3_1", modeName);
}
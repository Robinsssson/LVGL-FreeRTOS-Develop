#include "page1.h"
#include "CJSON/cJSON.h"
#include "mem_manage.h"
#include <string.h>

extern linklist page_list;
static lv_obj_t* page1_btn_normal_mode;
static lv_obj_t* page1_btn_fry_mode;
static lv_obj_t* page1_btn_progress_mode;
static lv_obj_t* label;
static lv_obj_t* label1;
static lv_obj_t* label2;
static lv_obj_t* label3;

static lv_style_t style_obj;
static void btn_press_1(lv_event_t* e)
{
    // cJSON* temp_json = (cJSON*)lv_event_get_user_data(e);
    page_callback(page_list, PAGE1_INIT, PAGE2_INIT, LV_SCR_LOAD_ANIM_NONE);
}

static void btn_press_2(lv_event_t* e)
{
    // cJSON* temp_json = (cJSON*)lv_event_get_user_data(e);
    page_callback(page_list, PAGE1_INIT, PAGE3_INIT, LV_SCR_LOAD_ANIM_NONE);
}

void page1_init(lv_obj_t* root, cJSON** message)
{
    PRINT_CJSON("page1", message);
    static _Bool ok = false;
    if (ok == false) {
        lv_style_init(&style_obj);
        ok = true;
    } else {
        lv_style_reset(&style_obj);
    }
    // btn btn1 btn2
    page1_btn_normal_mode = lv_btn_create(root);
    lv_obj_set_size(page1_btn_normal_mode, 242, 68);
    lv_obj_align(page1_btn_normal_mode, LV_ALIGN_CENTER, 0, -120);
    lv_obj_add_event_cb(page1_btn_normal_mode, btn_press_1, LV_EVENT_RELEASED, NULL);

    page1_btn_fry_mode = lv_btn_create(root);
    lv_obj_set_size(page1_btn_fry_mode, 242, 68);
    lv_obj_align(page1_btn_fry_mode, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(page1_btn_fry_mode, btn_press_2, LV_EVENT_RELEASED, NULL);

    page1_btn_progress_mode = lv_btn_create(root);
    lv_obj_set_size(page1_btn_progress_mode, 242, 68);
    lv_obj_align(page1_btn_progress_mode, LV_ALIGN_CENTER, 0, 120);

    // “普通模式”标签
    label = lv_label_create(page1_btn_normal_mode);
    lv_label_set_text(label, "Normal mode");
    lv_obj_align_to(label, page1_btn_normal_mode, LV_ALIGN_CENTER, 0, 0);

    // “先煎后下模式”标签
    label1 = lv_label_create(page1_btn_fry_mode);
    lv_label_set_text(label1, "Fry first and then serve");
    lv_obj_align_to(label1, page1_btn_fry_mode, LV_ALIGN_CENTER, 0, 0);

    // “进度”标签
    label2 = lv_label_create(page1_btn_progress_mode);
    lv_label_set_text(label2, "Setting");
    lv_obj_align_to(label2, page1_btn_progress_mode, LV_ALIGN_CENTER, 0, 0);

    // “模式选择”标签
    label3 = lv_label_create(root);
    lv_label_set_text(label3, "Change Mode");
    lv_obj_align(label3, LV_ALIGN_TOP_MID, 0, 20);

    lv_style_set_bg_color(&style_obj, lv_color_hex(0xD4B27D));
    lv_obj_add_style(page1_btn_normal_mode, &style_obj, 0);
    lv_obj_add_style(page1_btn_fry_mode, &style_obj, 0);
    lv_obj_add_style(page1_btn_progress_mode, &style_obj, 0);
}

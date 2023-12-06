#include "page0.h"
extern linklist page_list;

static uint8_t val = 0;
static lv_style_t style_bg;
static lv_style_t style_indic;
static lv_obj_t *label_load;
static lv_obj_t *label_per;
static lv_obj_t *page0_bar;
// static lv_obj_t *next_btn;

static void event_bar(lv_event_t *e)
{
    uint8_t code = lv_bar_get_value(page0_bar);
    if (code == 100)
        page_callback(page_list, PAGE0_INIT, PAGE1_INIT, LV_SCR_LOAD_ANIM_NONE, true);
}

static void timer_cb(lv_timer_t *timer)
{

    if (val < 100)
    {
        val++;
        lv_bar_set_value(page0_bar, val, LV_ANIM_ON);
        lv_label_set_text_fmt(label_per, "%d %%", lv_bar_get_value(page0_bar));
    }
    else
    {
        lv_timer_del(timer);
        lv_label_set_text(label_per, "finished");
        lv_label_set_text(label_load, "press it!");
    }
}

void page0_init(lv_obj_t *root)
{

    // set_this_page(PAGE0);
    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_color_make(0xd5, 0xb1, 0x7b));
    lv_style_set_border_width(&style_bg, 5);
    lv_style_set_pad_all(&style_bg, 12); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_radius(&style_bg, 50);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_color_make(0xd5, 0xb1, 0x7b));
    lv_style_set_radius(&style_indic, 50);

    label_load = lv_label_create(root);
    lv_label_set_text(label_load, "LOADING...");
    lv_obj_align(label_load, LV_ALIGN_CENTER, 0, 100);

    label_per = lv_label_create(root);
    lv_label_set_text(label_per, " 0 %%");
    lv_obj_align(label_per, LV_ALIGN_CENTER, 200, 0);

    page0_bar = lv_bar_create(root);
    lv_bar_set_range(page0_bar, 1, 100);
    lv_obj_set_style_anim_time(page0_bar, 1000, LV_STATE_DEFAULT);
    // lv_bar_set_value(bar, 100, LV_ANIM_ON);
    lv_obj_remove_style_all(page0_bar); /*To have a clean start*/
    lv_obj_add_style(page0_bar, &style_bg, 0);
    lv_obj_add_style(page0_bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(page0_bar, 300, 82);
    lv_obj_set_align(page0_bar, LV_ALIGN_CENTER);

    lv_timer_create(timer_cb, 20, NULL);
    lv_obj_add_event_cb(page0_bar, event_bar, LV_EVENT_PRESSED, NULL);
}

#include "page_main.h"
linklist page_list;
PageStruct_t page_0 = {
    .init_handler = page0_init,
    .page_id      = PAGE0_INIT,
    .root         = NULL,
};
PageStruct_t page_1 = {
    .init_handler = page1_init,
    .page_id      = PAGE1_INIT,
    .root         = NULL,
};
PageStruct_t page_2 = {
    .init_handler = page2_init,
    .page_id      = PAGE2_INIT,
    .root         = NULL,
};

PageStruct_t page_3 = {
    .init_handler = page3_init,
    .page_id      = PAGE3_INIT,
    .root         = NULL,
};
PageStruct_t page_3_1 = {
    .init_handler = page3_1_init,
    .page_id      = PAGE3_1_INIT,
    .root         = NULL,
};
PageStruct_t page_4 = {
    .init_handler = page4_init,
    .page_id      = PAGE4_INIT,
    .root         = NULL,
};
// sqqueue* id_queue;
void GUI_Init()
{
    // id_queue = sqqueue_create(2);
    page_list = list_create();
    page_add(page_list, &page_0);
    page_add(page_list, &page_1);
    page_add(page_list, &page_2);
    
    page_add(page_list, &page_3);
    page_add(page_list, &page_3_1);
    page_add(page_list, &page_4);
    // page_callback(page_list, PAGE0_INIT, PAGE0_INIT, LV_SCR_LOAD_ANIM_NONE, true);
    page_callback(page_list, PAGE0_INIT, PAGE0_INIT, LV_SCR_LOAD_ANIM_NONE, true);
    // page_callback(page_list, PAGE0_INIT, PAGE1_INIT, LV_SCR_LOAD_ANIM_NONE, true);
    // page_callback(page_list, PAGE1_INIT, PAGE2_INIT, LV_SCR_LOAD_ANIM_NONE, true);
    // page_callback(page_list, PAGE2_INIT, PAGE4_INIT, LV_SCR_LOAD_ANIM_NONE, true);
    // page_callback(page_list, PAGE1_INIT, PAGE2_INIT, LV_SCR_LOAD_ANIM_NONE, true);

}

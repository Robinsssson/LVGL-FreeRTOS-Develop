#include "page_main.h"
#include "linklist.h"
#include "mem_manage.h"
#include <stdlib.h>
linklist page_list;

#define page_i_init(i)                       \
    page_##i->init_handler = page##i##_init; \
    page_##i->page_id = PAGE##i##_INIT;      \
    page_##i->root = NULL;                   \
    page_##i->message = NULL;
void GUI_Init()
{
    PageStruct_t* page_0 = malloc(sizeof(PageStruct_t));
    PageStruct_t* page_1 = malloc(sizeof(PageStruct_t));
    PageStruct_t* page_2 = malloc(sizeof(PageStruct_t));
    PageStruct_t* page_3 = malloc(sizeof(PageStruct_t));
    PageStruct_t* page_3_1 = malloc(sizeof(PageStruct_t));
    PageStruct_t* page_4 = malloc(sizeof(PageStruct_t));
    page_i_init(0);
    page_i_init(1);
    page_i_init(2);
    page_i_init(3);
    page_i_init(4);
    page_3_1->init_handler = page3_1_init;
    page_3_1->page_id = PAGE3_1_INIT;
    page_3_1->root = NULL;
    page_3_1->message = NULL;
    page_list = list_create();
    // page_add(page_list, &page_0);
    // page_add(page_list, &page_1);
    // page_add(page_list, &page_2);

    // page_add(page_list, &page_3);
    // page_add(page_list, &page_3_1);
    // page_add(page_list, &page_4);

    page_add(page_list, page_0);
    page_add(page_list, page_1);
    page_add(page_list, page_2);

    page_add(page_list, page_3);
    page_add(page_list, page_3_1);
    page_add(page_list, page_4);
    // page_callback(page_list, PAGE0_INIT, PAGE0_INIT, LV_SCR_LOAD_ANIM_NONE);
    page_create(page_list, PAGE0_INIT, NULL);
    page_0->init_handler(page_0->root, &page_0->message);
    lv_scr_load_anim(page_0->root, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
}

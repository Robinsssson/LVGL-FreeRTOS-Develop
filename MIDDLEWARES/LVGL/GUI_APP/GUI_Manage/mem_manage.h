#ifndef __MEM_MANAGE__H__
#define __MEM_MANAGE__H__

#include "lvgl.h"
#include "linklist.h"
// #include "sqqueue.h"
typedef enum {
    PAGE_NULL = -1,
    PAGE0_INIT,
    PAGE1_INIT,
    PAGE2_INIT,
    PAGE3_INIT,
    PAGE3_1_INIT,
    PAGE4_INIT,
} PAGE_ID;

void page_add(linklist H, PageStruct_t *page);
linklist page_find(linklist H, uint8_t id);
// int page_delete(linklist H, uint8_t id);
PageStruct_t *page_create(linklist H, uint8_t id);
bool page_callback(linklist H, PAGE_ID local_id, PAGE_ID next_id, lv_scr_load_anim_t animation, bool del);


#endif //!__MEM_MANAGE__H__
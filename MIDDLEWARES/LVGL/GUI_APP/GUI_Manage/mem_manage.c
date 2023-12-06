#include "mem_manage.h"
#include <stdlib.h>
#define DEMO_PANEL_WIDTH  800
#define DEMO_PANEL_HEIGHT 480
// uint8_t page_cur;

linklist page_find(linklist H, uint8_t id)
{
    if (H == NULL) {
        return H;
    }

    linklist p = H->next;

    while (p != NULL) {
        if (p->data->page_id == id)
            return p;
        p = p->next;
    }
    return NULL;
}

void page_add(linklist H, PageStruct_t *page)
{
    /* 遍历链表看是否page_id是否被加入过 */
    linklist node = page_find(H, page->page_id);
    if (node != NULL) {
        return;
    }
    list_push_back(H, page);
}

PageStruct_t *page_create(linklist H, uint8_t id)
{
    PageStruct_t *page = NULL;
    linklist node      = page_find(H, id);
    if (node != NULL) {
        page = node->data;
        if (page->root == NULL)
            page->root = lv_obj_create(NULL);
        /* 每个页面的大小与LCD屏幕大小对应 */
        lv_obj_set_size(page->root, DEMO_PANEL_WIDTH, DEMO_PANEL_HEIGHT);
        page->init_handler(page->root);
    }

    return page;
}

/*
 * @param:arg 页面ID
 * @param:del 页面内存释放标志
 */
// extern sqqueue *id_queue;
bool page_callback(linklist H, PAGE_ID local_id, PAGE_ID next_id, lv_scr_load_anim_t animation, bool del)
{

    linklist p_node;
    PageStruct_t *page_next, *page_local;
    lv_obj_t *act_scr = lv_scr_act();
    lv_disp_t *d      = lv_obj_get_disp(act_scr);
    // uint8_t free_id   = 255;

    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
        p_node     = page_find(H, local_id);
        page_local = p_node->data;
        // if (sqqueue_full(id_queue))
        //     free_id = sqqueue_pop(id_queue);
        // sqqueue_push(id_queue, local_id);
        // if (free_id != 255) {
        //     p_node    = page_find(H, free_id);
        //     page_free = p_node->data;
        //     if (del) {
        //         lv_obj_clean(page_free->root);
        //         page_free->root = NULL;
        //     }
        // }
        if (del /* && local_id != next_id */) {
            lv_obj_clean(act_scr);
            page_local->root = NULL;
        }
        /* 根据待切换屏幕的page_id找到其结构体 */
        p_node = page_find(H, next_id);
        if (p_node == NULL)
            return false;

        page_next = p_node->data;
        /* 如果屏幕中的组件被删除了,重新创建 */
        if (page_next->root == NULL) {
            page_create(H, next_id);
            if (page_next->root == NULL)
                return true;
        } else {
            page_next->init_handler(page_next->root);
        }
        /* 加载新页面:这里固定了animation的时间 */
        lv_scr_load_anim(page_next->root, animation, 0, 0, true);
        return true;
    }
    return false;
}

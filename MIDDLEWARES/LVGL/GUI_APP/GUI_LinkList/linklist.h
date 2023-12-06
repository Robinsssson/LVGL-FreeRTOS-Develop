#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "lvgl.h"
typedef void (*page_init_handle)(lv_obj_t *);
void page_init_handle_null(lv_obj_t *root);
typedef struct
{
    uint8_t page_id;
    lv_obj_t *root;
    page_init_handle init_handler; // 页面中所有组件的初始化函数,以root为父对象
    
} PageStruct_t;

typedef PageStruct_t *data_t;
typedef struct node {
    data_t data;
    struct node *next;
} listnode, *linklist;

linklist list_create();
int list_push_back(linklist H, data_t value); // head node.
linklist list_createfrom_array(data_t *array, int len);
int list_insert(linklist H, data_t value, int pos);
linklist list_get(linklist H, int pos);
linklist list_find(linklist H, data_t value);
int list_delete(linklist H, int pos);
int list_show(linklist H);
int list_reverse(linklist H);
int list_merge(linklist H1, linklist H2);
linklist list_free(linklist H);
#endif

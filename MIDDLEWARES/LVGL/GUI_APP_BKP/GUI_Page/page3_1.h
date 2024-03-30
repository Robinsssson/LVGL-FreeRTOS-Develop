#ifndef __PAGE3_1__H__
#define __PAGE3_1__H__

#include "gui_manage.h"
#include "lvgl.h"
#include "mem_manage.h"

void page3_1_init(lv_obj_t* root, cJSON** message);
static void Page3_1_refresh_cJSON(cJSON** cjson);
#endif //!__PAGE3__H__
#ifndef __PAGE3__H__
#define __PAGE3__H__

#include "gui_manage.h"
#include "lvgl.h"
#include "mem_manage.h"

void page3_init(lv_obj_t* root, cJSON** message);
static void Page3_refresh_cJSON(cJSON**);
#endif //!__PAGE3__H__
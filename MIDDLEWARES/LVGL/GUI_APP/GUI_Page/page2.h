#ifndef __PAGE2__H__
#define __PAGE2__H__

#include "gui_manage.h"
#include "lvgl.h"
#include "mem_manage.h"

void page2_init(lv_obj_t* root, cJSON** message);

static void Page2_refresh_cJSON(cJSON**);
#endif //!__PAGE2__H__
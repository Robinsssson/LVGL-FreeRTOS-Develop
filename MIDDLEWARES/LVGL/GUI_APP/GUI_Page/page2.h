#ifndef __PAGE2__H__
#define __PAGE2__H__

#include "lvgl.h"
#include "gui_manage.h"
#include "mem_manage.h"

void page2_init(lv_obj_t *root);


// style
lv_style_t * btn_start_style(void);
lv_style_t * sub_windows_style(void);
lv_style_t *fn_btn_stop_style(void);

#endif  //!__PAGE2__H__
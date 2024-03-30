#include "page_setting.h"
#include "src/core/lv_obj_pos.h"
#include "src/extra/widgets/list/lv_list.h"
#include "src/misc/lv_area.h"

void page_setting_init(lv_obj_t* root, cJSON** message)
{
    PRINT_CJSON("page_setting", message);
    lv_obj_t* setting_list = lv_list_create(root);
    lv_obj_set_align(setting_list, LV_ALIGN_CENTER);
    lv_obj_set_size(setting_list, 300, 600);
    lv_list_add_text(setting_list,"Settings");   
    lv_obj_t *wifi_btn = lv_list_add_btn(setting_list,LV_SYMBOL_WIFI,"WLAN");

}
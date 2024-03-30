#include "page_setting.h"
#include "src/core/lv_obj_pos.h"
#include "src/extra/widgets/list/lv_list.h"
#include "src/misc/lv_area.h"
#include "esp8266_usart.h"
#include <stdint.h>
int wifi_connected_flag = 0;
static void btn_press_1(lv_event_t* e){
    Usart3_SendATCmd("AT\r\n", 200);
    char str[2000];
    Usart3_ReadBuffer((uint8_t *)str, 100);
    printf("%s\r\n", str);
}
void page_setting_init(lv_obj_t* root, cJSON** message)
{
    PRINT_CJSON("page_setting", message);
    lv_obj_t* setting_list = lv_list_create(root);
    lv_obj_set_align(setting_list, LV_ALIGN_CENTER);
    lv_obj_set_size(setting_list, 600, 300);
    lv_list_add_text(setting_list,"Settings");   
    lv_obj_t *wifi_btn = lv_list_add_btn(setting_list,LV_SYMBOL_WIFI,"WLAN");
    lv_obj_add_event_cb(wifi_btn, btn_press_1, LV_EVENT_RELEASED, NULL);
}
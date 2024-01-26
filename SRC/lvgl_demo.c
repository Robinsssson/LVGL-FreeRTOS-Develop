#include "lvgl_demo.h"
#include "FreeRTOS.h"
#include "all_gui.h"
#include "led.h"
#include "lvgl\examples\porting\lv_port_disp_template.h"
#include "lvgl\examples\porting\lv_port_indev_template.h"
#include "lvgl\lvgl.h"
#include "task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 128
TaskHandle_t StartTask_Handler;
void start_task(void* pvParameters);

#define LV_DEMO_TASK_PRIO 2
#define LV_DEMO_STK_SIZE 128
TaskHandle_t LV_DEMOTask_Handler;
void lv_demo_task(void* pvParameters);

#define LED_TASK_PRIO 3
#define LED_STK_SIZE 128
TaskHandle_t LEDTask_Handler;
void led_task(void* pvParameters);

void lvgl_demo()
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    xTaskCreate((TaskFunction_t)start_task, (const char*)"start_task",
        (uint16_t)START_STK_SIZE, (void*)NULL,
        (UBaseType_t)START_TASK_PRIO, (TaskHandle_t*)&StartTask_Handler);
    vTaskStartScheduler();
}

void start_task(void* pvParameters)
{
    pvParameters = pvParameters;
    taskENTER_CRITICAL(); // 进入临界区

    xTaskCreate((TaskFunction_t)lv_demo_task, (const char*)"lv_demo_task",
        (uint16_t)LV_DEMO_STK_SIZE, (void*)NULL,
        (UBaseType_t)LV_DEMO_TASK_PRIO,
        (TaskHandle_t*)&LV_DEMOTask_Handler);
    xTaskCreate((TaskFunction_t)led_task, (const char*)"led_task",
        (uint16_t)LED_STK_SIZE, (void*)NULL, (UBaseType_t)LED_TASK_PRIO,
        (TaskHandle_t*)&LEDTask_Handler);

    vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();
}
// queue
void lv_demo_task(void* pvParameters)
{
    pvParameters = pvParameters;
    All_Gui();
    while (1) {
        lv_timer_handler();
        vTaskDelay(5);
    }
}
void led_task(void* pvParameters)
{
    pvParameters = pvParameters;
    LED_Init();
    while (1) {
        LED0 = 1;
        vTaskDelay(500);
        LED0 = 0;
        vTaskDelay(500);
    }
}
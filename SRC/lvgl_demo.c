#include "lvgl_demo.h"
#include "FreeRTOS.h"
#include "all_gui.h"
#include "led.h"
#include "lvgl\examples\porting\lv_port_disp_template.h"
#include "lvgl\examples\porting\lv_port_indev_template.h"

#include "task.h"
#include <stdio.h>
#include "delay.h"
#include "semphr.h"
#include "portable.h"
#include "cJSON.h"


#define START_TASK_PRIO 1
#define START_STK_SIZE  128
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define LV_DEMO_TASK_PRIO 4
#define LV_DEMO_STK_SIZE  128
TaskHandle_t LV_DEMOTask_Handler;
void lv_demo_task(void *pvParameters);

#define LED_TASK_PRIO 2
#define LED_STK_SIZE  128
TaskHandle_t LEDTask_Handler;
void led_task(void *pvParameters);

#define USART_TASK_PRIO     3
#define USART_TASK_STK_SIZE 128
TaskHandle_t UsartTask_Handler;
void usart_task(void *pvParameters);


void lvgl_demo()
{
    cJSON_Hooks cJSONhooks_freeRTOS;
    cJSONhooks_freeRTOS.malloc_fn = pvPortMalloc;
    cJSONhooks_freeRTOS.free_fn   = vPortFree;
    cJSON_InitHooks(&cJSONhooks_freeRTOS);
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    printf("lvgl init\r\n");
    xTaskCreate((TaskFunction_t)start_task, (const char *)"start_task",
                (uint16_t)START_STK_SIZE, (void *)NULL,
                (UBaseType_t)START_TASK_PRIO, (TaskHandle_t *)&StartTask_Handler);
    vTaskStartScheduler();
}
SemaphoreHandle_t mutex;
void start_task(void *pvParameters)
{
    pvParameters = pvParameters;
    taskENTER_CRITICAL(); // 进入临界区

    printf("enter start\r\n");
    xTaskCreate((TaskFunction_t)lv_demo_task, (const char *)"lv_demo_task",
                (uint16_t)LV_DEMO_STK_SIZE, (void *)NULL,
                (UBaseType_t)LV_DEMO_TASK_PRIO,
                (TaskHandle_t *)&LV_DEMOTask_Handler);

    xTaskCreate((TaskFunction_t)led_task, (const char *)"led_task",
                (uint16_t)LED_STK_SIZE, (void *)NULL, 
                (UBaseType_t)LED_TASK_PRIO,
                (TaskHandle_t *)&LEDTask_Handler);

    xTaskCreate((TaskFunction_t)usart_task, (const char *)"usart_task",
                (uint16_t)USART_TASK_STK_SIZE, (void *)NULL, 
                (UBaseType_t)USART_TASK_PRIO,
                (TaskHandle_t *)&UsartTask_Handler);
    taskEXIT_CRITICAL();    
    vTaskDelete(StartTask_Handler);
}
// queue

void lv_demo_task(void *pvParameters)
{
    pvParameters = pvParameters;
    mutex = xSemaphoreCreateMutex();
    xSemaphoreTake(mutex, portMAX_DELAY);
    All_Gui();
    xSemaphoreGive(mutex);
    while (1) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        lv_timer_handler();
        xSemaphoreGive(mutex);
        delay_ms(5);
    }
}
void led_task(void *pvParameters)
{
    pvParameters = pvParameters;
    LED_Init();
    while (1) {
        LED0 = 1;
        delay_ms(500);
        LED0 = 0;
        delay_ms(500);
    }
}
// extern int USART3_RxFlag;
void usart_task(void *pvParameters)
{
    pvParameters = pvParameters;
    printf("enter usart1 thread\r\n");
    while (1) {
        // delay_ms(1);
    }
}
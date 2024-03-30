#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "touch.h" 
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "esp8266_usart.h"
#include "lvgl_demo.h"
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);  //初始化延时函数
	uart_init(9600);		//初始化串口波特率为115200  
	Usart3_Config(115200);
	
	printf("usart1 init!\r\n");
	lvgl_demo();
	while (1)
	{
	}
}

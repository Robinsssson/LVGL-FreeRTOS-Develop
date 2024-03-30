#ifndef __ESP8266_USART__H__
#define __ESP8266_USART__H__
// #include "main.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include <stdint.h>

#define PC0(bit) GPIO_WriteBit(GPIOC, GPIO_Pin_0, bit)
#define PF6(bit) GPIO_WriteBit(GPIOF, GPIO_Pin_6, bit)

#define GBC_TX PB10
#define GBC_RX PB11
#define GBC_KEY(bit) PF6(bit)
#define GBC_LED(bit) PC0(bit)

#define RST(bit) GBC_KEY(bit)
#define IO(bit) GBC_LED(bit)

int Usart3_Config(int bound_rate);
int Usart3_ReadBuffer(uint8_t* str, int delay_ms);
int Usart3_SendATCmd(const char* str,int ms, ...);
void Usart3_SendString(const char* str, ...);
#define DEBUG_MODE_USART3
#ifdef DEBUG_MODE_USART3


#endif

#endif //!__ESP8266_USART__H__
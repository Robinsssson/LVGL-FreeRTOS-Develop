#ifndef __USART_INLINE__H__
#define __USART_INLINE__H__
#include "stm32f4xx.h"
void Usart_SendString(USART_TypeDef* pUSARTx, char* str);
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t* array, uint16_t num);
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t ch);
#endif //!__USART_INLINE__H__
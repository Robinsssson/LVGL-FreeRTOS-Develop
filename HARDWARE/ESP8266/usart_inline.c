#include "usart_inline.h"

void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);
}

/****************** 发送8位的数组 ************************/
void Usart_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num)
{
    uint8_t i;

    for (i = 0; i < num; i++) {
        /* 发送一个字节数据到USART */
        Usart_SendByte(pUSARTx, array[i]);
        /* 等待发送完成 */
        while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
            ;
    }
}

/*****************  发送字符串 **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do {
        Usart_SendByte(pUSARTx, *(str + k));
        while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
            ;
        k++;
    } while (*(str + k) != '\0');

    /* 等待发送完成 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
        ;
}
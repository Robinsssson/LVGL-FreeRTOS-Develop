#include "esp8266_usart.h"
// #include "main.h"
#include "misc.h"
#include "stdarg.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "usart_inline.h"
#include <stdint.h>
#include <stm32f4xx_usart.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#define USART3_MaxDataNumber 500
uint8_t USART3_ReceiveDataNumber = 0;
uint8_t USART3_ReceiveDataBuffer[USART3_MaxDataNumber];
int USART3_RxFlag = 0;
int Usart3_Config(int bound_rate) // 2 --2
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    USART_InitTypeDef USART_InitStructure;
    USART_DeInit(USART3);
    USART_InitStructure.USART_BaudRate = bound_rate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);
    return 0;
}

int Usart3_ReadBuffer(uint8_t* str, int ms)
{
    USART3_ReceiveDataBuffer[USART3_ReceiveDataNumber] = '\0';
    int __temp = USART3_ReceiveDataNumber;
    delay_ms(ms);
    while(!USART3_RxFlag);
    strcpy((char*)str, (const char*)USART3_ReceiveDataBuffer);
    USART3_RxFlag = 0;
    USART3_ReceiveDataNumber = 0;
    return __temp;
}
void Usart3_SendString(const char* str, ...)
{
    va_list ap;
    char string[1000];
    va_start(ap, str);
    vsprintf(string, str, ap);
    va_end(ap);
    Usart_SendString(USART3, string);
}

int Usart3_SendATCmd(const char* str, int ms, ...)
{
    va_list ap;
    char string[1000];
    va_start(ap, ms);
    vsprintf(string, str, ap);
    va_end(ap);
    Usart_SendString(USART3, string);
    delay_ms(ms);
    if (USART3_ReceiveDataNumber == 0 || USART3_RxFlag == 0)
        return -1;
    if (strstr((char*)USART3_ReceiveDataBuffer, "error") != 0)
        return -2;
    return 0;
}
void USART3_IRQHandler()
{
    uint8_t receive;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        receive = USART_ReceiveData(USART3);
        USART3_ReceiveDataBuffer[USART3_ReceiveDataNumber++] = receive;
        if (receive == '\n')
            USART3_RxFlag = 1;
    }
}
#include "Driver_USART.h"

/**
 * @description: ��ʼ������1
 */
void Driver_USART1_Init(void)
{
    /* 1. ����ʱ�� */
    /* 1.1 ����1�����ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    /* 1.2 GPIOʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. ����GPIO���ŵĹ���ģʽ  PA9=Tx(�������� CNF=10 MODE=11)  PA10=Rx(�������� CNF=01 MODE=00)*/
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_MODE9;

    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE10;

    /* 3. ���ڵĲ������� */
    /* 3.1 ���ò����� 115200 */
    USART1->BRR = 0x271;
    /* 3.2 ����һ���ֵĳ��� 8λ */
    USART1->CR1 &= ~USART_CR1_M;
    /* 3.3 ���ò���ҪУ��λ */
    USART1->CR1 &= ~USART_CR1_PCE;
    /* 3.4 ����ֹͣλ�ĳ��� */
    USART1->CR2 &= ~USART_CR2_STOP;
    /* 3.5 ʹ�ܽ��պͷ��� */
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    /* 3.6 ʹ�ܴ��ڵĸ����ж� */
    USART1->CR1 |= USART_CR1_RXNEIE; /* ���շǿ��ж� */
    USART1->CR1 |= USART_CR1_IDLEIE; /* �����ж� */

    /* 4. ����NVIC */
    /* 4.1 �������ȼ��� */
    NVIC_SetPriorityGrouping(3);
    /* 4.2 �������ȼ� */
    NVIC_SetPriority(USART1_IRQn, 2);
    /* 4.3 ʹ�ܴ���1���ж� */
    NVIC_EnableIRQ(USART1_IRQn);

    /* 4. ʹ�ܴ��� */
    USART1->CR1 |= USART_CR1_UE;
}

/**
 * @description: ����һ���ֽ�
 * @param {uint8_t} byte Ҫ���͵��ֽ�
 */
void Driver_USART1_SendChar(uint8_t byte)
{
    /* 1. �ȴ����ͼĴ���Ϊ�� */
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;

    /* 2. ����д�������ݼĴ��� */
    USART1->DR = byte;
}

/**
 * @description: ����һ���ַ���
 * @param {uint8_t} *str Ҫ���͵��ַ���
 * @param {uint16_t} len �ַ������ֽڵĳ���
 * @return {*}
 */
void Driver_USART1_SendString(uint8_t *str, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(str[i]);
    }
}






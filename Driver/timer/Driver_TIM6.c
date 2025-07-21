#include "Driver_TIM6.h"

extern void lv_tick_inc(uint32_t tick_period);

void Driver_TIM6_Init(void)
{
    /* 1. ����ʱ��6����ʱ�� */
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 72 - 1;

    TIM6->ARR = 1000 - 1;

    TIM6->EGR |= TIM_EGR_UG;
    TIM6->SR &= ~TIM_SR_UIF;

    /* 4. ʹ�ܸ����ж� (�����ʱ������ж�)*/
    TIM6->DIER |= TIM_DIER_UIE;

    /* 5. ����NVIC  3 4 5 6 7*/
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM6_IRQn, 3);
    NVIC_EnableIRQ(TIM6_IRQn);
}

void Driver_TIM6_Start(void)
{
    /* ������ʹ�� */
    TIM6->CR1 |= TIM_CR1_CEN;
}

void Driver_TIM6_Stop(void)
{
    /* ������ʧ�� */
    TIM6->CR1 &= ~TIM_CR1_CEN;
}

extern void lv_tick_inc(uint32_t tick_period);

void TIM6_IRQHandler(void)
{
    /* 1. ������жϱ�־λ */
    TIM6->SR &= ~TIM_SR_UIF;

    lv_tick_inc(1);
    lv_timer_handler();
}

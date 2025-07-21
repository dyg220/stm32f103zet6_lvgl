#include "Driver_TIM6.h"

extern void lv_tick_inc(uint32_t tick_period);

void Driver_TIM6_Init(void)
{
    /* 1. 给定时器6开启时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 72 - 1;

    TIM6->ARR = 1000 - 1;

    TIM6->EGR |= TIM_EGR_UG;
    TIM6->SR &= ~TIM_SR_UIF;

    /* 4. 使能更新中断 (溢出的时候产生中断)*/
    TIM6->DIER |= TIM_DIER_UIE;

    /* 5. 配置NVIC  3 4 5 6 7*/
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM6_IRQn, 3);
    NVIC_EnableIRQ(TIM6_IRQn);
}

void Driver_TIM6_Start(void)
{
    /* 计数器使能 */
    TIM6->CR1 |= TIM_CR1_CEN;
}

void Driver_TIM6_Stop(void)
{
    /* 计数器失能 */
    TIM6->CR1 &= ~TIM_CR1_CEN;
}

extern void lv_tick_inc(uint32_t tick_period);

void TIM6_IRQHandler(void)
{
    /* 1. 先清除中断标志位 */
    TIM6->SR &= ~TIM_SR_UIF;

    lv_tick_inc(1);
    lv_timer_handler();
}

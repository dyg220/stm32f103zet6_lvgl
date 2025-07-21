#include "Inf_FT5x16.h"

uint8_t isPressed = 0;
/* 中断服务函数 */
void EXTI1_IRQHandler(void)
{
    EXTI->PR |= EXTI_PR_PR1;

    isPressed = 1;
}

uint8_t Inf_FT5x16_IsPressed(void)
{
    if(isPressed)
    {
        isPressed = 0;
        return 1;
    }
    return 0;
}

void Inf_FT5x16_PinInit(void)
{
    /* 1. 中断引脚初始化 PC1*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    /* 上拉输入 mode=00 cnf=10 odr=1*/
    GPIOC->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1_0);
    GPIOC->CRL |= GPIO_CRL_CNF1_1;
    GPIOC->ODR |= GPIO_ODR_ODR1;

    /* 配置PC1为外部中断模式 0010*/
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI1;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PC;

    /* 4. 配置EXTI */
    /* 4.1. 配置下降沿触发 RTSR TR10=1*/
    EXTI->FTSR |= EXTI_FTSR_TR1;
    /* 4.2 开启 LINE1 */
    EXTI->IMR |= EXTI_IMR_MR1;

    /* 5. 配置 NVIC */
    /* 5.1 配置优先级组 (3-7) 配置3表示4个二进制位全部用于表示抢占优先级*/
    NVIC_SetPriorityGrouping(3);
    /* 5.2 配置优先级 参数1:中断号*/
    NVIC_SetPriority(EXTI1_IRQn, 3);
    /* 5.3 使能Line1 */
    NVIC_EnableIRQ(EXTI1_IRQn);

    /* 2. rst引脚初始化 推挽输出 PC2 mode=11 cnf=00*/
    GPIOC->CRL |= GPIO_CRL_MODE2;
    GPIOC->CRL &= ~GPIO_CRL_CNF2;
}

void Inf_FT5x16_Reset(void)
{
    GPIOC->ODR &= ~GPIO_ODR_ODR2;
    Delay_s(1);
    GPIOC->ODR |= GPIO_ODR_ODR2;
    Delay_s(1);
}

/* 读取寄存器 */
void Inf_FT5x16_ReadReg(uint8_t reg, uint8_t data[], uint8_t len)
{
    Driver_I2C1_Start();
    Driver_I2C1_SendByte(FT5336_ADDR);
    Driver_I2C1_WaitAck();

    Driver_I2C1_SendByte(reg);
    Driver_I2C1_WaitAck();

    Driver_I2C1_Start();
    Driver_I2C1_SendByte(FT5336_ADDR + 1);
    Driver_I2C1_WaitAck();

    for(uint8_t i = 0; i < len; i++)
    {
        data[i] = Driver_I2C1_ReadByte();
        if(i < len - 1)
        {
            Driver_I2C1_Ack();
        }
        else
        {
            Driver_I2C1_NAck();
        }
    }
    Driver_I2C1_Stop();
}

void Inf_FT5x16_Init(void)
{
    /* i2c1 初始化 */
    Driver_I2C1_Init();

    /* 外部中断引脚和rst引脚初始化 */
    Inf_FT5x16_PinInit();

    /* 重置触摸屏 */
    Inf_FT5x16_Reset();
}

void Inf_FT5x16_ReadId(uint8_t *id)
{
    Inf_FT5x16_ReadReg(FT5336_CHIP_ID_REG, id, 1);
}

uint8_t ftRxBuff[5];
void    Inf_FT5x16_ReadXY(uint16_t *x, uint16_t *y)
{
    Inf_FT5x16_ReadReg(FT5336_P1_XH_REG, ftRxBuff, 5);
    // 我们只读取x和y的坐标
    *x = 320 - (((ftRxBuff[0] & 0x3f) << 8) + ftRxBuff[1]); /* x坐标的高2位是触摸状态.  */
    *y = (ftRxBuff[2] << 8) + ftRxBuff[3];
}

#include "Driver_I2C1.h"


#define I2C1_DELAY Delay_us(10)


/**
 * @description: ��ʼ��
 * @return {*}
 */
void Driver_I2C1_Init(void)
{
    /*
        PB10->SCL
        PB11->SDA
            ��©���: �ȿ����������Ҳ��������. ���Ҫ����������.
                    ���������ʱ��,��������һ��1,���ߵĿ���Ȩ�������.

            MODE=11 CNF=01

     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    GPIOB->CRL |= (GPIO_CRL_MODE6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);
    GPIOB->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1);
}

/**
 * @description: ��ʼ�ź�
 * @return {*}
 */
void Driver_I2C1_Start(void)
{
    /* 1. ����sda��scl */
    SDA_HIGH;
    SCL_HIGH;
    /* 2. ��ʱ */
    I2C1_DELAY;
    /* 3. ����sda */
    SDA_LOW;
    /* 4. ��ʱ */
    I2C1_DELAY;
}

/**
 * @description: ֹͣ�ź�
 * @return {*}
 */
void Driver_I2C1_Stop(void)
{
    /* 1. scl ���� sda���� */
    SCL_HIGH;
    SDA_LOW;
    /* 2. ��ʱ */
    I2C1_DELAY;
    /* 3. ����sda */
    SDA_HIGH;
    /* 4.  ��ʱ */
    I2C1_DELAY;
}

/**
 * @description: ���շ�����Ӧ���ź�
 */
void Driver_I2C1_Ack(void)
{
    /* 1. ����sda������scl */
    SDA_HIGH;
    SCL_LOW;
    /* 2. ��ʱ */
    I2C1_DELAY;
    /* 3. sda���� */
    SDA_LOW;
    /* 4. ��ʱ */
    I2C1_DELAY;
    /* 5. scl���� */
    SCL_HIGH;
    /* 6. ��ʱ */
    I2C1_DELAY;
    /* 7. scl���� */
    SCL_LOW;
    /* 8. ��ʱ */
    I2C1_DELAY;
    /* 9. sda ���� */
    SDA_HIGH;
    /* 10. ��ʱ */
    I2C1_DELAY;
}

/**
 * @description: ���շ�������Ӧ���ź�
 */
void Driver_I2C1_NAck(void)
{
    /* 1. ����sda������scl */
    SDA_HIGH;
    SCL_LOW;
    /* 2. ��ʱ */
    I2C1_DELAY;

    /* 3. scl���� */
    SCL_HIGH;

    /* 4. ��ʱ */
    I2C1_DELAY;

    /* 5. scl����*/
    SCL_LOW;

    /* 6. ��ʱ */
    I2C1_DELAY;
}

/**
 * @description: �ȴ����շ�����Ӧ��
 * @return {*} Ӧ����Ӧ��
 */
uint8_t Driver_I2C1_WaitAck(void)
{
    /* 1. ��sda����, sda������Ȩ�����Է�(e2promоƬ) */
    SDA_HIGH;

    /* 2. scl����  */
    SCL_LOW;
    /* 3. ��ʱ */
    I2C1_DELAY;
    /* 4. ����scl */
    SCL_HIGH;
    /* 5. ��ʱ */
    I2C1_DELAY;
    /* 6. ��ȡsda�ĵ�ƽ */
    uint8_t ack = ACK;
    if (READ_SDA)
    {
        ack = NACK;
    }
    /* 7. ����scl */
    SCL_LOW;

    /* 8. ��ʱ */
    I2C1_DELAY;
    return ack;
}

/**
 * @description: ����һ���ֽڵ�����
 * @param {uint8_t} byte Ҫ���͵��ֽ�
 */
void Driver_I2C1_SendByte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        /* 1. sda��scl ���� */
        SDA_LOW;
        SCL_LOW;

        I2C1_DELAY;

        /* 2. ��sdaд���� */
        if (byte & 0x80)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        I2C1_DELAY;

        /* 3. ʱ������ */
        SCL_HIGH;

        I2C1_DELAY;

        /* 4. ʱ������ */
        SCL_LOW;

        I2C1_DELAY;

        /* 5. ����1λ, Ϊ��һ�η�����׼�� */
        byte <<= 1;
    }
}

/**
 * @description: ��һ���ֽڵ�����
 * @param {uint8_t} byte Ҫ���͵��ֽ�
 */
uint8_t Driver_I2C1_ReadByte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        /* 1. ����scl */
        SCL_LOW;
        /* 2. ��ʱ */
        I2C1_DELAY;
        /* 3. ����scl */
        SCL_HIGH;
        /* 4. ��ʱ */
        I2C1_DELAY;
        /* 5. ��ȡsda */
        data <<= 1;
        if (READ_SDA)
        {
            data |= 0x01;
        }
        /* 6. ����scl */
        SCL_LOW;

        /* 7. ��ʱ */
        I2C1_DELAY;
    }

    return data;
}

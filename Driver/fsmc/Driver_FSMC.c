#include "Driver_FSMC.h"

void Driver_FSMC_GPIO_Init(void)
{
    /* 1 ���� A10 PG0 ��ַ�˿ڵ����ģʽ �����������CNF:10 50MHz�ٶ� MODE:11*/
    /* =============MODE=============== */
    GPIOG->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_CNF0_1);
    GPIOG->CRL &= ~GPIO_CRL_CNF0_0;

    /*
        2 ���ݶ˿� �����������
            ��ʵ��Ӧ���У���ʹ�����߱�����Ϊ���ģʽ��FSMC��������Ȼ�ܹ����������ߵķ���ʹ������Ҫʱ��Ϊ�����ߡ�
            �����Զ��л�����FSMC������Ӳ������ģ�����Ҫ�����Ԥ��
            ��ˣ���ʹGPIO����Ϊ�������������FSMC��Ȼ����ʵ�ֶ�ȡ������
    */
    /* =============MODE=============== */
    GPIOD->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);
    GPIOD->CRH |=
        (GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);

    /* =============CNF=============== */
    GPIOD->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 | GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1 |
                   GPIO_CRH_CNF12_1 | GPIO_CRH_CNF13_1 | GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0 |
                    GPIO_CRH_CNF12_0 | GPIO_CRH_CNF13_0 | GPIO_CRH_CNF14_0 | GPIO_CRH_CNF15_0);

    /* 3 �������ƶ˿�  �����������  pd4 pd5*/
    GPIOD->CRL |= (GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    // NE4=>PG12
    GPIOG->CRH |= (GPIO_CRH_MODE12 | GPIO_CRH_CNF12_1);
    GPIOG->CRH &= ~GPIO_CRH_CNF12_0;

    // LCD-RST =>PG15 �������� ͨ������MODE=11 CNF=00
    GPIOG->CRH |= GPIO_CRH_MODE15;
    GPIOG->CRH &= ~GPIO_CRH_CNF15;

    // LCD-BG PB0 ͨ������
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0;
}

void Driver_FSMC_Init(void)
{
    /* 1. ʱ�ӵĳ�ʼ�� */
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN |
                     RCC_APB2ENR_IOPFEN | RCC_APB2ENR_IOPGEN | RCC_APB2ENR_AFIOEN);

    /* 2. �������ŵ�ģʽ�ĳ�ʼ�� */
    Driver_FSMC_GPIO_Init();

    /* 3. ����FSMC  BCR3 Ƭѡ���ƼĴ���*/
    /* 3.1 bank1�Ŀ�4ʹ�� */
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN;
    /* 3.2 ���ô洢������ ����lcd��ʱ����Ȼѡ��sram*/
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MTYP;
    /* 3.3 �洢�����ݿ��  01=16λ */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MWID_1;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;
    /* 3.4 �������ߺ͵�ַ���߲����� 00 */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MUXEN;
    /* 3.5 ��ֹ����Nor Flash */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_FACCEN;
    /* 3.6 дʹ�� */
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;

    /* 4. BTR3 ʱ��Ĵ��� */
    /* 4.1 ��ַ����ʱ��, ��ͬ������, ��Զ��һ������ */
    // FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_ADDSET;
    /* 4.2 ��ַ����ʱ��, ��ͬ������, ��Զ��һ������ */
    // FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_ADDHLD;
    /* 4.3 ���ݵı������� оƬҪ���ܵ���55ns ��������1us 72��ʱ������ */
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_DATAST;
    FSMC_Bank1->BTCR[7] |= 71 << 8;
}


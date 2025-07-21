#include "Inf_LCD.h"


void Inf_LCD_Restart(void)
{
    GPIOG->ODR &= ~GPIO_ODR_ODR15;
    Delay_ms(800);
    GPIOG->ODR |= GPIO_ODR_ODR15;
    Delay_ms(100);
}

void Inf_LCD_OpenBg(void)
{
    GPIOB->ODR |= GPIO_ODR_ODR0;
}

void Inf_LCD_CloseBg(void)
{
    GPIOB->ODR &= ~GPIO_ODR_ODR0;
}

/* д���� */
void Inf_LCD_WriteCmd(uint16_t cmd)
{
    *LCD_CMD_ADDR = cmd;
}

/* д���� */
void Inf_LCD_WriteData(uint16_t data)
{
    *LCD_DATA_ADDR = data;
}

uint16_t Inf_LCD_ReadData(void)
{
    return *LCD_DATA_ADDR;
}

// TODO
/* ��ʼ���Ĵ�����ֵ */
void Inf_LCD_RegConfig(void)
{
    /* 1. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ� ��У׼��һ����������ú��� */
    Inf_LCD_WriteCmd(0xE0);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x07);
    Inf_LCD_WriteData(0x10);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x0B);
    Inf_LCD_WriteData(0x41);
    Inf_LCD_WriteData(0x89);
    Inf_LCD_WriteData(0x4B);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x0C);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x18);
    Inf_LCD_WriteData(0x1B);
    Inf_LCD_WriteData(0x0F);

    /* 2. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ���У׼ */
    Inf_LCD_WriteCmd(0XE1);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x1A);
    Inf_LCD_WriteData(0x04);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x06);
    Inf_LCD_WriteData(0x2F);
    Inf_LCD_WriteData(0x45);
    Inf_LCD_WriteData(0x43);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x32);
    Inf_LCD_WriteData(0x36);
    Inf_LCD_WriteData(0x0F);

    /* 3.  Adjust Control 3 (F7h)  */
    /*LCD_WriteCmd(0XF7);
   Inf_LCD_WriteData(0xA9);
   Inf_LCD_WriteData(0x51);
   Inf_LCD_WriteData(0x2C);
   Inf_LCD_WriteData(0x82);*/
    /* DSI write DCS command, use loose packet RGB 666 */

    /* 4. ��Դ����1*/
    Inf_LCD_WriteCmd(0xC0);
    Inf_LCD_WriteData(0x11); /* ��٤���ѹ */
    Inf_LCD_WriteData(0x09); /* ��٤���ѹ */

    /* 5. ��Դ����2 */
    Inf_LCD_WriteCmd(0xC1);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x03);

    /* 6. VCOM���� */
    Inf_LCD_WriteCmd(0XC5);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Inf_LCD_WriteCmd(0xB1);
    Inf_LCD_WriteData(0xB0);
    Inf_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) ��������ѹ��ת�����ٵ�Ÿ��ţ�*/
    Inf_LCD_WriteCmd(0xB4);
    Inf_LCD_WriteData(0x02);

    /* 9.  Display Function Control (B6h)  */
    Inf_LCD_WriteCmd(0xB6);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0xA2);

    /* 10. Entry Mode Set (B7h)  */
    Inf_LCD_WriteCmd(0xB7);
    Inf_LCD_WriteData(0xc6);

    /* 11. HS Lanes Control (BEh) */
    Inf_LCD_WriteCmd(0xBE);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x04);

    /* 12.  Interface Pixel Format (3Ah) */
    Inf_LCD_WriteCmd(0x3A);
    Inf_LCD_WriteData(0x55); /* 0x55 : 16 bits/pixel  */

    /* 13. Sleep Out (11h) �ر�����ģʽ */
    Inf_LCD_WriteCmd(0x11);

    /* 14. ������Ļ�����RGB */
    Inf_LCD_WriteCmd(0x36);
    Inf_LCD_WriteData(0x08);

    Delay_ms(120);

    /* 14. display on */
    Inf_LCD_WriteCmd(0x29);
}

void Inf_LCD_Init(void)
{
    /* 1. ��ʼ�� FSMC */
    Driver_FSMC_Init();

    /* 2. ����LCD */
    Inf_LCD_Restart();

    /* 3. ����LCD��(��LCD����һЩͨ�ò���) */
    Inf_LCD_RegConfig();

    /* 4. �������� */
    Inf_LCD_OpenBg();
}

/* ��ȡid,����lcd�Ƿ����� */
uint32_t Inf_LCD_ReadId(void)
{
    Inf_LCD_WriteCmd(0x04);
    Inf_LCD_ReadData();   // ��������

    uint32_t id = 0;

    id |= (Inf_LCD_ReadData() & 0xff) << 16;
    id |= (Inf_LCD_ReadData() & 0xff) << 8;
    id |= (Inf_LCD_ReadData() & 0xff) << 0;
    return id;
}


void Inf_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    /* 1. ������ʼ�кͽ����� */
    Inf_LCD_WriteCmd(0x2A);
    /* 1.1 ��ʼ�� */
    Inf_LCD_WriteData(x >> 8);
    Inf_LCD_WriteData(x & 0xff);

    /* 1.2 ������ */
    Inf_LCD_WriteData((x + w - 1) >> 8);
    Inf_LCD_WriteData((x + w - 1) & 0xff);

    /* 2. ������ʼ�кͽ����� */
    Inf_LCD_WriteCmd(0x2B);
    /* 1.1 ��ʼ�� */
    Inf_LCD_WriteData(y >> 8);
    Inf_LCD_WriteData(y & 0xff);

    /* 1.2 ������ */
    Inf_LCD_WriteData((y + h - 1) >> 8);
    Inf_LCD_WriteData((y + h - 1) & 0xff);
}

void Inf_LCD_FillColor(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *color)
{
    Inf_LCD_SetArea(x, y, w, h);
    

    Inf_LCD_WriteCmd(0x2C);

    for(uint32_t i = 0, count = w * h; i < count; i++)
    {
        Inf_LCD_WriteData(color[i]);
    }
}



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

/* 写命令 */
void Inf_LCD_WriteCmd(uint16_t cmd)
{
    *LCD_CMD_ADDR = cmd;
}

/* 写数据 */
void Inf_LCD_WriteData(uint16_t data)
{
    *LCD_DATA_ADDR = data;
}

uint16_t Inf_LCD_ReadData(void)
{
    return *LCD_DATA_ADDR;
}

// TODO
/* 初始化寄存器的值 */
void Inf_LCD_RegConfig(void)
{
    /* 1. 设置灰阶电压以调整TFT面板的伽马特性， 正校准。一般出厂就设置好了 */
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

    /* 2. 设置灰阶电压以调整TFT面板的伽马特性，负校准 */
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

    /* 4. 电源控制1*/
    Inf_LCD_WriteCmd(0xC0);
    Inf_LCD_WriteData(0x11); /* 正伽马电压 */
    Inf_LCD_WriteData(0x09); /* 负伽马电压 */

    /* 5. 电源控制2 */
    Inf_LCD_WriteCmd(0xC1);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x03);

    /* 6. VCOM控制 */
    Inf_LCD_WriteCmd(0XC5);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Inf_LCD_WriteCmd(0xB1);
    Inf_LCD_WriteData(0xB0);
    Inf_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) （正负电压反转，减少电磁干扰）*/
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

    /* 13. Sleep Out (11h) 关闭休眠模式 */
    Inf_LCD_WriteCmd(0x11);

    /* 14. 设置屏幕方向和RGB */
    Inf_LCD_WriteCmd(0x36);
    Inf_LCD_WriteData(0x08);

    Delay_ms(120);

    /* 14. display on */
    Inf_LCD_WriteCmd(0x29);
}

void Inf_LCD_Init(void)
{
    /* 1. 初始化 FSMC */
    Driver_FSMC_Init();

    /* 2. 重启LCD */
    Inf_LCD_Restart();

    /* 3. 设置LCD的(给LCD设置一些通用参数) */
    Inf_LCD_RegConfig();

    /* 4. 开启背光 */
    Inf_LCD_OpenBg();
}

/* 读取id,测试lcd是否正常 */
uint32_t Inf_LCD_ReadId(void)
{
    Inf_LCD_WriteCmd(0x04);
    Inf_LCD_ReadData();   // 垃圾数据

    uint32_t id = 0;

    id |= (Inf_LCD_ReadData() & 0xff) << 16;
    id |= (Inf_LCD_ReadData() & 0xff) << 8;
    id |= (Inf_LCD_ReadData() & 0xff) << 0;
    return id;
}


void Inf_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    /* 1. 设置起始列和结束列 */
    Inf_LCD_WriteCmd(0x2A);
    /* 1.1 起始列 */
    Inf_LCD_WriteData(x >> 8);
    Inf_LCD_WriteData(x & 0xff);

    /* 1.2 结束列 */
    Inf_LCD_WriteData((x + w - 1) >> 8);
    Inf_LCD_WriteData((x + w - 1) & 0xff);

    /* 2. 设置起始行和结束行 */
    Inf_LCD_WriteCmd(0x2B);
    /* 1.1 起始行 */
    Inf_LCD_WriteData(y >> 8);
    Inf_LCD_WriteData(y & 0xff);

    /* 1.2 结束行 */
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



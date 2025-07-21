#ifndef __INF_LCD_H
#define __INF_LCD_H

#include "Delay.h"
#include "Driver_FSMC.h"

#define LCD_BASE_ADDR 0X6C000000
#define LCD_CMD_ADDR (uint16_t *)LCD_BASE_ADDR
#define LCD_DATA_ADDR (uint16_t *)(LCD_BASE_ADDR + (1 << 11))


void     Inf_LCD_Init(void);
uint32_t Inf_LCD_ReadId(void);

void Inf_LCD_FillColor(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *color);

#endif

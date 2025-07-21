#ifndef __INF_FT5X16_H
#define __INF_FT5X16_H

#include "Common_Debug.h"
#include "Driver_I2C1.h"

#define FT5336_ADDR 0x70   // FT5336 IICͨѶ��ַ

// ��������߶���
#define FT5336_MAX_WIDTH ((uint16_t)320)    // �����������
#define FT5336_MAX_HEIGHT ((uint16_t)480)   // ���������߶�

#define FT5336_TOUCH_POS_XY_EXCHANGE 0   // �Ƿ񽫺�������������Ե�

// ��������״̬�Ĵ�������ȡ����Ч����������� (0..5)
#define FT5336_TD_STAT_REG ((u8)0x02)

// ����������Ϣ��ؼĴ���
#define FT5336_ONE_TOUCH_REG_CNT 6   // һ����������6���Ĵ������
// #1��������Ϣ
#define FT5336_P1_XH_REG ((u8)0x03)   // X������Ϣ
#define FT5336_P1_XL_REG ((u8)0x04)
#define FT5336_P1_YH_REG ((u8)0x05)   // Y������Ϣ
#define FT5336_P1_YL_REG ((u8)0x06)
#define FT5336_P1_WEIGHT_REG ((u8)0x07)   // ������ѹ��
#define FT5336_P1_MISC_REG ((u8)0x08)     // ��������
// #2��������Ϣ
#define FT5336_P2_XH_REG ((u8)0x09)
#define FT5336_P2_XL_REG ((u8)0x0A)
#define FT5336_P2_YH_REG ((u8)0x0B)
#define FT5336_P2_YL_REG ((u8)0x0C)
#define FT5336_P2_WEIGHT_REG ((u8)0x0D)
#define FT5336_P2_MISC_REG ((u8)0x0E)
// #3��������Ϣ
#define FT5336_P3_XH_REG ((u8)0x0F)
#define FT5336_P3_XL_REG ((u8)0x10)
#define FT5336_P3_YH_REG ((u8)0x11)
#define FT5336_P3_YL_REG ((u8)0x12)
#define FT5336_P3_WEIGHT_REG ((u8)0x13)
#define FT5336_P3_MISC_REG ((u8)0x14)
// #4��������Ϣ
#define FT5336_P4_XH_REG ((u8)0x15)
#define FT5336_P4_XL_REG ((u8)0x16)
#define FT5336_P4_YH_REG ((u8)0x17)
#define FT5336_P4_YL_REG ((u8)0x18)
#define FT5336_P4_WEIGHT_REG ((u8)0x19)
#define FT5336_P4_MISC_REG ((u8)0x1A)
// #5��������Ϣ
#define FT5336_P5_XH_REG ((u8)0x1B)
#define FT5336_P5_XL_REG ((u8)0x1C)
#define FT5336_P5_YH_REG ((u8)0x1D)
#define FT5336_P5_YL_REG ((u8)0x1E)
#define FT5336_P5_WEIGHT_REG ((u8)0x1F)
#define FT5336_P5_MISC_REG ((u8)0x20)


// FT5336 оƬID�Ĵ���
#define FT5336_CHIP_ID_REG ((u8)0xA8)

uint8_t Inf_FT5x16_IsPressed(void);

void Inf_FT5x16_Init(void);
void Inf_FT5x16_ReadId(uint8_t *id);
void Inf_FT5x16_ReadXY(uint16_t *x, uint16_t *y);
#endif

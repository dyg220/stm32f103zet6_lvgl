#ifndef __DRIVER_I2C1_H
#define __DRIVER_I2C1_H

#include "Delay.h"
#include "stm32f10x.h"
#include "Driver_USART.h"

#define ACK 0
#define NACK 1

#define SCL_HIGH  (GPIOB->ODR |= GPIO_ODR_ODR6)
#define SCL_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR6)

#define SDA_HIGH  (GPIOB->ODR |= GPIO_ODR_ODR7)
#define SDA_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR7)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR7)


void Driver_I2C1_Init(void);

void Driver_I2C1_Start(void);

void Driver_I2C1_Stop(void);

void Driver_I2C1_Ack(void);

void Driver_I2C1_NAck(void);

uint8_t Driver_I2C1_WaitAck(void);

void Driver_I2C1_SendByte(uint8_t byte);

uint8_t Driver_I2C1_ReadByte(void);

#endif


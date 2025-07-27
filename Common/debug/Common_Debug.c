#include "Common_Debug.h"

/**
 * @description: ����debugģ��
 * @return {*}
 */
void Common_Debug_Start(void)
{
    Driver_USART1_Init();


}

int fputc(int c, FILE *file)
{
    Driver_USART1_SendChar((uint8_t)c);
    return c;
}




#include "App_DisplayDemo.h"
#include "Common_Debug.h"

int main()
{
    debug_start();
    debug_printfln("\r\n"
                   "lvgl��Ŀģ��: \r\n"
                   "    1. ��ģ��֧���й��STM32������\r\n"
                   "    2. ��ģ���Ѿ�������LCD����(Inf_LCD.c)\r\n"
                   "    3. ��ģ���Ѿ������˴���������(Inf_FT5x16.c)");

    App_DisplayDemo_Init();

    /* ʵ��1: ����һ����ť */
    App_Display_CreateButton();

    while (1)
    {
    }
}

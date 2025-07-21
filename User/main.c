#include "App_DisplayDemo.h"
#include "Common_Debug.h"

int main()
{
    debug_start();
    debug_printfln("\r\n"
                   "lvgl项目模板: \r\n"
                   "    1. 该模板支持尚硅谷STM32开发板\r\n"
                   "    2. 该模板已经集成了LCD驱动(Inf_LCD.c)\r\n"
                   "    3. 该模板已经集成了触摸屏驱动(Inf_FT5x16.c)");

    App_DisplayDemo_Init();

    /* 实例1: 创建一个按钮 */
    App_Display_CreateButton();

    while (1)
    {
    }
}

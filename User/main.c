#include "App_DisplayDemo.h"
#include "Common_Debug.h"

int main()
{
    debug_start();
    debug_printfln("lvgl test!");

    App_DisplayDemo_Init();

    /* 实例1: 创建一个按钮 */
    App_Display_CreateButton();

    while (1)
    {
    }
}

#ifndef __COMMON_DEBUG_H
#define __COMMON_DEBUG_H

#include "Driver_USART.h"
#include "stdio.h"
#include "string.h"

#define DEBUG 1

#if(DEBUG == 1)
#define debug_start() Common_Debug_Start()

#define __FINE_NAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

// [文件名:行号] -- 具体的日志信息
#define debug_printf(format, ...) printf("[ %20s:%4d ] -- " format, __FINE_NAME__, __LINE__, ##__VA_ARGS__)
#define debug_printfln(format, ...) printf("[ %20s:%4d ] -- " format "\r\n", __FINE_NAME__, __LINE__, ##__VA_ARGS__)

#else

#define debug_start() 
#define debug_printf(format, ...)
#define debug_printfln(format, ...)

#endif

void Common_Debug_Start(void);

#endif

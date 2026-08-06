//==================================================================================================
//
// DA的编译宏，仅在ram中调试时设置
// 仅对DA传递到IO板的三个AO，
// 无论该宏定义是否打开，过流点基准值，总是输出的。
//
//
// Time-stamp: <2012-6-19 15:27:50  author, 0000>
//
//==================================================================================================


#ifndef __M_MACRO_AO_H__
#define __M_MACRO_AO_H__



#include "main.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_DA_AO_UPDATE    1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_DA_AO_UPDATE    0
#endif






#endif  //__M_MACRO_AO_H__



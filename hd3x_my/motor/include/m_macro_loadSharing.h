//==================================================================================================
//
// 调谐的编译宏，仅在ram中调试时设置
//
//
// Time-stamp: <2013-8-22 6:56:26  author, 0000>
//
//==================================================================================================


#ifndef __M_MACRO_LOAD_SHARING_H__
#define __M_MACRO_LOAD_SHARING_H__



#include "main.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_LOAD_SHARING        0   // 负荷分配
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_LOAD_SHARING        0   //
#endif






#endif  //__M_MACRO_LOAD_SHARING_H__



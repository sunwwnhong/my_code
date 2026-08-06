//==================================================================================================
//
// 同步机控制的编译宏，仅在ram中调试时设置
//
//
// Time-stamp: <2012-6-19 15:27:50  author, 0000>
//
//==================================================================================================


#ifndef __M_MACRO_SM_H__
#define __M_MACRO_SM_H__



#include "main.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_SM_CONTROL          0
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_SM_CONTROL          0
#endif






#endif  //__M_MACRO_SM_H__



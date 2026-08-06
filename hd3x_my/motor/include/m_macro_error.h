//==================================================================================================
//
// 调谐的编译宏，仅在ram中调试时设置
//
//
// Time-stamp: <2013-8-22 6:08:22  author, 0000>
//
//==================================================================================================


#ifndef __M_MACRO_ERROR_H__
#define __M_MACRO_ERROR_H__



#include "main.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_OL                  1   // 过载
#define DEBUG_P_OUT_GND             0   // 输出对地阻抗偏小
#define DEBUG_P_OUT_PHASE_LOSS      1   // 输出缺相
#define DEBUG_P_ERR95               0   // err95
#define DEBUG_P_ERR20               1   // err20
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_OL                  0   // 
#define DEBUG_P_OUT_GND             0
#define DEBUG_P_OUT_PHASE_LOSS      0
#define DEBUG_P_ERR95               0
#define DEBUG_P_ERR20               0   // err20
#endif






#endif  //__M_MACRO_ERROR_H__



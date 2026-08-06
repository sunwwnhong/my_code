//==================================================================================================
//
// SVC时的slip计算
//
//
//
// Time-stamp: <2012-2-9 16:38:52  author, 0000>
//
//==================================================================================================


#ifndef __M_SLIP_H__
#define __M_SLIP_H__



#include "main.h"



#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_SVC         1               // 异步机SVC
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_SVC         1
#endif





void SvcSlipFrqCalc(void);




#endif  //__M_SLIP_H__





//==================================================================================================
//
// 低频时，有一些特殊处理，目前仅在提升时使用。
//
//
// Time-stamp: <2012-6-29 10:02:53  author, 0000>
//
//==================================================================================================


#ifndef __M_MACRO_LOW_FRQ_H__
#define __M_MACRO_LOW_FRQ_H__



#include "main.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_LOW_FRQ_DEAL        1   // 低频时的一些特殊处理，目前仅在提升场合使用
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_LOW_FRQ_DEAL        0
#endif






#endif  //__M_MACRO_LOW_FRQ_H__



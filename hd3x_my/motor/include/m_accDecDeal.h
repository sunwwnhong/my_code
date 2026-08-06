//==================================================================================================
//
// 减速过压抑制头文件
// By Caizhun 10915   2013-08-06   9:11:22
//
//==================================================================================================


#ifndef __M_ACCDECDEAL_H__
#define __M_ACCDECDEAL_H__

#include "main.h"
#include "m_main.h"
#include "m_control.h"
#include "m_interface.h"

//=====================================================================
#if (!DEBUG_PRG_IN_RAM)   // 程序放在Flash中
#define DEC_TIME_CELLDC         0       // 减速制动时减速时间处理使能，1-使能，0-不使能
#define CELLVOLPRO              0       // 过压软件保护，1--使能，0--不使能

#elif 1                 // 程序放在RAM中调试
#define DEC_TIME_CELLDC         0 
#define CELLVOLPRO              0       // 过压软件保护，1--使能，0--不使能
#endif
//=====================================================================

//==============================================================================
struct CELLVOL_STR
{
    Uint16 cellGenVolMax;
    Uint16 cellGenVolMin;
    Uint16 cellGenVolA3;
    
    f32 cellGenVolAver;
    f32 cellGenVolAverFil;  // 单位: V
   
};

extern struct CELLVOL_STR cellVolData;
//==============================================================================



#endif  //__M_ACCDECDEAL_H

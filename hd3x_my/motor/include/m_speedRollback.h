//==================================================================================================
//
// 速度RollBack编译宏，头文件
//
//
// 
//   2014-5-16 14:59:17		Zhun Cai
//==================================================================================================


#ifndef __M_SPEEDROLLBACK_H__
#define __M_SPEEDROLLBACK_H__



#include "m_interface.h"




//=====================================================================
#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_SPEED_ROLLBACK             1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_SPEED_ROLLBACK             0
#endif
//=====================================================================

void SpeedRollbackDeal(void);


#endif  //__M_SPEEDROLLBACK_H__



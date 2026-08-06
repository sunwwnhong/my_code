//==================================================================================================
//
// 黑匣子数据dsp处理
//
//
//
// 
//
//==================================================================================================


#ifndef __M_BLACKBOXDEAL_H__
#define __M_BLACKBOXDEAL_H__



#include "m_output.h"



#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中 
#define DEBUG_BLACK_BOX  1 // LS_20221205
#elif 1                 // 程序放在RAM中调试 
#define DEBUG_BLACK_BOX  0
#endif



#define F2C_BLACK_BOX_PARA_LENTH    6       // 黑匣子数据通道数
#define C2F_BLACK_BOX_PARA_MAX      12      // 每2ms最多传递快环数据的个数

void BlackBoxDeal(void);






#endif  //_M_BLACKBOXDEAL_H__





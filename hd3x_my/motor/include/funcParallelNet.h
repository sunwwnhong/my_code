//----------------------------------------------------------//
// File Name		: funcParallelNet.h	
// Description		: 并网控制
// Time				: 2017.03.14
// Editor			: 
// Co.				: xxxxx
//----------------------------------------------------------//

#ifndef __F_FUNC_PARALLEL_NET_H__
#define __F_FUNC_PARALLEL_NET_H__



typedef struct
{
	Uint16 powerVoltToCore;
	Uint16 powerFrqToCore;
}POWER_SOURCE_OUTPUT;

extern POWER_SOURCE_OUTPUT powerSrcOpt;
// ----------------函数声明---------------------------------------------- 
extern void ParallelSpdDeal(void);
extern void ParallelVoltDeal(void);
// ----------------函数声明结束------------------------------------------ 




#endif


#ifndef __F_CELL_CMD_DEAL_H__
#define __F_CELL_CMD_DEAL_H__

// ----------------函数声明----------------------------------------------
extern void CellBypassDeal(Uint16 id);
// ----------------函数声明结束------------------------------------------
#include "funcCellFaultDeal.h"
extern Uint16 cellBypassMode;        // 旁路模式
extern u32 cellBypassEnable;       // ARM<-DSP   允许旁路的单元标记 0-15
extern u32 cellBypassCmdForDsp;
extern Uint16 cellBypassSameLevel;   // 同级旁路
extern Uint16 cellBypassNumLimit, cellBypassNumLimitDisp;
extern bool cellBypassFault[CELL_NUM];
extern u32 finalBypassFdb;
extern u32 cellBypassFdbTmp;
extern u32 cellBypassRes;        // 单元旁路结果，为1表示旁路成功
extern bool bypassFaultFlag;       // 单元旁路有效 1-有若干单元有旁路故障

#endif


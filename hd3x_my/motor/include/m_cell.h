//==================================================================================================
//
// 单元诊断
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_CELL_H__
#define __M_CELL_H__



#include "main.h"





//单元电压，版本
struct CELL_VOLVER_BITS
{
   Uint16 cellver :8;  //
   Uint16 cellvol: 8;

};
union CELL_VOLVER
{
  Uint16 all;
  struct CELL_VOLVER_BITS bit;
};
extern union CELL_VOLVER  cellVolVer;

// 单元状态
struct CELL_STATUS_BITS
{
    Uint16 cellId:6;        // 0-5:ID
    Uint16 cellGenFault:1;  // 6:单元总故障
    Uint16 cellCheckOver:1; // 7:单元自测完成 
    Uint16 temperature:8;   // 8-15 单元温度
};
union CELL_STATUS
{
	Uint16 all;
	struct CELL_STATUS_BITS bit; 
};
extern union CELL_STATUS cellStatus; 

// 单元命令
struct CELL_CHECK_FLAG_BITS
{
    Uint16 cellReset:1;             // 0: 单元复位命令
    Uint16 cellFaultCheckEnable:1;  // 1: 检测单元故障
    Uint16 cellSelfCheckEnable:1;   // 2: 单元自检:block检测允许
    Uint16 cellFirstChkArmOk:1;     // 3: 上电自检，ARM已经完成
    Uint16 cellDischarge:1;			// 4: 单元放电命令
    Uint16 rsvd:11;
};
union CELL_CHECK_FLAG
{
	Uint16 all;
	struct CELL_CHECK_FLAG_BITS bit;
};
extern union CELL_CHECK_FLAG cellCheckFlag,cellCheckFlagOld;

// 单元旁路处理相关
struct CELL_BYPASS_FLAG_BITS
{
    Uint16 bypassCellfaultFlag:1;           // 0: 旁路最小单元数超限
    Uint16 bypassVolTimeFlag:1;             // 1: 旁路最大反电势衰减时间超限
    Uint16 bypassRun:1;                     // 2: 旁路运行有效
    Uint16 cellBypassCmdChangeFlag:1;       // 3: 旁路命令改变标志位

    Uint16 rsvd:12;
};
union CELL_BYPASS_FLAG
{
	Uint16 all;
	struct CELL_BYPASS_FLAG_BITS bit;
};
extern union CELL_BYPASS_FLAG cellBypassFlag;

//void CellInfoDeal(void);// 单元故障整体处理程序 放在2ms定时程序中

#endif // __M_CELL_H__







#ifndef __F_CELL_CHECK_H__
#define __F_CELL_CHECK_H__

extern void CellDiagnoseStatusDeal(void);

// 系统状态
/*
struct CELL_CHECK_FLAG_BITS
{
    Uint16 cellReset:1;             // 0: 单元复位命令
    Uint16 rsvdcmd:1;               // 1: 保留命令 // 单元可以自检
    Uint16 cellSelfCheckEnable:1;   // 2: 单元block检测允许
    Uint16 bCellCheckOver:1;        // 3: 单元检测完成
    Uint16 cellDischarge:1;			// 4: 单元放电命令

    Uint16 rsvd:11;
};

union CELL_CHECK_FLAG
{
	Uint16 all;
	struct CELL_CHECK_FLAG_BITS bit; 
};
extern union CELL_CHECK_FLAG cellCheckFlag; 
*/
struct CELL_CHECK_STATUS_BITS
{
    u16 Rsvd:2;                   // 0 - 1单元故障保留不复位
    u16 bCellCheckOver:1;         // 2 单元检测完成
    u16 bCellError:1;             // 3 有单元故障
    u16 bCellAutoResetEnable:1;   // 4 单元自动复位允许
    u16 bCellFuncResetEnable:1;   // 5 cell 故障，需要旁路又不能复位时，仅把ARM故障复位
    u16 rsvd:2;                   // 6 - 7 //单元自检故障
};

union CELL_CHECK_STATUS
{
    u16 all;
    struct  CELL_CHECK_STATUS_BITS bit;
};
extern union CELL_CHECK_STATUS cellCheckStatus;

enum CELL_DIAGNOSE_STEP
{
    CELL_DIAGNOSE_INIT,             // 单元自检初始化
    CELL_DIAGNOSE_POWER_WAIT,       // 等待高压合闸
    CELL_DIAGNOSE_RESET,            // 高压电源正常后单元复位
    CELL_DIAGNOSE_FAULT,            // 单元检测
    CELL_DIAGNOSE_IGBT,        	    // 单元IGBT阻断检测
    CELL_DIAGNOSE_OVER,			    // 单元检测完成
    POWER_ON_LOGIC_STATUS_WAIT_UDC	// 等待母线电压建立
};
extern enum CELL_DIAGNOSE_STEP cellCheckStep;

#define CELL_RESET_KEEP_TIME			6       // 6MS
#define CELL_AUTO_RESET_COUNTER			3       // 单元故障检测 自动复位次数
#define CELL_SELF_AUTO_RESET_COUNTER	2		// 单元自检 自动复位次数

#endif



#ifndef __F_CELL_H__
#define __F_CELL_H__


#include  "main.h"
#include  "m_cell.h"

// ----------------函数声明----------------------------------------------
//extern void CellErrorDeal(void);
///extern int16 EnvirTempCalc(int16 envirTemp);
extern void FibreStatusJudgment(void);
extern void UpdateCellInfoDisp(void);
extern void UpdateU8Data(void);
//extern void CellGenMaxCal(void);
extern void CellSpecialTimerDeal(void);
extern void CellFaultReset(void);
extern void CellInforDataDeal(Uint16 id);
extern Uint16 CellOverTempAlarmDeal(int16 *tempt, Uint16 id, Uint16 *tempAlarmFilter, const Uint16 alarmTemp);
extern Uint16 CellOverTempFaultOnDeal(int16 *temp, Uint16 id,  Uint16 faultFlag, Uint16 *tempFilter, const Uint16 faultTemp);
extern Uint16 CellOverTempFaultOffDeal(int16 *temp, Uint16 id,  Uint16 faultFlag, Uint16 *tempFilter, const Uint16 faultTemp, const Uint16 hysteresisTemp);
extern Uint16 CellTempSampleAlarmDeal(int16 *tempt, Uint16 id, Uint16 *tempAlarmFilter, int16 agvTemp);
//extern void CellFaultSubcodeArrage(Uint16 id);
//extern void CellGenFaultGenrator(Uint16 id);
extern Uint16 CellStopFaultSubcodeArrage(Uint16 id, Uint16 cellFault);
extern void CellLosePhaseFaultFromFuncDeal(Uint16 id);
extern void CellBypassEnableAlarmFromFuncDeal(Uint16 id);
extern void ClearCellInfo(Uint16 id);
extern void CellTempInfoDeal(Uint16 id);
// ----------------函数声明结束------------------------------------------

#define CELL_NUM    30         // 30个单元 0为无效
#define CELL_TEMP_ERROR_LAG_RST_VALUE   15		// 单元过温滞后复位判定阈值
#define SUPER_CELL_DATA_LENGTH          120
// HD9X系统
#define CELL_CHECK_TIME					20      // 20ms

//#define CELL_LOSEPHASE_FAULT_FILTER     4       // 单元缺相滤波时间

#define CELL_BUSBAR_MAX_DISP            1300    // II代机母线电压上限
/*
// 单元状态
struct CELL_STATUS_BITS
{
    Uint16 cellId:6;        // 0-5:ID
    Uint16 cellGenFault:1;  // 6:单元总故障
    Uint16 cellCheckOver:1; // 7:单元自检IGBT和旁路接触器完成 
    Uint16 temperature:8;   // 8-15 单元温度
};

union CELL_STATUS
{
	Uint16 all;
	struct CELL_STATUS_BITS bit; 
};
*/
extern union CELL_STATUS cellStatus; 

struct CELL_SUB_STATUS_BITS
{
    Uint16 cellcpldVer:8;   // 0-7:cpld版本号
    Uint16 GeneratrixVol:8; // 8-15:单元母线电压
};

union CELL_SUB_STATUS
{
	Uint16 all;
	struct CELL_SUB_STATUS_BITS bit; 
};
extern union CELL_SUB_STATUS cellSubStatus; 
//----------------------------------------//
struct CELL_ERR_FOR_BYPASS_BITS
{
    Uint16 overVol:1;           // 0 过压
    Uint16 underVol:1;          // 1 欠压
    Uint16 capShare:1;          // 2 均压
    Uint16 oos:1;               // 3 过流
    Uint16 driverPower:1;       // 4 驱动电源故障，仅支持机械旁路
    Uint16 overTemp:1;          // 5 过热
    Uint16 linkErr:1;           // 6 通讯异常
    Uint16 afe:1;               // 7 整流故障
    Uint16 block:1;             // 8 阻断
    Uint16 losePhase:1;         // 9 单元输入缺相

    Uint16 rsvd:6;              // 10~15 保留--已经占满A9-13 A9-14，需要增加要新开功能码
};
    
union CELL_ERR_FOR_BYPASS
{   // 该功能码与A9-13、A9-14匹配用，不能超过10个位
    Uint16 all;
    struct CELL_ERR_FOR_BYPASS_BITS bit;
};
extern union CELL_ERR_FOR_BYPASS cellErrForBypass[CELL_NUM];

struct CELL_ERR_INFO_BITS
{
    u16 cellFault:1;         //  0  总故障
#if HD90_AFE
    u16 driverPower:1;       //  1  驱动电源故障
#else
    u16 losePhase:1;         //  1  缺相
#endif
    u16 rsvd3:1;             //  2  保留
    u16 brakeRes:1;          //  3  制动电阻故障
    u16 verifErr:1;          //  4  校验
    u16 oos:1;               //  5  过流
    u16 overVol:1;           //  6  过压
    u16 underVol:1;          //  7  欠压
    
    u16 capShare:1;          //  8  均压 老榴莲熔丝故障复用了这个BIT
    u16 downwardErr:1;       //  9  下行通讯故障 commErr
    u16 q1Err:1;             // 10  Q1
    u16 q2Err:1;             // 11  Q2
    u16 q3Err:1;             // 12  Q3
    u16 q4Err:1;             // 13  Q4
    u16 rsvd4:1;             // 14  保留 过温报警
    u16 upwardErr:1;         // 15  上行通讯故障 linkErr
    
    u16 rsvd:16;             // 16 - 31  保留
};

union CELL_ERR_INFO
{
    u16 all;
    struct CELL_ERR_INFO_BITS bit;
};
extern union CELL_ERR_INFO cellErrInfo[CELL_NUM];

struct CELL_INFO_FOR_HMI_BITS
{
    u16 overVol:1;           //  0  过压
    u16 underVol:1;          //  1  欠压
    u16 capShare:1;          //  2  均压
    u16 oos:1;               //  3  过流
    u16 losePhase:1;         //  4  缺相
    u16 overTemp:1;          //  5  过温故障
    u16 upwardErr:1;         //  6  上行通讯故障
    u16 bypassErr:1;         //  7  旁路故障

    u16 tempAlarm:1;         //  8  过温报警
    u16 bypassSucc:1;        //  9  旁路有效
    u16 blockErr:1;          // 10  阻断故障
    u16 verifErr:1;          // 11  校验错误
    u16 cellFault:1;         // 12  总故障
    u16 driverPower:1;       // 13  驱动电源故障
    u16 downwardErr:1;       // 14  下行通讯故障
    u16 afeErr:1;            // 15  AFE故障
    
    u16 envirTempAlarm:1;    // 16  环境报警
    u16 rsvd2:1;             // 17  保留
    u16 h1TempAlarm:1;       // 18  H1过温报警
    u16 h1OverTemp:1;        // 19  H1过温
    u16 h2TempAlarm:1;       // 20  H2过温报警
    u16 h2OverTemp:1;        // 21  H2过温
    u16 fuseErr:1;           // 22  熔丝故障  只有老的榴莲单元才有，新的已整合到均压故障中
    u16 brakeRes:1;          // 23  制动电阻故障
    
    u16 rsvd:8;              // 24 - 31  保留
};


union CELL_INFO_FOR_HMI
{
    u16 all;
    struct CELL_INFO_FOR_HMI_BITS bit;
};
extern union CELL_INFO_FOR_HMI cellErrInfoForHMI[CELL_NUM];

// 功能自产生单元报警
struct FUNC_GENRATOR_CELL_ALARM_BITS
{
    Uint16 overTempAlarm:1;         // 0 单元过温报警
    Uint16 envirOverTempAlarm:1;    // 1 环境过温报警 榴莲
    Uint16 h1OverTempAlarm:1;       // 2 H1过温报警 榴莲
    Uint16 h2OverTempAlarm:1;       // 3 H2过温报警 榴莲
    
    Uint16 losePhase:1;             // 4 单元缺相报警 保留
    
    Uint16 rsvd:11;                 // 5-15 保留报警
};

union FUNC_GENRATOR_CELL_ALARM
{
	Uint16 all;
	struct FUNC_GENRATOR_CELL_ALARM_BITS bit; 
};
extern union FUNC_GENRATOR_CELL_ALARM funcGenratorCellAlarm[CELL_NUM];


// 功能自产生单元故障
struct FUNC_GENRATOR_CELL_FAULT_BITS
{
    Uint16 overTempFault:1;     // 0 单元过温故障
    Uint16 h1OverTempFault:1;   // 1 H1过温故障 榴莲
    Uint16 h2OverTempFault:1;   // 2 H2过温故障 榴莲
    Uint16 driverPowerFault:1;  // 3 驱动电源故障 -- I代机专用
    
    Uint16 block:1;             // 4 阻断故障 保留
    Uint16 uv:1;                // 5 II代机单元母线欠压报警
    Uint16 losePhase:1;         // 6 单元输入缺相

    Uint16 rsvd:9;              // 7-15 故障保留
};

union FUNC_GENRATOR_CELL_FAULT
{
	Uint16 all;
	struct FUNC_GENRATOR_CELL_FAULT_BITS bit; 
};
extern union FUNC_GENRATOR_CELL_FAULT funcGenratorCellFault[CELL_NUM];

extern Uint16 cellStatusL;
extern int16 cellTempture[];
extern int16 enviromentTemp[];                 // 环境温度
extern Uint16 cellBlockStatus;
extern u32 cellBypassFdb;
//extern u32 cellSelfBypassFdb;

#define CELL_NUMBER_TRUE        (funcCode.code.installedCells * 3)//单元数
extern int16 cellTempMax;     // 单元温度最大值
extern int16 cellTempMin;     // 单元温度最小值
extern int16 cellTempAvg;          // 单元温度平均值
extern Uint32 cellStatusFlag, cellStatusClearEnable, cellInfoClearEnable; 

extern Uint16 cellGeneratrix[CELL_NUM];    //单元母线电压
extern Uint32 afeStatusFlag; // 记录单元状态发生变化，每个bit代表一个单元
extern Uint16 superCellData[];
extern Uint32 cellRunningBlock;
extern Uint16 cellAttribute;        // 单元属性

//extern Uint16 cellFibreErrNumber[CELL_NUM];
//extern Uint16 cellFibreErrNoStatis[CELL_NUM];
//extern Uint16 cellFibreErrSum[CELL_NUM];
//extern Uint32 cellFibreInferior;
extern bool bBlockFaultFlag;
extern Uint16 cellMajorFaultCode, cellStopFaultCode, cellAlarmCode;
//extern bool cellLinkFault[CELL_NUM];
extern Uint16 maxGenVol;
//extern Uint16 cellTempAlarmFilter[CELL_NUM];           // 单元温度滤波
//extern Uint16 cellTempSampleAlarmFilter[CELL_NUM];     // 单元温度采样异常滤波
//extern Uint16 cellTempErrorFilter[CELL_NUM];           // 单元温度滤波
//extern Uint16 cellTempErrorOffFilter[CELL_NUM];        // 单元温度滤波
//extern Uint16 cellEnvirTempAlarmFilter[CELL_NUM];      // 单元环境温度滤波
//extern Uint16 cellLosePhaseFilter[CELL_NUM];           // 单元缺相滤波


#endif



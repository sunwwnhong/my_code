//======================================================================
//
// Time-stamp: <2011-2-21 Lei.Min, 0656>
//
// LogInfoForHmi
// 整理交互给HMI的通讯数据
//
//======================================================================

#ifndef __FUNC_LOG_INFO_FOR_HMI_H_
#define __FUNC_LOG_INFO_FOR_HMI_H_

extern void SystemStatusDeal(void);
extern void FlagProcessForHMI(void);
extern void SuperPasswordProcess(void);
extern Uint16 IsFactoryTestOn(void);


// 系统日志 给上位机和HMI用
struct CABINET_LOG_FLAG_BITS
{
    Uint16 inletContactorOn:1;      // 0  进线接触器合闸命令有效  目前未用
    Uint16 inletContactorOff:1;     // 1  进线接触器分闸命令有效
    Uint16 outletContactorOn:1;     // 2  出线接触器1合闸命令有效
    Uint16 outletContactorOff:1;    // 3  出线接触器分闸命令有效
    Uint16 lineContactor1On:1;      // 4  工频接触器1合闸命令有效
    Uint16 lineContactor1Off:1;     // 5  工频接触器1分闸命令有效
    Uint16 bypassCmd:1;             // 6  自动旁路柜手动旁路命令
    Uint16 line2InvCmd:1;           // 7  自动旁路柜一键工频切变频命令
    Uint16 lineContactor2On:1;      // 8  工频接触器2合闸命令有效
    Uint16 lineContactor2Off:1;     // 9  工频接触器2分闸命令有效
    Uint16 outletContactor2On:1;    // 10 出线接触器2合闸命令有效
    Uint16 line2InvCmd2:1;          // 11 自动旁路柜一键工频切变频命令2

    Uint16 rsvd:4;                  // 12 - 15
};

union CABINET_LOG_FLAG
{
    Uint16 all;
    struct CABINET_LOG_FLAG_BITS bit;
};
extern union CABINET_LOG_FLAG cabinetLogFlag;

#endif

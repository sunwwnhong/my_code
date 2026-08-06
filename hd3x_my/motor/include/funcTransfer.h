//======================================================================
//
// Time-stamp: <2011-2-21 Lei.Min, 0656>
//
// P2P comm
// 点对点通讯数据处理
//
//======================================================================

#ifndef __FUNC_TRANSFER_H__
#define __FUNC_TRANSFER_H__

// ----------------函数声明----------------------------------------------
//extern void TransferDeal(void);
extern u16 MotorSnDiFuncSelValid(void);
// ----------------函数声明结束------------------------------------------
#define SYN_TRANSFER_MOTOR_NUM      4   // 支持同步上切个数

#define TRANSFER_NONE       0       // 不动作
#define TRANSFER_UP         1       // 变频切工频
#define TRANSFER_DOWN       2       // 工频切变频
#define TRANSFER_QUICK_UP   0x11    // 快速上切换
#define TRANSFER_QUICK_DOWN 0x12    // 快速下切换

struct TRANSFER_STATUS_BIT
{
    Uint16 invContactOff:1;             // 0 断开变频接触器 1-需要断开变频接触器
    Uint16 netContactFdb:1;             // 1 工频接触器反馈 1-工频接触器反馈有效
    Uint16 reactorContactOff:1;         // 2 电抗器旁路接触器断开 1-接入电抗器
    Uint16 upTransferOverTime:1;        // 3 上切超时
    Uint16 downTransferOverTime:1;		// 4 下切超时
    Uint16 reactorErr:1;                // 5 电抗器过热故障
    Uint16 inlineReverse:1;             // 6 网侧相序错误
    
    Uint16 rsvd:9;                     // 15:7
};
union TRANSFER_STATUS
{
    Uint16              all;
    struct TRANSFER_STATUS_BIT bit;
};
extern union TRANSFER_STATUS transferStatus;

struct QUICK_TRANSFER_STATUS_BIT
{
    Uint16 phaseCoincidenceFlag:1;      // 0 快速上切---相位重合标记
    Uint16 upChangeOver:1;              // 1 快速上切完成
    Uint16 phaseDifferInc:1;            // 2 相位差增加标识 
    Uint16 phaseLockSuccess:1;          // 3 快速切换锁相开始输出解锁

    Uint16 netContactOnTest:1;          // 4 工频接触器合闸--用于快速上切前检测工频接触器动作时间
    Uint16 netContactOffTest:1;         // 5 工频接触器分闸
    Uint16 netContactOff:1;             // 6 快速下切工频分闸
    Uint16 invContactOn:1;              // 7 快速下切变频合闸
    
    Uint16 rsvd:8;                      // 15:8
};
union QUICK_TRANSFER_STATUS
{
    Uint16              all;
    struct QUICK_TRANSFER_STATUS_BIT bit;
};
extern union QUICK_TRANSFER_STATUS quickTransferStatus;

extern Uint16 syncTransfer;

extern Uint16 invContactFdb, netContactFdb;

extern Uint16 phaseDiffer;
extern Uint16 netContactorTestNum;
extern Uint16 upTransSel;
extern Uint16 downTransSel;

#define UP_TRANSFER_MODE_SYN        0   // 同步上切换
#define UP_TRANSFER_MODE_QUICK      1   // 快速上切换
#define DOWN_TRANSFER_MODE_SYN      0   // 同步下切换
#define DOWN_TRANSFER_MODE_QUICK    1   // 快速下切换
#endif




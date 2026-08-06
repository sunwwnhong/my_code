//==================================================================================================
//
// 交互
// 功能与性能的接口(ARM与DSP的交互)；
// DSP与FPGA的交互
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_INTERFACE_H__
#define __M_INTERFACE_H__




#include "main.h"
#include "m_interfacePublic.h"








extern volatile Uint16 interfaceRam[];

extern Uint16 cfGroup[];
extern Uint16 ceGroup[];

extern u16 hwCellFlag;

//==============================================================================
#define VF_V_GAIN       (ceGroup[0])    // VF运行时输出电压增益
#define InvPwmPeriod    (ceGroup[1])    // 变频器发波时间，单位：载波周期
#define CirCurMode      (ceGroup[2])    // 环流模式。0：无效，不开启环流；1：环流模式1(电网定向)；2：环流模式2。
#define CirCurId        (ceGroup[3])    // 环流测试的励磁电流给定。0.0%：自动给定；0.1%：磁链环闭环给定；0.2%～100.0%。
#define CirCurSet       (ceGroup[4])    // 环流测试的电流给定
//==============================================================================




//==============================================================================
enum RAM_STATUS
{
    RAM_STATUS_WAIT_FPGA,       // FPGA没有准备好
    RAM_STATUS_FIRST,           // FPGA没有准备好->FPGA准备好
    RAM_STATUS_JUDGE_BUSY,      // 判断RAM标志是否busy
    RAM_STATUS_RW,              // RAM标志不busy，可以操作RAM
    RAM_STATUS_R_END
};
extern enum RAM_STATUS ramStatus;
//==============================================================================




void ResetIoc(void);





void RcvDataFunc2Core(void);
void SendDataCore2Func(void);



void UpdateDataCore2Fpga(void);








#endif  //__M_INTERFACE_H__






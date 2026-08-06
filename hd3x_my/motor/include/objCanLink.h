/*************** (C) COPYRIGHT 2010   Technology Co., Ltd****************
* File Name          : f_canlink.h
* Author             : 	
* Version            : V0.0.1
* Date               : 08/25/2010
* Description        : CAN_LINK驱动库
					  邮箱31可用作自动应答邮箱
					  邮箱30~16可用作接收邮箱
					  15~0可用作发送邮箱


********************************************************************************/

#ifndef __F_OBJ_CAN_LINK_H__
#define __F_OBJ_CAN_LINK_H__

// ----------------函数声明----------------------------------------------
extern void CanlinkFun(void);
extern void CanInitConfig(void);
// ----------------函数声明结束------------------------------------------

#define		CAN_REMOTE_EN   		0						// CAN远程帧使能

// ID号屏蔽标识
#define		CANLINK_ID_MASK			0x3f					// ID屏蔽标识


// 协议命令代码

#define		CAN_LINK_W_REG			5						// 写寄存器



// 功能码定义
#define		CAN_LINK_S_ADDR			(funcCode.code.commSlaveAddress & CANLINK_ID_MASK) // 本站地址
#define		CAN_LINK_BAUD_SEL		((funcCode.code.commBaudRate >> 12) & 0x07)    // 波特率设置

#define     P2P_COMM_HOST           1         // 点对点通讯主机
#define     P2P_COMM_SLAVE          2         // 点对点通讯从机


extern Uint16 CanRxTxCon;

#define P2P_SLAVE_NUMBER_MAX    8
#define CAN_LENGTH              8
extern Uchar dataRxCan[CAN_LENGTH];


// can 控制字
struct CAN_MASTER_CMD_BIT
{
    Uint16 canRunCmd:1;         // Bit0: CAN接收完成
    Uint16 canJogRunCmd:2;      // BIT1\2: 01 正转点动 02 反转点动 
    Uint16 rsvd2:1;             // BIT3: 
    Uint16 runFlag:1;           // BIT4 主机运行标记
    Uint16 mainF009:1;          // BIT5 主机的F0-09

    Uint16 rsvd:2;              // BIT6 BIT7 保留

    Uint16 rsvdNoUse:8;         // Bit8-15: 严禁使用
};

union CAN_MASTER_CMD
{
    Uint16 all;
    struct CAN_MASTER_CMD_BIT bit;
};
extern union CAN_MASTER_CMD canMasterCmd;

// can 状态字
struct CAN_SLAVE_STATUS_BIT
{
    Uint16 run:1;               // Bit0: CAN接收完成
    Uint16 err:1;               // BIT1: 运行方向

    Uint16 rsvd:14;             // Bit3-15: 保留
};

union CAN_SLAVE_STATUS
{
    Uint16 all;
    struct CAN_SLAVE_STATUS_BIT bit;
};
extern union CAN_SLAVE_STATUS canSlaveStatus[P2P_SLAVE_NUMBER_MAX];


extern Uchar commBaudCan;
#endif












//======================================================================
//
// Time-stamp: <2011-2-21 Lei.Min, 0656>
//
// P2P comm
// 点对点通讯数据处理
//
//======================================================================

#ifndef __FUNC_P2P_H__
#define __FUNC_P2P_H__

// ----------------函数声明----------------------------------------------
extern void P2PDataDeal(void);
// ----------------函数声明结束------------------------------------------

#define  COMM_P2P_COMM_ADDRESS        0x1001    // 点对点通讯使用地址
#if 1//DEBUG_F_P2P_CTRL
/*
typedef struct
{
    Uint16 p2pEnable;           // P2P当前是否有效
    // can主机发送的数据
    Uint16 P2PSendDataTorque;   // 通讯发送数据 实时转矩
    Uint16 P2PSendDataSpeed;    // 通讯发送数据 同步频率
    Uint16 P2PSendDataAimFrq;   // 通讯发送数据 目标频率
    
    // can从机接收到的数据
    Uint16 P2PRevDataTorque;    // 通讯接收数据
    Uint16 P2PRevDataSpeed;     // 通讯接收数据
    Uint16 P2PRevDataAimFrq;    // 通讯接收数据 目标频率
    
    // can从机接收后处理完成的数据
    int16 processValueTorque;   // 接收数据进行线性处理后
    int16 processValueSpeed;    // 接收数据进行线性处理后
    int16 processValueAimFrq;   // 接收数据进行线性处理后
} P2P_DATA_STRUCT;

extern P2P_DATA_STRUCT p2pData;
 */
#endif
#endif




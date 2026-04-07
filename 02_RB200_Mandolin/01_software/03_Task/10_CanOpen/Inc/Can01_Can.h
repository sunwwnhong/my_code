/*
 * Can01_Can.h
 *
 *  Created on: 2017年7月25日
 *      Author: zhuxc
 */

#ifndef Can01_Can_H
#define Can01_Can_H



#define SDOID_R     0x600UL                                       //SDO报文接收ID号
#define SDOID_T     0x580UL                                       // SDO报文发送ID号
#define PDO1ID_R    0x200UL                                       // PDO1报文接收ID号
#define PDO1ID_T    0x180UL                                       // PDO1报文发送ID号
#define PDO2ID_R    0x300UL                                       // PDO2报文接收ID号
#define PDO2ID_T    0x280UL                                       // PDO2报文发送ID号
#define PDO3ID_R    0x400UL                                       // PDO3报文接收ID号
#define PDO3ID_T    0x380UL                                       // PDO3报文发送ID号
#define PDO4ID_R    0x500UL                                       // PDO4报文接收ID号
#define PDO4ID_T    0x480UL                                       // PDO4报文发送ID号
#define NMT_T       0x0UL                                         // NMT报文接收ID号
#define SYNC        0x80UL                                        // SYNC报文接收ID号
#define BEAT        0x700UL                                       // 心跳报文发送ID号
#define EMERG       0x80UL                                        // 紧急报文发送ID号


#define SDOBuff_Max     20                                      // SDO 缓存最大数

//-------------------------------------------------------------------------------------------------
// SDO报文接收缓存格式定义
//-------------------------------------------------------------------------------------------------
typedef	struct
{
    UCHAR FCmd;                                                 // 命令
    UCHAR OD[2];                                                // 对象字典
    UCHAR Index;                                                // 子索引
    ULONG SDOData;                                              // 数据
}INFSTRUCT;
//-------------------------------------------------------------------------------------------------
typedef	union
{
        UINT w; 
        //-----------------------------------------------------------------------------------------
		struct {
                    UINT    NMT_En          :1;                 // 网络管理开关
                    UINT    SDO_En          :1;                 // SDO开关
                    UINT    PDO_En          :1;                 // PDO开关
                    UINT    HeartB_En       :1;                 // 心跳开关
                    UINT    NMTUpFlag       :1;                 // NMT节点保护
                    UINT    NMTGardEn       :1;                 // NMT节点保护开启
                    UINT    HeartBFlag      :1;                 // 第一个心跳标志
                    UINT    NMTChange       :1;                 // 节点切换
                    UINT    NMTStatus       :8;                 // NMT状态代码
                    UINT    NMTInitOK       :1;                 // NMT 初始化完成标志
                    UINT    ConsumHeart     :1;                 // 消费者心跳
                    UINT    PoroduHeart     :1;                 // 生产者心跳
                    UINT    NETInitEmcy     :1;                 // 初始化时有故障
                    UINT    ErrReset        :1;                 // 故障清除
                    UINT    PDOSyncFlg      :1;                 // 第一次标志
                    //-----------------------------------------------------------------------------
                    UINT    PDO1600Flg      :1;                 // 1600 可映射标志
                    UINT    PDO1601Flg      :1;                 // 1601 可映射标志
                    UINT    PDO1602Flg      :1;                 // 1602 可映射标志
                    UINT    PDO1603Flg      :1;                 // 1603 可映射标志
                    UINT    PDO1A00Flg      :1;                 // 1A00 可映射标志
                    UINT    PDO1A01Flg      :1;                 // 1A00 可映射标志
                    UINT    PDO1A02Flg      :1;                 // 1A00 可映射标志
                    UINT    PDO1A03Flg      :1;                 // 1A00 可映射标志
                    //-----------------------------------------------------------------------------
		} f;
        //-----------------------------------------------------------------------------------------
} NMTOPERATIONDEF;

typedef struct
{
    INFSTRUCT   SDO[SDOBuff_Max];                               // SDO 报文接收缓存
    NMTOPERATIONDEF NMTV;                                       // NMT 报文标志位
    ULONG   SiteGuardCnt;                                       // 节点保护
    ULONG   ConsumerTCnt;                                       // 消费者时间
    ULONG   ProductrTCnt;                                       // 生产者时间
    USHORT  CanStatus;                                          // Can命令状态
    USHORT  CanCmdStatus;                                       // Can命令状态
    UCHAR   SDOSavedNum;                                        // SDO 报文接收周期寄存器
    UCHAR   SDOSendNum;                                         // SDO 报文发送周期寄存器
    UCHAR   SDODealedNum;                                       // SDO 已经处理帧数
    UCHAR   SDORemain;                                          // SDO 待处理的帧数
    UCHAR   SDoSendBuff[8];                                     // SDO 发送缓存
    UCHAR   NMTStatus;                                          // NMT 状态
    UCHAR   BeatHrtFlg;                                         // 心跳标志
    UCHAR   PosCalFlg;                                          // 位置更新标准
    ULONG  CanStatusCnt;                                       // Can 接收数据标志
}CANSTRUCT;

extern CANSTRUCT CanVar;                                        // 全局变量声明
extern void CAN_Init(void);                                     // Can 相关信息初始化处理
extern void CAN1_RXCheck(void);                                 // Can 接收数据帧检查
//extern void Can_Deal(void);                                   // Can Open 对象字典处理
extern void CAN1_Tx_Msg(ULONG id,uint16_t len,uint16_t *dat);         // 数据发送
extern void NMT_StationMnge(UCHAR NMTStatus);					// 状态机管理

#endif

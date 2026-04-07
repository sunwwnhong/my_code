/*
 * Can04_PDOMngr.h
 *
 *  Created on: 2017年7月25日
 *      Author: zhuxc
 */

#ifndef Can04_PDOMngr_H
#define Can04_PDOMngr_H


#define PDOBuff_Max 50                                          /* 发送缓存个数                     */ /* <V0120> */

typedef struct
{
    uint16_t Data[8];                                              /* 发送数据帧                       */
    ULONG ID;                                                   /* 发送帧ID                         */
    UCHAR DataLength;                                           /* 发送数据长度                     */
}PDO_BUFF_DEFINE;

typedef struct
{
    USHORT PDO_Index;                                           /* PDO 映射的地址                   */
    UCHAR  DataLgth;                                            /* PDO 数据长度                     */
}PDO_MAP_STRUCT;

typedef struct
{
    PDO_MAP_STRUCT RPDO_Map[4][4];                              /* RPDO 映射地址组寄存器            */
    PDO_MAP_STRUCT TPDO_Map[4][4];                              /* TPDO 映射地址组寄存器            */
    PDO_BUFF_DEFINE PDO_SendBuff[PDOBuff_Max];                  /* TPDO 发送缓存                    */
    ULONG TPDO_PROBIT[4];                                       /* TPDO 禁止时间                    */
    ULONG TPDO_PROBITCnt[4];                                    /* TPDO 禁止时间计数器              */
    /*----------------------------------------------------------------------------------------------*/
    ULONG TPDO_DataVarBuff[4];                                  /* TPDO 同步事件(数据发生变化)      */
    ULONG TPDO_EVENTT[4];                                       /* TPDO 事件时间                    */
    ULONG TPDO_Asynch[4];                                       /* TPDO 异步事件计数器              */
    ULONG TPDO_AsyProbitcnt[4];                                 /* TPDO 异步时间禁止计数器          */
    UCHAR TPDO_Synch[4];                                        /* TPDO 同步事件值                  */
    USHORT TPDO_SynchCnt[4];                                    /* TPDO 同步事件计数器              */
    UCHAR TPDO_TRIGEn[4];                                       /* TPDO 数据发送有效                */
    UCHAR TPDO_TRIGFlg[4];                                      /* 首次发送数据标志                 */
    UCHAR TPDO_TYPE[4];                                         /* TPDO 发送方式                    */
    ULONG TPDO_ID[4];                                           /* 发送PDO帧ID                      */
    UCHAR TPDO_En[4];                                           /* 发送PDO使能标志                  */
    /*----------------------------------------------------------------------------------------------*/
    ULONG RPDO_En[4];                                           /* 接收PDO开启标志                  */
    /*----------------------------------------------------------------------------------------------*/
    ULONG RPDO_CobId[4];                                        /* RPDO 的COB_ID                    */
    UCHAR RPDO_Type[4];                                         /* RPDO 的传输类型                  */
    UCHAR RPDO_SyncBuf[4][8];                                   /* 同步帧报文                       */
//    UCHAR RPDO_SyncBufNew[4][8];                                /* 同步帧报文缓存                   */
    UCHAR RPDO_Synch[4];                                        /* 等待同步帧                       */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR PDOBuff_Cnt;                                          /* 缓存周期寄存器                   */
    UCHAR PDOSend_Cnt;                                          /* 发送计数器                       */
    UCHAR PDOBuff_Remain;                                       /* 发送剩余寄存器                   */
    UCHAR RPDO_MapNum[4];                                       /* RPDO 映射数                      */
    UCHAR TPDO_MapNum[4];                                       /* TPDO 映射数                      */
    UCHAR RPDO_ByteNum[4];                                      /* RPDO 字节数                      */
    UCHAR TPDO_ByteNum[4];                                      /* TPDO 字节数                      */
    UCHAR PDO_ErrFlag;                                          /* PDO 异常标志                     */
    UCHAR SYNCUpFlag;                                           /* 同步帧到达标志                   */
	UCHAR SYNCUpFlag1;											/* 同步帧到达标志					*/
    ULONG SYNC_Cnt;                                             /* 同步发生器计数器                 */
}PDO_STRUCT;
extern PDO_STRUCT PDO_Var;
   
extern void PDO_Dataclr(void);
extern void PDO_MapUpdate(USHORT IndexValue);
extern void TPDO_DataSendDeal(void);
extern void RPDO1(void);
extern void RPDO2(void);
extern void RPDO3(void);
extern void RPDO4(void);
extern void RPDO_SynchDeal(void);



#endif

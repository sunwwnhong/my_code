/*
 * Can03_ODBMngr.h
 *
 *  Created on: 2017年7月25日
 *      Author: zhuxc
 */

#ifndef Can03_ODBMngr_H
#define Can03_ODBMngr_H


#define EMCYBuff_Num    4

typedef struct
{
    USHORT Errcode;                                        /* 错误码                                */
    USHORT Auxiliary;                                      /* 辅助码                                */ 
}EMCY_STRUCT;

/*--------------------------------------------------------------------------------------------------*/
typedef struct
{
    /*----------------------------------------------------------------------------------------------*/
    UCHAR Reserved;                                        /* 保留,数据对齐用                       */
    UCHAR SendLength;                                      /* 发送数据长度                          */    
    /*----------------------------------------------------------------------------------------------*/
    uint16_t SendBuf[8];                                      /* 发送缓存                              */
    USHORT SDO_580;                                        /* SDO_580 ID                            */
    USHORT PDO1_180;
    USHORT PDO2_280;
    USHORT PDO3_380;
    USHORT PDO4_480;
    USHORT Heart_Beat;
    USHORT EMCY_ID;
    /*----------------------------------------------------------------------------------------------*/
    ULONG SiteGuardTime;                                   /* NMY节点保护时间                       */
    ULONG PoroductTime;                                    /* 生产者时间                            */
    ULONG ConsumerTime;                                    /* 消费者时间                            */
    USHORT ConsumerAddr;                                   /* 消费者地址                            */
    /*----------------------------------------------------------------------------------------------*/
    USHORT SYNC_En;                                        /* 同步发生器开启                        */
    ULONG  SYNC_Priod;                                     /* 同步发生器周期                        */
    /*----------------------------------------------------------------------------------------------*/
    EMCY_STRUCT EMCY_Buff[EMCYBuff_Num];                   /* EMCY 缓存                             */
    UCHAR EMCY_SavedCnt;                                   /* EMCY 存储计数                         */
    UCHAR EMCY_SendCnt;                                    /* EMCY 发送计数                         */
    UCHAR EMCY_Remain;                                     /* EMCY 剩余故障条数                     */
    UCHAR EMCY_En;                                         /* 紧急报文使能                          */
    UCHAR EMCY_Num;                                        /* 紧急报文条数                          */
    /*----------------------------------------------------------------------------------------------*/
}OD_OPERATION;
extern OD_OPERATION OD_V;



extern void ODBMange_Init(void);                   /* 对象字典管理处理化                            */
extern void Can_Deal(void);                        /* SDO 报文接收应答处理                          */
extern USHORT ODB_Check(USHORT Index,UCHAR SubIndex);
extern void ODB_Update(USHORT IndexAddr);
extern void CanOpenEMCY_Update(USHORT Errcode);
extern void OD_SDOError(UCHAR SDOSendNum,ULONG ErrorCode);
extern void OD_SDOWriteOver(UCHAR SDOSendNum);
extern UCHAR CANopen_SiteResponse(UCHAR Type);     /* 远程帧应答                                    */
extern void EMCY_Clear(void);

#endif

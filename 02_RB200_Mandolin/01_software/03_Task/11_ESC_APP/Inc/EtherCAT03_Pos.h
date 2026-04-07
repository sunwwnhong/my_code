/*
 * EtherCAT16_Pos.h
 *
 *  Created on: 2018年06月20日
 *      Author: zhuxc
 */
#ifndef EtherCAT16_Pos_H
#define EtherCAT16_Pos_H

typedef struct
{
    UCHAR HaltStatus;                                   /* 暂停状态                                 */
    UCHAR FastStatus;                                   /* 快速停机状态                             */
    LONG    TargetTorqQ15;
    LONG    TorCmdQ15;
    /*----------------------------------------------------------------------------------------------*/
    INT64   SpdOutQ15;
    INT64   DecBase_Q15;
    INT64   DecBase6084_Q15;             /* 减速基值6084                                       */
    INT64   DecBase6085_Q15;             /* 减速基值6085                                       */
    INT64   DecBase609A_Q15;             /* 减速基值609A                                        */
    INT64   DecSBase6084_Q15;            /* 减速基值6084                                        */
    INT64   DecSBase6085_Q15;            /* 减速基值6085                                        */
    INT64   IntorPosTmpQ15;

}ETHERCAT_CONTROL;
extern ETHERCAT_CONTROL EcontSMachine;

typedef struct
{
    LONG s32TargetPosOld;                               /* 上一周期目标位置                       */
    LONG s32PositionOffsetOld;                          /* 上一周期位置偏置                       */
    SHORT s32PositionOffsetFlag;                        /* 位置偏置标志位                         */
    LONG PosSum;                                        /* 位置计数                               */
    LONG PosSumRemain;                                  /* 位置余量                               */
    /*----------------------------------------------------------------------------------------------*/
    USHORT PPStep;                                       /* 状态机                                */
    USHORT OB6040Bit4Status;                             /* 6040bit上升沿                         */

    USHORT OB6040Bit4Status2;
    USHORT Mode18Sel;
    /*----------------------------------------------------------------------------------------------*/
    LONG AbsPosCmd;                                     /* 绝对位置指令                              */
    /*----------------------------------------------------------------------------------------------*/
    LONG PosCmdRemain;

    LONG s32TargetPos607AOld;                           /*  用于绝对位置自动更新                    */
    LONG s32TargetVel6081Old;                           /*  用于绝对位置自动更新                    */
}ETHERCAT_POS;
extern ETHERCAT_POS EthPosV;
extern LONG EtherCAT_PosCmd( void );
extern void EtherCATPosDeal( void );
extern UCHAR AbsPosRecord;
extern void EtherCATPosLatch( void );
extern void EtherCatHaltParameter_Update( void );
extern void PosLatch_Init( void );
#endif

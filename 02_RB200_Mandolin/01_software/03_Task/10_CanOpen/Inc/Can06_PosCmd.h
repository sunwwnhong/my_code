/*
 * Can06_PosCmd.h
 *
 *  Created on: 2019年10月10日
 *      Author: xuezhushan
 */

#ifndef Can06_PosCmd_H
#define Can06_PosCmd_H


typedef struct
{
    UCHAR HaltStatus;                                   /* 暂停状态                                 */
    UCHAR FastStatus;                                   /* 快速停机状态                             */
    /*----------------------------------------------------------------------------------------------*/
    INT64   SpdOutQ15;
    INT64   DecBase_Q15;
    INT64   DecBase6084_Q15;             /* 减速基值【6084】                                        */
    INT64   DecBase6085_Q15;             /* 减速基值【6085】                                        */
    INT64   DecBase609A_Q15;             /* 减速基值【609A】                                        */
    INT64   DecSBase6084_Q15;            /* 减速基值【6084】                                        */
    INT64   DecSBase6085_Q15;            /* 减速基值【6085】                                        */
    INT64   IntorPosTmpQ15;
}CanOpen_CONTROL;
extern CanOpen_CONTROL ContSMachine;


typedef struct
{
    LLONG   AccBasic_Q15;       //加速度   
    LLONG   DecBasic_Q15;       //减速度
    LLONG   SpdCmd;             //速度指令
    UCHAR   ManualAutoModOld;   //记录上一周期手自动切换端子状态      @瑞博特20240311  
    UCHAR   AutoJogStep;        //松开JOG端子实现回零状态机           @瑞博特20240311    
    
   
}CanOpen_POSJogOrg;
extern CanOpen_POSJogOrg CanPOSJOGV;

typedef struct
{
    LONG s32TargetPosOld;                               // 位置指令值(上一次)
    LONG PosSum;                                        // 位置指令累加值
    LONG PosSumRemain;                                  // 位置指令余数值
    LONG PosCmdQEP;                                     // 位置指令QEP
    /*----------------------------------------------------------------------------------------------*/
    UCHAR PPStep;                                       // 位置轮廓模式操作步骤
    UCHAR OB6040Bit4Status;                             // 控制字状态
    UCHAR OB6040Bit4Rising_edge;                        /* 控制字上升沿状态                         */
    /*----------------------------------------------------------------------------------------------*/
    LONG AbsPosCmd;                                     // 绝对位置脉冲
    LONG AbsPosCmdOld;                                  // 绝对位置脉冲指令上次值
    LONG SpdCmdOld;                                     /* 轮廓位置速度 (上一周期)                   */
    INT64 PosSpdCmd;                                    /* 开环位置脉冲                              */
    LONG PosActalue;                                    /* 6064实际用户位置反馈                     */
    LONG PosActalueOld;                                 /* 6064实际用户位置反馈   (上一周期)        */

    /*----------------------------------------------------------------------------------------------*/
    LONG PosCmdRemain;
    USHORT Ctrl_WordOld;                                /* 记录上一周期控制字                        */
    USHORT  UpdateTimeCnt;                              //控制字状态更新计时
}CanOpen_POS;
extern CanOpen_POS CanPosV;

extern UCHAR CiA402_StatusMachine(UCHAR ControlStatus );
extern UCHAR QuickStop_flag;
extern ULONG InterPeriod;       //插补位置周期
extern ULONG CanOpenSyncTimeus;
extern UCHAR CanOpen_ControlMode;
extern UCHAR CanOpen_ControlStatus;

void CanOpenPosParameterUpdate( void );
void AutoJOGSpd( void );
void CanOpenPosJOGUpdate( void );
extern LONG CanOpen_PosCmd( void );
extern void CanOpen_ControlModeSel(void);
extern void CanOpen402Status_ControlWordDeal(void);
extern void HaltParameter_Update( void );

#endif

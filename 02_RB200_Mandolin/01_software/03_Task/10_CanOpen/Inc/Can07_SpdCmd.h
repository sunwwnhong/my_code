/*
 * Can07_SpdCmd.h
 *
 *  Created on: 2019年10月10日
 *      Author: xuezhushan
 */

#ifndef Can07_SpdCmd_H
#define Can07_SpdCmd_H

typedef struct
{
    LLONG    AccBasic_Q15;       //加速度   
    LLONG    DecBasic_Q15;       //减速度
    LLONG   SpdCmd;             //速度指令
    LLONG   TargetSpd_Q15;      //目标速度
    LONG    CanMaxSpd;          //最大速度（0.1rpm）  
    LONG    MaxSpdLimt;         //最大速度（标幺值）
    UCHAR   ReachSpdFlg;        //速度发送完毕指令
   LONG    ReaSpdRef;      //速度到达计时
}CANOPENSPD;
extern CANOPENSPD CanSpdV; 


typedef struct
{
LONG    IntorPosOld ;           //前一拍插补位置值
LONG    InterPos_PreSet ;       //插补位置缓存
LONG    InterPosNew ;           //插补位置值

LONG    InterPeriodCnt;         //插补周期计时
LONG    PDOPeriodReal;          //PDO传输实际值
LONG    PDOPeriodCnt;           //插补位置更新计时
LONG    IntorPosTmp;
UCHAR   InterPeriodFlag;        //插补周期更新标志
UCHAR   PDOPeriodFlag;          //插补位置更新标志
  
}CANOPENINTERMODE;
extern CANOPENINTERMODE CanIntMod;
   
extern LONG CanOpenSpdSource( void );

extern LONG InterPosMode(void);
extern LONG PosDivOut(void);

#endif


/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                     */
/*                                          2017 ~                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*                                                                                                  */
/*      User09_MonDef.c : Ｕｎ功能码的监控管理                                                            */
/*                                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*                                                                                                  */
/*      1.Ｕｎ参数定义                                                                                    */
/*                                                                                                  */
/*      2.Ｕｎ参数管理                                                                                    */
/*                                                                                                  */
/*      3.Ｕｎ参数映射                                                                                    */
/*                                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
#include "Main.h"


#define UMONSETBIT( sig, bit )  ((sig)? (1UL<<bit) : 0x0000)
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数: Rv = 0;                                                                               */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdZero( MONDEF *Undef )
{
        return( 0 );
}
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数: Rv = (SHORT)Undef->Var;                                                           */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdShort( MONDEF *Undef )
{
        return( (LONG)*Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数 : Rv = (USHORT)Undef->Var;                                                         */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdUshort( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数 : Rv = (LONG)Undef->Var;                                                           */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdLong( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数 : Rv = (ULONG)Undef->Var;                                                          */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdUlong( MONDEF *Undef )
{
        return( *Undef->Var.Pulong );
}
/*--------------------------------------------------------------------------------------------------*/
/*      标准函数 : Rv = (LONG)Undef->Var * Gain                                                     */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_StdMulgain( MONDEF *Undef )
{
        return( MlibMulgain( *Undef->Var.Plong, *Undef->Gain.Plong ) );
}
/*--------------------------------------------------------------------------------------------------*/
/*      スキャン実行時間計算関数                                                                    */
/*--------------------------------------------------------------------------------------------------*/
ULONG   uncal_ScanExeTime( MONDEF *Undef )
{
float fx;
ULONG kx;
      fx = (float)(*Undef->Var.Pushort) * 0.1f;
      kx = (ULONG)fx;
      return( kx );
}
/*--------------------------------------------------------------------------------------------------*/

/****************************************************************************************************/
/*                                                                                                  */
/*      Ｕｎ监控码定义                                                                             */
/*                                                                                                  */
/****************************************************************************************************/




/****************************************************************************************************/
/*      Un000 : 电机旋转速度(动作监视) [min-1, mm/s]                                                      */
/****************************************************************************************************/
ULONG   uncal_MotSpdFbk( MONDEF *Undef )
{
LONG    val ;
    val = KpiMonSpeedCal( *Undef->Var.Plong ) ;
    return( MlibLimitul(val, 0x00007FFF, 0xFFFF8000)) ;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_SpdFbk = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MotSpdFbk,
/* 最小值                      */  (ULONG)&CoutV.UnMotSpd,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un001 : 速度指令(动作监视) [min-1, mm/s]                                                    */
/****************************************************************************************************/
ULONG   uncal_DispUnitSpeed( MONDEF *Undef )
{
    LONG    val ;
    val = KpiMonSpeedCal( *Undef->Var.Plong ) ;
    return( MlibLimitul(val, 0x00007FFF, 0xFFFF8000)) ;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_SpdRef = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_DispUnitSpeed,
/* 最小值                      */  (ULONG)&BoutV.UnSpdRef,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un002 : 内部转矩指令(动作监视) [%]                                                            */
/****************************************************************************************************/
ULONG   uncal_PercentTorque( MONDEF *Undef )
{
        return( KpiMonTorqueCal( *Undef->Var.Plong ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_TrqRef = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_PercentTorque,
/* 最小值                      */  (ULONG)&CoutV.UnTrqRef,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un004 : 电气角(U相0度)(动作监视) [deg]                                                       */
/****************************************************************************************************/
ULONG   uncal_MotAnglePhase( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MotAngDeg = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MotAnglePhase,
/* 最小值                      */  (ULONG)&CoutV.UnMotPhase,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un005 : 输入指令脉冲速度(仅位置控制有效)(动作监视) [min-1, mm/s]                           */
/****************************************************************************************************/
ULONG   uncal_PcmdSpeed( MONDEF *Undef )
{
    LONG    val ;
#if(FLOAT_USE == 1)
    val = (float)CoutV.UnPcmd64ms * Iprm.fKmonpcmdspd;           //64ms 平均
#else
    val = MlibMulgain( CoutV.UnPcmd64ms, Iprm.Kmonpcmdspd ) ;           //64ms 平均
    //val = MlibMulgain( CinK.dPcmdCnt, Iprm.Kmonpcmdspd2ms );          //2ms
#endif
    return( MlibLimitul(val, 0x00007FFF, 0xFFFF8000)) ;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_PosRefSpd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_VAL,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_PcmdSpeed,
/* 最小值                      */  (ULONG)&CoutV.UnPcmd64ms,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un006 : 输入指令脉冲计数器(动作监视) [指令单位]                                              */
/****************************************************************************************************/
ULONG   uncal_PcmdCounter( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_PcmdCounter = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_PcmdCounter,
/* 最小值                      */  (ULONG)&CoutRrst.UnPcmdCntr,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un007 : 电机反馈脉冲计数器 [指令单位]                                                        */
/****************************************************************************************************/
ULONG   uncal_Pfbk2Counter( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_Pfbk2Counter = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Pfbk2Counter,
/* 最小值                      */  (ULONG)&CoutRrst.UnPfbkCntr2,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un008 : 电机编码器反馈[编码器单位]                                                          */
/****************************************************************************************************/
ULONG   uncal_EncSTurnFbkCounter( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_EncSTurnFbk = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EncSTurnFbkCounter,
/* 最小值                      */  (ULONG)&CoutRrst.UnPfbkCntr,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un009 : 位置偏差量(仅位置控制有效)(动作监视) [pulse]                                                    */
/****************************************************************************************************/
ULONG   uncal_PerrCounter( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_PosErrCntr = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_PerrCounter,
/* 最小值                      */  (ULONG)&BoutV.AmonPosErra,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un00A : 累计负载率(动作监视) [%]                                                         */
/****************************************************************************************************/
ULONG   uncal_MotorLoad( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MotLoad = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MotorLoad,
/* 最小值                      */  (ULONG)&CoutV.UnIsqrSum,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un00B : 再生负载率(动作监视) [%]                                                         */
/****************************************************************************************************/
ULONG   uncal_RegenePerLoad( MONDEF *Undef )
{
        return( CoutV.UnMeanRgPower );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_RegLoad = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_RegenePerLoad,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0010 : 絶対値エンコーダ1回転内パルス                                                        */
/****************************************************************************************************/
CMONDEF undef_IncPulse = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUlong,
/* 最小值                      */  (ULONG)&RoutV.ABSEncSValue,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0011 : 絶対値エンコーダ多回転量                                                           */
/****************************************************************************************************/
CMONDEF undef_MultiTurn = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdShort,
/* 最小值                      */  (ULONG)&RoutV.ABSEncMValue,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un012 : 总运行时间(动作监视) [100ms]                                                     */
/****************************************************************************************************/
CMONDEF undef_PowerOnTime = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUlong,
/* 最小值                      */  (ULONG)&KnlV.TmStamp,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un014 : 有效增益监视(第1增益=1，第2增益=2) [－]                                               */
/****************************************************************************************************/
CMONDEF undef_ActGain = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&BoutV.ActGain,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un016 : 速度给定(负载端单位 rpm)                                               */
/****************************************************************************************************/
ULONG   uncal_SpeedRef( MONDEF *Undef )
{
LONG    val ;
    val = KpiMonSpeedCal( *Undef->Var.Plong ) ;
    return( MlibLimitul(val, 0x00007FFF, 0xFFFF8000)) ;
}
CMONDEF undef_SpeedRef = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_SpeedRef,
/* 最小值                      */  (ULONG)&CoutV.UnSpeedRef,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un017 : 速度反馈(负载端单位 rpm)                                                 */
/****************************************************************************************************/
ULONG   uncal_SpeedFbk( MONDEF *Undef )
{
LONG    val ;
    val = KpiMonSpeedCal( *Undef->Var.Plong ) ;
    return( MlibLimitul(val, 0x00007FFF, 0xFFFF8000)) ;
}
CMONDEF undef_SpeedFbk = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_SpeedFbk,
/* 最小值                      */  (ULONG)&CoutV.UnSpeedFbk,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un018 : 力矩给定(负载端单位 N·m)                                               */
/****************************************************************************************************/
ULONG   uncal_TorqueRef( MONDEF *Undef )
{
    return CoutV.UnTorqueRef;
}
CMONDEF undef_TorqueRef = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_TorqueRef,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un019 : 力矩反馈(负载端单位 N·m)                                              */
/****************************************************************************************************/
ULONG   uncal_TorqueFbk( MONDEF *Undef )
{
    return CoutV.UnTorqueFbk;
}
CMONDEF undef_TorqueFbk = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_TorqueFbk,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      Un01A : 粘滞摩擦系数辨识值 [×10-4N·ms/rad]                               */
/****************************************************************************************************/
CMONDEF undef_Friction = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&CoutV.Friction,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un01B : 在线惯量辨识值 [×10-4kgm2]                                                         */
/****************************************************************************************************/
CMONDEF undef_Intera = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&CoutV.Intera,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un020 : 全闭环反馈脉冲计数器(动作监视) [外部编码器脉冲单位]                                    */
/****************************************************************************************************/
CMONDEF undef_FposCounter = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&CoutRrst.UnFenseCnt2,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un021 : 光学尺反馈脉冲数  [编码器单位]                                                       */
/****************************************************************************************************/
CMONDEF undef_FenseFbkEnc = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&CoutRrst.UnFenseCnt1,
/* 最大值                          */  (ULONG)0
};




/****************************************************************************************************/
/*      Un022 : 全闭环反馈速度 [pulse/s]                                                           */
/****************************************************************************************************/
ULONG   uncal_FcFbkPulseSpeed( MONDEF *Undef )
{
LONG    lwk;

        lwk = 10 * (*Undef->Var.Plong);
        return( lwk );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_FcPfbkSpd = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_VAL,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_FcFbkPulseSpeed,
/* 最小值                          */  (ULONG)&CoutV.UnFpos100ms,
/* 最大值                          */  (ULONG)10
};

/****************************************************************************************************/
/*      Un023 : 光学尺全闭环和电机编码器的反馈位置偏差 [光栅尺脉冲单位]                               */
/****************************************************************************************************/
CMONDEF undef_FencePosErrCntr = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&CoutV.UnFposError,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un024 : 光学尺全闭环和电机编码器的反馈位置偏差 [用户单位]                                  */
/****************************************************************************************************/
CMONDEF undef_FenceErrCntrUser = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&AinK.MixUserErr,
/* 最大值                          */  (ULONG)0
};


/****************************************************************************************************/
/*      Un025 : 全闭环滑动补偿累加量 [用户单位]                                                       */
/****************************************************************************************************/
CMONDEF undef_FenceCompValue = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&CoutV.UnFposCompValue,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un026 : 光学尺绝对位置 [光学尺单位]                                                       */
/****************************************************************************************************/
CMONDEF undef_FenceAbsValue = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                          */  (ULONG)&FencV.FencAbsPos,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un027 : 负载端絶対値编码器多圈值                                                             */
/****************************************************************************************************/
CMONDEF undef_LoadMultiTurn = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdShort,
/* 最小值                      */  (ULONG)&FencV.FencMPos,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un02A : 内部信号状态监视1                                                                   */
/****************************************************************************************************/
ULONG   uncal_InternalSignal0( MONDEF *Undef )
{
ULONG   rv;
        rv =  UMONSETBIT( CoutV.f.Seq.MainPowerOn,      0   );          /* 主回路电压建立           */
        rv |= UMONSETBIT( CinK.f.EncReady,              1   );          /* 编码器准备好             */
        rv |= UMONSETBIT( CoutV.f.Sv.SvonReq,           2   );          /* 伺服ON请求               */
        rv |= UMONSETBIT( CoutV.f.Sv.DbOn,              3   );          /* 动态制动信号             */
        rv |= UMONSETBIT( Iprm.f.RvsDir,                4   );          /* 电机旋转方向             */
        rv |= UMONSETBIT( BoutV.f.ModeSWFlag,           5   );          /* 速度环控制方式           */
        rv |= UMONSETBIT( CoutV.f.Sv.Vrefon,            6   );          /* 电机旋转信号             */
        rv |= UMONSETBIT( CoutV.f.Sv.Trefon,            7   );          /* 最大转矩到达             */

        /*------------------------------------------------------------------------------------------*/
        /*  单轴 & 双轴机型                                                                            */
        /*  0: 单轴                                                                                  */
        /*  1: 双轴                                                                                  */
        /*------------------------------------------------------------------------------------------*/
        if( Kprm.f.AxisNum == 0 )
        {
            rv |= UMONSETBIT( 0, 14   );                                /* 单轴                      */
        }
        else
        {
            rv |= UMONSETBIT( 1, 14   );                                /* 双轴                     */
        }        
        return( rv );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_InterSignal0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_InternalSignal0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un02B : 内部信号状态监视2                                                                   */
/****************************************************************************************************/
ULONG   uncal_InternalSignal1( MONDEF *Undef )
{
ULONG   rv;
        rv =  UMONSETBIT( CinV.f.Seq.ServoOn,       0   );              /* 伺服使能                 */
        rv |= UMONSETBIT( CinV.f.Sv.Pot,            1   );              /* 正向限位                 */
        rv |= UMONSETBIT( CinV.f.Sv.Not,            2   );              /* 负向限位                 */
        rv |= UMONSETBIT( CinV.f.Seq.AlmReset,      3   );              /* 报警复位                 */
        rv |= UMONSETBIT( BinV.f.Ctrl.EnbPCtrl,     4   );              /* 速度环PI-P切换           */
        rv |= UMONSETBIT( BinV.f.Sv.TlimitSel,      5   );              /* 转矩限制选择             */
        rv |= UMONSETBIT( CinV.f.Sv.ABSEn,          6   );              /* 绝对位置信息请求         */
        rv |= UMONSETBIT( CinV.f.Sv.SpdD,           7   );              /* 速度方向                 */
        rv |= UMONSETBIT( CinV.f.Sv.SpdA,           8   );              /* 内部速度选择A            */
        rv |= UMONSETBIT( CinV.f.Sv.SpdB,           9   );              /* 内部速度选择B            */
        rv |= UMONSETBIT( CinV.f.Sv.Csel,           10  );              /* 控制模式选择             */
        rv |= UMONSETBIT( CinV.f.Sv.Zclamp,         11  );              /* 零速钳位                 */
        rv |= UMONSETBIT( BinV.f.Sv.Inhibit,        12  );              /* 脉冲禁止                 */
        rv |= UMONSETBIT( BinV.f.Sv.GainSel0,       13  );              /* 增益切换                 */
        rv |= UMONSETBIT( CinV.f.Sv.TorqD,          14  );              /* 转矩方向                 */
        rv |= UMONSETBIT( BinV.f.Sv.Psel,           15  );              /* 脉冲指令倍率             */
          
        return( rv );
}
CMONDEF undef_InterSignal1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_InternalSignal1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un02C : 内部信号状态监视3                                                                   */
/****************************************************************************************************/

ULONG   uncal_InternalSignal2( MONDEF *Undef )
{
ULONG   rv;

//        rv =  UMONSETBIT( BinV.f.Sv.PerClrSignal,   0   );              /* 脉冲偏差清除             */
//        rv |= UMONSETBIT( CinV.f.Sv.TorqA,          1   );              /* 转矩选择A                */
//        rv |= UMONSETBIT( CinV.f.Sv.TorqB,          2   );              /* 转矩选择B                */
//        rv |= UMONSETBIT( CinV.f.Sv.TCtrg,          3   );              /* 转矩触发                 */
//        rv |= UMONSETBIT( CinV.f.Sv.TSLimit,        4   );              /* 保留                     */
////      rv |= UMONSETBIT( CinV.f.Sv.FencS,          5   );              /* 全闭环/半闭环切换选择    */
//        rv |= UMONSETBIT( CinV.f.Sv.JOGP,           6   );              /* 正向点动                 */
//        rv |= UMONSETBIT( CinV.f.Sv.JOGN,           7   );              /* 负向点动                 */
//
//        rv |= UMONSETBIT( CinV.f.Sv.EmcyStop,       8   );              /* 紧急停机             */
//        rv |= UMONSETBIT( CinV.f.Sv.Csel2,          9  );               /* 控制模式切换         */
//        rv |= UMONSETBIT( CinV.f.Sv.CTrig,          10  );              /* 三种控制模式选择确认        */
//        rv |= UMONSETBIT( 0,                        11  );              /* 定时监控负载转矩触发        */
//        rv |= UMONSETBIT( 0,                        12  );              /* 预留                */
//        rv |= UMONSETBIT( CinV.f.Sv.ManualAutoMod,     13  );              /* 手动自动控制切换           */
//        rv |= UMONSETBIT( CinV.f.Sv.BKSel,          14  );              /* 抱闸输入                 */
//        rv |= UMONSETBIT( Pr_DICtrgV.f.CTRG,        15   );              /* 内部内置触发             */
//
//        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos0,     16   );              /* 内部位置0                */
//        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos1,     17  );              /* 内部位置1                */
//        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos2,     18  );              /* 内部位置2                */
//        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos3,     19  );              /* 内部位置3                */
//        rv |= UMONSETBIT( 0,                        20  );              /* 预留                   */
//        rv |= UMONSETBIT( 0,                        21  );              /* 预留                */
//        rv |= UMONSETBIT( BinV.f.Sv.ORGEn,          22  );              /* 原点回归使能             */
//        rv |= UMONSETBIT( BinV.f.Sv.ORGS,           23  );              /* 原点开关                 */
//        rv |= UMONSETBIT( CinV.f.Sv.ExFault,        24  );              /* 外部故障信号                 */

        rv =  UMONSETBIT( BinV.f.Sv.PerClrSignal,   0   );              /* 脉冲偏差清除             */
        rv |= UMONSETBIT( CinV.f.Sv.TorqA,          1   );              /* 转矩选择A                */
        rv |= UMONSETBIT( CinV.f.Sv.TorqB,          2   );              /* 转矩选择B                */
        rv |= UMONSETBIT( CinV.f.Sv.TCtrg,          3   );              /* 转矩触发                 */
        rv |= UMONSETBIT( CinV.f.Sv.ManualAutoMod,  4   );              /* 手动自动控制切换           */
//      rv |= UMONSETBIT( CinV.f.Sv.FencS,          5   );              /* 全闭环/半闭环切换选择    */
        rv |= UMONSETBIT( CinV.f.Sv.JOGP,           6   );              /* 正向点动                 */
        rv |= UMONSETBIT( CinV.f.Sv.JOGN,           7   );              /* 负向点动                 */
        rv |= UMONSETBIT( Pr_DICtrgV.f.CTRG,        8   );              /* 内部内置触发             */
        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos0,     9   );              /* 内部位置0                */
        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos1,     10  );              /* 内部位置1                */
        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos2,     11  );              /* 内部位置2                */
        rv |= UMONSETBIT( Pr_DICtrgV.DI.f.Pos3,     12  );              /* 内部位置3                */
        rv |= UMONSETBIT( BinV.f.Sv.ORGEn,          13  );              /* 原点回归使能             */
        rv |= UMONSETBIT( BinV.f.Sv.ORGS,           14  );              /* 原点开关                 */
        rv |= UMONSETBIT( CinV.f.Sv.ExFault,        15  );              /* 外部故障信号                 */

        return( rv );
}


CMONDEF undef_InterSignal2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_InternalSignal2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un02D : 内部信号状态监视4                                                                   */
/****************************************************************************************************/
ULONG   uncal_InternalSignal3( MONDEF *Undef )
{
ULONG   rv;
//        rv = UMONSETBIT( CoutV.f.Seq.ServoReady,    0   );              /* 伺服准备好               */
//        rv |= UMONSETBIT( BoutV.f.Ctrl.Coin,        1   );              /* 定位完成                 */
//        rv |= UMONSETBIT( CoutV.f.Ctrl.ReachSpd,    2   );              /* 速度一致                 */
//        rv |= UMONSETBIT( CoutV.f.Ctrl.MotorMoving, 3   );              /* 电机旋转                 */
//        rv |= UMONSETBIT( BoutV.f.Ctrl.TrqClamp,    4   );              /* 转矩限制中               */
//        rv |= UMONSETBIT( BoutV.f.Ctrl.SpdClamp,    5   );              /* 速度限制中               */
//        rv |= UMONSETBIT( CoutV.f.Seq.BrkReleasing, 6   );              /* 抱闸信号                 */
//        rv |= UMONSETBIT( Alm.f.WrnFlag,            7   );              /* 警告信号                 */
//        rv |= UMONSETBIT( BoutV.f.Sv.Near,          8   );              /* 位置接近                 */
//        rv |= UMONSETBIT( Iprm.PGAINSet == 1 ?
//                          1 :BoutV.f.Sv.PselA,        9 );              /* 指令脉冲输入倍率切换输出 */
//        rv |= UMONSETBIT( Alm.f.AlmFlag,            10  );              /* 故障信号                 */
//        rv |= UMONSETBIT( BoutV.f.Ctrl.TorqReach,   11  );              /* 目标转矩达到             */
//        rv |= UMONSETBIT( Obj60FE_01.f.Y1,          12  );              /* EtherCAT Y1输出       */
//        rv |= UMONSETBIT( Obj60FE_01.f.Y2,          13  );              /* EtherCAT Y2输出       */
//        rv |= UMONSETBIT( CoutV.f.Ctrl.JOGP,        14  );              /* 正向点动端子输出        */
//
//        rv |= UMONSETBIT( CoutV.f.Ctrl.JOGN,        15   );             /* 反向点动端子输出            */
//        rv |= UMONSETBIT( Pr_DICtrgV.f.CMDOK,       16   );             /* 指令发送完成              */
//        rv |= UMONSETBIT( Pr_DICtrgV.f.TPOS,        17   );             /* 指令完成                 */
//        rv |= UMONSETBIT( Pr_DICtrgV.f.MCOK,        18   );             /* 指令定位完成              */
//        rv |= UMONSETBIT( BoutV.f.Ctrl.SafetyStop,  19   );             /* STO输出                */
//        rv |= UMONSETBIT( CoutV.f.Ctrl.OrgC,        20   );             /* 原点回归完成              */

        rv = UMONSETBIT( CoutV.f.Seq.ServoReady,    0   );              /* 伺服准备好               */
        rv |= UMONSETBIT( BoutV.f.Ctrl.Coin,        1   );              /* 定位完成                 */
        rv |= UMONSETBIT( CoutV.f.Ctrl.ReachSpd,    2   );              /* 速度一致                 */
        rv |= UMONSETBIT( CoutV.f.Ctrl.MotorMoving, 3   );              /* 电机旋转                 */
        rv |= UMONSETBIT( BoutV.f.Ctrl.TrqClamp,    4   );              /* 转矩限制中               */
        rv |= UMONSETBIT( BoutV.f.Ctrl.SpdClamp,    5   );              /* 速度限制中               */
        rv |= UMONSETBIT( CoutV.f.Seq.BrkReleasing, 6   );              /* 抱闸信号                 */
        rv |= UMONSETBIT( Alm.f.WrnFlag,            7   );              /* 警告信号                 */
        rv |= UMONSETBIT( BoutV.f.Sv.Near,          8   );              /* 位置接近                 */
        rv |= UMONSETBIT( Iprm.PGAINSet == 1 ?
                          1 :BoutV.f.Sv.PselA,        9 );              /* 指令脉冲输入倍率切换输出 */
        rv |= UMONSETBIT( Alm.f.AlmFlag,            10  );              /* 故障信号                 */
        rv |= UMONSETBIT( BoutV.f.Ctrl.TorqReach,   11  );              /* 目标转矩达到             */
        rv |= UMONSETBIT( CoutV.f.Ctrl.OrgC,        12  );              /* 原点回归完成             */
        rv |= UMONSETBIT( BoutV.f.Ctrl.SafetyStop,  13   );             /* STO输出                */

        return( rv );
}
CMONDEF undef_InterSignal3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_InternalSignal3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un02E : Can状态                                                                               */
/****************************************************************************************************/
ULONG   uncal_CanStatus( MONDEF *Undef )
{
ULONG   rv = 0;
//ULONG rv = CanStatus( );    20221230
UCHAR   ErrorFlag   = rv & 0x07;                                /* 错误标志                         */
UCHAR   ErrorSTatus = ( rv >> 4 ) & 0x07;                       /* 上一个错误代码                   */
UCHAR   ReciveErrCnt= ( rv >> 24) & 0xFF;                       /* 接收错误计数器                   */
        return( (ReciveErrCnt << 8) | ( ErrorSTatus << 4 ) | ( ErrorFlag ) );
}
CMONDEF undef_CanStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CanStatus,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un02F : Can 当前命令状态                                                                      */
/****************************************************************************************************/
CMONDEF undef_CanCmdStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&CanVar.CanCmdStatus,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un030 : 伺服驱动器运行状态                                                                   */
/****************************************************************************************************/
CMONDEF undef_ServoStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&KnlV.ServoStatus,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      Un031 : CanOpen运行状态                                                                     */
/****************************************************************************************************/
ULONG   uncal_CanOpenStatus( MONDEF *Undef )
{
ULONG   rv;
        rv  = UMONSETBIT( CanVar.NMTV.f.SDO_En,         0   );              /* SDO                  */
        rv |= UMONSETBIT( CanVar.NMTV.f.PDO_En,         1   );              /* PDO                  */
        rv |= UMONSETBIT( CanVar.NMTV.f.ConsumHeart,    2   );              /* 消费者心跳           */
        rv |= UMONSETBIT( CanVar.NMTV.f.PoroduHeart,    3   );              /* 生产者心跳           */
        rv |= UMONSETBIT( OD_V.EMCY_En,                 4   );              /* 紧急报文             */
        rv |= UMONSETBIT( OD_V.SYNC_En,                 5   );              /* 同步                 */
        /*------------------------------------------------------------------------------------------*/
        rv |= ((CanVar.NMTV.f.NMTStatus & 0xFF ) << 8 );                    /* 网络状态             */
        return( rv );
}
            
CMONDEF undef_CanOpenStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CanOpenStatus,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un032 : EtherCAT运行状态                                                                    */
/****************************************************************************************************/
ULONG   uncal_EtherCatStatus( MONDEF *Undef )
{
    ULONG Kx;
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        Kx = EtherCAT_StatusMonitor();
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                    */
        Kx = (CanVar.NMTStatus <<4 )| ODDatArr[Operation_Mode].byte.FirstByte;
    else
        Kx = 0;
        return( Kx );
}
CMONDEF undef_EtherCATStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCatStatus,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un033 : EtherCAT 同步周期时间                                                             */
/****************************************************************************************************/
ULONG   uncal_EtherCatSynch( MONDEF *Undef )
{
ULONG Kx;
        Kx = EtherCat_Sync0CycleTime();
        return( Kx );
}
CMONDEF undef_EtherCATSynch = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  3,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCatSynch,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un033 : EtherCAT 同步帧异常计数器                                                           */
/****************************************************************************************************/
ULONG   uncal_EtherCatSynchCnt( MONDEF *Undef )
{
ULONG Kx = 0;
//        Kx = SynthErrCnt;    20221230
        return( Kx );
}
CMONDEF undef_EtherCATSynchCnt = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCatSynchCnt,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un035 : MCU版本号                                                                          */
/****************************************************************************************************/
ULONG   uncal_ARMVersion( MONDEF *Undef )
{
USHORT ID = 0;
    if( SystemVar.OrderID != 0 )
    {
        ID = SystemVar.McuVer + 10000;
    }
    else
    {
        ID = SystemVar.McuVer;
    }
    return( ID );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_ARMVersion = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ARMVersion,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un036 : FPGA版本号                                                                         */
/****************************************************************************************************/
ULONG   uncal_FPGAVersion( MONDEF *Undef )
{
        return( SystemVar.FpgaVer );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_FPGAVersion = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_FPGAVersion,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un037 : ARM 副版本号                                                                        */
/****************************************************************************************************/
ULONG   uncal_ARMSubVersion( MONDEF *Undef )
{
        return( SystemVar.OrderID );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MCUSubVersion = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ARMSubVersion,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*		Un038 : CPU2_BOOT版本号														                */
/****************************************************************************************************/
ULONG	uncal_FPGASubVersion( MONDEF *Undef )
{
        return(uint16_t)((*(uint32_t*)0x0003B250UL));
}

/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_FPGASubVersion = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_FPGASubVersion,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un039 : EtherCAT站点正名                                                                    */
/****************************************************************************************************/
ULONG   uncal_EtherCATStationName1( MONDEF *Undef )
{
USHORT DataTmp = EtherCAT_StationMonitor( 0 );
        return DataTmp;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_EtherCATName1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCATStationName1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un03A : EtherCAT站点别名                                                                    */
/****************************************************************************************************/
ULONG   uncal_EtherCATStationName2( MONDEF *Undef )
{
USHORT DataTmp = EtherCAT_StationMonitor( 1 );
        return DataTmp;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_EtherCATName2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCATStationName2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un03B : AL 状态值                                                                              */
/****************************************************************************************************/
ULONG   uncal_EtherCATALStatus( MONDEF *Undef )
{
USHORT DataTmp;
    DataTmp = EtherCAT_ALStatus( );
    return DataTmp;
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_EtherCATALStatus = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_EtherCATALStatus,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un03C : Sn序列                                                                              */
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/


CMONDEF undef_SnNum = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUlong,
/* 最小值                      */  (ULONG)&SystemVar.SnNum,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un040 : Author                                                                              */
/****************************************************************************************************/
CMONDEF undef_SysAuthor = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&SystemVar.Author,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un041 : 系统日期                                                                            */
/****************************************************************************************************/
ULONG   uncal_SysDate( MONDEF *Undef )
{
    return System_Year;
}    
CMONDEF undef_SysDate = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_SysDate,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

  
/****************************************************************************************************/
/*      Un042 : 系统时间                                                                            */
/****************************************************************************************************/
ULONG   uncal_SysTime( MONDEF *Undef )
{
    return System_Time;
} 
CMONDEF undef_SysTime = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_SysTime,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un043 : Boot 版本信息                                                                         */
/****************************************************************************************************/
ULONG   uncal_BootVersion( MONDEF *Undef )
{
    return (uint16_t)((*(uint32_t*)0x00085FF0UL));
}
CMONDEF undef_BootVersion = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_BootVersion,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un045 : 端口0 无效帧计数                                                                           */
/****************************************************************************************************/
CMONDEF undef_Un045 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un045,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un046 : 端口0 接收错误计数                                                                      */
/****************************************************************************************************/
CMONDEF undef_Un046 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un046,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un047 : 端口1 无效帧计数                                                                           */
/****************************************************************************************************/
CMONDEF undef_Un047 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un047,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un048 : 端口1 接收错误计数                                                                      */
/****************************************************************************************************/
CMONDEF undef_Un048 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un048,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un049 : 端口0 转发错误计数                                                                      */
/****************************************************************************************************/
CMONDEF undef_Un049 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un049,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un04A : 端口1 转发错误计数                                                                      */
/****************************************************************************************************/
CMONDEF undef_Un04A = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un04A,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un04B : 数据帧处理单元错误计数                                                                 */
/****************************************************************************************************/
CMONDEF undef_Un04B = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un04B,
/* 最大值                      */  (ULONG)0
};

    
/****************************************************************************************************/
/*      Un04C : PDI 错误计数计数                                                                          */
/****************************************************************************************************/
CMONDEF undef_Un04C = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un04C,
/* 最大值                      */  (ULONG)0
};    
    
/****************************************************************************************************/
/*      Un04D : 端口0链接丢失计数                                                                       */
/****************************************************************************************************/
CMONDEF undef_Un04D = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un04D,
/* 最大值                      */  (ULONG)0
};

    
/****************************************************************************************************/
/*      Un04E : 端口1链接丢失计数                                                                       */
/****************************************************************************************************/
CMONDEF undef_Un04E = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 处理函数指针                 */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&DataLinkV.Un04E,
/* 最大值                      */  (ULONG)0
};    
    


/****************************************************************************************************/
/*      Un100 : IO口输入信号监视(输入信号监视) [－]                                                           */
/****************************************************************************************************/
ULONG   uncal_InputSignal( MONDEF *Undef )
{
        return( KpiMonInputSignal( ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_InSignal = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEBIT,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_InputSignal,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un101 : IO口输出信号监视(输出信号监视) [－]                                                           */
/****************************************************************************************************/
ULONG   uncal_OutputSignal( MONDEF *Undef )
{
        return( KpiMonOutputSignal( ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_OutSignal = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEBIT,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_OutputSignal,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un087 : 串行编码器通信异常次数                                                                 */
/****************************************************************************************************/
CMONDEF undef_SencComErrCnt = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&MencV.ComErrCnt,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un105 : 位置整定时间 [0.1ms]                                                                  */
/****************************************************************************************************/
ULONG   uncal_SettlingTime( MONDEF *Undef )
{
        return( (*Undef->Var.Pulong) * KPI_SBCYCLEUS / 100 );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_SettlingTime = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_SettlingTime,
/* 最小值                      */  (ULONG)&BoutV.UnSettlingTime,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un106 : 位置超调量 [指令单位]                                                                    */
/****************************************************************************************************/
ULONG   uncal_MaxOverShoot( MONDEF *Undef )
{
        return( (*Undef->Var.Pulong) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_OverShoot = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MaxOverShoot,
/* 最小值                      */  (ULONG)&BoutV.UnMaxOverShoot,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un089 : 散热片温度 [0.1℃]                                                                        */
/****************************************************************************************************/
CMONDEF undef_HeatsinkTemp = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&CoutV.UnHeatSinkTemp,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un10C : 电机温度传感器检测值 [0.1℃]                                                                        */
/****************************************************************************************************/
CMONDEF undef_HeatMotTemp = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&CoutV.UnHeatMotTemp,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un10D : 环境温度温度 [0.1℃]                                                                   */
/****************************************************************************************************/
ULONG   uncal_envirtemp( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_EnvirTemperature = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_envirtemp,
/* 最小值                      */  (ULONG)&CoutV.UnEnvirTemp,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un140 : P-N 电压监控 [V]                                                                        */
/****************************************************************************************************/
ULONG   uncal_DcVoltx( MONDEF *Undef )
{
        return( *Undef->Var.Pulong );
}
CMONDEF undef_DcVoltx = {
/* :1: 数据类型(0:16位;1:32位)  */FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */DSPDEF_NOSIGN,
/* :3: 小数点的位数               */0,
/* :1: 变量是否可清除          */MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */NONEDSP_DISABLE,
/* :X: 保留                       */0,
/* 専用使用チェック             */KPI_CHKSPUSE_COMMON,
/* 用户权限                     */ACCLVL_USER1,
/* 処理関数ポインタ             */uncal_DcVoltx,
/* 最小值                      */(ULONG)&BinK.UnDcVolt,
/* 最大值                      */(ULONG)0
};



/****************************************************************************************************/
/*      Un141 : 电流检测值 [0.01A]                                                                       */
/****************************************************************************************************/
ULONG   uncal_IqRate( MONDEF *Undef )
{
    return( KpiMonCurrentCal1( *Undef->Var.Plong ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_IqRate = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_IqRate,
/* 最小值                      */  (ULONG)&CoutV.UnCrntDet,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un142 : 累计负载率 [%（周期2ms）]                                                                */
/****************************************************************************************************/
ULONG   uncal_MotLoad2ms( MONDEF *Undef )
{
        return( KpiMonCurrentCal( *Undef->Var.Plong ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MotLoad2ms = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MotLoad2ms,
/* 最小值                      */  (ULONG)&CoutV.UnCrntRef,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un143 : 再生负载累加值 [0.1%]                                                                  */
/****************************************************************************************************/
ULONG   uncal_RegenePerLoad2ms( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_RegerRate2ms = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_RegenePerLoad2ms,
/* 最小值                      */  (ULONG)&CoutV.UnRgPower,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un144 : DB电阻消耗电力 [0.1%]                                                                 */
/****************************************************************************************************/
ULONG   uncal_DbrxPerPower2ms( MONDEF *Undef )
{
        return( CoutV.UnDbPower );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_DbrxPower2ms = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_DbrxPerPower2ms,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un145 : 累计负载率(动作监视) [%]                                                                 */
/****************************************************************************************************/
ULONG   uncal_MotorTrgLoad( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MotTrgLoad = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MotorTrgLoad,
/* 最小值                      */  (ULONG)&CoutV.UnIsqrSum1,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un150 : AI1检测值 [0.001V] 未矫正前                                                        */
/****************************************************************************************************/
ULONG   uncal_AI1Channel0( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AI1Channel0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AI1Channel0,
/* 最小值                          */  (ULONG)&AdcV.ADCChannel10,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un151 : AI2检测值 [0.001V] 未矫正前                                                        */
/****************************************************************************************************/
ULONG   uncal_AI2Channel0( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AI2Channel0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  3,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AI2Channel0,
/* 最小值                          */  (ULONG)&AdcV.ADCChannel20,
/* 最大值                          */  (ULONG)0
};


/****************************************************************************************************/
/*      Un152 : AI1检测值 [0.001V] 未矫正后                                                        */
/****************************************************************************************************/
ULONG   uncal_AI1Channel1( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AI1Channel1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AI1Channel1,
/* 最小值                          */  (ULONG)&AdcV.ADCChannel11,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un153 : AI2检测值 [0.001V] 未矫正后                                                        */
/****************************************************************************************************/
ULONG   uncal_AI2Channel1( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AI2Channel1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  3,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AI2Channel1,
/* 最小值                          */  (ULONG)&AdcV.ADCChannel21,
/* 最大值                          */  (ULONG)0
};




/****************************************************************************************************/
/*      Un160 : MIT转矩前馈                                                       */
/****************************************************************************************************/
ULONG   uncal_MIT_TorqCmd( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_TorqCmd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_TorqCmd,
/* 最小值                          */  (ULONG)&MIT.TorqCmd,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un161 : MIT_AngleCmd                                                      */
/****************************************************************************************************/
ULONG   uncal_MIT_AngleCmd( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_AngleCmd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_AngleCmd,
/* 最小值                          */  (ULONG)&MIT.AngleCmd,
/* 最大值                          */  (ULONG)0
};


/****************************************************************************************************/
/*      Un162 : MIT_VelCmd                                                      */
/****************************************************************************************************/
ULONG   uncal_MIT_VelCmd( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_VelCmd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_VelCmd,
/* 最小值                          */  (ULONG)&MIT.VelCmd,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un163 : MIT_KpValCmd                                                        */
/****************************************************************************************************/
ULONG   uncal_MIT_KpValCmd( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_KpValCmd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_KpValCmd,
/* 最小值                          */  (ULONG)&MIT.KpValCmd,
/* 最大值                          */  (ULONG)0
};


/****************************************************************************************************/
/*      Un164 : MIT_KdValCmd                                                        */
/****************************************************************************************************/
ULONG   uncal_MIT_KdValCmd( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_KdValCmd = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_KdValCmd ,
/* 最小值                          */  (ULONG)&MIT.KdValCmd ,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un165 : MIT_AngleFeb                                                       */
/****************************************************************************************************/
ULONG   uncal_MIT_AngleFeb( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_AngleFeb = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_AngleFeb,
/* 最小值                          */  (ULONG)&MIT.AngleFeb,
/* 最大值                          */  (ULONG)0
};

/****************************************************************************************************/
/*      Un166 : MIT_VelFeb                                                     */
/****************************************************************************************************/
ULONG   uncal_MIT_VelFeb( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_VelFeb = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_VelFeb,
/* 最小值                          */  (ULONG)&MIT.VelFeb,
/* 最大值                          */  (ULONG)0
};


/****************************************************************************************************/
/*      Un167 : MIT_TorqFeb                                                    */
/****************************************************************************************************/
ULONG   uncal_MIT_TorqFeb( MONDEF *Undef )
{
    return( *Undef->Var.Pshort );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MIT_TorqFeb = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MIT_TorqFeb,
/* 最小值                          */  (ULONG)&MIT.TorqFeb,
/* 最大值                          */  (ULONG)0
};





/****************************************************************************************************/
/*      Un203 : 设定异常参数号(A.040)                                                                  */
/****************************************************************************************************/
CMONDEF undef_ErrPrmNo = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&Alm.PrmErrInfo.ErrPrmNo,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      Un212 : ScanA現在処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_CurExeTimeA = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.CurExeTimeA,
/* 最大值                      */  (ULONG)0x00010001
};



/****************************************************************************************************/
/*      Un213 : ScanA最大処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_MaxExeTimeA = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.MaxExeTimeA,
/* 最大值                      */  (ULONG)0x00010001
};



/****************************************************************************************************/
/*      Un214 : ScanB現在処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_CurExeTimeB = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.CurExeTimeB,
/* 最大值                      */  (ULONG)0x00010001
};



/****************************************************************************************************/
/*      Un215 : ScanB最大処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_MaxExeTimeB = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.MaxExeTimeB,
/* 最大值                      */  (ULONG)0x00010001
};


/****************************************************************************************************/
/*      Un216 : ScanC現在処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_CurExeTimeC = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.CurExeTimeC,
/* 最大值                      */  (ULONG)0x00010001
};


/****************************************************************************************************/
/*      Un217 : ScanC最大処理時間 [0.1us]                                                             */
/****************************************************************************************************/
CMONDEF undef_MaxExeTimeC = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  1,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.MaxExeTimeC,
/* 最大值                      */  (ULONG)0x00010001
};


/****************************************************************************************************/
/*      Un218 : Round現在処理時間 [1us]                                                                   */
/****************************************************************************************************/
CMONDEF undef_CurExeTimeR = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.CurExeTimeR,
/* 最大值                      */  (ULONG)0x0001000A
};


/****************************************************************************************************/
/*      Un219 : Round最大処理時間 [1us]                                                                   */
/****************************************************************************************************/
CMONDEF undef_MaxExeTimeR = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  2,
/* :1: 变量是否可清除          */  MONDEF_CLR_ENABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScanExeTime,
/* 最小值                      */  (ULONG)&KnlV.MaxExeTimeR,
/* 最大值                      */  (ULONG)0x0001000A
};


/****************************************************************************************************/
/*      0x0300 : Pr当前执行的编号 [－]                                                                  */
/****************************************************************************************************/
CMONDEF undef_PrCurrentNum = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&Pr_DICtrgV.MonitorPosNum,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0400 : 对象字典603Fh                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj603F( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16ErrCode );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Error_Code ].all);
    else
        return 0;
}
CMONDEF undef_Obj603F = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj603F,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0401 : 对象字典6040h                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj6040( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16ControlWord );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Control_Word ].all);
    else
        return 0;
}
CMONDEF undef_Obj6040 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6040,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0402 : 对象字典6041h                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj6041( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16StatusWord );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Status_Word ].all);
    else
        return 0;
}
CMONDEF undef_Obj6041 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6041,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0403 : 对象字典605Ah                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj605A( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16QuickShutdownOpt );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Quick_stop_option_code ].all);
    else
        return 0;
}
CMONDEF undef_Obj605A = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj605A,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0403 : 对象字典605Dh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj605D( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16HaltOptioncode );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Halt_option_code ].all);
    else
        return 0;
}
CMONDEF undef_Obj605D = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj605D,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0403 : 对象字典6060h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6060( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s8ModeofOP );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Operation_Mode ].all);
    else
        return 0;
}
CMONDEF undef_Obj6060 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6060,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0404 : 对象字典6061h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6061( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s8ModeofOPDis );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Operation_Mode_Display ].all);
    else
        return 0;
}
CMONDEF undef_Obj6061 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6061,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0405 : 对象字典6062h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6062( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32PosDemandValPUU );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Demand_Value_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6062 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6062,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0406 : 对象字典6063h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6063( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32PosActValInc );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Actual_Value_PUU ].all);
    else
        return 0;
}
CMONDEF undef_Obj6063 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6063,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0407 : 对象字典6064h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6064( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32PosActVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Actual_Value_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6064 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6064,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0408 : 对象字典6065h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6065( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32FollowErrWind );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Follow_Error_Window_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6065 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6065,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0409 : 对象字典6067h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6067( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32PosWindow );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Window_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6067 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6067,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040A : 对象字典6068h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6068( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16PosWindowTime );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Window_Time_MS ].all);
    else
        return 0;
}
CMONDEF undef_Obj6068 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6068,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040B : 对象字典606Bh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj606B( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32VelDemandVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Velocity_Demand_Value_RPM ].all);
    else
        return 0;
}
CMONDEF undef_Obj606B = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj606B,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040C : 对象字典606Ch                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj606C( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32VelActualVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ OD_606C ].sall);
    else
        return 0;
}
CMONDEF undef_Obj606C = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj606C,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040D : 对象字典606Dh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj606D( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16VelWindow );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Velocity_Window_RPM ].all);
    else
        return 0;
}
CMONDEF undef_Obj606D = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj606D,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040E : 对象字典606Eh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj606E( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16VelWindowTime );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Velocity_Window_Time_MS ].all);
    else
        return 0;
}
CMONDEF undef_Obj606E = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj606E,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x040F : 对象字典606Fh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj606F( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16Velthresd );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Zero_Velocity_Threshold ].all);
    else
        return 0;
}
CMONDEF undef_Obj606F = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj606F,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0410 : 对象字典6070h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6070( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16VelthresdTime );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Zero_Velocity_Time_MS ].all);
    else
        return 0;
}
CMONDEF undef_Obj6070 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6070,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0411 : 对象字典6071h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6071( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16TargTorq );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Target_Torque ].all);
    else
        return 0;
}
CMONDEF undef_Obj6071 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6071,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0412 : 对象字典6072h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6072( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16MaxTorq );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Max_Torque ].word.LowWord);
    else
        return 0;
}
CMONDEF undef_Obj6072 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6072,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0413 : 对象字典6074h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6074( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16TorqDemandVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Torque_Demand_Value ].all);
    else
        return 0;
}
CMONDEF undef_Obj6074 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6074,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0414 : 对象字典6075h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6075( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MotorRateCur );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Motor_Rated_Current_MA ].all);
    else
        return 0;
}
CMONDEF undef_Obj6075 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6075,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0415 : 对象字典6076h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6076( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MotorRateTorq );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Motor_Rated_Torque_MNM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6076 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6076,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0416 : 对象字典6077h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6077( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16TorqActVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Torque_Actual_Value ].all);
    else
        return 0;
}
CMONDEF undef_Obj6077 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6077,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0417 : 对象字典607Ah                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj607A( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TargetPos );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Targe_Position_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj607A = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607A,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0418 : 对象字典607Ch                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj607C( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32HomeOffset );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Homing_Offset_MM ].all);
    else
        return 0;
}
CMONDEF undef_Obj607C = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607C,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0419 : 对象字典607Dh 01                                                                   */
/****************************************************************************************************/
ULONG   uncal_Obj607D_1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( SoftPosLimit.aEntries[0] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Min_Soft_Posi_Limit ].all);
    else
        return 0;
}
CMONDEF undef_Obj607D_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607D_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x041A : 对象字典607Dh 02                                                                   */
/****************************************************************************************************/
ULONG   uncal_Obj607D_2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( SoftPosLimit.aEntries[1] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Max_Soft_Posi_Limit ].all);
    else
        return 0;
}
CMONDEF undef_Obj607D_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607D_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x041B : 对象字典607Eh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj607E( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u8Polarity );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Polarity ].all);
    else
        return 0;
}
CMONDEF undef_Obj607E = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607E,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x041C : 对象字典607Fh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj607F( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MaxProfileVel );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Max_Profile_Velocity ].all);
    else
        return 0;
}
CMONDEF undef_Obj607F = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj607F,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x041D : 对象字典6080h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6080( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MaxMotorSpd );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Max_Motor_Speed_RPM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6080 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6080,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x041E : 对象字典6081h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6081( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32ProfileVel );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Profile_Velocity_RPM ].all);
    else
        return 0;
}
CMONDEF undef_Obj6081 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6081,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x041F : 对象字典6083h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6083( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32ProfileAcc );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Profile_Acceleration ].all);
    else
        return 0;
}
CMONDEF undef_Obj6083 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6083,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0420 : 对象字典6084h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6084( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32ProfileDec );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Profile_Deceleration ].all);
    else
        return 0;
}
CMONDEF undef_Obj6084 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6084,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0420 : 对象字典6085h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6085( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32QuickStopDec );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Quick_Stop_Deceleration ].all);
    else
        return 0;
}
CMONDEF undef_Obj6085 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6085,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0421 : 对象字典6086h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6086( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16MotionProfileType );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Motion_Profile_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj6086 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6086,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0422 : 对象字典6087h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6087( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32TorqueSlope );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Torque_Slope_MS ].all);
    else
        return 0;
}
CMONDEF undef_Obj6087 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6087,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0423 : 对象字典6091h    01                                                                */
/****************************************************************************************************/
ULONG   uncal_Obj6091_1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( PositionFactor.aEntries[0] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Factor_Numer].all);
    else
        return 0;
}
CMONDEF undef_Obj6091_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6091_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0424 : 对象字典6091h    02                                                                */
/****************************************************************************************************/
ULONG   uncal_Obj6091_2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( PositionFactor.aEntries[1] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_Factor_Divisor ].all);
    else
        return 0;
}
CMONDEF undef_Obj6091_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6091_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x042D : 对象字典6098h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj6098( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s8HomingMethod );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Homing_Method ].all);
    else
        return 0;
}
CMONDEF undef_Obj6098 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6098,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x042E : 对象字典6099h    01                                                                */
/****************************************************************************************************/
ULONG   uncal_Obj6099_1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( HomingSpeed.aEntries[0] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Search_Switch_Spd ].all);
    else
        return 0;
}
CMONDEF undef_Obj6099_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6099_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x042F : 对象字典6099h    02                                                                */
/****************************************************************************************************/
ULONG   uncal_Obj6099_2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( HomingSpeed.aEntries[1] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Search_Zero_Spd ].all);
    else
        return 0;
}
CMONDEF undef_Obj6099_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6099_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0430 : 对象字典609Ah                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj609A( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32HomingAcc );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Homing_Acceleration ].all);
    else
        return 0;
}
CMONDEF undef_Obj609A = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj609A,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0431 : 对象字典60B0h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60B0( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32PositionOffset );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Postion_Offset ].all);
    else
        return 0;
}
CMONDEF undef_Obj60B0 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60B0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0432 : 对象字典60B1h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60B1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32VelocityOffset );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Spd_Offset ].all);
    else
        return 0;
}
CMONDEF undef_Obj60B1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60B1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0433 : 对象字典60B2h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60B2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s16TorqueOffset );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Torque_Offset ].all);
    else
        return 0;
}
CMONDEF undef_Obj60B2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60B2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0434 : 对象字典60B8h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60B8( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16TouchProbeFun );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
         return(ODDatArr[  TouchProbe_Fun ].all);
    else
        return 0;
}
CMONDEF undef_Obj60B8 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60B8,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0435 : 对象字典60B9h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60B9( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16TouchProbeSts );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  TouchProbe_Sts ].all);
    else
        return 0;
}
CMONDEF undef_Obj60B9 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60B9,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0436 : 对象字典60BAh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60BA( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TouchProbePos1PVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  TouchProbePos1_PVal ].all);
    else
        return 0;
}
CMONDEF undef_Obj60BA = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60BA,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0437 : 对象字典60BBh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60BB( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TouchProbePos1NVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  TouchProbePos1_NVal ].all);
    else
        return 0;
}
CMONDEF undef_Obj60BB = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60BB,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0438 : 对象字典60BCh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60BC( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TouchProbePos2PVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  TouchProbePos2_PVal ].all);
    else
        return 0;
}
CMONDEF undef_Obj60BC = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60BC,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0439 : 对象字典60BDh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60BD( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TouchProbePos2NVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  TouchProbePos2_NVal ].all);
    else
        return 0;
}
CMONDEF undef_Obj60BD = {
/* :1: 数据类型(0:16位;1:32位) */ TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                   */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60BD,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0436 : 对象字典60C5h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60C5( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MaxAcc );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return( ODDatArr[  Max_Acceleration ].all );
    else
        return 0;
}
CMONDEF undef_Obj60C5 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60C5,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0436 : 对象字典60C6h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60C6( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32MaxDec );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return( ODDatArr[  Max_Deceleration ].all );
    else
        return 0;
}
CMONDEF undef_Obj60C6 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60C6,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x043E : 对象字典60E0h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60E0( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16PositTorqLimit );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  OD_60E0 ].all);
    else
        return 0;
}
CMONDEF undef_Obj60E0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60E0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x043F : 对象字典60E1h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60E1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16NegtiTorqLimit );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  OD_60E1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj60E1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60E1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0440 : 对象字典60F2h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60F2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u16PositionOptCode );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Position_Optin ].all);
    else
        return 0;
}
CMONDEF undef_Obj60F2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60F2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0441 : 对象字典60F4h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60F4( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32FollowErrActVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Follow_Error_Actual_Value ].all);
    else
        return 0;
}
CMONDEF undef_Obj60F4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60F4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0442 : 对象字典60FCh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60FC( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32PosDemandVal );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Postion_Demand_Value ].all);
    else
        return 0;
}
CMONDEF undef_Obj60FC = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60FC,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0443 : 对象字典60FDh                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60FD( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32DigitalInput );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Digitial_Input ].all);
    else
        return 0;
}
CMONDEF undef_Obj60FD = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60FD,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0444 : 对象字典60FEh      01                                                              */
/****************************************************************************************************/
ULONG   uncal_Obj60FE_1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32DigitOutput.aEntries[0] );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Physical_Digitial_Output ].all);
    else
        return 0;
}
CMONDEF undef_Obj60FE_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60FE_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0445 : 对象字典60FFh                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj60FF( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( s32TargetVel );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Target_Velocity_RPM ].all);
    else
        return 0;
}
CMONDEF undef_Obj60FF = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60FF,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0446 : 对象字典6502h                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj6502( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( u32SuppDriveModes );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Drive_Mode_Support ].all);
    else
        return 0;
}
CMONDEF undef_Obj6502 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj6502,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      Un447 : 对象字典60C1h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60C1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( InterPolDataRecord.u32PosCmd );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Position_CMD_Lowword].all);
    else
        return 0;
}
CMONDEF undef_Obj60C1 = {
/* :1: 数据类型(0:16位;1:32位) */ TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                   */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60C1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*     Un448 : 对象字典60C2_1h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60C2_1( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( InterPolTimePeriod.u8InterpolationPeriod );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Interpolation_Period_Unit].all);
    else
        return 0;
}
CMONDEF undef_Obj60C2_1 = {
/* :1: 数据类型(0:16位;1:32位) */ FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                   */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60C2_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      Un449 : 对象字典60C2_2h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj60C2_2( MONDEF *Undef )
{
    if( Kprm.f.EtherCATNet == 1 )                               /* EtherCAT 机型                    */
        return( InterPolTimePeriod.i8InterpolationIndex );
    else if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ Interpolation_Period_Index].all);
    else
        return 0;
}
CMONDEF undef_Obj60C2_2 = {
/* :1: 数据类型(0:16位;1:32位) */ FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                   */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj60C2_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      Un450 : 对象字典1000h                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1000( MONDEF *Undef )
{
    if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  DeiviceType ].all);
    else
        return 0;
}
CMONDEF undef_Obj1000 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1000,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0451 : 对象字典1018_1h                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1018_1( MONDEF *Undef )
{
    if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Producer_Vendor_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1018_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1018_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0452 : 对象字典1018_2h                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1018_2( MONDEF *Undef )
{
    if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Producer_Code ].all);
    else
        return 0;
}
CMONDEF undef_Obj1018_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1018_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0453 : 对象字典1018_3h                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1018_3( MONDEF *Undef )
{
    if( Kprm.f.CanOpenNet == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[  Revision_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1018_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1018_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0454 : TPDO1映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1A00_0( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A00_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A00_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0455 : TPDO1映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A00_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 && (ODDatArr[PDO1_Trans_Map_Num].all >= 1) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A00_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A00_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0456 : TPDO1映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A00_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 && (ODDatArr[PDO1_Trans_Map_Num].all >= 2) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A00_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A00_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0457 : TPDO1映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A00_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 && (ODDatArr[PDO1_Trans_Map_Num].all >= 3) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A00_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A00_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0458 : TPDO1映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A00_4( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 && (ODDatArr[PDO1_Trans_Map_Num].all >= 4) )             /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A00_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A00_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0459 : TPDO1站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1800_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1800_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1800_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x045A : TPDO1传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1800_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1800_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1800_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x045B : TPDO1禁止时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1800_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Inhibt_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1800_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1800_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x045C : TPDO1事件时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1800_5( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Trans_Event_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1800_5 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1800_5,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};




/****************************************************************************************************/
/*      0x0460 : TPDO2映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1A01_0( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A01_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A01_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0461 : TPDO2映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A01_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 && (ODDatArr[PDO2_Trans_Map_Num].all >= 1) )             /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A01_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A01_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0462 : TPDO2映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A01_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 && (ODDatArr[PDO2_Trans_Map_Num].all >= 2) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A01_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A01_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0463 : TPDO2映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A01_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 && (ODDatArr[PDO2_Trans_Map_Num].all >= 3) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A01_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A01_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0464 : TPDO2映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A01_4( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 && (ODDatArr[PDO2_Trans_Map_Num].all >= 4) )              /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A01_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A01_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0465 : TPDO2站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1801_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1801_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1801_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0466 : TPDO2传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1801_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1801_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1801_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0467 : TPDO2禁止时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1801_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Inhibt_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1801_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1801_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0468 : TPDO2事件时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1801_5( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Trans_Event_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1801_5 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1801_5,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0469 : TPDO3映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1A02_0( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A02_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A02_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046A : TPDO3映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A02_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 && (ODDatArr[PDO3_Trans_Map_Num].all >= 1) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A02_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A02_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046B : TPDO3映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A02_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 && (ODDatArr[PDO3_Trans_Map_Num].all >= 2) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A02_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A02_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046C : TPDO3映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A02_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 && (ODDatArr[PDO3_Trans_Map_Num].all >= 3) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A02_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A02_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046D : TPDO3映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A02_4( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 && (ODDatArr[PDO3_Trans_Map_Num].all >= 4) )             /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A02_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A02_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046E : TPDO3站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1802_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1802_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1802_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x046F : TPDO3传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1802_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1802_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1802_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0470 : TPDO3禁止时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1802_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Inhibt_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1802_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1802_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0471 : TPDO3事件时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1802_5( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Trans_Event_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1802_5 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1802_5,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0472 : TPDO4映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1A03_0( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A03_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A03_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0473 : TPDO4映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A03_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 && (ODDatArr[PDO4_Trans_Map_Num].all >= 1) )            /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A03_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A03_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0474 : TPDO4映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A03_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 && (ODDatArr[PDO4_Trans_Map_Num].all >= 2) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A03_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A03_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0475 : TPDO4映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A03_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 && (ODDatArr[PDO4_Trans_Map_Num].all >= 3) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A03_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A03_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0476 : TPDO4映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1A03_4( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 && (ODDatArr[PDO4_Trans_Map_Num].all >= 4) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1A03_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1A03_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0477 : TPDO4站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1803_1( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1803_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1803_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0478 : TPDO4传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1803_2( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1803_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1803_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0479 : TPDO4禁止时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1803_3( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Inhibt_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1803_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1803_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x047A : TPDO4事件时间                                                                      */
/****************************************************************************************************/
ULONG   uncal_Obj1803_5( MONDEF *Undef )
{
    if( PDO_Var.TPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Trans_Event_Time ].all);
    else
        return 0;
}
CMONDEF undef_Obj1803_5 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1803_5,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x047B : RPDO1映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1600_0( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1600_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1600_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x047C : RPDO1映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1600_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 && (ODDatArr[PDO1_Receive_Map_Num].all >= 1) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1600_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1600_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x047D : RPDO1映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1600_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 && (ODDatArr[PDO1_Receive_Map_Num].all >= 2) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1600_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1600_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x047E : RPDO1映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1600_3( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 && (ODDatArr[PDO1_Receive_Map_Num].all >= 3) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1600_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1600_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x047F : RPDO1映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1600_4( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 && (ODDatArr[PDO1_Receive_Map_Num].all >= 4) )        /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1600_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1600_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0480 : RPDO1站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1400_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1400_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1400_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0481 : RPDO1传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1400_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[0] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO1_Receive_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1400_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1400_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0482 : RPDO2映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1601_0( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1601_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1601_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0483 : RPDO2映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1601_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 && (ODDatArr[PDO2_Receive_Map_Num].all >= 1) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1601_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1601_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0484 : RPDO2映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1601_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 && (ODDatArr[PDO2_Receive_Map_Num].all >= 2) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1601_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1601_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0485 : RPDO2映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1601_3( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 && (ODDatArr[PDO2_Receive_Map_Num].all >= 3) )        /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1601_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1601_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0486 : RPDO2映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1601_4( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 && (ODDatArr[PDO2_Receive_Map_Num].all >= 4) )        /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1601_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1601_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0487 : RPDO2站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1401_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1401_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1401_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0488 : RPDO2传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1401_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[1] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO2_Receive_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1401_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1401_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0489 : RPDO3映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1602_0( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1602_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1602_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048A : RPDO3映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1602_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 && (ODDatArr[PDO3_Receive_Map_Num].all >= 1) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1602_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1602_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048B : RPDO3映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1602_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 && (ODDatArr[PDO3_Receive_Map_Num].all >= 2) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1602_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1602_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048C : RPDO3映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1602_3( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 && (ODDatArr[PDO3_Receive_Map_Num].all >= 3) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1602_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1602_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048D : RPDO3映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1602_4( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 && (ODDatArr[PDO3_Receive_Map_Num].all >= 4) )          /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1602_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1602_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048E : RPDO3站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1402_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1402_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1402_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x048F : RPDO3传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1402_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[2] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO3_Receive_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1402_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1402_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0490 : RPDO4映射参数组                                                                    */
/****************************************************************************************************/
ULONG   uncal_Obj1603_0( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Map_Num ].all);
    else
        return 0;
}
CMONDEF undef_Obj1603_0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1603_0,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0491 : RPDO4映射1                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1603_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 && (ODDatArr[PDO4_Receive_Map_Num].all >= 1) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Map1 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1603_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1603_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0492 : RPDO4映射2                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1603_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 && (ODDatArr[PDO4_Receive_Map_Num].all >= 2) )         /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Map2 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1603_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1603_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0493 : RPDO4映射3                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1603_3( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 && (ODDatArr[PDO4_Receive_Map_Num].all >= 3) )       /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Map3 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1603_3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1603_3,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0495 : RPDO4映射4                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1603_4( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 && (ODDatArr[PDO4_Receive_Map_Num].all >= 4) )           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Map4 ].all);
    else
        return 0;
}
CMONDEF undef_Obj1603_4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1603_4,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0496 : RPDO4站号                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1403_1( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_COB_ID ].all);
    else
        return 0;
}
CMONDEF undef_Obj1403_1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1403_1,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};
/****************************************************************************************************/
/*      0x0495 : RPDO4传输类型                                                                          */
/****************************************************************************************************/
ULONG   uncal_Obj1403_2( MONDEF *Undef )
{
    if( PDO_Var.RPDO_En[3] == 1 )                           /* CanOpen 机型                     */
        return(ODDatArr[ PDO4_Receive_Type ].all);
    else
        return 0;
}
CMONDEF undef_Obj1403_2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_Obj1403_2,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0511 : 電流検出（U相）零調用データ                                                     */
/****************************************************************************************************/
ULONG   uncal_CurZadjUphase( MONDEF *Undef )
{
LONG    x;

        x = CurrentSample.IuZero;
        return( x );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_CurUphZadj = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CurZadjUphase,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0512 : 電流検出（V相）零調用データ                                                     */
/****************************************************************************************************/
ULONG   uncal_CurZadjVphase( MONDEF *Undef )
{
LONG    x;

        x = CurrentSample.IvZero;
        return( x );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_CurVphZadj = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CurZadjVphase,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0513 : 硬件版本信息                                                                             */
/****************************************************************************************************/
ULONG   uncal_CurZadjWphase( MONDEF *Undef )
{
    LONG    x;

            x = CurrentSample.IwZero;
            return( x );
}

CMONDEF undef_CurWphZadj = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CurZadjWphase,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0600 : 絶対値编码器 [ 用户单位 ]                                                            */
/****************************************************************************************************/
ULONG   uncal_ScaleAbsPosUser( MONDEF *Undef )
{
LONG    x;
INT64 llkx1;
INT64 llkx2;

    /*----------------------------------------------------------------------------------------------*/
    llkx1 = ((INT64)RoutV.ABSEncMValue) * MencP.PulseNo + RoutV.ABSEncSValue;
    /*----------------------------------------------------------------------------------------------*/
    if( (Prm.orgmode & 0x00B0) == 0x00B0 )
    {
        llkx2 = ((INT64)((SHORT)Prm.orgMpos)) * MencP.PulseNo + \
                ULONGOF( Prm.orgSposL, Prm.orgSposH );
    }
    else
    {
        llkx2 = 0;
    }
    
    llkx1 -= llkx2;
    
    llkx1 = llkx1 * Iprm.Egear.a;
    x = llkx1 / Iprm.Egear.b;
    
    
    return( x );
}
CMONDEF undef_ScaleAbsPosUser = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_ScaleAbsPosUser,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0603 : 絶対値スケール位置（下位）                                                          */
/****************************************************************************************************/
CMONDEF undef_ScaleAbsPos_l = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&RoutV.ScaleAbsPosL,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0605 : 絶対値スケール位置（上位）                                                          */
/****************************************************************************************************/
CMONDEF undef_ScaleAbsPos_h = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&RoutV.ScaleAbsPosH,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0607 : 絶対値スケール位置（下位）                                                          */
/****************************************************************************************************/
CMONDEF undef_MechAbsPosL = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&RoutV.MechAbsPosL,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0609 : 絶対値スケール位置（上位）                                                          */
/****************************************************************************************************/
CMONDEF undef_MechAbsPosH = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&RoutV.MechAbsPosH,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x060B : 当前多圈上限值                                                                    */
/****************************************************************************************************/
CMONDEF undef_EncLimtM = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&MRevV.MRPulseL,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x060C : 当前多圈上限值                                                                    */
/****************************************************************************************************/
CMONDEF undef_EncLimtS = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&MRevV.MRPulseH,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0700 : 采样时间单位                                                                     */
/****************************************************************************************************/
ULONG   uncal_CycleTime( MONDEF *Undef )
{
        return( KPI_SBCYCLEUS );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_SamplingTime = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_CycleTime,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0701 : データが16384の時のトルク                                                            */
/****************************************************************************************************/
ULONG   uncal_MaxTorque( MONDEF *Undef )
{
        return( Bprm.PerMaxTrq );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MaxTorque = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MaxTorque,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0702 : データが16384の時の速度                                                         */
/****************************************************************************************************/
ULONG   uncal_MaxSpeed( MONDEF *Undef )
{
        return( KpiMonSpeedCal( 0x01000000 ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_MaxSpeed = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_MaxSpeed,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0800 : 当前警报代码 [－]                                                                 */
/****************************************************************************************************/
CMONDEF undef_AlmCodeX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&Alm.AlmWrnCode,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0801 : 当前警报代码 [－]                                                                 */
/****************************************************************************************************/
CMONDEF undef_AlmLtAlmCodeX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUshort,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.AlmCode,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0802 : 当前报警时间戳 [－]                                                                */
/****************************************************************************************************/
CMONDEF undef_AlmLtTmStampX = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdUlong,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.TmStamp,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0803 : 当前警报发生时的电机旋转/移动速度 [min-1, mm/s]                                    */
/****************************************************************************************************/
ULONG   uncal_AlmLtSpdFbk( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}
CMONDEF undef_AlmLtSpdFbkX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtSpdFbk,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.MotSpd,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0804 : 当前警报发生时的速度指令 [min-1, mm/s]                                             */
/****************************************************************************************************/
ULONG   uncal_AlmLtSpdRef( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}
CMONDEF undef_AlmLtSpdRefX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtSpdRef,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.SpdRef,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0805 : 当前警报发生时的内部转矩指令 [%]                                                 */
/****************************************************************************************************/
ULONG   uncal_AlmLtTrqRef( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}
CMONDEF undef_AlmLtTrqRefX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtTrqRef,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.TrqRef,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0806 : 当前警报发生时输入指令脉冲速度 [min-1, mm/s]                                      */
/****************************************************************************************************/
ULONG   uncal_AlmLtPosRefSpd( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}

CMONDEF undef_AlmLtPosRefSpdX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtPosRefSpd,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.PcmdSpd,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0807 : 当前警报发生时偏差计数器(位置偏差量) [pulse]                                        */
/****************************************************************************************************/
ULONG   uncal_AlmLtPosErrCntr( MONDEF *Undef )
{
        return( *Undef->Var.Plong );
}

CMONDEF undef_AlmLtPosErrCntrX = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtPosErrCntr,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.PosErr,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0808 : 当前警报发生时主回路母线电压 [V]                                                 */
/****************************************************************************************************/
ULONG   uncal_AlmLtDcVoltx( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}

CMONDEF undef_AlmLtDcVoltxX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtDcVoltx,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.DcVoltage,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0809 : 電流検出値 [%]                                                                      */
/****************************************************************************************************/
ULONG   uncal_AlmLtIqRate( MONDEF *Undef )
{
        return( *Undef->Var.Pshort );
}
CMONDEF undef_AlmLtIqRateX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_W_SIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtIqRate,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.IFBMon,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x080A : 当前警报发生时累计负载率 [%(周期2ms)]                                                */
/****************************************************************************************************/
ULONG   uncal_AlmLtMotLoad2ms( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
CMONDEF undef_AlmLtMotLoad2msX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtMotLoad2ms,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.MotLoad,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x080B : 当前警报发生时再生负载率 [%(周期2ms)]                                                */
/****************************************************************************************************/
ULONG   uncal_AlmLtRegerRate2ms( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}

CMONDEF undef_AlmLtRegerRate2msX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtRegerRate2ms,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.RgPower,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x080C : ＤＢ抵抗消費電力 [%(周期2ms)]                                                        */
/****************************************************************************************************/
ULONG   uncal_AlmLtDbrxPower2ms( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
CMONDEF undef_AlmLtDbrxPower2msX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtDbrxPower2ms,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.DbPower,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x080D : 最大累積負荷率 [%]                                                                    */
/****************************************************************************************************/
ULONG   uncal_AlmLtMotLoad10s( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
CMONDEF undef_AlmLtMotLoad10sX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtMotLoad10s,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.MaxMotLoad10s,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x080E : 慣性モーメント比/重量比 [%]                                                       */
/****************************************************************************************************/
ULONG   uncal_AlmLtJLRatio( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
CMONDEF undef_AlmLtJLRatioX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtJLRatio,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.JLRatio,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x080F : シリアルエンコーダ通信異常回数 [－]                                                */
/****************************************************************************************************/
ULONG   uncal_AlmLtSencComErrCnt( MONDEF *Undef )
{
        return( *Undef->Var.Pushort );
}
CMONDEF undef_AlmLtSencComErrCntX = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEDEC,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmLtSencComErrCnt,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.EncComErrCnt,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0810 : 内部监视信号 [－]                                                                 */
/****************************************************************************************************/
CMONDEF undef_AlmLtInterSignalX = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEBIT,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.InterSignal,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0814 : 内部输入信号监视 [－]                                                               */
/****************************************************************************************************/
CMONDEF undef_AlmLtIntInSignalX = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEBIT,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.InSignal,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0818 : 内部输出信号监视 [－]                                                               */
/****************************************************************************************************/
CMONDEF undef_AlmLtIntOutSignalX = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEBIT,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_NONE,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_StdLong,
/* 最小值                      */  (ULONG)&CoutV.AlmLtMon.OutSignal,
/* 最大值                      */  (ULONG)0
};


/****************************************************************************************************/
/*      0x0820 : 警报记录0                                                                          */
/****************************************************************************************************/
ULONG   uncal_AlmTrcData( MONDEF *Undef )
{
        return( KpiGetAlarmTraceAlmCode( (LONG)Undef->Var.Ulong ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AlmTrace0 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0821 : 警报记录1                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace1 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)1,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0822 : 警报记录2                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace2 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)2,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0823 : 警报记录3                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace3 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)3,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0824 : 警报记录4                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace4 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)4,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0825 : 警报记录5                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace5 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)5,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0826 : 警报记录6                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace6 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)6,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0827 : 警报记录7                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace7 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)7,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0828 : 警报记录8                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace8 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)8,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0829 : 警报记录9                                                                          */
/****************************************************************************************************/
CMONDEF undef_AlmTrace9 = {
/* :1: 数据类型(0:16位;1:32位)  */    FALSE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcData,
/* 最小值                      */  (ULONG)9,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*      0x0830 : 警报记录0时间戳(动作监视)                                                         */
/****************************************************************************************************/
ULONG   uncal_AlmTrcTmStamp( MONDEF *Undef )
{
        return( KpiGetAlarmTraceTmStamp( (LONG)Undef->Var.Ulong ) );
}
/*--------------------------------------------------------------------------------------------------*/
CMONDEF undef_AlmTmStamp0 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)0,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0832 : 警报记录1时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp1 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)1,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0834 : 警报记录2时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp2 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)2,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0836 : 警报记录3时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp3 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)3,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0838 : 警报记录4时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp4 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)4,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x083A : 警报记录5时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp5 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)5,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x083C : 警报记录6时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp6 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)6,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x083E : 警报记录7时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp7 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)7,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0840 : 警报记录8时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp8 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)8,
/* 最大值                      */  (ULONG)0
};



/****************************************************************************************************/
/*      0x0842 : 警报记录9时间戳(动作监视)                                                         */
/****************************************************************************************************/
CMONDEF undef_AlmTmStamp9 = {
/* :1: 数据类型(0:16位;1:32位)  */    TRUE,
/* :2: 数据类型(Hex,DEC,Bin)    */  DSPDEF_BASEHEX,
/* :1: 是否为有符号数          */  DSPDEF_NOSIGN,
/* :3: 小数点的位数               */  0,
/* :1: 变量是否可清除          */  MONDEF_CLR_DISABLE,
/* :2: ゲインタイプ               */  MONDEF_GTYPE_CONST,
/* :1: モニタ無効時none表示     */  NONEDSP_DISABLE,
/* :X: 保留                       */  0,
/* 専用使用チェック             */  KPI_CHKSPUSE_COMMON,
/* 用户权限                     */  ACCLVL_USER1,
/* 処理関数ポインタ             */  uncal_AlmTrcTmStamp,
/* 最小值                      */  (ULONG)9,
/* 最大值                      */  (ULONG)0
};

/****************************************************************************************************/
/*                                                                                                  */
/*      Ｕｎ监控参数管理表  (键盘)                                                                 */
/*                                                                                                  */
/****************************************************************************************************/
CMONTBL UnMonTbl[] = {
/*--------------------------------------------------------------------------------------------------*/
/*      UnNo   UnDef                        Comment                                                 */
/*--------------------------------------------------------------------------------------------------*/
    { 0x0000, &undef_SpdFbk             },  /* Un000:电机旋转速度(动作监视) [min-1, mm/s]         */
    { 0x0001, &undef_SpdRef             },  /* Un001:速度指令(动作监视) [min-1, mm/s]               */
    { 0x0002, &undef_TrqRef             },  /* Un002:内部转矩指令(动作监视) [%]                       */
    { 0x0004, &undef_MotAngDeg          },  /* Un004:电机磁极位置[deg]                                */
    { 0x0005, &undef_PosRefSpd          },  /* Un005:输入指令脉冲速度(仅位置控制有效)[min-1, mm/s] */
    { 0x0006, &undef_PcmdCounter        },  /* Un006:输入指令脉冲计数器(动作监视) [指令单位]        */            
    { 0x0007, &undef_Pfbk2Counter       },  /* Un007:反馈脉冲计数器 [指令单位]                     */
    { 0x0008, &undef_EncSTurnFbk        },  /* Un008:反馈脉冲计数器[编码器]                         */
    { 0x0009, &undef_PosErrCntr         },  /* Un009:位置偏差量(仅位置控制有效)(动作监视) [pulse]   */
    { 0x000A, &undef_MotLoad            },  /* Un00A:累计负载率(动作监视) [%]                        */
    { 0x000B, &undef_RegLoad            },  /* Un00B:再生负载率(动作监视) [%]                        */
    { 0x000D, &undef_ActGain            },  /* Un00D:有效增益                                       */
    { 0x000E, &undef_PowerOnTime        },  /* Un00E:总运行时间(动作监视) [100ms]                    */
    { 0x0010, &undef_IncPulse           },  /* Un010:絶対値エンコーダ1回転内パルス                    */
    { 0x0011, &undef_MultiTurn          },  /* Un011:絶対値エンコーダ多回転量                       */
    { 0x0016, &undef_SpeedRef           },  /* Un016:负载端旋转速度指令     [rpm]                    */
    { 0x0017, &undef_SpeedFbk           },  /* Un017:负载端旋转速度反馈     [rpm]                    */
    { 0x0018, &undef_TorqueRef          },  /* Un018:负载端旋转转矩指令     [N·m]                    */
    { 0x0019, &undef_TorqueFbk          },  /* Un019:负载端旋转转矩反馈     [N·m]                    */
    { 0x001A, &undef_Friction           },  /* Un01A:在线粘滞系数辨识值                             */
    { 0x001B, &undef_Intera             },  /* Un01B:在线惯量辨识值                                 */
    { 0x0020, &undef_FposCounter        },  /* Un020:全闭环反馈脉冲计数器                           */
    { 0x0021, &undef_FenseFbkEnc        },  /* Un021:光学尺反馈计数[编码器单位]                     */
    { 0x0022, &undef_FcPfbkSpd          },  /* Un022:全闭环反馈速度 [pulse/s]                      */
    { 0x0023, &undef_FencePosErrCntr    },  /* Un023:光学尺全闭环和电机编码器的反馈位置偏差[pulse] */
    { 0x0024, &undef_FenceErrCntrUser   },  /* Un024:光学尺全闭环和电机编码器的反馈位置偏差[pulse] */
    { 0x0025, &undef_FenceCompValue     },  /* Un025:全闭环滑动补偿累加量                             */
    { 0x0026, &undef_FenceAbsValue      },  /* Un026:全闭环绝对位置[光学尺单位]                         */
    { 0x0027, &undef_LoadMultiTurn      },  /* Un027:负载端絶対値编码器多圈值                       */
    { 0x002A, &undef_InterSignal0       },  /* Un02A:内部信号监控                                   */
    { 0x002B, &undef_InterSignal1       },  /* Un02B:内部信号监控2                                  */
    { 0x002C, &undef_InterSignal2       },  /* Un02C:内部信号监控3                                  */
    { 0x002D, &undef_InterSignal3       },  /* Un02D:内部信号监控4                                  */
    { 0x002E, &undef_CanStatus          },  /* Un02E:Can网络状态                                    */
    { 0x002F, &undef_CanCmdStatus       },  /* Un02F:CanOpen 命令状态                               */
    { 0x0030, &undef_ServoStatus        },  /* Un030:伺服运行状态                                   */
    { 0x0031, &undef_CanOpenStatus      },  /* Un031:CanOpen运行状态                                */
    { 0x0032, &undef_EtherCATStatus     },  /* Un032:EtherCAT 运行状态                              */
    { 0x0033, &undef_EtherCATSynch      },  /* Un033:EtherCAT 同步周期时间                          */
    { 0x0034, &undef_EtherCATSynchCnt   },  /* Un034:EtherCAT 同步帧异常计数器                      */
    { 0x0035, &undef_ARMVersion         },  /* Un035:MCU 版本                                       */
    { 0x0036, &undef_FPGAVersion        },  /* Un036:FPGA 版本                                      */
    { 0x0037, &undef_MCUSubVersion      },  /* Un037:MCU 子版本                                     */
    { 0x0038, &undef_FPGASubVersion     },  /* Un038:FPGA子 版本                                    */
    { 0x0039, &undef_EtherCATName1      },  /* Un039:EtherCAT 站点正名                              */
    { 0x003A, &undef_EtherCATName2      },  /* Un03A:EtherCAT 站点别名                              */
    { 0x003B, &undef_EtherCATALStatus   },  /* Un03B:EtherCAT AL 状态                               */
    { 0x003C, &undef_SnNum              },  /* Un03C:Sn序列                             */
    { 0x0040, &undef_SysAuthor          },  /* Un0040:作者ID                                          */
    { 0x0041, &undef_SysDate            },  /* Un0041:系统编译日期                                    */
    { 0x0042, &undef_SysTime            },  /* Un0042:系统编译时间                                    */
    { 0x0043, &undef_BootVersion        },  /* Un043:Boot 版本                                 */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0045, &undef_Un045              },  /* Un045:端口0 无效帧计数                               */
    { 0x0046, &undef_Un046              },  /* Un046:端口0 接收错误计数                             */
    { 0x0047, &undef_Un047              },  /* Un047:端口1 无效帧计数                               */
    { 0x0048, &undef_Un048              },  /* Un048:端口1 接收错误计数                             */
    { 0x0049, &undef_Un049              },  /* Un049:端口0 转发错误计数                             */
    { 0x004A, &undef_Un04A              },  /* Un04A:端口1 转发错误计数                             */
    { 0x004B, &undef_Un04B              },  /* Un04B:数据帧处理单元错误计数                         */
    { 0x004C, &undef_Un04C              },  /* Un04C:PDI 错误计数计数                               */
    { 0x004D, &undef_Un04D              },  /* Un04D:端口0链接丢失计数                              */
    { 0x004E, &undef_Un04E              },  /* Un04E:端口1链接丢失计数                              */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0087, &undef_SencComErrCnt      },  /* Un087:串行编码器通信异常次数                            */
    { 0x0089, &undef_HeatsinkTemp       },  /* Un089:模块温度[0.1℃]                                 */
    { 0x0100, &undef_InSignal           },  /* Un100:IO口输入信号监视(输入信号监视) [－]          */
    { 0x0101, &undef_OutSignal          },  /* Un101:IO口输出信号监视(输出信号监视) [－]          */
    { 0x0105, &undef_SettlingTime       },  /* Un105:位置整定时间 [0.1ms]                         */
    { 0x0106, &undef_OverShoot          },  /* Un106:位置超调量 [指令单位]                           */
    { 0x010C, &undef_HeatMotTemp        },  /* Un10C : 电机温度传感器检测值 [0.1℃]                 */
    { 0x010D, &undef_EnvirTemperature   },  /* Un10D:环境温度[0.1℃]                                 */

    { 0x0140, &undef_DcVoltx            },  /* Un140:主回路母线电压 [V]                                */
    { 0x0141, &undef_IqRate             },  /* Un141:电流检测值 [%]                                  */
    { 0x0142, &undef_MotLoad2ms         },  /* Un142:累计负载率 [%（周期2ms）]                       */
    { 0x0143, &undef_RegerRate2ms       },  /* Un143:再生负载率 [%（周期2ms）]                      */
    { 0x0144, &undef_DbrxPower2ms       },  /* Un144:DB 电阻热量累加                                */

    { 0x0145, &undef_MotTrgLoad         },  /* Un145:负载转矩监控                                   */
    { 0x0150, &undef_AI1Channel0        },  /* Un150:模拟量通道1电压[0.001V](未处理前)              */
    { 0x0151, &undef_AI2Channel0        },  /* Un151:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0152, &undef_AI1Channel1        },  /* Un152:模拟量通道1电压[0.001V](处理后)                */
    { 0x0153, &undef_AI2Channel1        },  /* Un153:模拟量通道2电压[0.001V](处理后)                */

    { 0x0160, &undef_MIT_TorqCmd        },  /* Un160:负载转矩监控                                   */
    { 0x0161, &undef_MIT_AngleCmd       },  /* Un161:模拟量通道1电压[0.001V](未处理前)              */
    { 0x0162, &undef_MIT_VelCmd         },  /* Un162:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0163, &undef_MIT_KpValCmd       },  /* Un163:模拟量通道1电压[0.001V](处理后)                */
    { 0x0164, &undef_MIT_KdValCmd       },  /* Un164:模拟量通道2电压[0.001V](处理后)                */
    { 0x0165, &undef_MIT_AngleFeb      },  /* Un165:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0166, &undef_MIT_VelFeb        },  /* Un166:模拟量通道1电压[0.001V](处理后)                */
    { 0x0167, &undef_MIT_TorqFeb       },  /* Un167:模拟量通道2电压[0.001V](处理后)                */

    { 0x0203, &undef_ErrPrmNo           },  /* Un203:设定异常参数号(A.040)                         */
    { 0x0212, &undef_CurExeTimeA        },  /* ScanA現在処理時間 [0.1us]                          */
    { 0x0213, &undef_MaxExeTimeA        },  /* ScanA最大処理時間 [0.1us]                          */
    { 0x0214, &undef_CurExeTimeB        },  /* ScanB現在処理時間 [0.1us]                          */
    { 0x0215, &undef_MaxExeTimeB        },  /* ScanB最大処理時間 [0.1us]                          */
    { 0x0216, &undef_CurExeTimeC        },  /* ScanC現在処理時間 [0.1us]                          */
    { 0x0217, &undef_MaxExeTimeC        },  /* ScanC最大処理時間 [0.1us]                          */
    { 0x0218, &undef_CurExeTimeR        },  /* Round現在処理時間 [0.1ms]                          */
    { 0x0219, &undef_MaxExeTimeR        },  /* Round最大処理時間 [0.1ms]                          */
//  { 0x021A, &undef_CurExeTimeN        },  /* ScanN現在処理時間 [0.1us]                          */
//  { 0x021B, &undef_MaxExeTimeN        },  /* ScanN最大処理時間 [0.1us]                          */
    { 0x0300, &undef_PrCurrentNum       },  /* Pr 当前执行的路径                                    */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0511, &undef_CurUphZadj         },  /* Un511:電流検出（U相）零調用データ                     */
    { 0x0512, &undef_CurVphZadj         },  /* Un512:電流検出（V相）零調用データ                     */
    { 0x0513, &undef_CurWphZadj        },   /* Un513:電流検出（W相）零調用データ                       */
    { 0x0600, &undef_ScaleAbsPosUser    },  /* Un600:编码器绝对位置(用户单位)                         */
    { 0x0603, &undef_ScaleAbsPos_l      },  /* Un603:编码器绝对位置(L)                             */
    { 0x0605, &undef_ScaleAbsPos_h      },  /* Un605:编码器绝对位置(H)                             */
    { 0x0607, &undef_MechAbsPosL        },  /* Un607:机械绝对坐标(L)                               */
    { 0x0609, &undef_MechAbsPosH        },  /* Un609:机械绝对坐标(H)                               */
    { 0x060B, &undef_EncLimtM           },  /* Un60B:当前多圈上限值                                */
    { 0x060D, &undef_EncLimtS           },  /* Un60D:当前单圈上限值                                 */
    { 0x0800, &undef_AlmCodeX           },  /* 当前警报代码 [－]                                   */
    { 0x0801, &undef_AlmLtAlmCodeX      },  /* 当前警报代码 [－]                                   */
    { 0x0802, &undef_AlmLtTmStampX      },  /* 当前报警代码时间戳 [100ms]                            */
    { 0x0803, &undef_AlmLtSpdFbkX       },  /* 当前警报发生时的电机旋转/移动速度 [min-1, mm/s]      */
    { 0x0804, &undef_AlmLtSpdRefX       },  /* 当前警报发生时的速度指令 [min-1, mm/s]               */
    { 0x0805, &undef_AlmLtTrqRefX       },  /* 当前警报发生时的内部转矩指令 [%]                       */
    { 0x0806, &undef_AlmLtPosRefSpdX    },  /* 当前警报发生时输入指令脉冲速度 [min-1, mm/s]            */
    { 0x0807, &undef_AlmLtPosErrCntrX   },  /* 当前警报发生时偏差计数器(位置偏差量) [pulse]          */
    { 0x0808, &undef_AlmLtDcVoltxX      },  /* 当前警报发生时主回路母线电压 [V]                       */
    { 0x0809, &undef_AlmLtIqRateX       },  /* 電流検出値 [%]                                        */
    { 0x080A, &undef_AlmLtMotLoad2msX   },  /* 当前警报发生时累计负载率 [%(周期2ms)]              */
    { 0x080B, &undef_AlmLtRegerRate2msX },  /* 当前警报发生时再生负载率 [%(周期2ms)]              */
    { 0x080C, &undef_AlmLtDbrxPower2msX },  /* ＤＢ抵抗消費電力 [%(周期2ms)]                      */
    { 0x080D, &undef_AlmLtMotLoad10sX   },  /* 最大累積負荷率 [%]                                  */
    { 0x080E, &undef_AlmLtJLRatioX      },  /* 慣性モーメント比/重量比 [%]                         */
    { 0x080F, &undef_AlmLtSencComErrCntX},  /* シリアルエンコーダ通信異常回数 [－]                  */
    { 0x0810, &undef_AlmLtInterSignalX  },  /* 内部监视信号 [－]                                   */
    { 0x0814, &undef_AlmLtIntInSignalX  },  /* 内部输入信号监视 [－]                             */
    { 0x0818, &undef_AlmLtIntOutSignalX },  /* 内部输出信号监视 [－]                             */
    { 0x0820, &undef_AlmTrace0          },  /* 警报记录0                                            */
    { 0x0821, &undef_AlmTrace1          },  /* 警报记录1                                            */
    { 0x0822, &undef_AlmTrace2          },  /* 警报记录2                                            */
    { 0x0823, &undef_AlmTrace3          },  /* 警报记录3                                            */
    { 0x0824, &undef_AlmTrace4          },  /* 警报记录4                                            */
    { 0x0825, &undef_AlmTrace5          },  /* 警报记录5                                            */
    { 0x0826, &undef_AlmTrace6          },  /* 警报记录6                                            */
    { 0x0827, &undef_AlmTrace7          },  /* 警报记录7                                            */
    { 0x0828, &undef_AlmTrace8          },  /* 警报记录8                                            */
    { 0x0829, &undef_AlmTrace9          },  /* 警报记录9                                            */
    { 0x0830, &undef_AlmTmStamp0        },  /* 警报记录0时间戳(动作监视)                           */
    { 0x0832, &undef_AlmTmStamp1        },  /* 警报记录1时间戳(动作监视)                           */
    { 0x0834, &undef_AlmTmStamp2        },  /* 警报记录2时间戳(动作监视)                           */
    { 0x0836, &undef_AlmTmStamp3        },  /* 警报记录3时间戳(动作监视)                           */
    { 0x0838, &undef_AlmTmStamp4        },  /* 警报记录4时间戳(动作监视)                           */
    { 0x083A, &undef_AlmTmStamp5        },  /* 警报记录5时间戳(动作监视)                           */
    { 0x083C, &undef_AlmTmStamp6        },  /* 警报记录6时间戳(动作监视)                           */
    { 0x083E, &undef_AlmTmStamp7        },  /* 警报记录7时间戳(动作监视)                           */
    { 0x0840, &undef_AlmTmStamp8        },  /* 警报记录8时间戳(动作监视)                           */
    { 0x0842, &undef_AlmTmStamp9        },  /* 警报记录9时间戳(动作监视)                           */
};

/*--------------------------------------------------------------------------------------------------*/
const   USHORT  UnMonTblEntNum = sizeof(UnMonTbl)/sizeof(UnMonTbl[0]);



/****************************************************************************************************/
/*                                                                                                  */
/*      Ｕｎ监视器寄存器表  (通讯)                                                                     */
/*                                                                                                  */
/****************************************************************************************************/
CMONTBL UnRegTbl[] = {
/*--------------------------------------------------------------------------------------------------*/
/*      RegNo    UnDef                      Comment                                                 */
/*--------------------------------------------------------------------------------------------------*/
    { 0x0000, &undef_SpdFbk             },  /* Un000:电机旋转速度(动作监视) [min-1, mm/s]         */
    { 0x0001, &undef_SpdRef             },  /* Un001:速度指令(动作监视) [min-1, mm/s]               */
    { 0x0002, &undef_TrqRef             },  /* Un002:内部转矩指令(动作监视) [%]                       */
    { 0x0004, &undef_MotAngDeg          },  /* Un004:电机磁极位置[deg]                                */
    { 0x0005, &undef_PosRefSpd          },  /* Un005:输入指令脉冲速度(仅位置控制有效)(动作监视) [min-1, mm/s]  */
    { 0x0006, &undef_PcmdCounter        },  /* Un006:输入指令脉冲计数器(动作监视) [指令单位]        */
    { 0x0007, &undef_Pfbk2Counter       },  /* Un007:反馈脉冲计数器 [指令单位]                     */
    { 0x0008, &undef_EncSTurnFbk        },  /* Un008:反馈脉冲计数器[编码器]                         */
    { 0x0009, &undef_PosErrCntr         },  /* Un009:位置偏差量(动作监视) [pulse]                    */
    { 0x000A, &undef_MotLoad            },  /* Un00A:累计负载率(动作监视) [%]                        */
    { 0x000B, &undef_RegLoad            },  /* Un00B:再生负载率(动作监视) [%]                        */
    { 0x000D, &undef_ActGain            },  /* Un00D:有效增益                                       */
    { 0x000E, &undef_PowerOnTime        },  /* Un00E:总运行时间(动作监视) [100ms]                    */
    { 0x0010, &undef_IncPulse           },  /* Un011:絶対値エンコーダ1回転内パルス                    */
    { 0x0011, &undef_MultiTurn          },  /* Un010:絶対値エンコーダ多回転量                       */
    { 0x0016, &undef_SpeedRef           },  /* Un016:负载端旋转速度指令     [rpm]                    */
    { 0x0017, &undef_SpeedFbk           },  /* Un017:负载端旋转速度反馈     [rpm]                    */
    { 0x0018, &undef_TorqueRef          },  /* Un018:负载端旋转转矩指令     [N·m]                    */
    { 0x0019, &undef_TorqueFbk          },  /* Un019:负载端旋转转矩反馈     [N·m]                    */
    { 0x001A, &undef_Friction           },  /* Un01A:在线粘滞系数辨识值                             */
    { 0x001B, &undef_Intera             },  /* Un01B:在线惯量辨识值                                 */
    { 0x0020, &undef_FposCounter        },  /* Un020:全闭环反馈脉冲计数器                           */
    { 0x0021, &undef_FenseFbkEnc        },  /* Un021:光学尺反馈计数[编码器单位]                     */
    { 0x0022, &undef_FcPfbkSpd          },  /* Un022:全闭环反馈速度 [pulse/s]                      */
    { 0x0023, &undef_FencePosErrCntr    },  /* Un023:光学尺全闭环和电机编码器的反馈位置偏差[pulse] */
    { 0x0024, &undef_FenceErrCntrUser   },  /* Un024:光学尺全闭环和电机编码器的反馈位置偏差[pulse] */
    { 0x0025, &undef_FenceCompValue     },  /* Un025:全闭环滑动补偿累加量                         */
    { 0x0026, &undef_FenceAbsValue      },  /* Un026:全闭环绝对位置[光学尺单位]                         */
    { 0x0027, &undef_LoadMultiTurn      },  /* Un027:负载端絶対値编码器多圈值                       */
    { 0x002A, &undef_InterSignal0       },  /* Un02A:内部信号监控1                                  */
    { 0x002B, &undef_InterSignal1       },  /* Un02B:内部信号监控2                                  */
    { 0x002C, &undef_InterSignal2       },  /* Un02C:内部信号监控3                                  */
    { 0x002D, &undef_InterSignal3       },  /* Un02D:内部信号监控4                                  */
    { 0x002E, &undef_CanStatus          },  /* Un02E:Can网络状态                                    */
    { 0x002F, &undef_CanCmdStatus       },  /* Un02F:CanOpen 命令状态                               */
    { 0x0030, &undef_ServoStatus        },  /* Un030:伺服运行状态                                   */
    { 0x0031, &undef_CanOpenStatus      },  /* Un031:CanOpen运行状态                                */
    { 0x0032, &undef_EtherCATStatus     },  /* Un032:EtherCAT 运行状态                              */
    { 0x0033, &undef_EtherCATSynch      },  /* Un033:EtherCAT 同步周期时间                          */
    { 0x0034, &undef_EtherCATSynchCnt   },  /* Un034:EtherCAT 同步帧异常计数器                      */
    { 0x0035, &undef_ARMVersion         },  /* Un035:MCU 版本                                       */
    { 0x0036, &undef_FPGAVersion        },  /* Un036:FPGA 版本                                      */
    { 0x0037, &undef_MCUSubVersion      },  /* Un037:MCU 子版本                                     */
    { 0x0038, &undef_FPGASubVersion     },  /* Un038:FPGA子 版本                                    */
    { 0x0039, &undef_EtherCATName1      },  /* Un039:EtherCAT 站点正名                              */
    { 0x003A, &undef_EtherCATName2      },  /* Un03A:EtherCAT 站点别名                              */
    { 0x003B, &undef_EtherCATALStatus   },  /* Un03B:EtherCAT AL 状态                               */
    { 0x003C, &undef_SnNum              },  /* Un03C:Sn序列                             */
    { 0x0040, &undef_SysAuthor          },  /* Un040:作者ID                                           */
    { 0x0041, &undef_SysDate            },  /* Un041:系统编译日期                                 */
    { 0x0042, &undef_SysTime            },  /* Un042:系统编译时间                                 */
    { 0x0043, &undef_BootVersion        },  /* Un043:Boot 版本                                 */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0045, &undef_Un045              },  /* Un045:端口0 无效帧计数                               */
    { 0x0046, &undef_Un046              },  /* Un046:端口0 接收错误计数                             */
    { 0x0047, &undef_Un047              },  /* Un047:端口1 无效帧计数                               */
    { 0x0048, &undef_Un048              },  /* Un048:端口1 接收错误计数                             */
    { 0x0049, &undef_Un049              },  /* Un049:端口0 转发错误计数                             */
    { 0x004A, &undef_Un04A              },  /* Un04A:端口1 转发错误计数                             */
    { 0x004B, &undef_Un04B              },  /* Un04B:数据帧处理单元错误计数                         */
    { 0x004C, &undef_Un04C              },  /* Un04C:PDI 错误计数计数                               */
    { 0x004D, &undef_Un04D              },  /* Un04D:端口0链接丢失计数                              */
    { 0x004E, &undef_Un04E              },  /* Un04E:端口1链接丢失计数                              */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0087, &undef_SencComErrCnt      },  /* Un087:串行编码器通信异常次数                            */
    { 0x0089, &undef_HeatsinkTemp       },  /* Un089:模块温度[0.1℃]                                 */
    { 0x0100, &undef_InSignal           },  /* Un100:IO口输入信号监视(输入信号监视) [－]          */
    { 0x0101, &undef_OutSignal          },  /* Un102:IO口输出信号监视(输出信号监视) [－]          */
    { 0x0105, &undef_SettlingTime       },  /* Un105:位置整定时间 [0.1ms]                         */
    { 0x0106, &undef_OverShoot          },  /* Un106:位置超调量 [指令单位]                           */
    { 0x010C, &undef_HeatMotTemp        },  /* Un10C:电机温度传感器检测值 [0.1℃]                 */
    { 0x010D, &undef_EnvirTemperature   },  /* Un10D:环境温度[0.1℃]                                 */
    { 0x0140, &undef_DcVoltx            },  /* Un140:主回路母线电压 [V]                                */
    { 0x0141, &undef_IqRate             },  /* Un141:电流检测值 [%]                                  */
    { 0x0142, &undef_MotLoad2ms         },  /* Un142:累计负载率 [%（周期2ms）]                       */
    { 0x0143, &undef_RegerRate2ms       },  /* Un143:再生负载率 [%（周期2ms）]                      */
    { 0x0144, &undef_DbrxPower2ms       },  /* Un144:DB 电阻热量累加                                */
    { 0x0145, &undef_MotTrgLoad         },  /* Un145:负载转矩监控                                   */   
    { 0x0150, &undef_AI1Channel0        },  /* Un150:模拟量通道1电压[0.001V](未处理前)              */
    { 0x0151, &undef_AI2Channel0        },  /* Un151:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0152, &undef_AI1Channel1        },  /* Un152:模拟量通道1电压[0.001V](处理后)                */
    { 0x0153, &undef_AI2Channel1        },  /* Un153:模拟量通道2电压[0.001V](处理后)                */

    { 0x0160, &undef_MIT_TorqCmd        },  /* Un160:负载转矩监控                                   */
    { 0x0161, &undef_MIT_AngleCmd       },  /* Un161:模拟量通道1电压[0.001V](未处理前)              */
    { 0x0162, &undef_MIT_VelCmd         },  /* Un162:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0163, &undef_MIT_KpValCmd       },  /* Un163:模拟量通道1电压[0.001V](处理后)                */
    { 0x0164, &undef_MIT_KdValCmd       },  /* Un164:模拟量通道2电压[0.001V](处理后)                */
    { 0x0165, &undef_MIT_AngleFeb      },  /* Un165:模拟量通道2电压[0.001V](未处理前)              */
    { 0x0166, &undef_MIT_VelFeb        },  /* Un166:模拟量通道1电压[0.001V](处理后)                */
    { 0x0167, &undef_MIT_TorqFeb       },  /* Un167:模拟量通道2电压[0.001V](处理后)                */

    { 0x0203, &undef_ErrPrmNo           },  /* Un203 设定异常参数号(A.040)                         */
    { 0x0212, &undef_CurExeTimeA        },  /* ScanA現在処理時間 [0.1us]                          */
    { 0x0213, &undef_MaxExeTimeA        },  /* ScanA最大処理時間 [0.1us]                          */
    { 0x0214, &undef_CurExeTimeB        },  /* ScanB現在処理時間 [0.1us]                          */
    { 0x0215, &undef_MaxExeTimeB        },  /* ScanB最大処理時間 [0.1us]                          */
    { 0x0216, &undef_CurExeTimeC        },  /* ScanC現在処理時間 [0.1us]                          */
    { 0x0217, &undef_MaxExeTimeC        },  /* ScanC最大処理時間 [0.1us]                          */
    { 0x0218, &undef_CurExeTimeR        },  /* Round現在処理時間 [0.1ms]                          */
    { 0x0219, &undef_MaxExeTimeR        },  /* Round最大処理時間 [0.1ms]                          */
//  { 0x021A, &undef_CurExeTimeN        },  /* ScanN現在処理時間 [0.1us]                            */
//  { 0x021B, &undef_MaxExeTimeN        },  /* ScanN最大処理時間 [0.1us]                            */
    { 0x0300, &undef_PrCurrentNum       },  /* Pr 当前执行的路径                                      */
    { 0x0400, &undef_Obj603F            },  /* Un400:对象字典603F                                   */
    { 0x0401, &undef_Obj6040            },  /* Un401:对象字典6040                                   */
    { 0x0402, &undef_Obj6041            },  /* Un402:对象字典6041                                   */    
    { 0x0403, &undef_Obj6060            },  /* Un403:对象字典6060                                   */
    { 0x0404, &undef_Obj6061            },  /* Un404:对象字典6061                                   */
    { 0x0405, &undef_Obj6062            },  /* Un405:对象字典6062                                   */
    { 0x0406, &undef_Obj6063            },  /* Un406:对象字典6063                                   */
    { 0x0407, &undef_Obj6064            },  /* Un407:对象字典6064                                   */
    { 0x0408, &undef_Obj6065            },  /* Un408:对象字典6065                                   */
    { 0x0409, &undef_Obj6067            },  /* Un409:对象字典6067                                   */
    { 0x040A, &undef_Obj6068            },  /* Un40A:对象字典6068                                   */
    { 0x040B, &undef_Obj606B            },  /* Un40B:对象字典606B                                   */
    { 0x040C, &undef_Obj606C            },  /* Un40C:对象字典606C                                   */
    { 0x040D, &undef_Obj606D            },  /* Un40D:对象字典606D                                   */
    { 0x040E, &undef_Obj606E            },  /* Un40E:对象字典606E                                   */
    { 0x040F, &undef_Obj606F            },  /* Un40F:对象字典606F                                   */    
    { 0x0410, &undef_Obj6070            },  /* Un410:对象字典6070                                   */
    { 0x0411, &undef_Obj6071            },  /* Un411:对象字典6071                                   */
    { 0x0412, &undef_Obj6072            },  /* Un412:对象字典6072                                   */
    { 0x0413, &undef_Obj6074            },  /* Un413:对象字典6074                                   */
    { 0x0414, &undef_Obj6075            },  /* Un414:对象字典6075                                   */
    { 0x0415, &undef_Obj6076            },  /* Un415:对象字典6076                                   */
    { 0x0416, &undef_Obj6077            },  /* Un416:对象字典6077                                   */
    { 0x0417, &undef_Obj607A            },  /* Un417:对象字典607A                                   */
    { 0x0418, &undef_Obj607C            },  /* Un418:对象字典607C                                   */
    { 0x0419, &undef_Obj607D_1          },  /* Un419:对象字典607D_1                                 */
    { 0x041A, &undef_Obj607D_2          },  /* Un41A:对象字典607D_2                                 */
    { 0x041B, &undef_Obj607E            },  /* Un41B:对象字典607E                                   */
    { 0x041C, &undef_Obj607F            },  /* Un41C:对象字典607F                                   */    
    { 0x041D, &undef_Obj6080            },  /* Un41D:对象字典6080                                   */
    { 0x041E, &undef_Obj6081            },  /* Un41E:对象字典6081                                   */
    { 0x041F, &undef_Obj6083            },  /* Un41F:对象字典6083                                   */
    { 0x0420, &undef_Obj6084            },  /* Un420:对象字典6084                                   */
    { 0x0421, &undef_Obj6086            },  /* Un421:对象字典6086                                   */
    { 0x0422, &undef_Obj6087            },  /* Un422:对象字典6087                                   */   
    { 0x0423, &undef_Obj6091_1          },  /* Un423:对象字典6091_1                                 */
    { 0x0424, &undef_Obj6091_2          },  /* Un424:对象字典6091_2                                 */
    { 0x0425, &undef_Obj6085            },  /* Un425:对象字典6085                                   */
    { 0x0426, &undef_Obj605A            },  /* Un426:对象字典605D                                   */ 
    { 0x0427, &undef_Obj605D            },  /* Un426:对象字典605D                                   */ 
//    { 0x0425, &undef_Obj6093_1         },  /* Un425:对象字典6091_1                                */
//    { 0x0426, &undef_Obj6093_2         },  /* Un426:对象字典6091_0                                */
//    { 0x0427, &undef_Obj6094_1         },  /* Un427:对象字典6091_1                                */
//    { 0x0428, &undef_Obj6094_2         },  /* Un428:对象字典6091_2                                */
//    { 0x0429, &undef_Obj6095_1         },  /* Un429:对象字典6091_1                                */
//    { 0x042A, &undef_Obj6095_2         },  /* Un42A:对象字典6091_2                                */
//    { 0x042B, &undef_Obj6097_1         },  /* Un42B:对象字典6091_1                                */
//    { 0x042C, &undef_Obj6097_2         },  /* Un42C:对象字典6091_2                                */   
    { 0x042D, &undef_Obj6098            },  /* Un42D:对象字典6098                                   */ 
    { 0x042E, &undef_Obj6099_1          },  /* Un42E:对象字典6099_1                                 */
    { 0x042F, &undef_Obj6099_2          },  /* Un42F:对象字典6099_2                                  */
    { 0x0430, &undef_Obj609A            },  /* Un430:对象字典609A                                   */    
    { 0x0431, &undef_Obj60B0            },  /* Un431:对象字典60B0                                   */
    { 0x0432, &undef_Obj60B1            },  /* Un432:对象字典60B1                                   */
    { 0x0433, &undef_Obj60B2            },  /* Un433:对象字典60B2                                   */
    { 0x0434, &undef_Obj60B8            },  /* Un434:对象字典60B8                                   */
    { 0x0435, &undef_Obj60B9            },  /* Un435:对象字典60B9                                   */
    { 0x0436, &undef_Obj60BA            },  /* Un436:对象字典60BA                                   */
    { 0x0437, &undef_Obj60BB            },  /* Un437:对象字典60BB                                   */
    { 0x0438, &undef_Obj60BC            },  /* Un438:对象字典60BC                                   */
    { 0x0439, &undef_Obj60BD            },  /* Un439:对象字典60BD                                   */  
    { 0x043C, &undef_Obj60C5            },  /* Un43C:对象字典60C5                                   */
    { 0x043D, &undef_Obj60C6            },  /* Un43D:对象字典60C6                                   */   
    { 0x043E, &undef_Obj60E0            },  /* Un43E:对象字典60E0                                   */
    { 0x043F, &undef_Obj60E1            },  /* Un43F:对象字典60E1                                   */    
    { 0x0440, &undef_Obj60F2            },  /* Un440:对象字典60F2                                   */
    { 0x0441, &undef_Obj60F4            },  /* Un441:对象字典60F4                                   */
    { 0x0442, &undef_Obj60FC            },  /* Un442:对象字典60FC                                   */
    { 0x0443, &undef_Obj60FD            },  /* Un443:对象字典60FD                                   */
    { 0x0444, &undef_Obj60FE_1          },  /* Un444:对象字典60FE_1                                 */
    { 0x0445, &undef_Obj60FF            },  /* Un445:对象字典60FF                                   */    
    { 0x0446, &undef_Obj6502            },  /* Un446:对象字典6502                                   */
    { 0x0447, &undef_Obj60C1            },  /* Un447:对象字典60C1                                   */
    { 0x0448, &undef_Obj60C2_1          },  /* Un448:对象字典60C2_1                                 */
    { 0x0449, &undef_Obj60C2_2          },  /* Un449:对象字典60C2_2                                 */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0450, &undef_Obj1000            },  /* Un450:对象字典1000                                   */
    { 0x0451, &undef_Obj1018_1          },  /* Un451:对象字典1018_1                                 */
    { 0x0452, &undef_Obj1018_2          },  /* Un452:对象字典1018_2                                 */
    { 0x0453, &undef_Obj1018_3          },  /* Un453:对象字典1018_3                                 */    
    /*----------------------------------------------------------------------------------------------*/
    { 0x0454, &undef_Obj1A00_0          },  /* Un454:对象字典1A00_0                                 */
    { 0x0455, &undef_Obj1A00_1          },  /* Un455:对象字典1A00_1                                 */
    { 0x0456, &undef_Obj1A00_2          },  /* Un456:对象字典1A00_2                                 */
    { 0x0457, &undef_Obj1A00_3          },  /* Un457:对象字典1A00_3                                 */
    { 0x0458, &undef_Obj1A00_4          },  /* Un458:对象字典1A00_4                                 */
    { 0x0459, &undef_Obj1800_1          },  /* Un459:对象字典1800_1                                 */
    { 0x045A, &undef_Obj1800_2          },  /* Un45A:对象字典1800_2                                 */
    { 0x045B, &undef_Obj1800_3          },  /* Un45B:对象字典1800_3                                 */
    { 0x045C, &undef_Obj1800_5          },  /* Un45C:对象字典1800_5                                 */
    { 0x0460, &undef_Obj1A01_0          },  /* Un460:对象字典1A01_0                                 */
    { 0x0461, &undef_Obj1A01_1          },  /* Un461:对象字典1A01_1                                 */
    { 0x0462, &undef_Obj1A01_2          },  /* Un462:对象字典1A01_2                                 */
    { 0x0463, &undef_Obj1A01_3          },  /* Un463:对象字典1A01_3                                 */
    { 0x0464, &undef_Obj1A01_4          },  /* Un464:对象字典1A01_4                                 */
    { 0x0465, &undef_Obj1801_1          },  /* Un465:对象字典1801_1                                 */
    { 0x0466, &undef_Obj1801_2          },  /* Un466:对象字典1801_2                                 */
    { 0x0467, &undef_Obj1801_3          },  /* Un467:对象字典1801_3                                 */
    { 0x0468, &undef_Obj1801_5          },  /* Un468:对象字典1801_5                                 */
    { 0x0469, &undef_Obj1A02_0          },  /* Un469:对象字典1A02_0                                 */
    { 0x046A, &undef_Obj1A02_1          },  /* Un46A:对象字典1A02_1                                 */
    { 0x046B, &undef_Obj1A02_2          },  /* Un46B:对象字典1A02_2                                 */
    { 0x046C, &undef_Obj1A02_3          },  /* Un46C:对象字典1A02_3                                 */
    { 0x046D, &undef_Obj1A02_4          },  /* Un46D:对象字典1A02_4                                 */
    { 0x046E, &undef_Obj1802_1          },  /* Un46E:对象字典1801_1                                 */
    { 0x046F, &undef_Obj1802_2          },  /* Un46F:对象字典1801_2                                 */
    { 0x0470, &undef_Obj1802_3          },  /* Un470:对象字典1801_3                                 */
    { 0x0471, &undef_Obj1802_5          },  /* Un471:对象字典1801_5                                 */
    { 0x0472, &undef_Obj1A03_0          },  /* Un472:对象字典1A03_0                                 */
    { 0x0473, &undef_Obj1A03_1          },  /* Un473:对象字典1A03_1                                 */
    { 0x0474, &undef_Obj1A03_2          },  /* Un474:对象字典1A03_2                                 */
    { 0x0475, &undef_Obj1A03_3          },  /* Un475:对象字典1A03_3                                 */
    { 0x0476, &undef_Obj1A03_4          },  /* Un476:对象字典1A03_4                                 */
    { 0x0477, &undef_Obj1803_1          },  /* Un477:对象字典1803_1                                 */
    { 0x0478, &undef_Obj1803_2          },  /* Un478:对象字典1803_2                                 */
    { 0x0479, &undef_Obj1803_3          },  /* Un479:对象字典1803_3                                 */
    { 0x047A, &undef_Obj1803_5          },  /* Un47A:对象字典1803_5                                 */
    { 0x047B, &undef_Obj1600_0          },  /* Un47B:对象字典1600_0                                 */
    { 0x047C, &undef_Obj1600_1          },  /* Un47C:对象字典1600_1                                 */
    { 0x047D, &undef_Obj1600_2          },  /* Un47D:对象字典1600_2                                 */
    { 0x047E, &undef_Obj1600_3          },  /* Un47E:对象字典1600_3                                 */
    { 0x047F, &undef_Obj1600_4          },  /* Un47F:对象字典1600_4                                 */
    { 0x0480, &undef_Obj1400_1          },  /* Un480:对象字典1400_1                                 */
    { 0x0481, &undef_Obj1400_2          },  /* Un481:对象字典1400_2                                 */
    { 0x0482, &undef_Obj1601_0          },  /* Un482:对象字典1601_0                                 */
    { 0x0483, &undef_Obj1601_1          },  /* Un483:对象字典1601_1                                 */
    { 0x0484, &undef_Obj1601_2          },  /* Un484:对象字典1601_2                                 */
    { 0x0485, &undef_Obj1601_3          },  /* Un485:对象字典1601_3                                 */
    { 0x0486, &undef_Obj1601_4          },  /* Un486:对象字典1601_4                                 */
    { 0x0487, &undef_Obj1401_1          },  /* Un487:对象字典1401_1                                 */
    { 0x0488, &undef_Obj1401_2          },  /* Un488:对象字典1401_2                                 */
    { 0x0489, &undef_Obj1602_0          },  /* Un489:对象字典1602_0                                 */
    { 0x048A, &undef_Obj1602_1          },  /* Un48A:对象字典1602_1                                 */
    { 0x048B, &undef_Obj1602_2          },  /* Un48B:对象字典1602_2                                 */
    { 0x048C, &undef_Obj1602_3          },  /* Un48C:对象字典1602_3                                 */
    { 0x048D, &undef_Obj1602_4          },  /* Un48D:对象字典1602_4                                 */
    { 0x048E, &undef_Obj1402_1          },  /* Un48E:对象字典1402_1                                 */
    { 0x048F, &undef_Obj1402_2          },  /* Un48F:对象字典1402_2                                 */
    { 0x0490, &undef_Obj1603_0          },  /* Un490:对象字典1603_0                                 */
    { 0x0491, &undef_Obj1603_1          },  /* Un491:对象字典1603_1                                 */
    { 0x0492, &undef_Obj1603_2          },  /* Un492:对象字典1603_2                                 */
    { 0x0493, &undef_Obj1603_3          },  /* Un493:对象字典1603_3                                 */
    { 0x0494, &undef_Obj1603_4          },  /* Un494:对象字典1603_4                                 */
    { 0x0495, &undef_Obj1403_1          },  /* Un495:对象字典1403_1                                 */
    { 0x0496, &undef_Obj1403_2          },  /* Un496:对象字典1403_2                                 */
    /*----------------------------------------------------------------------------------------------*/
    { 0x0511, &undef_CurUphZadj         },  /* Un511:電流検出（U相）零調用データ                 */
    { 0x0512, &undef_CurVphZadj         },  /* Un512:電流検出（V相）零調用データ                 */
    { 0x0513, &undef_CurWphZadj        },  /* Un513:硬件版本                                       */
    { 0x0600, &undef_ScaleAbsPosUser    },  /* Un600:编码器绝对位置(用户单位)                       */
    { 0x0603, &undef_ScaleAbsPos_l      },  /* Un603:编码器绝对位置(L)                             */
    { 0x0605, &undef_ScaleAbsPos_h      },  /* Un605:编码器绝对位置(H)                             */
    { 0x0607, &undef_MechAbsPosL        },  /* Un607:机械绝对坐标(L)                                */
    { 0x0609, &undef_MechAbsPosH        },  /* Un609:机械绝对坐标(H)                                */  
    { 0x060B, &undef_EncLimtM           },  /* Un60B:当前多圈上限值                                 */
    { 0x060D, &undef_EncLimtS           },  /* Un60D:当前单圈上限值                                 */
    { 0x0700, &undef_SamplingTime       },  /* 采样时间单位                                           */
    { 0x0701, &undef_MaxTorque          },  /* 显示数据16384时转矩                                 */
    { 0x0702, &undef_MaxSpeed           },  /* 显示数据16384时速度                                 */
    { 0x0800, &undef_AlmCodeX           },  /* 当前警报代码 [－]                                   */
    { 0x0801, &undef_AlmLtAlmCodeX      },  /* 警报代码                                             */
    { 0x0802, &undef_AlmLtTmStampX      },  /* 当前报警代码时间戳 [100ms]                            */
    { 0x0803, &undef_AlmLtSpdFbkX       },  /* 当前警报发生时的电机旋转/移动速度 [min-1, mm/s]      */
    { 0x0804, &undef_AlmLtSpdRefX       },  /* 当前警报发生时的速度指令 [min-1, mm/s]               */
    { 0x0805, &undef_AlmLtTrqRefX       },  /* 当前警报发生时的内部转矩指令 [%]                       */
    { 0x0806, &undef_AlmLtPosRefSpdX    },  /* 当前警报发生时输入指令脉冲速度 [min-1, mm/s]            */
    { 0x0807, &undef_AlmLtPosErrCntrX   },  /* 当前警报发生时偏差计数器(位置偏差量) [pulse]          */
    { 0x0808, &undef_AlmLtDcVoltxX      },  /* 当前警报发生时主回路母线电压 [V]                       */
    { 0x0809, &undef_AlmLtIqRateX       },  /* 電流検出値 [%]                                        */
    { 0x080A, &undef_AlmLtMotLoad2msX   },  /* 当前警报发生时累计负载率 [%(周期2ms)]              */
    { 0x080B, &undef_AlmLtRegerRate2msX },  /* 当前警报发生时再生负载率 [%(周期2ms)]              */
    { 0x080C, &undef_AlmLtDbrxPower2msX },  /* ＤＢ抵抗消費電力 [%(周期2ms)]                      */
    { 0x080D, &undef_AlmLtMotLoad10sX   },  /* 最大累積負荷率 [%]                                  */
    { 0x080E, &undef_AlmLtJLRatioX      },  /* 慣性モーメント比/重量比 [%]                         */
    { 0x080F, &undef_AlmLtSencComErrCntX},  /* シリアルエンコーダ通信異常回数 [－]                  */
    { 0x0810, &undef_AlmLtInterSignalX  },  /* 内部监视信号 [－]                                   */
    { 0x0814, &undef_AlmLtIntInSignalX  },  /* 内部输入信号监视 [－]                             */
    { 0x0818, &undef_AlmLtIntOutSignalX },  /* 内部输出信号监视 [－]                             */
    { 0x0820, &undef_AlmTrace0          },  /* 警报记录0                                            */
    { 0x0821, &undef_AlmTrace1          },  /* 警报记录1                                            */
    { 0x0822, &undef_AlmTrace2          },  /* 警报记录2                                            */
    { 0x0823, &undef_AlmTrace3          },  /* 警报记录3                                            */
    { 0x0824, &undef_AlmTrace4          },  /* 警报记录4                                            */
    { 0x0825, &undef_AlmTrace5          },  /* 警报记录5                                            */
    { 0x0826, &undef_AlmTrace6          },  /* 警报记录6                                            */
    { 0x0827, &undef_AlmTrace7          },  /* 警报记录7                                            */
    { 0x0828, &undef_AlmTrace8          },  /* 警报记录8                                            */
    { 0x0829, &undef_AlmTrace9          },  /* 警报记录9                                            */
    { 0x0830, &undef_AlmTmStamp0        },  /* 警报记录0时间戳(动作监视)                           */
    { 0x0832, &undef_AlmTmStamp1        },  /* 警报记录1时间戳(动作监视)                           */
    { 0x0834, &undef_AlmTmStamp2        },  /* 警报记录2时间戳(动作监视)                           */
    { 0x0836, &undef_AlmTmStamp3        },  /* 警报记录3时间戳(动作监视)                           */
    { 0x0838, &undef_AlmTmStamp4        },  /* 警报记录4时间戳(动作监视)                           */
    { 0x083A, &undef_AlmTmStamp5        },  /* 警报记录5时间戳(动作监视)                           */
    { 0x083C, &undef_AlmTmStamp6        },  /* 警报记录6时间戳(动作监视)                           */
    { 0x083E, &undef_AlmTmStamp7        },  /* 警报记录7时间戳(动作监视)                           */
    { 0x0840, &undef_AlmTmStamp8        },  /* 警报记录8时间戳(动作监视)                           */
    { 0x0842, &undef_AlmTmStamp9        },  /* 警报记录9时间戳(动作监视)                           */
};
/*--------------------------------------------------------------------------------------------------*/
const   USHORT  UnRegTblEntNum = sizeof(UnRegTbl)/sizeof(UnRegTbl[0]);

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/

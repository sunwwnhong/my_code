/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                     */
/*											2019 ~													*/
/****************************************************************************************************/
/*文件名:Can00_Main.c                                                                                 */
/*创建时间:2017.11.13                                                                                 */
/*版本说明:V1.0                                                                                       */
/*功能描述: CanOpen 通讯部分                                                                            */
/****************************************************************************************************/
#include "Main.h"


void Can_EgearUpdate( void );
void Can_MaxSpdUpdate( void );
void Can_MaxTorqUpdate( void );
void Can_Obj60FFUpdate( void );


/****************************************************************************************************/
/*                                                                                                  */
/*                                      CanOpen_2msLoop                                             */
/*                                                                                                  */
/****************************************************************************************************/
void CanOpen_2msLoop( void )
{
    USHORT	CurAlarm = 0;
    LONG  Datatemp = 0;
    if(  Kprm.f.CanOpenNet )                                /* 判断是否为CanOpen机型               */
    {
        CanOpen402Status_ControlWordDeal( );                    /* 控制字和状态字处理                   */
        CanOpen_ControlModeSel();                               /* CanOpenCAT 控制模式选择            */
        Can_EgearUpdate();
        Can_MaxSpdUpdate();
        Can_MaxTorqUpdate();
        Can_Obj60FFUpdate( );
        HaltParameter_Update( );
        /*------------------------------------------------------------------------------------------*/
        /* 无报警时,清除603F里面的值                                                                     */
        /*------------------------------------------------------------------------------------------*/
        CurAlarm = KpiGetAlarmInfo();
        /*------------------------------------------------------------------------------------------*/
        if( Alm.f.AlmFlag )                                     /* 故障时显示故障代码,优先级最高    */
        {
            ODDatArr[Error_Code].all = CurAlarm;
        }
        else
        {
            ODDatArr[Error_Code].all = 0x0000;
        }
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典【6078】                                                                         */
        /*------------------------------------------------------------------------------------------*/
//        Datatemp = KpiMonCurrentCal1(CoutV.UnCrntDet);
//        if(CinK.IqRefMon >= 0)
//        {
//            ODDatArr[Current_Actual_Value].sall = Datatemp;
//        }
//        else
//        {
//            ODDatArr[Current_Actual_Value].sall = -Datatemp;
//        }
        Datatemp = KpiMonCurrentCal (AinK.IqFbMon) / 100;
        ODDatArr[Current_Actual_Value].sall = Datatemp;
        ODDatArr[ Torque_Actual_Value ].sall = Datatemp;
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典【6079】                                                                         */
        /*------------------------------------------------------------------------------------------*/
        ODDatArr[DcVolt_Actual_Value].all = BinK.UnDcVolt;

        /*------------------------------------------------------------------------------------------*/
        /* 对象字典【6086】                                                                         */
        /*------------------------------------------------------------------------------------------*/
        ODDatArr[Motion_Profile_Type].all = BinK.UnDcVolt * 10;

        /*------------------------------------------------------------------------------------------*/
        ODDatArr[Producer_Code].all = 0xd100;
        ODDatArr[Producer_Code].all = 3;

        /*------------------------------------------------------------------------------------------*/
        if( BinV.f.BaseEnable == 1 )
        {
            if( ODDatArr[Position_Factor_Numer].all == 0 || ODDatArr[Position_Factor_Divisor].all == 0 )
            {
                KPI_ALARMSET(ALM_GEAR);
            }
        }
        /*------------------------------------------------------------------------------------------*/
        /* 示波器通道                                                                               */
        /*------------------------------------------------------------------------------------------*/
        AinK.Ctrl_Word = ODDatArr[ Control_Word ].all;                                    //控制字6040
        AinK.Stus_Word = ODDatArr[ Status_Word ].all;                                     //状态字6041
        AinK.Targe_Pos = ODDatArr[ Targe_Position_MM ].all;                               //目标位置607A
        AinK.Pulse_PosFB = ODDatArr[ Position_Actual_Value_MM ].all;                      //电机位置6064
        AinK.Actual_VelRPM  = ODDatArr[ Velocity_Actual_Value_RPM ].all;                  //电机速度606C
        AinK.Profile_VelRPM = ODDatArr[ Profile_Velocity_RPM ].all;                       //轮廓速度6081
        AinK.InterPos_CMD   = ODDatArr[ Position_CMD_Lowword ].all;                       //插补位置60C1
        AinK.Pos_CMDVal     = ODDatArr[ Postion_Demand_Value ].all;                       //电机位置指令60FC
        AinK.Target_Vel     = ODDatArr[ Target_Velocity_RPM ].all;                        //目标速度60FF

        CanBussOffCheck();  // Can总线异常后恢复

        return;
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                      CanOpen电子齿轮比                                              */
/*                                                                                                  */
/****************************************************************************************************/
static ULONG EgearNumTemp;
static ULONG EgearDenTemp;
void Can_EgearUpdate(void)
{

    /*-------------------------------------对象字典6091---------------------------------------------*/
    if( EgearNumTemp != ODDatArr[Position_Factor_Numer].all  ||
        EgearDenTemp != ODDatArr[Position_Factor_Divisor].all)
    {
        EgearNumTemp     = ODDatArr[Position_Factor_Numer].all ;        // b
        EgearDenTemp     = ODDatArr[Position_Factor_Divisor].all;       // a
        MlibPcalKegear( EgearDenTemp,EgearNumTemp,&Iprm.CANgear );
        CanVar.PosCalFlg = 0;                                      /* 重新计算当前的位置            */
        MencP.FirstFlag = 0;
    }
}
/****************************************************************************************************/
/*                                                                                                  */
/*                                      CanOpen最大速度限制                                         */
/*                                                                                                  */
/****************************************************************************************************/
void Can_MaxSpdUpdate( void )
{
    static ULONG   MaxSpdOld;
    /*-------------------------------------对象字典607F---------------------------------------------*/
    if(MaxSpdOld != ODDatArr[Max_Profile_Velocity].all)
    {
        MaxSpdOld = ODDatArr[Max_Profile_Velocity].all;
        /*     解决速度限制607F仅与对象字典6091电子齿轮比相关 @20240430                             */
        MaxSpdOld = (INT64)MaxSpdOld  * Iprm.Egear.b / Iprm.Egear.a;
#if(FLOAT_USE == 1)
        CanSpdV.CanMaxSpd = (double)MaxSpdOld * 600.0f * Iprm.CANgear.bdiva / (float)MencP.PulseNo;
#else
        CanSpdV.CanMaxSpd = (INT64)MaxSpdOld  * ODDatArr[Position_Factor_Numer].all * 600 / 
                         ((INT64)MencP.PulseNo * ODDatArr[Position_Factor_Divisor].all);
#endif

        CanSpdV.MaxSpdLimt = KpiSpeedLevelCal( CanSpdV.CanMaxSpd, 0 );
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                      CanOpen最大速度限制                                         */
/*                                                                                                  */
/****************************************************************************************************/
void Can_Obj60FFUpdate( void )
{
    static ULONG   Spd60FFOld = 0;
    /*-------------------------------------对象字典607F---------------------------------------------*/
    if(Spd60FFOld != ODDatArr[ Target_Velocity_RPM ].all)
    {
        Spd60FFOld = ODDatArr[ Target_Velocity_RPM ].all;
#if(FLOAT_USE == 1)
        CanSpdV.ReaSpdRef = (double)Spd60FFOld  * 600.0f * Iprm.CANgear.bdiva / (float)MencP.PulseNo;
#else
        CanSpdV.ReaSpdRef = (INT64)Spd60FFOld  * 600 * Iprm.CANgear.b / \
                      (( INT64 )MencP.PulseNo * Iprm.CANgear.a);
#endif
        CanSpdV.ReaSpdRef = KpiSpeedLevelCal( CanSpdV.ReaSpdRef, 0 );
    }
}

LONG MaxTorqOld = 0;
LONG PosTorqOld = 0;
LONG NegTorqOld = 0;
/****************************************************************************************************/
/*                                                                                                  */
/*                                      CanOpen最大转矩限制                                            */
/*                                                                                                  */
/****************************************************************************************************/
void Can_MaxTorqUpdate( void )
{
    if(MaxTorqOld != ODDatArr[Max_Torque].word.LowWord || 
       PosTorqOld != ODDatArr[Positive_torque_limit].word.LowWord ||
       NegTorqOld != ODDatArr[Negtive_torque_limit].word.LowWord )
    {
        MaxTorqOld = ODDatArr[Max_Torque].word.LowWord;
        PosTorqOld = ODDatArr[Positive_torque_limit].word.LowWord;
        NegTorqOld = ODDatArr[Negtive_torque_limit].word.LowWord;

#if(FLOAT_USE == 1)
        CanTorq.MaxTorq     = 10.0f * (float)MaxTorqOld * Iprm.fKtrqlvl;        //[0.1%] --> [2^24/MaxTrq]
        CanTorq.PosTorqLimt = 10.0f * (float)PosTorqOld * Iprm.fKtrqlvl;
        CanTorq.NegTorqLimt = 10.0f * (float)NegTorqOld * Iprm.fKtrqlvl;
#else
        CanTorq.MaxTorq     = KpiTorqueLevelCal( 10 * MaxTorqOld, 0 );          //[0.1%] --> [2^24/MaxTrq]
        CanTorq.PosTorqLimt = KpiTorqueLevelCal( 10 * PosTorqOld, 0 );
        CanTorq.NegTorqLimt = KpiTorqueLevelCal( 10 * NegTorqOld, 0 );
#endif
    }
}

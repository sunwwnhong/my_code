/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                     */
/*                                          2019 ~                                                  */
/****************************************************************************************************/
/*文件名:EtherCAT_Main.c                                                                              */
/*创建时间:2017.11.13                                                                                  */
/*版本说明:V1.0                                                                                        */
/*功能描述:EtherCAT 从机通讯部分                                                                          */
/****************************************************************************************************/
#include "Main.h"

#ifdef CPU1
#include "EtherCAT07_EthSlv.h"
#include "EtherCAT03_ObjDef.h"
#endif




OBJ60FE_01 Obj60FE_01;

USHORT EtherCatALStatus = 0;
void EtherCatODUpdateCheck( void );
void ErrCode_603F( void );
void EtherCAT_ODB_Cia402_Init( void );

USHORT Syncch0Time = 0;

/* EtherCat 周期同步位置模式下滑动平均处理  */
//volatile ULONG EtherCatSyncTimeus = 0;
//#pragma LOCATION(EtherCatSyncTimeus, 0x03A208)

USHORT  EtherCatSyncTimeusOld   = 0;
ULONG   EtherCatSyncSm3Time     = 0;

USHORT u16PositTorqLimitOld = 0;
USHORT u16NegtiTorqLimitOld = 0;
ULONG u32SynchCnt = 0;

ULONG PositionFactor_0Old = 0;
ULONG PositionFactor_1Old = 0;
ULONG Position_b = 0;
ULONG Position_a = 0;
ULONG u32MaxProfileVelOld = 0;

extern USHORT EtherCATErrorCode;
/****************************************************************************************************/
/* 对象字典6091更新处理                                                                             */
/****************************************************************************************************/
LONG PositionFactor0 = 0;
LONG PositionFactor1 = 0;
void Obj6091UpdateCheck( void )
{
ULONG Rata,Ratb;
    if( PositionFactor0 != PositionFactor.aEntries[0] || \
        PositionFactor1 != PositionFactor.aEntries[1] )
    {
        Rata = PositionFactor.aEntries[1];                     /* 电子齿轮——分母                       */
        Ratb = PositionFactor.aEntries[0];                     /* 电子齿轮——分子                       */
        MlibPcalKegear( Rata, Ratb, &Iprm.Ethfgear );
        MencP.FirstFlag = 0;                                   /* 重新计算当前的位置                     */
        /*------------------------------------------------------------------------------------------*/
        PositionFactor0 = PositionFactor.aEntries[0];
        PositionFactor1 = PositionFactor.aEntries[1];
    }
}

//*************************************************************************************************
// 对象字典 606D 更新
//*************************************************************************************************
USHORT u16VelWindow_Old = 0;
void Obj606DUpdateCheck( void )
{
    if( u16VelWindow_Old != u16VelWindow )
    {
        Gprm.EthVcmpSpdLevel = KpiSpeedLevelCal( 10UL * u16VelWindow, 0 );
        u16VelWindow_Old = u16VelWindow;
    }
    return;
}

//*************************************************************************************************
// 对象字典 606F 更新
//*************************************************************************************************
USHORT u16Velthresd_Old = 0;
void Obj606FUpdateCheck( void )
{
    if( u16Velthresd_Old != u16Velthresd )
    {
        Gprm.EthTgonSpdLevel = KpiSpeedLevelCal( 10UL * u16Velthresd, 0 );
        u16Velthresd_Old = u16Velthresd;
    }
    return;
}

//*************************************************************************************************
// 对象字典 6072 更新
//*************************************************************************************************
USHORT u16MaxTorq_Old = 0;
void Obj6072UpdateCheck( void )
{
    if( u16MaxTorq_Old != u16MaxTorq )
    {
        Gprm.EthMaxTorq = KpiTorqueLevelCal( 10UL * u16MaxTorq, 0 );
        u16MaxTorq_Old = u16MaxTorq;
    }
}
/*--------------------------------------------------------------------------------------------------*/
/*      6072 及时更新处理                                                                              */
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*                                                                                                  */
/*                                       EtherCAT Init                                              */
/*                                                                                                  */
/****************************************************************************************************/
void EtherCAT_Init( void )
{
LONG lkx;


    if( Kprm.f.CanOpenNet == 1 )
    {
        PosLatch_Init(  );
        return;
    }

    if( Kprm.f.EtherCATNet == 0 )
    {
        return;
    }

    if( CIA402_CAN_PRM_TEST )
    {
        EtherCAT_ODB_Cia402_Init( );
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  特定对象字典初始化( 主要为只读对象字典 )                                                    */
    /*----------------------------------------------------------------------------------------------*/
    u32SuppDriveModes = 0x000003AD;                         /* 对象字典【0x6502】                   */
    u32MotorRateCur  = Prm.irat * 100UL;                    /* 对象字典【0x6075】                   */
    u32MotorRateTorq = Prm.rattrq * 10UL;                   /* 对象字典【0x6076】                   */
    u32MaxMotorSpd   = ((Prm.vrat_max.b.h) + Prm.MaxspdTun) * 100UL;       /* 对象字典【0x6080】          */

    /*----------------------------------------------------------------------------------------------*/
    /* 电子齿轮比计算                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    ULONG Rata = PositionFactor.aEntries[1];                /* 电子齿轮——分母                       */
    ULONG Ratb = PositionFactor.aEntries[0];                /* 电子齿轮——分子                       */
    MlibPcalKegear( Rata, Ratb, &Iprm.Ethfgear );

    /*----------------------------------------------------------------------------------------------*/
    /* 速度一致检出幅值                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    Gprm.EthVcmpSpdWrmLev = KpiSpeedLevelCal( 10UL * Prm.vcmplv, 0 );
    
    /*----------------------------------------------------------------------------------------------*/
    /* 电机旋转检出幅值                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    Gprm.EthTgonSpdLevel = KpiSpeedLevelCal( 10UL * u16Velthresd, 0 );
    
    /*----------------------------------------------------------------------------------------------*/
    /* 最大转矩                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    Gprm.EthMaxTorq = KpiTorqueLevelCal( 10UL * u16MaxTorq, 0 );          /* [0.1%] --> [2^24/MaxTrq]   */
    /*----------------------------------------------------------------------------------------------*/
    /* 正向最大转矩                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    Gprm.EthMaxPTorq = KpiTorqueLevelCal( 10UL * u16PositTorqLimit, 0 ); /* [0.1%] --> [2^24/MaxTrq]    */
    Gprm.EthMaxNTorq = KpiTorqueLevelCal( 10UL * u16NegtiTorqLimit, 0 ); /* [0.1%] --> [2^24/MaxTrq]    */
    
    /*----------------------------------------------------------------------------------------------*/
    /* 最大速度     【0x607F】          转换成 0.1rpm 单位                                                */
    /*----------------------------------------------------------------------------------------------*/
    lkx = (LONG)(( INT64 )u32MaxProfileVel * Iprm.Egear.b / Iprm.Egear.a);
    Gprm.EthMaxSpd = (INT64)lkx  * PositionFactor.aEntries[0] * 600 / 
                     ((INT64)MencP.PulseNo * PositionFactor.aEntries[1]);
    if( Gprm.EthMaxSpd < 0 )
    {
        Gprm.EthMaxSpd = u32MaxMotorSpd * 10;
    }
    else if( Gprm.EthMaxSpd >= ( u32MaxMotorSpd * 10UL ))
    {
        Gprm.EthMaxSpd = u32MaxMotorSpd * 10UL;
    }
    
    u32MaxProfileVelOld = u32MaxProfileVel;
    Iprm.EthCatMaxSpd = KpiSpeedLevelCal( Gprm.EthMaxSpd, 0 );
    
    /*----------------------------------------------------------------------------------------------*/
    /*  数据链路错误检查                                                                            */
    /*----------------------------------------------------------------------------------------------*/
    DataLink_Init( );
    
    PosLatch_Init(  );

    // 站点别名
#ifdef CPU1
    if( 0 != Prm.EtherCatAddr )
    {
        ESC_writeWord(Prm.EtherCatAddr,0x0012);
    }

    // 产品码
    if( Kprm.f.AxisNum == 1 )
    {
        sIdentity.u32Productcode = 0x03001002;
    }
    else
    {
        sIdentity.u32Productcode = 0x03001001;
    }
    // Eeprom 是否正确装载

    USHORT TmpVar = 0;
    HW_EscReadWord(TmpVar, ESC_EEPROM_CONTROL_OFFSET);
    TmpVar = SWAPWORD(TmpVar);

    if (((TmpVar & ESC_EEPROM_ERROR_CRC) > 0) || ((TmpVar & ESC_EEPROM_ERROR_LOAD) > 0))
    {
        KPI_ALARMSET( ALM_EET_Eeprom );
    }

#endif
}


extern void ServoEmcyCheck( void );
USHORT EtherCatRunStatus = 0;
/****************************************************************************************************/
/*                                                                                                  */
/*                                      EtherCAT_2msLoop                                            */
/*                                                                                                  */
/****************************************************************************************************/
void EtherCAT_2msLoop( void )
{
ULONG Synch0;
ULONG Rata,Ratb;
float Ratio = 0.0f;
    /*----------------------------------------------------------------------------------------------*/
    if( Kprm.f.EtherCATNet )                                /* 判断是否为EtherCAT机型               */
    {
//        EtherCATApplication_Main( );      20221230                  /* EtherCAT 应用层主程序                */
        Ds402Status_ControlWordDeal( );                     /* 控制字和状态字处理                   */
        EtherCAT_ControlModeSel( );                         /* EtherCAT 控制模式选择                */
#ifdef CPU1
        //-----------------------------------------------------------------------------------------
        // EtherCAT 连接状态

        if( bEcatOutputUpdateRunning == 1 )
        {
            EtherCatRunStatus = 1;
        }

        if( EtherCatRunStatus == 1 )
        {
            if( bEcatOutputUpdateRunning == 1 )
            {
                KPI_WARNINGCLR( WRN_SYNC0 );
            }
            else
            {
                if(CAN_EXFUNC1_3_EN)
                {
                    KPI_ALARMSET(ALM_EET_SYNC0);
                }
                else
                {
                    KPI_WARNINGSET( WRN_SYNC0 );
                }

            }
        }
        //-----------------------------------------------------------------------------------------
        ServoEmcyCheck( );                                  // EtherCAT 紧急报文处理
#endif
        //-----------------------------------------------------------------------------------------
        EtherCatODUpdateCheck( );                           /* 对象字典值更新处理                   */
#ifdef CPU1
        Synch0 = sSyncManOutPar.u32Sync0CycleTime % 125000; /* 同步周期非125us 整数倍               */
        Syncch0Time = (USHORT)((float)sSyncManOutPar.u32Sync0CycleTime * 0.000008f);
#endif
        EtherCatHaltParameter_Update( );                    /* 暂停参数更新                         */

        
        /*------------------------------------------------------------------------------------------*/
        Obj60FE_01.Dw = (u32DigitOutput.aEntries[ 1 ]) >> 16; /* Y 输出                               */
        
        /*------------------------------------------------------------------------------------------*/
#ifdef CPU1
        if( Synch0 != 0 )
        {
            KPI_ALARMSET( ALM_EET_SYNCH0 );
        }

        /*------------------------------------------------------------------------------------------*/
        /* EtherCat 周期同步位置模式下,位置指令进行滑动平均滤波处理                                 */
        /*------------------------------------------------------------------------------------------*/
        EtherCatSyncTimeus = (USHORT)((float)sSyncManOutPar.u32Sync0CycleTime * 0.001f);
        if( EtherCatSyncTimeus == 0 )
        {
            EtherCatSyncTimeus = (USHORT)((float)sSyncManOutPar.u32MinCycleTime * 0.001f);
        }
#endif

        if( EtherCatSyncTimeus != EtherCatSyncTimeusOld )
        {
            PcalPcmdMoveAvergeFilter( Prm.mafil,1 );
            PcalPcmdExpFilter( Prm.expfil, 1 );
            
            EtherCatSyncTimeusOld = EtherCatSyncTimeus;
            u32SynchCnt = (float)EtherCatSyncTimeus / 125.0f;
        }

        /*------------------------------------------------------------------------------------------*/
        /* 检查用户是否有设置不支持的操作模式                                                       */
        /*------------------------------------------------------------------------------------------*/
        switch( s8ModeofOP )
        {
            /*--------------------------------------------------------------------------------------*/
            case 0:
            case 1:
            case 3:
            case 4:
            case 6:
            case 8:
            case 9:
            case 10:
            case 5:
                break;
            /*--------------------------------------------------------------------------------------*/
            default:
                if(( Prm.almmsk1 & 0x0010 ) == 0x0010 )
                {
                    KPI_ALARMSET( ALM_EET_OPER );
                }
                break;
            /*--------------------------------------------------------------------------------------*/
        }
        
/*--------------------------------------------------------------------------------------------------*/
/*      伺服ON时对电子齿轮比的范围进行相关的检查处理                                                           */
/*--------------------------------------------------------------------------------------------------*/
        if( BinV.f.BaseEnable == 1 )
        {
            Rata = PositionFactor.aEntries[1];                     /* 电子齿轮——分母                */
            Ratb = PositionFactor.aEntries[0];                     /* 电子齿轮——分子                */    
            Ratio = (float)Ratb / (float)Rata;
            if( Ratio > 64000.0 || Ratio < 0.001 )
            {
                KPI_ALARMSET( ALM_GEAR );
            }
            if( PositionFactor.aEntries[0] == 0 || PositionFactor.aEntries[1] == 0 )
            {
                KPI_ALARMSET(ALM_GEAR);
            }
        }
        /*------------------------------------------------------------------------------------------*/
#if 1
        Synch0 = (float)EtherCatSyncTimeus * 2.0f / 125.0f;
        if( Synch0 < 5 )
        {
            EtherCatSyncSm3Time = 0;
        }
        else
        {
            EtherCatSyncSm3Time = Synch0 - 3;
        }
#endif
        
        Obj6091UpdateCheck( );   // 6091 更新检查

        Obj606DUpdateCheck( );   // 606D 更新检查

        Obj606FUpdateCheck( );   // 606F 更新检查

        Obj6072UpdateCheck( );   // 6072 更新

        /*------------------------------------------------------------------------------------------*/
        /* 对象字典60E0 更新检查                                                                        */
        /*------------------------------------------------------------------------------------------*/
        if( u16PositTorqLimitOld != u16PositTorqLimit )
        {
            Gprm.EthMaxPTorq = KpiTorqueLevelCal( 10 * u16PositTorqLimit, 0 ); /* [0.1%] --> [2^24/MaxTrq]  */
            u16PositTorqLimitOld = u16PositTorqLimit;
        }
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典60E1 更新检查                                                                        */
        /*------------------------------------------------------------------------------------------*/
        if( u16NegtiTorqLimitOld != u16NegtiTorqLimit )
        {
            Gprm.EthMaxNTorq = KpiTorqueLevelCal( 10 * u16NegtiTorqLimit, 0 ); /* [0.1%] --> [2^24/MaxTrq]  */
            u16NegtiTorqLimitOld = u16NegtiTorqLimit;
        }
        
        /*------------------------------------------------------------------------------------------*/
        /* 警告代码更新至603F                                                                          */
        /*------------------------------------------------------------------------------------------*/
        ErrCode_603F( );
        
        /*------------------------------------------------------------------------------------------*/
        /* 【6078】电流瞬间输出(Current actual value)                                                   */
        /*------------------------------------------------------------------------------------------*/
//        if(ECAT_402_COUNT_UNIT)
//        {
//            s16CurrentActVal = KpiMonCurrentCal (AinK.IqFbMon) / 100;
//        }
//        else
//        {
//            s16CurrentActVal = KpiMonCurrentCal1( CoutV.UnCrntRef );
//        }

        //20260311@ syhu FUWEI客户临时处理 TODO
        if( Prm.Pn543 == 1 )
        {
            s16CurrentActVal = -KpiMonCurrentCal (AinK.IqFbMon) / 100;
            u16TorqActVal =  s16CurrentActVal;
        }
        else
        {
            s16CurrentActVal = KpiMonCurrentCal (AinK.IqFbMon) / 100;
            u16TorqActVal =  s16CurrentActVal;
        }
        
        /*------------------------------------------------------------------------------------------*/
        /* 数据链路错误计数器                                                                            */
        /*------------------------------------------------------------------------------------------*/        
        DataLink_Deal( );
        /*------------------------------------------------------------------------------------------*/
        /* 示波器通道显示                                                                           */
        /*------------------------------------------------------------------------------------------*/
        AinK.Ctrl_Word = u16ControlWord;                                                  //控制字6040
        AinK.Stus_Word = u16StatusWord;                                                   //状态字6041
        AinK.Targe_Pos = s32TargetPos;                                                    //目标位置607A
        AinK.Pulse_PosFB = s32PosActVal;                                                  //电机位置6064
        AinK.Actual_VelRPM  = s32VelActualVal;                                            //电机速度606C
        AinK.Profile_VelRPM = u32ProfileVel;                                              //轮廓速度6081
        AinK.InterPos_CMD   = InterPolDataRecord.u32PosCmd;                               //插补位置60C1
        AinK.Pos_CMDVal     = s32PosDemandVal;                                            //电机位置指令60FC
        AinK.Target_Vel     = s32TargetVel;                                               //目标速度60FF
    }
    else
    {
        EtherCatSyncTimeus = 0;
    }





    return;
}


/****************************************************************************************************/
/*                                                                                                  */
/*                                  EtherCAT 运行状态监控                                              */
/*                                                                                                  */
/****************************************************************************************************/
USHORT EtherCAT_StatusMonitor( void )
{
    USHORT PorLinkStatus =  0;
#ifdef CPU1
    USHORT ESC_DL_Status = 0;
    
    if( Kprm.f.EtherCATNet == 0 )
    {
        return 0;
    }

    ESC_DL_Status = ESC_readWord(0x0110U);
    /*----------------------------------------------------------------------------------------------*/
    /*  端口连接状态                                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    
    
    if( ESC_DL_Status & 0x0010 )
    {
        PorLinkStatus |= 0x01;
    }
    if( ESC_DL_Status & 0x0020)
    {
        PorLinkStatus |= 0x02;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 端口通讯状态                                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if( ESC_DL_Status & 0x0200 )
    {
        PorLinkStatus |= 0x10;
    }
    else
    {
        PorLinkStatus &= 0xFE;
    }
    if( ESC_DL_Status & 0x0800)
    {
        PorLinkStatus |= 0x20;
    }

    PorLinkStatus = (PorLinkStatus) << 8;
    PorLinkStatus |= ((((USHORT)(nAlStatus & 0x0F)) << 4 ) | s8ModeofOP);
    return PorLinkStatus;
#endif

}


/****************************************************************************************************/
/*                                                                                                  */
/*                                  EtherCAT 站点正名监控                                              */
/*                                                                                                  */
/****************************************************************************************************/
USHORT EtherCAT_StationMonitor( UCHAR Type )
{
USHORT EtherCATName = 0;
    
    if( Kprm.f.EtherCATNet == 0 ) return 0;
    if( Type == 0 )
    {
//        EtherCATName = ET1100RegisterRead( 0x0010 );      20221230        /* 站点正名                       */
    }
    else
    {
//        EtherCATName = ET1100RegisterRead( 0x0012 );      20221230        /* 站点别名                       */
    }
    return EtherCATName;
}


/****************************************************************************************************/
/*                                                                                                  */
/*                                  EtherCAT AL 状态寄存器                                             */
/*                                                                                                  */
/****************************************************************************************************/
USHORT EtherCAT_ALStatus( void )
{
USHORT ALStatus = 0;
#ifdef CPU1
    if( Kprm.f.EtherCATNet == 0 )
    {
        return 0;
    }

    ALStatus = ESC_readWord( 0x0134U );
#endif
    return ALStatus;
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                  EtherCAT Synch0 周期时间                                        */
/*                                                                                                  */
/****************************************************************************************************/
USHORT EtherCat_Sync0CycleTime( void )
{
    USHORT Sych0Time = 0;
#ifdef CPU1
    Sych0Time = (ULONG)((float)sSyncManOutPar.u32Sync0CycleTime * 0.001f);
#endif
    return Sych0Time;
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                  动态监测对象字典值是否有更新                                            */
/*                                                                                                  */
/****************************************************************************************************/
void EtherCatODUpdateCheck( void )
{
INT64 lkx;
    /*----------------------------------------------------------------------------------------------*/
    /*  最大轮廓速度单位转换                                                                              */
    /*----------------------------------------------------------------------------------------------*/
    if( ( u32MaxProfileVelOld != u32MaxProfileVel ) || \
        ( PositionFactor_0Old != PositionFactor.aEntries[0] ) || \
        ( PositionFactor_1Old != PositionFactor.aEntries[1] ) || \
        (  Position_a         != Iprm.Egear.a )               || \
        ( Position_b          != Iprm.Egear.b))
    {
      
        u32MaxProfileVelOld = u32MaxProfileVel;
        PositionFactor_0Old = PositionFactor.aEntries[0];
        PositionFactor_1Old = PositionFactor.aEntries[1];
        
        Position_a = Iprm.Egear.a;
        Position_b = Iprm.Egear.b;

        lkx = (LONG)(( INT64 )u32MaxProfileVel * Iprm.Egear.b / Iprm.Egear.a);
        
        Gprm.EthMaxSpd = (INT64)lkx  * PositionFactor.aEntries[0] * 600 / 
                         ((INT64)MencP.PulseNo * PositionFactor.aEntries[1]);
        if( Gprm.EthMaxSpd < 0 )
        {
            Gprm.EthMaxSpd = u32MaxMotorSpd * 10;
        }
        else if( Gprm.EthMaxSpd >= ( u32MaxMotorSpd * 10 ))
        {
            Gprm.EthMaxSpd = u32MaxMotorSpd * 10;
        }        
        Iprm.EthCatMaxSpd = KpiSpeedLevelCal( Gprm.EthMaxSpd, 0 );
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*                          警告代码上传至对象字典603F,但不发送紧急报文                                       */
/*                                                                                                  */
/****************************************************************************************************/
void ErrCode_603F( void )
{
#if 1 /*修复第一次上电报警而没有确定EtherCAT机型造成603F对象字典为0的bug*/
USHORT  CurAlarm = 0;
    if( Alm.f.AlmFlag == 1 && u16ErrCode == 0x0000 )
    {
        u16ErrCode = EtherCATErrorCode;                           //解决603F故障不上传问题

        CurAlarm = KpiGetAlarmInfo();
        if( CurAlarm == 0x0021 )
        {
            u16ErrCode = 0x6001;
        }
    }

    if( Alm.f.AlmFlag == 0 )
    {
        if(Alm.f.WrnFlag == 0)
            u16ErrCode = 0;
        else
        {
            u16ErrCode =  Alm.OpWrnCode + 0x5000;
        }
    }

#endif
    return;
}


/****************************************************************************************************/
/* Function Name:Obj6040Up                                                                          */
/* Function Description: 对象字典0x6040 相关变量更新                                                */
/****************************************************************************************************/
void Obj6040Up()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16ControlWord = (SHORT)Prm.OBJ_6040;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
       ODDatArr[ Control_Word ].all = (SHORT)Prm.OBJ_6040;
}

/****************************************************************************************************/
/* Function Name:Obj605AUp                                                                          */
/* Function Description: 对象字典0x605A 相关变量更新                                                */
/****************************************************************************************************/
void Obj605AUp()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s16QuickShutdownOpt = (SHORT)Prm.OBJ_605A;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
       ODDatArr[ Quick_stop_option_code ].all = (SHORT)Prm.OBJ_605A;
}

/****************************************************************************************************/
/* Function Name:Obj605DUp                                                                          */
/* Function Description: 对象字典0x605A 相关变量更新                                                */
/****************************************************************************************************/
void Obj605DUp()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s16HaltOptioncode = (SHORT)Prm.OBJ_605D;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
       ODDatArr[ Halt_option_code ].all = (SHORT)Prm.OBJ_605D;
}


/****************************************************************************************************/
/* Function Name:Obj605DUp                                                                          */
/* Function Description: 对象字典0x6060 相关变量更新                                                */
/****************************************************************************************************/
void Obj6060Up()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s8ModeofOP = (SHORT)Prm.OBJ_6060;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
       ODDatArr[ Operation_Mode ].all = (SHORT)Prm.OBJ_6060;
}



/****************************************************************************************************/
/* Function Name:Obj6065Up                                                                          */
/* Function Description: 对象字典0x6065 相关变量更新                                                */
/****************************************************************************************************/
void Obj6065Up()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      u32FollowErrWind = ULONGOF( Prm.OBJ_6065_L, Prm.OBJ_6065_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Follow_Error_Window_MM ].all = ULONGOF( Prm.OBJ_6065_L, Prm.OBJ_6065_H );
}

/****************************************************************************************************/
/* Function Name:Obj6067Up                                                                          */
/* Function Description: 对象字典0x6067 相关变量更新                                                */
/****************************************************************************************************/
void Obj6067Up()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32PosWindow = ULONGOF( Prm.OBJ_6067_L, Prm.OBJ_6067_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Position_Window_MM ].all = ULONGOF( Prm.OBJ_6067_L, Prm.OBJ_6067_H );
}



/****************************************************************************************************/
/* Function Name:Obj6068Up                                                                          */
/* Function Description: 对象字典0x6068 相关变量更新                                                */
/****************************************************************************************************/
void Obj6068Up()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16PosWindowTime = ULONGOF( Prm.OBJ_6068_L, Prm.OBJ_6068_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Position_Window_Time_MS ].all = ULONGOF( Prm.OBJ_6068_L, Prm.OBJ_6068_H );
}

/****************************************************************************************************/
/* Function Name:Obj606DUp                                                                          */
/* Function Description: 对象字典0x606D 相关变量更新                                                */
/****************************************************************************************************/
void Obj606DUp()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16VelWindow = (SHORT)Prm.OBJ_606D;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
        ODDatArr[ Velocity_Window_RPM ].all = (SHORT)Prm.OBJ_606D;
}

/****************************************************************************************************/
/* Function Name:Obj606EUp                                                                          */
/* Function Description: 对象字典0x606E 相关变量更新                                                */
/****************************************************************************************************/
void Obj606EUp()
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16VelWindowTime = (SHORT)Prm.OBJ_606E;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
        ODDatArr[ Velocity_Window_Time_MS ].all = (SHORT)Prm.OBJ_606E;
}

/****************************************************************************************************/
/* Function Name:Obj606FUp                                                                          */
/* Function Description: 对象字典0x606F 相关变量更新                                                */
/****************************************************************************************************/
void Obj606FUp( void )
{
   if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
       u16Velthresd = (SHORT)Prm.OBJ_606F;
   else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Zero_Velocity_Threshold ].all = (SHORT)Prm.OBJ_606F;
}

/****************************************************************************************************/
/* Function Name:Obj6070Up                                                                          */
/* Function Description: 对象字典0x6070 相关变量更新                                                */
/****************************************************************************************************/
void Obj6070Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
       u16VelthresdTime = (SHORT)Prm.OBJ_6070;
   else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Zero_Velocity_Time_MS ].all = (SHORT)Prm.OBJ_6070;
}

/****************************************************************************************************/
/* Function Name:Obj6071Up                                                                          */
/* Function Description: 对象字典0x6071 相关变量更新                                                */
/****************************************************************************************************/
void Obj6071Up( void )
{
   if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
       s16TargTorq = (SHORT)Prm.OBJ_6071;
   else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Target_Torque ].all = (SHORT)Prm.OBJ_6071;
}

/****************************************************************************************************/
/* Function Name:Obj6072Up                                                                          */
/* Function Description: 对象字典0x6072 相关变量更新                                                */
/****************************************************************************************************/
void Obj6072Up( void )
{
   if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
       u16MaxTorq = (SHORT)Prm.OBJ_6072;
   else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Max_Torque ].all = (SHORT)Prm.OBJ_6072;
}


/****************************************************************************************************/
/* Function Name:Obj607AUp                                                                          */
/* Function Description: 对象字典0x6065 相关变量更新                                                */
/****************************************************************************************************/
void Obj607AUp( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      s32TargetPos = ULONGOF( Prm.OBJ_607A_L, Prm.OBJ_607A_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Targe_Position_MM ].all= ULONGOF( Prm.OBJ_607A_L, Prm.OBJ_607A_H );
}


/****************************************************************************************************/
/* Function Name:Obj607CUp                                                                          */
/* Function Description: 对象字典0x607C 相关变量更新                                                */
/****************************************************************************************************/
void Obj607CUp( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      s32HomeOffset = ULONGOF( Prm.OBJ_607C_L, Prm.OBJ_607C_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Homing_Offset_MM ].all= ULONGOF( Prm.OBJ_607C_L, Prm.OBJ_607C_H );
}

/****************************************************************************************************/
/* Function Name:Obj607D 01Up                                                                          */
/* Function Description: 对象字典0x607D 01 相关变量更新                                                */
/****************************************************************************************************/
void Obj607D_1Up( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      SoftPosLimit.aEntries[0] = ULONGOF( Prm.OBJ_607D_01_L, Prm.OBJ_607D_01_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Min_Soft_Posi_Limit ].all= ULONGOF( Prm.OBJ_607D_01_L, Prm.OBJ_607D_01_H );
}

/****************************************************************************************************/
/* Function Name:Obj607D 02Up                                                                          */
/* Function Description: 对象字典0x607D 02 相关变量更新                                                */
/****************************************************************************************************/
void Obj607D_2Up( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      SoftPosLimit.aEntries[1] = ULONGOF( Prm.OBJ_607D_02_L, Prm.OBJ_607D_02_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Max_Soft_Posi_Limit ].all= ULONGOF( Prm.OBJ_607D_02_L, Prm.OBJ_607D_02_H);
}

/****************************************************************************************************/
/* Function Name:Obj607E                                                                         */
/* Function Description: 对象字典0x607E 相关变量更新                                                */
/****************************************************************************************************/
void Obj607EUp( void )
{
   if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      u8Polarity = (SHORT)Prm.OBJ_607E;
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Polarity ].all= (SHORT)Prm.OBJ_607E;
}

/****************************************************************************************************/
/* Function Name:Obj607F                                                                         */
/* Function Description: 对象字典0x607F 相关变量更新                                                */
/****************************************************************************************************/
void Obj607FUp( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
  {
      u32MaxProfileVel = ULONGOF( Prm.OBJ_607F_L, Prm.OBJ_607F_H);
  }
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Max_Profile_Velocity ].all= ULONGOF( Prm.OBJ_607F_L, Prm.OBJ_607F_H);
}

/****************************************************************************************************/
/* Function Name:Obj6080                                                                         */
/* Function Description: 对象字典0x6080 相关变量更新                                                */
/****************************************************************************************************/
void Obj6080Up( void )
{
  /*
  //只读参数取消更新		
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST)

      u32MaxMotorSpd = ULONGOF( Prm.OBJ_6080_L, Prm.OBJ_6080_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Max_Motor_Speed_RPM ].all= ULONGOF( Prm.OBJ_6080_L, Prm.OBJ_6080_H);*/
}

/****************************************************************************************************/
/* Function Name:Obj6081                                                                         */
/* Function Description: 对象字典0x6081 相关变量更新                                                */
/****************************************************************************************************/
void Obj6081Up( void )
{
  if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      u32ProfileVel = ULONGOF( Prm.OBJ_6081_L, Prm.OBJ_6081_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Profile_Velocity_RPM ].all= ULONGOF( Prm.OBJ_6081_L, Prm.OBJ_6081_H);
}

/****************************************************************************************************/
/* Function Name:Obj6083                                                                         */
/* Function Description: 对象字典0x6083 相关变量更新                                                */
/****************************************************************************************************/
void Obj6083Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      u32ProfileAcc = ULONGOF( Prm.OBJ_6083_L, Prm.OBJ_6083_H);
  else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
    ODDatArr[Profile_Acceleration ].all= ULONGOF( Prm.OBJ_6083_L, Prm.OBJ_6083_H);
}


/****************************************************************************************************/
/* Function Name:Obj6084Up                                                                          */
/* Function Description: 对象字典0x6084 相关变量更新                                                */
/****************************************************************************************************/
void Obj6084Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      u32ProfileDec = ULONGOF( Prm.OBJ_6084_L, Prm.OBJ_6084_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[Profile_Deceleration ].all= ULONGOF( Prm.OBJ_6084_L, Prm.OBJ_6084_H );
}

/****************************************************************************************************/
/* Function Name:Obj6085Up                                                                          */
/* Function Description: 对象字典0x6084 相关变量更新                                                */
/****************************************************************************************************/
void Obj6085Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32QuickStopDec = ULONGOF( Prm.OBJ_6085_L, Prm.OBJ_6085_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[Quick_Stop_Deceleration ].all= ULONGOF( Prm.OBJ_6085_L, Prm.OBJ_6085_H );
}

/****************************************************************************************************/
/* Function Name:Obj6087Up                                                                          */
/* Function Description: 对象字典0x6087 相关变量更新                                                */
/****************************************************************************************************/
void Obj6087Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32TorqueSlope = ULONGOF( Prm.OBJ_6087_L, Prm.OBJ_6087_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[Torque_Slope_MS ].all= ULONGOF( Prm.OBJ_6087_L, Prm.OBJ_6087_H );
}

/****************************************************************************************************/
/* Function Name:Obj6091 01Up                                                                          */
/* Function Description: 对象字典0x6091 01 相关变量更新                                                */
/****************************************************************************************************/
void Obj6091_1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      PositionFactor.aEntries[ 0 ] = ULONGOF( Prm.OBJ_6091_01_L, Prm.OBJ_6091_01_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Position_Factor_Numer].all= ULONGOF( Prm.OBJ_6091_01_L, Prm.OBJ_6091_01_H);
}

/****************************************************************************************************/
/* Function Name:Obj6091_2Up                                                                       */
/* Function Description: 对象字典0x6092 02 相关变量更新                                                */
/****************************************************************************************************/
void Obj6091_2Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      PositionFactor.aEntries[ 1 ] = ULONGOF( Prm.OBJ_6091_02_L, Prm.OBJ_6091_02_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Position_Factor_Divisor].all= ULONGOF( Prm.OBJ_6091_02_L, Prm.OBJ_6091_02_H );
}

/****************************************************************************************************/
/* Function Name:Obj6098Up                                                                          */
/* Function Description: 对象字典0x6098 相关变量更新                                                */
/****************************************************************************************************/
void Obj6098Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s8HomingMethod = (SHORT)Prm.OBJ_6098;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Homing_Method].all= (SHORT)Prm.OBJ_6098;
}


/****************************************************************************************************/
/* Function Name:Obj6099 01Up                                                                          */
/* Function Description: 对象字典0x6099 01 相关变量更新                                                */
/****************************************************************************************************/
void Obj6099_1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        HomingSpeed.aEntries[0] = LONGOF( Prm.OBJ_6099_01_L, Prm.OBJ_6099_01_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Search_Switch_Spd].all= LONGOF( Prm.OBJ_6099_01_L, Prm.OBJ_6099_01_H );
}

/****************************************************************************************************/
/* Function Name:Obj6099 02Up                                                                          */
/* Function Description: 对象字典0x6099 02 相关变量更新                                                */
/****************************************************************************************************/
void Obj6099_2Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        HomingSpeed.aEntries[1] = LONGOF( Prm.OBJ_6099_02_L, Prm.OBJ_6099_02_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Search_Zero_Spd].all= LONGOF( Prm.OBJ_6099_02_L, Prm.OBJ_6099_02_H );
}

/****************************************************************************************************/
/* Function Name:Obj609AUp                                                                          */
/* Function Description: 对象字典0x609A 相关变量更新                                                */
/****************************************************************************************************/
void Obj609AUp( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32HomingAcc = LONGOF( Prm.OBJ_609A_L, Prm.OBJ_609A_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Homing_Acceleration].all= LONGOF( Prm.OBJ_609A_L, Prm.OBJ_609A_H );
}

/****************************************************************************************************/
/* Function Name:Obj60B0Up                                                                          */
/* Function Description: 对象字典0x60B0 相关变量更新                                                */
/****************************************************************************************************/
void Obj60B0Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s32PositionOffset = LONGOF( Prm.OBJ_60B0_L, Prm.OBJ_60B0_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Postion_Offset].all= LONGOF( Prm.OBJ_60B0_L, Prm.OBJ_60B0_H );
}

/****************************************************************************************************/
/* Function Name:Obj60B1Up                                                                          */
/* Function Description: 对象字典0x60B1 相关变量更新                                                */
/****************************************************************************************************/
void Obj60B1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s32VelocityOffset = LONGOF( Prm.OBJ_60B1_L, Prm.OBJ_60B1_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Spd_Offset].all= LONGOF( Prm.OBJ_60B1_L, Prm.OBJ_60B1_H );
}

/****************************************************************************************************/
/* Function Name:Obj60B2Up                                                                          */
/* Function Description: 对象字典0x60B2 相关变量更新                                                */
/****************************************************************************************************/
void Obj60B2Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        s16TorqueOffset = (SHORT) Prm.OBJ_60B2_L;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Torque_Offset].all= (SHORT) Prm.OBJ_60B2_L;
}

/****************************************************************************************************/
/* Function Name:Obj60B8Up                                                                          */
/* Function Description: 对象字典0x60B8 相关变量更新                                                */
/****************************************************************************************************/
void Obj60B8Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16TouchProbeFun = (SHORT)Prm.OBJ_60B8;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ TouchProbe_Fun].all= (SHORT)Prm.OBJ_60B8;
}

/****************************************************************************************************/
/* Function Name:Obj60C1 01Up                                                                          */
/* Function Description: 对象字典0x60C1 01 相关变量更新                                                */
/****************************************************************************************************/
void Obj60C1_1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        InterPolDataRecord.u32PosCmd = LONGOF( Prm.OBJ_60C1_01_L, Prm.OBJ_60C1_01_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Position_CMD_Lowword].all= LONGOF( Prm.OBJ_60C1_01_L, Prm.OBJ_60C1_01_H );
}

/****************************************************************************************************/
/* Function Name:Obj60C1 01Up                                                                          */
/* Function Description: 对象字典0x60C1 01 相关变量更新                                                */
/****************************************************************************************************/
void Obj60C2_1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        InterPolTimePeriod.u8InterpolationPeriod = (SHORT)Prm.OBJ_60C2_01;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Interpolation_Period_Unit].all= (SHORT)Prm.OBJ_60C2_01;
}

/****************************************************************************************************/
/* Function Name:Obj60C2_02Up                                                                          */
/* Function Description: 对象字典0x60C2 02 相关变量更新                                                */
/****************************************************************************************************/
void Obj60C2_2Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
         InterPolTimePeriod.i8InterpolationIndex = (SHORT)Prm.OBJ_60C2_02;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
         ODDatArr[ Interpolation_Period_Index].all= (SHORT)Prm.OBJ_60C2_02;
}

/****************************************************************************************************/
/* Function Name:Obj60C5Up                                                                          */
/* Function Description: 对象字典0x60C5 相关变量更新                                                */
/****************************************************************************************************/
void Obj60C5Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32MaxAcc = LONGOF( Prm.OBJ_60C5_L, Prm.OBJ_60C5_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Max_Acceleration].all= LONGOF( Prm.OBJ_60C5_L, Prm.OBJ_60C5_H );
}

/****************************************************************************************************/
/* Function Name:Obj60C6Up                                                                          */
/* Function Description: 对象字典0x60C6 相关变量更新                                                */
/****************************************************************************************************/
void Obj60C6Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u32MaxDec = LONGOF( Prm.OBJ_60C6_L, Prm.OBJ_60C6_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Max_Deceleration].all= LONGOF( Prm.OBJ_60C6_L, Prm.OBJ_60C6_H );
}

/****************************************************************************************************/
/* Function Name:Obj60E0Up                                                                          */
/* Function Description: 对象字典0x60E0 相关变量更新                                                */
/****************************************************************************************************/
void Obj60E0Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16PositTorqLimit = (SHORT)Prm.OBJ_60E0;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Positive_torque_limit].all= (SHORT)Prm.OBJ_60E0;
}

/****************************************************************************************************/
/* Function Name:Obj60E1Up                                                                          */
/* Function Description: 对象字典0x60E1 相关变量更新                                                */
/****************************************************************************************************/
void Obj60E1Up( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
        u16NegtiTorqLimit = (SHORT)Prm.OBJ_60E1;
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Negtive_torque_limit].all= (SHORT)Prm.OBJ_60E1;
}

/****************************************************************************************************/
/* Function Name:Obj60FFUp                                                                          */
/* Function Description: 对象字典0x60FF 相关变量更新                                                */
/****************************************************************************************************/
void Obj60FFUp( void )
{
    if( Kprm.f.EtherCATNet && CIA402_ETH_TEST && (Kprm.f.AxisNum == 0))
      s32TargetVel = LONGOF( Prm.OBJ_60FF_L, Prm.OBJ_60FF_H );
    else if(Kprm.f.CanOpenNet && CIA402_CAN_TEST)
      ODDatArr[ Target_Velocity_RPM].all= LONGOF( Prm.OBJ_60FF_L, Prm.OBJ_60FF_H );
}


void EtherCAT_ODB_Cia402_Init( void )
{
    s16QuickShutdownOpt         = (SHORT)Prm.OBJ_605A;
    s16HaltOptioncode           = (SHORT)Prm.OBJ_605D;
    u32FollowErrWind            = ULONGOF( Prm.OBJ_6065_L, Prm.OBJ_6065_H );
    u32PosWindow                = ULONGOF( Prm.OBJ_6067_L, Prm.OBJ_6067_H );
    u16PosWindowTime            = ULONGOF( Prm.OBJ_6068_L, Prm.OBJ_6068_H );
    u16VelWindow                = (SHORT)Prm.OBJ_606D;
    u16VelWindowTime            = (SHORT)Prm.OBJ_606E;
    u16Velthresd                = (SHORT)Prm.OBJ_606F;
    u16VelthresdTime            = (SHORT)Prm.OBJ_6070;
    u16MaxTorq                  = (SHORT)Prm.OBJ_6072;
    s32HomeOffset               = ULONGOF( Prm.OBJ_607C_L, Prm.OBJ_607C_H );
    SoftPosLimit.aEntries[0]      = ULONGOF( Prm.OBJ_607D_01_L, Prm.OBJ_607D_01_H );
    SoftPosLimit.aEntries[1]      = ULONGOF( Prm.OBJ_607D_02_L, Prm.OBJ_607D_02_H);
    u8Polarity                  = (SHORT)Prm.OBJ_607E;
    u32MaxProfileVel            = ULONGOF( Prm.OBJ_607F_L, Prm.OBJ_607F_H);
    u32ProfileVel               = ULONGOF( Prm.OBJ_6081_L, Prm.OBJ_6081_H);
    u32ProfileAcc               = ULONGOF( Prm.OBJ_6083_L, Prm.OBJ_6083_H);
    u32ProfileDec               = ULONGOF( Prm.OBJ_6084_L, Prm.OBJ_6084_H );
    u32QuickStopDec             = ULONGOF( Prm.OBJ_6085_L, Prm.OBJ_6085_H );
    u32TorqueSlope              = ULONGOF( Prm.OBJ_6087_L, Prm.OBJ_6087_H );
    PositionFactor.aEntries[ 0 ]    = ULONGOF( Prm.OBJ_6091_01_L, Prm.OBJ_6091_01_H);
    PositionFactor.aEntries[ 1 ]  = ULONGOF( Prm.OBJ_6091_02_L, Prm.OBJ_6091_02_H );
    s8HomingMethod              = (SHORT)Prm.OBJ_6098;
    HomingSpeed.aEntries[0]     = LONGOF( Prm.OBJ_6099_01_L, Prm.OBJ_6099_01_H );
    HomingSpeed.aEntries[1]     = LONGOF( Prm.OBJ_6099_02_L, Prm.OBJ_6099_02_H );
    u32HomingAcc                = LONGOF( Prm.OBJ_609A_L, Prm.OBJ_609A_H );
    s32PositionOffset           = LONGOF( Prm.OBJ_60B0_L, Prm.OBJ_60B0_H );
    s32VelocityOffset           = LONGOF( Prm.OBJ_60B1_L, Prm.OBJ_60B1_H );
    s16TorqueOffset             = (SHORT) Prm.OBJ_60B2_L;
    u16TouchProbeFun            = (SHORT)Prm.OBJ_60B8;
    InterPolDataRecord.u32PosCmd     = LONGOF( Prm.OBJ_60C1_01_L, Prm.OBJ_60C1_01_H );
    InterPolTimePeriod.u8InterpolationPeriod  = (SHORT)Prm.OBJ_60C2_01;
    InterPolTimePeriod.i8InterpolationIndex   = (SHORT)Prm.OBJ_60C2_02;
    u32MaxAcc                   = LONGOF( Prm.OBJ_60C5_L, Prm.OBJ_60C5_H );
    u32MaxDec                   = LONGOF( Prm.OBJ_60C6_L, Prm.OBJ_60C6_H );
    u16PositTorqLimit           = (SHORT)Prm.OBJ_60E0;
    u16NegtiTorqLimit           = (SHORT)Prm.OBJ_60E1;

    u16MITMode.aEntries[EMIT_PosO_FTC]            = (SHORT)Prm.MIT_PosFil;
    u16MITMode.aEntries[EMIT_TorqueO_FTC]         = (SHORT)Prm.MIT_Tref;
    u16MITMode.aEntries[EMIT_Red_Num]             = (SHORT)Prm.MIT_RateA;
    u16MITMode.aEntries[EMIT_Red_Den]             = (SHORT)Prm.MIT_RateB;
}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/










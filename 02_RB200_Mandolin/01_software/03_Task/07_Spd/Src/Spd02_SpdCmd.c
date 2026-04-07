/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Spd02_SpdCmd.c
* Version            : V0.1
* Date               : 2024
* Description        : 速度环控制处理
***********************************************************************************************/
  
  
  
#include "Main.h"
 
typedef struct
{
    LLONG AccBasic_Q15;         //加速度
    LLONG DecBasic_Q15;         //减速度
    LLONG SpdCmd;               //最终设定转速
    LLONG TargetSpd_Q15;        //目标转速
}ETHERCATSPD;
ETHERCATSPD EthSpdV;
 
  
  
  
/**********************************************************************************************/
/* Function_Name: KpiSpeedLevelCal                                                          */
/* Description  : 速度值得計算
               SCANB调用
               速度值得計算 :
               Speed [0.1r/min, 0.1mm/s] --> NormalizedSpeed [2^24/OvrSpd]
               LmtSel == 0 : NorMaxSpd Limit
               LmtSel != 0 : NorOvrSpd(2^24) Limit
               输入：
               输出：                                                    */
/**********************************************************************************************/
LONG KpiSpeedLevelCal( LONG  Speed, LONG  LmtSel )
{
	LONG x;
#if(FLOAT_USE == 1)
	x = (float)Speed * Iprm.fKspdlvl;
#else
	x = MlibMulgain( Speed, Iprm.Kspdlvl );
#endif
	if( ( LmtSel == 0 ) && ( x > Bprm.NorMaxSpd ) )
	{
		x = Bprm.NorMaxSpd;
	}
	return ( x );
 }
 
  
  
/**********************************************************************************************/
/* Function_Name: EtherCatSpdSource                                                          */
/* Description  : EtherCAT机型速度给定处理(PV,CSV)与停机处理
                                                   */
/**********************************************************************************************/
  
LONG EtherCatSpdSource( void )
{
LONG TargetSpd = 0;
INT64 TargetSpd_Q15;
    /* 轮廓速度模式处理 */
    if( s8ModeofOP == 3 )
    {
        /* 加减速规划 */
        LONG  SpdAcc,SpdDec;
        if( u32ProfileAcc >= u32MaxAcc )
        {
            SpdAcc = u32MaxAcc;
        }
        else
        {
            SpdAcc = u32ProfileAcc;
        }
        if( u32ProfileDec >= u32MaxDec )
        {
            SpdDec = u32MaxDec;
        }
        else
        {
            SpdDec = u32ProfileDec;
        }        
          
        EthSpdV.AccBasic_Q15 = (ULLONG)SpdAcc * 512 / 125;
        if(EthSpdV.AccBasic_Q15 <= 1) EthSpdV.AccBasic_Q15 = 1;
          
        EthSpdV.DecBasic_Q15 = (ULLONG)SpdDec * 512 / 125;
        if(EthSpdV.DecBasic_Q15 <= 1)EthSpdV.DecBasic_Q15 = 1;
          
        TargetSpd_Q15 = ((LLONG)s32TargetVel) << 15;
        EthSpdV.TargetSpd_Q15 = TargetSpd_Q15;
        if( EthSpdV.SpdCmd >= 0 )
        {
            if( EthSpdV.SpdCmd <= TargetSpd_Q15 )
            {
                  
                EthSpdV.SpdCmd +=  EthSpdV.AccBasic_Q15;
                if( EthSpdV.SpdCmd >= TargetSpd_Q15)EthSpdV.SpdCmd = TargetSpd_Q15;
            }
            else
            {
                  
                EthSpdV.SpdCmd -=  EthSpdV.DecBasic_Q15;
                if( EthSpdV.SpdCmd < TargetSpd_Q15)EthSpdV.SpdCmd = TargetSpd_Q15;
            }
        }
        else
        {
            if( EthSpdV.SpdCmd <= TargetSpd_Q15 )
            {
                  
                EthSpdV.SpdCmd +=  EthSpdV.DecBasic_Q15;
                if( EthSpdV.SpdCmd >= TargetSpd_Q15)EthSpdV.SpdCmd = TargetSpd_Q15;
            }
            else
            {
                  
                EthSpdV.SpdCmd -=  EthSpdV.AccBasic_Q15;
                if( EthSpdV.SpdCmd < TargetSpd_Q15)EthSpdV.SpdCmd = TargetSpd_Q15;
            }        
        }
        if( BinV.f.BaseEnable == 0 )
        {
            EthSpdV.SpdCmd = 0;
        }
        TargetSpd = EthSpdV.SpdCmd >> 15;
    }
    /* 立即速度模式 */
    else if( s8ModeofOP == 9 )                                   
    {
        TargetSpd = s32TargetVel + s32VelocityOffset;            
        EthSpdV.SpdCmd = 0;
    }
    else                                                         
    {
        TargetSpd = 0;
        EthSpdV.SpdCmd = 0;
    }
      
    EcontSMachine.HaltStatus = ( EcontSMachine.HaltStatus << 1 ) & 0x03;
      
    /* 暂停停机处理 */
    if( ( u16ControlWord & 0x0104 ) == 0x0104 )
    {
        EcontSMachine.HaltStatus |= 0x01;
    }
      
    if( EcontSMachine.HaltStatus == 1 )
    {
          
        if( s16HaltOptioncode == 1 )
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6084_Q15;
        }
        else if( s16HaltOptioncode == 2 )
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6085_Q15;
        }
        else
        {
            EcontSMachine.DecBase_Q15 = ( (INT64)TargetSpd ) << 15;
            if( EcontSMachine.DecBase_Q15 < 0 )
            {
                EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
            }
        }
         EcontSMachine.SpdOutQ15 = ( (INT64)TargetSpd ) << 15;            
    }
    else if( EcontSMachine.HaltStatus == 3 )
    {
        TargetSpd_Q15 = 0;
    }
    else
    {;}
      
    /* 快速停机处理 */
    EcontSMachine.FastStatus = ( EcontSMachine.FastStatus << 1 ) & 0x03;
    if( ( u16ControlWord & 0x0004 ) == 0x0000 )
    {
        EcontSMachine.FastStatus |= 0x01;
    }
      
    if( EcontSMachine.FastStatus == 0x01 )                    
    {
          
         if( s16QuickShutdownOpt == 0 )
        {
             if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
             {
                 EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
             }
             else if(CiA402StatusMachine == 0)
             {
                 EtherCAT_ControlStatus = 2;
             }
        }
        else if( s16QuickShutdownOpt == 1 || s16QuickShutdownOpt == 5)
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6084_Q15;
        }
        else if( s16QuickShutdownOpt == 2 || s16QuickShutdownOpt == 6)
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6085_Q15;
        }
        else
        {
            EcontSMachine.DecBase_Q15 = ( (INT64)TargetSpd ) << 15;
            if( EcontSMachine.DecBase_Q15 < 0 )
            {
                EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
            }
        }
         EcontSMachine.SpdOutQ15 = ( (INT64)TargetSpd ) << 15;
    }
    else if( EcontSMachine.FastStatus == 0x03 )
    {
        TargetSpd_Q15 = 0;
        if( EcontSMachine.SpdOutQ15 == 0 )
        {
          if(s16QuickShutdownOpt == 1 || s16QuickShutdownOpt == 2)
          {
              if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
              {
                  EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
              }
              else if(CiA402StatusMachine == 0)
              {
                  EtherCAT_ControlStatus = 1;
              }
          }
        }
    }
    else
    {;}
    if( EcontSMachine.FastStatus == 0x03 || EcontSMachine.HaltStatus == 0x03 )
    {
        if( EcontSMachine.SpdOutQ15 == 0 )
        {
            ;
        }
        else if( EcontSMachine.SpdOutQ15 > 0 )                       
        {
              
             EcontSMachine.SpdOutQ15 -=  EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 > 0 )
            {
                ;
            }
            else
            {
                EcontSMachine.SpdOutQ15 = 0;
                TargetSpd_Q15 = 0;
            }
        }
        else
        {
              
            EcontSMachine.SpdOutQ15 +=  EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 < 0 )
            {
                ;
            }
            else
            {
                TargetSpd_Q15 = 0;
                EcontSMachine.SpdOutQ15 = 0;
            }
        }
        TargetSpd = EcontSMachine.SpdOutQ15 >> 15;
    }
      
    /* 断使能下，目标速度清零 */
    if( !BinV.f.BaseEnable  || ((u16ControlWord & 0x0008) == 0x0000))
    {
        TargetSpd = 0;
    }

    /* 目标单位速度系数 Unit/s->0.1rpm */
    TargetSpd = (LONG)(( INT64 )TargetSpd * Iprm.Egear.b / Iprm.Egear.a);
    TargetSpd = (LONG)(( INT64 )TargetSpd * 600 * PositionFactor.aEntries[0] / 
                      (( INT64 )MencP.PulseNo * PositionFactor.aEntries[1]));    
    /* 极性处理 */
    if( u8Polarity & 0x40)
    {
        TargetSpd = -TargetSpd;
    }

    /* 目标单位速度系数 0.1rpm->[2^24/OvrSpd] */
    TargetSpd = KpiSpeedLevelCal( TargetSpd, 0 );

    /* 速度限制 */
    TargetSpd = MlibLimitul(TargetSpd,  Iprm.MaxSpd,    -Iprm.MaxSpd);
    TargetSpd = MlibLimitul(TargetSpd,  Iprm.EthCatMaxSpd,    -Iprm.EthCatMaxSpd);
    return TargetSpd;
 }
 
LONG MotorTestDelayCnt = 0;
USHORT MotorTestStep = 0;
  
LONG MotorTestCmdGenerator( void )
{
    return 0;
}

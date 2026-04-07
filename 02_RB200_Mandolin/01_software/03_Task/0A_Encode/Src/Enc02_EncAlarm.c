/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name 		 : Enc02_EncAlarm.c
* Version			 : V0.1
* Date				 : 2024
* Description		 : 编码器异常检测和报警处理
***********************************************************************************************/
#include "Enc02_EncAlarm.h"

void AbsAlmCheck(USHORT AlarmCode);                              

/**********************************************************************************************/
/* Function_Name: CheckSencAlarm         */ 
/* Description  : 电机侧编码器报警监测
                  调用：ScanC中的故障检测主函数中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void KpxCheckSencAlarm(void)
{
     if( Kprm.f.MotorLessTestMode == TRUE )
    {
        return;  // 若出于无电机测试模式，直接返回                                           
    }
   
    switch(Prm.EncoderType)
    {
         case 2: // 多摩川17bit绝对式编码器     
         case 3: // 多摩川23bit绝对式编码器      
            if(Iprm.f.MulTSingT) // 绝对值编码器多圈型号当做单圈使用
		  	{
		  		AbsAlmCheck(MencV.EncStatus.w & 0x001F);// 单圈使用时，忽略电池和备份检测	 
		  	}
			else
			{
				AbsAlmCheck(MencV.EncStatus.w );
			}
        break;
         case 4:      
		case 6:      
         case 5:      
        case 7:      
         default:     
        break;
    }
}
  
 /**********************************************************************************************/
 /* Function_Name: AbsAlmCheck         */ 
 /* Description  : 根据故障码进行故障检查并报警
                   调用：需要时调用
                   输入：
                   输出：     */
 /**********************************************************************************************/
 void AbsAlmCheck(USHORT AlarmCode)
{
	ABSENCALM_DEF AlarmCodeV;
	AlarmCodeV.w = AlarmCode;

    /*** 针对电池多圈编码器，存在备份报警和欠压报警情况 ***/
    if( AlarmCodeV.f.MTERR == 1 || AlarmCodeV.f.BattError == 1 )
    {
        KPI_ALARMSET( ALM_PG1 );     // A.810 : 编码器备份报警
        KPI_WARNINGCLR( WRN_PGBAT ); // 清除 A.930 : 绝对值编码器的电池故障-警告

        if( CAN_EXFUNC1_0_EN )
        {
            OrgStatusEEPReset();
        }

    }
    else
    {
          
         if(AlarmCodeV.f.BattAlarm == 1)
        {
             /*** 主程序运行时间计时,用于绝对值编码器上电时编码器欠压；并且允许欠压报警 ***/
            if( KnlV.MainTimer < 4000 && Iprm.f.BatWrnMode == FALSE)
            {
                KPI_ALARMSET( ALM_PG3 );    // A.830 : 编码器电池欠压报警
            }
            else if(Iprm.f.BatWrnMode == TRUE)
            {
                KPI_WARNINGSET( WRN_PGBAT );    // A.930 : 绝对值编码器的电池故障-警告
            }
        }
        else
        {
            KPI_WARNINGCLR( WRN_PGBAT );        // 清除 A.930 : 绝对值编码器的电池故障-警告	
        }
    }
 	 
 	 
#if 0
    if(AlarmCodeV.f.TMout)
	{
	  	if(++MencP.EncOffCnt > 3)
		{
 			 
             MencP.f.ENCErrorFlag = 1;                       
			KPI_ALARMSET( ALM_PGCOM );                         
		}
	}
	else
	{
		MencP.EncOffCnt = 0;
        MencP.f.ENCErrorFlag = 0;
	}
#endif
 }
  
/**********************************************************************************************/
/* Function_Name: SerialEncAlarmCheck         */ 
/* Description  : 电机侧编码器过热报警监测
                  调用：ScanC中的故障检测主函数中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
USHORT TempDelayCnt = 0;
void KpxSerialEncAlarmCheck( void )
{
      
     if( ( Prm.almmsk1 & 0x0008 ) == 0x0000 ) // 故障未屏蔽情况下，进行故障检测
    {
        if( MencV.EncStatus.f.EncOH )
        {
            if( ++TempDelayCnt > 20 )           // 故障持续20次，触发报警
            {
                KPI_ALARMSET( ALM_PG6 );        // A.860 : 编码器过热
                TempDelayCnt = 0;
            }
        }
        else
        {
            TempDelayCnt = 0;
        }
    }
    else
    {
        TempDelayCnt = 0;
    }
}

//*************************************************************************************************
//文件名:APP26_MotorBrake.c
//创建时间:2021.07.11
//版本说明:V1.0
//功能描述:电机抱闸信号输出
//*************************************************************************************************
#include "Main.h"

BRAKE_DEF Brake_V;
//*************************************************************************************************
//
// 抱闸信号初始化
//
//*************************************************************************************************
void MotorBK_Init(void)
{
#ifdef CPU1
    KPX_MOTA_BRAKE_OFF( );
#endif

}

//*************************************************************************************************
//
// 抱闸打开
//
//*************************************************************************************************
void MotorBK_On(void)
{
    if( 0 == Iprm.f.BKsel )
    {
#ifdef CPU1
        KPX_MOTA_BRAKE_ON( );
#endif

    }
}

//*************************************************************************************************
//
// 抱闸关闭
//
//*************************************************************************************************
void MotorBK_Off(void)
{
    if( 0 == Iprm.f.BKsel )
    {
#ifdef CPU1
        KPX_MOTA_BRAKE_OFF( );
#endif

    }
}



/**********************************************************************************************/
/* Function_Name: BrakePWM_Control         */
/* Description  : 抱闸控制
              调用：SCANC调用
              输入：
              输出：   */
/**********************************************************************************************/

void BrakePWM_Control( void )
{
   //抱闸内部信号获取后，按照状态机执行抱闸逻辑
   if( CoutV.f.Seq.BrkReleasing == 1 )
   {
       Brake_V.Period  = 0;
       Brake_V.Step    = 0;
   }
   else
   {
       Brake_V.Periodcnt_24V = 24.0f * 6250.0f / (float)BinK.UnDcVolt;
       Brake_V.Periodcnt_12V = 8.0f * 6250.0f / (float)BinK.UnDcVolt;


       switch( Brake_V.Step )
       {
           //设定初始抱闸电压
           case 0:
               Brake_V.Period = 10;
               Brake_V.Step ++;
//               Brake_V.Period = Brake_V.Periodcnt_24V;
//               Brake_V.Step = 1;
           break;

           //抱闸电压逐渐增加
            case 1:
               Brake_V.Period += 100;
               if( Brake_V.Period >  Brake_V.Periodcnt_24V)
               {
                   Brake_V.Period = Brake_V.Periodcnt_24V;
                   Brake_V.HoldTimeCnt = 0;
                   Brake_V.Step ++;
               }
//                Brake_V.Step ++;
           break;

           //抱闸电压增至最大，维持0.2s
            case 2:
                Brake_V.Period =  Brake_V.Periodcnt_24V;
                Brake_V.HoldTimeCnt ++;
               if( Brake_V.HoldTimeCnt >  100)
               {
                   //Brake_V.Period = 6250 - Brake_V.Periodcnt_24V;
                   Brake_V.Step ++;
               }
           break;

           //抱闸电压降至12V
            case 3:
               Brake_V.Period =  Brake_V.Periodcnt_12V;
           break;
            default:
               Brake_V.Step = 0;
           break;
       }
   }
   HWREGH(0x386B) = Brake_V.Period;
}




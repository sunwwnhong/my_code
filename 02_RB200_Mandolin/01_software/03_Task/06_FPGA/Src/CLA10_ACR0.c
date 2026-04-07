/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA10_ACR0.c
* Version            : V0.1
* Date               : 2024
* Description        : CLA与CPU1数据交互，PWM发波自举控制与配置，LED控制
***********************************************************************************************/
  
  
  
#include "Main.h"
 
typedef struct
{
    USHORT PWMEn_Step;          // 自举开启步骤
    float  Peridod;             // 自举占空比
    float  BootStrapStart;      // 自举启动占空比
    float  BootStrapCmp1;       // 自举占空比递减阈值1
    float  BootStrapCmp2;       // 自举占空比递减阈值2
    float  BootStrapCmp3;       // 自举占空比递减阈值3
    float  BootStrapEnd;        // 自举截止占空比
    float  BootStrapDec1;       // 自举占空比周期递减值1
    float  BootStrapDec2;       // 自举占空比周期递减值2
    float  BootStrapDec3;       // 自举占空比周期递减值3
    USHORT DlyCnt;              // 暂未用
}ACR0;
ACR0 MotAPwmConfig;
ACR0 MotBPwmConfig;
 
#define BuffNum 1024
volatile SHORT DataBuf1[ BuffNum ];
volatile SHORT DataBuf2[ BuffNum ];
volatile SHORT DataBuf3[ BuffNum ];
volatile SHORT DataBuf4[ BuffNum ];
volatile USHORT BuffNumCnt = 0;
  
  
/**********************************************************************************************/
/* Function_Name: BootstrapOut_MotA         */
/* Description  : 轴1解除上桥封波
            调用：
            输入：
            输出：   */
/**********************************************************************************************/
void BootstrapOut_MotA( void )
{
     GPIO_setPinConfig(GPIO_0_EPWM1A);
     GPIO_setPinConfig(GPIO_2_EPWM2A);
     GPIO_setPinConfig(GPIO_4_EPWM3A);
}

  
/**********************************************************************************************/
/* Function_Name: BootstrapIn_MotA         */
/* Description  : 关闭轴1上桥
            调用：
            输入：
            输出：   */
/**********************************************************************************************/
void BootstrapIn_MotA( void )
{
    GPIO_setPinConfig(GPIO_0_GPIO0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(0, GPIO_QUAL_SYNC);
    GPIO_writePin( 0,0 );
      
    GPIO_setPinConfig(GPIO_2_GPIO2);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(2, GPIO_QUAL_SYNC);
    GPIO_writePin( 2,0 );
      
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(4, GPIO_QUAL_SYNC);
    GPIO_writePin( 4,0 );
}
  
  

/**********************************************************************************************/
/* Function_Name: CLA_TaskA         */
/* Description  : 从CLA RAM中将轴2参数传递给CPU1与CPU2的共享RAM中
            调用：
            输入：
            输出：   */
/**********************************************************************************************/
void CLA_TaskA( void )
{
#ifdef CPU1

#endif
 
 }
  
  
 #ifdef CPU1

/**********************************************************************************************/
/* Function_Name: CLA_TaskB         */
/* Description  : 轴1和轴2的上电自举操作
                PWMEn_Step:使能过程 0（初始化）->10(解除封波)->11（ACR开始工作）->12(停机)->0
             自举过程 0->1(解除trip，打开下管)->2（解除trip中）->3(解除封波)-> 4(自举执行，电压逐步减小)->5（等待自举完成）
             TODO:自举配置的比较值未根据变化而变化，需要调整
            输入：
            输出：   */
/**********************************************************************************************/
#define PWM_BOOTSTRAP_START   0.708f

#define PWM_BOOTSTRAP_DEC1    0.00005714f
#define PWM_BOOTSTRAP_DEC2    0.004571f
#define PWM_BOOTSTRAP_DEC3    0.022857f

#define PWM_BOOTSTRAP_STEP1   0.6856f
#define PWM_BOOTSTRAP_STEP2   0.5714f
#define PWM_BOOTSTRAP_STEP3   0.2285f

#define PWM_BOOTSTRAP_END    0.057f

void CLA_TaskB( void )
{
    /*轴1的自举操作*/
    MotAPwmConfig.BootStrapStart = PWM_BOOTSTRAP_START * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapCmp1  = PWM_BOOTSTRAP_STEP1 * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapCmp2  = PWM_BOOTSTRAP_STEP2 * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapCmp3  = PWM_BOOTSTRAP_STEP3 * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapEnd   = PWM_BOOTSTRAP_END * (float)CurrentLoopVar.PWM_Priod;

    MotAPwmConfig.BootStrapDec1  = PWM_BOOTSTRAP_DEC1 * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapDec2  = PWM_BOOTSTRAP_DEC2 * (float)CurrentLoopVar.PWM_Priod;
    MotAPwmConfig.BootStrapDec3  = PWM_BOOTSTRAP_DEC3 * (float)CurrentLoopVar.PWM_Priod;


    switch( MotAPwmConfig.PWMEn_Step )
    {
         case 0:
            if( SysBitDef.f.ServoOnOff == 0 )
            {
                if( StateM_Var.f.PwmEn == 0 && StateM_Var.f.MotA_OC == 0 && SysBitDef1.f.MossfetEn == 1 )
                {
                    MotA_PWM_Lock();                             
                    BootstrapIn_MotA( );     //关闭上桥
                    MotAPwmConfig.Peridod       = MotAPwmConfig.BootStrapStart;
                    MotAPwmConfig.DlyCnt        = 0;             
                    MotAPwmConfig.PWMEn_Step    = 1;
                }
                else
                {
                    if( CoutV.f.Sv.BaseEnable )
                    {
                        KPX_MOTA_RUN_LED_ON( );
                    }
                    else
                    {
                        KPX_MOTA_RUN_LED_OFF( );
                    }
                }
            }
            else
            {
                if( StateM_Var.f.MotA_OC == 0 )
                {
                    MotAPwmConfig.PWMEn_Step    = 10;            
                }
            }
            break;
         case 1:
            EPWM_clearTripZoneFlag(EPWM1_BASE,(EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
            EPWM_clearTripZoneFlag(EPWM2_BASE,EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(EPWM3_BASE,EPWM_TZ_FLAG_OST);
            HWREGH(0x306B) = MotAPwmConfig.Peridod;
            HWREGH(0x326B) = MotAPwmConfig.Peridod;
            HWREGH(0x346B) = MotAPwmConfig.Peridod;
            MotAPwmConfig.PWMEn_Step    = 2;                 
            break;
        case 2:
            MotAPwmConfig.PWMEn_Step    = 3;                 
            break;
        case 3:
            MotA_PWM_UnLock();                               
            MotAPwmConfig.PWMEn_Step    = 4;                 
            break;
         case 4:
            if( MotAPwmConfig.Peridod > MotAPwmConfig.BootStrapCmp1)
            {
                MotAPwmConfig.Peridod -= MotAPwmConfig.BootStrapDec1;
            }
            else if( MotAPwmConfig.Peridod > MotAPwmConfig.BootStrapCmp2)
            {
                MotAPwmConfig.Peridod -= MotAPwmConfig.BootStrapDec2;
            }
            else
            {
                MotAPwmConfig.Peridod -= MotAPwmConfig.BootStrapDec3;
            }
             if( MotAPwmConfig.Peridod < MotAPwmConfig.BootStrapCmp3)
            {
                MotAPwmConfig.Peridod    = MotAPwmConfig.BootStrapEnd;
                MotAPwmConfig.PWMEn_Step = 5;
            }
            HWREGH(0x306B) = (uint16_t)MotAPwmConfig.Peridod;
            HWREGH(0x326B) = (uint16_t)MotAPwmConfig.Peridod;
            HWREGH(0x346B) = (uint16_t)MotAPwmConfig.Peridod;
         break;
         case 5:
            if( SysBitDef1.f.MossfetEn == 0 )
            {
                MotA_PWM_Lock();
                BootstrapOut_MotA();
                EPWM_forceTripZoneEvent( EPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
                MotAPwmConfig.PWMEn_Step = 0;
            }
        break;
          
        case 10:
            MotA_PWM_UnLock();                           
            EPWM_clearTripZoneFlag(EPWM1_BASE,(EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
            EPWM_clearTripZoneFlag(EPWM2_BASE,EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(EPWM3_BASE,EPWM_TZ_FLAG_OST);
            KPX_MOTA_RUN_LED_ON( );                      
            MotAPwmConfig.PWMEn_Step    = 11;            
            break;
        case 11:
            StateM_Var.f.PwmEn      = 1;
            CoutV.f.Sv.PWMEn        = 1;
            ACR_Smachine            |= 0x0001;           
            MotAPwmConfig.PWMEn_Step    = 12;            
            break;
        case 12:
            if( (SysBitDef.f.ServoOnOff == 0 && StateM_Var.f.EncError == 0 ) || StateM_Var.f.MotA_OC == 1 )
            {
                if( StateM_Var.f.MotA_OC == 1 )
                {
                    KPI_ALARMSET( ALM_OC );                  
                }
                  
                MotA_PWM_Lock();
                EPWM_forceTripZoneEvent( EPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
                EPWM_forceTripZoneEvent( EPWM2_BASE, EPWM_TZ_FORCE_EVENT_OST);
                EPWM_forceTripZoneEvent( EPWM3_BASE, EPWM_TZ_FORCE_EVENT_OST);
                  
                StateM_Var.f.PwmEn          = 0;
                CoutV.f.Sv.PWMEn            = 0;
                ACR_Smachine            &= 0xFFFE;
                KPX_MOTA_RUN_LED_OFF( );
                MotAPwmConfig.PWMEn_Step    = 0;
            }
            else if( StateM_Var.f.EncError == 1 )
            {
                StateM_Var.f.PwmEn          = 0;
                CoutV.f.Sv.PWMEn            = 0;
            }
            break;
        default:
        break;
    }
    Acr_V.PWMEn_Step = MotAPwmConfig.PWMEn_Step ;
}
#endif

 
 
volatile USHORT CanStatusCnt = 0;

/**********************************************************************************************/
/* Function_Name: ComLedStatu         */
/* Description  : 通讯状态LED控制（建立后1s闪亮）
            调用：
            输入：
            输出：   */
/**********************************************************************************************/
void ComLedStatu( void )
{
    if( CanVar.CanStatusCnt > 32000 )
    {
 #ifdef CPU1
        KPX_MOTA_POWER_ON( );
#endif

        CanStatusCnt = 0;
    }
    else
    {
        CanStatusCnt ++;
        if( CanStatusCnt < 400 )
        {
 #ifdef CPU1
            KPX_MOTA_POWER_OFF( );
#endif
        }
        else if( CanStatusCnt < 800)
        {
#ifdef CPU1
            KPX_MOTA_POWER_ON( );
#endif

        }
        else
        {
            CanStatusCnt = 0;
        }
    }
}


 
 
 
 
 
 
 
 
 
 
 

/*********** (C) COPYRIGHT 2024 Veichi Technology Co., Ltd******************************************
* File Name   : Mot16_Temperature.c
* Version     : V0.1
* Date        : 2024
* Description : IGBT or 散热器温度检测部分
****************************************************************************************************/
#include "Main.h"
 
#define SVCDEF_HSOH_ALMTIME     500             // 模块温模块温度过高度过高检测滤波时间：500ms
#define SVCDEF_ALMTIME_VALVE    (SVCDEF_HSOH_ALMTIME / (10 * KPI_SCCYCLEMS))
typedef struct{
    LONG   HeatSinkSum;         // 温度累加和
    LONG   MotSinkSum;         // 温度累加和
    LONG   EnviSinkSum;         // 环境温度累加和
    USHORT EnviSinkSumCnt;      // 环境温度累加计数器
    USHORT HeatSinkSumCnt;      // 温度累加计数器
    USHORT MotSinkSumCnt;      // 温度累加计数器
    USHORT HeatSincErrCnt;      // 温度过高故障判定延时技术
    USHORT HeatMotErrCnt;      // 温度过高故障判定延时技术
}TEMPVARDEF;
TEMPVARDEF TempVar;
 
const SHORT IGBTTabel[];                         
const SHORT IGBTTableNeg[];
const SHORT IGBTTableOv80degree[];

const SHORT MOTTable1[];
const SHORT MOTTable2[];
const SHORT MOTTable3[];
const SHORT MOTTable4[];

SHORT KpiInputHeatAdc_NTC10K( SHORT );
SHORT KpiInputMotHeatAdc_NTC10K( SHORT adcValue );
/****************************************************************************************************
Function_Name:LpxTemperatur_Init
Description  :温度检测相关变量清零
*****************************************************************************************************/
void LpxTemperatur_Init(void)
{
    TempVar.HeatSinkSum     = 0;
    TempVar.EnviSinkSum     = 0;
    TempVar.EnviSinkSumCnt  = 0;
    TempVar.HeatSinkSumCnt  = 0;
    TempVar.HeatSincErrCnt  = 0;
}
 
 
/****************************************************************************************************
Function_Name:LpxCheckHeatSinkAlm
Description  :模块温度报警检测,以及环境温度的检测,使用散热器上的问题同时反映出环境
              温度.
*****************************************************************************************************/
void    LpxCheckHeatSinkAlm( void )
{
SHORT kx = 0;
#ifdef CPU1
    TempVar.HeatSinkSum += AMotVar[0].IGBTTemp;
    TempVar.MotSinkSum  += AMotVar[0].DriveType;
#endif

    if( ++TempVar.HeatSinkSumCnt >= 256 )
    {
        kx = TempVar.HeatSinkSum >> 8;

 #if 1
        CoutV.UnHeatSinkTemp = 10L * KpiInputHeatAdc_NTC10K( kx );


        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            CoutV.UnHeatSinkTemp    = (float)TempVar.HeatSinkSum * 0.1f;
        }
#else
        CoutV.UnHeatSinkTemp = 0;
 #endif

        TempVar.HeatSinkSum    = 0;
        TempVar.HeatSinkSumCnt = 0;
         if( CoutV.UnHeatSinkTemp >= (SHORT)Prm.TempOH )
        {
            if( TempVar.HeatSincErrCnt < SVCDEF_ALMTIME_VALVE )
            {
                TempVar.HeatSincErrCnt++;
            }
            else
            {
                KPI_ALARMSET( ALM_OH );     // A.7A0 : 散热片过热
            }
        }
        else
        {
            TempVar.HeatSincErrCnt = 0;
        }
    }
    if ((Prm.drvno & 0x0F) == 0x0E)
    {

        if( ++TempVar.MotSinkSumCnt >= 256 )
        {
            kx = TempVar.MotSinkSum >> 8;

     #if 1
           // CoutV.UnHeatSinkTemp = 10L * KpiInputHeatAdc_NTC10K( kx );
            CoutV.UnHeatMotTemp = 10L * KpiInputMotHeatAdc_NTC10K( kx );

            if( ( Prm.Mode & 0xF000 ) == 0x1000 )
            {
                CoutV.UnHeatMotTemp    = (float)TempVar.MotSinkSum * 0.1f;
            }
    #else
            CoutV.UnHeatSinkTemp = 0;
     #endif

            TempVar.MotSinkSum    = 0;
            TempVar.MotSinkSumCnt = 0;

            if( ( Prm.almmsk1 & 0x0008 ) == 0x0000 ) // 故障未屏蔽情况下，进行故障检测
            {
                 if( CoutV.UnHeatMotTemp >= (SHORT)Prm.TempOH )
                {
                    if( TempVar.HeatMotErrCnt < SVCDEF_ALMTIME_VALVE )
                    {
                        TempVar.HeatMotErrCnt++;
                    }
                    else
                    {
                        KPI_ALARMSET( ALM_OH );     // A.7A0 : 散热片过热
                    }
                }
                else
                {
                    TempVar.HeatMotErrCnt = 0;
                }
            }
            else
            {
                TempVar.HeatMotErrCnt = 0;
            }
        }
    }

    //环境温度检测
 #ifdef CPU1
    TempVar.EnviSinkSum += A1ToC1V.DspCoreTemp;
    if( ++TempVar.EnviSinkSumCnt >= 256 )
    {
        TempVar.EnviSinkSumCnt = 0;
         TempVar.EnviSinkSum = TempVar.EnviSinkSum >> 8;

         //TODO:温度值不对
        //CoutV.UnEnvirTemp = (SHORT)(ADC_getTemperatureC((float)TempVar.EnviSinkSum ,ADC_REFERENCE_EXTERNAL,3.3f ));
        CoutV.UnEnvirTemp = 0;
        TempVar.EnviSinkSum = 0;

    }
#endif
}
/****************************************************************************************************
Function_Name:KpiInputHeatAdc_NTC10K
Description  :模块温度或者散热器温度检测,将ADC采集的电压转换成对应的实际温度.
           热电阻类型:NTC-10KΩ
*****************************************************************************************************/
SHORT KpiInputHeatAdc_NTC10K( SHORT adcValue )
{
SHORT Degree;
SHORT DataTmp;
USHORT Index;
   if( adcValue <= 96 )
   {
       Degree = 125;
   }
   else if( adcValue > 3760)
   {
       if( adcValue >= 3960 )
       {
           Degree = -40;
       }
       else
       {
           DataTmp = ( 3960 - adcValue ) >> 3;
           Degree = IGBTTableNeg[ DataTmp ];
       }
   }
   else
   {
       if( adcValue <= 560 )
       {
           Index = (560 - adcValue) >> 3;
            Degree = IGBTTableOv80degree[ Index ];
       }
       else
       {
           Index = (3760 - adcValue) >> 4;
            Degree = IGBTTabel[ Index ];
       }
   }

   return( Degree );
}

const SHORT IGBTTabel[]={
                         -25 ,-24 ,-24 ,-23 ,-22 ,-21 ,-21 , -20 ,-19 ,-18 ,-18 ,-17 ,-16 , -16 , -15 ,-15 ,
                        -14 , -13,-13 ,-12 ,-12 ,-11 , -11 , -10 ,-9  , -9  ,-8  , -8  , -7  , -7  , -6  , -6  ,
                        -5  , -5 , -5  ,-4  , -4  , -3  , -3  , -2  , -2  , -1  , -1  ,
                        0   ,0   ,0   ,1   ,1   ,2   ,3   ,3   ,4   ,4   ,5   ,5   ,6   ,6   ,6   ,7   ,7   ,8   ,8   ,
                        8   ,9   ,9   ,9   ,10  ,10  ,11  ,11  ,11  ,12  ,12  ,13  ,13  ,13  ,14  ,14  ,14  ,15  ,15  ,
                        16  ,16  ,16  ,17  ,17  ,17  ,18  ,18  ,19  ,19  ,19  ,20  ,20  ,20  ,21  ,21  ,22  ,22  ,22  ,
                        23  ,23  ,24  ,24  ,24  ,25  ,25  ,25  ,26  ,26  ,27  ,27  ,27  ,28  ,28  ,29  ,29  ,29  ,30  ,
                        30  ,31  ,31  ,31  ,32  ,32  ,33  ,33  ,34  ,35  ,35  ,35  ,35  ,36  ,36  ,37  ,37  ,37  ,38  ,
                        38  ,39  ,39  ,40  ,40  ,41  ,41  ,42  ,42  ,42  ,43  ,43  ,44  ,44  ,45  ,45  ,46  ,46  ,47  ,
                        47  ,48  ,48  ,49  ,50  ,50  ,51  ,51  ,52  ,52  ,53  ,54  ,54  ,55  ,56  ,56  ,57  ,57  ,58  ,
                        59  ,59  ,60  ,61  ,62  ,62  ,63  ,64  ,65  ,65  ,66  ,67  ,68  ,69  ,70  ,70  ,71  ,72  ,73  ,
                        74  ,75  ,76  ,77  ,78  ,80  ,81  ,82  ,83  ,84  ,86  ,87  ,89  ,90  ,92  ,93  ,95  ,97  ,99  ,
                        101 ,103 ,105 ,107 ,109 ,112 ,115 ,118 ,122 ,125 ,125 ,125 ,125 ,125 ,125 ,125};

const SHORT IGBTTableNeg[] = {
-40,-39,-39,-38,-37,-37,-36,-35,-35,-34,-33,-32,-32,-31,-31,-30,-30,-29,-29,-28,-28,-27, -27,-26,-26};


const SHORT IGBTTableOv80degree[] = {
   80  ,80  ,81  ,81  ,82  ,83  ,83  ,84  ,84  ,85  ,86  ,86  ,87  ,88  ,89  ,89  ,90  ,
   91  ,92  ,92  ,93  ,94  ,95  ,96  ,97  ,98  ,99  ,100 ,101 ,102 ,103 ,104 ,105 ,106 ,
   107 ,108 ,109 ,111 ,112 ,114 ,115 ,116 ,118 ,120 ,122 ,123 ,125 };


SHORT KpiInputMotHeatAdc_NTC10K( SHORT adcValue )
{
    SHORT Degree;
    SHORT DataTmp;
    USHORT Index;
       if( adcValue <= 1031 )
       {
           Degree = 125;
       }
       else if( adcValue > 4029)
       {
           if( adcValue >= 4093 )
           {
               Degree = -55;
           }
           else
           {
               DataTmp = ( 4092 - adcValue ) >> 1;
               Degree = MOTTable1[ DataTmp ];
           }
       }
       else if( (adcValue > 2731) && (adcValue <= 4028) )
       {
           if( adcValue <= 3626 )
           {
               Index = (3626 - adcValue) >> 4;
               Degree = MOTTable2[ Index ];
           }
           else
           {
               Index = (4028 - adcValue) >> 3;
               Degree = MOTTable3[ Index ];
           }
       }
       else
       {
           Index = (2731 - adcValue) >> 5;
           Degree = MOTTable4[ Index ];
       }

       return( Degree );
}

const SHORT MOTTable1[] = {
-53,-49,-44,-41,-39,-36,-34,-33,-31,-30,-28,-27,-26,-25,-24,-23,-22,-21,-20,-19,-18,-17, -16,-16,-15,-15,-14,-13,-13,-12,-12};

const SHORT MOTTable2[] = {
31, 32, 33, 34, 35, 36, 36, 37, 38, 39, 39, 40, 41, 41, 42, 43, 44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 50, 51, 52, 52,
53, 53, 54, 54, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 65, 65 };

const SHORT MOTTable3[] = {
-10, -8, -6, -4, -3, -1, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21, 22,
22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 28, 29, 29, 30, 30, 30};

const SHORT MOTTable4[] = {
66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
97, 99, 100, 101, 102, 103, 104, 105, 107, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120, 121, 123, 124, 125
};
/*--------------------------------------------------------------------------------------------------*/
/*                                          End of The File                                         */
/*--------------------------------------------------------------------------------------------------*/

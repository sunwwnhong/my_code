/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA05_DSPUpdate.c
* Version            : V0.1
* Date               : 2024
* Description        : DSP IAP升级处理接口
***********************************************************************************************/

#include "Main.h"
#define JumpToApp (void  (*)(void))0x0080000
 
  
struct ID_TAG
{
    uint32_t ID1;
    uint32_t ID2;
};
#pragma RETAIN(ID_Flag)
//#pragma LOCATION(ID_Flag, 0x11FFF8)
#pragma LOCATION(ID_Flag, 0x000DFFF8UL)
#ifdef CPU1
const struct ID_TAG ID_Flag = {0x11111111, 0x9ABCDEF0};
#endif
  
  
#pragma RETAIN( DriverID1 )
uint16_t DriverID1 = 0;                                             
#pragma LOCATION(DriverID1,                0x03A1E8)
 #pragma RETAIN( DriverID2 )
uint16_t DriverID2 = 0;                                             
#pragma LOCATION(DriverID2,                0x03A1E9)

#ifdef CPU1
//#pragma RETAIN(MotB_IAP_ID)
//uint16_t MotB_IAP_ID = 0;
//#pragma LOCATION(MotB_IAP_ID, 0x03A1EA)
#endif
#define KEY1    0x1234
#define KEY2    0x5678
volatile USHORT DFUDelcnt = 0;
  
/**********************************************************************************************/
/* Function_Name: DSP_Update         */
/* Description  : 跳转至IAP区域执行烧录
               调用：主循环2ms查询
               输入：
               输出：   */
/**********************************************************************************************/
void DSP_Update( void )
{
#ifdef CPU1
    //接收到升级指令，开始执行升级程序
    if(Prm.password != 0x2193)
    {
        DFUDelcnt = 0;
        return;
    }

    //升级时，必须保证伺服在待机状态
    if((BinV.f.BaseEnable == 0) && (Kprm.f.AxisNum == 0))
    {
        ++DFUDelcnt;
        if( DFUDelcnt > 120 )
        {
            Prm.password = 0;
            DriverID1 = KEY1;
            DriverID2 = KEY2;
            //MotB_IAP_ID = 0x7654;
            (*JumpToApp)();
        }
    }
#endif

}
 

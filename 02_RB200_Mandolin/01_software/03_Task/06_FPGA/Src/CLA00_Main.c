/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA00_Main.c
* Version            : V0.1
* Date               : 2024
* Description        : CLA模块主循环与初始化
***********************************************************************************************/
  
#include "Main.h"
 
 #ifdef CPU1
extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint32_t Cla1ConstRunStart, Cla1ConstLoadStart, Cla1ConstLoadSize;
#endif
 
  
/**********************************************************************************************/
/* Function_Name: InitCLA1         */
/* Description  : CLA模块初始化
                  调用：初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void InitCLA1( void )
{
    //1、复制CLA任务从FLASH 至 CLA的程序RAM区域

#ifdef CPU1
#if defined(_FLASH)
    memcpy((uint32_t *)&Cla1ProgRunStart,      (uint32_t *)&Cla1ProgLoadStart,     (uint32_t)&Cla1ProgLoadSize );
    memcpy((uint32_t *)&Cla1ConstRunStart,      (uint32_t *)&Cla1ConstLoadStart,     (uint32_t)&Cla1ConstLoadSize );
 #endif  
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while(!MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1));
    while(!MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU));

      
    //CLA分配RAM空间区域
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMCONTROLLER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMCONTROLLER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMCONTROLLER_CPU_CLA1);
    //配置CLA的程序/数据
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);
 
  
  
  //3.CLA寄存器配置
#pragma diag_suppress=770
      
    //CLA中断向量映射配置
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_2, (uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_6, (uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_7, (uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_8, (uint16_t)&Cla1Task8);
 
     //CLA任务触发源配置
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);
//    CLA_setTriggerSource(CLA_TASK_2, CLA_TRIGGER_ADCA2);
//
//    CLA_setTriggerSource(CLA_TASK_6, CLA_TRIGGER_TINT0);       //SCANC触发2ms
//
//    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);     //由软件触发
 #pragma diag_warning=770
      
      //CLA任务使能
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1);
//    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_2);
// #if 1
    //CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_6);
//    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_7);
//#endif
//    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_8);
#endif
}
  
  

/**********************************************************************************************/
/* Function_Name: CLA_init         */
/* Description  : CLA初始化
                  调用：初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void CLA_init( void )
{
    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_8);   //Task8软件强制触发
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 

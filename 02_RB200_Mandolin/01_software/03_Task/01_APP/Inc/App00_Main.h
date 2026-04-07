/*
 * App00_Main.h
 *
 *  Created on: 2022年7月9日
 *      Author: zhuxc
 */

#ifndef App00_Main_H
#define App00_Main_H

/*-------------------------------------------------------------------------------------------------*/
#include "App01_Timer.h"
#include "App02_MConfg.h"
#include "App03_INT.h"
#include "App04_GPIO.h"
#include "APP05_ADC.h"
#include "App06_QEP.h"
#include "App07_IIC.h"
#include "App09_Uart.h"
#include "App10_DMA.h"
#include "APP11_ScanA.h"
#include "APP12_ScanB.h"
#include "APP13_ScanC.h"
#include "App15_Can.h"
#include "App16_SPI.h"
#include "APP19_BKCtrl.h"                 //刹车控制
#include "APP20_RelayCtrl.h"              //继电器控制
#include "APP21_DBCtrl.h"                 //动态制动控制
#include "APP22_PWMEn.h"                  //PWM使能控制
#include "APP26_MotorBrake.h"
#include "App27_PWM.h"
#include "APP28_SysDelay.h"
#include "APP29_STO.h"
#include "APP30_MT6709.h"

/*-------------------------------------------------------------------------------------------------*/
extern void InitCPU10( void );
extern void InitCPU11( void );
extern void CPU_Reset( void );
extern void InitC1_EtherCAT( void );

#endif


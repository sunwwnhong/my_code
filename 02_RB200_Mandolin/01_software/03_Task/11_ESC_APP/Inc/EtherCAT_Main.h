/*
 * EtherCAT_Main.h
 *
 *  Created on: 2017年2月28日
 *      Author: zhuxc
 */

#ifndef EtherCAT_Main_H
#define EtherCAT_Main_H


#include "EtherCAT01_ContWord.h"                        // CIA 402 状态机
#include "EtherCAT02_ContrlMode.h"                      // EtherCAT 控制模式
#include "EtherCAT03_Pos.h"                             // 位置处理
#include "EtherCAT04_Spd.h"                             // 速度处理
#include "EtherCAT06_PortCheck.h"                       // Port Check
#include "EtherCAT07_EMCYCode.h"                        // 紧急报文ID
#include "EtherCAT08_2000Rw.h"


#define  CIA402_ETH_TEST      ((Prm.Cia402Test & 0x02) == 0x02)
#define  CIA402_CAN_TEST      ((Prm.Cia402Test & 0x01) == 0x01)
#define  CIA402_ETH_PRM_TEST  ((Prm.Cia402Test & 0x08) == 0x08)
#define  CIA402_CAN_PRM_TEST  ((Prm.Cia402Test & 0x04) == 0x04)

/*--------------------------------------------------------------------------------------------------*/
#define EtherCATVer     12                          /* EtherCAT 版本号                                */
/*--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------*/
typedef union   {
        ULONG    Dw;
        struct
        {
            USHORT  Y1:             1;      // Y1
            USHORT  Y2:             1;      // Y2
            USHORT  Y3:             1;      // Y3
            USHORT  Y4:             1;      // Y4
            USHORT  Reserved:       12;     // 预留
        } f;
}OBJ60FE_01;
extern OBJ60FE_01 Obj60FE_01;
/*--------------------------------------------------------------------------------------------------*/


extern USHORT Syncch0Time;
extern ULONG u32SynchCnt;
extern void EtherCAT_Init( void );
extern void EtherCAT_2msLoop( void );
extern void EtherCAT_125usLoop( void );
extern USHORT EtherCAT_StatusMonitor( void );
extern USHORT EtherCAT_StationMonitor( UCHAR );
extern USHORT EtherCat_Sync0CycleTime( void );
extern ULONG EtherCatSyncSm3Time;
extern USHORT EtherCatALStatus;
extern USHORT EtherCAT_ALStatus( void );
extern USHORT EtherCAT_StationMonitor( UCHAR Type );

extern void Obj6040Up( void );
extern void Obj605AUp( void );
extern void Obj605DUp( void );
extern void Obj6060Up( void );
extern void Obj6065Up( void );
extern void Obj6067Up( void );
extern void Obj6068Up( void );
extern void Obj606DUp( void );
extern void Obj606EUp( void );
extern void Obj606FUp( void );

extern void Obj6070Up( void );
extern void Obj6071Up( void );
extern void Obj6072Up( void );
extern void Obj607AUp( void );
extern void Obj607CUp( void );
extern void Obj607D_1Up( void );
extern void Obj607D_2Up( void );
extern void Obj607EUp( void );
extern void Obj607FUp( void );

extern void Obj6080Up( void );
extern void Obj6081Up( void );
extern void Obj6083Up( void );
extern void Obj6084Up( void );
extern void Obj6085Up( void );
extern void Obj6087Up( void );

extern void Obj6091_1Up( void );
extern void Obj6091_2Up( void );
extern void Obj6098Up( void );
extern void Obj6099_1Up( void );
extern void Obj6099_2Up( void );

extern void Obj609AUp( void );
extern void Obj60B0Up( void );
extern void Obj60B1Up( void );
extern void Obj60B2Up( void );
extern void Obj60B8Up( void );
extern void Obj60C1_1Up( void );
extern void Obj60C2_1Up( void );
extern void Obj60C2_2Up( void );
extern void Obj60C5Up( void );
extern void Obj60C6Up( void );
extern void Obj60E0Up( void );
extern void Obj60E1Up( void );
extern void Obj60FFUp( void );


#endif

/*
 * Main.h
 *
 *  Created on: 2017年2月28日
 *      Author: zhuxc
 */

#ifndef Main_H
#define Main_H

/*--------------------------------------------------------------------------------------------------*/
/*  1.芯片相关的外设                                                                                */
/*--------------------------------------------------------------------------------------------------*/




#include "f28x_project.h"

#define FPGAUse     0

#include "Base_Def.h"
#include "App00_Main.h"
#include "User00_Main.h"
#include "Mot00_Main.h"
#include "Lib00_Main.h"
#include "MlibSvc.h"

#include "CLA00_Main.h"
//-------------------------------------------------------------------------------------------------
#ifdef CPU1
#include "EtherCAT00_Main.h"
#endif
//-------------------------------------------------------------------------------------------------
#ifdef CPU2
#include "CLA04_EtherCATV.h"
#endif
//-------------------------------------------------------------------------------------------------
#define KPI_DI( )   ;
#define KPI_EI( )   ;
#define __DSB()     ;


#define MOTTYPE_ROTARY          0x00
#define MOTTYPE_LINEAR          0x01
#define AMPTYPE_ROTARY          0x00
#define AMPTYPE_LINEAR          0x01


#define KPI_CHKSPUSE_COMMON     0x01
#define KPI_CHKSPUSE_ROTARY     0x02
#define KPI_CHKSPUSE_LINEAR     0x04
#define KPI_CHKSPUSE_FENC       0x08
#define KPI_CHKSPUSE_SAFETY     0x10

#define TRCCMD_NOCMD        0x00
#define TRCCMD_DATATRACE    0x01
#define TRCCMD_RINGTRACE    0x02
#define TRCCMD_CONTTRACE    0x03


#define KPI_SACYCLENS   62500UL         /* ScnA 的执行周期62.5us   【单位:ns】                      */
#define KPI_SBCYCLENS   125000UL        /* ScnB 的执行周期125us                                   */
#define KPI_SCCYCLEMS   2UL             /* ScnC 的执行周期2ms                                     */

#define SVCDEF_UNSPD_SCMEANNUM      ((64UL + KPI_SCCYCLEMS - 1) / KPI_SCCYCLEMS)
#define SVCDEF_UNSPD_SCMEANTMMS     ( KPI_SCCYCLEMS * SVCDEF_UNSPD_SCMEANNUM )

#define KPX_SBTIMER1MS( Bcnt )  ((Bcnt)>>3)
#define KPX_SBTIMERPMS( Bcnt )  (((Bcnt)*100UL)>>3)


#define KPX_CHK_2N( x ) (((x)==2)||((x)==4)||((x)==8)||((x)==16)||((x)==32)||((x)==64)||((x)==128))
#define KPX_SCANC_SCANBCNT      ( (KPI_SCCYCLEMS * 1000000UL) / KPI_SBCYCLENS )
#define KPX_CHECK_SCCYCLE( )    ( (KPX_SCANC_SCANBCNT * KPI_SBCYCLENS)==(KPI_SCCYCLEMS * 1000000UL) )
#if     ( KPX_CHECK_SCCYCLE( ) && KPX_CHK_2N( KPX_SCANC_SCANBCNT ) )    /* 判断ScanC 的时间是否合理 */
#define KPX_SCANC_STRCHKMSK             ( KPX_SCANC_SCANBCNT - 1 )
#define KPX_CHK_SCANC_START( Cnt )      ( (Cnt & KPX_SCANC_STRCHKMSK) == 0x00 )
#define KPX_CHK_SCANC_ENDCHK( Cnt )     ( (Cnt & KPX_SCANC_STRCHKMSK) == KPX_SCANC_STRCHKMSK )
#define KPX_UPD_SCANC_STRCNTR( Cnt )    { ++Cnt;}
#else
#error "ScanC/ScanB Cycle Time Error"
#endif


#define KPI_SACYCLEUS   ((KPI_SACYCLENS + 500UL)/1000UL)
#define fKPI_SACYCLEUS  62.5f
#define KPI_SBCYCLEUS   ((KPI_SBCYCLENS + 500UL)/1000UL)
#define fKPI_SBCYCLEMS  1.250f
#define KPI_SCCYCLEUS   ( KPI_SCCYCLEMS * 1000UL     )
#define KPI_SACOUNTMS   (1000000UL/KPI_SACYCLENS)
#define KPI_SBCOUNTMS   (1000000UL/KPI_SBCYCLENS)
#define KPI_SCANA_US( us )  (((us)*1000UL)/KPI_SACYCLENS)
#define KPI_SCANB_US( us )  (((us)*1000UL)/KPI_SBCYCLENS)
#define KPI_SCANA_MS( ms )  ( (ms)*KPI_SACOUNTMS )
#define KPI_SCANB_MS( ms )  ( (ms)*KPI_SBCOUNTMS )
#define KPI_SCANC_MS( ms )  ( (ms)/KPI_SCCYCLEMS )

#define YEAR ((((__DATE__[7] - '0') * 10UL + (__DATE__[8] - '0')) * 10UL + (__DATE__[9] - '0')) * 10UL + (__DATE__ [10] - '0'))
#define MONTH (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n' ? 1 \
              :__DATE__[0] == 'F' && __DATE__[1] == 'e' && __DATE__[2] == 'b' ? 2 \
              :__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r' ? 3 \
              :__DATE__[0] == 'A' && __DATE__[1] == 'p' && __DATE__[2] == 'r' ? 4 \
              :__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y' ? 5 \
              :__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n' ? 6 \
              :__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l' ? 7 \
              :__DATE__[0] == 'A' && __DATE__[1] == 'u' && __DATE__[2] == 'g' ? 8 \
              :__DATE__[0] == 'S' && __DATE__[1] == 'e' && __DATE__[2] == 'p' ? 9 \
              :__DATE__[0] == 'O' && __DATE__[1] == 'c' && __DATE__[2] == 't' ? 10\
              :__DATE__[0] == 'N' && __DATE__[1] == 'o' && __DATE__[2] == 'v' ? 11\
              : 12)
#define DAY ((__DATE__[4] == ' ' ? 0 : __DATE__[4] - '0') * 10 + (__DATE__[5] - '0'))
#define HOUR        ((__TIME__[0] == ' ' ? 0 : __TIME__[0] - '0') * 10 + (__TIME__[1] - '0'))
#define MINUTE      ((__TIME__[4] == ' ' ? 0 : __TIME__[3] - '0') * 10 + (__TIME__[4] - '0'))
#define SECOND      ((__TIME__[4] == ' ' ? 0 : __TIME__[6] - '0') * 10 + (__TIME__[7] - '0'))

#define System_Time (10000UL * HOUR  + 100UL * MINUTE + SECOND)
#define System_Year (10000UL * YEAR + 100* MONTH + DAY)


#define     C10POW7     10000000UL              /* < 10^7 >                                         */
#define     C2PAIE7     62831853UL              /* < (2*PAI) * 10^7 >                               */







#endif


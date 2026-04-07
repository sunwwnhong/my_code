/*
 * Cur02_CurCmd.h
 *
 *  Created on: 2017年6月14日
 *      Author: zhuxc
 */
 #ifndef Cur02_CurCmd_H
#define Cur02_CurCmd_H
 extern UCHAR ETorFlag;
 extern LONG KpiInputTrqRef(void);
extern LONG KpiEtherCatInputTrqRef(void);
extern LONG KpiTorqueLevelCal( LONG , LONG );
extern LONG KpiNorTorqueCal( LONG );
extern LONG AIChanneTorqCnt( LONG Voltage );
 #endif

/*
 * Spd02_SpdCmd.h
 *
 *  Created on: 2018Äê5ÔÂ14ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd02_SpdCmd_H
#define Spd02_SpdCmd_H
 extern LONG KpiInputSpdRef(void);
extern LONG EtherCatSpdSource( void );
extern LONG KpiSpeedLevelCal( LONG  Speed, LONG  LmtSel );
extern LONG MotorTestCmdGenerator( void );
#endif

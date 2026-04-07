/*
 * Spd08_SpdStatus.h
 *
 *  Created on: 2018Äê5ÔÂ14ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd08_SpdStatus_H
#define Spd08_SpdStatus_H
 extern void LpxCheckMotorStop( void );
extern void LpxCheckMotorRun( void );
extern void LpxCheckMotorVcmp( void );
extern void LpxEtherCatCheckMotorVcmp( void );
extern void LpxEtherCatCheckMotorRun( void );
extern void LpxCanOpenCheckMotorVcmp( void );
extern void LpxCanOpenCheckMotorRun( void );
extern void LpxVelOver( void );

extern void LpxCheckMotorLowVel( void );
#endif

/*
 * Spd06_SpdPICoeff.h
 *
 *  Created on: 2018Äê06ÔÂ04ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd06_SpdPICoeff_H
#define Spd06_SpdPICoeff_H
 extern void PcalBaseSpeedControl( USHORT  Loophz, USHORT  Pitime, USHORT  jrate, LONG	GselNo );
extern void PcalBaseTrqLpassFilter( USHORT  Trqfil1, LONG	GselNo );
extern void PcalBaseSpeedFFControl( void );
#endif

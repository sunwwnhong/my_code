/*
 * Spd10_VibrSuppress.h
 *
 *  Created on: 2018Äê8ÔÂ10ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd10_VibrSuppress_H
#define Spd10_VibrSuppress_H
 #define	ATYPERES_CTRL				1        
#define	POSSTB_CTRL					0        
 
extern void BpxMFVibSup( void );
extern void PcalResVibControl( void );
extern void PcalMFVibSupSel( void );
extern LONG BpxNorObsGainCal( LONG , LONG );
extern LONG BpxNorObsJGainCal( LONG , LONG );
extern void BpxInitResVibControl( void );
extern void BpxInitPosStbCtrl( void );
extern void PcalPosStbCtrl( void );
 extern float f_BpxNorObsGainCal(float,float);
extern float f_BpxNorObsJGainCal( float, float, float, float);
 
#endif
 
 
 
 
 

/*
 * ¡°Cur09_MotorPhase.h
 *
 *  Created on: 2018Äê3ÔÂ30ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur09_MotorPhase_H
#define Cur09_MotorPhase_H
 
typedef struct
{
    SHORT OffsetAng;          
    USHORT ZeroPhaseDir;      
    USHORT IncEncZLatchAng;   
}MOTORPHASE;
#define MOTORPHASEV_DEFAULT { 0,0 }
extern MOTORPHASE MotorPhaseV;
 extern void IprmcalMotorPhaseInit(void);
extern void MotorPhaseCnt_Deg(void);
#endif

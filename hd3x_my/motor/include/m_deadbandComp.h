//==================================================================================================
//
// 死区补偿
//
//
//
// Time-stamp: <2012-2-10 10:26:02  author, 0000>
//
//==================================================================================================


#ifndef __M_DEADBAND_COMP_H__
#define __M_DEADBAND_COMP_H__



#include "main.h"

#if (INV_MODEL == INV_1140)
#define Tdt 				0.000003//死区时间3us

#define Ton 				0.0000004//IGBT导通时间400ns
#define Toff 				0.0000016//IGBT关断时间1.6us
#elif (INV_MODEL == INV_3300)
#define Tdt 				0.000020//死区时间20us

#define Ton 				0.0000027//IGBT导通时间0.86us
#define Toff 				0.0000048//IGBT关断时间2.4us
#endif


//Tcomp = (Tdt + Ton - Toff) / 2;

//================================================================================

struct DEADBAND_COMP_STR
{
    f32 ua;                             // ua phase
    f32 ub;                             // ub phase
    f32 uc;                             // uc phase
    
    f32 ia;                             // magnetizing current
    f32 ib;                             // torque current
    f32 ic;
	
    f32 dtComp;                         // dead time gain
    bool enable;                        // enable
};

//void DeadTimeCompCalc(struct DEADBAND_COMP_STR *p);
//void DeadTimeCompCalc1(struct DEADBAND_COMP_STR *p);
void DeadTimeCompCalcNew(struct DEADBAND_COMP_STR *p);




//================================================================================


/*

void                      // returns nothing
SynchMotorDeadTimeComp(
    f32 ia,                         // a phase current
    f32 ib,                         // b phase current
    f32 ic,                         // c phase current
    f32 ua,                         // ua phase output
    f32 ub,                         // ub phase output
    f32 uc,                         // uc phase output
    f32 *vaPtr,                     // pointer to a phase voltage
    f32 *vbPtr,                     // pointer to b phase voltage
    f32 *vcPtr,                     // pointer to c phase voltage
    f32 dtComp,                     // dead time gain
    bool enable)                    // enable
;


*/




#endif  //__M_DEADBAND_COMP_H__





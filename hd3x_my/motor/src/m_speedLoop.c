//==================================================================================================
//
// 速度环
//
//
//
//
//==================================================================================================


#include "m_speedLoop.h"
#include "m_output.h"




// 调试使用
f32 spdRegError;
f32 spdRegInt;

//extern u16 SpeedLoopPreset;
extern f32 iqRef;
//SUPPL_TOR_STRUCT   gSupplTor;
//void SupplyTorFucn (void);
//void SupplyTorFucnReset (void);
//#define SPD_LOOP_OUT_DELTA_MAX  0.01    // 速度环输出增量限幅
//f32 SPD_LOOP_OUT_DELTA_MAX = 0.01;

//==============================================================================
//
// Speed Regulator (dual)
// 
// integrator += ki * (e(n) + e(n-1)) / 2
// out = integrator + kp * (ref - fdb/kf)
//
//==============================================================================
extern f32 DqTo2ndiq;
extern u16 IFmodelFlga; 
void SpeedRegulator(struct SPEED_REGULATOR_STR *p)
{
    f32 output;
    static f32 integrator, lastInput;
    f32 input, input2;
    f32 pOut;
    f32 tmp;
    f32 tmp1;
//    f32 outOld;

//    outOld = iqRef;//p->out;

    p->propGain = p->propGain / p->kf;      // reduce the proportional gain by the feedforward gain

    input = p->speedReference - p->wr;
    spdRegError = input;

    input2 = p->speedReference * p->kf - p->wr;
    pOut = p->propGain * input2;

   // if (SpeedLoopPreset)
    if (IFmodelFlga == 1)
    {
        output = integrator = DqTo2ndiq;
	  // output = integrator = 0.90 * highStartingTorqueMenu.torqueCurrent;
    }
    else
    {
        // integrator section of regulator
        if ((FALSE == p->enable) || (0.0 == p->integGain))
        {   // Reset integrator
            integrator = input = 0.0;
        }
        else
        {
            integrator += p->integGain * 0.5 * (input + lastInput);
        }
     
        output = integrator + pOut * p->enable;
        tmp1 = p->wr * p->propGain * (1.0 - p->kf);

#if 0   // 速度环输出增量限幅
        if (output > outOld + SPD_LOOP_OUT_DELTA_MAX)
        {
            output = outOld + SPD_LOOP_OUT_DELTA_MAX;
            integrator = output - pOut;
            tmp = output + tmp1;
            if (integrator < tmp)
            {
                integrator = tmp;
            }
        }
        else if (output < outOld - SPD_LOOP_OUT_DELTA_MAX)
        {
            output = outOld - SPD_LOOP_OUT_DELTA_MAX;
            integrator = output - pOut;
            tmp = output + tmp1;
            if (integrator > tmp)
            {
                integrator = tmp;
            }
        }
#endif
        
        
        if (output > p->maxLimit)
        {   // limit output to maximium and check for rollback
            output = p->maxLimit;
            integrator = output - pOut;

            tmp = output + tmp1;
            if (integrator < tmp)
            {
                integrator = tmp;
            }
            *(p->speedRollback) = MAXIMUM_LIMIT; 
        }
        else if (output < p->minLimit)
        {   // limit output to minimum and check for rollback
            output = p->minLimit;
            integrator = output - pOut;

            tmp = output + tmp1;
            if (integrator > tmp)
            {
                integrator = tmp;
            }
            *(p->speedRollback) = MINIMUM_LIMIT;
        }
        else
        {
            *(p->speedRollback) = FALSE;    // rollback flag FALSE
        }

        lastInput = input;          // save error(n) into error(n-1)  
    }
    
   // spdRegInt = integrator;

    p->out = output;            // return regulated output
}











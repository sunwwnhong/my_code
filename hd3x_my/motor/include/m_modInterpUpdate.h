//==================================================================================================
//
// Modulator Interpolator update
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_MOD_INTERP_UPDATE_H__
#define __M_MOD_INTERP_UPDATE_H__



#include "main.h"




#define volPU       26880       // 输出电压指令，1PU对应的值



//#define ModInterpClamp  32767
//#define ModInterpClamp  (s16)(26880 * 1.15)
#define ModInterpClamp  26880



//================================================================================
struct MOD_INTERP_UPDATE_STR
{
    f32 VaRef;                      // A phase voltage reference
    f32 VbRef;                      // B phase voltage reference
    f32 VcRef;                      // C phase voltage reference
    f32 VaStepRef;                  // A phase voltage reference step
    f32 VbStepRef;                  // B phase voltage reference step
    f32 VcStepRef;                  // C phase voltage reference step
    f32 VaPrimeRef;                 // A phase voltage reference (midpoint)
    f32 VbPrimeRef;                 // B phase voltage reference (midpoint)
    f32 VcPrimeRef;                 // C phase voltage reference (midpoint)
    f32 VaPrimeStepRef;             // A phase voltage reference step (midpoint)
    f32 VbPrimeStepRef;             // B phase voltage reference step (midpoint)
    f32 VcPrimeStepRef;             // C phase voltage reference step (midpoint)
    bool enable;                    // allows non-zero ouputs
};
void ModInterpUpdate(struct MOD_INTERP_UPDATE_STR *p);
//================================================================================





//================================================================================
// 使用宏定义，减小执行时间。
#define ModInterpUpdateMacro(VaRef, VbRef, VcRef, VaStepRef, VbStepRef, VcStepRef, VaPrimeRef, VbPrimeRef, VcPrimeRef, VaPrimeStepRef, VbPrimeStepRef, VcPrimeStepRef) \
{                                                                                               \
    outputVol.va            = _IQsat(volPU * (VaRef),         ModInterpClamp, -ModInterpClamp); \
    outputVol.vb            = _IQsat(volPU * (VbRef),         ModInterpClamp, -ModInterpClamp); \
    outputVol.vc            = _IQsat(volPU * (VcRef),         ModInterpClamp, -ModInterpClamp); \
    outputVol.vaStep        = _IQsat(volPU * (VaStepRef),     ModInterpClamp, -ModInterpClamp); \
    outputVol.vbStep        = _IQsat(volPU * (VbStepRef),     ModInterpClamp, -ModInterpClamp); \
    outputVol.vcStep        = _IQsat(volPU * (VcStepRef),     ModInterpClamp, -ModInterpClamp); \
    outputVol.vaPrime       = _IQsat(volPU * (VaPrimeRef),    ModInterpClamp, -ModInterpClamp); \
    outputVol.vbPrime       = _IQsat(volPU * (VbPrimeRef),    ModInterpClamp, -ModInterpClamp); \
    outputVol.vcPrime       = _IQsat(volPU * (VcPrimeRef),    ModInterpClamp, -ModInterpClamp); \
    outputVol.vaPrimeStep   = _IQsat(volPU * (VaPrimeStepRef),ModInterpClamp, -ModInterpClamp); \
    outputVol.vbPrimeStep   = _IQsat(volPU * (VbPrimeStepRef),ModInterpClamp, -ModInterpClamp); \
    outputVol.vcPrimeStep   = _IQsat(volPU * (VcPrimeStepRef),ModInterpClamp, -ModInterpClamp); \
}
//================================================================================









#endif  //__M_MOD_INTERP_UPDATE_H__





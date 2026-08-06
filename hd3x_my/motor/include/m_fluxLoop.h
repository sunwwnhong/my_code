//==================================================================================================
//
// 磁链环
//
//
//
// Time-stamp: <2012-2-9 16:42:08  author, 0000>
//
//==================================================================================================


#ifndef __M_FLUX_LOOP_H__
#define __M_FLUX_LOOP_H__



#include "main.h"
#include "m_control.h"



#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_FLUX_REG        1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_FLUX_REG        1
#endif




//================================================================================
struct FLUX_REGULATOR_STR
{
    f32 out;                        // regulated flux output

    f32 fluxRef;                    // reference input
    f32 fluxDsFil;                  // feedback input
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 idsRated;                   // ids rated
    f32 mi;                         // modulation index
    f32 filterGain;                 // flux filter gain

    f32 lSigma;                     // L Sigma，= sigma * Ls
    f32 iNoload;                    // 空载电流
    f32 iqGain;                     // iq电流给定的增益

    bool isTransfer;                // is transfer
    bool piRegulatorEnable;         // enable for PI Regulator
    bool globalEnable;              // global enable
};
void FluxRegulator(struct FLUX_REGULATOR_STR *p);
//================================================================================




#endif  //__M_FLUX_LOOP_H__





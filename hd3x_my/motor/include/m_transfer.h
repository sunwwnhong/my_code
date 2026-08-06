//==================================================================================================
//
// 同步切换，包括上切换、下切换、环流
// 环流是下切换的特殊情况
//
//
// Time-stamp: <2012-1-4 16:23:00  author, 0000>
//
//==================================================================================================


#ifndef __M_TRANSFER_H__
#define __M_TRANSFER_H__



#include "main.h"
#include "m_pll.h"
/*


//==============================================================================
enum SynchTransferMode
{
    SYNCH_TRANSFER_DISABLE,         // 0
    SYNCH_TRANSFER_UP,              // 1，上切换
    SYNCH_TRANSFER_DOWN             // 2，下切换
};

enum TransferStates
{
    TRANSFER_INIT,                  // 0
    WAITING_FOR_FREQUENCY_LOCK,     // 1
    WAITING_FOR_PHASE_LOCK,         // 2
    WAITING_FOR_FLUX_TO_BUILD,      // 3
    WAITING_FOR_CONTACTOR_CLOSURE,  // 4
    WAITING_FOR_INV_CURRENT_DEC,    // 5
    WAITING_FOR_CONTACTOR_OPENING,  // 6
    TRANSFER_COMPLETE               // 7
};

struct SynchTransferType                // SynchTransfer Data Structure
{
    bool UpTransferTimeoutFlag;             // Up Transfer Time out Flag
    enum TransferStates UpTransferState;    // Up Transfer State
    f32 UpTransferTimer;                    // Up Transfer Timer

    bool DownTransferTimeoutFlag;           // Down Transfer Time out Flag
    enum TransferStates DownTransferState;  // Down Transfer State
    f32 DownTransferTimer;                  // Down Transfer Timer
    f32 DownTransferStartTimer;             // Down Transfer Start Timer (after PLL locked)

    f32 FrequencyDelta;                     // Frequency Delta (input frequency - output frequency)
    f32 PhaseDelta;                         // Phase Delta (input phase - output phase)
    f32 PhaseRegOutput;                     // Output of Phase Regulator

    f32 FrequencyLockTimer;                 // Frequency Lock Timer
    f32 PhaseLockTimer;                     // Phase Lock Timer
};
extern struct SynchTransferType SynchTransfer;    // Synch Transfer Structure

struct UpTransferError
{
    f32 frequencyErrorHz;                   // 输入电压频率与输出电压频率差值 
    f32 phaseErrorAngle;                    // 电网电压超前输出电压的相位角度/度       
};
//==============================================================================


extern u16 circulatingCurrentFlag;
extern u16 synchTransfer;                   // F8-52:1 SYNCH_TRANSFER_UP/上切换；2 SYNCH_TRANSFER_DOWN/下切换







void TransferFastDeal(void);
//void TransferSlowDeal(void);
void UpTransferFastDeal(void);
void UpTransferSlowDeal(void);
//void DownTransferPhaseLockDeal(void);




*/

#endif  //__M_TRANSFER_H__



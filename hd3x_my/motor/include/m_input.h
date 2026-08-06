//==================================================================================================
//
// 输入处理
//
//
//
// Time-stamp: <2011-8-25 19:49:47  author, 0000>
//
//==================================================================================================


#ifndef __M_INPUT_H__
#define __M_INPUT_H__



#include "main.h"




enum MV_STATUS
{
    UNKNOWN,    // 0
        LOW,    // 1
        OK      // 2
};


enum TapSettings
{
    TAP_AT_MINUS_5_PERCENT,     // 0，-5%
    TAP_AT_ZERO,                // 1, 0%
    TAP_AT_PLUS_5_PERCENT       // 2, +5%
};



//==============================================================================
struct InputProcessType                     // Input Process Data Structure
{
    u16 Enable;                         // 使能，目前一直有效
    enum MV_STATUS  MediumVoltageStatus;// 输入电压状态
    f32 frqFilterGain;                  // 输入电压频率滤波参数
    f32 Id;                             // id input current
    f32 Iq;                             // iq input current
    f32 IaU;                            // phase A input current
    f32 IbU;                            // phase B input current
    f32 IcU;                            // phase C input current
    f32 EaU;                            // phase A input voltage
    f32 EbU;                            // phase B input voltage
    f32 EcU;                            // phase C input voltage
    f32 E0Average;                      // 零序分量平均值
    f32 EdNegative;                     // negative sequence D voltage
    f32 EqNegative;                     // negative sequence Q voltage
    f32 Ed;                             // d voltage
    f32 Eq;                             // q voltage
    f32 Frequency;                      // 电网频率 
    f32 FrequencyFiltered;              // 电网频率，滤波之后
    f32 AveragePower;                   // input power average (kilowatts)
    f32 PowerFactor;                    // input power factor
                                        
    f32 IdNegSeq;                       // negative sequence D current
    f32 IqNegSeq;                       // negative sequence Q current
    f32 INegSeqTotal;                   // negative sequence
    f32 eUnbalance;                     // input voltage imbalance
                                        
    f32 ThermalOverloadLimit;           // transformer thermal level
    f32 OneCycleProtectionLimit;        // one cycle reative current level
    f32 SinglePhasingLimit;             // single phasing current level
    f32 UnderVoltageLimit;              // Under Voltage upper level
    f32 UnderVoltageLowerLimit;         // Under Voltage lower level
                                        
    f32 LineFluxVectorAngle;            // Line Flux Vector Angle
    f32 SamplePeriod;                   // Fast Loop Sample Period
    f32 TransformerTapSetting;          // Input transformer tap setting (-5, 0, or +5%)
                                        
    f32 ExcessReactiveCurrent;          // Input reactive current over max allowed 
    f32 ErmsMax;                        // Maximum phase rms voltage
    f32 PmaxUV;                         // Pmax rollback for low line
    f32 Pmax1P;                         // Pmax rollback for Single Phase
    f32 EdAverage;                      // Intermediate Ed before LPF
                                        
    f32 Kva;                            // Kva, not filtered
    f32 EdIq;                           // Reactive power, not filtered
    f32 EdId;                           // Real power, not filtered
    f32 IdRaw;                          // Raw unfiltered input Id current
    f32 IqRaw;                          // Raw unfiltered input Iq current
    f32 EdRaw;                          // Raw unfilteded Ed voltage
    f32 EqRaw;                          // Raw unfilteded Eq voltage
                                        
    f32 AvailableReactiveCurrent;       // Available reactive current
    f32 OneCycleLimitInput;             // One cycle protection limit input to protection function
    f32 OverVoltageLowerLimit;          // Over Voltage regen lower level (6-step)
};
extern struct InputProcessType InputProcess;     // Input Process Structure
//==============================================================================



//==============================================================================
struct InputProcessDisplayType          // Input Process Display Data Structure
{
    f32 Id;                             // id input current
    f32 Iq;                             // iq input current
    f32 Ed;                             // d voltage
    f32 Eq;                             // q voltage
    f32 AveragePower;                   // input power average (kilowatts)
    f32 Erms;                           // RMS voltage
    f32 Irms;                           // RMS current
    f32 Efficiency;                     // Efficiency
    f32 THD;                            // Total Harmonic Distortion
    f32 Kvar;                           // Kvar
    f32 Frequency;                      // Line frequency
    f32 ErmsMax;                        // 三相的最大输入电压
};
extern struct InputProcessDisplayType InputProcessDisplay;
//==============================================================================




f32                                 // returns Power Factor (unitless)
PowerFactorCalc(
    f32 id,                         // id current
    f32 iq)                         // iq current
;




void InitInputProcessing(void);
void InFastLoopControl(void);
void InSlowLoopControl(void);


#endif  //__M_INPUT_H__



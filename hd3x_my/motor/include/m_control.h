//==================================================================================================
//
// 电机控制的一些公共函数，包括:
// clarke变换，clarke反变换；
// park变换，park反变换；
// 2r->3s，两相旋转坐标系到三相静止坐标系；
// 通用PI函数；
// SynchFilter()，同步滤波函数，即一个周期内的平均值。
//
// 其中，一些短的函数使用宏定义，减小执行时间，略微增加空间。包括:
// ClarkeCalcMacro(), 
// ParkCalcMacro(), ParkCalcMacroSc(), 
// Conversion2rTo3sMacro(), Conversion2rTo3sMacroSc(), 
// SynchFilterMacro()
// CheckLowLimitMacro()
//
//
// Time-stamp: <2011-3-10 14:59:47  author, 0000>
//
//==================================================================================================


#ifndef __M_CONTROL_H__
#define __M_CONTROL_H__



#include "main.h"











//==============================================================================
// clarke变换
struct CLARKE_STR
{
    f32 a;          // Input: phase-a stator variable
    f32 b;          // Input: phase-b stator variable  

    f32 alpha;      // Output: stationary d-axis stator variable 
    f32 beta;       // Output: stationary q-axis stator variable
};
void ClarkeCalc(struct CLARKE_STR *p);
//==============================================================================



//==============================================================================
// clarke反变换
struct CLARKE_INVERSION_STR
{
    f32 alpha;      // Input: stationary d-axis stator variable 
    f32 beta;       // Input: stationary q-axis stator variable

    f32 a;          // Output: phase-a stator variable
    f32 b;          // Output: phase-b stator variable  
    f32 c;          // Output: phase-c stator variable  
};
void ClarkeInversionCalc(struct CLARKE_INVERSION_STR *p);
//==============================================================================



//==============================================================================
// park变换
struct PARK_STR
{
    f32 alpha;      // Input: stationary d-axis stator variable 
    f32 beta;       // Input: stationary q-axis stator variable 
    f32 angle;      // Input: rotating angle (pu) , 1PU = 2*pi

    f32 d;          // Output: rotating d-axis stator variable 
    f32 q;          // Output: rotating q-axis stator variable 
};
void ParkCalc(struct PARK_STR *p);
//==============================================================================



//==============================================================================
// park反变换
struct PARK_INVERSION_STR
{
    f32 d;          // Input: rotating d-axis stator variable
    f32 q;          // Input: rotating q-axis stator variable
    f32 angle;      // Input: rotating angle (pu) , 1PU = 2*pi

    f32 alpha;      // Output: stationary d-axis stator variable 
    f32 beta;       // Output: stationary q-axis stator variable 
};
void ParkInversionCalc(struct PARK_INVERSION_STR *p);
//==============================================================================



//================================================================================
// 两相旋转坐标系到三相静止坐标系
struct CONVERSION_2R_3S_STR
{
    f32 d;          // Input: rotating d-axis stator variable 
    f32 q;          // Input: rotating q-axis stator variable 
    f32 angle;      // Input: rotating angle (pu) , 1PU = 2*pi

    f32 a;          // Output: phase-a stator variable
    f32 b;          // Output: phase-b stator variable  
    f32 c;          // Output: phase-c stator variable  
};
void Conversion2rTo3s(struct CONVERSION_2R_3S_STR *p);
//================================================================================



// modulo'd angle limited to 2PI
void Modulo2PI(f32 *angle);


// modulo'd angle limited to +/-PI
void ModuloSignedPI(f32 *angle);











//==============================================================================
// 低通滤波的宏定义
//
// T为调用周期时间，t为滤波时间，k为拍数。
//
// 注意: old应该是全局变量、静态变量

// k，拍数。k越大滤波时间越大。k = t / T。t = T * k。 
// 使用示例: varFil = LPF_K(var, varFil, k);
// LPF_K()的k不能为0，LPF_K_VAR()的k可以为0
#define LPF_K(now, old, k)          ( (old) + ( 1.0 / (k) ) * ((now) - (old)) )
#define LPF_K_VAR(now, old, k)      ( (0 == (k)) ? (now) : LPF_K(now, old, k) )

// t, T只要为同样的时间单位即可，例如t,T的单位可都为ms
// 例如，t=100,T=2. 如果单位是ms，则滤波时间为100ms；如果单位为s，则滤波时间为100s
// LPF_T()的t不能为0，LPF_T_VAR()的t可以为0
// LPF_T()的t不能小于T，LPF_T_VAR()的t可以小于T
#define LPF_T(now, old, t, T)       ( (old) + ((f32)(T) * (1.0 / (t))) * ((now) - (old)) )
#define LPF_T_VAR(now, old, t, T)   ( ((t) < T) ? (now) : LPF_T(now, old, t, T) )

// gain范围是[0,1)，越大表示滤波时间越大。不能超过该范围，否则结果不可预料。
// gain = 1 - T/t, t = T / (1-gain)，k = t/T = 1/(1-gain)， gain = 1 - 1/k
// 建议使用前面的宏定义，LPF_K(), LPF_K_VAR(), LPF_T(), LPF_T_VAR()
#define LPF_Gain(now, old, gain)    ( (old) + (1.0 - (gain)) * ((now) - (old)) )
#define LPF_GAIN(now, old, gain)    LPF_Gain(now, old, gain)

// gainR = 1-gain, gainR = 1.0/k
// t = T / gainR, gainR范围是(0, 1], 其它范围时，不进行滤波处理
#define LPF_GainR(now, old, gainR)      ( (old) + (gainR) * ((now) - (old)) )
#define LPF_GainR_VAR(now, old, gainR)  ( ((0 < (gainR)) && ((gainR) < 1.0)) ? LPF_GainR(now, old, gainR) : (now) )
//==============================================================================

#define LPF_Gain_VF(now,last,old,gainR)   ( (old + (gainR) *((now) + (last) -(2.0 *(old)))))
#define HPF_Gain_VF(now,last,old,gainR)  ((1.0 -(2.0 *(gainR))) *(old) + (1.0 -(gainR))*((now)-(last)))

void
SynchFilter(
    f32 new_input,                  // New Input to filter
    f32 *out,                       // Output
    f32 *accumulator,               // accumulated value
    f32 one_over_sample_period,     // 1.0 / sample period (number of samples)
    bool reset)                     // resets accumulator
;










//==============================================================================
// PI regulator data template
struct PiDataType
{
    f32 maxLimit;                   // Maximum output limit
    f32 minLimit;                   // Minimum output limit
    f32 integGain;                  // Integrator gain
    f32 propGain;                   // Proportional gain
    f32 lastInput;                  // input (n-1)
    f32 accumulator;                // integrator accumulator
};

// PR regulator data template
struct PrDataType
{
    f32 maxLimit;                   // Maximum output limit
    f32 minLimit;                   // Minimum output limit
    f32 integGain;                  // Integrator gain
    f32 propGain;                   // Proportional gain
    f32 resoFre;					// resonant frequency谐振频率
    f32 resoFreOb;					// resonant frequency观测的谐振频率
    f32 resoFreComp;				// resonant frequency谐振频率补偿值
    f32 resoBw;						// Resonance bandwidth谐振带宽
    f32 lastOneInput;               // input (n-1)
    f32 lastTwoInput;               // input (n-2)
    f32 lastOneOutput;              // output (n-1)
    f32 lastTwoOutput;              // output (n-2)
};

//==============================================================================



//==============================================================================
struct REGULATOR_STR
{
    f32 out;
   // f32 out_pr;
    f32 input;                  // 注意为error，ref-fdb
    struct PiDataType *pi;      // structure containing gains and limits
   // struct PrDataType *pr;		
    s16 enable;                 // enable (resets integrator)
};
void RegulatorCalc(struct REGULATOR_STR *p);
void RegulatorCalcD(struct REGULATOR_STR *p);
void RegulatorCalcQ(struct REGULATOR_STR *p);
//==============================================================================


//==============================================================================
struct PRREGULATOR_STR
{
    f32 out;
    f32 input;                  // 注意为error，ref-fdb
    struct PrDataType *pr;      // structure containing gains and limits	
    s16 enable;                 // enable (resets integrator)
};
void PrRegulatorCalc(struct PRREGULATOR_STR *p);
//==============================================================================



//==============================================================================
//
// 一些短的函数使用宏定义，减小执行时间，略微增加空间。
//
//==============================================================================

//================================================================================
#define ClarkeCalcMacro(a, b, alpha, beta)  \
{                                           \
    (alpha) = (a);                          \
    (beta)  = ((a) + 2 * (b)) * ISQRT3;     \
}
//================================================================================

#define IClarkeCalcMacro(a, b, c, alpha, beta)       \
{                                                   \
    (a) = alpha;                                    \
    (c) = 0.5 * (-alpha - SQRT3 * beta);            \
    (b) = -((a) + (c));                             \
}
//================================================================================

//================================================================================
#define ParkCalcMacro(alpha, beta, angle, d, q)         \
{                                                       \
    f32 sinAngle, cosAngle;                             \
                                                        \
    sincos((angle), &sinAngle, &cosAngle);              \
    d =  (alpha) * (cosAngle) + (beta) * (sinAngle);    \
    q = -(alpha) * (sinAngle) + (beta) * (cosAngle);    \
}
//================================================================================



//================================================================================
#define ParkCalcMacroSc(alpha, beta, sinAngle, cosAngle, d, q) \
{                                                       \
    d =  (alpha) * (cosAngle) + (beta) * (sinAngle);    \
    q = -(alpha) * (sinAngle) + (beta) * (cosAngle);    \
}
//================================================================================



//================================================================================
#if 0
#define Conversion2rTo3sMacro(d, q, angle, a, b, c) \
{                                                   \
    f32 alpha, beta;                                \
    f32 sinAngle, cosAngle;                         \
    sincos((angle), &sinAngle, &cosAngle);          \
    alpha = (d) * cosAngle - (q) * sinAngle;        \
    beta  = (d) * sinAngle + (q) * cosAngle;        \
    (a) = alpha;                                    \
    (b) = 0.5 * (-alpha + SQRT3 * beta);            \
    (c) = 0.5 * (-alpha - SQRT3 * beta);            \
}
#elif 1
#define Conversion2rTo3sMacro(d, q, angle, a, b, c) \
{                                                   \
    f32 alpha, beta;                                \
    f32 sinAngle, cosAngle;                         \
    sincos((angle), &sinAngle, &cosAngle);          \
    alpha = (d) * cosAngle - (q) * sinAngle;        \
    beta  = (d) * sinAngle + (q) * cosAngle;        \
    (a) = alpha;                                    \
    (c) = 0.5 * (-alpha - SQRT3 * beta);            \
    (b) = -((a) + (c));                             \
}
#endif
//================================================================================



//================================================================================
#if 0
#define Conversion2rTo3sMacroSc(d, q, sinAngle, cosAngle, a, b, c) \
{                                                   \
    f32 alpha, beta;                                \
    alpha = (d) * (cosAngle) - (q) * (sinAngle);    \
    beta  = (d) * (sinAngle) + (q) * (cosAngle);    \
    (a) = alpha;                                    \
    (b) = 0.5 * (-alpha + SQRT3 * beta);            \
    (c) = 0.5 * (-alpha - SQRT3 * beta);            \
}
#elif 1
#define Conversion2rTo3sMacroSc(d, q, sinAngle, cosAngle, a, b, c) \
{                                                   \
    f32 alpha, beta;                                \
    alpha = (d) * (cosAngle) - (q) * (sinAngle);    \
    beta  = (d) * (sinAngle) + (q) * (cosAngle);    \
    (a) = alpha;                                    \
    (c) = 0.5 * (-alpha - SQRT3 * beta);            \
    (b) = -((a) + (c));                             \
}
#endif
//================================================================================



//================================================================================
#define SynchFilterMacro1(new_input, out, accumulator, one_over_sample_period, reset)    \
{                                                   \
    f32 tmp;                                        \
                                                    \
    tmp = (accumulator) + (new_input);              \
    if (TRUE == (reset))                            \
    {                                               \
        (out) = tmp * (one_over_sample_period);     \
        tmp = 0.0;                                  \
    }                                               \
    (accumulator) = tmp;                            \
}
//================================================================================



//================================================================================
#define SynchFilterMacro(new_input, out, accumulator, one_over_sample_period, reset)    \
{                                                           \
    (accumulator) = (accumulator) + (new_input);            \
    if (TRUE == (reset))                                    \
    {                                                       \
        (out) = (accumulator) * (one_over_sample_period);   \
        (accumulator) = 0.0;                                \
    }                                                       \
}
//================================================================================




//==============================================================================
#define Modulo2PIMacro(angle)                   \
{                                               \
    while ((angle) >= TWO_PI) (angle) -= TWO_PI;\
    while ((angle) < 0.0) (angle) += TWO_PI;    \
}
//==============================================================================




//==============================================================================
#define Modulo2PIMacro1(angle)      \
{                                   \
    f32 k;                          \
    k = (angle) * I_TWO_PI;         \
    k = k - (s32)k;                 \
    k = (k >= 0) ? k : (k + 1.0);   \
    (angle) = k * TWO_PI;           \
}
//==============================================================================





// returns TRUE if the input is less than or equal to the limit.
#define CheckLowLimitMacro(input, limit) ((fabs(input) <= limit) ? (TRUE) : (FALSE))













#endif  //__M_CONTROL_H__






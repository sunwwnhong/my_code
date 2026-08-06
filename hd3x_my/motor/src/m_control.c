//==================================================================================================
//
// 电机控制的一些公共函数，包括:
// clarke变换，clarke反变换；
// park变换，park反变换；
// 2r->3s，两相旋转坐标系到三相静止坐标系；
// 通用PI函数；
// SynchFilter()，同步滤波函数，即一个周期内的平均值。
// 
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_control.h"
#include "m_speedLoop.h"
#include "m_output.h"



#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
#pragma CODE_SECTION(ClarkeCalc,        "ramfuncs");
//#pragma CODE_SECTION(ClarkeInversionCalc,"ramfuncs");
#pragma CODE_SECTION(ParkCalc  ,        "ramfuncs");
//#pragma CODE_SECTION(ParkInversionCalc, "ramfuncs");
#pragma CODE_SECTION(Conversion2rTo3s , "ramfuncs");

#pragma CODE_SECTION(RegulatorCalc,     "ramfuncs");
#pragma CODE_SECTION(Modulo2PI    ,     "ramfuncs");
//#pragma CODE_SECTION(SynchFilter  ,     "ramfuncs");
#endif









#if 0
//==============================================================================
//
// clarke变换
//
// alpha = a
// beta  = (a + 2*b) / 3^0.5
//
//
//==============================================================================
void ClarkeCalc(struct CLARKE_STR *p)
{
    p->alpha = p->a;
//    p->beta  = (p->a + 2 * p->b) / SQRT3;
    p->beta  = (p->a + 2 * p->b) * ISQRT3;
}
#endif



//==============================================================================
//
// clarke反变换
//
// a = alpha
// b = 0.5 * (-alpha + 3^0.5 * beta)
// c = 0.5 * (-alpha - 3^0.5 * beta)
//
//==============================================================================
#if 0
void ClarkeInversionCalc(struct CLARKE_INVERSION_STR *p)
{
    p->a = p->alpha;
    p->b = 0.5 * (-p->alpha + SQRT3 * p->beta);
    p->c = 0.5 * (-p->alpha - SQRT3 * p->beta);
}
#elif 1
void ClarkeInversionCalc(struct CLARKE_INVERSION_STR *p)
{
    p->a = p->alpha;
    p->c = 0.5 * (-p->alpha - SQRT3 * p->beta);
    p->b = -(p->a + p->c);
}
#endif



//==============================================================================
//
// park变换
// 
// d =  alpha * cos(angle) + beta * sin(angle)
// q = -alpha * sin(angle) + beta * cos(angle)
//
//==============================================================================
void ParkCalc(struct PARK_STR *p)
{
    f32 sinAngle, cosAngle;

    sincos(p->angle, &sinAngle, &cosAngle);
    p->d =  p->alpha * cosAngle + p->beta * sinAngle;
    p->q = -p->alpha * sinAngle + p->beta * cosAngle;
}



//==============================================================================
//
// park反变换
//
// alpha = d * cos(angle) - q * sin(angle)
// beta  = d * sin(angle) + q * cos(angle)
//
//==============================================================================
void ParkInversionCalc(struct PARK_INVERSION_STR *p)
{
    f32 sinAngle, cosAngle;

    sincos(p->angle, &sinAngle, &cosAngle);
    p->alpha = p->d * cosAngle - p->q * sinAngle;
    p->beta  = p->d * sinAngle + p->q * cosAngle;
}



//==============================================================================
//
// 两相旋转坐标系到三相静止坐标系
//
//==============================================================================
#if 0
void Conversion2rTo3s(struct CONVERSION_2R_3S_STR *p)
{
    f32 alpha, beta;
    f32 sinAngle, cosAngle;

    sincos(p->angle, &sinAngle, &cosAngle);
    alpha = p->d * cosAngle - p->q * sinAngle;
    beta  = p->d * sinAngle + p->q * cosAngle;
    p->a = alpha;
    p->b = 0.5 * (-alpha + SQRT3 * beta);
    p->c = 0.5 * (-alpha - SQRT3 * beta);
}
#elif 1
void Conversion2rTo3s(struct CONVERSION_2R_3S_STR *p)
{
    f32 alpha, beta;
    f32 sinAngle, cosAngle;

    sincos(p->angle, &sinAngle, &cosAngle);
    alpha = p->d * cosAngle - p->q * sinAngle;
    beta  = p->d * sinAngle + p->q * cosAngle;
    p->a = alpha;
    p->c = 0.5 * (-alpha - SQRT3 * beta);
    p->b = -(p->a + p->c);
}
#endif


/*******************************************************************************
//PR控制器
	
*******************************************************************************/
void PrRegulatorCalc(struct PRREGULATOR_STR *p)
{
	f32 output;
	f32 Ts;
	f32 Temp;
	f32 output1;
	f32 output2;
	f32 output3;
	f32 pr_a1;
	f32 pr_a2;
	f32 pr_b0;
	f32 pr_b2;

	Ts = OutputProcess.FastLoopSamplePeriod;

	Temp = 4.0 + 4.0*p->pr->resoBw*Ts + p->pr->resoFre * p->pr->resoFre * Ts * Ts;//分母

	pr_a1 = (2.0 * p->pr->resoFre * p->pr->resoFre * Ts * Ts - 8.0) / Temp;
	pr_a2 = (4.0 - 4.0*p->pr->resoBw*Ts + p->pr->resoFre * p->pr->resoFre * Ts * Ts) / Temp;
	pr_b0 = (4*p->pr->integGain*p->pr->resoBw*Ts) / Temp;
	pr_b2 = (-pr_b0);

	if (!p->enable)
	{
		p->input = 0;
	}

	output1 = p->pr->propGain*(p->input + pr_a1*p->pr->lastOneInput + pr_a2*p->pr->lastTwoInput);
	output2 = pr_b0*p->input +pr_b2*p->pr->lastTwoInput;
	output3 = pr_a1*p->pr->lastOneOutput + pr_a2*p->pr->lastTwoOutput;

	output = output1 + output2 - output3;

	output = (output > p->pr->maxLimit) ? p->pr->maxLimit : output;
    output = (output < p->pr->minLimit) ? p->pr->minLimit : output;

	p->out = output * p->enable;
	
	p->pr->lastTwoInput = p->pr->lastOneInput;
	p->pr->lastOneInput = p->input;

	p->pr->lastTwoOutput = p->pr->lastOneOutput;
	p->pr->lastOneOutput = p->out;
}


//==============================================================================
//
// 通用PI函数
// 输入: 
//      p->input.    注意为error，ref-fdb
//      p->pi.       PI的参数, kp, ki, 上下限
//      p->enable.   无效时复位integrator
// 输出:
//      p->out
//
//==============================================================================
//f32 ag,bg;
   //f32 kpOut;
   // 复矢量电流环比例系数dcoeff = 0.5一般
   //  
  //  dzhou_accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput)
  //                - dcoeff * OutputProcess.Frequency * OutputProcess.iRatedFrequency * 0.5 *( iqRegError + iqRegErrorLast)
  //                  *p->pi->propGain * OutputProcess.FastLoopFrequencyPU;
  //
  //  qzhou_accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput)
  //                + dcoeff * OutputProcess.Frequency * OutputProcess.iRatedFrequency * 0.5 *( idRegError + idRegErrorLast)
  //                  * p->pi->propGain * OutputProcess.FastLoopFrequencyPU;
extern f32 iqRegErrorLast;
extern f32 idRegErrorLast;
extern f32 idRegError;
extern f32 iqRegError;
extern f32 dcoeff;
void RegulatorCalcD(struct REGULATOR_STR *p)
{
    f32 output;
    f32 kpOut;
    f32 accmulator;
	

    kpOut = p->pi->propGain * p->input;
	
    if ((p->pi->integGain != 0.0) && (p->enable))
    {   // accumulator += integGain * (input(n) + input(n-1)) / 2
      //  accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput);
          accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput)
                  - dcoeff * OutputProcess.Frequency * OutputProcess.iRatedFrequency * 0.5 *( iqRegError + iqRegErrorLast)
                    *p->pi->propGain * OutputProcess.FastLoopFrequencyPU;
	}
    else
    {   // Reset integrator
        accmulator = 0.0;
        p->input = 0.0;
    }
    
    
    output = accmulator + kpOut;
    output = (output > p->pi->maxLimit) ? p->pi->maxLimit : output;
    output = (output < p->pi->minLimit) ? p->pi->minLimit : output;
    
//	ag = output;
//	bg =  kpOut;
	
    p->pi->accumulator = output - kpOut;


    p->pi->lastInput = p->input;     // save error(n) into error(n-1)

    p->out = output * p->enable;
    
}
void RegulatorCalcQ(struct REGULATOR_STR *p)
{
    f32 output;
    f32 kpOut;
    f32 accmulator;
	

    kpOut = p->pi->propGain * p->input;
	
    if ((p->pi->integGain != 0.0) && (p->enable))
    {   // accumulator += integGain * (input(n) + input(n-1)) / 2
       // accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput);
          accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput)
                  + dcoeff * OutputProcess.Frequency * OutputProcess.iRatedFrequency * 0.5 *( idRegError + idRegErrorLast)
                    * p->pi->propGain * OutputProcess.FastLoopFrequencyPU;
	}
    else
    {   // Reset integrator
        accmulator = 0.0;
        p->input = 0.0;
    }
    
    
    output = accmulator + kpOut;
    output = (output > p->pi->maxLimit) ? p->pi->maxLimit : output;
    output = (output < p->pi->minLimit) ? p->pi->minLimit : output;
    
//	ag = output;
//	bg =  kpOut;
	
    p->pi->accumulator = output - kpOut;


    p->pi->lastInput = p->input;     // save error(n) into error(n-1)

    p->out = output * p->enable;
    
}
void RegulatorCalc(struct REGULATOR_STR *p)
{
    f32 output;
    f32 kpOut;
    f32 accmulator;
	

    kpOut = p->pi->propGain * p->input;
	
    if ((p->pi->integGain != 0.0) && (p->enable))
    {   // accumulator += integGain * (input(n) + input(n-1)) / 2
        accmulator = p->pi->accumulator + 0.5 * p->pi->integGain * (p->input + p->pi->lastInput);
    }
    else
    {   // Reset integrator
        accmulator = 0.0;
        p->input = 0.0;
    }
    
    
    output = accmulator + kpOut;
    output = (output > p->pi->maxLimit) ? p->pi->maxLimit : output;
    output = (output < p->pi->minLimit) ? p->pi->minLimit : output;
    
//	ag = output;
//	bg =  kpOut;
	
    p->pi->accumulator = output - kpOut;


    p->pi->lastInput = p->input;     // save error(n) into error(n-1)

    p->out = output * p->enable;
    
}
//=======================================================================
void CellVoltageRegulator(struct CELL_VOLTAGE_REGULATOR_STR *p)
{
   /*

    f32 out;                        // regulated voltage output
    f32 celVoltageFdb;              // celVoltageFdb
    f32 celVoltageRef;              // celVoltageRef 
    f32 celVoltageDelta;            // celVoltageDelta
    f32 maxLimit;                   // maximum limit
    f32 minLimit;                   // minimum limit
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 accumulator;                // integr
    f32 lastInput;                  // lastInput
    bool enable; 
    */
    
    f32 output;
    f32 kpOut;
    f32 accmulator;

    kpOut = p->propGain * p->celVoltageDelta;
    
    if ((p->integGain != 0.0) && (p->enable))
    {   // accumulator += integGain * (input(n) + input(n-1)) / 2
        accmulator = p->accumulator + 0.5 * p->integGain * (p->celVoltageDelta + p->lastInput);
    }
    else
    {   // Reset integrator
        accmulator = 0.0;
        p->celVoltageDelta = 0.0;
    }
    
    output = accmulator + kpOut;
    output = (output > p->maxLimit) ? p->maxLimit : output;
    output = (output < p->minLimit) ? p->minLimit : output;

    p->accumulator = output - kpOut;

    p->lastInput = p->celVoltageDelta;     // save error(n) into error(n-1)

    p->out = output * p->enable;
}



//==============================================================================
//
// Modulo 2 PI
// (0, 2*pi)
//
//==============================================================================
void Modulo2PI(f32 *angle)
{
#if 0
    while (*angle >= TWO_PI) *angle -= TWO_PI;
    while (*angle < 0.0) *angle += TWO_PI;
#elif 0
    f32 tmp;
    tmp = *angle;
    while (tmp > TWO_PI) tmp -= TWO_PI;
    while (tmp < 0.0) tmp += TWO_PI;
    *angle = tmp;
#elif 1
    *angle = *angle - (s32)(*angle * I_TWO_PI) * TWO_PI;
    if (*angle < 0.0)
        *angle += TWO_PI;
#elif 1
    f32 k;
    k = *angle * I_TWO_PI;
    k = k - (s32)k;
    k = (k >= 0) ? k : (k + 1.0);
    *angle = k * TWO_PI;
#endif
}



//==============================================================================
//
// Modulo signed PI limits between (-PI and + PI)
//
//==============================================================================
void ModuloSignedPI(f32 *angle)
{
    while (*angle > ONE_PI)
    {
        *angle -= TWO_PI;
    }
    
    while (*angle < -ONE_PI)
    {
        *angle += TWO_PI;
    }
}




/*******************************************************************************
* Function Name  : CoffFilter1stF32.c	// bycb14269
* Description    : F32型莸囊唤坠咝月瞬ǎ捎盟咝员浠?s= 2/Ts * (z-1)/(z+1)
			1/(Tor*s + 1)    coff = 1/( 2*Tor/Ts + 1)
* Input          : F32型采样数据;
* Output         : F32型滤波后采样数据
* Return         : F32型滤波后采样数据
*******************************************************************************/
void CoffFilter1stF32(COFF_FILTER1STF32_STRUCT *pFilter1stF32)
{
	f32	mF32Data1;

	mF32Data1 = pFilter1stF32->Input + pFilter1stF32->InputLast;	// X(k+1)+X(k)
	mF32Data1 = mF32Data1 - 2.0f * pFilter1stF32->Out; // X(k+1)+X(k)-2*Y(k)
	mF32Data1 = pFilter1stF32->Coff * mF32Data1;	// coff * ( X(k+1)+X(k)-2*Y(k) )
	pFilter1stF32->Out = pFilter1stF32->Out + mF32Data1;// Y(k+1) = Y(k) + coff * ( X(k+1) + X(k) - 2*Y(k) )

	pFilter1stF32->InputLast = pFilter1stF32->Input;
}

   









//==============================================================================
//
// Synchronous filter
// 求一个周期内的平均值 
// 在 (TRUE == reset) 时求平均值
//
//==============================================================================
#if 0
void
SynchFilter(
    f32 new_input,                  // New Input to filter
    f32 *out,                       // Output
    f32 *accumulator,               // accumulated value
    f32 one_over_sample_period,     // 1.0 / sample period (number of samples)
    bool reset)                     // resets accumulator
{
    f32 tmp;

    tmp = *accumulator + new_input;
    if (TRUE == reset)
    {                // at every 2 PI rollover
        *out = tmp * one_over_sample_period;
        tmp = 0.0;
    }
    *accumulator = tmp; 
}
#endif






























//==================================================================================================
//
// 电流环
// 励磁电流环调节器，转矩电流环调节器
//
//
//
//==================================================================================================


#include "m_currentLoop.h"
#include "m_output.h"
#include "m_main.h"

extern f32 sampleVoldOb,sampleVolqOb;


#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
#pragma CODE_SECTION(MagnetizingCurrentReg,     "ramfuncs");
#pragma CODE_SECTION(TorqueCurrentReg,          "ramfuncs");
#endif



struct REGULATOR_STR regulatorDataId;
struct REGULATOR_STR regulatorDataIq;

struct PiDataType idRegulatorParams;
struct PiDataType iqRegulatorParams;

f32 idRegError;
f32 iqRegError;
f32 iqRegErrorLast;
f32 idRegErrorLast;
extern Uint16 cfGroup[];
//f32 itOutMin = -0.2;
//==============================================================================
//
// Magnetizing Current Regulator
//
//==============================================================================
void MagnetizingCurrentReg(struct MAGNETIZING_CURRENT_REG_STR *p)
{
    bool enable; 
	static Uint16 RunFlag = 0;//删掉程序不执行，先不动

    idRegulatorParams.propGain  = p->propGain;
    idRegulatorParams.integGain = p->integGain;
    idRegulatorParams.maxLimit  = p->maxLimit;
    idRegulatorParams.minLimit  = -idRegulatorParams.maxLimit;
//    idRegulatorParams.minLimit  = itOutMin;
    
    // enable regulator flux reference > 0.0
    enable = (p->fluxReference > 0.0) ? TRUE : FALSE;

    // returns regulated voltage
    {
//        struct REGULATOR_STR regulatorDataId;		

        idRegError = p->reference - p->feedback;
        regulatorDataId.input = idRegError;
        regulatorDataId.enable = enable;
		if(cfGroup[15] == 0)
		{
        	RegulatorCalc(&regulatorDataId);
		}
		else
		{
        	RegulatorCalcD(&regulatorDataId);
		}
        p->out = regulatorDataId.out;
    }
	idRegErrorLast = idRegError;
}


f32 vqsffScaler;
f32 vqsffSetpoint;
f32 vqff;                               // 转矩电流环前馈
extern f32 curLoopFeedForwardGain;

#define oneHalfHertz    ONE_PI
#define iqGainRate      0.001
//==============================================================================
//
// Torque Current Regulator
//
//==============================================================================
void TorqueCurrentReg(struct TORQUE_CURRENT_REG_STR *p)
{
    //f32 tmp;

/*
// determine vqs feedforward scaler based on drive state
//    if (IM_SVC2 == OutputProcess.ControlAlgorithm)
//    {
//        vqsffScaler = 0.0;
//    }
//    else if (MAGNETIZING_STATE == DriveControl.State)
//    {
//        vqsffScaler = 0.5;
//    }
//    else
    {                              // ramp scaler up or down to config setting
        if ((TRUE == OutputProcess.CellImbalance) && (curLoopFeedForwardGain < 0.5))
        {
            vqsffSetpoint = 0.5;
        }
        else
        {
            vqsffSetpoint = curLoopFeedForwardGain;
        }

        if (vqsffScaler > vqsffSetpoint)
        {
            vqsffScaler -= 0.0001;
            if (vqsffScaler < 0.0)
                vqsffScaler = 0.0;
        }
        else if (vqsffScaler < vqsffSetpoint)
        {
            vqsffScaler += 0.0001;
        }
        else
        {
            vqsffScaler = vqsffSetpoint;
        }
    }

    // calculate vqs feedforward based on braking enabled or disabled
    if (TRUE == OutputProcess.Braking)
    {
        tmp = OutputProcess.FluxDSFil * OutputProcess.WsFil;
    }
    else
    {
        tmp = OutputProcess.FluxDS * OutputProcess.Frequency;
    }
    vqff = (vqsffScaler * tmp * OutputProcess.MotorVoltageClampLimit * 
        OutputProcess.iRatedFrequency) * OutputProcess.Enable;
    */
//=========================================================
    
    iqRegulatorParams.propGain  = p->propGain;
    iqRegulatorParams.integGain = p->integGain;
    iqRegulatorParams.maxLimit  = p->maxLimit;
    iqRegulatorParams.minLimit  = -iqRegulatorParams.maxLimit; 

    // regulator is enabled when speed reference is > 0.1
    
   // if (fabs(p->speedReference) > 0.1)
    {
        *(p->enable) = TRUE;
    }
    // regulator is disabled if motor speed drops below 1/2 hertz
   // else if (fabs(p->motorSpeed) < oneHalfHertz)
  //  else
  //  {
  //      *(p->enable) = FALSE;
  //  }
 
/*
    tmp = *(p->iqGain);
    // iqGain is set to one if torque regulator is enabled
    if (*(p->enable))
    {
        tmp = 1.0;
    }
    // ramp down gain to zero if torque regulator is disabled 
    else
    {
        tmp -= iqGainRate;
        tmp = (tmp < 0.0) ? 0.0 : tmp;
    }
    *(p->iqGain) = tmp;
*/
    // returns regulated voltage
    {
//        struct REGULATOR_STR regulatorDataIq;

        iqRegError = p->reference - p->feedback;
        regulatorDataIq.input = iqRegError;
        regulatorDataIq.enable = p->globalEnable;
		if(cfGroup[15] == 0)
		{
        	RegulatorCalc(&regulatorDataIq);
		}
		else
		{
        	RegulatorCalcQ(&regulatorDataIq);
		}
        p->out = regulatorDataIq.out;
    }
	iqRegErrorLast = iqRegError;
}
















//==================================================================================================
//
// 频率源处理
// 这里借用了这个名字，还包括flux给定的处理
//
//
//
// 
//
//==================================================================================================


#include "m_frqSrc.h"
#include "m_main.h"
#include "m_interface.h"
#include "m_autoTune.h"
#include "m_spinningLoad.h"
#include "m_brake.h"
#include "m_interfaceModify.h"

#include "m_macro_transfer.h"




#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_TORQUE_TEST     1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_TORQUE_TEST     0
#endif


int16 coreFrq;      // Q15
int32 coreFrqHz;    // 0.01Hz
int16 coreFrqAim;
int32 coreFrqAimHz;

Uint16 coreMaxFrq;  // 功能传递的最大频率，0.01Hz



extern u16 speedLoopSpinEnable;


struct CommandGeneratorType CommandGenerator;





f32 EnergySaverControl(f32 input);
f32 FieldWeakening(f32 input);
f32 FluxRamp(f32 input);

extern void SpinningLoadSlowDeal(void);


u16 startFlag;  // 正在启动

u16 lowVolTicker;
u16 lowVolFlag;
extern f32 inputVol;
extern f32 inputVolFil;
u32 frqStart = 100;     // *0.01Hz，最低频率。非停机。
u32 frqStop = 100;      // *0.01Hz，最低频率。停机时的处理
extern f32 iqFdbFil;
extern f32 FluxRef;
//==============================================================================
//
// 磁链给定计算
// 频率给定计算
//
//==============================================================================
void CommandGeneratorControl(void)
{
    f32 tmp;
    
    if ((TRUE == AutoTune.RequestStage1) 
        || (SPINNING_LOAD_STATE == DriveControl.State)
       )
    {
        return;
    }    

// Calculate droop scaled for units of speed
//    if (true == OutputProcess.usePllAndDroop)

    if (speedLoopSpinEnable)
    {
        tmp = coreFrqHz;
        CommandGenerator.SpeedReference = (f32)tmp * (TWO_PI / 100);
    }
    
    CommandGenerator.SpeedReferencePU = CommandGenerator.SpeedReference * OutputProcess.iRatedFrequency;
    if(AUTO_TUNE_STATE != DriveControl.State) 
    {
   		OutputProcess.PerUnitSpeedReference = fabs(CommandGenerator.SpeedReferencePU);
    }
    if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
    {
		if (AUTO_TUNE_STATE != DriveControl.State)
		{
			OutputProcess.PerUnitSpeedReference = fabs(CommandGenerator.SpeedReferencePU);
		}
	}
    else
	{
		OutputProcess.PerUnitSpeedReference = fabs(CommandGenerator.SpeedReferencePU);
 	}
    CommandGenerator.RawFluxDemand = fluxCtrlMenu.fluxDemand;
// 启动后3s
// 或者转矩电流大于0.9
#define TIME_STRAT_LARGE_FLUX_TIME  3.0
#define TIME_STRAT_LARGE_FLUX       1.2

    {
        static f32 timeStart;

        tmp = TIME_STRAT_LARGE_FLUX_TIME;
        tmp = (f32)cfGroup[11] / 1000;

        startFlag = 0;
        if (TRUE == OutputProcess.Enable)
        {
            timeStart += MAIN_LOOP_TIME;
            if (timeStart >= tmp)
            {
                timeStart = tmp;
            }
            else
            {
                startFlag = 1;  // 正在启动
            }
        }
        else
        {
            timeStart = 0;
        }

        if ((motorControlOtherEnable.bit.startLargeFlux)     // 
            && (startFlag)
           )
        {
            f32 tmp1;
//                tmp1 = fluxCtrlMenu.fluxDemand * TIME_STRAT_LARGE_FLUX;
                tmp1 = fluxCtrlMenu.fluxDemand * cfGroup[10] * (1.0 / 100);

            CommandGenerator.RawFluxDemand = tmp1;
        }
    }

  

#if DEBUG_P_SYNC_TRANSFER
    // modify flux demand to match line voltage on transfer
    if ((UP_TRANSFER_STATE == DriveControl.State) || (DOWN_TRANSFER_STATE == DriveControl.State))
    {
        CommandGenerator.RawFluxDemand = 
            fluxCtrlMenu.fluxDemand * inputVolFil;
//            InputProcess.Ed * (CommandGenerator.RawFluxDemand / (1.0 - InputProcess.TransformerTapSetting))
//            * (driveParameterMenu.ratingOuputVoltage / InputProcess.Frequency)
//            * (OutputProcess.RatedFrequency   / motorPara.ratingVoltage); 
    }
#endif

    CommandGenerator.EnergySaverOutput = EnergySaverControl(CommandGenerator.RawFluxDemand);
#if DEBUG_P_SYNC_TRANSFER
    if ((UP_TRANSFER_STATE == DriveControl.State) || (DOWN_TRANSFER_STATE == DriveControl.State))
    {
        CommandGenerator.FieldWeakeningOutput = CommandGenerator.EnergySaverOutput;
    }
    else
#endif
    {
        //if (SM_FVC != motorControlMode)
        {
            CommandGenerator.FieldWeakeningOutput = FieldWeakening(CommandGenerator.EnergySaverOutput);
        }
       // else
        {
            //CommandGenerator.FieldWeakeningOutput = FluxRef;
        }
    }
    CommandGenerator.FluxRampOutput = FluxRamp(CommandGenerator.FieldWeakeningOutput);
    tmp = CommandGenerator.FluxRampOutput; 

// 下切换，flux不进行斜坡处理。
#if DEBUG_P_SYNC_TRANSFER
    if ((DOWN_TRANSFER_STATE == DriveControl.State) && (OutputProcess.Enable))
//    if (fluxRefUseInputEd)
    {
        tmp = fluxCtrlMenu.fluxDemand * inputVolFil;
    }
#endif

    CommandGenerator.FluxReference = tmp;

// 关闭预励磁
    if (((!motorControlOtherEnable.bit.magnetize) && (!smControl))  // 同步机一直开启预励磁
        ||
        (PURE_VF == motorControlMode)
       )
    {
        CommandGenerator.FluxAtSetPoint = TRUE;
    }
}



extern u16 flux__Src;
//==============================================================================
//
// 节能控制
//
//==============================================================================
f32 EnergySaverControl(f32 input)
{
    f32 output;

    output = input;

#if DEBUG_P_DUAL_FRQ_BRAKE
//    if (DUAL_FREQUENCY_BRAKING == flux__Src)
    if ((1 == flux__Src) 
//        || 
//        ((2 == coreMainCmd.bit.accDecStatus) && 
//         (OutputProcess.BrakingEnable)
//        )
       )
    {
//        output = fabs(0.5 * fluxCtrlMenu.fluxDemand
//            * OutputProcess.RatedFrequency / CommandGenerator.SpeedReference);

        output = fabs(0.5 * fluxCtrlMenu.fluxDemand
            * OutputProcess.RatedFrequency / OutputProcess.WsFil);

        if (output > input)
        {
            output = input;
        }
        else if (output < 0.5)
        {
            output = 0.5;
        }
    }
#endif

    return output;
}







RAMP_CTRL_STRUCT fluxRampCtrl;
u32 FluxAtSetPointTicker;
u32 FluxAtSetPointTickerMax = 0;
f32 fluxSetup = 0.90;
//==============================================================================
//
// 磁链给定斜坡处理
//
//==============================================================================
f32 FluxRamp(f32 input)
{
    if (COAST_STATE == DriveControl.State)
    {
        input = 0.0;
    }

    if (IDLE_STATE == DriveControl.State)   // 停机后清零
    {
        fluxRampCtrl.curValue = 0.0;
        FluxAtSetPointTicker = 0;
    }
    else
    {
        fluxRampCtrl.aimValue = input;
        fluxRampCtrl.maxValue = 1.0;
        fluxRampCtrl.tickerAll = fluxCtrlMenu.fluxRampRate * (1000 / SLOW_LOOP_TIME_MS);
        RampCalc(&fluxRampCtrl);
    }

    if (input > 0.15)
    { // this prevents a race condition that caused the FluxAtSetPoint to be true prematurely
        if ((OLTM == OutputProcess.ControlAlgorithm) ||
            (TRUE == smControl) ||      // 同步机控制
            (TRUE == OutputProcess.HighStartingTorqueEnable)
           )
        {
            if (fluxRampCtrl.curValue > 0.95 * input)
            {
                CommandGenerator.FluxAtSetPoint = TRUE;
            }
            else
            {
                CommandGenerator.FluxAtSetPoint = FALSE;
            }
        }
        else
        {
#if 1
            if ((OutputProcess.FluxDS > fluxSetup * input) && 
                (FALSE == SpinningLoad.UseFluxReference) && 
                (fluxRampCtrl.curValue >= 0.99 * input)
               )
            {
                CommandGenerator.FluxAtSetPoint = TRUE;
            }
            else
            {
                CommandGenerator.FluxAtSetPoint = FALSE;
            }
#elif 1 
            if ((fluxRampCtrl.curValue >= input) &&
                (FALSE == SpinningLoad.UseFluxReference)
               )
            {
                if (OutputProcess.FluxDS > fluxSetup * input)
                {
                    FluxAtSetPointTicker++;
                    if (FluxAtSetPointTicker >= FluxAtSetPointTickerMax/MAIN_LOOP_TIME_MS)
                    {
                        CommandGenerator.FluxAtSetPoint = TRUE;
                    }
                }
            }
            else
            {
                CommandGenerator.FluxAtSetPoint = FALSE;
                FluxAtSetPointTicker = 0;
            }
#endif
        }
    }
    else
    {
        CommandGenerator.FluxAtSetPoint = FALSE;
        
    }

    SpinningLoadSlowDeal();

    fluxRampCtrl.curValue = GetMax(fluxRampCtrl.curValue, 0.0);

    return(fluxRampCtrl.curValue);
}



#if DEBUG_P_TORQUE_TEST
//==============================================================================
//
// Torque Test - creates a squarewave of duration 2 * testtime
//
//==============================================================================
f32 TorqueTest(f32 maxLimit, f32 minLimit)
{
    static f32 testTimer;
    f32 output;

    testTimer += OutputProcess.SlowLoopSamplePeriod;

    if (testTimer <= ctrlLoopTestMenu.testTime)
    {
        output = ctrlLoopTestMenu.testPointPositive;
    }
    else
    {
        if (testTimer >= (ctrlLoopTestMenu.testTime * 2.0))
        {
            testTimer = 0;
        }
        output = ctrlLoopTestMenu.testPointNegative;
    }

    // limit output
    if (output > maxLimit)
    {
        output = maxLimit;
    }
    else if (output < minLimit)
    {
        output = minLimit;
    }

    return (output);
}
#endif







//==================================================================================================
//
//
// 快速制动单元过压抑制处理
// 简单的过压抑制处理: 加减速禁止标记
// 
//
//
//
//==================================================================================================


//==============================================================================

//============================================================================== 

#include "m_main.h"
#include "m_interface.h"
#include "m_input.h"
#include "m_frqSrc.h"
#include "m_cell.h"
#include "m_cell_bypass.h"
#include "m_autoTune.h"
#include "m_spinningLoad.h"
#include "m_transfer.h"
#include "m_brake.h"
#include "m_fluxStatorObserve.h"
#include "m_currentLoop.h"
#include "m_speedLoop.h"
#include "m_fluxLoop.h"
#include "m_slip.h"
#include "m_modInterpUpdate.h"
#include "m_peakReduction.h"
#include "m_deadbandComp.h"
#include "m_npc.h"

#include "m_macro_sm.h"
#include "m_macro_tune.h"
#include "m_macro_transfer.h"
#include "m_macro_lowFrq.h"
#include "m_macro_error.h"
#include "m_macro_loadSharing.h"
#include "m_accDecDeal.h"
#include "m_speedRollback.h"
#include "m_error.h" 

#define     VDCRAMPTIME     50      // 母线电压指令斜坡时间，单位ms
#define     FASTDECVHZMIN   0.3     // 减速制动最小频率之差，单位Hz
#define     FAST_REGEN_MIN  0.001   // 快速制动最小发电转矩下限判断
#define     FAST_REGEN_MAX  0.20    // 过压抑制发电转矩调整最大上限
f32 overVolInhibitKp, overVolInhibitKi;
struct CELL_VOLTAGE_REGULATOR_STR cellVoltageRegulatorBrk;
//RAMP_CTRL_STRUCT vdcSetRamp;
u16 decVolDealEnable;
//extern f32 cellDCVoltage;
extern struct SPEED_REGULATOR_STR spdRegData;
extern f32 iqRef;
f32 cellVolDelta;
extern BUS_VOTAGE invbusVoltage;
extern f32 udcMax,udcHalfoverMax,up1,down1;
f32 udcPreControl;

f32 minLimitwork = 0;

f32 outold = 0;

u16 FastDecDealtimes = 0;
void FastDecDeal(void)
{
	static f32 minLimitold;
	static f32 minLimitReal;

	static f32 maxLimitold;
	static f32 maxLimitReal;
	
    //f32 udcPreControl;
	udcPreControl = udcMax - 0.08;
	if(udcPreControl >= 1.3)
	{
		udcPreControl = 1.3;
	}
    cellVoltageRegulatorBrk.celVoltageFdb = invbusVoltage.add;
    cellVolDelta = udcPreControl -  cellVoltageRegulatorBrk.celVoltageFdb;	
    if (
		//((coreMainCmd.bit.accDecStatus == 2) 
        //  || (fabs(spdRegData.speedReference - spdRegData.wr) > FASTDECVHZMIN * TWO_PI)
        //  || ((iqRef < -FAST_REGEN_MIN) && (spdRegData.speedReference > 0.0))
        //  || ((iqRef > FAST_REGEN_MIN) && (spdRegData.speedReference < 0.0))
        //  || ((iqRef * OutputProcess.Frequency) < 0.0)
        // )
        // && 
         (decVolDealEnable)
         && (overVolInhibitKp > 0.0)  // 过压抑制比例增益设置为0.0为关闭该功能
         && (cellVolDelta <= 0.03)
         //|| ((udcHalfoverMax - up1)< 0.02)||((udcHalfoverMax - down1)< 0.02)) // 单元母线电压在5020~5300V之间控制,取决于母线过压点的设置
       )  // 1.181 - 1.127 = 0.054
	{     // 1.127 = 1050V / (690V * 1.35), 1.181-->1100V, 1.234-->1150V
		/*
		vdcSetRamp.maxValue = udcPreControl;    // 控制母线电压最大值为过压点-0.02；
        vdcSetRamp.tickerAll = VDCRAMPTIME / SLOW_LOOP_TIME_MS;
        vdcSetRamp.aimValue = vdcSetRamp.maxValue;   
        if (0 == cellVoltageRegulatorBrk.enable)
        {
            vdcSetRamp.curValue = cellVoltageRegulatorBrk.celVoltageFdb;    // 停止制动时要清零
        }
        else
        {
            RampCalc(&vdcSetRamp); 
        }
        */
        cellVoltageRegulatorBrk.celVoltageRef = udcPreControl;//vdcSetRamp.curValue;
        cellVoltageRegulatorBrk.celVoltageDelta = (cellVoltageRegulatorBrk.celVoltageRef - 
                                    cellVoltageRegulatorBrk.celVoltageFdb);
        cellVoltageRegulatorBrk.propGain = overVolInhibitKp;
        cellVoltageRegulatorBrk.integGain = overVolInhibitKi;
		{
		    cellVoltageRegulatorBrk.maxLimit = 0.15;
            cellVoltageRegulatorBrk.minLimit = spdRegData.minLimit - FAST_REGEN_MAX;
		}
         
		cellVoltageRegulatorBrk.enable = (cellVoltageRegulatorBrk.celVoltageDelta <= 0.05);
        CellVoltageRegulator(&cellVoltageRegulatorBrk); 

        if (0 == cellVoltageRegulatorBrk.enable)
		{
            cellVoltageRegulatorBrk.out = 0;
        }
		/*
        if ((spdRegData.speedReference >= 0.0) &&(OutputProcess.MotorSpeedFiltered > 0.0))    // 正向速度
        {
		    //spdRegData.minLimit = spdRegData.minLimit - cellVoltageRegulatorBrk.out;
			
			if(spdRegData.minLimit <= (spdRegData.minLimit - cellVoltageRegulatorBrk.out))
			{
			    spdRegData.minLimit = spdRegData.minLimit - cellVoltageRegulatorBrk.out;
			}
			else
			{
				spdRegData.minLimit = minLimitold - 0.01; 
			}
			
			if (spdRegData.minLimit > FAST_REGEN_MAX)
			{
			    spdRegData.minLimit = FAST_REGEN_MAX;
			}

			minLimitold = spdRegData.minLimit;
		}
        if ((spdRegData.speedReference <= 0.0) &&(OutputProcess.MotorSpeedFiltered < 0.0))    // 反向速度
        {
            spdRegData.maxLimit = spdRegData.maxLimit + cellVoltageRegulatorBrk.out;
			if (spdRegData.maxLimit < -FAST_REGEN_MAX)
			{
			    spdRegData.maxLimit = -FAST_REGEN_MAX;
			}
        }
        */
	}
	else
	{
		cellVoltageRegulatorBrk.out = 0;
		cellVoltageRegulatorBrk.enable = 0;
    }

	if((decVolDealEnable)
         && (overVolInhibitKp > 0.0))
		{
			if ((spdRegData.speedReference >= 0.0) &&(OutputProcess.MotorSpeedFiltered > 0.0))    // 正向速度
	        {
			    //spdRegData.minLimit = spdRegData.minLimit - cellVoltageRegulatorBrk.out;
				minLimitReal = spdRegData.minLimit;

				if(cellVoltageRegulatorBrk.out <= outold)
				{
					spdRegData.minLimit = spdRegData.minLimit - cellVoltageRegulatorBrk.out;
				}
				else
				{
					spdRegData.minLimit = minLimitold - 0.01;
				}

				if(spdRegData.minLimit > minLimitReal)
				{
					FastDecDealtimes ++; 
				}

				if (spdRegData.minLimit >= FAST_REGEN_MAX)
				{
				    spdRegData.minLimit = FAST_REGEN_MAX;
				}
				else if(minLimitReal > spdRegData.minLimit)
				{
					spdRegData.minLimit = minLimitReal;
				}
				
				outold = cellVoltageRegulatorBrk.out;
				minLimitold = spdRegData.minLimit;
				minLimitwork = minLimitold;
				/*
				if(spdRegData.minLimit < (spdRegData.minLimit - cellVoltageRegulatorBrk.out))
				{
				    minLimitwork = spdRegData.minLimit - cellVoltageRegulatorBrk.out;
				}
				else
				{
					minLimitwork = minLimitold - 0.01; 
				}
				
			
				if (minLimitwork >= 0.0)
				{
				    minLimitwork = 0.0;
				}
				else if(minLimitReal > minLimitwork)
				{
					minLimitwork = minLimitReal;
				}
				
				
				minLimitold = minLimitwork;
				spdRegData.minLimit = minLimitwork;
				*/
			}
	        if ((spdRegData.speedReference <= 0.0) &&(OutputProcess.MotorSpeedFiltered < 0.0))    // 反向速度
	        {
	        	/*
	            spdRegData.maxLimit = spdRegData.maxLimit + cellVoltageRegulatorBrk.out;
				if (spdRegData.maxLimit < -FAST_REGEN_MAX)
				{
				    spdRegData.maxLimit = -FAST_REGEN_MAX;
				}*/

				maxLimitReal = spdRegData.maxLimit;

				if(cellVoltageRegulatorBrk.out <= outold)
				{
					spdRegData.maxLimit = spdRegData.maxLimit + cellVoltageRegulatorBrk.out;
				}
				else
				{
					spdRegData.maxLimit = maxLimitold + 0.01;
				}

				if(spdRegData.maxLimit < maxLimitReal)
				{
					FastDecDealtimes ++; 
				}

				if (spdRegData.maxLimit <= -FAST_REGEN_MAX)
				{
				    spdRegData.maxLimit = -FAST_REGEN_MAX;
				}
				else if(maxLimitReal < spdRegData.maxLimit)
				{
					spdRegData.maxLimit = maxLimitReal;
				}
				
				outold = cellVoltageRegulatorBrk.out;
				maxLimitold = spdRegData.maxLimit;
				minLimitwork = maxLimitold;
	        }
		}
} 


// 预励磁过程过压抑制调节制动转矩上限
extern struct DriveControlType DriveControl;
extern f32 SpeedReferenceCore2Fun;
struct REGULATOR_STR regulatorDataIqMag;
struct PiDataType iqMagMaxRegulatorParams;
extern struct OVER_VOL_SUPPRESS_REG_STR iqMagRegData;
#define oneHalfHertzMag    ONE_PI
f32 MAG_REGEN_MAX = 0.03;
/*
void OverVolSuppressionReg(struct OVER_VOL_SUPPRESS_REG_STR *p)
{
    int16 flag;
    f32 udcPreControl1;
	udcPreControl1 = udcMax - 0.05;
	if(udcPreControl1 >= 1.15)
	{
		udcPreControl1 = 1.15;
	}
    iqMagMaxRegulatorParams.propGain = overVolInhibitKp;
    iqMagMaxRegulatorParams.integGain = overVolInhibitKi * OutputProcess.SlowLoopSamplePeriod;
    iqMagMaxRegulatorParams.maxLimit = 0.0;
    iqMagMaxRegulatorParams.minLimit = -MAG_REGEN_MAX;
    
    if (SpeedReferenceCore2Fun > oneHalfHertzMag)
    {
        flag = -1;
    }
    else if (SpeedReferenceCore2Fun < -oneHalfHertzMag)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    iqMagRegData.reference = udcPreControl1; 
    iqMagRegData.feedback  = invbusVoltage.add * 0.0010695187;
    regulatorDataIqMag.input = iqMagRegData.reference - iqMagRegData.feedback;
    regulatorDataIqMag.enable = ((p->globalEnable)
                                  && (DriveControl.State == MAGNETIZING_STATE)
                                  && (overVolInhibitKp != 0.0)
                                  );
    RegulatorCalc(&regulatorDataIqMag);

    iqMagRegData.out = regulatorDataIqMag.out * flag;
}
*/






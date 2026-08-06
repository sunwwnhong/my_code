




#include "m_frqSrc.h"
#include "main.h"
#include "m_output.h"
#include "m_main.h"
#include "m_transfer.h"

#include "m_accDecDeal.h"
#include "m_interface.h"
#include "m_interfaceModify.h"
#include "m_cell.h"


f32 FieldWeakening(f32 input);

f32 volLineMax;
//f32 tttttttt = 1.0;

//extern u16 synchTransfer;
extern f32 udcFil;
//u16 dfasxz = 1;
extern f32 lcLPu;
//f32 adfsz = 0.05;
f32 fluxlimitA;
//f32 nbsa;
f32 testfluxref;
extern f32 iTotalFil;
extern Uint16 ranksMin;                 // 线间最小单元数
extern f32 cellDCVoltage;               // 单元母线电压
extern u32 cellBypassCmdNew;            // 旁路命令
extern Uint16 coreMaxFrq;
f32 ratedFrequencyFil;           // 弱磁处理后等效的临界频率
 u16 coreMaxFrqBypass;             // 旁路后的最大频率，0.01Hz
extern f32 inputVolFil;
extern u32 cellBypassCmd;
extern f32 inputVolDis;
extern f32 OutputMotorSpeedFiltered;
extern f32 inputVolFil;
f32 volLineMaxCnt = 1.0;
//f32 inputGainFlag = 1.05;
//==============================================================================
//
// 弱磁控制
//
//==============================================================================
f32 FieldWeakening(f32 input)
{
    f32 fluxlimit;
    f32 spd;
    f32 tmp;
    f32 tmp1;
    //f32 ratedFrequency;

	if(cfGroup[16] != 0)
	{
		tmp = fabs(OutputProcess.FrequencyFiltered / motorPara.ratingFrq * I_TWO_PI);
	}
	else
	{
    	tmp = fabs(CommandGenerator.SpeedReference / motorPara.ratingFrq * I_TWO_PI);
	}
    spd = GetMax(tmp, 0.05);

	fluxlimit = OutputProcess.RatedFrequency / spd;
    {
        f32 LVolDrop;
        
        // 最大的输出电压上限，考虑输出电感
        LVolDrop = fabs(OutputProcess.WsFilPu) * lcLPu * OutputProcess.IdsFil * SQRT3;
        volLineMax = udcFil * driveParameterMenu.ratingInputVoltage;
		if(motorPara.ratingVoltage != 0)
		{			
		    tmp1 = volLineMax / motorPara.ratingVoltage - LVolDrop - (f32)((s32)(s16)funcCode.code.WeakFluxdepth)*0.01;
				    
        	volLineMaxCnt = LPF_K(tmp1, volLineMaxCnt, 15.0/MAIN_LOOP_TIME_MS);

		}

    }
	fluxlimit = volLineMaxCnt / spd;
	
/*
    
  //  coreMaxFrqBypass = coreMaxFrq;  // HD3X最大频率不限制
    ratedFrequency = (tmp1 * motorPara.ratingFrq + 0.5) * TWO_PI;   // 额定频率根据母线电压平均值修正
    ratedFrequencyFil = LPF_K(ratedFrequency, ratedFrequencyFil, 100/MAIN_LOOP_TIME_MS);    
    
    if ((tmp > ratedFrequencyFil) &&   
        (OutputProcess.ControlAlgorithm != PURE_VF)         // VF控制时不进行弱磁
        )
    {
        f32 fluxlimitmin;
        
       // fluxlimitA = fabs(tmp1 / OutputProcess.WsFilPu);  
        fluxlimitA = fabs(tmp1 / OutputMotorSpeedFiltered);
        if (fabs(OutputProcess.WsFilPu) < 0.05)
        {
            fluxlimitA = input;
        }
        fluxlimit = GetMin(fluxlimit, fluxlimitA);
        fluxlimitmin = fluxCtrlMenu.fluxDemand * (1.0 / 3);
        fluxlimit = (fluxlimit < fluxlimitmin) ? fluxlimitmin : fluxlimit;
    }
*/

    input = GetMin(fluxlimit, input);
    testfluxref = input;
    return input;
}




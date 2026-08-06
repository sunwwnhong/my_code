//==================================================================================================
//
// 性能状态处理
// 空闲、励磁、正常运行、调谐、同步切换、飞车启动等处理
//
//
// Time-stamp: <2012-2-19 4:55:59  author, 0000>
//
//==================================================================================================


#include "m_stateControl.h"
#include "m_main.h"
#include "m_autoTune.h"
#include "m_spinningLoad.h"
#include "m_transfer.h"
#include "m_interface.h"
#include "m_frqSrc.h"
#include "m_error.h"
//#include "funcCode.h"
#include "m_interfaceModify.h"

#include "m_macro_sm.h"
#include "m_macro_tune.h"
#include "m_macro_transfer.h"


#include "pmsvc.h"
#include "m_autoTunePmsm.h"


extern void pm_svc_init(void);

extern Uint16 coreTuneCmd;
extern u16 speedLoopSpinEnable;


extern f32 DeltaImSvc4;
extern f32 ImSvc4FluxRFrq;



void IdleState(void);
void MagnetizingState(void);
void NormalRunState(void);
void CoastState(void);
void UpTransferState(void);
void DownTransferState(void);
void RotorInitStatePmsm(void);

extern f32 pllBackEmfFrq;
u16 dcBrakeenable =0;
f32 dcBrakeTime;
u16 dcBrakeStartflag;
f32 netDisconnectTime; 
u16 sotopAFEsignalticker;
//extern u16 inSpinFlag;
//磁极初始位置辨识
#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_PMSM_CONTROL          1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_PMSM_CONTROL          0
#endif
//extern FUNCCODE_ALL funcCode; 
extern union ROTOR_POSITION_REG RotorPositionPwmReg;
extern u16 rotorPositionSection;
extern f32 InitRotorPosition;
extern u16 PmInitPosError;
u16 hhhhpp;
extern u16 EncoderType;
//extern u16 upTransferNetContactorOnstart;
//extern u16 currentLoopFlag;
u16 afeRestartCnt = 400;
extern u16 flagTime;
//==============================================================================
//
// 性能状态处理
// 空闲、励磁、正常运行、调谐、同步切换、飞车启动等处理
//
//==============================================================================
void StateControl(void)
{
    if (IDLE_STATE == DriveControl.State)
    {
        IdleState(); 
//        currentLoopFlag = 0;
        if (!coreMainCmd.bit.run )
        {            
            sotopAFEsignalticker = sotopAFEsignalticker + 1;
        }
        else
        {
            sotopAFEsignalticker = 0;

        } 
        { 
	    	if( sotopAFEsignalticker > afeRestartCnt)  //大样机停机时间较长
		    {
               interfaceRam[FPGA_REG_rsel_vd_afe_wr] = 0x5a5a; 
               sotopAFEsignalticker = 0;
//               upTransferNetContactorOnstart = 0;
		    }
		
		}
    }
    else if ((!coreMainCmd.bit.run) || (coreErrorCode))   // 故障时，DSP停机
    {
        coreRunStatus.bit.run = 0;
        OutputProcess.Enable = FALSE;

        AutoTune.RequestStage1 = FALSE;
        AutoTune.RequestStage2 = FALSE;
        
        DriveControl.State = COAST_STATE;
    }

    switch (DriveControl.State)
    {
        case IDLE_STATE: 
            break;

        case MAGNETIZING_STATE:
            break;

#if DEBUG_P_AUTO_TUNE
        case AUTO_TUNE_STATE:
		    if((IM_SVC1  == motorControlMode)||
				(IM_FVC  == motorControlMode)||
				(IM_SVC2  == motorControlMode)||
				(IM_SVC3  == motorControlMode)||
				(IM_SVC4  == motorControlMode))
			{
            	AutoTuneState();
			}
			if((PMSM_FVC == motorControlMode)||(PMSM_SVC == motorControlMode))
			{
				AutoTuneStatePmsm();
			}
            break;
#endif

#if DEBUG_P_SPINNING_LOAD
        case SPINNING_LOAD_STATE:
            SpinningLoadState();
            break;
#endif

        case RUN_STATE:
            break;

#if DEBUG_P_SYNC_TRANSFER
        case UP_TRANSFER_STATE:
            UpTransferState();
            break;

        case DOWN_TRANSFER_STATE:
            DownTransferState();
            break;
#endif

        case STOP_STATE:
            break;

        case COAST_STATE:
            break;

        default:
            break;
    }

    if (MAGNETIZING_STATE == DriveControl.State)
    {
        MagnetizingState();
    }

    if (RUN_STATE == DriveControl.State)
    {
        NormalRunState();
    }

    if (COAST_STATE == DriveControl.State)
    {
        CoastState();
    }
    
//磁极初始位置辨识    
#if DEBUG_P_PMSM_CONTROL
    if (ROTOR_INITIAL_STATE == DriveControl.State)
    {
        RotorInitStatePmsm();
    }
#endif
}




//extern s32 curTickerTemp;
//u16 spinTicker;
//u16 spinTickerMax = 5;
u32 magTicker;
extern u16 spinLoadStatus;
//extern f32 fieldStartTimer;
extern u16 clControl;
extern bool rollbackenableflag;
u16 rotorObserverFinishFlag;
u16 rotorInitDelayTimer;
//extern f32 idRefBuf;
u16 rotorPosDelayTimer;
u16 RotorPosPluseMethodFinish;
f32 rotorIntPositonRTComp;
u16 posstatetest;
extern u16 flagPos;
//extern u16 qiehuanCounter;
//==============================================================================
//
// 空闲状态
// 等待启动命令(coreMainCmd.bit.run)，然后根据具体的输入命令(tune, 
// synchronous transfer, spinning load等)，进入相应的状态。
//
//==============================================================================
void IdleState(void)
{
    u16 tmp;
    
    coreStatus.bit.speedTrackEnd = 0; 
    speedLoopSpinEnable = 1;
//    spinTicker = 0;
    magTicker = 0;
    dcBrakeStartflag = 0;
    //fieldStartTimer = 0;
    SpinningLoad.SpeedReference = 0.0;
   //	qiehuanCounter = 0;
    coreStatus.bit.forbidAccDecSpd = 1;
  //  ZsignalPostionFlag = 0;
  	if(PMSM_FVC != motorControlMode)
  	{   
//  	    idRefBuf = 0;
     //   ZsignalPostionFlag = 0;
	    rotorPosDelayTimer = 0;
		rotorObserverFinishFlag = 0;
		RotorPosPluseMethodFinish = 0;
		rotorIntPositonRTComp = 0;
		
	}
     flagTime = 0;
	 interfaceRam[FPGA_REG_bypassCmd1] = 0x0120;
//    spinPmsmTicker = 0;
//    inSpinFlag = (TRUE == OutputProcess.SpinningLoadEnable); 
  //  if (cfGroup[21] == 3)
    {
		flagPos = 0;
		interfaceRam[FPGA_REG_bypassCmd1] = 0x0110;
		RotorPositionPwmReg.bit.finishFlg = 0;
	}
    if ((!coreMainCmd.bit.run)   // 停机
        || (coreErrorCode)
       )
    {
        coreRunStatus.bit.run = 0;
        OutputProcess.Enable = FALSE;

        OutputProcess.SMFieldEnable = FALSE;

        coreMotorCtrlTuneStatus = TUNE_STEP_WAIT;

        coreStatus.bit.upTransferFinish = 0;

       // curTickerTemp = 0;
        rollbackenableflag = 0;
        coreSubStatus.bit.speedRollBack = 0; 
        pm_svc_init();
        return;
    }

    tmp = 1;
    coreStatus.bit.forbidAccDecSpd = 0;

#if DEBUG_P_AUTO_TUNE
    if (TUNE_IM_1 == coreTuneCmd)
    {
        AutoTune.StatusStage1 = AT_INIT;
        AutoTune.StatusStage2 = AT_DONE;
        DriveControl.State = AUTO_TUNE_STATE;
    }
    else
#endif
#if DEBUG_P_AUTO_TUNE
    if (TUNE_IM_2 == coreTuneCmd)
    {
        AutoTune.StatusStage1 = AT_DONE;
        AutoTune.StatusStage1 = AT_INIT;            // 动态调谐，先进行静态调谐
        AutoTune.StatusStage2 = AT_INIT;
        DriveControl.State = AUTO_TUNE_STATE;
    }
    else
#endif
#if DEBUG_P_SYNC_TRANSFER
    if ((SYNCH_TRANSFER_DOWN == synchTransfer) &&   // 下切换
        (!circulatingCurrentFlag)
       )
    {
        DriveControl.State = DOWN_TRANSFER_STATE; 
    }
    else
#endif
#if DEBUG_P_SPINNING_LOAD
    if (((TRUE == OutputProcess.SpinningLoadEnable) ||   // 转速跟踪
        (clControl)     // 闭环矢量默认进入飞车启动状态
        )
         &&  (coreMainCmd.bit.run)
       //  && ((motorControlMode != PMSM_SVC)&&(motorControlMode != PMSM_FVC))//同步机飞车启动不进飞车启动状态
        )
    {
        tmp = 0;
        DriveControl.State = SPINNING_LOAD_STATE;
        spinLoadStatus = 0;
    }
    else
#endif
    {
        coreStatus.bit.forbidAccDecSpd = 1;         // 禁止功能加减速

#if DEBUG_P_SM_CONTROL
        if (TRUE == smControl)  // 同步机控制
        {
            OutputProcess.SMFieldEnable = TRUE;
        }
#endif

#if DEBUG_P_PMSM_CONTROL
        if(((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
			&&(funcCode.code.motorParaM1.InitPosDetPulse != 0) && (fabs(pllBackEmfFrq) < (motorPara.ratingFrq * 1.0 * TWO_PI / 50.0)))
        {
        	DriveControl.State = ROTOR_INITIAL_STATE;
			flagPos = 0;
			interfaceRam[FPGA_REG_bypassCmd1] = 0x0110;
        }
		else
		{
        	DriveControl.State = MAGNETIZING_STATE;
		}
#else
        DriveControl.State = MAGNETIZING_STATE;
#endif
//        DriveControl.State = MAGNETIZING_STATE;

    }

    if (tmp)
    {
        coreRunStatus.bit.run = 1;
        OutputProcess.Enable = true; 
    }
    else
    {
        coreRunStatus.bit.run = 0;
        OutputProcess.Enable = FALSE;
    }
}


#define rotorInitDelayPeriod  2

//extern f32 deltaThetaRT;
extern u16 dataRdRTEncoder;
//==============================================================================
//
// 磁极初始位置识别状态处理
//
//==============================================================================
void RotorInitStatePmsm(void)
{
	//#if DEBUG_P_PMSM_CONTROL
	//if((PMSM_FVC == motorControlMode)||(PMSM_SVC == motorControlMode))
	if((PMSM_FVC == motorControlMode))
	{   
		if(cfGroup[13] == 1300)
		{
			rotorPosDelayTimer ++;
			if(rotorPosDelayTimer >= 1500)//3                                               
			{
		    	rotorPosDelayTimer = 1500;
				rotorObserverFinishFlag = 1;
//				inSpinFlag = 0;
//				rotorIntPositonRTComp = 0 - deltaThetaRT;//((f32)dataRdRTEncoder) /corePgPara.elem.encoderPole / 4096.0 * TWO_PI;
				Modulo2PI(&rotorIntPositonRTComp);
				DriveControl.State = MAGNETIZING_STATE;
				
			}
		}   
		else
		{
		    if(RotorPosPluseMethodFinish == 0)
		    {
			    if (RotorPositionPwmReg.bit.finishFlg == 1)
			    {
			        if (rotorInitDelayTimer++ >= rotorInitDelayPeriod)
			        {
			            OutputProcess.DeltaS = InitRotorPosition;
			            DriveControl.State = MAGNETIZING_STATE;
						hhhhpp = hhhhpp +1;
			            RotorPositionPwmReg.bit.state = 0;
			            RotorPositionPwmReg.bit.finishFlg = 0;
//						inSpinFlag = 0;
						rotorInitDelayTimer = 0;
						speedLoopSpinEnable = 1;
						RotorPosPluseMethodFinish = 1;
			        }
					return;
			    }
				if ((RotorPositionPwmReg.bit.state == 0)
			        && (coreErrorCode == 0)
			        && (TRUE == OutputProcess.ZeroSpeed) 
			        )
			    {
			        RotorPositionPwmReg.bit.state = 1;
			        rotorPositionSection = 0;
			        rotorInitDelayTimer = 0;
					speedLoopSpinEnable = 0;
			    }
		    }
			else
			{
				DriveControl.State = MAGNETIZING_STATE;
			}
		}
	}
	else
	{
		//DriveControl.State = MAGNETIZING_STATE;
		if(RotorPositionPwmReg.bit.finishFlg == 1)
		{
			//DriveControl.State = RUN_STATE;
		}
		if(coreErrorCode != 0)
		{
			//DriveControl.State = IDLE_STATE;
		}
	}
//#endif
}




extern f32 pllFluxSFrq;
void MagnetizingStateSm(void);


#define MAG_TICKER_MAX  1000        // 限制预励磁时间，在磁链斜坡时间基础上。_ms
f32 MAG_FRQ_HZ = 5.0;
//#define MAG_FRQ_HZ  5.0             // 预励磁期间同步频率低于__Hz清零
extern f32 SpeedReferenceCore2Fun;  // 与功能交互的频率
extern f32 magnetizingMaxVaule;
//==============================================================================
//
// 励磁状态处理
//
//==============================================================================
void MagnetizingState(void)
{
/*
#if DEBUG_P_SM_CONTROL
    if (smControl)
    {
        MagnetizingStateSm();
    }
    else
#endif
*/  
    
    if((dcBrakeenable == 0)||(PURE_VF == motorControlMode))
    {
        coreStatus.bit.forbidAccDecSpd = 1; // 预励磁期间禁止功能加减速

        SpeedReferenceCore2Fun = pllFluxSFrq;  // 预励磁期间，也给功能传递频率
        
		if(motorControlMode == IM_SVC4)
		{
			//SpeedReferenceCore2Fun = ImSvc4FluxRFrq;
		}
		

// 预励磁开启，静止飞车启动的处理
        if (SpinningLoad.Status == PLL_FREQUENCY_VALID)
        {
            magnetizingMaxVaule = 0.0;  
        }
        else if (fabs(SpinningLoad.SpeedReference) <= TWO_PI * MAG_FRQ_HZ * 1.1)
        {
            SpeedReferenceCore2Fun = 0.0;
            coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
            magnetizingMaxVaule = 0.03; 
        }
        else
        {
            magnetizingMaxVaule = 0.0;      // 有剩磁启动时防止过压
        }
        
        magTicker++;
        if (magTicker >= (MAG_TICKER_MAX + fluxCtrlMenu.fluxRampRate * 1000)/SLOW_LOOP_TIME_MS)  // 限制励磁步骤，最长时间_ms 
        {          
            DriveControl.State = RUN_STATE;
            coreStatus.bit.forbidAccDecSpd = 0;
            coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
        }
        else if ((TRUE == motorControlOtherEnable.bit.magnetize) 
				&& (PMSM_SVC != motorControlMode)//同步机设置A5-18，也不进行预励磁
				&& (PMSM_FVC != motorControlMode)
				)
        {
            if ((TRUE == CommandGenerator.FluxAtSetPoint)//达到励磁设定点，进入运行状态
                || (PURE_VF == motorControlMode) 
                )
            {
#if DEBUG_P_SPINNING_LOAD
                if (TRUE == OutputProcess.SpinningLoadEnable)
                {
        //            spinTicker++;
        //            if (spinTicker >= spinTickerMax)
                    {
                        coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
                        DriveControl.State = RUN_STATE;
                        coreStatus.bit.forbidAccDecSpd = 0;
                    }
                }
                else
#endif
                {
                    DriveControl.State = RUN_STATE;
                    coreStatus.bit.forbidAccDecSpd = 0; 
                    coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
                }
            }
        }
        else
        {	
        
        	if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))//同步机飞车启动
        	{
        		SpeedReferenceCore2Fun = pllBackEmfFrq;
        	}
			else//异步机飞车启动
			{
				SpeedReferenceCore2Fun = SpinningLoad.SpeedReference;
			}
			
			
            if(((SPINNING_LOAD_OFF != spinningLoadMenu.mode)) && 
				((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC)))
            {
            	if (magTicker >= 10)     // 预励磁关闭或者有剩磁时，启动延迟一拍
	            {                
	                speedLoopSpinEnable = 1;
	                DriveControl.State = RUN_STATE;
	                coreStatus.bit.forbidAccDecSpd = 0;
	                coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
	            }
            }
			else
			{
				if (magTicker >= 2)     // 预励磁关闭或者有剩磁时，启动延迟一拍
	            {                
	                speedLoopSpinEnable = 1;
	                DriveControl.State = RUN_STATE;
	                coreStatus.bit.forbidAccDecSpd = 0;
	                coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
	            }
			}

            

			/*
			SpeedReferenceCore2Fun = SpinningLoad.SpeedReference;

			if (magTicker >= 2)     // 预励磁关闭或者有剩磁时，启动延迟一拍
            {                
                speedLoopSpinEnable = 1;
                DriveControl.State = RUN_STATE;
                coreStatus.bit.forbidAccDecSpd = 0;
                coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
            }
			*/
        }
    }
	else
	{
        coreStatus.bit.forbidAccDecSpd = 1; // 预励磁期间禁止功能加减速
        SpeedReferenceCore2Fun = pllBackEmfFrq;  // 预励磁期间，也给功能传递频率
        magTicker++;
        if (magTicker >= (MAG_TICKER_MAX + dcBrakeTime * 1000)/SLOW_LOOP_TIME_MS)  // 限制励磁步骤，最长时间_ms 
        {          
            DriveControl.State = RUN_STATE;
            coreStatus.bit.forbidAccDecSpd = 0;
            coreStatus.bit.speedTrackEnd = 1;   // 转速跟踪完成
            dcBrakeStartflag = 0;
        }   
		else
		{
			dcBrakeStartflag = 1;
		}
	}

}



extern f32 coreFrqAimHzOld;
//==============================================================================
//
// 正常运行状态处理
//
//==============================================================================
void NormalRunState(void)
{
    coreStatus.bit.forbidAccDecSpd = 0;
    coreFrqAimHzOld = coreFrqAimHz;
    
#if DEBUG_P_SYNC_TRANSFER
    // 是否有up transfer请求
    if (SYNCH_TRANSFER_UP == synchTransfer)
    {
        DriveControl.State = UP_TRANSFER_STATE;
    }
#endif
}



//==============================================================================
//
// 自由停车处理
//
//==============================================================================
void CoastState(void)
{
    coreRunStatus.bit.run = 0;
    OutputProcess.Enable = FALSE;
    DriveControl.State = IDLE_STATE;
}



#if DEBUG_P_SYNC_TRANSFER
//==============================================================================
//
// 上切换(变频切工频)处理
//
//==============================================================================
void UpTransferState(void)
{
    if (SYNCH_TRANSFER_UP != synchTransfer)
    {
        DriveControl.State = RUN_STATE;
    }
}



//==============================================================================
//
// 下切换(工频切变频)处理
//
//==============================================================================
void DownTransferState(void)
{
    if (SYNCH_TRANSFER_DOWN != synchTransfer)
    {
        DriveControl.State = RUN_STATE;
    }
}

#endif









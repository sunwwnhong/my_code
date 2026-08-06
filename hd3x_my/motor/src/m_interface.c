//==================================================================================================
//
// 交互
// 功能与性能的接口(ARM与DSP的交互)；
// DSP与FPGA的交互
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_interface.h"
#include "m_main.h"
#include "m_input.h"
#include "m_autoTune.h"
#include "m_cell.h"
#include "m_cell_bypass.h"
#include "m_frqSrc.h"
#include "m_error.h"
#include "m_spinningLoad.h"
#include "m_transfer.h"
#include "m_brake.h"
#include "m_fluxLoop.h"
#include "m_macro_tune.h"
#include "m_macro_AO.h"
#include "m_macro_transfer.h"
#include "m_macro_sm.h"
#include "m_macro_loadSharing.h"
#include "m_macro_lowFrq.h"
#include "m_torqueDebugCalc.h"

//------串口PC后台观测---------
#include "Debug.h"
#include "SimpleDebug.h"
#include "m_speedLoop.h"
#include "m_accDecDeal.h"
//-----------------------------

#include "funcRunSrc.h"

#include "funcErrorFlag.h"

#include "m_blackBoxDeal.h"


// DSP软件版本号
#if (INV_MODEL == INV_3300)
#define CORE_SOFT_VERSION          13911
#else
#define CORE_SOFT_VERSION          11004
#endif



#define LIMIT_PWM_OPEN_TIME         1       // 0，不限制时间；1-限制开PWM的时间
//#define LIMIT_PWM_OPEN_TIME         0       // 0，不限制时间；1-限制开PWM的时间



#if LIMIT_PWM_OPEN_TIME
u32 enableTicker;
#endif




#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
#pragma CODE_SECTION(UpdateDataCore2Fpga,     "ramfuncs");
#endif
//#pragma DATA_SECTION(sampleD, "data_ram");  // 放入M1中
//#pragma DATA_SECTION(blackBoxGroupAddr, "data_ram");    // 加入黑匣子数据，data_ram放不下了
#if DEBUG_PRG_IN_RAM
//#pragma DATA_SECTION(ceGroup, "data_ram");
//#pragma DATA_SECTION(cfGroup, "data_ram");
//#pragma DATA_SECTION(cellOffsetRegMirror, "data_ram");
#endif


// FPGA看门狗
#define FPGA_WATCHDOG_CMD_ENABLE    0xA5A5
#define FPGA_WATCHDOG_CMD_RESET     0x5A5A
#define FPGA_WATCHDOG_CMD_DISABLE   0x5AA5




extern int16 coreFrqAim;
extern f32 coreUpperTorque;
extern f32 upperTorqueRegen;
extern Uint16 coreTuneCmd;
extern int32 frqMotorRun;
extern int32 frqMotorRun1;
extern f32 iTotalInvDis;
extern f32 iuDisFil; //u相输出电流显示
extern f32 ivDisFil; //v相输出电流显示
extern f32 iwDisFil; //w相输出电流显示
extern f32 iqRef;
extern f32 iqRefMaster;
extern f32 windowWidth;
extern f32 motorRunMaster;
f32 motorRunMasterPu;
f32 offTransitoryKp;        // F9-38 瞬停不停Kp
f32 offTransitoryKi;        // F9-39 瞬停不停Ki
extern f32 zeroSpeedSet;
extern Uint16 coreMaxFrq;
f32 coreMaxFrqRads;
extern f32 pllBackEmfFrq;
f32 cellOverloadLevel;

extern u16 circulatingCurrentFlag;

extern struct InputProcessType InputProcess;

Uint16 coreCarrierFrq = 7000;      // F0-15的值，单位0.1Hz
Uint16 vfSeparateVol;       // 12   VF分离时的输出电压
Uint16 vfCurve;             // 13   VF曲线选择




extern struct DA_DATA aoData;




extern union AUTO_TUNE_PARA autoTunePara;    // 调谐参数
extern struct REGULATOR_STR npcPi;





extern f32 deadTimeComp;

extern f32 curLoopFeedForwardGain;

extern f32 dropFrq;

Uint16 invIOCSetpoint;       // 35 FA-30 过流点设定




// 这里使用了static，限制 f2cData, c2fData 的scope
// f2cData仅允许在ReadRamData(), ReadRamAData(), ReadRamBData() 中使用
// f2cData.code.slowData.codeA.xxx，仅允许在ReadRamAData()函数中使用
// f2cData.code.slowData.codeB.xxx，仅允许在ReadRamBData()函数中使用
// c2fData仅允许在WriteRamData()中使用
union FUNC_TO_CORE_DATA f2cData;   // 仅在二者交互时使用
union CORE_TO_FUNC_DATA c2fData;

void RcvDataFunc2Core(void);
void SendDataCore2Func(void);

void ReadRamData(void);
void ReadRamAData(void);
void ReadRamBData(void);
void WriteRamData(void);

void RamOkJudge(void);

void FCErrLedDeal(void);

// DSP与FPGA交互RAM，分成三部分
// 0-511,     共DSP_W_LEN(512)，为 DSP写,ARM读。其中前 AUTO_TUNE_PARA_LEN 长度为 (调谐数据autoTunePara)
// 512-1023,  共DSP_R_LEN(512)，为 DSP读,ARM写。
// 1024-2023，共FPGA_REG_LEN(1000)，为 DSP与FPGA 之间的交互register
#pragma DATA_SECTION(interfaceRam, "ZONE7_RAM");
volatile Uint16 interfaceRam[DSP_W_LEN+DSP_R_LEN+FPGA_REG_LEN];

#define F2C_MSG_FLAG_ADDR (DSP_R_ADDR + FUNC_TO_CORE_DATA_LEN - 3)
#define C2F_MSG_FLAG_ADDR (DSP_W_ADDR + CORE_TO_FUNC_DATA_LEN - 3)

enum RAM_STATUS ramStatus;

Uint16 dataFuncToCoreRsvd;
Uint16 dataCoreToFuncRsvd;


Uint16 ceGroup[F2C_TEST_PARA_LEN];
Uint16 cfGroup[F2C_DEBUG_PARA_LEN];


#if DEBUG_BLACK_BOX // LS_20221205
f32 sampleD[6][12];
Uint16  blackBoxGroupAddr[F2C_BLACK_BOX_PARA_LENTH];
extern Uint16 blackBoxDataTicker;       // 每2ms记录的快环数据个数
#endif


//Uint32 f2cCrcErrTickerSingle;       // 单次，无错误时清零
//Uint16 f2cCrcErrTickerContinuous;   // 连续累加，无错误时不清零

//Uint16 f2cNoRcvTickerSingle;        // 单次，无错误时清零
//Uint16 f2cNoRcvTickerContinuous;    // 连续累加，无错误时不清零

//Uint16 rcvOkTicker;                 // DSP接收到ARM的数据，且CRC正确

extern u16 tickerDspDeal;
//==============================================================================
//
// 接收功能传递给性能的数据
//
//==============================================================================
void RcvDataFunc2Core(void)
{
    ReadRamData();
   // FCErrLedDeal();
}



// 功能性能交互的故障LED处理
// CRC错误，亮，正常0.5s(FC_LED_CRC_ERR_TIME)后熄灭
// CRC正确，但没有成功交互(ARM未更新程序)，闪烁，正常0.5s(FC_LED_NO_RCV_ERR_TIME)后熄灭

#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中 
//u16 fCLedCrcErr;    //
//u16 fCLedCrcErrTicker;

//u16 fCLedNoRcvErr;
//u16 fCLedNoRcvErrTicker;
//u16 fCLedWinkTicker;

#define FC_LED_CRC_ERR_TIME     1000     // _ms
#define FC_LED_NO_RCV_ERR_TIME  2000     //_ms

#define FC_LED_NO_RCV_ERR_TICKER_MAX    2

//==============================================================================
//
// 功能、性能交互错误的LED灯指示处理
//
//==============================================================================
/*
void FCErrLedDeal(void)
{
// CRC错误，亮，正常0.5s(FC_LED_CRC_ERR_TIME)后熄灭
	if (fCLedCrcErrTicker < FC_LED_CRC_ERR_TIME * I_MAIN_LOOP_TIME_MS)
    {
        fCLedCrcErrTicker++;
    }
	else
	{
        fCLedCrcErrTicker = 0;
	}
	if (fCLedCrcErrTicker >= 250 )
    {
        LED_DSP_ERROR_ON;
    }
	else
	{
       LED_DSP_ERROR_OFF;
	}

// CRC正确，但没有成功交互(ARM未更新程序)，闪烁，正常0.5s(FC_LED_NO_RCV_ERR_TIME)后熄灭
    if (f2cNoRcvTickerSingle >= FC_LED_NO_RCV_ERR_TICKER_MAX)
    {
        fCLedNoRcvErr = 1;
        fCLedNoRcvErrTicker = 0;
    }
    else
    {
        fCLedNoRcvErrTicker++;
        if (fCLedNoRcvErrTicker >= FC_LED_NO_RCV_ERR_TIME * I_MAIN_LOOP_TIME_MS)
        {
            fCLedNoRcvErr = 0;

            fCLedWinkTicker = 0;
        }
    }
    if (fCLedCrcErr)
    {
        fCLedNoRcvErr = 0;
        fCLedNoRcvErrTicker = 0;
        fCLedWinkTicker = 0;
    }

#define FC_LED_WINK_ON_TIME     50
#define FC_LED_WINK_OFF_TIME    50
    if (fCLedCrcErr)
    {
        LED_DSP_ERROR_ON;
    }
    else if (fCLedNoRcvErr)
    {
        fCLedWinkTicker++;
        if (fCLedWinkTicker < FC_LED_WINK_ON_TIME * I_MAIN_LOOP_TIME_MS)
        {
            LED_DSP_ERROR_ON;
        }
        else if (fCLedWinkTicker < (FC_LED_WINK_ON_TIME+FC_LED_WINK_OFF_TIME) * I_MAIN_LOOP_TIME_MS)
        {
            LED_DSP_ERROR_OFF;
        }
        else
        {
            fCLedWinkTicker = 0;
        }
    }
    else
    {
        LED_DSP_ERROR_OFF;
    }

}
*/
#elif 1                 // 程序放在RAM中调试
/*
void FCErrLedDeal(void)
{
    if (f2cCrcErrTickerSingle || f2cNoRcvTickerSingle)
    {
        LED_DSP_ERROR_ON;
    }
    else
    {
        LED_DSP_ERROR_OFF;
    }
}
*/
#endif



//==============================================================================
//
// 性能传递给功能的数据传递
//
//==============================================================================
void SendDataCore2Func(void)
{

    WriteRamData(); 
  //  interfaceRam[FPGA_REG_reset_watchdog] = FPGA_WATCHDOG_CMD_RESET;    // 复位FPGA看门狗
}



//==============================================================================
//
// 功能、性能的交互RAM，性能是否能读取
//
//==============================================================================
/*
void RamOkJudge(void)
{
    if (!FPGA_OK)
    {
        ramStatus = RAM_STATUS_WAIT_FPGA; 
    }
    else if (RAM_STATUS_WAIT_FPGA == ramStatus)
    {
        ramStatus = RAM_STATUS_FIRST;
    }
    else
    {
        if (!RAM_ARM_BUSY)
        {
            // 在操作RAM之前，把BUSY置高。需要提前几个周期，否则可能在操作一次RAM后，BUSY才为高
            // "if (RAM_STATUS_FIRST == ramStatus)"也有几个周期 
            NOP10;

            if (RAM_STATUS_FIRST == ramStatus)
            {
                // 保证FPGA OK后的第一次，RAM标志空闲后，DSP一定会读全部数据
                f2cData.code.flag = interfaceRam[F2C_MSG_FLAG_ADDR] - 10;
            }

            ramStatus = RAM_STATUS_RW;
        }
        else
        {
            ramStatus = RAM_STATUS_JUDGE_BUSY;
        }
    }
}
*/





extern u16 motorControlMode;
#define DPRAM_NUM   16      // memcpy()函数一次的个数。60MHz下，16个，时间接近2us


f32 outPhaseNoBalanceSet;    // 输出电流不平衡 F9-15
u16 errorProtectOtherEnable1;// F9-72 附加功能选择1
extern f32 fluxCompLimit;                       // 磁链观测补偿限幅
extern f32 fluxLoopCloseFrq;                    // 磁链闭环频率
extern f32 fluxOpenIdRef;                       // 磁链开环时励磁电流给定
extern f32 fluxLoopFeedForwardGain;
extern f32 motorTripVoltage;
extern u32 cellBypassMechCmd;         
//extern f32 outputGroundFaultLimit;
//extern f32 outputGroundFaultGainR;
extern f32 inputvolimbalanceLimit;
extern f32 outputvolimbalanceLimit;
extern s16 transformerOLMode;
extern s16 sampleAbnomityEnable;               // 采样异常使能开关: 0 禁止；1 开启
extern s16 sampleSequenceEnable;
extern u32 cellBypassCmd;
extern u16 decVolDealEnable;
extern f32 regDecTime;
extern u16 masterOrSlave;
//extern u16 netContactorAcknowledge;
//extern u16 invContactorAcknowledge;
//u16 iNoloadTmp;
extern f32 gfd;

extern f32 midMax;
extern f32 udcMax;        
extern f32 udcHalfoverMax;  
extern f32 udcOverHalfLimit;   
extern f32 udcOverVolLimit; 
extern f32 midMax; 


//==============================================================================
//
// 读取功能传递的数据，仅读取数据
//
//==============================================================================
void ReadRamData(void)
{

// 拷贝至实际使用的变量
    coreMainCmd.all                     = f2cData.code.mainCmd;
    coreFrq                             = f2cData.code.frq2Core;
    coreMainCmd1.all                    = f2cData.code.mainCmd1;
    coreSubCmd.all                      = f2cData.code.subCmd;
    coreTuneCmd                         = f2cData.code.tuneCmd;
    
//    vfSeparateVol                       = f2cData.code.vfSeparateVol;
//    vfCurve                             = f2cData.code.vfCurve;


#if 1    
    iqRefMaster                         = (f32)(s16)f2cData.code.masterTorque * (1.0/1000);
    motorRunMaster                      = (f32)(((int32)(int16)f2cData.code.masterSpeedMotor * (coreMaxFrq + 2000) + (1L << 14)) >> 15) * (1.0/100);
    motorRunMasterPu = motorRunMaster * TWO_PI * motorPara.iFPuOmegaOne;
#endif


    if (!coreMainCmd.bit.codeAB)    // 0-codeA
    { 
        ReadRamAData();
    }
    else                            // 1-codeB
    { 
        ReadRamBData();
    }
    
//    netContactorAcknowledge = coreSubCmd.bit.netContactorFdb;
//    invContactorAcknowledge = coreSubCmd.bit.invContactorFdb;
}


//f32 LowCarfrq = 700;
u16 brakeEnable;
f32 brakeFpRef;
u16 hwCellFlag;     // 1-大样机，0-小样机(包括全功能小样机和非全功能小样机)
extern f32 newCarrierFrq;
extern f32 overVolInhibitKp, overVolInhibitKi;
u16 newCarrierFrqtimes = 0;

extern void LCDataDeal(void);
//==============================================================================
//
// 读取功能传递的数据，仅读取A数据
// f2cData.code.slowData.codeA.xxx，仅允许在ReadRamAData()函数中使用
//
//==============================================================================
void ReadRamAData(void)
{
    f32 tmp;
    f32 tmp1;
    f32 newCarrierFrqtmp;
	//整流侧发波方式，放到这里和FPGA交互
	if(cellMenu.cellVoltage != 3)
	{	//逆变是之前的发波方式
		interfaceRam[FPGA_REG_Fb_rect_Flag] = 0;
	}
	else
	{	//整流根据参数确定发波方式
		interfaceRam[FPGA_REG_Fb_rect_Flag] = funcCode.code.AfeMode;
	}
	
    coreUpperTorque     = f2cData.code.slowData.codeA.upperTorque * (1.0/1000);
//    coreUpperTorque     = f2cData.code.slowData.codeA.upperTorque * (2.0/1000);
    coreFrqAim          = f2cData.code.slowData.codeA.frqCurAim2Core;

// 三电平时，由于FPGA发波的原因，这里需要除以2。
#if (INV_TYPE == HW_HD90)
    if ((CELL_TYPE_690 == cellMenu.cellVoltage) ||
        (CELL_TYPE_690_DURIAN == cellMenu.cellVoltage)
        )
    {
        coreCarrierFrq  = f2cData.code.slowData.codeA.carrierFrq;
    }
    else //if (CELL_TYPE_AFE_1140 == cellMenu.cellVoltage)      // HD92，需要除以2
    {
        coreCarrierFrq  = f2cData.code.slowData.codeA.carrierFrq * 0.5;
    }

    cellCheckFlag.all   = f2cData.code.slowData.codeA.cellCheckFlag;
    
#elif (INV_TYPE == HW_HD3x)                                     // HD3x

#if (2 != FPGA_PWM_VER)
    coreCarrierFrq = f2cData.code.slowData.codeA.carrierFrq * gfd;
#elif 1
    newCarrierFrqtmp = f2cData.code.slowData.codeA.carrierFrq * (1.0/10);
   // if((motorControlMode == PMSM_SVC)&&(DriveControl.State != AUTO_TUNE_STATE))
#if(0)

	if(fabs(CommandGenerator.SpeedReference)<= (100.0))
	{
		newCarrierFrq	= 700;
	}
	else 
	//if(fabs(CommandGenerator.SpeedReference) >= (200))
	{
		newCarrierFrq = f2cData.code.slowData.codeA.carrierFrq * (1.0/10);
	}
	//else
	//{
	//	newCarrierFrq = (newCarrierFrqtmp - LowCarfrq)/(20.0 * TWO_PI)
	//		             * (fabs(CommandGenerator.SpeedReference) - 15.0 * TWO_PI) + LowCarfrq;

	//}

#else
	{
		newCarrierFrq = newCarrierFrqtmp;
		
		#if (INV_MODEL == INV_3300)
		
		newCarrierFrqtimes++;
		if(newCarrierFrqtimes > 10)//不加这个会导致芯片异常
		{
            newCarrierFrqtimes = 10;

			
			 	 if(fabs(CommandGenerator.SpeedReference) <= (3.0*TWO_PI))
                {
                    newCarrierFrq   = 500;//500  原来的值
                    //荣信启动载波频率改成700
                }
                else if(fabs(CommandGenerator.SpeedReference) >= (TWO_PI*5.0))
                {
                    newCarrierFrq = f2cData.code.slowData.codeA.carrierFrq * (1.0/10);
                }
                else
                {
                    newCarrierFrq = (newCarrierFrqtmp - 500)/(2.0 * TWO_PI)
                                     * (fabs(CommandGenerator.SpeedReference) - 3.0*TWO_PI) + 500;
                }

            //if(AUTO_TUNE_STATE != DriveControl.State)
            {
            	/*
                if(fabs(CommandGenerator.SpeedReference) <= (3.0*TWO_PI))
                {
                    newCarrierFrq   = 500;//500  原来的值
                    //荣信启动载波频率改成700
                }
                else if(fabs(CommandGenerator.SpeedReference) >= (TWO_PI*5.0))
                {
                    newCarrierFrq = f2cData.code.slowData.codeA.carrierFrq * (1.0/10);
                }
                else
                {
                    newCarrierFrq = (newCarrierFrqtmp - 300)/(2.0 * TWO_PI)
                                     * (fabs(CommandGenerator.SpeedReference) - 3.0*TWO_PI) + 300;
                }
				 */
                //荣信3300 500Hz载频启动锁相不对
				 //newCarrierFrq = f2cData.code.slowData.codeA.carrierFrq * (1.0/10);
            }
        }
		#endif
	}
#endif
#endif

#endif
    if ((newCarrierFrq == 0))//||(coreCarrierFrq == 0))
    {
    	newCarrierFrq = 700;
    	coreCarrierFrq = 7000;
    }

    coreMaxFrq          = f2cData.code.slowData.codeA.maxFrq;
    upperTorqueRegen    = f2cData.code.slowData.codeA.upperTorqueRegen * (-1.0/1000);
//    dataFuncToCoreRsvd  = f2cData.code.slowData.codeA.curSampleDelayComp;
    motorTripVoltage    = f2cData.code.slowData.codeA.motorTripVoltage * (1.0/1000); 

    invIOCSetpoint      = f2cData.code.slowData.codeA.invIOCSetpoint;
    cellOverloadLevel   = f2cData.code.slowData.codeA.invCurrentLimit * (1.0/1000);
    cellOverloadLevel   = 1.0;
    zeroSpeedSet        = f2cData.code.slowData.codeA.zeroSpeed * (1.0/1000);
    deadTimeComp        = f2cData.code.slowData.codeA.DeadTimeComp * (1.0/10);

#if CELL_BYPASS
    cellBypassCmd       = f2cData.code.slowData.codeA.cellBypassCmdArmL + ((u32)f2cData.code.slowData.codeA.cellBypassCmdArmH << 16);
#endif


//    spinningLoadMenu.mode                   = f2cData.code.spinningLoadPara[0];
    spinningLoadMenu.mode                   = coreMainCmd1.bit.speedTrack;
#if DEBUG_P_SPINNING_LOAD
    spinningLoadMenu.currentLevel           = f2cData.code.slowData.codeA.spinningLoadPara[0] * (1.0/1000); 
    spinningLoadMenu.speedRampRate          = f2cData.code.slowData.codeA.spinningLoadPara[1] * (1.0/100);  // 
    spinningLoadMenu.threshold              = f2cData.code.slowData.codeA.spinningLoadPara[2] * (1.0/1000);
    spinningLoadMenu.currentRampRate        = 0.05;     // 电流斜坡时间修改。
    spinningLoadMenu.maximumCurrent         = 0.6;      // 最大电流修改。
#endif

#if DEBUG_P_SYNC_TRANSFER
    syncTransferMenu.phaseKp                = f2cData.code.slowData.codeA.SyncTransferMenu[0] * (1.0/10);
    syncTransferMenu.phaseKi                = f2cData.code.slowData.codeA.SyncTransferMenu[1] * (1.0/10);
    syncTransferMenu.phaseOffset            = (f32)(int16)f2cData.code.slowData.codeA.SyncTransferMenu[2] * (1.0/10);
    syncTransferMenu.phaseErrorThreshold    = f2cData.code.slowData.codeA.SyncTransferMenu[3] * (1.0/10);
    syncTransferMenu.frqErrorThreshold      = f2cData.code.slowData.codeA.SyncTransferMenu[4] * (1.0/10);
    syncTransferMenu.transferTimeout        = f2cData.code.slowData.codeA.SyncTransferMenu[5] * (1.0/10);
//    syncTransferMenu.downTransferTimeout    = f2cData.code.SyncTransferMenu[6] * (1.0/10);
#endif

    motorPara.motorType       = f2cData.code.slowData.codeA.motorParaArm.motorType;
    motorPara.ratingPower     = f2cData.code.slowData.codeA.motorParaArm.ratingPower;
    motorPara.ratingVoltage   = f2cData.code.slowData.codeA.motorParaArm.ratingVoltage;
    motorPara.ratingCurrent   = f2cData.code.slowData.codeA.motorParaArm.ratingCurrent * (1.0 / 10);
    motorPara.ratingFrq       = f2cData.code.slowData.codeA.motorParaArm.ratingFrq * (1.0 / 100);
    motorPara.ratingSpeed     = f2cData.code.slowData.codeA.motorParaArm.ratingSpeed; 
    motorPara.rs              = f2cData.code.slowData.codeA.motorParaArm.statorResistance * (1.0 / 10000);
    motorPara.rr              = f2cData.code.slowData.codeA.rotorResistance * (1.0 / 10000);
    //motorPara.rr              = f2cData.code.motorParaArm.rotorResistance  * (1.0 / 10000);
    motorPara.lSigma          = f2cData.code.slowData.codeA.motorParaArm.leakInductance   * (1.0 / 10000);
//    motorPara.lm              = f2cData.code.motorParaArm.mutualInductance * (1.0 / 10000);
 //   iNoloadTmp                = f2cData.code.slowData.codeA.motorParaArm.zeroLoadCurrent;
  //  motorPara.iNoload         = iNoloadTmp  * (1.0 / 10000);
    motorPara.iNoload         = f2cData.code.slowData.codeA.motorParaArm.zeroLoadCurrent* (1.0 / 10000);
	motorPara.IfModeRefCur    = f2cData.code.slowData.codeA.IfModeRefCur* (1.0 / 10000);
	motorPara.PMLowSpdIdAddCur= f2cData.code.slowData.codeA.PMLowSpdIdAddCur* (1.0 / 10000);
    motorPara.smRs            = f2cData.code.slowData.codeA.motorParaArm.pmsmRs           * (1.0 / 10000);
    motorPara.smLd            = f2cData.code.slowData.codeA.motorParaArm.pmsmLd           * (1.0 / 10000);
    motorPara.smLq            = f2cData.code.slowData.codeA.motorParaArm.pmsmLq           * (1.0 / 10000);
    motorPara.smCoeff         = f2cData.code.slowData.codeA.motorParaArm.pmsmCoeff        * (1.0 / 10000);
    motorPara.inertia         = f2cData.code.slowData.codeA.motorParaArm.inertia;

    memcpy(&corePgPara.all[0], &f2cData.code.slowData.codeA.pgPara.all[0], PG_PARA_LEN);

    speedLoopMenu.speedRegPropLowFrq    = f2cData.code.slowData.codeA.SpeedLoopMenu[0] * (1.0/1000);
    speedLoopMenu.speedRegIntegLowFrq   = f2cData.code.slowData.codeA.SpeedLoopMenu[1] * (1.0/1000);
    speedLoopMenu.speedParaFrqLow       = f2cData.code.slowData.codeA.SpeedLoopMenu[2] * (1.0/100) * TWO_PI;
    speedLoopMenu.speedRegProp          = f2cData.code.slowData.codeA.SpeedLoopMenu[3] * (1.0/1000);
    speedLoopMenu.speedRegInteg         = f2cData.code.slowData.codeA.SpeedLoopMenu[4] * (1.0/1000);
    speedLoopMenu.speedParaFrqHigh      = f2cData.code.slowData.codeA.SpeedLoopMenu[5] * (1.0/100) * TWO_PI;
    speedLoopMenu.speedRegKf            = f2cData.code.slowData.codeA.SpeedLoopMenu[8] * (1.0/100);
  //  speedLoopMenu.speedFilterTimeConstant   = f2cData.code.slowData.codeA.SpeedLoopMenu[3] * (1.0/10000);

    
    tmp  = f2cData.code.slowData.codeA.CurrentLoopMenu[0] * (1.0/100);
    tmp1 = f2cData.code.slowData.codeA.CurrentLoopMenu[1] * (1.0/10);
    
#if DEBUG_P_SYNC_TRANSFER
//    if (WAITING_FOR_CONTACTOR_CLOSURE <= SynchTransfer.UpTransferState)
 //   {
 //       tmp = tmp * 0.3;
 //       tmp1 = tmp1 * 0.3;
 //   }
  //  else if ((SYNCH_TRANSFER_DOWN == synchTransfer) && (!circulatingCurrentFlag))
 //   {
 //       tmp = tmp * 0.2;    //zhangyuan
 //       tmp1 = tmp1 * 0.2;
 //   }
#endif

    // 有输出滤波器时，电流环参数需要限制
    if (OutputProcess.DoFilterComp)
    {
        tmp  = GetMin(tmp,  0.30);  // 限制为_
        tmp1 = GetMin(tmp1, 30.0);
    }
    currentLoopMenu.currentRegProp  = tmp;
    currentLoopMenu.currentRegInteg = tmp1;
    
#if DEBUG_P_DUAL_FRQ_BRAKE || DEBUG_P_AUTO_TUNE
    currentLoopMenu.currentRegPropBraking   = f2cData.code.slowData.codeA.CurrentLoopMenu[2] * (1.0/100);
    currentLoopMenu.currentRegIntegBraking  = f2cData.code.slowData.codeA.CurrentLoopMenu[3] * (1.0/10);
#endif

    fluxStatorObserverMenu.lowFrqWo         = f2cData.code.slowData.codeA.LowFrequencyCompensationMenu[0] * (1.0/1000);
    fluxStatorObserverMenu.lowFrqComGain    = f2cData.code.slowData.codeA.LowFrequencyCompensationMenu[1] * (1.0/10); 
    fluxStatorObserverMenu.swCompensatorPole= f2cData.code.slowData.codeA.LowFrequencyCompensationMenu[2] * (1.0/10);

    fluxCtrlMenu.fluxRegPropGain            = f2cData.code.slowData.codeA.FluxContrlMenu[0] * (1.0/100);
    fluxCtrlMenu.fluxIntegralGain           = f2cData.code.slowData.codeA.FluxContrlMenu[1] * (1.0/10);
    fluxCtrlMenu.fluxFilterTime             = f2cData.code.slowData.codeA.FluxContrlMenu[2] * (1.0/10000);
    fluxCtrlMenu.fluxDemand                 = f2cData.code.slowData.codeA.FluxContrlMenu[3] * (1.0/1000);
    fluxCtrlMenu.fluxRampRate               = f2cData.code.slowData.codeA.FluxContrlMenu[4] * (1.0/10);
//    fluxCtrlMenu.energySaverMinFlux         = f2cData.code.FluxContrlMenu[5] * (1.0/10);
//    fluxCtrlMenu.idsDC                      = f2cData.code.FluxContrlMenu[6] * (1.0/1000);
//    fluxCtrlMenu.fluxDroop                  = f2cData.code.FluxContrlMenu[7] * (1.0/100);

//    motorOlProtect.enable       = f2cData.code.overLoadPara[0];
    motorOlProtect.enable       = coreSubCmd.bit.overloadMode;
    motorOlProtect.time         = (f32)f2cData.code.slowData.codeA.overLoadPara[0] * (1.0/10);
    motorOlProtect.predictCoef  = (f32)f2cData.code.slowData.codeA.overLoadPara[1] * (1.0/100);
    motorOlProtect.olCoef       = f2cData.code.slowData.codeA.overLoadPara[2] * (1.0/1000);
//    motorOlProtect.olCoef       = (f32)f2cData.code.motorOverloadCoef * (1.0/1000);                                    

    cellMenu.installedCellsPerPhase     = f2cData.code.slowData.codeA.CellMenu[0];
    cellMenu.minCells                   = f2cData.code.slowData.codeA.CellMenu[1];
    cellMenu.cellVoltage                = f2cData.code.slowData.codeA.CellMenu[2];
#if CELL_BYPASS
//    cellMenu.thermistorWarnLevel        = f2cData.code.CellMenu[3];
    cellMenu.maxEMFDecayTime            = f2cData.code.slowData.codeA.CellMenu[3] * (1.0/10);
//    cellMenu.thermistorWarnLevel        = 200; // 此处替代上面功能码，功能码调整 验证。 是不是永远不报警 过温。
//    cellMenu.contactorSettlingTime      = f2cData.code.CellMenu[4];
//    cellMenu.bypassEnable               = f2cData.code.CellMenu[6];
#endif

    inputProtectMenu.phaseImbalanceLimit    = f2cData.code.slowData.codeA.protectMenu[0] * (1.0/1000);      // F9-14
    outPhaseNoBalanceSet                    = (f32)f2cData.code.slowData.codeA.protectMenu[1] * (1.0/1000); // F9-15
    inputProtectMenu.groundFaultLimit       = f2cData.code.slowData.codeA.protectMenu[2] * (1.0/1000);      // F9-16
#if !DEBUG_PRG_IN_RAM
    inputvolimbalanceLimit                  = f2cData.code.slowData.codeA.protectMenu[3] * (1.0/1000);      // F9-17
    inputProtectMenu.undervoltageKp         = f2cData.code.slowData.codeA.protectMenu[4] * (1.0/10);        // F9-18
    inputProtectMenu.undervoltageKi         = f2cData.code.slowData.codeA.protectMenu[5] * (1.0/1000);      // F9-19   
    inputProtectMenu.oneCycleProtectKi      = f2cData.code.slowData.codeA.protectMenu[6] * (1.0/10000);     // F9-20
    inputProtectMenu.oneCycleProtectLimit   = f2cData.code.slowData.codeA.protectMenu[7] * (1.0/1000);      // F9-21
    inputProtectMenu.excessLossIdle         = f2cData.code.slowData.codeA.protectMenu[8] * (1.0/100);       // F9-22
    inputProtectMenu.excessLossRunning      = f2cData.code.slowData.codeA.protectMenu[9] * (1.0/100);       // F9-23
    inputProtectMenu.xformerTapSetting      = f2cData.code.slowData.codeA.protectMenu[10];                  // F9-24
    inputProtectMenu.xformerThermalGain     = f2cData.code.slowData.codeA.protectMenu[11] * (1.0/10000);    // F9-25
    inputProtectMenu.xformerProtectK        = f2cData.code.slowData.codeA.protectMenu[12] * (1.0/10);       // F9-26
    outputvolimbalanceLimit                 = f2cData.code.slowData.codeA.protectMenu[13] * (1.0/1000);     // F9-27
    //outputGroundFaultLimit                  = f2cData.code.slowData.codeA.protectMenu[14] * (1.0/1000);     // F9-28
    offTransitoryKp                         = f2cData.code.slowData.codeA.offTransitoryMenu[0] * (1.0/1000);// F9-38
    offTransitoryKi                         = f2cData.code.slowData.codeA.offTransitoryMenu[1] * (1.0/1000);// F9-39
    
#define outputGroundFaultTime   0.017
 //   outputGroundFaultGainR                  = OutputProcess.FastLoopSamplePeriod * (1.0/outputGroundFaultTime);
#endif

#if DEBUG_P_DUAL_FRQ_BRAKE
    brakeEnable                             = coreSubCmd.bit.dualFrqBrakeEnable;                        // F6-11 叠频制动使能
    dualFrqBrake.pLoss                      = f2cData.code.slowData.codeA.BrakingMenu[1] * (1.0/10000); // F6-13 叠频制动功率损耗
    dualFrqBrake.vdLossMax                  = f2cData.code.slowData.codeA.BrakingMenu[2] * (1.0/100);   // F6-14 叠频制动d轴电压损耗
    dualFrqBrake.brakingK                   = f2cData.code.slowData.codeA.BrakingMenu[3] * (1.0/100);   // F6-15 叠频制动常数
#endif
// 即使叠频制动不使能，dualFrqBrake.superposeFrq也需要的。
    brakeFpRef                              = f2cData.code.slowData.codeA.BrakingMenu[0] * (1.0/10);    // F6-12 叠频制动叠加频率
    tmp = OutputProcess.FastLoopFrequency / brakeFpRef + 0.5;
    dualFrqBrake.superposeFrq = (OutputProcess.FastLoopFrequency / (u16)tmp) * TWO_PI;

#if 0
    ctrlLoopTestMenu.testType               = f2cData.code.ControlLoopTestMenu[0];
    ctrlLoopTestMenu.testPointPositive      = f2cData.code.ControlLoopTestMenu[1] * (1.0/1000);
    ctrlLoopTestMenu.testPointNegative      = f2cData.code.ControlLoopTestMenu[2] * (1.0/1000);
    ctrlLoopTestMenu.testTime               = f2cData.code.ControlLoopTestMenu[3] * (1.0/10);
    ctrlLoopTestMenu.enable                 = f2cData.code.ControlLoopTestMenu[4];
#endif

    driveSampleMenu.inVolReviseCoef  = f2cData.code.slowData.codeA.VolCurSampleMenu[0] * (1.0/1000);
    driveSampleMenu.inCurReviseCoef  = f2cData.code.slowData.codeA.VolCurSampleMenu[1] * (1.0/1000);
    driveSampleMenu.outVolReviseCoef = f2cData.code.slowData.codeA.VolCurSampleMenu[2] * (1.0/1000);
    driveSampleMenu.outCurReviseCoef = f2cData.code.slowData.codeA.VolCurSampleMenu[3] * (1.0/1000);
    driveSampleMenu.inVolResOhm      = f2cData.code.slowData.codeA.VolCurSampleMenu[4];
    driveSampleMenu.inCTRatio        = f2cData.code.slowData.codeA.VolCurSampleMenu[5];
    driveSampleMenu.inCurResOhm      = f2cData.code.slowData.codeA.VolCurSampleMenu[6] * (1.0/100);
    driveSampleMenu.outVolResOhm     = f2cData.code.slowData.codeA.VolCurSampleMenu[7];
    driveSampleMenu.outCTRatio       = f2cData.code.slowData.codeA.VolCurSampleMenu[8];
    driveSampleMenu.outCurResOhm     = f2cData.code.slowData.codeA.VolCurSampleMenu[9] * (1.0/100);

    driveParameterMenu.ratingInputVoltage   = f2cData.code.slowData.codeA.DriveRatingMenu[0];
    driveParameterMenu.ratingInputCurrent   = f2cData.code.slowData.codeA.DriveRatingMenu[1] * (1.0/10);
    driveParameterMenu.ratingOuputVoltage   = f2cData.code.slowData.codeA.DriveRatingMenu[2];
    driveParameterMenu.ratingOutputCurrent  = f2cData.code.slowData.codeA.DriveRatingMenu[3] * (1.0/10);
	overVolInhibitKp = f2cData.code.slowData.codeA.overVolInhibitKp * (1.0/10);        // 过压抑制电压环Kp
	overVolInhibitKi = f2cData.code.slowData.codeA.overVolInhibitKi * (1.0/10); 
// 一些数据。。。
    hwCellFlag = (driveParameterMenu.ratingInputVoltage > 381);

    masterOrSlave = coreMainCmd1.bit.masterOrSlave;
}

#if (DEBUG_TORQUE_CALC && (INV_TYPE == HW_HD90))

extern f32 TorqueDebugCalc(f32 loadingRate);

f32 loadingRate;    // 模拟风机负载，负载转速，单位:0.01Hz
f32 torqueDebug;
#endif
//==============================================================================
//
// 读取功能传递的数据，仅读取B数据
// f2cData.code.slowData.codeB.xxx，仅允许在ReadRamBData()函数中使用
//
//==============================================================================
void ReadRamBData(void)
{
    curLoopFeedForwardGain              = f2cData.code.slowData.codeB.FeedForwardConstant * (1.0/10);
    fluxLoopFeedForwardGain             = f2cData.code.slowData.codeB.fluxLoopFeedForwardGain * (1.0/10);  // A5-02
#if DEBUG_P_LOW_FRQ_DEAL
    fluxCompLimit                       = f2cData.code.slowData.codeB.fluxCompLimit * (1.0/1000);
    fluxLoopCloseFrq                    = f2cData.code.slowData.codeB.fluxLoopCloseFrq * (1.0/100);
    fluxOpenIdRef                       = f2cData.code.slowData.codeB.fluxOpenIdRef * (1.0/100);
#endif
    motorControlOtherEnable.all         = f2cData.code.slowData.codeB.motorControlOtherEnable;
    errorProtectOtherEnable1            = f2cData.code.slowData.codeB.coreFunc[0];

    windowWidth                         = (f32)f2cData.code.slowData.codeB.windowFrq * (1.0/100);


#if 1//!DEBUG_PRG_IN_RAM
    outputConnectionMenu.ctRatio                = f2cData.code.slowData.codeB.OutputConnectionMenu[0];
    outputConnectionMenu.filterInductance       = f2cData.code.slowData.codeB.OutputConnectionMenu[1] * (1.0/1000);
    outputConnectionMenu.filterCapacitance      = f2cData.code.slowData.codeB.OutputConnectionMenu[2] * (1.0/1000);
    outputConnectionMenu.cableResistance        = f2cData.code.slowData.codeB.OutputConnectionMenu[3] * (1.0/1000);
    outputConnectionMenu.cableInductance        = f2cData.code.slowData.codeB.OutputConnectionMenu[4] * (1.0/1000);
    outputConnectionMenu.filterDampingGain      = (f32)(s16)f2cData.code.slowData.codeB.OutputConnectionMenu[5] * (1.0/100);
    LCDataDeal();
#endif
#if DEBUG_P_SM_CONTROL
//    highStartingTorqueMenu.enable           = f2cData.code.HighStartingTorqueMenu[0];
    highStartingTorqueMenu.enable           = coreSubCmd.bit.highStartingEnable;
    highStartingTorqueMenu.torqueCurrent    = f2cData.code.slowData.codeB.HighStartingTorqueMenu[0] * (1.0/100);
    highStartingTorqueMenu.currentRampTime  = f2cData.code.slowData.codeB.HighStartingTorqueMenu[1] * (1.0/10);
    highStartingTorqueMenu.pllAcqTime       = f2cData.code.slowData.codeB.HighStartingTorqueMenu[2] * (1.0/1);
#endif


//#if (INV_TYPE == HW_HD3x)   // HD3x
{
    extern f32 npcKp;
    extern f32 npcKi;
    extern f32 npcPiMax;
    
    npcKp = f2cData.code.slowData.codeB.npcKp * (1.0/100);
    npcKi = f2cData.code.slowData.codeB.npcKi * (1.0/100);
    npcPiMax = f2cData.code.slowData.codeB.npcMax * (1.0/100);
	//npcPiMax = 0.12;
	npcPi.pi->maxLimit = npcPiMax;
	npcPi.pi->minLimit = -npcPiMax;
	npcPi.pi->propGain = npcKp;
	npcPi.enable = 1;
}
//#endif
/*    
#if DEBUG_P_DA_AO_UPDATE
    aoData.ao1Vol                       = f2cData.code.slowData.codeB.aoData[0];
    aoData.ao1Offset                    = (f32)(s16)f2cData.code.slowData.codeB.aoData[1] * 32.768;
    aoData.ao1Gain                      = (f32)(s16)f2cData.code.slowData.codeB.aoData[2] * 327.68;
    aoData.ao2Vol                       = f2cData.code.slowData.codeB.aoData[3];
    aoData.ao2Offset                    = (f32)(s16)f2cData.code.slowData.codeB.aoData[4] * 32.768;
    aoData.ao2Gain                      = (f32)(s16)f2cData.code.slowData.codeB.aoData[5] * 327.68;
    aoData.ao3Vol                       = f2cData.code.slowData.codeB.aoData[6];
    aoData.ao3Offset                    = (f32)(s16)f2cData.code.slowData.codeB.aoData[7] * 32.768;
    aoData.ao3Gain                      = (f32)(s16)f2cData.code.slowData.codeB.aoData[8] * 327.68;
#endif
*/    
#if (DEBUG_TORQUE_CALC && (INV_TYPE == HW_HD90))
    loadingRate = (f32)(s16)f2cData.code.slowData.codeB.debugParaCF[24];    // 模拟风机负载，功能下传的负载转速，单位?
    torqueDebug = TorqueDebugCalc(loadingRate);    
#endif

    memcpy(&ceGroup[0], &f2cData.code.slowData.codeB.ceTestPara[0], F2C_TEST_PARA_LEN);
    memcpy(&cfGroup[0], &f2cData.code.slowData.codeB.debugParaCF[0], F2C_DEBUG_PARA_LEN);
#if DEBUG_BLACK_BOX    
    memcpy(&blackBoxGroupAddr[0], &f2cData.code.slowData.codeB.flowSampleAddr[0], F2C_BLACK_BOX_PARA_LENTH); // LS_20221205
#endif

#if CELL_BYPASS_MECH
    cellBypassMechCmd     = cfGroup[19] + ((u32)cfGroup[20] << 16);     // 蔡准手动改T1_T2接线调试用，暂时放在调试功能码，建议放在FF组里不允许更改
#endif

#if !DEBUG_PRG_IN_RAM
    sampleSequenceEnable    = ((errorProtectOtherEnable1 & BIT0) || (PURE_VF == motorControlMode)
    //							 ||
 //                               (SYNCH_TRANSFER_DOWN == synchTransfer)
 								) ? TRUE : FALSE;
    transformerOLMode       = (errorProtectOtherEnable1 & BIT1) ?
                                CUR_TIME_INVERATIO_CURVE : CUR_TIME_INVERATIO_TABLE;
    sampleAbnomityEnable    = (errorProtectOtherEnable1 & BIT2) ? TRUE : FALSE;
    decVolDealEnable        = (errorProtectOtherEnable1 & BIT3) ? TRUE : FALSE;

#if (INV_TYPE == HW_HD3x)
/*
    if (driveParameterMenu.ratingInputVoltage <= 690.0)
    {
        midMax = 40.0/537.4;              
        udcMax = 750.0/537.4;             
        udcHalfoverMax = 370.0/537.4;     
        udcOverHalfLimit = 370.0/537.4;   
        udcOverVolLimit = 750.0/537.4;    
    }
    else
    */
    {
        udcMax = f2cData.code.slowData.codeB.genVolOV / (driveParameterMenu.ratingInputVoltage * SQRT2) / 10.0;     
        udcHalfoverMax = f2cData.code.slowData.codeB.halfGenVolOV / (driveParameterMenu.ratingInputVoltage * SQRT2) / 10.0;
        udcOverHalfLimit = f2cData.code.slowData.codeB.halfGenVolOL / (driveParameterMenu.ratingInputVoltage * SQRT2) / 10.0;
        udcOverVolLimit = f2cData.code.slowData.codeB.genVolOL / (driveParameterMenu.ratingInputVoltage * SQRT2) / 10.0; 
    }
        

#endif

#endif

}



//==============================================================================
//
// 读取数据之后的一些处理
//
//==============================================================================
void RcvDataDeal(void)
{
    coreFrqHz = ((int32)(int16)coreFrq * (coreMaxFrq + 2000) + (1L << 14)) >> 15;
    coreFrqAimHz = ((int32)(int16)coreFrqAim * (coreMaxFrq + 2000) + (1L << 14)) >> 15;

    coreMaxFrqRads = coreMaxFrq * (TWO_PI/100.0);

#if DEBUG_P_SM_CONTROL   // 暂时这么调试
    if ((2 == motorPara.motorType)   // 同步机
        && (IM_FVC == coreMainCmd.bit.motorCtrlMode)
       )
    {
        motorControlMode = SM_FVC; 
    }
    else
#endif
    {
        motorControlMode = coreMainCmd.bit.motorCtrlMode;
    }
#if 1   // 
    if ((
		(driveParameterMenu.ratingInputCurrent <= 0)    ||  
        (motorPara.ratingCurrent <= 0)                  ||  
        (driveParameterMenu.ratingOutputCurrent <= 0)   ||  
        (cellMenu.installedCellsPerPhase > 10) ||
        (3750< invIOCSetpoint) ||  
        (fluxCtrlMenu.fluxDemand <= 0.0) || (2.0 <= fluxCtrlMenu.fluxDemand) 
        ||    
#if (2 != FPGA_PWM_VER)
        (coreCarrierFrq < 500) || (100000 < coreCarrierFrq)  
#elif 1
          
        (newCarrierFrq < 50) || (10000 < newCarrierFrq) 
#endif                
       )
       )
    {
        coreErrorCode = 99;
    }
#endif

 //   synchTransfer = coreMainCmd.bit.synchTransfer;

    if (coreMainCmd.bit.run)   // 调试使用
    {   // 运行
        NOP2;
    }
    else
    {
        NOP;
    }
}



extern f32 coreErrorInfo;
extern STATISTICS_STRUCT adc7606IsrTime;
extern u32 rstCellTicker;
extern u32 cellErrTicker;
extern f32 iNetInTotalDis;
extern f32 inputVolDis;
extern f32 coreCarrierFrqAct;
extern STATISTICS_STRUCT mainLoopTime;
extern f32 pwmTDetect;
extern f32 outVoltageHwFil;
extern f32 outVoltagePrgDis;
extern f32 outVoltagePrgFil;
extern f32 iInTotalDis;
extern f32 iTotalMotor;
extern f32 InputPower;
extern f32 inputVolFil;
extern f32 outVoltageHwDis;
extern f32 fluxFdb;
extern f32 fluxRegError;
extern f32 modulationIndex;
extern f32 idRefFil;
extern f32 idFdbFil;
extern f32 iqFdbFil;
extern f32 pllFluxSFrqFil;
f32 inputVolDisDebug;   // 输入电压显示的调试。=0时，显示为实际采样值，否则显示为inputVolDisDebug变量值。1.0-表示100%
extern f32 inputPowerAct;
extern f32 outputPowerAct;
extern f32 inputSAct;
//extern f32 synchMotorFieldCurrent;
extern f32 fluxAdd;
extern f32 inputFrq;
extern f32 inputPowerDis;
extern f32 driveLosses;
extern f32 iqsRatedPU;
extern f32 pllFluxSFrq;
extern f32 iqMaxAllowed1;
extern f32 fluxFdbFil;
extern f32 ai1SampleFilNew;
extern f32 ai2SampleFilNew;
extern s32 motorRun;
extern f32 iNegSeqTotal;
extern u16 coreAlarmCode;
extern u16 coreMaxFrqBypass;        // 旁路后的最大频率
extern f32 iqFdbDroopFil;           // 不同场合应用需要用的转矩电流反馈

//extern f32 powerDelta;
extern Uint16 canRxDataLow;
extern Uint16 canRxDataHigh;
extern Uint16 canErrRegHighValue;
extern Uint16 canSlaveSendDataCheckCounter;
extern Uint16 canRecRegCounterValue;
extern Uint16 canTecRegCounterValue;
extern f32 unpcFil;
extern f32 udcFil;

extern s16 upTransferWPTicker;
extern f32 synTransferTime;
extern u16 errorBitsSyncTransfer;
//extern u16 upTransferStateError;

extern f32 inputE0Fil;          // 输入电压零序分量
extern f32 outputE0AvgFil;      // 输出电压零序分量
extern f32 inputINegFil;        // 输入电流负序分量
extern f32 outputINegFil;       // 输出电流负序分量
extern f32 outputE0Fil;


extern f32 motorOLInfo;
extern u16 inputPhaseLossInfo;
extern u16 outputPhaseLossInfo;
extern f32 inputPhaseImbanlanceInfo;
extern f32 encoderLossInfo;
extern f32 outCurImbalanceInfo;
extern f32 inputVolImbalanceInfo;
extern f32 outputVolImbalanceInfo;


extern f32 iqRefMasterFil;

extern Uint16 cellStatusL;
extern Uint16 cellBlockStatus;
extern Uint16 bypassEnableFlag1;
extern Uint16 bypassEnableFlag2; 
extern u32 bypassContactorFdb;
extern struct NPC_DATA npcData;
//extern u16 upTransferInvOffCmd;
extern u16 netContactorOnCmd;
//extern u16 upTransferNetOnCmd;
extern u16 netContactorOffCmd;
extern u16 downTransferNetOffCmd;
//extern u16 upTransferOverLoad;
//extern u16 lineFluxOrientedEnable;

extern struct UpTransferError upTransferError;
extern struct CELL_OVERLOAD_PROTECT cellOlProtect;
extern struct SAMPLE_PHASE_DELAY samplePhaseDelay;
extern f32 vds,vqs;
extern struct FLUX_REGULATOR_STR fluxRegData;
extern f32 spdRegError;
extern f32 iAlphaS, iBetaS;
extern f32 idRef;
extern f32 idFdb, iqFdb;
extern f32 svcSpeedEst;
extern f32 fluxAlphaS, fluxBetaS;
extern f32 deltaSPLL;
extern struct CELLVOL_STR cellVolData;
#if (INV_TYPE == HW_HD3x)
extern f32 udcHalfOverVol;
extern f32 udcOverVol;
#endif
extern struct SPEED_REGULATOR_STR spdRegData;
f32 currentOc;     // 三相输出电流最大瞬时值，单位pu---电机额定输出电流
extern f32 reactivePower;    // 无功功率 
u16 POWER_UNIT_K;
u16 VOLTAGE_UNIT_K;
f32 testInpuVol;

//==============================================================================
//
// 写性能传递给功能的数据
//
//==============================================================================
extern f32 udcPreControl;
extern struct CELL_VOLTAGE_REGULATOR_STR cellVoltageRegulatorBrk;
extern struct SPEED_REGULATOR_STR spdRegData;
extern f32 minLimitwork;
extern struct DriveControlType DriveControl;
extern bool busOverFlag;
extern f32 udcMax;
extern f32 udc1,up1,down1,midMax,unpc1,inputVolFil,udcFil2;
extern struct DecouplePLL_STR  Current_Dsrf;
extern struct PARK_STR ParkOutCur;
extern f32 volPidRef,volPidfdb,inputFrq1;
extern u16 decouple_control_enable;
extern f32 idRef_OB,iqRef_OB;

void CopySampleD(Uint16 pFirst, Uint16 pLast, Uint16 pIdx)
{
    Uint16 i, j, idx;
    for (i = 0; i < F2C_BLACK_BOX_PARA_LENTH; i++)
    {
        idx = pIdx;
        for (j = pFirst; j < pLast; j++)
        {
            c2fData.code.sampleD[i][idx++] = (u16)(s16)(_IQtoQ12(sampleD[i][j]));
        }
    }
}

void WriteRamData(void)
{    
    u16 i;
    f32 tmp;
    Uint16 first, last;
    static Uint16 black_box_data_ticker_bak = 0;

    tmp = ((f32)(1L << 15)) / (coreMaxFrq + 2000);

    coreStatus.bit.runEnable = 1;   //?
    if (!coreStatus.bit.codeAB)
    {
        coreStatus.bit.codeAB = 1;
    }
    else
    {
        coreStatus.bit.codeAB = 0;
    }
//    coreStatus.bit.codeAB = !coreStatus.bit.codeAB;

    if (!hwCellFlag)        // 小样机
    {
        POWER_UNIT_K = 100;
        VOLTAGE_UNIT_K = 10;
    }
    else
    {
        POWER_UNIT_K = 1;
        VOLTAGE_UNIT_K = 1;
    }

// 赋值到c2fData
    c2fData.code.dspStatus              = coreStatus.all;
    c2fData.code.dspSubStatus           = coreSubStatus.all;
    c2fData.code.motorCtrlTuneStatus    = coreMotorCtrlTuneStatus;
    c2fData.code.errorCodeFromCore      = coreErrorCode;
    c2fData.code.currentOc              = _IQtoQ12(currentOc);
    //c2fData.code.coreErrorInfo          = coreErrorInfo * 1000;
    c2fData.code.coreErrorInfo          = coreErrorInfo;
    c2fData.code.alarmCodeFromCore      = coreAlarmCode;
    
#if DEBUG_BLACK_BOX // LS_20221205

    i = blackBoxDataTicker;
    if (i > black_box_data_ticker_bak)
    {
        first = black_box_data_ticker_bak;
        last = i;
        CopySampleD(first, last, 0);
        c2fData.code.sampleFastT = last - first;
    }
    else
    {
        first = black_box_data_ticker_bak;
        last = C2F_BLACK_BOX_PARA_MAX;
        CopySampleD(first, last, 0);
        c2fData.code.sampleFastT = last - first;
        
        first = 0;
        last = i;
        CopySampleD(first, last, c2fData.code.sampleFastT);
        c2fData.code.sampleFastT += (last - first);
    }
    black_box_data_ticker_bak = i;

#endif    
/*========================================================================================*
* coreAlarmInfo[0-3]为报警提示信息(按B字节表示)
* coreAlarmInfo[X]表示alarmCodeFromCore bit[X]的提示信息:
* X=0 表示电机过载时电流；X=1 输入缺相；X=2 表示输出缺相；
* X=3 预留
*=========================================================================================*/
    c2fData.code.coreAlarmInfo[0]       = motorOLInfo;
    c2fData.code.coreAlarmInfo[1]       = inputPhaseLossInfo;
    c2fData.code.coreAlarmInfo[2]       = outputPhaseLossInfo;
	
    c2fData.code.coreAlarmInfo[4]      = inputPhaseImbanlanceInfo;
    c2fData.code.coreAlarmInfo[7]      = encoderLossInfo;
    c2fData.code.coreAlarmInfo[8]      = outCurImbalanceInfo;
	c2fData.code.coreAlarmInfo[9]      = inputVolImbalanceInfo;
	c2fData.code.coreAlarmInfo[10]      = outputVolImbalanceInfo;
#if (INV_TYPE == HW_HD3x)
    c2fData.code.coreAlarmInfo[11]      = udcHalfOverVol;
#endif
/*========================================================================================*
* coreAlarmInfo4[X]表示alarmCodeFromCore bit[4+X]的提示信息:
* X=0 表示输入电流负序分量；X = 1、2预留；X=3 表示编码器反馈转速与同步转速差值；
* X=4 表示输出电流不负序分量
* X=5 表示输入电压不平衡
* X=6 表示输出电压不平衡
* X=7 表示母线电压超限
*=========================================================================================*/
/*
    c2fData.code.coreAlarmInfo4[0]      = inputPhaseImbanlanceInfo;
    c2fData.code.coreAlarmInfo4[3]      = encoderLossInfo;
    c2fData.code.coreAlarmInfo4[4]      = outCurImbalanceInfo;
	c2fData.code.coreAlarmInfo4[5]      = inputVolImbalanceInfo;
	c2fData.code.coreAlarmInfo4[6]      = outputVolImbalanceInfo;
#if (INV_TYPE == HW_HD3x)
    c2fData.code.coreAlarmInfo4[7]      = udcHalfOverVol;
#endif
    //c2fData.code.coreAlarmInfo4[8]      = udcOverVol;
*/
    c2fData.code.syncFrq                = (u16)(s16)(OutputProcess.FrequencyFiltered * (100/TWO_PI) * tmp);
    c2fData.code.speedMotor             = (u16)(s16)(motorRun * tmp);
    c2fData.code.encoderFdb             = (u16)(s16)(frqMotorRun * tmp);
    c2fData.code.outVoltage             = _IQtoQ12(outVoltageHwDis);
   // c2fData.code.generatrixVoltage      = (testInpuVol * (driveParameterMenu.ratingInputVoltage * SQRT2) + 0.5) * 10;
    c2fData.code.generatrixVoltage      = (udcFil * (driveParameterMenu.ratingInputVoltage * SQRT2) + 0.5) * 10;
    c2fData.code.torqueCurrent          = _IQtoQ12(iqFdbDroopFil);
    c2fData.code.outCurrent             = _IQtoQ12(iTotalInvDis);//_IQtoQ12(OutputProcess.TotalCurrentFil);//iTotalInv;
	
	c2fData.code.uoutCurrent            = _IQtoQ12(iuDisFil);
	c2fData.code.voutCurrent			= _IQtoQ12(ivDisFil);
	c2fData.code.woutCurrent			= _IQtoQ12(iwDisFil);
	
	c2fData.code.itDisp                 = (u16)(s16)(OutputProcess.IqsRef * 1000); // 主机的实时转矩
    c2fData.code.inputPower             = _IQtoQ12(InputProcessDisplay.AveragePower);
    //c2fData.code.outPower               = _IQtoQ12(OutputProcess.AveragePower);
    c2fData.code.outPower               = (((int32)(OutputProcess.AveragePower * 4096.0))&(0x0FFFF));
    c2fData.code.outPowerH               = (((int32)(OutputProcess.AveragePower * 4096.0))>>16);
	//if (udcFil >= 0.85)
	//{
   // 	inputVolDisDebug = cfGroup[19] * 0.01;
	//}
	//else
	//{
	//	inputVolDisDebug = 0;
	//}
    if (inputVolDisDebug == 0.0)
    {
        #if (INV_MODEL == INV_3300)
		if(motorControlOtherEnable.bit.inVol == 1)
		{
			c2fData.code.inputVoltage		= _IQtoQ12(inputVolDis);
		}
		else//没有输入电压采样，直接用母线电压当成输入电压
		{
			c2fData.code.inputVoltage		= _IQtoQ12(udcFil2);
		}
		#elif (INV_MODEL == INV_1140)
		c2fData.code.inputVoltage		= _IQtoQ12(inputVolDis);
		#endif
    }
    else
    {
        c2fData.code.inputVoltage       = _IQtoQ12(inputVolDisDebug);  // 使用全局变量给定，调试使用 
    }
   // c2fData.code.inputVoltage       = _IQtoQ12(1.0);  // 模拟给定输入电压为10000V，回馈试验时可能使用
//    c2fData.code.inputVoltage       = _IQtoQ12(0.0);  // 模拟给定输入电压为0

    // 输入电压频率，单位0.1Hz
    c2fData.code.inputFrq               = (u16)(InputProcess.FrequencyFiltered * (10.0) + ((InputProcess.FrequencyFiltered > 0) ? 0.5 : -0.5));

#if (INV_TYPE == HW_HD90)
    c2fData.code.cellStatus = cellStatus.all;
    c2fData.code.cellStatusL = cellStatusL;     // 单元故障码
    c2fData.code.cellBlockStatus = cellBlockStatus;
    c2fData.code.cellVolVer = cellVolVer.all;   // 此处将值传给ARM。
#endif

    if (!coreStatus.bit.codeAB)     // 0-codeA
//================================================
    {
        c2fData.code.slowData.codeA.currentPu           = motorPara.ratingCurrent * 10.0; // 注意功能显示的是有效值
#if !DEBUG_PRG_IN_RAM
        c2fData.code.slowData.codeA.ai1Sample           = ai1SampleFilNew;  // RAM调试时关闭了
        c2fData.code.slowData.codeA.ai2Sample           = ai2SampleFilNew;
#endif
      c2fData.code.slowData.codeA.inputCurrent        = _IQtoQ12(iInTotalDis);
//        c2fData.code.slowData.codeA.iTotalMotor         = _IQtoQ12(iTotalMotor); 

        c2fData.code.slowData.codeA.coreMaxFrqBypass    = coreMaxFrqBypass;
        c2fData.code.slowData.codeA.motorSoftVersion    = CORE_SOFT_VERSION;
        c2fData.code.slowData.codeA.FPGAVersion         = interfaceRam[FPGA_REG_Ver_fpga];     // FPGA版本号

#if (INV_TYPE == HW_HD90)
        c2fData.code.slowData.codeA.cellBypassFdbL      = bypassContactorFdb & 0x0000FFFF;
        c2fData.code.slowData.codeA.cellBypassFdbH      = (bypassContactorFdb >> 16) & 0x0000FFFF;
        c2fData.code.slowData.codeA.cellBypassEnableL   = bypassEnableFlag1;
        c2fData.code.slowData.codeA.cellBypassEnableH   = bypassEnableFlag2;
#endif

        c2fData.code.slowData.codeA.coreErrorCode      = coreErrorCode;                        // UA-00，DSP的故障
        c2fData.code.slowData.codeA.fastLoopClks       = adc7606IsrTime.mean*(10.0/DSP_CLOCK); // UA-01，快环中断的时间，0.1us
        c2fData.code.slowData.codeA.mainLoopUs         = mainLoopTime.mean * (10.0/DSP_CLOCK); // UA-02，2ms主循环的时间，0.1us
        c2fData.code.slowData.codeA.coreCarrierFrqAct  = coreCarrierFrqAct * 10;               // UA-03，(单元的)(实际使用的)载波频率单位：0.1Hz 
        c2fData.code.slowData.codeA.fastLoopFrequency  = OutputProcess.FastLoopFrequency;      // UA-04，快环频率，单位：1Hz
		c2fData.code.slowData.codeA.dropFrq			   = (u16)(s16)(dropFrq * 100);

#if !DEBUG_PRG_IN_RAM
        c2fData.code.slowData.codeA.inputSAct          = inputSAct * POWER_UNIT_K;             // UA-05，输入视在功率
    //    c2fData.code.slowData.codeA.inputPowerAct      = (u16)(fabs(inputPowerAct) * POWER_UNIT_K);     // 输入功率，单位0.1kW。小样机单位W
    //    c2fData.code.slowData.codeA.outputPowerAct     = (u16)(fabs(outputPowerAct) * POWER_UNIT_K);    // 输出功率，单位0.1kW。小样机单位W
        c2fData.code.slowData.codeA.inputPowerAct      = inputPowerAct * POWER_UNIT_K;         // UA-06，输入功率，单位0.1kW。小样机单位W
#endif
        c2fData.code.slowData.codeA.outputPowerAct     = outputPowerAct * POWER_UNIT_K;        // UA-07，输出功率，单位0.1kW。小样机单位W
        c2fData.code.slowData.codeA.driveLosses        = driveLosses * 1000;                   // UA-08 变频器损耗，0.1%
        c2fData.code.slowData.codeA.coreInfo0[0]       = 1.0 / pwmTDetect;                     // UA-09 DSP自己检测的快环频率 
        c2fData.code.slowData.codeA.idCurrent          = _IQtoQ12(idRefFil);                   // 励磁电流显示
        c2fData.code.slowData.codeA.unpcFil            = fabs(unpcFil) * driveParameterMenu.ratingInputVoltage * (SQRT2 * 10);
        c2fData.code.slowData.codeA.reactivePower      = _IQtoQ12(reactivePower);              // 无功功率


        c2fData.code.slowData.codeA.debugParaUF[0] = (*((f32 *)cfGroup[0])) * 1000;          // UF-00，显示小数位，真实内部变量值
        c2fData.code.slowData.codeA.debugParaUF[1] = (*((f32 *)cfGroup[1])) * 1000;          // UF-01
        c2fData.code.slowData.codeA.debugParaUF[2] = (*((f32 *)cfGroup[2])) * 100;           // UF-02
        c2fData.code.slowData.codeA.debugParaUF[3] = (s32)((*((f32 *)cfGroup[3])) * 1000);   // UF-03，不显示小数位，内部变量放大1000倍。
        c2fData.code.slowData.codeA.debugParaUF[4] = (s32)((*((f32 *)cfGroup[4])) * 1000);   // UF-04
        c2fData.code.slowData.codeA.debugParaUF[5] = (s32)((*((f32 *)cfGroup[5])) * 100);    // UF-05
        c2fData.code.slowData.codeA.debugParaUF[6] = (s32)((*((f32 *)cfGroup[6])) * 10);     // UF-06，不显示小数位，内部变量放大10倍。
      //  c2fData.code.slowData.codeA.debugParaUF[7] = (u16)(powerDelta * 1000);               // UF-07
        c2fData.code.slowData.codeA.debugParaUF[8] = (*((u16 *)cfGroup[8])) * 1;             // UF-08
        c2fData.code.slowData.codeA.debugParaUF[9] = (*((s16 *)cfGroup[9])) * 1;             // UF-09
#if (INV_TYPE == HW_HD3x)
        c2fData.code.slowData.codeA.debugParaUF[10] = fabs(unpcFil) * driveParameterMenu.ratingInputVoltage * (SQRT2 * 10);  // 中点偏差，0.1V
        c2fData.code.slowData.codeA.debugParaUF[11] = udcFil * driveParameterMenu.ratingInputVoltage * (SQRT2 * 10);         // 母线电压，0.1V
#endif

#if (DEBUG_TORQUE_CALC && (INV_TYPE == HW_HD90))
        c2fData.code.slowData.codeA.debugParaUF[12] = torqueDebug * 10;   // 模拟风机负载，上传给功能转矩
#endif





    }
//================================================

    else                            // 1-codeB
    
//================================================
    {

		if (cellMenu.cellVoltage == 3)//整流
		{
			c2fData.code.slowData.codeB.coreInfo1[2] = (u16)(s16)(volPidRef * 1000.0);		  // 电压环给定 
			c2fData.code.slowData.codeB.coreInfo1[3] = (u16)(s16)(volPidfdb * 1000.0);		  // 电压环反馈

			c2fData.code.slowData.codeB.coreInfo2[0] = (u16)(s16)(inputFrq1);//显示实际值  50Hz 

			#if !DEBUG_PRG_IN_RAM
			if(decouple_control_enable == 1)
			{
				c2fData.code.slowData.codeB.coreInfo1[4] = (u16)(s16)(idRef_OB * 1000.0);				 // !UA-14 输出电压伏秒零序分量
				c2fData.code.slowData.codeB.coreInfo1[5] = (u16)(s16)(Current_Dsrf.dpos * 1000.0);						// !UA-15 输入电压零序分量

				c2fData.code.slowData.codeB.coreInfo1[7] = (u16)(s16)(iqRef_OB * 1000.0);					   // !UA-17 输入电流负序分量
				c2fData.code.slowData.codeB.coreInfo1[8] = (u16)(s16)(Current_Dsrf.qpos * 1000.0);							 // !UA-18 输出电流负序分量
			}
			else
			{
				c2fData.code.slowData.codeB.coreInfo1[4] = (u16)(s16)(idRef_OB * 1000.0);				 // !UA-14 输出电压伏秒零序分量
				c2fData.code.slowData.codeB.coreInfo1[5] = (u16)(s16)(ParkOutCur.d * 1000.0);						// !UA-15 输入电压零序分量
				
				c2fData.code.slowData.codeB.coreInfo1[7] = (u16)(s16)(iqRef_OB * 1000.0);					   // !UA-17 输入电流负序分量
				c2fData.code.slowData.codeB.coreInfo1[8] = (u16)(s16)(ParkOutCur.q * 1000.0);							 // !UA-18 输出电流负序分量
			}
			//c2fData.code.slowData.codeB.coreInfo1[6] = (u16)(s16)(vds * 1000);				   // !UA-16 输出电压零序分量
			c2fData.code.slowData.codeB.coreInfo1[6] = (u16)(s16)(OutputProcess.VdsRef * 1000);

			//c2fData.code.slowData.codeB.coreInfo1[9] = (u16)(s16)(vqs * 1000);//	  (s32)(pllFluxSFrqFil * (100.0 / TWO_PI));// !UA-19 输出频率检测，单位: 0.01Hz
			c2fData.code.slowData.codeB.coreInfo1[9] = (u16)(s16)(OutputProcess.VqsRef * 1000);
#endif
		}
		else//逆变
		{
	        c2fData.code.slowData.codeB.coreInfo1[2] = (u16)(s16)(fluxRegData.fluxRef * 1000.0);          // UA-12 
	        c2fData.code.slowData.codeB.coreInfo1[3] = (u16)(s16)(fluxRegData.fluxDsFil * 1000.0);         // UA-13 输出功率因数显示
			
			c2fData.code.slowData.codeB.coreInfo2[0] = (u16)(s16)(pllBackEmfFrq * I_TWO_PI);//显示实际值  50Hz     
			
#if !DEBUG_PRG_IN_RAM
			c2fData.code.slowData.codeB.coreInfo1[4] = (u16)(s16)(idRef * 1000.0);				 // !UA-14 输出电压伏秒零序分量
			c2fData.code.slowData.codeB.coreInfo1[5] = (u16)(s16)(idFdb * 1000.0);						// !UA-15 输入电压零序分量
			//c2fData.code.slowData.codeB.coreInfo1[6] = (u16)(s16)(vds * 1000);				   // !UA-16 输出电压零序分量
			c2fData.code.slowData.codeB.coreInfo1[6] = (u16)(s16)(OutputProcess.VdsRef * 1000);

			c2fData.code.slowData.codeB.coreInfo1[7] = (u16)(s16)(iqRef * 1000.0);					   // !UA-17 输入电流负序分量
			c2fData.code.slowData.codeB.coreInfo1[8] = (u16)(s16)(iqFdb * 1000.0);							 // !UA-18 输出电流负序分量
			//c2fData.code.slowData.codeB.coreInfo1[9] = (u16)(s16)(vqs * 1000);//	  (s32)(pllFluxSFrqFil * (100.0 / TWO_PI));// !UA-19 输出频率检测，单位: 0.01Hz
			c2fData.code.slowData.codeB.coreInfo1[9] = (u16)(s16)(OutputProcess.VqsRef * 1000);
#endif
		}
        c2fData.code.slowData.codeB.coreInfo1[0] = (u16)(s16)(spdRegData.speedReference * OutputProcess.iRatedFrequency * 1000.0);////synchMotorFieldCurrent * 1000;           // UA-10 电励磁同步机的励磁电流
		c2fData.code.slowData.codeB.coreInfo1[1] = (u16)(s16)(spdRegData.wr * OutputProcess.iRatedFrequency * 1000.0);// !UA-11 允许的最大电流，相对于电机额定电流
        //c2fData.code.slowData.codeB.coreInfo1[3] = (u16)startRunStatus;

        //c2fData.code.slowData.codeB.coreInfo2[1] = (u16)(s16)(outVolData.u * 1000);                // !UA-21 iq反馈
        //c2fData.code.slowData.codeB.coreInfo2[2] = (u16)(s16)(outVolData.v * 1000);              // !UA-22 磁链反馈
        //c2fData.code.slowData.codeB.coreInfo2[3] = (u16)(s16)(outVolData.w * 1000);             // UA-23 磁链环偏差，注意乘以10000
		
		
        c2fData.code.slowData.codeB.coreInfo2[1] = (u16)(s16)(DSP_AD_UR);                // !UA-21 iq反馈
        c2fData.code.slowData.codeB.coreInfo2[2] = (u16)(s16)(DSP_AD_US);              // !UA-22 磁链反馈
        c2fData.code.slowData.codeB.coreInfo2[3] = (u16)(s16)(DSP_AD_UT);             // UA-23 磁链环偏差，注意乘以10000
		
        c2fData.code.slowData.codeB.coreInfo2[4] = (u16)(s16)(outCurData.u * 1000); 
        c2fData.code.slowData.codeB.coreInfo2[5] = (u16)(s16)(outCurData.v * 1000); 
        c2fData.code.slowData.codeB.coreInfo2[6] = (u16)(s16)(outCurData.w * 1000); 
		//c2fData.code.slowData.codeB.coreInfo2[5] = (s32)(InputProcess.Id * 1000);  // 输入电流id分量
        //c2fData.code.slowData.codeB.coreInfo2[6] = (s32)(InputProcess.Iq * 1000);  // 输入电流iq分量
        //c2fData.code.slowData.codeB.coreInfo2[5] = (u16)(s16)(busOverFlag * 1000); 
        //c2fData.code.slowData.codeB.coreInfo2[6] = (u16)(s16)(udc1 * 1000); 
        c2fData.code.slowData.codeB.coreInfo2[7] = (u16)(s16)(OutputProcess.DeltaS * 1000 * I_TWO_PI); //
		c2fData.code.slowData.codeB.coreInfo2[8] = (u16)(s16)(deltaSPLL * 1000 * I_TWO_PI); 
		c2fData.code.slowData.codeB.coreInfo2[9] = (u16)(s16)(OutputProcess.DeltaSBackEMF * 1000 * I_TWO_PI); 		
        c2fData.code.slowData.codeB.coreInfo3[0] = (u16)(s32)(samplePhaseDelay.inVolDisp * 10);            // 输入电压采样S相滞后R相角度
        c2fData.code.slowData.codeB.coreInfo3[1] = (u16)(s32)(samplePhaseDelay.outVolDisp * 10);           // 输出电压采样V相滞后U相角度
        c2fData.code.slowData.codeB.coreInfo3[2] = (u16)(s32)(samplePhaseDelay.inCurDisp * 10);            // 输入电流采样S相滞后R相角度
        c2fData.code.slowData.codeB.coreInfo3[3] = (u16)(s32)(samplePhaseDelay.outCurDisp * 10);           // 输出电流采样V相滞后U相角度
        
#if 1
//        if (SYNCH_TRANSFER_UP == synchTransfer)
//        {
 //           c2fData.code.slowData.codeB.coreInfo3[5] = SynchTransfer.UpTransferState;                 // 上切换状态
//            c2fData.code.slowData.codeB.coreInfo3[6] = (s32)(upTransferError.phaseErrorAngle * 10);   // 上切换锁相阶段相位差
//            c2fData.code.slowData.codeB.coreInfo3[7] = (u32)(synTransferTime * 10);                   // 上切换用时
//        }
 //       else if (SYNCH_TRANSFER_DOWN== synchTransfer)
 //       {
//            c2fData.code.slowData.codeB.coreInfo3[5] = SynchTransfer.DownTransferState;
//        }
 //       c2fData.code.slowData.codeB.coreInfo3[8] = upTransferStateError;
       // c2fData.code.slowData.codeB.coreInfo3[9] = downTransferStateError;

#endif
        // UA组 12 14 15 16 21 25 26 34 41 19 有符号型
        c2fData.code.slowData.codeB.coreInfo4[0] = OutputProcess.IqsMax * 1000;
        c2fData.code.slowData.codeB.coreInfo4[1] = (s32)(OutputProcess.IqsMin * 1000);         // 功能码显示有负号
        c2fData.code.slowData.codeB.coreInfo4[2] = OutputProcess.MaximumTorqueCurrent * 1000;
        c2fData.code.slowData.codeB.coreInfo4[5] = fluxAdd * 1000;
//        c2fData.code.slowData.codeB.coreInfo5[4] = modulationIndex * 1000;
//        c2fData.code.slowData.codeB.coreInfo5[9] = OutputProcess.MotorVoltage * motorPara.ratingVoltage * VOLTAGE_UNIT_K;  // 电机电压
#if DEBUG_P_LOAD_SHARING
        c2fData.code.slowData.codeB.coreInfo4[4] = (s32)(iqFdbDroopFil * 1000);                       // 下垂控制用的转矩电流反馈
        c2fData.code.slowData.codeB.coreInfo4[6] = (s32)(motorRunMaster * 100);
#endif
        c2fData.code.slowData.codeB.coreInfo4[7] = iqMaxAllowed1 * 1000;           // 允许的输入电流iq分量最大值
        c2fData.code.slowData.codeB.coreInfo4[8] = OutputProcess.LimitUsed;
        c2fData.code.slowData.codeB.coreInfo4[9] = OutputProcess.TotalCurrentFil * 1000;

//        c2fData.code.slowData.codeB.coreInfo4[9] = fabs(npcData.v0) * 1000;
    }

// 以下用于380底层PC端内部数据调用
#ifdef DEBUG_COMMUNICATE_TO_PC
        //commuPCData.gReservedDebugData = 
        commuPCData.coreFrqAimHz = (u16)(s16)(coreFrqAimHz);                                // 设定频率
        commuPCData.speedReference = (u16)(s16)(spdRegData.speedReference * (100/TWO_PI));  // 运行频率
        commuPCData.syncFrq = (u16)(s16)(OutputProcess.FrequencyFiltered * (100/TWO_PI));   // 同步频率
        commuPCData.speedMotor = (u16)(s16)(motorRun);                                     // 反馈频率
        commuPCData.spdRegError = (u16)(s16)(spdRegError * (100/TWO_PI));                   // 速度环偏差
        commuPCData.SlipFrequency = (u16)(s16)(OutputProcess.SlipFrequency * (100/TWO_PI)); // 转差频率

        commuPCData.outCurrent = (u16)(iTotalInvDis * motorPara.ratingCurrent * 10);           // 输出电流显示大小
        commuPCData.outCurDatau = (u16)(s16)(outCurData.u * motorPara.ratingCurrent * 10);  // U相输出电流
        commuPCData.outCurDatav= (u16)(s16)(outCurData.v * motorPara.ratingCurrent * 10);   // V相输出电流
        commuPCData.outCurDataw= (u16)(s16)(outCurData.w * motorPara.ratingCurrent * 10);   // W相输出电流
        commuPCData.outVolDatau = (u16)(s16)(outVolData.u * 1000);         // U相输出伏秒
        commuPCData.outVolDatav= (u16)(s16)(outVolData.v * 1000);         // V相输出伏秒
        commuPCData.outVolDataw= (u16)(s16)(outVolData.w * 1000);         // W相输出伏秒
        commuPCData.iAlphaS = (u16)(s16)(iAlphaS * motorPara.ratingCurrent * 10);           // iAlpha
        commuPCData.iBetaS = (u16)(s16)(iBetaS * motorPara.ratingCurrent * 10);             // iBeta
        commuPCData.idFdbFil = (u16)(s16)(idFdb * 1000); // id反馈
        commuPCData.iqFdbFil = (u16)(s16)(iqFdb * 1000); // iq反馈
        commuPCData.idRefFil = (u16)(s16)(idRef * 1000); // id设定
        commuPCData.iqRefFil = (u16)(s16)(iqRef * 1000); // iq设定

        commuPCData.cellGenVolAverFil = (u16)(cellVolData.cellGenVolAverFil);   // 单元母线电压平均值

        commuPCData.VdsRef = (u16)(s16)(OutputProcess.VdsRef * 1000);   // 励磁电压
        commuPCData.VqsRef = (u16)(s16)(OutputProcess.VqsRef * 1000);   // 转矩电压
        commuPCData.DeltaS = (u16)(OutputProcess.DeltaS * 100);     // 同步旋转角度
        commuPCData.EncoderSpeed = (u16)(s16)(OutputProcess.EncoderSpeed * (100/TWO_PI));  // 编码器反馈速度
        
        commuPCData.ai1SampleFilNew = (u16)(s16)(ai1SampleFilNew);       // 模拟量给定1
        commuPCData.ai2SampleFilNew = (u16)(s16)(ai2SampleFilNew);       // 模拟量给定2

        //commuPCData.accDecStatus = (u16)(coreMainCmd.bit.accDecStatus); // 加减速状态标记
        commuPCData.coreCarrierFrqAct = (u16)(coreCarrierFrqAct * 10);  // 单元实际载波频率
        commuPCData.FastLoopFrequency = (u16)(OutputProcess.FastLoopFrequency); // 快环频率

        commuPCData.svcSpeedEst = (u16)(s16)(svcSpeedEst * (100/TWO_PI));   // SVC估计的转速
        commuPCData.fluxAlphaS = (u16)(s16)(fluxAlphaS * 10);   // 定子磁链Alpha分量
        commuPCData.fluxBetaS = (u16)(s16)(fluxBetaS * 10);     // 定子磁链Beta分量
        commuPCData.fluxFdbFil = (u16)(fluxFdbFil * 10);        // 定子磁链幅值
        commuPCData.deltaSPLL = (u16)(s16)(deltaSPLL * 100);    // 定子磁链相位                
#endif


//==========
  //  c2fData.code.flag                   = f2cData.code.flag; 

// 计算CRC
   // c2fData.code.crc = CrcValueWordCalc((const Uint16 *)(&c2fData.all[0]), CORE_TO_FUNC_DATA_LEN-2);

// 把c2fData赋值到FPGA的RAM中
#if 1
   // memcpy((Uint16 *)&interfaceRam[DSP_W_ADDR + 0], &c2fData.all[0], CORE_TO_FUNC_DATA_LEN);
#elif 1
    for (i = 0; i < CORE_TO_FUNC_DATA_LEN / DPRAM_NUM; i++)
    {
        memcpy(
            (Uint16 *)&interfaceRam[DSP_W_ADDR + DPRAM_NUM * i],
            &c2fData.all[DPRAM_NUM * i],
            DPRAM_NUM
           );
    }
    memcpy(
        (Uint16 *)&interfaceRam[DSP_W_ADDR + CORE_TO_FUNC_DATA_LEN / DPRAM_NUM * DPRAM_NUM],
        &c2fData.all[CORE_TO_FUNC_DATA_LEN / DPRAM_NUM * DPRAM_NUM],
        CORE_TO_FUNC_DATA_LEN - CORE_TO_FUNC_DATA_LEN / DPRAM_NUM * DPRAM_NUM
       );
#elif 1
    interfaceRam[DSP_W_ADDR + 0] = c2fData.all[0];
    interfaceRam[DSP_W_ADDR + 1] = c2fData.all[1];
    ...
#endif


#if DEBUG_P_AUTO_TUNE
    if ((TUNE_STEP_END == coreMotorCtrlTuneStatus) ||       // 调谐已经完成
        (TUNE_STEP_ACC == coreMotorCtrlTuneStatus) ||       // 静态调谐完成后就传递数据
        (TUNE_STEP_DEC == coreMotorCtrlTuneStatus)          // 进入减速状态，调谐其实也已经完成
       )
    {
      //  autoTunePara.code.crc = CrcValueWordCalc((const Uint16 *)(&autoTunePara.all[0]), AUTO_TUNE_PARA_LEN-1);
        
     //   memcpy((Uint16 *)&interfaceRam[DSP_W_TUNE_ADDR + 0], &autoTunePara.all[0], AUTO_TUNE_PARA_LEN);
    }
#endif

    // 同步切换
#if 1
//    coreSubStatus.bit.netContactOn      = upTransferNetOnCmd;
//    coreSubStatus.bit.netContactOff     = downTransferNetOffCmd;
#elif 1
//    coreSubStatus.bit.netContactOn      = (netContactorOnCmd || upTransferNetOnCmd);
//    coreSubStatus.bit.netContactOff     = (netContactorOffCmd || downTransferNetOffCmd);
#endif
//   coreSubStatus.bit.invContactOff     = upTransferInvOffCmd;
//   coreSubStatus.bit.overLoad          = upTransferOverLoad;
//   coreSubStatus.bit.lockPhase         = lineFluxOrientedEnable;

    // 过载保护
    coreStatus.bit.motorPreOl           = motorOlProtect.predict;
//    coreStatus.bit.inverterPreOl        = cellOlProtect.predict;
}





//==============================================================================
//
// 调谐参数的初始化，全部参数从功能获得
//
//==============================================================================
void InitAutoTunePara(void)
{
#if DEBUG_P_AUTO_TUNE
	if(motorControlMode >= 6)
	{
		autoTunePara.code.rs = (u16)(motorPara.rs * 10000);
		autoTunePara.code.rr = (u16)(motorPara.rr * 10000);
		autoTunePara.code.lSigma = (u16)(motorPara.lSigma * 10000);
	//	  autoTunePara.code.lm = ;
		autoTunePara.code.iNoLoad =(u16)(motorPara.iNoload* 10000);// iNoloadTmp; 	//	不能使用 motorPara.iNoload，该值会被更改
		
	}
	else
	{
		autoTunePara.code.pmsmRs = (u16)(motorPara.smRs * 10000);

		autoTunePara.code.pmsmLd = (u16)(motorPara.smLd * 10000);
		autoTunePara.code.pmsmLq = (u16)(motorPara.smLq * 10000);
		autoTunePara.code.pmsmCoeff = (u16)(motorPara.smCoeff * 10000);
		autoTunePara.code.inertia = (u16)(motorPara.inertia * 10000);

		if(autoTunePara.code.iNoLoad == 0)
		{	
			autoTunePara.code.iNoLoad =(u16)(motorPara.iNoload* 10000);
		}
	}

// 这里好像要加0.5，原因待查。
// 否则，F2-13=0.15, 调谐后变为了0.14
    autoTunePara.code.acrKp = currentLoopMenu.currentRegProp * 100.0 + 0.5;
    autoTunePara.code.acrKi = currentLoopMenu.currentRegInteg * 10.0 + 0.5;
    autoTunePara.code.acrKpBrake = currentLoopMenu.currentRegPropBraking * 100.0 + 0.5;
    autoTunePara.code.acrKiBrake = currentLoopMenu.currentRegIntegBraking * 10.0 + 0.5;

//    autoTunePara.code.inertia = motorPara.inertia;    // 注意对应

//    autoTunePara.code.uvGainWarp = ;
#endif
}





//==============================================================================
Uint16 N1Reg0Mirror;
Uint16 N2Reg0Mirror;
Uint16 N3Reg0Mirror;
Uint16 aReg0Mirror;
Uint16 bReg0Mirror;

void UpdataFpgaCarrierReg(void);




Uint16 rsel_clk_enaReg0Mirror;




#define FLOAT_EQUAL_MIN     1e-6

//#define N1_MIN  91
//#define N1_MAX  109
#define N1_MIN  90
#define N1_MAX  110
//#define N1_MIN  95
//#define N1_MAX  105
// 可以考虑减小范围，例如98-102

#define fo      (10.0*1000000)    // FPGA调制的base frequency，10MHz

#if (1 == FPGA_PWM_VER)
f32 dfsaa = 1;
f32 gfd = 1.0;
#elif 1//(0 == FPGA_PWM_VER)
f32 dfsaa = 2;
f32 gfd = 0.5;
#endif

//==============================================================================
//
// 更新FPGA的启动AD的时序，N1N2N3ab
// 计算传递给FPGA的N1,N2,N3,A,B寄存器值，产生PWM周期
//
// fo为10MHz 
// Fxmit = fo/N1，90 <= N1 <= 110
// Fcar = Fxmit/N3。Fcar为用户设定的单元开关频率
// Fsamp = 2 * Ncells * Fcar/2^p, p=0,1,2。Fsamp为快环频率。3025Hz <= Fsamp <= 6050Hz
// Fsamp = Fxmit / N2
//
// N2，N3必须为偶数
// 2*N3/N2为整数
// 
// Fo/(Fcar*2*ranks) 约= N1 * n, N1和n为整数
// 90 <= N1 <= 110
// n = 1,2,3,...
//
//
// 调用:
//if ((coreCarrierFrqOld != coreCarrierFrq) ||    // F0-15开关频率改变了
//    (ranksOld != ranks) ||                      // 每相单元数改变了
//    (NabcFlag) ||                               // 实际的每相单元数改变了
//    (RAM_STATUS_FIRST == ramStatus)             // FPGA刚准备好，也需要执行
//   )
//{
//    ......
//    UpdateFpgaTimeSequence(
//        &coreCarrierFrqAct,
//        &OutputProcess.FastLoopFrequency,
//        ranks,
//        &OutputProcess.iStep);
//    ......
//}
//
// 
//
//==============================================================================
void UpdateFpgaTimeSequence (
    f32 *carrierFrq,        // coreCarrierFrqAct
    f32 *sampFreq,          // OutputProcess.FastLoopFrequency
    u16 rank,               // 三相最大的实际单元数
    f32 *stepNumber)        // 1/stepNumber
{
    f32 tmp, tmp1, tmp2;
    f32 min = 1.1;
    f32 fXmit;


    volatile Uint16 n1, n3;     // 去掉volatile后，o2编译有问题(N3Reg0Mirror为0)


    // check for valid rank value
    if (!rank)
    {
        return;
    }

    tmp = (fo/4) / (*carrierFrq * rank);
    // 找到 n1*n3 最接近tmp的 n1和n3.
#if 0
    for (n1 = N1_MIN; n1 <= N1_MAX; n1++)
#elif 1
    n1 = 104;   // 2012-11-26 14:25:55，根据FPGA的要求，固定分频系数N1
#endif
    {
        tmp2 = tmp / n1;
        n3 = (Uint16)(tmp2 + 0.5);
        tmp1 = fabs(tmp2 - n3);
        if (tmp1 < min)
        {
            min = tmp1;
            N1Reg0Mirror = n1;
            N3Reg0Mirror = n3;
        }
    }

    N3Reg0Mirror = 4 * N3Reg0Mirror * rank;

    fXmit = fo / N1Reg0Mirror;
    *carrierFrq = fo / ((u32)N1Reg0Mirror * N3Reg0Mirror);
    *sampFreq = 2 * rank * *carrierFrq;

#if (INV_TYPE == HW_HD90)
#define FAST_LOOP_FREQ_MAX  6050    // 快环频率的最大值
    while (*sampFreq > FAST_LOOP_FREQ_MAX)
    {
        *sampFreq *= 0.5;
    }
    while (*sampFreq < FAST_LOOP_FREQ_MAX/2)
    {
        *sampFreq *= 2;
    }
#elif (INV_TYPE == HW_HD3x)
    *sampFreq *= dfsaa;     // 暂时乘以2。担心瞬时开关频率会上升。
#endif

    rsel_clk_enaReg0Mirror = 55;

    UpdataFpgaCarrierReg();
//    UpdataFpgaCarrierReg();     // 写两次。写一次FPGA接收的好像有问题。
//    UpdataFpgaCarrierReg();

    return;
}





//==============================================================================
//
// 以下是DSP与FPGA的交互!!
//
//==============================================================================


extern Uint16 daInitOk;
u16 runTicker;
u16 stopTicker;

#define RUN_TICKER      2
#define STOP_TICKER     2

#define RUN_ENABLE_TICKER      5


u16 masterOrSlave;              // 0:单机 1:主机 2:从机
u16 ocFlag;                     // 仅在刚过流时，获取过流时刻电流。

u16 dspWVolFpgaCnt;             // FPGA中的DSP写电压指令的计数器。每次写，FPGA加1
u16 dspWVolFpgaCntErrorTicker;  // 错误累计
//extern f32 coreErrorInfo;
u16 igbt_fault,enable,fixNum;//
//==============================================================================
//
// DSP更新给FPGA数据
//
//==============================================================================
void UpdateDataCore2Fpga(void)
{
    u16 enableTmp;          // 给FPGA的runEnable，运行给4，停机给0
//    f32 currentOc;          // 过流时刻电流
    if (daInitOk && (0x1234 == interfaceRam[FPGA_REG_ERROR]))
    {
      	coreErrorCode = ERROR_HARDWAREOV;
        coreRunStatus.bit.run = 0;
	}
    if (daInitOk && (0xA5A5 == interfaceRam[FPGA_REG_ERROR]))
    {
        coreErrorCode = ERROR_OC_ACC_SPEED;
        coreRunStatus.bit.run = 0;

        // 过流时的电流显示
        // 通鼺PGA传递过流故障，显示的过流时刻电流可能不准。        
        if (0 == ocFlag)    // 过流时刻电流，U0-95显示
        {
            // 三相输出最大电流瞬时值，每拍都传
            f32 tmp1, tmp2, tmp3;
            
            if ((masterOrSlave) && (!PARA_WAY_SEL))
            {
                tmp1 = fabs(outCurData.uParaInv);
                tmp2 = fabs(outCurData.vParaInv);
                tmp3 = fabs(outCurData.wParaInv);
            }
            else
            {
                tmp1 = fabs(outCurData.u);
                tmp2 = fabs(outCurData.v);
                tmp3 = fabs(outCurData.w);
            }
            currentOc = GetMax3(tmp1, tmp2, tmp3);  // currentOc为有效值pu
            //coreErrorInfo = currentOc * motorPara.ratingCurrent / driveParameterMenu.ratingOutputCurrent;
            coreErrorInfo = currentOc * motorPara.ratingCurrent * SQRT2;
            ocFlag = 1;
			//ocFlag = 0;
        }
        
    }
// FPGA发现单元有故障时，立即封锁所有单元的PWM。
// 当有单元故障时，尽快停止输出PWM
//    else if (interfaceRam[FPGA_REG_GENERAL_ERROR])  // 总故障寄存器
//    {
//        coreRunStatus.bit.run = 0;
//    }

    enableTmp = 0;
    if ((coreRunStatus.bit.run)&&(ROTOR_INITIAL_STATE != DriveControl.State)
		&&(AT_LEAKAGE_MEASUREMENT_ERROR_NEW != AutoTune.StatusStage1))
    {
        stopTicker = 0;

        runTicker++;
        // 启动时，先给电压指令，再给运行命令
        if (runTicker > RUN_TICKER)
        {
//            runTicker = RUN_TICKER;

            enableTmp = 4;
        }
    }
    else
    {
        runTicker = 0;

        stopTicker++;
        // 停机时，先给停机命令，再把电压指令清零。
        if (stopTicker > STOP_TICKER)
        {
            stopTicker = STOP_TICKER;
            outputVol.va = 0;
            outputVol.vb = 0;
            outputVol.vc = 0;

            outputVol.vaPrime = 0;
            outputVol.vbPrime = 0;
            outputVol.vcPrime = 0;

            outputVol.vaStep = 0;
            outputVol.vbStep = 0;
            outputVol.vcStep = 0;

            outputVol.vaPrimeStep = 0;
            outputVol.vbPrimeStep = 0;
            outputVol.vaPrimeStep = 0;
        }
    }

#if LIMIT_PWM_OPEN_TIME
// PWM只开通_个载波周期
    if (InvPwmPeriod)
    {
        if (!enableTmp)
        {
            enableTicker = 0;
        }
        else
        {
            enableTicker++;
        }

        if (enableTicker > InvPwmPeriod)
        {
            enableTicker = InvPwmPeriod;
            enableTmp = 0;
            coreRunStatus.bit.run = 0;

            if (ERROR_OC_ACC_SPEED != coreErrorCode)
                coreErrorCode = 98;
        }
    }
#endif

    //if ((0 == outputVol.enable) && (4 == enableTmp))        // 0->4
    if((ROTOR_INITIAL_STATE == DriveControl.State)
		||(AT_LEAKAGE_MEASUREMENT_ERROR_NEW == AutoTune.StatusStage1))
    {
		interfaceRam[FPGA_REG_runEnable] = 0;
	}
	else		
    if (4 == enableTmp)  // 4，运行。连续发RUN_ENABLE_TICKER拍
    {
        if (runTicker <= RUN_TICKER + RUN_ENABLE_TICKER)
        {
//            NOP;    //?
            interfaceRam[FPGA_REG_runEnable] = 4; //?
        }
        else
        {
            runTicker = RUN_TICKER + RUN_ENABLE_TICKER + 1;
        }
    }
    //else if ((4 == outputVol.enable) && (0 == enableTmp))   // 4->0
    else if (0 == enableTmp)    // 0，停机
    {
        interfaceRam[FPGA_REG_runEnable] = 0;
//        asm(" nop");
    }

//    outputVol.enable = enableTmp;


#if 0
    interfaceRam[FPGA_REG_rsel_va_wr]       = outputVol.va;
    interfaceRam[FPGA_REG_rsel_vap_wr]      = outputVol.vaPrime;
    interfaceRam[FPGA_REG_rsel_vb_wr]       = outputVol.vb;
    interfaceRam[FPGA_REG_rsel_vbp_wr]      = outputVol.vbPrime;
    interfaceRam[FPGA_REG_rsel_vc_wr]       = outputVol.vc;
    interfaceRam[FPGA_REG_rsel_vcp_wr]      = outputVol.vcPrime;
    interfaceRam[FPGA_REG_rsel_va_step_wr]  = outputVol.vaStep;
    interfaceRam[FPGA_REG_rsel_vap_step_wr] = outputVol.vaPrimeStep;
    interfaceRam[FPGA_REG_rsel_vb_step_wr]  = outputVol.vbStep;
    interfaceRam[FPGA_REG_rsel_vbp_step_wr] = outputVol.vbPrimeStep;
    interfaceRam[FPGA_REG_rsel_vc_step_vr]  = outputVol.vcStep;
    interfaceRam[FPGA_REG_rsel_vcp_step_wr] = outputVol.vcPrimeStep;

//    interfaceRam[FPGA_REG_runEnable]        = outputVol.enable;
#elif 1
    memcpy(
        (u16 *)&interfaceRam[FPGA_REG_rsel_va_wr],
        (u16 *)&outputVol.va,
        12+0
       );

#endif

#if 0
{
    u16 old;

    old = dspWVolFpgaCnt + 1;
    dspWVolFpgaCnt = interfaceRam[FPGA_REG_DSP_W_VOL];
    if (old != dspWVolFpgaCnt)
    {
        dspWVolFpgaCntErrorTicker++;
    }
    else
    {
        dspWVolFpgaCntErrorTicker = 0;
    }
    if (dspWVolFpgaCntErrorTicker >= 3)
    {
        coreErrorCode = 97;
    }
}
#endif

}




#define FPGA_N1_CNT_MAX     10      // 写N1N2N3AB寄存器次数的最大值
extern Uint16 N1Reg0Mirror;
extern Uint16 N2Reg0Mirror;
extern Uint16 N3Reg0Mirror;
extern Uint16 aReg0Mirror;
extern Uint16 bReg0Mirror;
extern Uint16 cellOffsetRegMirror[];
extern Uint16 rsel_clk_enaReg0Mirror;
u16 updateFpgaCarrierRegFlag;   // DSP已经更新了给FPGA的PWM载波寄存器(N1,N2,N3,a,b等)
u16 wN1Ticker;

//==============================================================================
//
// 更新给FPGA的PWM 分频寄存器(N1,N2,N3,a,b等)
//
//==============================================================================
void UpdataFpgaCarrierReg(void)
{
    u16 N1Tmp;
    u16 N2Tmp;
    u16 N3Tmp;
    u16 aTmp;
    u16 bTmp;
//    u16 wN1Ticker;

    wN1Ticker = 0;

    do
    {
        // 关键代码，必须一次性写入，关闭中断
        DINT;
        interfaceRam[FPGA_REG_N1_ENABLE] = FPGA_N1_ENABLE;      // 开启写N1N2N3ab寄存器使能
        DELAY_US(0.5);                                          // 延时_us
        interfaceRam[FPGA_REG_N1] = N1Reg0Mirror;               // 写寄存器值
        interfaceRam[FPGA_REG_N2] = N2Reg0Mirror;
        interfaceRam[FPGA_REG_N3] = N3Reg0Mirror;
        interfaceRam[FPGA_REG_A]  = aReg0Mirror;
        interfaceRam[FPGA_REG_B]  = bReg0Mirror;
        DELAY_US(0.5);                                          // 延时_us
        interfaceRam[FPGA_REG_N1_ENABLE] = FPGA_N1_DISENABLE;   // 关闭写N1N2N3ab寄存器使能 
        EINT;

        N1Tmp = interfaceRam[FPGA_REG_R_N1];                    // 读取寄存器值
        N2Tmp = interfaceRam[FPGA_REG_R_N2];
        N3Tmp = interfaceRam[FPGA_REG_R_N3];
        aTmp  = interfaceRam[FPGA_REG_R_A];
        bTmp  = interfaceRam[FPGA_REG_R_B];

        wN1Ticker++;
    }
    while (((N1Tmp != N1Reg0Mirror) ||      // 有不对的数据
            (N2Tmp != N2Reg0Mirror) ||
            (N3Tmp != N3Reg0Mirror) ||
            (aTmp  != aReg0Mirror ) ||
            (bTmp  != bReg0Mirror )
           ) &&
           (wN1Ticker < FPGA_N1_CNT_MAX)    // 最多多少次
          );

    if (wN1Ticker >= FPGA_N1_CNT_MAX)
    {
        // 可以考虑报故障。
        NOP;
    }


    interfaceRam[FPGA_REG_SyncStopReg0] = 167;
    interfaceRam[FPGA_REG_SyncStopReg1] = 167;
    interfaceRam[FPGA_REG_SyncStopReg2] = 167;
    interfaceRam[FPGA_REG_SyncStopReg3] = 167;
    interfaceRam[FPGA_REG_SyncStopReg4] = 167;
/*
    interfaceRam[FPGA_REG_cellOffset0] = cellOffsetRegMirror[0];
    interfaceRam[FPGA_REG_cellOffset1] = cellOffsetRegMirror[1];
    interfaceRam[FPGA_REG_cellOffset2] = cellOffsetRegMirror[2];
    interfaceRam[FPGA_REG_cellOffset3] = cellOffsetRegMirror[3];
    interfaceRam[FPGA_REG_cellOffset4] = cellOffsetRegMirror[4];
    interfaceRam[FPGA_REG_cellOffset5] = cellOffsetRegMirror[5];
    interfaceRam[FPGA_REG_cellOffset6] = cellOffsetRegMirror[6];
    interfaceRam[FPGA_REG_cellOffset7] = cellOffsetRegMirror[7];
    interfaceRam[FPGA_REG_cellOffset8] = cellOffsetRegMirror[8];
    interfaceRam[FPGA_REG_cellOffset9] = cellOffsetRegMirror[9];
    interfaceRam[FPGA_REG_cellOffset10] = cellOffsetRegMirror[10];
    interfaceRam[FPGA_REG_cellOffset11] = cellOffsetRegMirror[11];
    interfaceRam[FPGA_REG_cellOffset12] = cellOffsetRegMirror[12];
    interfaceRam[FPGA_REG_cellOffset13] = cellOffsetRegMirror[13];
    interfaceRam[FPGA_REG_cellOffset14] = cellOffsetRegMirror[14];
    interfaceRam[FPGA_REG_cellOffset15] = cellOffsetRegMirror[15];
    interfaceRam[FPGA_REG_cellOffset16] = cellOffsetRegMirror[16];
    interfaceRam[FPGA_REG_cellOffset17] = cellOffsetRegMirror[17];
    interfaceRam[FPGA_REG_cellOffset18] = cellOffsetRegMirror[18];
    interfaceRam[FPGA_REG_cellOffset19] = cellOffsetRegMirror[19];
    interfaceRam[FPGA_REG_cellOffset20] = cellOffsetRegMirror[20];
    interfaceRam[FPGA_REG_cellOffset21] = cellOffsetRegMirror[21];
    interfaceRam[FPGA_REG_cellOffset22] = cellOffsetRegMirror[22];
    interfaceRam[FPGA_REG_cellOffset23] = cellOffsetRegMirror[23];
    interfaceRam[FPGA_REG_cellOffset24] = cellOffsetRegMirror[24];
    interfaceRam[FPGA_REG_cellOffset25] = cellOffsetRegMirror[25];
    interfaceRam[FPGA_REG_cellOffset26] = cellOffsetRegMirror[26];
    interfaceRam[FPGA_REG_cellOffset27] = cellOffsetRegMirror[27];
    interfaceRam[FPGA_REG_cellOffset28] = cellOffsetRegMirror[28];
    interfaceRam[FPGA_REG_cellOffset29] = cellOffsetRegMirror[29];
*/

    interfaceRam[FPGA_REG_rsel_clk_ena] = rsel_clk_enaReg0Mirror;

    updateFpgaCarrierRegFlag = 1;


}





#define CELL_FAULT_SET_NUM  10
//u16 cellFaultSet[CELL_FAULT_SET_NUM];
#if 0   // 屏蔽单元故障的示例
    interfaceRam[FPGA_REG_BASE_ADDR + 0x009b] = 0xFFFF;//block2,全部屏蔽

    // 1-屏蔽；0-开通
//    interfaceRam[FPGA_REG_FAULT_BLOCK00] = 0x0000;//block0,bit0~bit5表示cell1~cell6；
                                                       //bit8~bit13表示link1~link6，其他未用
//    interfaceRam[FPGA_REG_FAULT_BLOCK01] = 0x0000;//block1,bit0、2、4、6、8、10分别表示commfault1~6
                                                       //block1,bit1、3、5、7、9、11分别表示parity_error1~6

 //   interfaceRam[FPGA_REG_FAULT_BLOCK10] = 0xF8F8;//block10,bit0~bit5表示cell7~cell12；
                                                       //bit8~bit13表示link7~link12，其他未用
  //  interfaceRam[FPGA_REG_FAULT_BLOCK11] = 0xFFC0;//block11,bit0、2、4、6、8、10分别表示commfault7~12
                                                       //block11,bit1、3、5、7、9、11分别表示parity_error7~12

  //  interfaceRam[FPGA_REG_FAULT_BLOCK20] = 0xFFFF;//block20,bit0~bit5表示cell13~cell18；
                                                       //bit8~bit13表示link13~link18，其他未用
  //  interfaceRam[FPGA_REG_FAULT_BLOCK21] = 0xFFFF;//block21,bit0、2、4、6、8、10分别表示commfault13~18
                                                       //block21,bit1、3、5、7、9、11分别表示parity_error13~18

 //   interfaceRam[FPGA_REG_FAULT_BLOCK30] = 0xFFFF;//block30,bit0~bit5表示cell19~cell24；
                                                       //bit8~bit13表示link19~link24，其他未用
  //  interfaceRam[FPGA_REG_FAULT_BLOCK31] = 0xFFFF;//block31,bit0、2、4、6、8、10分别表示commfault19~24
                                                       //block31,bit1、3、5、7、9、11分别表示parity_error19~24

 //   interfaceRam[FPGA_REG_FAULT_BLOCK40] = 0xFFFF;//block40,bit0~bit5表示cell25~cell30；
                                                       //bit8~bit13表示link25~link30，其他未用
  //  interfaceRam[FPGA_REG_FAULT_BLOCK41] = 0xFFFF;//block41,bit0、2、4、6、8、10分别表示commfault25~30
                                                       //block41,bit1、3、5、7、9、11分别表示parity_error25~30



#if 1       // 大样机   // 使用前面8*3个单元
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0x0000; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0x0000;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0x0000; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0x0000;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0x0000; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0x0000;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0x0000; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0x0000;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xFFFF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xFFFF;
#elif 1     // 小样机   // 使用前面3*3个单元
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0x0000; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0x0000;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0xF8F8; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0xFFC0;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0xFFFF; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0xFFFF; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xFFFF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xFFFF;
#elif 1   // 全部单元屏蔽故障
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0xFFFF; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0xFFFF; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0xFFFF; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0xFFFF; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xFFFF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xFFFF;
#elif 0 // 仅使用A1单元
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0xFEFE; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0xFFFC;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0xFFFF; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0xFFFF; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0xFFFF; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xFFFF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xFFFF;
#elif 1 // 仅使用B1单元
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0xFDFD; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0xFFF3;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0xFFFF; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0xFFFF; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0xFFFF; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xFFFF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xFFFF;
#elif 1 // 仅使用C10单元
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0095] = 0xFFFF; // cell1-6
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0098] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0115] = 0xFFFF; // cell7-12
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0118] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0195] = 0xFFFF; // cell13-18
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0198] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0215] = 0xFFFF; // cell19-24
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0218] = 0xFFFF;
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0295] = 0xDFDF; // cell25-30
    interfaceRam[FPGA_REG_BASE_ADDR + 0x0298] = 0xF3FF;
#endif

#endif



#if (INV_TYPE == HW_HD90)
//==============================================================================
//
// 单元收
// DSP与FPGA交互
//
//==============================================================================
void CellErrorEnableDeal(u32 cellFaultEnableFlag, u32 bypassFlag)
{
    u16 i, j, k;
    u16 cellFaultSet[CELL_FAULT_SET_NUM];

    for (i = 0; i < CELL_FAULT_SET_NUM; i++)
    {
        cellFaultSet[i] = 0xFFFF;
    }

    for (i = 0; i < MAX_CELLS; i++)
    {
        if (cellFaultEnableFlag & (1UL << i))
        {
            j = i / 6 * 2;
            k = i % 6;

            if (bypassFlag & (1UL << i))    // 旁路，屏蔽cellError
            {
                cellFaultSet[j] &= ~(0x0100U << k);
            }
            else
            {
                cellFaultSet[j] &= ~(0x0101U << k);
            }
            cellFaultSet[j+1] &= ~(0x0003U << (k*2));
        }
    }

//    interfaceRam[FPGA_REG_FAULT_BLOCK00] = cellFaultSet[0];
//    interfaceRam[FPGA_REG_FAULT_BLOCK01] = cellFaultSet[1];
//    interfaceRam[FPGA_REG_FAULT_BLOCK10] = cellFaultSet[2];
//    interfaceRam[FPGA_REG_FAULT_BLOCK11] = cellFaultSet[3];
//    interfaceRam[FPGA_REG_FAULT_BLOCK20] = cellFaultSet[4];
 //   interfaceRam[FPGA_REG_FAULT_BLOCK21] = cellFaultSet[5];
 //   interfaceRam[FPGA_REG_FAULT_BLOCK30] = cellFaultSet[6];
 //   interfaceRam[FPGA_REG_FAULT_BLOCK31] = cellFaultSet[7];
//    interfaceRam[FPGA_REG_FAULT_BLOCK40] = cellFaultSet[8];
 //   interfaceRam[FPGA_REG_FAULT_BLOCK41] = cellFaultSet[9];
}
#endif




//==============================================================================
//
// 复位(FPGA传递的)过流故障
//
//==============================================================================
void ResetIoc(void)
{
    interfaceRam[FPGA_REG_RST_ERROR] = 0x5A5A;  // 复位(FPGA传递的)过流故障
}



























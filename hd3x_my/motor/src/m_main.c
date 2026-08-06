//==================================================================================================
//
// 电机控制的主循环
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_main.h"
#include "m_interface.h"
#include "m_speedSample.h"
#include "m_frqSrc.h"
#include "m_input.h"
#include "m_error.h"
#include "m_fluxLoop.h"
#include "m_speedLoop.h"
#include "m_spinningLoad.h"
#include "m_interfaceModify.h"
//#include "f_dspcan.h"
#include "m_transfer.h"
#include "m_accDecDeal.h"

#include "m_macro_AO.h"
#include "m_macro_log.h"
#include "m_macro_sm.h"
#include "m_macro_transfer.h"

#include "Debug.h"
#include "SimpleDebug.h"

#include "m_accDecDeal.h"
#include "m_ImSVC4CalcFlux.h"
#include "m_ImSvc3Include.h"


#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
//#pragma CODE_SECTION(UpdateDataLog,     "ramfuncs");
#endif


void RcvDataDeal(void);



Uint16 coreTuneCmd;

union DSP_MAIN_COMMAND coreMainCmd;
union DSP_MAIN_COMMAND1 coreMainCmd1;
union DSP_SUB_COMMAND coreSubCmd;
union DSP_STATUS coreStatus;
union DSP_SUB_STATUS coreSubStatus;
union CORE_RUN_STATUS coreRunStatus; 


extern f32 pllBackEmfFrq;
extern Uint16 rcvOkTicker;




void UpdateAdPara(void);
void MotorParaChange(void);
void InfoCalc(void);
void CurVolRmsCalc(void);
void CoreErrorDeal(void);
void InitPerformanceData(void);
void InitMiscData(void);
void InitIo(void);
void ExciteDealSM(void);
void MiscDataDealMainLoop(void);
void SecVerIoInit(void);
extern void SlowLoopControl(void);
extern void RcvDataFunc2Core(void);
extern void SendDataCore2Func(void);
extern void RcvDataFunc2Core(void);
extern void InitInputProcessing(void);

extern void Main05msFunctionA(void);
extern void Main05msFunctionB(void);
extern void Main05msFunctionC(void);
extern void Main05msFunctionD(void);
extern void Main0msFuction(void);
extern void InitAd7606(void);

//==============================================================================
//
// 0ms调用函数
//
//==============================================================================
void Main0msMotor(void)
{
    pulseInSampleFvcQep();
}
/*
void Main05msFunctionA(void)
{
	;
}

void Main05msFunctionB(void)
{
	;
}

void Main05msFunctionC(void)
{
	;
}
*/
/*
void Main05msFunctionD(void)
{
	;
}
*/
void Main0msFuction(void)
{
	;
}

//==============================================================================
//
// 
//
//==============================================================================
void Main05msMotorA(void)
{
    ;
}



//==============================================================================
//
// 
//
//==============================================================================
void Main05msMotorB(void)
{
    ;
}



u16 secondVersionFlag = 1;
extern Uint16 adRam[];
u16 *pAdResult = (u16 *)&interfaceRam[FPGA_REG_SampleSecondBoardCh1];//(u16 *)&adRam[0];
u32 mainLoopTicker;     // 主循环计数器
//extern void CellInfoDeal(void);
extern void InitIoFirst(void);
extern void InitIoSecond(void);
//==============================================================================
//二代板IO初始化函数
//==============================================================================
void SecVerIoInit(void)
{   
    /////if(coreMainCmd1.bit.newKernel == 1)
    //{
        InitIoSecond();
        pAdResult = (u16 *)&interfaceRam[FPGA_REG_SampleSecondBoardCh1];
    //    secondVersionFlag = 1;
   // }
  //  else
 //   { 
  //      InitIoFirst();
 //       pAdResult = (u16 *)&adRam[0];
 //       secondVersionFlag = 0;        
 //   }
}



//==============================================================================
//
// 2ms调用1次
// 
// 2013-7-12 15:35测试，主循环，如果没有中断，占用时间约615us(电机不运行)、623us(电机运行)。
//
// 测试占用中断的主循环时间，
// 2013-7-17 19:32:08测试，
// 修改交互之后，2013-8-8 16:07:34测试
// 快环频率(Hz) 主循环us(0717)  主循环us(0808)
// 6000         1186            811
// 5500         1104            755
// 5000         1024            698
// 4500         952             652
// 4000         882 871         635
// 3500         850             608
// 3000         797             580
// 2500         741
// 2000         720
//
//==============================================================================
extern f32 PWMDuty;
void Main05msMotorC(void)
{
    mainLoopTicker++;
    
    RcvDataFunc2Core();     // 247->216us, 接收功能传递给性能的数据。221us
    
    RcvDataDeal();
	
    StateControl();         // 
  //  EPwm1Regs.CMPB = PWMDuty * 2500; 
//	EPwm3Regs.CMPB = PWMDuty * 2500; 
    MotorRunDeal();         // 155us

    InfoCalc();             // 9.5us

    CoreErrorDeal();        // 40us

    SendDataCore2Func();    // 147us

#ifdef DEBUG_COMMUNICATE_TO_PC
 //   CommunicatePC();
#endif
}



//==============================================================================
//
// 
//
//==============================================================================
void Main05msMotorD(void)
{
    ;
}



//extern void InitAd7606(void);
//==============================================================================
//
// 系统初始化
// 1. 变量初始化
// 2. 等待功能传递数据。一些功能传递的数据是被除数，防止这些变量为0.
//
//==============================================================================
void InitSystem(void)
{
    InitPerformanceData();      // 性能变量初始化
    InitMiscData();             // 其它变量初始化

// 接收到正确数据后才进入主循环，多接收几次
  //  while (rcvOkTicker < 10)
  //  {
  //      RcvDataFunc2Core();     // rcvOkTicker 也是在RcvDataFunc2Core()函数中更新
  //      LED_DSP_ERROR_ON;
  //  }
 //   LED_DSP_ERROR_OFF;

   // MotorRunDeal();//暂时不执行，功能码没交互成功不能执行

// AD7606的电源建立比DSP电源建立可能慢很多，所以这里延迟一段时间后，再进行初始化。
// DSP 可能比AD7606 电源建立要快， 再次延时其初始化时间
    DELAY_US(1UL * 150);

    InitAd7606();           // 初始化AD采样芯片
    
    SecVerIoInit();         // 二代板，IO口进行重新初始化
}







#define MAIN_LOOP_STAT_PRD  0.500     // 主循环统计周期，s
extern STATISTICS_STRUCT mainLoopTime;
//==============================================================================
//
// 上电初始化其它变量
//
//==============================================================================
void InitMiscData(void)
{
    mainLoopTime.prd = MAIN_LOOP_STAT_PRD / MAIN_LOOP_TIME;

// 防止DSP与ARM交互时，AB数据个数不等
    if (sizeof(struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT) != sizeof(struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT))
    {
        coreErrorCode = 99;
    }
    if (sizeof(struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT) != sizeof(struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT))
    {
        coreErrorCode = 99;
    }
}






extern u16 circulatingCurrentFlag;
//extern u16 netContactorAcknowledge;
//extern u16 invContactorAcknowledge;
//extern u16 upTransferInvOffCmd;
extern u16 upTransferInvOffTicker;

u16 netContactorOffCmd;
u16 netContactorOnCmd;
//==============================================================================
//
// 主循环中一些数据之间的转换，包括:
// 输入电压，输入电流，输出电压，输出电流的有效值计算
// 其它信息交互
//
// 调用周期: 主循环
//
//==============================================================================

void InfoCalc(void)
{
//    u16 netContactorOffReady = 0;
//    u16 netContactorOnReady = 0;
//    static u16 netContactorOffTicker = 0;
//    static u16 netContactorOnTicker = 0;
//    static u16 netContactorOffReadyOld = 0;
//    static u16 netContactorOnReadyOld = 0;
//    static u16 contactorTestTicker = 0;

// 输入电压，输入电流，输出电压，输出电流的有效值计算
    CurVolRmsCalc();

 //   MiscDataDealMainLoop();

//=============================================================    
#if DEBUG_P_SYNC_TRANSFER
    // 环流测试，可吸合工频接触器
    if (1 == NET_CONTACTOR_CMD)
    {
        netContactorOnReady = (circulatingCurrentFlag) ? TRUE : netContactorOnReady;
    }
    // 下切换结束，可断开工频接触器
    else if (2 == NET_CONTACTOR_CMD)
    {
        netContactorOffReady = TRUE;
    }
    // 工频接触器信号础焘:未上高压，变频接触器还未吸合
    else if (3 == NET_CONTACTOR_CMD)
    {
        netContactorOnReady = TRUE;
        if (!netContactorAcknowledge)
        {
            contactorTestTicker++;
            coreErrorCode =
                ((contactorTestTicker >= 200) && !coreErrorCode) ? 96 : FALSE;
        }
        else
        {
            contactorTestTicker = 0;
        }
    }
    else if (4 == NET_CONTACTOR_CMD)
    {
        netContactorOffReady = TRUE;
        if (netContactorAcknowledge)
        {
            contactorTestTicker++;
            coreErrorCode =
                ((contactorTestTicker >= 60) && !coreErrorCode) ? 96 : FALSE;
        }
        else
        {
            contactorTestTicker = 0;
        }
    }
    
//    PulseTriggerMacro(netContactorOnReady,  netContactorOnReadyOld,  netContactorOnTicker,  netContactorOnCmd); 
//    PulseTriggerMacro(netContactorOffReady, netContactorOffReadyOld, netContactorOffTicker, netContactorOffCmd);
#endif


#if 0
// CF-19模拟控制电网断电，1000代表1000ms
// 借用netContactor
{
    static u16 cf19Old;
    
    coreStatus.bit.invContactor = 1;    // 变频接触器
//    coreStatus.bit.netContactor = cfGroup[19];

    coreStatus.bit.netContactor = 1;
    if (cfGroup[19] == 0)
    {
        netDisconnectTime = 0;
        cf19Old = cfGroup[19];
    }
    else if (cf19Old != cfGroup[19])
    {
        coreStatus.bit.netContactor = 0;
        netDisconnectTime += SLOW_LOOP_TIME;
        if (netDisconnectTime >= (f32)cfGroup[19] / 1000)
        {
            cf19Old = cfGroup[19];
        }
    }
}
#endif
//=============================================================
}



f32 svcSpeedEstPu;
f32 SlipFrequencyPu;
extern f32 svcSpeedEst;
//==============================================================================
//
// 主循环中一些数据之间的转换
//
//==============================================================================
void MiscDataDealMainLoop(void)
{
    SlipFrequencyPu = OutputProcess.SlipFrequency * motorPara.iFPuOmegaOne;
    svcSpeedEstPu  = svcSpeedEst * motorPara.iFPuOmegaOne;
}







void OutVoltageDeal(void);
extern void DecVolDeal(void);


//==============================================================================
//
// 性能的主循环函数
//
//==============================================================================
void MotorRunDeal(void)
{
    CommandGeneratorControl();  // 获取磁链给定，频率给定

#if DEC_TIME_CELLDC
    DecVolDeal();               // 减速制动处理
#endif     
        
    UpdateAdPara();

    MotorParaChange();
	//IM SVC3 SVC4
//	if((motorControlMode == IM_SVC4) || (motorControlMode == IM_SVC3))
	{
		IMMotorParaChangeSVC34();
		ChangeMotorParSVC34();
		PrepareSVC4Par();
	}
	
    InitInputProcessing();
    InitOutputProcessing();

    OutVoltageDeal();

    SlowLoopControl();

#if DEBUG_P_SM_CONTROL
    ExciteDealSM();             // 电励磁同步机，与励磁柜的信息交互 
#endif
}





void MiscDataDealAdInt(void);

extern f32 spdRef, spdFdb;
extern f32 fluxAlphaS, fluxBetaS;
extern f32 yAlphaS, yBetaS;
extern f32 vAlphaff, vBetaff, deltaVAlpha, deltaVBeta, vAlphaRef, vBetaRef;
extern f32 yAlphaRef, yBetaRef, fluxAlphaRef, fluxBetaRef;
extern f32 vaRef_, vbRef_, vcRef_;
extern f32 fluxDS, fluxQS;
extern f32 fluxDSBackEMF, fluxQSBackEMF;
extern f32 fluxAlphaRef, fluxBetaRef;
extern f32 fluxAlphaFiltered, fluxBetaFiltered;
extern f32 pllFluxSFrq;
extern f32 vds;
extern f32 vqs;
extern struct OutputProcessType OutputProcess;
extern f32 IqsRef;
extern f32 outPhaseFpga;
extern f32 spdRegError;
extern f32 spdRegInt;
extern f32 ua1,ub1,uc1;
extern f32 svcSpeedEstPu;
extern f32 iAlphaS, iBetaS;
extern f32 fluxAlphaSDC, fluxBetaSDC;
extern f32 vqs;
extern f32 SlipFrequencyPu;
extern f32 pllFluxSFrqPu;
extern f32 pllBackEmfFrqPu;
extern f32 inputFrqPu;
extern f32 idRef, iqRef;
extern f32 deltaU;
extern f32 deltaSPLL;
extern f32 iNetIn[];
extern f32 iAlphaNetIn, iBetaNetIn;
extern f32 idNetIn, iqNetIn;
extern f32 inputVolFil;
extern f32 idFdb;
extern f32 iqFdb;
extern f32 fluxFdb;
extern f32 fluxRegError;
extern f32 idRegError;
extern f32 iqRegError;
extern f32 syncFrqEst;
extern f32 vaLastUpdate, vbLastUpdate, vcLastUpdate;
extern f32 vaRef, vbRef, vcRef;
extern f32 fluxRegError1;
extern f32 fluxRegErrorTmp;
//extern f32 synchMotorFieldCurrent;
extern u16 speedLoopSpinEnable;
extern struct FLUX_REGULATOR_STR fluxRegData;
extern struct SPEED_REGULATOR_STR spdRegData;
extern u16 encoderLossError;
//extern struct REGULATOR_STR upTransfer;
extern f32 deltaU;
extern f32 deltaSPLL;
//extern f32 iTotalRef;
extern f32 iqsRatedPuLimitLpf;
extern f32 iqsRatedPuLimitL2;
extern f32 iqsRefFiltered;
extern f32 cellGenVolA3Fil;
extern f32 cellGenVolMaxFil;
extern f32 outPowercore;
extern f32 iLossSquare;
#include "m_brake.h"
extern f32 fluxSS, fluxSSaaa;
#include "m_npc.h"
extern struct NPC_DATA npcData;
extern struct REGULATOR_STR npcPi;
extern struct PiDataType npcPiData;
extern f32 unpcFil;
extern f32 npc1Err;
//extern s16 npcSign;
extern BUS_VOTAGE invbusVoltage;
extern THREE_PHASE_CURRENT_SAMPLE filCapCurData;
extern struct CELL_VOLTAGE_REGULATOR_STR cellVoltageRegulator;
extern f32 inputVolDis;
//extern struct REGULATOR_STR upTransfer;
extern     f32 vaRef, vbRef, vcRef;
extern f32 fluxlimitA;
extern f32 asasdsfq;
extern f32 afeFpgaData[3];
//extern u16 lineFluxOrientedEnable;
extern struct UpTransferError upTransferError;
extern struct PHASE_LOCK_LOOP_STR inVolPll2;
extern f32 deltathetavalue;
//extern f32 vaReftest,vbReftest,vcReftest;
extern struct CELL_VOLTAGE_REGULATOR_STR cellVoltageRegulatorBrk;
//extern f32 sinTheta, cosTheta;     // 角度的正余弦值，减少执行时间。
//extern int16 coreFrqHz;
#if DEBUG_DATA_LOG

Uint16 logSel = 13;
//Uint16 logSel = 21;
//Uint16 logSel = 5;
//Uint16 logSel = 43;   // 同步机
u16 tickerLog;
f32 dataLogContinueLogTime = 0.2;   // 在记录命令无效之后再记录_s

f32 *pDebugPara[6] = 
{
    (f32 *)&spdFdb,
    (f32 *)&spdFdb,
    (f32 *)&spdFdb,
    (f32 *)&spdFdb,
    (f32 *)&spdFdb,
    (f32 *)&spdFdb, 
};
u16 debugNum = 6;
extern f32 inputVol;
extern struct PHASE_LOCK_LOOP_STR pllDataInputPrc;
extern struct MAGNETIZING_CURRENT_REG_STR idRegData;
//extern u16 Uvoltage,Vvoltage;
u16 matlabflag;
extern f32 AlphaOutputVol;
extern f32 BetaOutputVol;
extern f32 DeltaPmsmSvc;
extern f32 FrqPmsmsvc;
//extern f32 calVold,calVolq;
extern f32 sampleVoldOb,sampleVolqOb;
extern f32 InitRotorPosition;
//extern f32 vaRefTest_,vbRefTest_,vcRefTest_;
/*
extern f32 iAlphaSLpf,iBetaSLpf;
extern f32 yAlphaSLpf,yBetaSLpf;
extern f32 iAlphaSSG,iBetaSSG;
extern f32 yAlphaSSG,yBetaSSG;
*/
//f32 CCSData[30];
//u16 ccsCnt;
//==============================================================================
//
// 调试函数，
// 将 dataLog.dataIn[] 的数据 保存到 dataLogScope[]中。
// 详细见 DataLogDeal() 函数说明。
// input: dataLog.chNum, dataLog.dataIn[0->], dataLog.trig
//
//==============================================================================
void UpdateDataLog(void)
{
    MiscDataDealAdInt();
    /*

//    if (cfGroup[6] >= 6)   // >=6表示不使能log调试。
//        return;
     if(ccsCnt >= 29)
     {
		ccsCnt = 0;
	 }
	 else
	 {
		ccsCnt++;
	 }
     CCSData[ccsCnt] = outCurData.u;//outVolData.ufpga0;
   */
    if (0 == logSel)
    {
        dataLog.chNum = 6;  // 发给FPGA的电压
        //dataLog.dataIn[0] = _IQtoQ12(vaLastUpdate);
       // dataLog.dataIn[1] = _IQtoQ12(vbLastUpdate);
       // dataLog.dataIn[2] = _IQtoQ12(vcLastUpdate);
       // dataLog.chNum = 3;  // 输出电压采样、输出电流采样
    //    dataLog.dataIn[0] = _IQtoQ12(yAlphaS);//yAlphaS);//(s16)Uvoltage * 0.0001);//inVolData.u);//outVolData.u);
     //   dataLog.dataIn[1] = _IQtoQ12(yAlphaSLpf);//inVolData.v);//outCurData.u);
    //    dataLog.dataIn[2] = _IQtoQ12(yAlphaSSG);//outVolData.v);
      
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.VdsRef);
        //dataLog.dataIn[1] = _IQtoQ12(calVold);
        dataLog.dataIn[2] = _IQtoQ12(sampleVoldOb);
		dataLog.dataIn[3] = _IQtoQ12(OutputProcess.VqsRef);
      //  dataLog.dataIn[4] = _IQtoQ12(calVolq);
        dataLog.dataIn[5] = _IQtoQ12(sampleVolqOb);
	//	dataLog.dataIn[3] = _IQtoQ12(iAlphaS);//BetaOutputVol);//outVolData.ufpga0);
    //    dataLog.dataIn[4] = _IQtoQ12(iAlphaSLpf);//OutputProcess.DeltaS);
    //    dataLog.dataIn[5] = _IQtoQ12(iAlphaSSG);
       /*
        
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(idFdb);
//        dataLog.dataIn[1] = _IQtoQ12(idFdb);
        dataLog.dataIn[2] = _IQtoQ12(vds);
    ///    dataLog.dataIn[2] = _IQtoQ12(vds);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(iqFdb);
//        dataLog.dataIn[1] = _IQtoQ12(idFdb);
//        dataLog.dataIn[2] = _IQtoQ12(vds);
        dataLog.dataIn[5] = _IQtoQ12(vqs);
        */
      //  dataLog.chNum = 6;
       // dataLog.dataIn[0] = _IQtoQ12(adResult[0]/16384.0);
      //  dataLog.dataIn[1] = _IQtoQ12(adResult[1]/16384.0);
      //  dataLog.dataIn[2] = _IQtoQ12(outCurData.w0);
      //  dataLog.dataIn[3] = _IQtoQ12(outCurData.u);
      //  dataLog.dataIn[4] = _IQtoQ12(outCurData.v);
      //  dataLog.dataIn[5] = _IQtoQ12(outCurData.w);
/*
     //   dataLog.chNum = 2;
       dataLog.dataIn[0] = _IQtoQ12(inVolData.u);
     //   dataLog.dataIn[0] = _IQtoQ12(adResult[0]/3276.8);
        dataLog.dataIn[1] = _IQtoQ12(inVolData.v);
      //  dataLog.dataIn[1] = _IQtoQ12(adResult[1]/3276.8);
        dataLog.dataIn[2] = _IQtoQ12(inVolData.w);
      //  dataLog.dataIn[2] =  _IQtoQ12(adResult[0]/3276.8);
	   dataLog.dataIn[3] = _IQtoQ12(outVolData.u);
	    dataLog.dataIn[4] = _IQtoQ12(outVolData.v);
		 dataLog.dataIn[5] = _IQtoQ12(outVolData.w);
*/

//        dataLog.chNum = 3;// 输入压样，原始
//        dataLog.dataIn[0] = _IQtoQ12(inVolData.u0);
//        dataLog.dataIn[1] = _IQtoQ12(inVolData.v0);
//        dataLog.dataIn[2] = _IQtoQ12(inVolData.w0);

      //  dataLog.chNum = 4;  // 输入电压采样
      //  dataLog.dataIn[0] = _IQtoQ12(inVolData.u0);
      //  dataLog.dataIn[1] = _IQtoQ12(inVolData.v0);
      //  dataLog.dataIn[2] = _IQtoQ12(inVolData.w0);
	//	dataLog.dataIn[3] = _IQtoQ12(inVolData.e0);

//        dataLog.chNum = 4;  // 输出电压采样，原始值
//        dataLog.dataIn[0] = _IQtoQ12(outVolData.u0);
//        dataLog.dataIn[1] = _IQtoQ12(outVolData.v0);
//        dataLog.dataIn[2] = _IQtoQ12(outVolData.w0);
//        dataLog.dataIn[3] = _IQtoQ12(outVolData.e0);

//        dataLog.chNum = 4;  // 输出电压采样，始值
//        dataLog.dataIn[0] = _IQtoQ12(outVolData.u);
//        dataLog.dataIn[1] = _IQtoQ12(outVolData.v);
//        dataLog.dataIn[2] = _IQtoQ12(outVolData.w);
//        dataLog.dataIn[3] = _IQtoQ12(outVolData.e0);

//        dataLog.chNum = 3;  // 输出电流采样，原始值
      //  dataLog.dataIn[3] = _IQtoQ12(outCurData.u0);
      //  dataLog.dataIn[4] = _IQtoQ12(outCurData.v0);
     //   dataLog.dataIn[5] = _IQtoQ12(outCurData.w0);

        //dataLog.chNum = 3;  // 输出电流采样
        //dataLog.dataIn[0] = _IQtoQ12(outCurData.u);
        //dataLog.dataIn[1] = _IQtoQ12(outCurData.v);
        //dataLog.dataIn[2] = _IQtoQ12(outCurData.w);
        //  dataLog.chNum = 4;  // 输出电流采样
       //   dataLog.dataIn[0] = _IQtoQ12(cellVoltageRegulator.out);
        //  dataLog.dataIn[1] = _IQtoQ12(cellVoltageRegulator.celVoltageDelta);
        //  dataLog.dataIn[2] = _IQtoQ12(cellVoltageRegulator.celVoltageFdb);
        //  dataLog.dataIn[3] = _IQtoQ12(inputVolDis);
//        dataLog.chNum = 1;  // 输出电流采样
//        dataLog.dataIn[0] = _IQtoQ12(filCapCurData.u);
//        dataLog.dataIn[1] = _IQtoQ12(filCapCurData.v);
//        dataLog.dataIn[0] = _IQtoQ12(filCapCurData.w);

//        dataLog.chNum = 3;  // 输入电流采样
//        dataLog.dataIn[0] = _IQtoQ12(inCurData.u);
//        dataLog.dataIn[1] = _IQtoQ12(inCurData.v);
//        dataLog.dataIn[2] = _IQtoQ12(inCurData.w);

//        dataLog.chNum = 3;  // 输入电流采样
//        dataLog.dataIn[0] = _IQtoQ12(inCurData.u0);
//        dataLog.dataIn[1] = _IQtoQ12(inCurData.v0);
//        dataLog.dataIn[2] = _IQtoQ12(inCurData.w0);

//        dataLog.chNum = 4;
//        dataLog.dataIn[0] = _IQtoQ12(fluxRegError);
//        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.IdsRef);
//        
//        dataLog.dataIn[2] = _IQtoQ12(spdRegError * OutputProcess.Enable * motorPara.iFPuOmegaOne);
//        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef); 

    }
    else if (99 == logSel)
    {
        dataLog.chNum = debugNum;

        dataLog.dataIn[0] = _IQtoQ12( *((f32 *)pDebugPara[0]) );
        dataLog.dataIn[1] = _IQtoQ12( *((f32 *)pDebugPara[1]) );
        dataLog.dataIn[2] = _IQtoQ12( *((f32 *)pDebugPara[2]) );
        dataLog.dataIn[3] = _IQtoQ12( *((f32 *)pDebugPara[3]) );
        dataLog.dataIn[4] = _IQtoQ12( *((f32 *)pDebugPara[4]) );
        dataLog.dataIn[5] = _IQtoQ12( *((f32 *)pDebugPara[5]) );
    }


#if 0
    else if (1 == logSel)
    {
        dataLog.chNum = 4;
        dataLog.dataIn[0] = _IQtoQ12(idRegError);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.VdsRef);
        
        dataLog.dataIn[2] = _IQtoQ12(iqRegError);
        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.VqsRef);
    }

    else if (10 == logSel)
    {
        dataLog.chNum = 2;  // 输出电压采样、输出电流采样
        dataLog.dataIn[0] = _IQtoQ12(outVolData.u);
        dataLog.dataIn[1] = _IQtoQ12(outCurData.u);
    }

    else if (11 == logSel)
    {
        dataLog.chNum = 3;  // 发给FPGA的电压
        dataLog.dataIn[0] = _IQtoQ12(vaRef_);
        dataLog.dataIn[1] = _IQtoQ12(vbRef_);
        dataLog.dataIn[2] = _IQtoQ12(vcRef_);

//        dataLog.chNum = 5;
//        dataLog.dataIn[3] = _IQtoQ12(spdRegData.speedReference * motorPara.iFPuOmegaOne);
//        dataLog.dataIn[4] = _IQtoQ12((f32)coreFrq * (7000.0/(1L<<15)/5000) );
    }
    
    else if (12 == logSel)
    {
        dataLog.chNum = 3;  // 输出电流采样
//        dataLog.dataIn[0] = _IQtoQ12(outCurData.u0);
//        dataLog.dataIn[1] = _IQtoQ12(outCurData.v0);
//        dataLog.dataIn[2] = _IQtoQ12(outCurData.w0);
        dataLog.dataIn[0] = _IQtoQ12(outCurData.u);
        dataLog.dataIn[1] = _IQtoQ12(outCurData.v);
        dataLog.dataIn[2] = _IQtoQ12(outCurData.w);
    }
#endif

#if 1
    else if (11 == logSel)
    {
        dataLog.chNum = 6;  // 发给FPGA的电压
        dataLog.dataIn[0] = _IQtoQ12(outVolData.u);//outVolData.u);
        dataLog.dataIn[1] = _IQtoQ12(outVolData.v);//outVolData.v);
        dataLog.dataIn[2] = _IQtoQ12(outVolData.w);//outVolData.w);
		dataLog.dataIn[3] = _IQtoQ12(AlphaOutputVol);
        dataLog.dataIn[4] = _IQtoQ12(BetaOutputVol);
        dataLog.dataIn[5] = _IQtoQ12(vcLastUpdate);
    }
    else if (12 == logSel)
    {
        dataLog.chNum = 6;  // 发给FPGA的电压
        dataLog.dataIn[0] = _IQtoQ12(outCurData.u0);
        dataLog.dataIn[1] = _IQtoQ12(outCurData.v0);
        dataLog.dataIn[2] = _IQtoQ12(outCurData.w0);
		dataLog.dataIn[3] = _IQtoQ12(outCurData.u);
        dataLog.dataIn[4] = _IQtoQ12(outCurData.v);
        dataLog.dataIn[5] = _IQtoQ12(outCurData.w);
    }
    else if (13 == logSel)
    {
        dataLog.chNum = 6;  // 发给FPGA的电压
        dataLog.dataIn[0] = _IQtoQ12(vaRef_);
        dataLog.dataIn[1] = _IQtoQ12(vbRef_);
        dataLog.dataIn[2] = _IQtoQ12(vcRef_);
       // dataLog.dataIn[3] = _IQtoQ12(vaRefTest_);
       // dataLog.dataIn[4] = _IQtoQ12(vbRefTest_);
        //dataLog.dataIn[5] = _IQtoQ12(vcRefTest_);
        //dataLog.dataIn[0] = _IQtoQ12(OutputProcess.DeltaSBackEMF);
       // dataLog.dataIn[1] = _IQtoQ12(cosTheta);
       // dataLog.dataIn[2] = _IQtoQ12(OutputProcess.DeltaS);
  //  f32 sinTheta, cosTheta;     // 角度的正余弦值，减少执行时间。
    }
    else if (14 == logSel)
    {
        dataLog.chNum = 3;  // 发给FPGA的电压
        dataLog.dataIn[0] = outputVol.vaPrime;
        dataLog.dataIn[1] = outputVol.vbPrime;
        dataLog.dataIn[2] = outputVol.vcPrime;
    } 
#endif


    else if (2 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
//        dataLog.dataIn[1] = _IQtoQ12(idFdb);
//        dataLog.dataIn[2] = _IQtoQ12(vds);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.VdsRef);
        //dataLog.dataIn[2] = _IQtoQ12(invbusVoltage.add);
        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
//        dataLog.dataIn[4] = _IQtoQ12(iqFdb);
//        dataLog.dataIn[5] = _IQtoQ12(vqs);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.VqsRef);
    }
#if 0
    else if (200 == logSel)
    {
        dataLog.chNum = 6;

        dataLog.dataIn[0] = _IQtoQ12(pllFluxSFrqPu);
        dataLog.dataIn[1] = _IQtoQ12(spdFdb);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.WsFilPu);
        dataLog.dataIn[3] = _IQtoQ12(fluxDS);
        dataLog.dataIn[4] = _IQtoQ12(fluxQS);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.VqsRef);
    }
    else if (201 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.IdsFil);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.IqsFil);
    }
    else if (220 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.Frequency * motorPara.iFPuOmegaOne);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[5] = _IQtoQ12(SpinningLoad.Status * 0.1);
    }
    else if (221 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.Frequency * motorPara.iFPuOmegaOne);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.VqsRef);
    }
    else if (222 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.VdsRef);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.VqsRef);
    }
    else if (223 == logSel)
    {
        extern f32 vqff;
        
        dataLog.chNum = 5;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(iqRegError);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.IqsRef);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.VqsRef);
        dataLog.dataIn[4] = _IQtoQ12(vqff);
        
    }
#endif
    
#if 0
    else if (21 == logSel)
    {
        dataLog.chNum = 6;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.IdsRef);
//        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.Ids);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.IdsFil);
//        dataLog.dataIn[2] = _IQtoQ12(vds);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.VdsRef);

        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.IqsRef);
//        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.Iqs);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.IqsFil);
//        dataLog.dataIn[5] = _IQtoQ12(vqs);
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.VqsRef);
    }
    else if (22 == logSel)
    {
        dataLog.chNum = 4;  // 电流环
        dataLog.dataIn[0] = _IQtoQ12(idFdb);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.VdsRef);
        dataLog.dataIn[2] = _IQtoQ12(iqFdb);
        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.VqsRef);
    }
#endif

    else if (4 == logSel)
    {
        dataLog.chNum = 3;  // 异步机，磁链环与速度环，速度反馈为编码器反馈
        dataLog.dataIn[0] = _IQtoQ12(DeltaPmsmSvc);//OutputProcess.DeltaSBackEMF);
        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.DeltaS);
        dataLog.dataIn[2] = _IQtoQ12(InitRotorPosition);
//        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.FluxDS);
      //  dataLog.dataIn[1] = _IQtoQ12(fluxFdb);
      //  dataLog.dataIn[2] = _IQtoQ12(OutputProcess.IdsRef);

      //  dataLog.dataIn[3] = _IQtoQ12(spdRegData.speedReference * motorPara.iFPuOmegaOne);
//        dataLog.dataIn[3] = _IQtoQ12(spdRef);
     //   dataLog.dataIn[4] = _IQtoQ12(spdFdb);
//        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.MotorSpeedFilteredPU);
     //   dataLog.dataIn[5] = _IQtoQ12(OutputProcess.IqsRef);
    }
    else if (41 == logSel)
    {
        dataLog.chNum = 6;  // 异步机，磁链环与速度环
        dataLog.dataIn[0] = _IQtoQ12(fluxRegData.fluxRef);
//        dataLog.dataIn[0] = _IQtoQ12(fluxRegError);
//        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.FluxDS);
        dataLog.dataIn[1] = _IQtoQ12(fluxFdb);
//        dataLog.dataIn[1] = _IQtoQ12(fluxRegErrorTmp);
        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.IdsRef); 


        dataLog.dataIn[3] = _IQtoQ12(spdRegData.speedReference * motorPara.iFPuOmegaOne);
//        dataLog.dataIn[3] = _IQtoQ12(spdRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.MotorSpeedFilteredPU);   // 速度反馈
//        dataLog.dataIn[4] = _IQtoQ12(pllFluxSFrqPu); // 同步频率
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.IqsRef);
    }
    else if (410 == logSel)
    {
        dataLog.chNum = 2;
//        dataLog.dataIn[0] = _IQtoQ12(fluxRegData.fluxRef);
//        dataLog.dataIn[1] = _IQtoQ12(fluxFdb);
//        dataLog.dataIn[2] = _IQtoQ12(OutputProcess.IdsRef); 

//        dataLog.dataIn[3] = _IQtoQ12(spdRegData.speedReference * motorPara.iFPuOmegaOne); 
//        dataLog.dataIn[4] = _IQtoQ12(spdFdb);           // 编码器反馈
//        dataLog.dataIn[5] = _IQtoQ12(pllFluxSFrqPu);    // 同步频率

        dataLog.dataIn[0] = _IQtoQ12(spdFdb);           // 编码器反馈
//        dataLog.dataIn[1] = _IQtoQ12(pllFluxSFrqPu);    // 同步频率
//        dataLog.dataIn[1] = _IQtoQ12(OutputProcess.MotorSpeedFilteredPU);   // 速度反馈
        dataLog.dataIn[1] = _IQtoQ12(svcSpeedEstPu);
    }
#if 0
    else if (141 == logSel)
    {
        extern f32 udcFil;
        extern f32 nbsa;
        
        dataLog.chNum = 6;  // 异步机，磁链环与速度环
        dataLog.dataIn[0] = _IQtoQ12(fluxRegData.fluxRef);
        dataLog.dataIn[1] = _IQtoQ12(udcFil);
        dataLog.dataIn[2] = _IQtoQ12(nbsa); 


        dataLog.dataIn[3] = _IQtoQ12(spdRegData.speedReference * motorPara.iFPuOmegaOne);
//        dataLog.dataIn[3] = _IQtoQ12(spdRef);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.MotorSpeedFilteredPU);   // 速度反馈
//        dataLog.dataIn[4] = _IQtoQ12(pllFluxSFrqPu); // 同步频率
        dataLog.dataIn[5] = _IQtoQ12(OutputProcess.IqsRef);
    }
#endif

#if (INV_TYPE == HW_HD3x)
    else if (111 == logSel)
    {
        dataLog.chNum = 3;
        dataLog.dataIn[0] = _IQtoQ12(invbusVoltage.diff);
        dataLog.dataIn[1] = _IQtoQ12(npcPi.out);
        dataLog.dataIn[2] = _IQtoQ12(npcData.v0);
    }
    else if (112 == logSel)
    {
        dataLog.chNum = 2;
        dataLog.dataIn[0] = _IQtoQ12(invbusVoltage.diff);
        dataLog.dataIn[1] = _IQtoQ12(npcPi.out);
    }
    else if (113 == logSel)
    {
        dataLog.chNum = 3;
        dataLog.dataIn[0] = _IQtoQ12(invbusVoltage.diff);
        dataLog.dataIn[1] = _IQtoQ12(npcPi.out);
        dataLog.dataIn[2] = _IQtoQ12(npcPiData.accumulator);
    }
    else if (114 == logSel)
    {
        dataLog.chNum = 3;
        dataLog.dataIn[0] = _IQtoQ12(cellVoltageRegulatorBrk.celVoltageRef);//invbusVoltage.diff);
        dataLog.dataIn[1] = _IQtoQ12(invbusVoltage.add);//cellVoltageRegulatorBrk.out);
		dataLog.dataIn[2] = _IQtoQ12(spdRegData.minLimit);
    }
    // npcData.v0
    else if (115 == logSel)
    {
        dataLog.chNum = 6;
        dataLog.dataIn[0] = _IQtoQ12(invbusVoltage.diff);
        dataLog.dataIn[1] = _IQtoQ12(npc1Err);
        dataLog.dataIn[2] = _IQtoQ12(npcPi.out);
//        dataLog.dataIn[3] = _IQtoQ12(npcSign*0.01);
		dataLog.dataIn[4] = _IQtoQ12(invbusVoltage.up);
		dataLog.dataIn[5] = _IQtoQ12(invbusVoltage.down);
    }
#endif
    else if (50 == logSel)
    {
        dataLog.chNum = 6;
       // dataLog.dataIn[3] = _IQtoQ12(upTransfer.input * I_TWO_PI);
        dataLog.dataIn[0] = _IQtoQ12(OutputProcess.DeltaSBackEMF);
        dataLog.dataIn[3] = _IQtoQ12(pllBackEmfFrq*0.02*I_TWO_PI);
		dataLog.dataIn[1] = _IQtoQ12(DeltaPmsmSvc);
		dataLog.dataIn[4] = _IQtoQ12(FrqPmsmsvc*0.02*I_TWO_PI);//
		//dataLog.dataIn[4] = _IQtoQ12(idRef);
		//dataLog.dataIn[5] = _IQtoQ12(iqRef);//
       // dataLog.dataIn[2] = _IQtoQ12(atan2(OutputProcess.VdsRef,OutputProcess.VqsRef));
       // dataLog.dataIn[0] = _IQtoQ12(InputProcess.LineFluxVectorAngle);
       // dataLog.dataIn[1] = _IQtoQ12(InputProcess.Frequency * motorPara.iFPuOmegaOne);
      
       // dataLog.dataIn[3] = _IQtoQ12(InputProcess.LineFluxVectorAngle * I_TWO_PI);
       // dataLog.dataIn[4] = _IQtoQ12(deltaSPLL * I_TWO_PI);
       // dataLog.dataIn[3] = _IQtoQ12(OutputProcess.VdsRef);
       // dataLog.dataIn[4] = _IQtoQ12(OutputProcess.VqsRef);
        //dataLog.dataIn[5] = _IQtoQ12(upTransferError.phaseErrorAngle * I_TWO_PI);
    }

#if 0
    else if (5 == logSel)
    {
        dataLog.chNum = 6;
        dataLog.dataIn[0] = _IQtoQ12(CommandGenerator.SpeedReference * motorPara.iFPuOmegaOne);
        dataLog.dataIn[1] = _IQtoQ12(pllFluxSFrqPu);    // 同步频率
        dataLog.dataIn[2] = _IQtoQ12(svcSpeedEstPu);
        
        dataLog.dataIn[3] = _IQtoQ12(OutputProcess.FluxDS);
        dataLog.dataIn[4] = _IQtoQ12(OutputProcess.FluxQS);
        dataLog.dataIn[5] = _IQtoQ12(fluxAlphaS);
        
    } 
#endif
    else
    {
        ;
    }


//    if (coreRunStatus.bit.run)
//    if ((coreRunStatus.bit.run) && (InputProcess.ErmsMax < 0.66))
//    if (
////        1
//        (coreMainCmd.bit.run)
////        && (2 <= SynchTransfer.UpTransferState)
////        && (MAGNETIZING_STATE != DriveControl.State)
//        && (MATLAB_SCOPE_ENABLE)
//       )

    if ((2 == MATLAB_SCOPE_ENABLE) ||
         ((coreMainCmd.bit.run) &&
        //  (2 <= SynchTransfer.UpTransferState)&&
          (1 == MATLAB_SCOPE_ENABLE)
         // &&(coreMainCmd.bit.DCBrakeStatus == 1)
        //  && (SPINNING_LOAD_STATE != DriveControl.State)
          )
          
          
        //                           ||
       //    ((coreMainCmd.bit.run) && 
       //   (3 == MATLAB_SCOPE_ENABLE)) 
 //                                  ||
//          (4 == MATLAB_SCOPE_ENABLE)&& (lineFluxOrientedEnable)
 //                                  ||
//          ((5 == MATLAB_SCOPE_ENABLE)&&(4 <= SynchTransfer.UpTransferState))
          
       )
     //  if(matlabflag == 1)
    {
        tickerLog = 0;
        dataLog.trig = 1;
    }
    else
    {
        tickerLog++;
        if (tickerLog >= dataLogContinueLogTime * OutputProcess.FastLoopFrequency)
        {
            dataLog.trig = 0;
        }
    }
    
//    dataLog.trig = coreRunStatus.bit.run; // coreRunStatus.bit.run, 1
//    dataLog.trig = coreRunStatus.bit.run && (SynchTransfer.UpTransferState > TRANSFER_INIT);

//    dataLog.trig = 1;

 //   DataLogDeal(&dataLog);
}

#elif 1

void UpdateDataLog(void){}

#endif











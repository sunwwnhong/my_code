//==================================================================================================
//
// 快环，慢环处理
// 
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================




#include "m_main.h"
#include "m_input.h"
#include "m_autoTune.h"
#include "m_interface.h"
#include "m_frqSrc.h"
#include "m_spinningLoad.h"
#include "m_interfaceModify.h"
#include "m_cell_bypass.h"
#include "m_error.h"
#include "m_macro_tune.h"
#include "m_speedLoop.h"
#include "m_blackBoxDeal.h"
#include "m_autoTunePmsm.h"
// PC后台观测数据用
#include "Debug.h"
#include "SimpleDebug.h"
#include "AFE_observer.h"
#include "public.h"


// 电流采样相序，改变了好几次，使用宏定义方便以后维护。
#define CUR_PHASE_XINJIANG_YILI_0p9MVA      0   // 新疆伊犁钢铁，0.9MVA，   输入ab，输出ab
#define CUR_PHASE_XINJIANG_YILI_1p4MVA      0   // 新疆伊犁钢铁，1.4MVA，   输入ac，输出-a-c
#define CUR_PHASE_HENAN_SHANXI_XINXING      0   // 山西新星                 输入ac，输出-a-c
#define CUR_PHASE_HENAN_JINGYE_16           0   // 河南敬业钢铁，16#，      输入a-c，输出-a-c
#define CUR_PHASE_HENAN_JINGYE_14_15        0   // 河南敬业钢铁，14#, 15#， 输入ac，输出ac
#define CUR_PHASE_NORMAL                    0   // 上海三环1.6MVA(唐山)，   输入ac，输出ac





#define DEBUG_P_CELL_T1T2_REVERSE   0   // 1-单元的T1，T2取反；0-单元的T1，T2不取反








#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
#pragma CODE_SECTION(GetCurrentResult,  "ramfuncs");
#pragma CODE_SECTION(FastLoopControl,   "ramfuncs");
#pragma CODE_SECTION(GetVoltageResult,  "ramfuncs");
#endif







//#pragma DATA_SECTION(inputProtectMenu, "data_ram");
//#pragma DATA_SECTION(driveSampleMenu, "data_ram");
#pragma DATA_SECTION(fluxCtrlMenu, "data_ram");

#if DEBUG_PRG_IN_RAM
#pragma DATA_SECTION(inputProcessingMenu, "data_ram");
#pragma DATA_SECTION(outVolLine, "data_ram");
#pragma DATA_SECTION(motorPara, "data_ram");
#endif


MotorPara motorPara;                        // 电机参数

THREE_PHASE_SAMPLE inCurData;               // 输入电流采样
THREE_PHASE_SAMPLE inVolData;               // 输入电压采样
THREE_PHASE_SAMPLE outVolData;              // 输出电压采样
THREE_PHASE_CURRENT_SAMPLE outCurData;      // 输出电流采样
THREE_PHASE_CURRENT_SAMPLE filCapCurData;   // 输出滤波器的电容电流采样


struct DriveControlType DriveControl;       // 变频器的状态机，当前运行状态





// 一些性能相关的参数定义
struct CURRENT_LOOP_MENU currentLoopMenu;               // 电流环参数
struct SPEED_LOOP_MENU speedLoopMenu;                   // 速度环相关参数
struct FLUX_CTRL_MENU fluxCtrlMenu;                     // 磁链控制相关参数
struct FLUX_STATOR_OBSERVER_MENU fluxStatorObserverMenu;// 定子磁链观测参数
struct CELL_MENU cellMenu;                              // 单元参数
struct INPUT_PROTECT_MENU inputProtectMenu;             // 输入保护参数
struct DRIVE_PARAMETER_MENU driveParameterMenu;         // 变频器参数
struct SPINNING_LOAD_MENU spinningLoadMenu;             // 飞车启动参数
struct SYNC_TRANSFER_MENU syncTransferMenu;             // 同步切换参数
struct DRIVE_SAMPLE_MENU driveSampleMenu;               // 变频器采样相关参数
struct OUTPUT_CONNECTION_MENU outputConnectionMenu;     // 长线驱动参数
struct CTRL_LOOP_TEST_MENU ctrlLoopTestMenu;            // 环路测试参数
struct INPUT_PROCESSING_MENU inputProcessingMenu;       // 输入处理参数
struct HIGH_STARTING_TORQUE_MENU highStartingTorqueMenu;// 高启动转矩参数
extern union ROTOR_POSITION_REG RotorPositionPwmReg;


f32 outPhase;
f32 outPhaseStep;
f32 coreUpperTorque;
f32 upperTorqueRegen;
f32 pllFluxSFrqPu;
f32 pllBackEmfFrqPu;
f32 inputFrqPu;
extern int32 frqMotorRun;
extern Uint16 coreCarrierFrq;
extern u16 masterOrSlave;
extern u16 secondVersionFlag;

extern f32 AlphaOutputVol;
extern f32 BetaOutputVol;

bool busOverFlag = false;
bool busMidOverFlag = false;

void BusVolProtectFun(void);
void GetCurrentResult(void);
void SlowLoopControl(void);
extern void ReadAd7606Result(void);
extern void AFEUpdateFpgaVoltageData(void);
extern void LAFEUpdateFpgaVoltageData(void);

extern void uvwOutCurrentCalc(void);

extern void  VolRegulator(void);
extern void DecouplePLL(void);
extern void CurrentDecouple(void);
extern void GridAsynValueCalc(void);
extern void GridPLLOKChk(void);
extern void CurrentRefCalc(void);
extern void AfeFastLoop(void);
extern void LAfeDutyCal(void);

extern void OutputVoltageSample(void); 
extern void OutputVoltageIntegration(void);





#define I_OFFSET_K  (_IQ18(0.02))
//f32 I_OFFSET_K = _IQ18(0.02);
//BURR_FILTER_STRUCT iuBurrFilter;
//BURR_FILTER_STRUCT ivBurrFilter;
#define CUR_MAX     _IQ(64.0)


#define I_TOTAL_FILTER_T    250             // 电流显示滤波时间, _ms
#define VOLTAGE_FILTER_T    200             // 电压显示滤波时间, _ms
#define INPUT_VOL_LPF_TIME  500              // 输入电压显示滤波时间，_ms 
#define VOL_DIS_MIN         (200.0/10000)
#define I_TOTAL_FILTER_Td_T 50              // 反时限过载保护电流滤波时间, _ms




f32 ai1SampleFil, ai1SampleFilNew;
f32 ai2SampleFil, ai2SampleFilNew;
///f32 ai3SampleFil, ai3SampleFilNew;



#if (INV_TYPE == HW_HD3x)
BUS_VOTAGE invbusVoltage;   // INV母线电压采样

#if (HW_CELL_ALL_FUNC == HW_CELL)   // 大样机

f32 midMax = 280.0/4666.9;            // 中点偏差超过_时，报中点偏差过大故障
f32 udcMax = 5200.0/4666.9;           // 母线电压超过_时，报过压故障
f32 udcHalfoverMax = 2600/4666.9;     // 半母线电压过压，报故障，不跳高压
f32 udcOverHalfLimit = 2800.0/4666.9; // 半母线超过_，报故障，跳高压
f32 udcOverVolLimit = 5600.0/4666.9;  // 母线超限，跳高压 

#elif 1                               // 小样机
f32 midMax = 40.0/537.4;              // 中点偏差超过_时，报中点偏差过大故障
f32 udcMax = 650.0/537.4;             // 母线电压超过_时，报过压故障
f32 udcHalfoverMax = 340.0/537.4;     // 半母线电压过压，报故障，不跳高压
f32 udcOverHalfLimit = 370.0/537.4;   // 半母线超过_，报故障，跳高压
f32 udcOverVolLimit = 750.0/537.4;    //母线超过_,报故障，跳高压

#endif


f32 npcDiffAo;              // 转换成0.1对应AO 10V

f32 unpcFil= 0.0001;               // 中点偏差，_，滤波值，显示使用
f32 udcFil = 0.0001;                 // 母线电压，_，滤波值，显示使用


// 报故障，小滤波
f32 unpc1;
f32 udc1;
f32 up1;        // 上母线，小滤波
f32 down1;
u16 udcHalfOverFlag;
f32 udcHalfOverVol;
f32 udcOverVol;
u16 udcOverFlag;
extern f32 coreErrorInfo;



#define AD7606_FPGA_UR      (adResultFpga[0])  //输出电压
#define AD7606_FPGA_US      (adResultFpga[1])
#define AD7606_FPGA_UT      (adResultFpga[2])
#define AD7606_FPGA_UPO     (adResultFpga[3]) //母线电压
#define AD7606_FPGA_UNO     (adResultFpga[4])
#define AD7606_FPGA_NTC1    (adResultFpga[5])  // 输入电压
#define AD7606_FPGA_NTC2    (adResultFpga[6])
#define AD7606_FPGA_NTC3    (adResultFpga[7])

#endif


//f32 sampleIu,sampleIv;
//==============================================================================
//
// 输入电流、输出电流采样
//
//==============================================================================
void GetCurrentResult(void)
{
    f32 a, b, c;                        // 并联方案:控制电流
 //   f32 aParaInv, bParaInv, cParaInv;   // 并联方案:显示电流
/*
#if (INV_TYPE == HW_HD90)
//-----------------------------------------------------------------
// 输入电流采样
//
// 大样机曾经为abc
// 后来改为acb
// 2012年8月初，哈尔滨9台，采样了AC，接到IO板的AC。
//


// 输入电流
 //   a = (f32)((s16)(DSP_AD_IN_IR - 2048)) * inCurData.scaler;
//    b = (f32)((s16)(DSP_AD_IN_IS - 2048)) * inCurData.scaler;
//    c = -(a+b);

//    inCurData.u0 = a;
//    inCurData.v0 = b;
//    inCurData.w0 = c;

// 顺序转换
#if (HW_CELL_PART_FUNC != HW_CELL)  // 大样机，全功能小样机

#if 0       // 0.9MVA新疆伊犁钢铁
    inCurData.u = a;
    inCurData.v = b;
    inCurData.w = c;
#elif 1     // 河北敬业钢铁，斯可络72A
    inCurData.u = a;
    inCurData.v = c;
    inCurData.w = b;
#endif

#elif 1                             // 小样机

    inCurData.u = a;
    inCurData.v = b;
    inCurData.w = c;
    
#endif
*/
//-----------------------------------------------------------------
//#elif (INV_TYPE == HW_HD3x)
// 电机电流采样
 //   a = (f32)((int16)DSP_AD_IU2 - 2048) * filCapCurData.scaler;
 //   b = (f32)((int16)DSP_AD_IV2 - 2048) * filCapCurData.scaler;
 //   filCapCurData.u0 = a;
 //   filCapCurData.v0 = b;
//    filCapCurData.w0 = -(a + b);

// 零漂处理
   // if (!coreRunStatus.bit.run)
   // {
   //     filCapCurData.offsetU += _IQ18mpy(I_OFFSET_K, a - filCapCurData.offsetU);
    //    filCapCurData.offsetV += _IQ18mpy(I_OFFSET_K, b - filCapCurData.offsetV);
   // }
    
  //  a = a - filCapCurData.offsetU;     // 减去零漂
  //  b = b - filCapCurData.offsetV;     // 减去零漂
  //  c = -(a + b);
    
  //  filCapCurData.u = a;
  //  filCapCurData.v = c;
  //  filCapCurData.w = b;
//#endif

//-----------------------------------------------------------------
// 输出电流采样
/*
    if (masterOrSlave)
    {
        if (!PARA_WAY_SEL)
        {
            a = (f32)((int32)AD7606_IU_PARA_INV - 0) * outCurData.scaler;
            b = (f32)((int32)AD7606_IV_PARA_INV - 0) * outCurData.scaler;

            aParaInv = (f32)((int16)AD7606_IU - 0) * outCurData.scaler;
            bParaInv = (f32)((int16)AD7606_IV - 0) * outCurData.scaler;
        }
        else
        {
            a = (f32)((int16)AD7606_IU - 0) * outCurData.scaler;
            b = (f32)((int16)AD7606_IV - 0) * outCurData.scaler;

            aParaInv = (f32)((int32)AD7606_IU_PARA_INV - 0) * outCurData.scaler;
            bParaInv = (f32)((int32)AD7606_IV_PARA_INV - 0) * outCurData.scaler;
        }

        outCurData.u0ParaInv = aParaInv;
        outCurData.v0ParaInv = bParaInv;
        outCurData.w0ParaInv = -(aParaInv + bParaInv);

        if (!coreRunStatus.bit.run)
        {
            outCurData.offsetUParaInv += _IQ18mpy(I_OFFSET_K, aParaInv - outCurData.offsetUParaInv);
            outCurData.offsetVParaInv += _IQ18mpy(I_OFFSET_K, bParaInv - outCurData.offsetVParaInv);
        }
        
        aParaInv = aParaInv - outCurData.offsetUParaInv;
        bParaInv = bParaInv - outCurData.offsetVParaInv;
        cParaInv = -(aParaInv + bParaInv);

#if (HW_CELL_PART_FUNC != HW_CELL)
        outCurData.uParaInv = aParaInv;
        outCurData.vParaInv = cParaInv;
        outCurData.wParaInv = bParaInv;
#elif 1
        outCurData.uParaInv = aParaInv;
        outCurData.vParaInv = bParaInv;
        outCurData.wParaInv = cParaInv;
#endif
    }
    else
*/
	
    {
    #if (INV_MODEL == INV_3300)
		//a = (f32)(0 - (int16)(AD7606_IU)) * outCurData.scaler;
		//b = (f32)(0 - (int16)(AD7606_IV)) * outCurData.scaler;
		
		if(funcCode.code.HallDirection == 0)//霍尔方向朝外
    	{
			a = (f32)((int16)(AD7606_IU) - 0) * outCurData.scaler;
			b = (f32)((int16)(AD7606_IV) - 0) * outCurData.scaler;
		}
		else
		{
			a = (f32)(0 - (int16)(AD7606_IU)) * outCurData.scaler;
			b = (f32)(0 - (int16)(AD7606_IV)) * outCurData.scaler;
		}
		
	#elif (INV_MODEL == INV_1140)
		//a = (f32)((int16)AD7606_IU - 0) * outCurData.scaler;
		//b = (f32)((int16)AD7606_IV - 0) * outCurData.scaler;
		
		if(funcCode.code.HallDirection == 0)//霍尔方向朝外
    	{
			if(cellMenu.cellVoltage == 3)//整流
			{
			   a = (f32)(0 - (int16)AD7606_IU) * outCurData.scaler;
			   b = (f32)(0 - (int16)AD7606_IV) * outCurData.scaler;
			}
			else//逆变
			{
				a = (f32)((int16)AD7606_IU - 0) * outCurData.scaler;
				b = (f32)((int16)AD7606_IV - 0) * outCurData.scaler;
			}
		}
		else//霍尔方向朝内
		{
			if(cellMenu.cellVoltage == 3)//整流
			{
				a = (f32)((int16)AD7606_IU - 0) * outCurData.scaler;
				b = (f32)((int16)AD7606_IV - 0) * outCurData.scaler;
			}
			else//逆变
			{
				a = (f32)(0 - (int16)AD7606_IU) * outCurData.scaler;
			    b = (f32)(0 - (int16)AD7606_IV) * outCurData.scaler;
			}
		}
	#endif
        //sampleIu=(f32)((int16)AD7606_IU)/1000;
        //sampleIv=(f32)((int16)AD7606_IV)/1000;
    //////    a = -(f32)((int16)DSP_AD_IU1 - 2048) * outCurData.scaler;
    ///////    b = -(f32)((int16)DSP_AD_IV1 - 2050) * outCurData.scaler;
      // b = -(f32)((int16)DSP_AD_NTC1 - 2065) * outCurData.scaler;
    }
/*
#if DEBUG_P_CELL_T1T2_REVERSE
    a = -a;
    b = -b;
#endif
*/
    outCurData.u0 = a;
	outCurData.v0 = b;
    outCurData.w0 = -(a + b);
    

// 零漂处理,目前有问题，无穷大
    if (!coreRunStatus.bit.run)
    {
        outCurData.offsetU += _IQ18mpy(I_OFFSET_K, a - outCurData.offsetU);
        outCurData.offsetV += _IQ18mpy(I_OFFSET_K, b - outCurData.offsetV);
    }
    
    a = (a - outCurData.offsetU) * 1.0;     // 减去零漂
    b = (b - outCurData.offsetV) * 1.0;     // 减去零漂
    c = -(a + b);

// 根据硬件进行的转换
// 注意: 发货机器的输出电流采样多次变化，软件要相应修改。
// 2011年贵州样机，abc
// 72A样机，abc
//
// 2012年修改了
// 0.9MVA新疆样机，abc
// 1.4MVA新疆样机，-a-c-b
// 2012年5月前，均为-a-c-b
// 2012年6月1日以后，均为acb
// 小样机均为abc
// HD3x小样机为abc。
//
// 2014年5月6日
// HD90全功能小样机，与大样机一致。
// HD90非全功能小样机，abc。目前仅1台(4#，四象限小样机)
// 凯撒小样机已经改为跟凯撒大样机一致(-c-a-b)。

/*
#if (HW_CELL_PART_FUNC != HW_CELL)  // 大样机，全功能小样机

#if 0       // 0.9MVA新疆伊犁钢铁，斯可络72A
    outCurData.u = a;
    outCurData.v = b;
    outCurData.w = c;
#elif 0     // 1.4MVA新疆伊犁钢铁，河北敬业钢铁
    outCurData.u = -a;
    outCurData.v = -c;
    outCurData.w = -b;
#elif (INV_TYPE == HW_HD90) // 上海三环1.6MVA(唐山)
    outCurData.u = a;
    outCurData.v = c;
    outCurData.w = b;
#elif (INV_TYPE == HW_HD3x) // HD3x，怀疑有问题。
#if (HD33_A == HD33_A_BIG)
 */   
    outCurData.u = a;
    outCurData.v = b;
    outCurData.w = c;
	/*
#else 
    outCurData.u = -c;
    outCurData.v = -a;
    outCurData.w = -b;
#endif
#endif

#elif 1                             // 非全功能小样机

    outCurData.u = a;
    outCurData.v = b;
    outCurData.w = c;
    
#endif
*/
//-----------------------------------------------------------------



//-----------------------------------------------------------------
// DSP的AI采样
// 有一个小的滤波
#if !DEBUG_PRG_IN_RAM
   
   // ai1SampleFil = LPF_K((f32)DSP_AD_AI3, ai1SampleFil, 10);
    ai2SampleFil = LPF_K((f32)DSP_AD_AI2, ai2SampleFil, 10);
	ai1SampleFil = LPF_K((f32)DSP_AD_AI1, ai1SampleFil, 10);

#if 0       // AI_AO多机运行时使用
    ai1SampleFilNew = (f32)((s16)ai1SampleFil - 2048) * 1.0 / 1024;
    ai2SampleFilNew = ai2SampleFil;
#elif 1
    ai1SampleFilNew = ai1SampleFil;
    ai2SampleFilNew = ai2SampleFil;
#endif

#endif
}

//==============================================================================
//
// 
// HD3x的母线电压过压,超限故障判断函数
// 
//
//==============================================================================
void BusVolProtectFun()
{   
   // midMax = 0.06;
	if(funcCode.code.MidDevErThreshold == 0)
	{
		midMax = 0.16;
	}
	else
	{
		midMax = (f32)funcCode.code.MidDevErThreshold * 0.01;
	}
    if (fabs(unpc1) >= midMax)       // 中点偏差过大故障
    {
        busMidOverFlag = true;
        coreErrorInfo = fabs(unpc1 * driveParameterMenu.ratingInputVoltage * SQRT2);
    }
#define NPC_ERR_VAL   0.01
    else if (fabs(unpc1) <= (midMax - NPC_ERR_VAL))
    {
        busMidOverFlag = false;
    }
    if ((!coreErrorCode) && (busMidOverFlag == true))
    { 
        if (funcCode.code.ErPNDevOrOutLackPhaseSel == 1)
        {
           coreErrorCode = ALARM_LOSE_PHASE_OUTPUT;  
        }
        else
        {
           coreErrorCode = ERROR_UNPC_VOL;//中点偏差过大故障ERR104
        }  
    }
    if ((udc1 >= udcMax) && (coreRunStatus.bit.run))              // 母线电压过压
    { 
        busOverFlag = true;
        coreErrorInfo = (f32)(((u16)(udc1*driveParameterMenu.ratingInputVoltage * SQRT2))
                             & 0x3FFF);
        
    }
    else if ((up1 >= udcHalfoverMax) && (coreRunStatus.bit.run))             // 上半母线电压过压
    {
        busOverFlag = true;
        coreErrorInfo = (f32)(10000 + (((u16)(up1*driveParameterMenu.ratingInputVoltage * SQRT2))
                            & 0x3FFF));
    }

    else if ((down1 >= udcHalfoverMax) && (coreRunStatus.bit.run))            // 下半母线电压过压
    {
        busOverFlag = true;
        coreErrorInfo = (f32)(20000 + (((u16)(down1*driveParameterMenu.ratingInputVoltage * SQRT2)) 
                             & 0x3FFF));
    }
#define  UDC_DELAY_VAL       0.05
#define  HALF_UDC_DEALY_VAL  0.04
    else if ((udc1 <= (udcMax - UDC_DELAY_VAL)) && (up1 <= (udcHalfoverMax - HALF_UDC_DEALY_VAL)) 
	          && (down1 <= (udcHalfoverMax - HALF_UDC_DEALY_VAL)) || (!coreRunStatus.bit.run))
    {
        busOverFlag = false;
    }

    if ((!coreErrorCode) && (busOverFlag == true))
    {
        coreErrorCode = ERROR_OV_ACC_SPEED; //母线过压故障
    }

    //下面故障为 母线电压超限， 需要跳高压


    if (up1 >= udcOverHalfLimit)      // 上半半母线超限
    {
        udcHalfOverFlag = 1;
        udcHalfOverVol = (f32)(10000 + (0x3FFF &(u16)(up1*driveParameterMenu.ratingInputVoltage * SQRT2)));
    }
    else if (down1 >= udcOverHalfLimit)   // 下半半母线超限
    {
        udcHalfOverFlag = 1;
        udcHalfOverVol = (f32)(20000 +(0x3FFF &(u16)(down1*driveParameterMenu.ratingInputVoltage * SQRT2)));
    }
    else if (udc1 > udcOverVolLimit)   // 母线超限
    {
        udcHalfOverFlag = 1;
        udcHalfOverVol = (udc1*driveParameterMenu.ratingInputVoltage * SQRT2);        
    }
    else
    {
       udcHalfOverFlag = 0;
    }
}

//==============================================================================
//
// 输入电压(V)、输出电压(V.sec)采样
// HD3x的母线电压(PO, NO)采样
// 
// 均为三相采样，需要去除零序分量
//
//==============================================================================
f32 udcFil1;
f32 udcFil2;
u16 sampleTest;
f32 adConvvalue,sampledata;
f32 sampleBusvot;
f32 sampleINvot,sampleINvot1;
f32 AlphainputVol,BetainputVol;

void GetVoltageResult(void)
{
    f32 a = 0.0;
	f32 b = 0.0;
	f32 c = 0.0;
//#if (INV_TYPE == HW_HD3x)
    f32 diff, sum;
//#endif
#if (INV_MODEL == INV_3300)
	if(motorControlOtherEnable.bit.inVol == 1)//有输入电压采样
	{
	    if( driveParameterMenu.ratingInputVoltage != 0)
		{
			inVolData.ufpga0 = -driveSampleMenu.inVolReviseCoef *24000.0* ((f32)((s16)interfaceRam[FPGA_REG_SampleCh1]))  *0.32*(1.0/32768.0)
			          /(driveParameterMenu.ratingInputVoltage);
			inVolData.vfpga0 = driveSampleMenu.inVolReviseCoef * 24000.0* ((f32)((s16)interfaceRam[FPGA_REG_SampleCh2]))  *0.32*(1.0/32768.0)
			          /(driveParameterMenu.ratingInputVoltage);
			sampleINvot=((f32)((s16)interfaceRam[FPGA_REG_SampleCh1]))/10000.0;
			sampleINvot1=((f32)((s16)interfaceRam[FPGA_REG_SampleCh2]))/10000.0;
		}
	    inVolData.wfpga = (inVolData.ufpga0 + inVolData.vfpga0);

	    AlphainputVol = SQRT3 * 0.2357022603 * (inVolData.ufpga0 + inVolData.wfpga);//SQRT2 / 6.0
	    BetainputVol =  SQRT3 * 0.4082482905 * inVolData.vfpga0;//SQRT6 / 6.0

	    IClarkeCalcMacro(a, b, c, AlphainputVol, BetainputVol);

	    inVolData.e0 = (a + b + c) * (1.0/3);
	    // Zero Sequence Compensation
	    inVolData.u = a - inVolData.e0;
	    inVolData.v = b - inVolData.e0;
	    inVolData.w = c - inVolData.e0;
	}
	else
	{
		inVolData.e0 = 0.0;
	    inVolData.u = 0.0;
	    inVolData.v = 0.0;
	    inVolData.w = 0.0;
	}
#elif (INV_MODEL == INV_1140)
// 输入电压
    a = (f32)((int16)(DSP_AD_UR - 2048)) * inVolData.scaler;
    b = (f32)((int16)(DSP_AD_US - 2048)) * inVolData.scaler;
    c = (f32)((int16)(DSP_AD_UT - 2048)) * inVolData.scaler;

    inVolData.e0 = (a + b + c) * (1.0/3);
// Zero Sequence Compensation
    inVolData.u = a - inVolData.e0;
    inVolData.v = b - inVolData.e0;
    inVolData.w = c - inVolData.e0;
#endif
/*
#elif (INV_TYPE == HW_HD3x)
*/
    {
     // adConvvalue = (f32)((s16)adResultFpga[0]);
	  
     // if(adConvvalue >= 2000)
      //{
			sampleTest++;
			//sampledata = adConvvalue;
	 // }
   //   a = (f32)((int16)(AD7606_FPGA_NTC1)) * inVolData.scaler;
  //    c = (f32)((int16)(AD7606_FPGA_NTC2)) * inVolData.scaler;
  //    b = (f32)((int16)(AD7606_FPGA_NTC3)) * inVolData.scaler;
	//	sampledata = a;
  //    inVolData.e0 = (a + b + c) * (1.0/3);
     // inVolData.e0 = (inVolData.u0 + inVolData.v0 + inVolData.w0) * (1.0/3.0);
        // 新的HD33的输入电压采样板，采样相电压
   //   inVolData.u = a - inVolData.e0;
   //   inVolData.v = b - inVolData.e0;
   //   inVolData.w = c - inVolData.e0;
      ////  inVolData.u = inVolData.u0 - inVolData.e0;
      ////  inVolData.v = inVolData.v0 - inVolData.e0;
      ///  inVolData.w = inVolData.w0 - inVolData.e0;
       // inVolData.u = 0;
       // inVolData.v = 0;
       // inVolData.w = 0;
 	}
//#endif
   // inVolData.u0 = 0;
   // inVolData.v0 = 0;
    //inVolData.w0 = 0;
   // inVolData.u0 = a;
  //  inVolData.v0 = b;
  //  inVolData.w0 = c;


// 输出电压
   //   a = (f32)((int16)(AD7606_FPGA_UR)) * outVolData.scaler;
   //   b = (f32)((int16)(AD7606_FPGA_US)) * outVolData.scaler;
   //   c = (f32)((int16)(AD7606_FPGA_UT)) * outVolData.scaler;
  //  a = (f32)((int16)(DSP_AD_INTER_U - 2048)) * outVolData.scaler;
  //  b = (f32)((int16)(DSP_AD_INTER_V - 2048)) * outVolData.scaler;
 //   c = (f32)((int16)(DSP_AD_INTER_W - 2048)) * outVolData.scaler;
	/*
#if DEBUG_P_CELL_T1T2_REVERSE
    a = -a;
    b = -b;
    c = -c;
#endif
*/
 //   outVolData.e0 = (a + b + c) * (1.0/3);
// Zero Sequence Compensation
 //   outVolData.u = a - outVolData.e0;
 //   outVolData.v = b - outVolData.e0;
 //   outVolData.w = c - outVolData.e0;

 //   outVolData.u0 = a;
 //   outVolData.v0 = b;
 //   outVolData.w0 = c;
    

#if (INV_TYPE == HW_HD3x)
// HD3x母线电压
    // 母线电压使用HD3x的采样板进行采样，AD7606->CPLD->FPGA
  //  a = (f32)((int16)AD7606_FPGA_UPO) * invbusVoltage.scaler;
  //  b = (f32)((int16)AD7606_FPGA_UNO) * invbusVoltage.scaler;
#if (INV_MODEL == INV_3300)
    a = ((f32)((s16)interfaceRam[FPGA_REG_SampleCh4 ])) * invbusVoltage.scaler;//以变频器额定输入电压FF-16*sqrt(2)为基值得标幺值
    b = -((f32)((s16)interfaceRam[FPGA_REG_SampleCh5])) * invbusVoltage.scaler;
    sampleBusvot= ((f32)((s16)interfaceRam[FPGA_REG_SampleCh4 ]))/5000.0;
#elif (INV_MODEL == INV_1140)
   a = (f32)((int16)DSP_AD_UPO) * invbusVoltage.scaler;//以变频器额定输入电压FF-16*sqrt(2)为基值得标幺值
   b = (f32)((int16)DSP_AD_UNO) * invbusVoltage.scaler;
#endif


    invbusVoltage.up = a;
    invbusVoltage.down = b;

//    invbusVoltage.diff = a - b;      // 中点偏差
//    invbusVoltage.add  = a + b;      // 母线电压   FF-16 输入V 时，对应的标幺。此时a ， b 应该各为1200V ，及为0.5
    diff = a - b;
    sum = a + b;
#define NPC_DIFF_FILTER_MAX     (400/4666.9)
//    if (fabs(diff - invbusVoltage.diff) <= NPC_DIFF_FILTER_MAX)     // 滤除突变的母线电压，可能要改为0.03
    {
        invbusVoltage.diff = diff;
        invbusVoltage.add = sum;
    }
    unpcFil = LPF_T(invbusVoltage.diff, unpcFil, VOLTAGE_FILTER_T/1000.0, OutputProcess.FastLoopSamplePeriod);
    udcFil =  LPF_T(invbusVoltage.add,  udcFil,  VOLTAGE_FILTER_T/2000.0, OutputProcess.FastLoopSamplePeriod);
    udcFil2 = LPF_T(invbusVoltage.add,  udcFil2,  0.003, OutputProcess.FastLoopSamplePeriod);
   // udcFil = GetMin(udcFil1, udcFil2);

    npcDiffAo = invbusVoltage.diff * 10;    // 转换成0.1对应AO 10V
    
// 报故障，小滤波
#define NPC_VOL_ERR_T   5   // _ms  5
    unpc1 = LPF_T(diff, unpc1, NPC_VOL_ERR_T/1000.0, OutputProcess.FastLoopSamplePeriod);//fabs(diff);
    udc1  = LPF_T(sum,  udc1,  NPC_VOL_ERR_T/1000.0, OutputProcess.FastLoopSamplePeriod);//sum;
	up1   = LPF_T(fabs(invbusVoltage.up),  up1,  NPC_VOL_ERR_T/1000.0, OutputProcess.FastLoopSamplePeriod);//fabs(invbusVoltage.up);
    down1 = LPF_T(fabs(invbusVoltage.down),  down1,  NPC_VOL_ERR_T/1000.0, OutputProcess.FastLoopSamplePeriod);//fabs(invbusVoltage.down);
 
#endif
}



extern u16 hwCellFlag;
extern Uint16 invIOCSetpoint;
extern Uint16 iocDaSet;
//==============================================================================
//
// 更新输入电流、输入电压、输出电流、输出电压的采样系数
//
//==============================================================================
void UpdateAdPara(void)
{
    //f32 KOutVolMagNew;
    f32 rOutCurrent;
    f32 kOpOutCurrent;
    static f32 outCurData_scaler;
    static f32 outCurData_ocScaler;
    static f32 filCurData_scaler;
  //  f32 rInCurrent;
 //   f32 kOpInCurrent;
    //static f32 inCurData_scaler;
    f32 kOpInVol;
    f32 rVol;
    f32 inVolR;
    static f32 inVolData_scaler;
    static f32 outVolData_scaler;
#if (INV_TYPE == HW_HD3x)
    static f32 invbusVoltage_scaler;
#endif

    f32 tmp;

    if (!coreRunStatus.bit.run)
    {
//    %*******************************************************************************
//    % 输出电流采样系数的计算
//    outCurRes2 = 200;
//    outCurRes34 = 1 / (1/20e3 + 1/400e3);
//    rOutCurrent = outCurResOhm / (outCurRes2 + outCurRes34 + outCurResOhm) * outCurRes34;
//    kOpOutCurrent = (1.0/20.0) / ((380.0*21.1/(380.0+21.1)) / ((380.0*21.1/(380.0+21.1)) + 380.0)); % 输出电流采样的运放倍数
//
//    rOutCurrent = kOpOutCurrent * rOutCurrent;
//    % 2000A -- 1A -- 1*Ri V -- Ri/10*32768
//    % 电流PU值 = AD_RESULT / (Ri/10*32768) * (2000) / (2^0.5*ratingOutputCurrent)
//    outCurData_scaler = outCurReviseCoef * outCTRatio / (rOutCurrent/10*32768) / (2^0.5*ratingOutputCurrent) * (2^12)
//
//=================================================================================================================
/*  最新输出电流采样系数  以IU1 为例
    rOutCurrent =  1/(1/ R1219 + 1/(9530 + 200));
    kOpOutCurrent = 2.43/9.53 * 9.53 / 9.73 = 2.43 / 9.73;//输出电流运放倍数
    rOutCurrent = rOutCurrent * kOpOutCurrent;

    X /outCTRatio    ----- * r1219 * rOutCurrent - 1.5V = (AD_RESULT - 2048) / 2048 * 3.0V 
    Xpu = X/(ratingOutputCurrent * SQRT2);

    =>  Xpu = (AD_RESULT - 2048) / 2048 * 3.0V  * outCTRatio / rOutCurrent * (ratingOutputCurrent * SQRT2);
    =>  Xpu = (AD_RESULT - 2048) * outCurData_scaler;
    => outCurData_scaler = outCurReviseCoef * 3.0 * outCTRatio / 2048.0 / rOutCurrent / (ratingOutputCurrent * SQRT2);

    



*/
//    % 输入电流采样系数的计算
//    rInCurrent = 1/(1/inCurResOhm+1/9550);
//    kOpInCurrent = 2/5.49;      % 输入电流采样的运放倍数
//    rInCurrent = kOpInCurrent * rInCurrent;
//    % 3000A -- 1A -- 1*Ri V -- Ri/3.0*2048
//    % 电流PU值 = AD_RESULT / (Ri/3.0*2048) * (3000) / (2^0.5*ratingInputCurrent)
//    inCurData_scaler = inCurReviseCoef * inCTRatio / (rInCurrent/3.0*2048.0) / (2^0.5*ratingInputCurrent) * (2^12)
//    %*******************************************************************************
//
//    %*******************************************************************************
//    % 过流点通过DA设定，由过流点设定到DA设定值的系数计算
//    % 过流点(iocSet, 单位0.1%)相对于变频器额定电流，Iinv(需要先转换为A)
//    % DA范围：[-32768,32767] <==> [-10V, +10V]
//    % 过流电流(A)：ioc = (iocSet/1000) * Iinv * 2^0.5
//    % 对应的电压(V)：ioc / outCTRatio * rOutCurrent
//    % DA对应的设定：iocSet * ratingOutputCurrent * 2^0.5 / 1000 / outCTRatio * rOutCurrent / 10 * 32768
//    outCurData_ocScaler = 1/outCurReviseCoef*ratingOutputCurrent*2^0.5/1000/outCTRatio*rOutCurrent/10*32768
//    %******************************************************************************* 

// 输出电流采样系数的计算
/*
#if 0
        rOutCurrent = driveSampleMenu.outCurResOhm * 20000.0 / (driveSampleMenu.outCurResOhm + 20200.0);
        kOpOutCurrent = 1.0;    // 输出电流采样的运放倍数
#elif 1
#define OUT_I_r1    (driveSampleMenu.outCurResOhm)
#define OUT_I_r2    9730.0
//#define OUT_I_r34   (1000.0/(1/20.0 + 1/400.0))
      //  rOutCurrent = OUT_I_r1 / (OUT_I_r1 + OUT_I_r2 + OUT_I_r34) * OUT_I_r34;
     //   kOpOutCurrent = (1.0/20.0) / ((380.0*21.1/(380.0+21.1)) / ((380.0*21.1/(380.0+21.1)) + 380.0));    // 输出电流采样的运放倍数
     rOutCurrent = 1.0 /( 1.0 / driveSampleMenu.outCurResOhm + 1.0 / OUT_I_r2);
	 kOpOutCurrent = 2.43 / 9.73 * rOutCurrent;
//#endif
///*--------------------------- 输出电流采样系数的计算------------------------------------*/
///*       输出电流采样：3.3KV和1140v比例系数一样，仅采样电阻和霍尔比不同，可通过功能码修改                                                                          */
/*
#define OUT_I_r1    (driveSampleMenu.outCurResOhm)//采样电阻 3.3KV默认40K
#define OUT_I_r2    (driveSampleMenu.outCTRatio) //霍尔额定电流，1140里面默认300A，3300默认1000A;
#define OUT_I_r34   (1000.0/(1/20.0 + 1/400.0))

        kOpOutCurrent = OUT_I_r2 / 4.0;
        //kOpOutCurrent = 50.0 / 7.5;

        rOutCurrent = (OUT_I_r1 + 5.1)/OUT_I_r1 * 20.0 /21.0 * 0.5* 10 / 0.39 ;//二代板输出电流

        if (motorPara.ratingCurrent != 0)
        {
            outCurData_scaler =  rOutCurrent * kOpOutCurrent * 0.32*(1.0/16384.0) * 1.0/SQRT2 /motorPara.ratingCurrent;
            filCurData_scaler = outCurData_scaler;
        }
*/
#define OUT_I_r1    (driveSampleMenu.outCurResOhm)
#define OUT_I_r2    (driveSampleMenu.outCTRatio) //霍尔额定电流，1140里面默认300A;
#define OUT_I_r34   (1000.0/(1/20.0 + 1/400.0))

        kOpOutCurrent = OUT_I_r2 / 4.0;

        rOutCurrent = (OUT_I_r1 + 5.1)/OUT_I_r1 * 20.0 /21.0 * 0.5;
		if (motorPara.ratingCurrent != 0)
 		{
            outCurData_scaler =  rOutCurrent * kOpOutCurrent * (10.0/32768 * 1.0/SQRT2 /motorPara.ratingCurrent);
        	filCurData_scaler = outCurData_scaler;
 		}

/*---------------------------过流点系数计算-----------------------------------*/
/*
        if ((OUT_I_r1 != 0)&&(OUT_I_r2 != 0))
        {
           outCurData_ocScaler = 1.0/(rOutCurrent* 0.39 *0.1 * kOpOutCurrent) / 10.60 * 3750.0 * SQRT2 * driveParameterMenu.ratingOutputCurrent * 0.001;
        }
*/
		if ((OUT_I_r1 != 0)&&(OUT_I_r2 != 0))
		{    
		    outCurData_ocScaler = 1.0/(rOutCurrent * kOpOutCurrent) / 10.60 * 3750.0 * SQRT2 * driveParameterMenu.ratingOutputCurrent * 0.001;
		}


//    %*******************************************************************************
//    % 输入电压采样系数的计算
//    rVol = 9.53/2;          % 两个9.53k欧姆的电阻并联
//    rVol = rVol / (inVolResOhm + rVol);
//    % 输入相电压，1PU = 2^0.5*(ratingInputVoltage/3^0.5)
//    kOpInVoltage = 2.49/5.49;   % 输入电压的运放放大系数
//    inVolData_scaler = inVolReviseCoef*(3.0/2048.0)/rVol/kOpInVoltage/(2^0.5*(ratingInputVoltage/3^0.5)) * 2^10
//
//    % 输出电压采样系数的计算
//    rVol = 9.53/2;          % 两个9.53k欧姆的电阻并联
//    rVol = rVol / (outVolResOhm + rVol);
//    KOutVolMag = 1.20411372479981;% 输出电压伏秒电路，输入输出的幅值比例，50Hz时
//    % 输出相电压，1PU = 2^0.5*(ratingVoltageMotor/3^0.5)
//    outVolData_scaler = outVolReviseCoef*(1/KOutVolMag)*(10.0/32768.0)/rVol * (ratingFrqMotor / 50.0) /(2^0.5*(ratingVoltageMotor/3^0.5)) * 2^14
//    %*******************************************************************************
/*
      输出电压采样电路划换算系数
      rVol = 9.53/2;          % 两个9.53k欧姆的电阻并联
      rVol = rVol / (outVolResOhm + rVol);
      运放比例系数:  
      kGain = (2.74 * 2.43 /(2.74+2.43)) / 9.53 = 1.28 / 9.53 
      kInator = ((1/jwc)//(R)) / 5.6k;
              = (1/(2*3.1415926* 50.0 * 0.47e-6)) // (56*e3)
              = (6772.5508539515 * 56000)/(56000+6772.550853915) 
              = 6041.85818 /5600
              = 1.078903246
      kGain = kGain * kInator = 0.1449104045767851;
      
      

*/



/*------------------输入电压采样系数--------------------*/
/*---------------------------------------------------*/


#if (INV_MODEL == INV_3300) //3.3KV产品
        inVolR =(1.0*22.0)/(1.0+22.0);//实际为(1.0*22)/(1.0+22)1欧并22欧
        kOpInVol=inVolR/(47.0+inVolR)*2.0/1000.0*8.2*7.5*0.1;
     if(driveParameterMenu.ratingInputVoltage != 0)
       {
        inVolData_scaler = (3.0/2048.0) /kOpInVol/ (driveParameterMenu.ratingInputVoltage *SQRT2);
        }


#elif (INV_MODEL == INV_1140) //1140V产品
     inVolR =(1.0*22.0)/(1.0+22.0);//实际为(1.0*22)/(1.0+22)1欧并22欧
        kOpInVol=inVolR/(10*560+inVolR)*8.2*7.5*0.1;

     if(driveParameterMenu.ratingInputVoltage != 0)
       {
        inVolData_scaler = (3.0/2048.0) /kOpInVol/ (driveParameterMenu.ratingInputVoltage *SQRT2/SQRT3);
       }

#endif



        rVol = 9.53/2;                  // 两个9.53k欧姆的电阻并联
        rVol = rVol / (driveSampleMenu.outVolResOhm + rVol);
	////	KOutVolMagNew = 0.1449104045767851;
        tmp = (fluxStatorObserverMenu.lowFrqWo > 30.0) ? 
            ((10.0/32768.0) / (SQRT2/SQRT3) / KOutVolMag1 / 50.0) : 
            ((10.0/32768.0) / (SQRT2/SQRT3) / KOutVolMag / 50.0);
      ////  tmp =  (3.0 / 2048) /(SQRT2/SQRT3)/ KOutVolMagNew / 50.0;
	    if ((motorPara.ratingVoltage != 0)&&(driveSampleMenu.outVolResOhm != 0))
	    {
        	outVolData_scaler = tmp * motorPara.ratingFrq / (rVol * motorPara.ratingVoltage);
	    }
//#if (INV_TYPE == HW_HD3x)
/*
		if (driveParameterMenu.ratingInputVoltage != 0)
		{
        // 新的HD33的输入电压采样板，采样相电压
        rVol = 1.0 / (1.0/9.53 + 1.0/9.53);         // 9.53k与9.53k电阻并联
        rVol = rVol / (driveSampleMenu.inVolResOhm + rVol);
        inVolData_scaler = ((10.0/32768.0) / (SQRT2/SQRT3)) / 
            (rVol * driveParameterMenu.ratingInputVoltage);
		}
		*/
       // rVol = 2.3;           // 7.5k电阻
        // 母线电压采样的分压电阻
        // 大样机2400k欧姆，小样机4*68k
    //    rVol = rVol / ((272 + 15.0) * 1);
    //    1140母线电压用7.5//3.3K = 2.2916666; FF-10 = 900
    //    driveSampleMenu.inVolResOhm  1140 的这个值设置为900K 母线电压采样
       // rVol = 2.2916666;

//=====================================
//                            二代板母线采样
//===============================================
#if (INV_MODEL == INV_3300)

 rVol = 7.5;
  if(driveSampleMenu.inVolResOhm == 0)
 {

   driveSampleMenu.inVolResOhm = 2.0*1200.0;
  }

   rVol=rVol/(2*1200.0+2*rVol)*2.0/100.0;

 if (driveParameterMenu.ratingInputVoltage <= 0)
 {
  driveParameterMenu.ratingInputVoltage = 3300.0;
 }

  invbusVoltage_scaler = (0.32*(1.0/32768.0)) /
      (rVol * driveParameterMenu.ratingInputVoltage*SQRT2);//二代板母线采样

#elif (INV_MODEL == INV_1140)
  rVol = 1.5;
  if(driveSampleMenu.inVolResOhm == 0)
 {

   driveSampleMenu.inVolResOhm = 9.0*560.0;
  }

   rVol=(22* rVol)/(22+ rVol)/(((rVol+22)*rVol)/((rVol+22)+rVol)+9*560)*22/23.5*8.2;

 if (driveParameterMenu.ratingInputVoltage <= 0)
 {
  driveParameterMenu.ratingInputVoltage = 1140.0;
 }

  invbusVoltage_scaler = ((3.0/4096) / (SQRT2)) /
      (rVol * driveParameterMenu.ratingInputVoltage);//二代板母线采样
#endif

//#endif
    }


 //   inCurData.scaler = driveSampleMenu.inCurReviseCoef * inCurData_scaler;
    outCurData.scaler = driveSampleMenu.outCurReviseCoef * outCurData_scaler;
    filCapCurData.scaler = filCurData_scaler;
    inVolData.scaler = driveSampleMenu.inVolReviseCoef * inVolData_scaler;
    outVolData.scaler = driveSampleMenu.outVolReviseCoef * outVolData_scaler;
    //invbusVoltage.scaler = driveSampleMenu.inVolReviseCoef * invbusVoltage_scaler;
    //invbusVoltage.scaler = 1.015 * invbusVoltage_scaler;
    invbusVoltage.scaler = invbusVoltage_scaler;


// 过流点处理
    tmp = (f32)invIOCSetpoint * outCurData_ocScaler + 0.5;
	 tmp = (tmp > 3750.0) ? (3750.0) : tmp;
   // tmp = (tmp > 2500.0) ? (2500.0) : tmp;
    iocDaSet = (s32)tmp;

}





extern Uint16 coreTuneCmd;
//==============================================================================
//
// 电机参数的转换
//
//==============================================================================
void MotorParaChange(void)
{
    if (motorPara.ratingFrq == 0)
    {
    	motorPara.ratingFrq = 50.0;
	}
    motorPara.fPuOne = motorPara.ratingFrq;
    motorPara.fPuOmegaOne = motorPara.fPuOne * TWO_PI;
    motorPara.iFPuOmegaOne = 1.0 / motorPara.fPuOmegaOne;
    
// zPuOne = U / (3^0.5 * I), U为额定电压, zPU为 1 per unit impedance (ohms) 
    motorPara.zPuOne = motorPara.ratingVoltage / (SQRT3 * motorPara.ratingCurrent);

// LPuOne = zPuOne / (2*pi*fBase), fBase为基准频率
// lPu = L/LPuOne,  L为漏感(单位0.01mH)，互感(单位0.1mH)等
    motorPara.lPuOne = motorPara.zPuOne * motorPara.iFPuOmegaOne;

#if DEBUG_P_AUTO_TUNE
    // 防止异步电机空载电流设置不合理:1)完整调谐；2)完整调谐过程中，减速停车
	//这里要加，不然调谐空载电流会报过流
	if((IM_SVC1 == motorControlMode)||
		(IM_FVC == motorControlMode)||
		(IM_SVC2 == motorControlMode)||
		(IM_SVC3 == motorControlMode)||
		(IM_SVC4 == motorControlMode)
		)
	{
		if (FALSE == smControl)
	    {
	        if ((TUNE_IM_2 == coreTuneCmd) ||
	            ((AUTO_TUNE_STATE == DriveControl.State) && (TUNE_NULL == coreTuneCmd))
	           )
	        {
	            motorPara.iNoload = 0.2;
	        }
	    }
	}
    	
	/*
	//有问题，不能这样加，重新上电导致电机参数自动清零，另外同步机调谐也会修改这些参数
	//这个在异步机电阻漏感调谐完，立刻赋值
    if (TUNE_IM_2 == coreTuneCmd)   // 动态调谐时，当静态调谐完成时，要先更新使用的参数
    {
        if ((AT_DONE == AutoTune.StatusStage1) || 
            (AT_LEAKAGE_MEASUREMENT_DONE == AutoTune.StatusStage1)
           )
        {
            extern f32 rs;
            extern f32 ls;
            
            motorPara.rs = rs;
            motorPara.lSigma = ls;
        }
    }
	*/
    
#endif

}





f32 iInTotal;       // 变频器输入电流
f32 iInTotalFil;
f32 iInTotalDis;

f32 outVoltageHwFil;
f32 outVoltageHwDis;
f32 outVoltagePrgFil;
f32 outVoltagePrgDis; 

f32 iTotalInvDis;       // 双机并联:单机电流
f32 iTotalMotor;        // 双机并联:并机电流
f32 iTotalFil;
f32 iTotalFilTd;        // 变频器、电机反时限过载保护时使用
f32 outputPowerAct;     // 输出功率，单位0.1kw
f32 inputPowerAct;      // 输入功率，单位0.1kw
f32 inputSAct;          // 输入视在功率，单位0.1kVA
f32 iAlphaSParaInv, iBetaSParaInv;
extern f32 inputVol;
extern f32 inputVolFil;
extern f32 inputVolDis;
extern f32 pllBackEmfFrq;
extern f32 outVoltagePrg;
extern f32 iAlphaS, iBetaS;             // local stator current (alpha and beta)
extern f32 yAlphaS, yBetaS;             // local volt-sec measurement alpha & beta
extern f32 ialpha, ibeta;               // 2 phase input currents
extern f32 ealpha, ebeta;               // 2 phase input voltages

//f32 iTotalRef;      // 输出总电流，给定
f32 iTotalFdb;      // 输出总电流，反馈，没有滤波
extern f32 E1R;

//==============================================================================
//
// 输入电压，输入电流，输出电压，输出电流的有效值计算
// 功率计算
// 
// 调用周期: 主循环
//
//==============================================================================
void CurVolRmsCalc(void)
{
    f32 tmp;
    f32 outCurSquareSum;        // 输出电流的平方和
    f32 inCurSquareSum;         // 输入电流
    f32 outVolSecSquareSum;     // 输出电压伏秒的平方和
    f32 outVolSquareSum;		//输出电压平方和
    f32 inVolSquareSum;         // 输入电压的平方和
    f32 outCurSquareSumParaInv; // PARA_WAY_SEL = 0:单机电流；= 1:并机电流
    f32 f1;
    f32 outVolCalc;

    DINT;
    if (masterOrSlave)
    {
        outCurSquareSumParaInv = GetA2AddB2(iAlphaSParaInv, iBetaSParaInv);
    }
    outCurSquareSum = GetA2AddB2(iAlphaS, iBetaS);
    outVolSecSquareSum = GetA2AddB2(yAlphaS, yBetaS);
	outVolSquareSum = GetA2AddB2(AlphaOutputVol, BetaOutputVol);
    inCurSquareSum = GetA2AddB2(ialpha, ibeta);
    inVolSquareSum = GetA2AddB2(ealpha, ebeta);
  // inVolSquareSum = GetA2AddB2(InputProcess.Ed, InputProcess.Eq); 
    f1 = pllBackEmfFrq;     // 还是应该为 OutputProcess.Frequency?
    EINT;

// 计算输入电流有效值
    iInTotal = sqrt(inCurSquareSum);
    iInTotalFil = LPF_T(iInTotal, iInTotalFil, I_TOTAL_FILTER_T, MAIN_LOOP_TIME_MS);

// 计算输入电压有效值
    inputVol = sqrt(inVolSquareSum);
    inputVolFil = LPF_K(inputVol*1.05, inputVolFil, INPUT_VOL_LPF_TIME/MAIN_LOOP_TIME_MS) ;
//    inputVolFil = LPF_K(InputProcess.EdRaw, inputVolFil, INPUT_VOL_LPF_TIME/MAIN_LOOP_TIME_MS);
//    inputVolFil = LPF_K(InputProcess.EdAverage, inputVolFil, INPUT_VOL_LPF_TIME/MAIN_LOOP_TIME_MS);

// 输入电压太小，输入电压显示为0V，输入电流显示为0A
    inputVolDis = inputVol; // 给功能的输入电压显示不滤波
    iInTotalDis = iInTotalFil;
    if (inputVolDis < VOL_DIS_MIN)
    {
        inputVolDis = 0;
        iInTotalDis = 0; 
    }

// 输出电流计算
    tmp = sqrt(outCurSquareSum);
    iTotalFdb = tmp;                // 输出总电流，
    if (iTotalFdb == 0)
    {
    	iTotalFil = 0;
    }
	else
	{
    	iTotalFil = LPF_T(tmp, iTotalFil, I_TOTAL_FILTER_T, MAIN_LOOP_TIME_MS);
	}

    // 并机方案
    if (masterOrSlave)
    {
        static f32 iTotalFilParaInv;    // PARA_WAY_SEL =0:单机电流；= 1:并机电流
        
        if (!PARA_WAY_SEL)
        {
            // 单机电流:显示及过载保护用
            tmp = sqrt(outCurSquareSumParaInv);
			if (tmp == 0)
			{
				iTotalFilParaInv = 0;
			}
			else
			{
           		iTotalFilParaInv = LPF_T(tmp, iTotalFilParaInv, I_TOTAL_FILTER_T, MAIN_LOOP_TIME_MS);
				iTotalFilTd = LPF_T(tmp, iTotalFilTd, I_TOTAL_FILTER_Td_T, MAIN_LOOP_TIME_MS);
			}
            iTotalMotor = iTotalFil;
            iTotalInvDis = iTotalFilParaInv;
        }
        else if (1 == PARA_WAY_SEL)
        {
            // 单机电流:过载保护用
            iTotalFilTd = LPF_T(tmp, iTotalFilTd, I_TOTAL_FILTER_Td_T, MAIN_LOOP_TIME_MS);
            // 并机电流:显示用
            tmp = sqrt(outCurSquareSumParaInv);
            iTotalFilParaInv = LPF_T(tmp, iTotalFilParaInv, I_TOTAL_FILTER_T, MAIN_LOOP_TIME_MS);

            iTotalMotor = iTotalFilParaInv;
            iTotalInvDis = iTotalFil;
        }
    }
    // 单机方案
    else
    {
        iTotalFilTd = tmp;//LPF_T(tmp, iTotalFilTd, I_TOTAL_FILTER_Td_T, MAIN_LOOP_TIME_MS);

        iTotalMotor = iTotalFil;
        iTotalInvDis = iTotalFil;
    }

// 输出电压计算

// 程序的输出电压
    outVoltagePrgFil = LPF_K(outVoltagePrg, outVoltagePrgFil, VOLTAGE_FILTER_T/MAIN_LOOP_TIME_MS);

// 根据输出电压的伏秒值，计算输出电压
    {
        //tmp = (fluxStatorObserverMenu.lowFrqWo > 30.0) ? CALC_VOL_A1 : CALC_VOL_A;
        //outVolCalc = tmp * motorPara.iFPuOmegaOne *
        //    sqrt((f1*f1 + CALC_VOL_B*CALC_VOL_B) * outVolSecSquareSum);
        outVolCalc = sqrt(outVolSquareSum);

        outVoltageHwFil = LPF_K(outVolCalc, outVoltageHwFil, VOLTAGE_FILTER_T/MAIN_LOOP_TIME_MS);
       E1R = LPF_K(outVolCalc, E1R, 5);//outVoltageHwFil;
}

// 停机时，输出电流显示为0A，程序理论输出电压显示为0V
    outVoltagePrgDis = outVoltagePrgFil;
    if (!coreRunStatus.bit.run)
    {
        iTotalMotor = 0;
        iTotalInvDis = 0;
        outVoltagePrgDis = 0;
    }
// 根据伏秒值计算的输出电压很低时，显示为0V
    outVoltageHwDis = outVoltageHwFil;
    if (outVoltageHwFil < VOL_DIS_MIN)
    {
        outVoltageHwDis = 0;
    }




#if !DEBUG_PRG_IN_RAM
// 输入功率，单位0.1kw
    inputPowerAct  = InputProcessDisplay.AveragePower * driveParameterMenu.ratingInputVoltage * driveParameterMenu.ratingInputCurrent * (SQRT3/100.0);
// 输入视在功率，单位0.1kVA
    inputSAct = InputProcess.Kva * driveParameterMenu.ratingInputVoltage * driveParameterMenu.ratingInputCurrent * (SQRT3/100.0);
#endif

// 输出功率，单位0.1kw
    outputPowerAct = OutputProcess.AveragePower * motorPara.ratingVoltage * motorPara.ratingCurrent * (SQRT3/100.0);

}




extern Uint16 vfSeparateVol;       // 12   VF分离时的输出电压
extern Uint16 vfCurve;             // 13   VF曲线选择
extern f32 volAmpl;
#define OUT_VOL_MIN     (int32)(0/100.0*0x7FFF)    // Q15
//#define OUT_VOL_MAX     (int32)(30/100.0*0x7FFF)   // Q15
//#define OUT_VOL_MAX     _IQ15(50/100.0)   // Q15
//#define OUT_VOL_MAX     (int32)(50/100.0*0x7FFF)   // Q15
#define OUT_VOL_MAX     (int32)(100/100.0*0x7FFF)   // Q15
LINE_STRUCT outVolLine;
//==============================================================================
//
// 根据VF，计算输出电压
// 仅VF需要计算
//
//==============================================================================
void OutVoltageDeal(void)
{
    f32 volOut;

    if ((PURE_VF != motorControlMode)
        && (SIN_ONLY != motorControlMode)
        )
    {
        return;
    }

    outPhaseStep = (f32)coreFrqHz / 100 * pwmT;

    outVolLine.x2 = motorPara.ratingFrq * 100;
    outVolLine.x  = ABS_INT32(coreFrqHz);
    LineCalc(&outVolLine);

    if (outVolLine.y < OUT_VOL_MIN)
    {
        outVolLine.y = OUT_VOL_MIN;
    }
    else if (outVolLine.y > OUT_VOL_MAX)
    {
        outVolLine.y = OUT_VOL_MAX;
    }

    volOut = _Q15toIQ(outVolLine.y);
    //volOut = 1.0;

    if (10 == vfCurve)  // VF完全分离
    {
        volAmpl = vfSeparateVol;
    }
    else
    {
        volAmpl = volOut * VF_V_GAIN / 1000;
    }

    volAmpl = GetMin(volAmpl, 1.3);     // 限制输出电压太大
}







extern f32 pllFluxSFrq;
//==============================================================================
//
// 
//
//==============================================================================
void MiscDataDealAdInt(void)
{
//    DeltaSPu = OutputProcess.DeltaS * I_TWO_PI;
    pllFluxSFrqPu = pllFluxSFrq * motorPara.iFPuOmegaOne;
    pllBackEmfFrqPu = pllBackEmfFrq * motorPara.iFPuOmegaOne;
    inputFrqPu = InputProcess.Frequency * motorPara.iFPuOmegaOne;
}








extern void DaDeal(void);
extern void SpinningLoadControl(void);
extern void SamplePhaseCalc(void);
extern u16 tuneStage1NoFlag;
extern f32 iAlphaSMotor, iBetaSMotor;
extern f32 iAlphaSFilter, iBetaSFilter;
//==============================================================================
//
// 输入、输出快环处理
// 中断调用
//
//==============================================================================
void FastLoopControl(void)
{
    OutputVoltageSample();          // 隔离输出电压采样 
    OutputVoltageIntegration();
    ReadAd7606Result();             // 读取AD7606的采样结果     56clk    
    GetCurrentResult();             // 输入电流、输出电流采样   86clk,152
    GetVoltageResult();             // 输入电压、输出电压采样   110clk 

    BusVolProtectFun();             // 母线电压保护
 //   SamplePhaseCalc();

//===============================================================================
    if (masterOrSlave)
    {
        ClarkeCalcMacro(outCurData.uParaInv, outCurData.vParaInv, iAlphaSParaInv, iBetaSParaInv);   // 11clk
    }
    ClarkeCalcMacro(outCurData.u, outCurData.v, iAlphaS, iBetaS);   // 11clk
  // ClarkeCalcMacro(0.1, 0.1, iAlphaS, iBetaS);   // 11clk
   // ClarkeCalcMacro(outVolData.u, outVolData.v, yAlphaS, yBetaS);   // 11clk
    ClarkeCalcMacro(filCapCurData.u, filCapCurData.v, iAlphaSFilter, iBetaSFilter);
//    ClarkeCalcMacro(outCurData.u - filCapCurData.u, outCurData.v - filCapCurData.v, iAlphaSFilter, iBetaSFilter);
//===============================================================================
//    iAlphaS = iAlphaSMotor;
//    iBetaS = iBetaSMotor;

  //  TEST_IO3_ON;
 	 uvwOutCurrentCalc();

    InFastLoopControl();                // 输入快环处理，685clk, 761clk
	
  if (cellMenu.cellVoltage != 3)
    {
    tuneStage1NoFlag = TRUE;

//    UpdateFpgaVoltageDataSinOnly();   // 测试

#if DEBUG_P_AUTO_TUNE
    if (AUTO_TUNE_STATE == DriveControl.State)      // 调谐
    {
		if((IM_SVC1  == motorControlMode)||
			(IM_FVC  == motorControlMode)||
			(IM_SVC2  == motorControlMode)||
			(IM_SVC3  == motorControlMode)||
			(IM_SVC4  == motorControlMode)
			)
		{
        	AutoTuneControl();
		}
		else
		if((PMSM_FVC == motorControlMode)||(PMSM_SVC == motorControlMode))
		{
			AutoTuneControlPmsm();
		}
		else
		{
			return;
		}
    }
    else
#endif
#if DEBUG_P_SPINNING_LOAD
    if (SPINNING_LOAD_STATE == DriveControl.State)  // 飞车启动
    {
		SpinningLoadControl(); 
    }
#endif
#if 0
	else if((ROTOR_INITIAL_STATE == DriveControl.State)
		    &&(RotorPositionPwmReg.bit.finishFlg == 0)
		    )
    {
		break;
    }
#endif
	else
    if ( ((IM_SVC1  == motorControlMode) ||  // 无速度传感器矢量控制，SVC1
         (IM_FVC   == motorControlMode) ||  // 有速度传感器矢量控制，FVC
         (IM_SVC2  == motorControlMode) ||  // 电压型开环矢量，SVC2
         (IM_SVC3  == motorControlMode) ||  // IM SVC3
         (IM_SVC4  == motorControlMode) ||  // IM SVC4
         (SM_SVC   == motorControlMode) ||  // 
         (SM_FVC   == motorControlMode) ||  // 
         (SMDC_SVC == motorControlMode) ||  // 
         (PMSM_SVC == motorControlMode) ||  // 
         (PMSM_FVC == motorControlMode) ||  // 
         (PURE_VF  == motorControlMode)     // 标准VF
         )&&(ROTOR_INITIAL_STATE != DriveControl.State)
         
       )
    {
        OutputFastLoopSfoc();               // 输出快环处理，2550clk
    }
	 else
#if !DEBUG_PRG_IN_RAM
    if (OLTM == motorControlMode)           // 测试模式
    {
       // OLTMDeal();
    }
    else
#endif
    {   
      //  UpdateFpgaVoltageDataSinOnly();     // SIN_ONLY
    }
//    TEST_IO3_OFF;
   }
else  //整流侧
   {
		 DecouplePLL();
         GridAsynValueCalc();
         GridPLLOKChk();
		 if(funcCode.code.AfeMode == 0)
		 {
			CurrentDecouple();
			VolRegulator();
			AFE_LoadObserverLoop();
			CurrentRefCalc();
			AfeFastLoop();
			AFE_LoadObserverInit();
			AFEUpdateFpgaVoltageData();
		 }
		 else
		 {
			LAfeDutyCal();
			LAFEUpdateFpgaVoltageData();
		 }
   }

    
    UpdateDataCore2Fpga();              // 将指令传递给FPGA，180-200clk

    DaDeal();                           // DA处理，包括了过流点的更新。165clk
    
//    UpdateDataLog();                    // log，调试使用。145clk

#ifdef DEBUG_COMMUNICATE_TO_PC
 //   SaveDebugData(0);   // 快环保存数据
#endif
#if DEBUG_BLACK_BOX
    BlackBoxDeal();     // 黑匣子数据dsp处理 // LS_20221205
#endif
#if 0
// 这几个寄存器，每个载波周期都传递。
// 新疆现场发现快环频率自己变了。
    interfaceRam[FPGA_REG_N1] = N1Reg0Mirror;
    interfaceRam[FPGA_REG_N2] = N2Reg0Mirror;
    interfaceRam[FPGA_REG_N3] = N3Reg0Mirror;
    interfaceRam[FPGA_REG_A]  = aReg0Mirror;
    interfaceRam[FPGA_REG_B]  = bReg0Mirror;
#endif

}





s32 motorRun;   // 反馈给功能的输出频率，单位0.01Hz。
// FVC时，为编码器反馈频率；SVC2时为同步频率；SVC1为辨识频率

u16 speedTrackEndOld;
extern u16 clControl;
extern int32 frqMotorRun;
extern u32 frqStop;
extern f32 spdRef, spdFdb;
extern f32 SpeedReferenceCore2Fun;
extern bool rollbackenableflag;
extern struct SPEED_REGULATOR_STR spdRegData;
void pulseInCalcFvcEQep(void); 
//==============================================================================
//
// 慢环处理
// 
// 目前为2ms调用
//
//==============================================================================
void SlowLoopControl(void)
{
    f32 tmp;
	

    InSlowLoopControl();
    
    pulseInCalcFvcEQep();       // 速度采样计算

    tmp = (1.0 / 100.0) / motorPara.fPuOne;
    spdRef = (f32)coreFrqHz * tmp;
    spdFdb = (f32)frqMotorRun * tmp;
    
    if ((TRUE != AutoTune.RequestStage1) &&
        (SPINNING_LOAD_STATE != DriveControl.State)
       )
    {
        if (OLTM != OutputProcess.ControlAlgorithm)
        {
            OutputProcessSlowLoop(); 
        }
    }

// 反馈给功能的输出频率
    if (PURE_VF == motorControlMode)        // 标准VF
    {
        motorRun = coreFrqHz;
    }
    else if (clControl)                     // 闭环
    {
        motorRun = frqMotorRun;
    }
    else
    {
        motorRun = OutputProcess.MotorSpeed * (100.0 / TWO_PI); // 考虑SVC1 

// 飞车启动过程中，给功能传递当前搜索频率  				   异步电机
        if ((TRUE == OutputProcess.SpinningLoadEnable) &&
            (OutputProcess.Enable) &&   // 加入，停机时触摸屏显示反馈速度清零
            (!speedTrackEndOld)
           )
        {
            motorRun = SpeedReferenceCore2Fun * (100.0 / TWO_PI);
        }


#if 0
// if (MAGNETIZING_STATE == DriveControl.State)
        if (startFlag)
        {
//            if (coreFrqAimHz * motorRun < 0)    // 防止给反向频率
//            {
//                motorRun = 0.0;
//            }
            if (coreFrqAimHz >= 0)
                motorRun = sdafh;
            else
                motorRun = -sdafh;
        }
#elif 0
        if (coreFrqAimHz)
#endif

        if ((0 == coreFrqAimHz) && (0 == coreFrqHz))    // 可能是停机
        {
            if (fabs(motorRun) <= frqStop)
            {
                motorRun = 0;
            }
        }



		if (AUTO_TUNE_STATE == DriveControl.State)//防止调谐反馈速度是0
		{
			motorRun = OutputProcess.PerUnitSpeedReference * OutputProcess.RatedFrequency * (100.0 / TWO_PI);
		}
    }
    speedTrackEndOld = coreStatus.bit.speedTrackEnd;
}










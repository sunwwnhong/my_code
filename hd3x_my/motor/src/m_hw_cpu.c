//==================================================================================================
//
// DSP芯片的初始化
// 包括:
// 1. 芯片时钟初始化
// 2. 中断初始化，中断函数调用。
//
// 
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================

#include "m_input.h"
#include "m_main.h"
#include "m_pll.h"
#include "m_frqSrc.h"
#include "m_cell.h"
#include "m_interfaceModify.h"
#include "m_macro_transfer.h"
#include "main.h"
#include "m_main.h"
#include "test.h"
#include "m_speedSample.h"
#include "m_interface.h"
#include "m_macro_AO.h"
#include "m_interfaceModify.h"


#include "m_macro_error.h"

#include "Debug.h"
#include "SimpleDebug.h"


#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
#pragma CODE_SECTION(Ad7606Isr,     "ramfuncs");
//#pragma CODE_SECTION(iputVolIsr,     "ramfuncs");
#endif



// AD7606的电源是IO板供电，如果没有接IO板，AD7606不能正常采样，也就不能产生Ad7606Isr().
// 电压指令产生，在哪里调用
// 0-AD7606采样完成的中断，FPGA给AD7606启动信号
// 1-DSP自己产生的中断
#define VOL_CMD_7606_OR_DSP     0







void InitCpu(void);
void EnableInterrupt(void);
void InitClock(void);
extern void InFastLoopControl(void);
interrupt void AdcIsr(void);
interrupt void RsvdIsr(void);
interrupt void Ad7606Isr(void);
interrupt void iputVolIsr(void);
interrupt void local_DINTCH2_ISR(void);
extern interrupt void SCI_RXD_isr(void);
extern interrupt void SCI_TXD_isr(void);
//==============================================================================
//
// DSP的初始化
//
//==============================================================================
void InitCpu(void)
{
    InitSysCtrl();

    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;
 //   PieVectTable.ADCINT      = AdcIsr;     // AD采样完成中断(EOS)
    PieVectTable.XINT1       = Ad7606Isr;          // 外部中断1, AD采样完成
  //  PieVectTable.DINTCH2     = local_DINTCH2_ISR;  // DMA中断
//    PieVectTable.SCIRXINTB   = SCI_RXD_isr;
//    PieVectTable.SCITXINTB   = SCI_TXD_isr;
   // PieVectTable.TINT0       = Ad7606Isr;//iputVolIsr;    //成都项目输入电压采样中断
#if DEBUG_F_CAN
	//PieVectTable.ECAN0INTA   = ECAN0INTA_ISR;
#endif

    EDIS;

    InitCpuTimers();
    StartCpuTimer1();                    // 作为主程序的时间基准
  //  ConfigCpuTimer(&CpuTimer0,100,1000);   //6K 采样频率作为输入电压采样
  //  StartCpuTimer0();  

#if !DEBUG_PRG_IN_RAM   // 在FLASH中运行
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
#endif
}








//==============================================================================
//
// 初始化时钟，在进入main()之前调用
//
//==============================================================================
void InitClock(void)
{
    InitPll(DSP28_PLLCR,DSP28_DIVSEL);
}



//==============================================================================
//
// 中断使能
//
//==============================================================================
void EnableInterrupt(void)
{
  //  PieCtrlRegs.PIEIER1.bit.INTx6 = 1;      // ADCINT
   // PieCtrlRegs.PIEIER7.bit.INTx2 = 1;      // DMA, RX
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;      // XINT1, AD7606的BUSY信号，表示AD采样完成
   // PieCtrlRegs.PIEIER9.bit.INTx3 = 1;
//	PieCtrlRegs.PIEIER9.bit.INTx4 = 1;
    //PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      //成都项目输入电压采样
 //   IER = IER | M_INT1 | M_INT7| M_INT9;
    IER = IER | M_INT1;
   //IER = IER | M_INT1 ;
#if DEBUG_F_CAN
  //  PieCtrlRegs.PIEIER9.bit.INTx5 = 1;      // enable ECAN0INTA
  //  IER = IER | M_INT9;
#endif
}




//==============================================================================
//
// 
//
//==============================================================================
void InitPieVectTable(void)
{
    int16 i;
    PINT *Dest = (void *)&PieVectTable;

    EALLOW;
    for (i = 0; i < 128; i++)
    {
        *Dest++ = RsvdIsr;
    }
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;      // Enable the PIE Vector Table
}





Uint32 IsrErrTicker;
//==============================================================================
//
// 所有没有使用的中断函数
//
//==============================================================================
interrupt void RsvdIsr(void)
{
    IsrErrTicker++;
}







#if 1
STATISTICS_STRUCT adcIsrTime;
u16 ADCcunter;
interrupt void AdcIsr(void)
{
    Uint32 baseTime;
    baseTime = GetTime();

#if VOL_CMD_7606_OR_DSP // 仅测试使用
    {
   //     extern void UpdateFpgaVoltageDataSinOnly(void);
   //     extern void UpdateDataCore2Fpga(void);

   //     UpdateFpgaVoltageDataSinOnly();
   //     UpdateDataCore2Fpga();
    }
#endif

    adcIsrTime.now = baseTime - GetTime();
    adcIsrTime.prd = 10000;
    //StatisticDeal(&adcIsrTime);
    ADCcunter++;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
#endif


//输入电压中断采样
u16 adResultFpga1[8];
f32 inVolDatau0,inVolDatav0,inVolDataw0;
u16 kl = 6;//此时输入电压采样效果最好，F6-21=25.8 ---26.5可调 小样机效果较好，满载都没有问题。
           //CF-11=3效果也不错
f32 afeFpgaData[3];
extern f32 ealpha, ebeta;                  // 2 phase input voltages  
extern f32 deltaU;

interrupt void iputVolIsr(void)
{
  //  u16 i;
//    f32 edneg, eqneg;               // dq negtive sequence voltages 
  //  memcpy(&adResultFpga[0], (u16 *)&interfaceRam[FPGA_REG_SampleCh1], 8); 
    afeFpgaData[0] = ((f32)(s16)interfaceRam[FPGA_REG_rsel_vd_afe_rd])/4096.0; //输入D轴
    afeFpgaData[1] = ((f32)(s16)interfaceRam[FPGA_REG_rsel_vq_afe_rd])/4096.0; //输入Q轴
    afeFpgaData[2] = ((f32)(s16)interfaceRam[FPGA_REG_rsel_theta_rd])/4096.0; //输入角度0---2PI
    
    inVolDatau0 = (f32)((int16)(adResultFpga[0])) * inVolData.scaler;
    inVolData.u0 = LPF_K(inVolDatau0,inVolData.u0,kl);
    inVolDatav0 = (f32)((int16)(adResultFpga[1])) * inVolData.scaler;
    inVolData.v0 = LPF_K(inVolDatav0,inVolData.v0,kl);
    inVolDataw0 = (f32)((int16)(adResultFpga[2])) * inVolData.scaler;
    inVolData.w0 = LPF_K(inVolDataw0,inVolData.w0,kl);
    
    CpuTimer0Regs.TCR.bit.TIF = 1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;  
}
/*
extern struct InputProcessType InputProcess;
struct PiDataType inVolPll2Pid =  
//       Max   Min     Ki          Kp     
        { 0.01 ,   -0.01,   0.0001,    0.01};
struct PHASE_LOCK_LOOP_STR inVolPll2;
 u16 counterqq;
 f32 pwmTDetect2;
 struct PARK_STR parkInVol2;
interrupt void iputVolIsr(void)
{
    
    u16 i;
    f32 a, b, c;
    f32 ebeta2,ealpha2;
  //  u16 counter;
    Uint32 baseTime; 
    static u32 baseTimeOld;
    
    baseTime = GetTime();  
    
    memcpy(&adResultFpga[0], (u16 *)&interfaceRam[FPGA_REG_SampleCh1], 8);  
      
    {
        a = (f32)((int16)(adResultFpga[0])) * inVolData.scaler;
        b = (f32)((int16)(adResultFpga[1])) * inVolData.scaler;
        c = (f32)((int16)(adResultFpga[2])) * inVolData.scaler;

        inVolData.e0 = (a + b + c) * (1.0/3);

        // 新的HD33的输入电压采样板，采样相电压
        inVolData.u = a - inVolData.e0;
        inVolData.v = b - inVolData.e0;
        inVolData.w = c - inVolData.e0;
 	}


   // inVolDataul =  LPF_K(inVolDatau ,inVolDataul , kl);
   // inVolDatavl =  LPF_K(inVolDatav ,inVolDatavl , kl);
   // inVolDatawl =  LPF_K(inVolDataw ,inVolDatawl , kl);
    

    ClarkeCalcMacro(inVolData.u, inVolData.v, ealpha2, ebeta2);

    counterqq++;
    if(counterqq >=5000)
    {
       // inVolPll2.enable = 1;
       inVolPll2Pid.maxLimit = 0.5;
       inVolPll2Pid.minLimit = -0.5;
       
       
        counterqq = 5000;
    }

    else
    {
        //inVolPll2.enable = 0;
        inVolPll2Pid.maxLimit = 0.01;
        inVolPll2Pid.minLimit = -0.01;
    }

   
    inVolPll2.enable = TRUE;
    parkInVol2.alpha = ealpha2;
    parkInVol2.beta  = ebeta2;
    parkInVol2.angle = inVolPll2.angle;
    ParkCalc(&parkInVol2); 

    
   ///////////////////////// 
    inVolPll2.input = parkInVol2.q;
  
    inVolPll2.pllParams = &inVolPll2Pid;
  //  inVolPll2.sampleRate = TWO_PI * 50.0 *  pwmTDetect2;
    inVolPll2.sampleRate = TWO_PI * 50.0 *  CpuTimer0.PeriodInUSec * 0.000001;
    inVolPll2.seed = 1;
    PhaseLockLoop(&inVolPll2);

   // testpll = atan2(ebeta2,ealpha2);

   //////////////////////////


    inVolPll2.input = parkInVol2.q;
  
    inVolPll2.pllParams = &inVolPll2Pid;
  //  inVolPll2.sampleRate = TWO_PI * 50.0 *  pwmTDetect2;
    inVolPll2.sampleRate = TWO_PI * 50.0 *  CpuTimer0.PeriodInUSec * 0.000001;
    inVolPll2.seed = 1;
    PhaseLockLoop(&inVolPll2);
    baseTimeOld = GetTime();
    
    pwmTDetect2 = (baseTimeOld - baseTime) * (1.0/(DSP_CLOCK*1000000.0));    // 总是检测中断周期

   // deltaU = inVolPll2.angle;
    InputProcess.EdRaw = LPF_K(parkInVol2.d,InputProcess.EdRaw,kl);
    InputProcess.EqRaw = LPF_K(parkInVol2.q,InputProcess.EqRaw,kl);
   // InputProcess.LineFluxVectorAngle = inVolPll2.angle - (ONE_PI / 2);
  //  Modulo2PIMacro1(InputProcess.LineFluxVectorAngle);
   InputProcess.Frequency = inVolPll2.frequency * 50 * TWO_PI;
  // UpdateDataLog(); 
   CpuTimer0Regs.TCR.bit.TIF = 1;
   PieCtrlRegs.PIEACK.bit.ACK1 = 1; 
}
*/
void FastLoopControl(void);
u32 fastLoopTicker;     // 快环中断计数器
f32 pwmTDetect;         // DSP自己检测的快环周期
extern f32 pwmT;
STATISTICS_STRUCT adc7606IsrTime;
//==============================================================================
//
// 外部中断1
// 表示AD7606采样完成
// 即，快环(电流环)中断函数
//
//==============================================================================
interrupt void Ad7606Isr(void)
{
    Uint32 baseTime; 
    static u32 baseTimeOld;

    //TEST_IO4_ON;
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;
    baseTime = GetTime();
    pwmTDetect = (baseTimeOld - baseTime) * (1.0/(DSP_CLOCK*1000000.0));    // 总是检测中断周期
    baseTimeOld = baseTime;

    fastLoopTicker++;

   // ConfigCpuTimer(&CpuTimer0,100,166);   //6K 采样频率作为输入电压采样
   // StartCpuTimer0();  
    
//--------------------------------------------------------------------------------
#if DEBUG_P_ERR95   // DSP自己检测快环周期
    {
        static u16 fFastLoopDetectWrongTicker;
        extern u16 updateFpgaCarrierRegFlag;
        extern u16 poweringFlag;

        extern u16 coreCarrierFrq;
        static u16 coreCarrierFrqOld;
        static u16 coreCarrierFrqFlag;
        static u16 coreCarrierFrqFlagTicker;

     
        if (coreCarrierFrqOld != coreCarrierFrq)    // 载波频率改变了
        {
            coreCarrierFrqOld = coreCarrierFrq;
            coreCarrierFrqFlag = 1;
        }
        else
        {
            if (coreCarrierFrqFlag)     // 载波频率改变了，延迟几拍才检测F95
            {
                coreCarrierFrqFlagTicker++;
                if (coreCarrierFrqFlagTicker >= 7)
                {
                    coreCarrierFrqFlag = 0;
                    coreCarrierFrqFlagTicker = 0;
                }
            }            
        }
        
        // 检测进入fast loop的周期是否与给FPGA的指令基本一致
        // 这也与AD7606的采样有关系
        if ((updateFpgaCarrierRegFlag) && (!coreCarrierFrqFlag))
        {
            if ((fabs(pwmTDetect - pwmT) > 0.07 * pwmT)
                && (!poweringFlag)
               )
            {
                fFastLoopDetectWrongTicker++;

                if (fFastLoopDetectWrongTicker >= 5)
                {
                    if (!coreErrorCode)
                    {
                        coreErrorCode = 95;
                    }
                }
            }
            else
            {
                fFastLoopDetectWrongTicker = 0;
            }
        }
    }
#endif
//--------------------------------------------------------------------------------
 //  if (OutputProcess.FastLoopFrequency == 0)
 //  {
	//	OutputProcess.FastLoopFrequency = 750 * 2;
	//	pwmT = 1.0 / OutputProcess.FastLoopFrequency;
	//	OutputProcess.FastLoopSamplePeriod = pwmT;
//   }
   FastLoopControl();

    adc7606IsrTime.now = baseTime - GetTime();
    StatisticDeal(&adc7606IsrTime);

  //////  TEST_IO4_OFF;

//    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
//    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
  //  CpuTimer0Regs.TCR.bit.TIF = 1;
  //  PieCtrlRegs.PIEACK.bit.ACK1 = 1;  

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}



extern void UpdateDaPin(void);
//==============================================================================
//
// DMA中断
// DA芯片使用
//
//==============================================================================
interrupt void local_DINTCH2_ISR(void)
{
  //  UpdateDaPin(); 

//    EALLOW;									// NEED TO EXECUTE EALLOW INSIDE ISR !!!
//    DmaRegs.CH1.CONTROL.bit.RUN=0;		    // Re-enable DMA CH1. Should be done every transfer
//    DmaRegs.CH2.CONTROL.bit.RUN=0;
//    EDIS;

   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt
}



#if DEBUG_F_CAN

u16  canRxStatus;
u16  canRecv;
Uint32 canReciveData,canReciveDataOld;
Uint16 canRxDataLow;
Uint16 canRxDataHigh;
Uint16 canSlaveSendDataCheckCounter;
u16 canRxFlag;
interrupt void ECAN0INTA_ISR(void)
{ 
     //中断执行时间 2.08us.

     canRxStatus = eCanDataRec(canRXMailBox,   (Uint32 * ) & canRecv);	   //mbox =0x6
     canReciveData = ECanaMboxes.MBOX6.MDL.all;
      // 测试是否收到数据，并且有漏掉的数据
     if (ABS_INT32(canReciveData - canReciveDataOld) != 100)
     {
         canSlaveSendDataCheckCounter = canSlaveSendDataCheckCounter + 1;
     }
      canRxDataLow  = (Uint16) (canReciveData & 0x0000ffff); 
      canRxDataHigh  = (Uint16) ((canReciveData & 0xffff0000)>>16); 
      canRxFlag = canRxFlag + 1;   //进中断标志位
      canReciveDataOld = canReciveData;	    
      PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

#endif





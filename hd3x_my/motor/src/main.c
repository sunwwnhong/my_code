//==================================================================================================
//
// 
// 使用了浮点CPU。
// 
// main文件。
// 主要是初始化、主循环，以及硬件相关的处理。
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "main.h"
#include "m_main.h"
#include "test.h"
#include "m_speedSample.h"
#include "m_interface.h"
#include "m_macro_AO.h"
#include "m_interfaceModify.h"
#include "m_hw_cpu.h"
#include "m_hw_misc.h"
#include "m_macro_error.h"

#include "Debug.h"
#include "SimpleDebug.h"
#include "funcAuxMain.h"
#include "funcMcbsp.h"
#include "ethernet.h"


//==============================================================================
// 包含一些硬件处理相关的文件和函数
//#include "m_hw_cpu.c"
//#include "m_hw_adc.c"
//#include "m_hw_misc.c"
//==============================================================================




long GlobalQ = GLOBAL_Q;


Uint16 timerTicker;
Uint16 bTimerHalfMs;
Uint32 NowTick;

#if(0)
Uint16 timerTickerHalfMsOld;
#endif

#if 0
typedef struct
{
    Uint16 ms;
    Uint16 s;
    //Uint16 min;
    Uint16 hour;
} TIME_STRUCT;
TIME_STRUCT timeRecord;
Uint16 timerTicker1msOld;
#endif
void TimerDeal(void);
extern void InitEQep1Gpio(void);
extern void InitEQep2Gpio(void);

extern void InitEPwmGpio(void);
extern void InitEPwm(void);
void InitHardware(void);
void InitSystemPeripherals(void);
extern void EnableDog(void);
extern void InitXintf(void);
extern void InitTempVol(void);     // 温度电压同步信号初始化
extern void InitFiberPortFlag(void);
extern void EnableCellDiag(void);
//extern void InitForFunctionApp(void);
void Calzaiboint(void);
extern void Main05msFunctionA(void);
extern void Main05msFunctionB(void);
extern void Main05msFunctionC(void);
extern void Main05msFunctionD(void);
extern void InitForFunctionApp(void);
extern void Main0msFuction(void);
extern void InitFuncCode(void);
u16 tickerDspDeal;
//u16 flagDspDealt;   // 已经执行了 DspDeal()
u16 flagDspA;       // 0-根据RAM_ARM_BUSY进入DSP主循环；1-根据时间进入DSP主循环
u16 ARMbusyBak;
//void DspDeal(void);

extern void UpdateDataLog();   
u16 interflag;
extern Uint16 errorCode;
//==============================================================================
//
// main函数
//
//==============================================================================
void main(void)
 {
    Uint32 baseTime;
   // Uint16 tickerDspTimer = 0;
    u16 ticker;
    Uint16 run_tmr = 0;

    InitHardware();     // 硬件初始化
    InitSystem();       // 系统初始化
   // Calzaiboint();
   //	InitForMotorApp();					// Step 4. User specific code
  //  InitOutputProcessing();//暂时不执行，功能码没交互成功不能执行
  	InitForFunctionApp();
   /*
#if TEST_K
    TestIQmath();   // 在中断开启之前测试
    TestMath1();
    TestMv();
    for (;;){}
#endif
*/

//    EnableDog();    //? 调试时可以先关闭看门口狗
    EnableInterrupt();
// Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM


    baseTime = GetTime();
     
    for (;;)
    {
      //  Main0msFuction();
        //Main0msMotor();

        NowTick = GetTime();
        if (baseTime - NowTick >= TIME_100US)
        {
            baseTime -= TIME_100US;
            TimerDeal();
			
            ServiceDog();
        }
		
        if (bTimerHalfMs)   // 0.5ms
        {
        	
            bTimerHalfMs = 0;

		    func05MsDeal();
            if (0 == ticker)
            {		
           		Main05msFunctionA();
				Main05msMotorA();
				
				// LED_DSP_RUN
				if (run_tmr >= 200)
				{
				    run_tmr = 0;
				}
				else
				{
				    run_tmr++;
				}
				if (run_tmr <= 100)
				{
				    LED_DSP_RUN_ON;
                    if (errorCode != 0)
                    {
                        LED_DSP_ERROR_ON;
                    }
				}
				else
				{
				    LED_DSP_RUN_OFF;
                    LED_DSP_ERROR_OFF;
				}

			}
			else if (1 == ticker)
            {
				Main05msFunctionB();
				Main05msMotorB();
			}
			else if (2 == ticker)			
            {
				Main05msFunctionC();
				Main05msMotorC();
				//UpdateDataLog();    
			}
			else if (3 == ticker)
            {
				Main05msFunctionD();
				Main05msMotorD();
				/*
			    if (interflag == 0)
			    {
			        interflag = 1;
					EnableInterrupt();
					EINT;   // Enable Global interrupt INTM
   					ERTM;   // Enable Global realtime interrupt DBGM
			    }
			    */
			}

			ticker++;
			if (ticker >= 4)
			{
				ticker = 0;
			}
#ifdef DEBUG_COMMUNICATE_TO_PC
         //   SaveDebugData(1);   // 0.5ms循环中保存数据
#endif

			ETH_Status.bit.active = 1;
        }
        funcEthernet();
    }
    
}



//==============================================================================
//
// 简单的软件定时器
// 每0.5ms将 bTimerHalfMs 置1
//
//==============================================================================
void TimerDeal(void)
{
    timerTicker++;

#if 0
// 软件定时器
    if (timerTicker - timerTicker1msOld >= 1 * 10) // 1ms
    {
        timerTicker1msOld = timerTicker;

        if (++timeRecord.ms >= 1000)    // 计时
        {
            timeRecord.ms = 0;
            if (++timeRecord.s >= 3600)
            {
                timeRecord.s = 0;
                timeRecord.hour++;
            }
        }
    }
#endif

// 软件定时器
#if (0)
    if (timerTicker - timerTickerHalfMsOld >= 5)      // 0.5ms
    {
        timerTickerHalfMsOld = timerTicker;
        bTimerHalfMs = 1;
    }
#elif (1)
    if (timerTicker >= 5) // 0.5ms
    {
        timerTicker = 0;
        bTimerHalfMs = 1;
    }
#endif
}



// ARM_IO GPIO39 Pin175 R204
// DSP_IO GPIO87 Pin174 R203
STATISTICS_STRUCT mainLoopTime;     // DSP 2ms程序执行时间, us
//==============================================================================
//
// DSP处理，相对于ARM处理而言
// 可以认为是2ms调用1次
//
//==============================================================================
/*
void DspDeal(void)
{
    Uint32 baseTime;

    baseTime = GetTime();
    
    RAM_DSP_BUSY_ON;        // 开始操作DPRAM
    Main05msMotorC();
    RAM_DSP_BUSY_OFF;       // 完成操作DPRAM

    mainLoopTime.now = baseTime - GetTime();
    StatisticDeal(&mainLoopTime);

 //  UpdateDataLog();        
}
*/



//==============================================================================
//
// 硬件初始化
// 1. DSP的初始化
// 2. 各种外设的初始化
//
//==============================================================================
void InitHardware(void)
{
    InitCpu();                  // DSP的初始化
    
    InitSystemPeripherals();    // 初始化各种外设
}




//==============================================================================
//
// 初始化各种外设
// 包括:
// 1. IO
// 2. External Interface
// 3. AD7606(AD采样)
// 4. DA
// 5. DSP的一些外设，如ADC, QEP, CAN等
//
//==============================================================================
void InitSystemPeripherals(void)
{
    InitIo();           // 初始化DSP的IO

    InitXintf();        // initializes the External Interface
    
//    InitAd7606();       // 初始化AD采样芯片

//----------------------------------
// DA初始化
   // InitMcbspaIo();
   // InitMcbspDma();     // DMA应该在McBSP之前初始化?
   // InitMcbspaSpi();
  //  InitDa();
//----------------------------------

    InitAdc();          // DSP的AD初始化


    InitEPwmGpio();     // EPWM初始化
    InitEPwm();
    InitEQep1Gpio();
//    InitEQep2Gpio();
    InitFvcEqep();      // QEP初始化

    init_mcbsp_spi();
}




































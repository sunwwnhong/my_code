//==================================================================================================
//
// 速度采样
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_speedSample.h"
#include "m_interfacePublic.h"
#include "m_autoTune.h"



#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_QEP             1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_QEP             0
#endif


#pragma DATA_SECTION(corePgPara, "data_ram");


union PG_PARA corePgPara;
int32 frqMotorRun;              // 编码器反馈速度, 0.01Hz
int32 frqMotorRun1;             // 编码器反馈速度滤波值, 0.01Hz

extern volatile struct EQEP_REGS *pEQepRegsFvc;
extern int16 qepTickerSum;
extern Uint32 qepPeriodSum;
extern Uint16 noQepTickerSum;
extern union DSP_MAIN_COMMAND1 coreMainCmd1;
extern int16 period;


#if DEBUG_P_QEP

//#include "m_hw_qep.c"



int32 frqPg;                   // clk信号频率，Q5
int32 frqPgAfterAver;

#if !DEBUG_PRG_IN_RAM
//#pragma DATA_SECTION(pcRefAverArray, "data_ram");
#endif

#define PC_REF_AVER_NUM     50
int32 pcRefAverArray[PC_REF_AVER_NUM];
int32 pcRefAverSum;
Uint16 iOldFrqPg;
int32 AverFilterDeal1(int32 dataArray[], Uint16 dataNum, int32 *dataSum, int32 newData, Uint16 *iOld);


extern Uint16 polePairs;




#define SPEED_FILTER_N  50
extern int32 coreFrqAimHz;
extern Uint16 coreTuneCmd;
extern union AUTO_TUNE_PARA autoTunePara;    // 调谐参数
//==============================================================================
//
// 反馈速度采样计算
//
//==============================================================================
void pulseInCalcFvcEQep(void)
{
    int32 frq1;
    Uint16 num;
    static Uint16 coreTuneCmdOld;
    static u32 encoderDirTicker;
    
    FvcQepChange();

//    pEQepRegsFvc->QDECCTL.bit.SWAP = corePgPara.elem.encoderDir;
    pEQepRegsFvc->QDECCTL.bit.SWAP = coreMainCmd1.bit.fvcPgLogic;
    if ((TUNE_IM_2 == coreTuneCmd) && (TUNE_IM_2 != coreTuneCmdOld))   
    {
        autoTunePara.code.encoderDir = coreMainCmd1.bit.fvcPgLogic;
    }
    coreTuneCmdOld = coreTuneCmd;
    

    if (!qepTickerSum)
    {
        noQepTickerSum++;

        // 估算
        frq1 = ((CPU_FRQ << 5) / (pEQepRegsFvc->QCTMR + period * 65536UL)) >> 4; //
        //frq1 = (((Uint32)TIME_UNIT_MS_PER_SEC << (1+5)) / (noQepTickerSum * PULSE_IN_CALC_PERIOD) + 1) >> 1;
        // 仅在之前频率大于估算频率时，即频率在减小时，才进行估算。
        if (pEQepRegsFvc->QEPSTS.bit.QDF)
        {
            if (frqPg > frq1)
                frqPg = frq1;
        }
        else
        {
            if (-frq1 > frqPg)
                frqPg = -frq1;
        }

        if (noQepTickerSum > 100)   // 连续100个周期没有捕获，认为给定脉冲频率为0
            frqPg = 0;
    }

    if (qepTickerSum)
    {
        qepPeriodSum += period * 65536UL;
        frqPg = ((int32)((CPU_FRQ << 5) / qepPeriodSum) * qepTickerSum) >> (4+1); // CLK _倍频

        qepTickerSum = 0;
        qepPeriodSum = 0;
        noQepTickerSum = 0;
        period = 0;
    }

    num = SPEED_FILTER_N;
    if (num < sizeof(pcRefAverArray)/sizeof(int32))
    {
        ESTOP0;
    }
    frqPgAfterAver = AverFilterDeal1(pcRefAverArray, num, &pcRefAverSum, frqPg, &iOldFrqPg);

    // frqPg * polePairs / encoderPulse / 32 * 100
    frqMotorRun = (int32)frqPg * polePairs * 25 / ((int32)corePgPara.elem.encoderPulse*8);

    frqMotorRun1 = (int32)frqPgAfterAver * polePairs * 25 / ((int32)corePgPara.elem.encoderPulse*8);

    if (TUNE_IM_2 == coreTuneCmd)   // 完整调谐，自动获得AB相序，更新一次
    {
        if (((frqMotorRun > 300) && (coreFrqAimHz < 0)) ||
            ((frqMotorRun < -300) && (coreFrqAimHz > 0))
            )
        {
            encoderDirTicker++;
            if (100 == encoderDirTicker)
            {
               autoTunePara.code.encoderDir = !(autoTunePara.code.encoderDir & 0x0001); 
            }
        }
    }
    else
    {
        encoderDirTicker = 0;
    }
}





//==============================================================================
//
// 平滑滤波
//
//==============================================================================
int32 AverFilterDeal1(int32 dataArray[], Uint16 dataNum, int32 *dataSum, int32 newData, Uint16 *iOld)
{
    int32 aver;

    if (0 == dataNum)
    {
        return newData;
    }

    *dataSum = *dataSum - dataArray[*iOld] + newData;
    dataArray[*iOld] = newData;
    *iOld = *iOld + 1;
    if (*iOld >= dataNum)
    {
        *iOld = 0;
    }

    aver = *dataSum / dataNum;

    return aver;
}

#elif 1

//extern void InitEQep1Gpio(void);
//extern void InitEQep2Gpio(void);


void InitFvcEqep(void){}
void pulseInCalcFvcEQep(void){}
void pulseInSampleFvcQep(void){}


#endif




//==================================================================================================
//
// 调谐。
// 辨识参数:
// 1. 定子电阻
// 2. 漏感 
// 3. 空载电流
// 4. 惯量
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_AUTO_TUNE_H__
#define __M_AUTO_TUNE_H__



#include "main.h"




//================================================================================
enum TUNE_CMD_ENUM
{
    TUNE_NULL,      // 0
    TUNE_IM_1,      // 1, 静止调谐
    TUNE_IM_2       // 2，完整调谐
};



enum AUTO_TUNE_STATUS_WORD
{
    TUNE_STEP_WAIT = 0,                 // 正在辨识，性能没有任何指令
    TUNE_STEP_ACC  = 50,                // 辨识过程中加速
    TUNE_STEP_DEC  = 51,                // 辨识过程中减速
    TUNE_STEP_END  = 100                // 辨识结束。保存结果，减速停机。
};
extern enum AUTO_TUNE_STATUS_WORD coreMotorCtrlTuneStatus;
//================================================================================






//================================================================================
enum autoTuneStatus
{
    AT_INIT,                                        // 0
    AT_DONE,                                        // 1
    AT_STATOR_MEASUREMENT_IN_PROGRESS,              // 2    rs正在
    AT_STATOR_MEASUREMENT_DONE,                     // 3    rs完成
    AT_STATOR_MEASUREMENT_ERROR,                    // 4    rs故障
    AT_LEAKAGE_MEASUREMENT_IN_PROGRESS,             // 5    lSigma正在
    AT_LEAKAGE_MEASUREMENT_DONE,                    // 6    lSigma完成
    AT_LEAKAGE_MEASUREMENT_ERROR,                   // 7    lSigma故障
    AT_NOLOAD_CURRENT_MEASUREMENT_IN_PROGRESS,      // 8    空载电流 正在
    AT_NOLOAD_CURRENT_MEASUREMENT_DONE,             // 9    空载电流 完成
    AT_NOLOAD_CURRENT_MEASUREMENT_ERROR,            // 10   空载电流 故障
    AT_INERTIA_MEASUREMENT_IN_PROGRESS,             // 11   惯量 正在
    AT_INERTIA_MEASUREMENT_DONE,                    // 12   惯量 完成
    AT_INERTIA_MEASUREMENT_ERROR,                   // 13   惯量 故障
    AT_BACKUPEMF_MEASUREMENT_IN_PROGRESS,          // 14   反电动势正在
    AT_BACKUPEMF_MEASUREMENT_IN_DONE,              // 15   反电动势完成
    AT_BACKUPEMF_MEASUREMENT_IN_ERROR,             // 16   反电动势故障
	AT_LEAKAGE_MEASUREMENT_IN_PROGRESS_NEW,        //17   新的互感辨识正在
    AT_LEAKAGE_MEASUREMENT_DONE_NEW,                // 18  新的互感辨识完成
    AT_LEAKAGE_MEASUREMENT_ERROR_NEW,               // 19  新的互感辨识故障
    AT_ABORT                                          // 20
};

struct  autoTuneType
{
    bool   RequestStage1;
    bool   RequestStage2;
    bool   OpenSpeedLoop;
    bool   AutoCalculateCurrentLoop;
    bool   AutoCalculateSpeedLoop;
    bool   AutoCalculateFluxLoop;
    enum autoTuneStatus StatusStage1;
    enum autoTuneStatus StatusStage2;
    f32 SpeedDemand;
    f32 AccelerationRate;
    f32 IqsRef;
    f32 yAlphaS;
    f32 yBetaS;
    f32 iAlphaS;
    f32 iBetaS;
};
extern struct autoTuneType AutoTune;
//================================================================================











void AutoTuneState(void);

void AutoTuneControl(void);

void AutoTuneStage1FastDeal1(void);
void AutoTuneStage1FastDeal2(void);



#endif  // __M_AUTO_TUNE_H__






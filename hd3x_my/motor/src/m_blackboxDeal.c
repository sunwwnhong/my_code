//==================================================================================================
//
// 故障黑匣子数据dsp处理
// 
//
//
// 
//
//==================================================================================================



#include "m_blackBoxDeal.h"
#include "m_interface.h"
#include "m_speedLoop.h"
#include "m_fluxLoop.h"
#include "m_npc.h"
#include "m_output.h"
#include "m_frqSrc.h"


extern f32 spdRef, spdFdb;
extern f32 pllFluxSFrqPu;
//extern f32 synchMotorFieldCurrent;
extern f32 outputE0Fil;
extern f32 inputE0Fil;
extern f32 outputE0AvgFil;
extern f32 inputINegFil;
extern f32 outputINegFil;
extern f32 inputEdNegSeqTotal;
extern f32 yNegSeqTotal;
extern f32 npcPiOutAo;
extern f32 npcDiffAo;
extern f32 LMT_VSC;
extern f32 E1R;
extern f32 idrefWeakField;
extern struct SPEED_REGULATOR_STR spdRegData;
extern struct FLUX_REGULATOR_STR fluxRegData;
extern struct CommandGeneratorType CommandGenerator;





f32 rsvdBlackBox;
extern f32 vaRef_, vbRef_, vcRef_;
extern f32 yAlphaS, yBetaS;
extern f32 yalpha_ob,ybeta_ob;
extern f32 udcFil;
extern f32  unpc1;
extern f32 AlphaOutputVol;
extern f32 BetaOutputVol;


extern f32 AlphaOutputVolOB;
extern f32 BetaOutputVolOB;
extern f32 yAlphaSRef, yBetaSRef;
extern f32 vaLastUpdate, vbLastUpdate, vcLastUpdate; 
extern f32 DeltaImSvc4;
extern f32 ImSvc4FluxRFrq;
extern f32 simpleInvot;
extern f32 simpleInvot1;
extern f32 pllFluxSFrq;
extern f32 pllBackEmfFrqPu;
extern f32 pllFluxSFrqPu;
extern f32 pllBackEmfFrq;












#if DEBUG_BLACK_BOX
const f32 *blackBoxData[] =
{
//  变量地址                                    功能码设置，C0-06~C0-11设置具体的RAM地址
    (f32 *)&rsvdBlackBox,                       // 0  保留，不允许使用，不要修改。
    (f32 *)&CommandGenerator.SpeedReferencePU,  // 1  给定频率
    (f32 *)&OutputProcess.MotorSpeedFilteredPU, // 2  观测器速度反馈
    (f32 *)&spdFdb,                     		// 3  编码器速度反馈
    (f32 *)&spdRegData.out,                     // 4  速度环输出
    (f32 *)&fluxRegData.fluxRef,                // 5  异步机D轴磁链环给定
    (f32 *)&OutputProcess.FluxDS,               // 6  异步机D轴磁链环反馈
    (f32 *)&fluxRegData.out,                    // 7  磁链环输出
    (f32 *)&LMT_VSC,         					// 8  同步机电压环给定
    (f32 *)&E1R,               					// 9  同步机电压环反馈
    (f32 *)&idrefWeakField,               		// 10 同步机电压环输出
    (f32 *)&OutputProcess.IdsRef,				// 11 D轴电流给定
    (f32 *)&OutputProcess.Ids,                  // 12 D轴电流反馈
    (f32 *)&OutputProcess.VdsRef,               // 13 D轴电压指令
    (f32 *)&OutputProcess.IqsRef,               // 14 Q轴电流给定
    (f32 *)&OutputProcess.Iqs,                  // 15 Q轴电流反馈
    (f32 *)&OutputProcess.VqsRef, 				// 16 Q轴电压指令
    (f32 *)&OutputProcess.Frequency,            // 17 输出频率 
    (f32 *)&OutputProcess.DeltaS,               // 18 磁链角度
    (f32 *)&udcFil,								// 19 母线电压
    (f32 *)&npcData.upn,                        // 20 中点偏差反馈
    (f32 *)&npcData.v0,                    		// 21 中点偏差输出
    (f32 *)&vaRef_,                       		// 22 u相输出电压调制比
    (f32 *)&vbRef_,                       		// 23 v相输出电压调制比
    (f32 *)&vcRef_,                       		// 24 w相输出电压调制比
    (f32 *)&outputE0Fil,                       	// 25 输出电压伏秒零序分量
    (f32 *)&inputE0Fil,                       	// 26 输入电压零序分量   
    (f32 *)&outputE0AvgFil,                     // 27 输出电压零序分量
    (f32 *)&inputINegFil,                       // 28 输入电流负序分量
    (f32 *)&outputINegFil,                      // 29 输出电流负序分量
    (f32 *)&inputEdNegSeqTotal,                 // 30 输入电压负序分量
    (f32 *)&yNegSeqTotal,                       // 31 输出电压负序分量
    (f32 *)&OutputProcess.MotorVoltage,         // 32 电机侧输出电压
    (f32 *)&outCurData.u0,                      // 33 u相输出电流零序分量
    (f32 *)&outCurData.v0,                      // 34 v相输出电流零序分量
    (f32 *)&outCurData.w0,                      // 35 w相输出电流零序分量
    (f32 *)&outCurData.u,                       // 36 u相输出电流
    (f32 *)&outCurData.v,                       // 37 v相输出电流
    (f32 *)&outCurData.w,                       // 38 w相输出电流  
    (f32 *)&yAlphaS,              				// 39 Alpha磁链
    (f32 *)&yBetaS,                      		// 40 Beta磁链
    (f32 *)&AlphaOutputVol,                     // 41 w相输出电压零序分量
    (f32 *)&BetaOutputVol,                      // 42 输出电压零序分量
    (f32 *)&ImSvc4FluxRFrq,                     // 43 SVC4频率
    (f32 *)&pllBackEmfFrqPu,                    // 44 反电动势频率
    (f32 *)&pllFluxSFrqPu,                      // 45 w相输出电压
    (f32 *)&simpleInvot,                       	// 46 u相输入电流零序分量
    (f32 *)&simpleInvot1,                       // 47 v相输入电流零序分量
    (f32 *)&inCurData.w0,                       // 48 w相输入电流零序分量
    (f32 *)&inCurData.u,                        // 49 u相输入电流
    (f32 *)&inCurData.v,                        // 50 v相输入电流
    (f32 *)&inCurData.w,                        // 51 w相输入电流
    (f32 *)&inVolData.u0,                       // 52 u相输入电压零序分量
    (f32 *)&inVolData.v0,                       // 53 v相输入电压零序分量
    (f32 *)&inVolData.w0,                       // 54 w相输入电压零序分量
    (f32 *)&inVolData.e0,                       // 55 输入电压零序分量
    (f32 *)&inVolData.u,                        // 56 u相输入电压
    (f32 *)&inVolData.v,                        // 57 v相输入电压
    (f32 *)&inVolData.w,                        // 58 w相输入电压
};
#define BLACKBOX_DATA_ARRY_LENGTH   SIZEOF(blackBoxData)

extern Uint16  blackBoxGroupAddr[];
extern f32 sampleD[6][12];  // 6路通道，2ms最多传递12个快环数据
extern Uint16 ceGroup[];

Uint16 blackBoxDataTicker = 0;  // 每2ms记录的快环数据个数


void BlackBoxDeal(void) // 快环里传递数据
{
    Uint16 i;
    Uint16 blackBoxFunc;

#if 0
    for(i = 0; i < F2C_BLACK_BOX_PARA_LENTH; i++)   // 黑匣子数据通道
    {
        blackBoxFunc = blackBoxGroupAddr[i];
        if (blackBoxSamplePara & (0x0001 << i))     // bit位不等于零，dsp内部RAM地址读取
        {
            sampleD[i][blackBoxDataTicker] = 
                (blackBoxFunc >= 0x0400) ? (*((f32 *)blackBoxFunc)) : 0.0;
        }
        else        // bit位等于零，默认配置
        {
            sampleD[i][blackBoxDataTicker] =
                (blackBoxFunc <= BLACKBOX_DATA_ARRY_LENGTH) ? (*blackBoxData[blackBoxFunc]) : 0.0;
        }
    }
#endif

#if 1
    for(i = 0; i < F2C_BLACK_BOX_PARA_LENTH; i++)   // 黑匣子数据通道
    {
        blackBoxFunc = blackBoxGroupAddr[i];

        if (blackBoxFunc == 0xFFFF)     // 功能过来的地址可能是全F
        {
            blackBoxFunc = 0;
        }

        if (blackBoxFunc < BLACKBOX_DATA_ARRY_LENGTH)
        {
            sampleD[i][blackBoxDataTicker] = *blackBoxData[blackBoxFunc];
        }
        else
        {
            sampleD[i][blackBoxDataTicker] = 
                (blackBoxFunc >= 0x0400) ? (*((f32 *)blackBoxFunc)) : 0.0;
        }
    }

    blackBoxDataTicker++;
    if (blackBoxDataTicker >= C2F_BLACK_BOX_PARA_MAX)
    {
        blackBoxDataTicker = 0;
    }
#endif    
}

#elif 1
void BlackBoxDeal(void)
{
    ;
}

#endif


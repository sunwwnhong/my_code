/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA06_MotEncoder.c
* Version            : V0.1
* Date               : 2024
* Description        : 霍尔信号自解码程序
***********************************************************************************************/
  
#include "Main.h"

MotEncoder_VAR MotEncoder_V;
Mag_Dec MagDec;

//最大最小值判断阈值 (中点电平+峰峰值*0.6/2)/3.3*65536取大于0.6阈值外的计入最大值(以实际测试的原始信号为准计算阈值)
#define Ori_ThresholdH 40513
#define Ori_ThresholdL 26214
void MotEncoder_ST_MT_Get( void )
{
    LONG delta;

    MagDec.A_Ori = AMotVar[0].HallBSIN;//机械狗测试
    MagDec.B_Ori = AMotVar[0].HallBCOS;

    if((Prm.AutoAIAdj & 0x800) == 0x800)
    {
        fun_SinCos_ADC_Correct();
        MotEncoder_V.PosA = 0;
    }
    else
    {
        fun_SinCos_ADC_Deal();
    }


    if( MotEncoder_V.DelayCnt > 50)
    {
        delta = MotEncoder_V.PosA - MotEncoder_V.PosALast;
        if( delta < -32767)
        {
            MotEncoder_V.PoleCnt ++;
            if( MotEncoder_V.PoleCnt >= (Prm.oslv_pol.b.h >> 1))
            {
                MotEncoder_V.PoleCnt = 0;
                MotEncoder_V.Multi ++;
            }
        }
        else if( delta > 32767)
        {
            MotEncoder_V.PoleCnt --;
            if(MotEncoder_V.PoleCnt < 0)
            {
                MotEncoder_V.PoleCnt = (Prm.oslv_pol.b.h >> 1) - 1;
                MotEncoder_V.Multi --;
            }
        }
    }
    else
    {
        MotEncoder_V.DelayCnt ++;
    }
    MotEncoder_V.Single = (MotEncoder_V.PosA + 65536 * MotEncoder_V.PoleCnt) * 2 / (Prm.oslv_pol.b.h) ;
    MotEncoder_V.PosALast = MotEncoder_V.PosA;
}


void fun_SinCos_ADC_Init(void)
{
    uint8_t  i;

    GPIO_setAnalogMode(216, GPIO_ANALOG_ENABLED);//B5可作为GPIO口，左右模拟量口使用时需使能

    MlibResetSHORTMemory( &MotEncoder_V, sizeof( MotEncoder_V ) / 2 );
    MlibResetSHORTMemory( &MagDec, sizeof( MagDec ) / 2 );
    MagDec.MagRing_Pole = Prm.oslv_pol.b.h >> 1;
    for( i = 0; i < MagDec.MagRing_Pole+2; i++)
    {
        MagDec.A_Max[i] = 32768;
        MagDec.B_Max[i] = 32768;
        MagDec.A_Min[i] = 32768;
        MagDec.B_Min[i] = 32768;
    }
    MagDec.first = 1;
}
/*===========================================
@ Func: fun_SinCos_ADC_Correct
@ Note: 用于得到幅值、偏置校准值、以及校准完成标志
============================================*/
void fun_SinCos_ADC_Correct(void)
{
    static uint16_t AMax_Cnt =0;
    static uint16_t BMax_Cnt =0;
    static uint8_t  AMax_Cnt_En =0;
    static uint8_t  BMax_Cnt_En =0;
    static uint8_t  R_Cnt =0;
    uint8_t  i;
    //static uint16_t SinCosEnc_A_flt =0;
    //static uint16_t SinCosEnc_B_flt =0;

    /* 得到校准命令后，取1000组最大最小值 */

    //SinCosEnc_A_flt += ((SinCosEnc_A - SinCosEnc_A_flt)/SinCosPg_fltcoef);
    //SinCosEnc_B_flt += ((SinCosEnc_B - SinCosEnc_B_flt)/SinCosPg_fltcoef);
    if(MagDec.A_Ori > Ori_ThresholdH)  //(中点电平+峰峰值*0.6/2)/3.3*65536取大于0.6阈值外的计入最大值(以实际测试的原始信号为准计算阈值)
    {
        if(MagDec.A_Max[AMax_Cnt] < MagDec.A_Ori)
        {
            MagDec.A_Max[AMax_Cnt] = MagDec.A_Ori;
        }
        if(AMax_Cnt_En)
        {
            AMax_Cnt++;
            AMax_Cnt_En =0;
        }
    }
    else if(MagDec.A_Ori < Ori_ThresholdL)
    {
        if(MagDec.A_Min[AMax_Cnt] > MagDec.A_Ori)
        {
            MagDec.A_Min[AMax_Cnt] = MagDec.A_Ori;
        }
        AMax_Cnt_En =1;
    }
    if(MagDec.B_Ori > Ori_ThresholdH)
    {
        if(MagDec.B_Max[BMax_Cnt] < MagDec.B_Ori)
        {
            MagDec.B_Max[BMax_Cnt] = MagDec.B_Ori;
        }
        if(BMax_Cnt_En)
        {
            BMax_Cnt++;
            BMax_Cnt_En =0;
        }
    }
    else if(MagDec.B_Ori < Ori_ThresholdL)
    {
        if(MagDec.B_Min[BMax_Cnt] > MagDec.B_Ori)
        {
            MagDec.B_Min[BMax_Cnt] = MagDec.B_Ori;
        }
        BMax_Cnt_En =1;
    }

    if(AMax_Cnt >=(MagDec.MagRing_Pole+1) && BMax_Cnt >=(MagDec.MagRing_Pole+1))
    {
        for(i=1;i<(MagDec.MagRing_Pole+1);i++)
        {
            MagDec.A_Max_ave += MagDec.A_Max[i];
            MagDec.A_Min_ave += MagDec.A_Min[i];
            MagDec.B_Max_ave += MagDec.B_Max[i];
            MagDec.B_Min_ave += MagDec.B_Min[i];
        }
        R_Cnt++;
        AMax_Cnt =0;
        BMax_Cnt =0;
        AMax_Cnt_En =0;
        BMax_Cnt_En =0;
        for( i = 0; i < MagDec.MagRing_Pole+2; i++)
        {
            MagDec.A_Max[i] = 32768;
            MagDec.B_Max[i] = 32768;
            MagDec.A_Min[i] = 32768;
            MagDec.B_Min[i] = 32768;
        }
    }

    if(R_Cnt>=8)
    {
        MagDec.A_Max_ave = MagDec.A_Max_ave/(MagDec.MagRing_Pole<<3);
        MagDec.A_Min_ave = MagDec.A_Min_ave/(MagDec.MagRing_Pole<<3);
        MagDec.B_Max_ave = MagDec.B_Max_ave/(MagDec.MagRing_Pole<<3);
        MagDec.B_Min_ave = MagDec.B_Min_ave/(MagDec.MagRing_Pole<<3);

        MagDec.A_Offset = (MagDec.A_Max_ave + MagDec.A_Min_ave)>>1;
        MagDec.AB_Gain =  (USHORT)((MagDec.A_Max_ave - MagDec.A_Min_ave)*2048/(MagDec.B_Max_ave - MagDec.B_Min_ave));
        MagDec.B_Offset = (MagDec.B_Max_ave + MagDec.B_Min_ave)>>1;
        Prm.AutoAIAdj = 0;
    }

}

/*===========================================
@ Func: fun_SinCos_ADC_Deal
@ Note: 对正余弦进行幅值、偏置校准，并得到电角度
注意：实测调整霍尔的相位补偿*******************
============================================*/
void fun_SinCos_ADC_Deal(void)
{

    if(Prm.Pn540)
    {
        MagDec.A = (SHORT)Prm.Pn540 - (SHORT)MagDec.A_Ori;
        MagDec.B = (SHORT)(((LONG)((SHORT)Prm.Pn541 - (SHORT)MagDec.B_Ori)) * Prm.Pn542 >>11);
    }
    else
    {
        MagDec.A = 32569 - MagDec.A_Ori;
        MagDec.B = 32569 - MagDec.B_Ori;
    }

    AinK.Monitor2 = MagDec.B;

    if(Prm.Pn533)
        MagDec.Theta = MlibAtan16(MagDec.A,MagDec.B);//机械狗测试
    else
        MagDec.Theta = MlibAtan16(MagDec.B,MagDec.A);//调整A/B，B/A调整角度增减方向,前一个为cos

   if(((LONG)MagDec.Theta)<0)
        MagDec.Theta = MotEncoder_V.PosA;

    //fun_SinCos_PLL();
    MotEncoder_V.PosA = MagDec.Theta;

    AinK.Monitor4 = MotEncoder_V.PosA;
    AinK.Monitor5 = MagDec.A;
}

/*===========================================
@ Func: fun_SinCos_PLL
@ Note: 以反正切值为PLL初始角度进行锁相
============================================*/
void fun_SinCos_PLL(void)
{
    float kiTsBy2;

    if(MagDec.first == 1)
    {
        //MagDec.Theta = MlibAtan16(MagDec.A,MagDec.B);//调整A/B，B/A调整角度增减方向
        MagDec.Theta = MlibAtan16(MagDec.B,MagDec.A);//机械狗测试
        MagDec.angleObs = ((float)MagDec.Theta / 32768.0f - 1.0f);
        MagDec.first = 0;
        return;
    }

    // Pn553 filter corner frequency (Hz)
    // Pn554  pi controller - prop gain
    // Pn555  pi controller - ZERO frequency
    // 角度 -1~1
    MagDec.errorWfT  = (float)Prm.Pn553  * 6.283185307f * 62.5f /1000000.0f;
    kiTsBy2 = (float)Prm.Pn554 * ((float)Prm.Pn555 * 6.283185307f) * 62.5f /1000000.0f;
    MagDec.picon_K0  =  (float)Prm.Pn554 + kiTsBy2;
    MagDec.picon_K1  = -(float)Prm.Pn554 + kiTsBy2;

    MagDec.angleObs = (MagDec.rpsObs * 62.5f /1000000.0f) + MagDec.angleObs;   // Feedback calc -  integral of speed

    if(MagDec.angleObs > 1.0f)
    {
        MagDec.angleObs -= 2.0f;
    }
    else if(MagDec.angleObs < -1.0f)
    {
        MagDec.angleObs += 2.0f;
    }

    MagDec.errorOld  = MagDec.errorNew;                                   // save prev error
    //MagDec.errorNew  = MagDec.Theta - MagDec.angleObs;      // calc new error
    MagDec.errorNew  = __cos((MagDec.angleObs+1.0f) * 3.141592653589f) * (MagDec.A / 32768.0f) + __sin((MagDec.angleObs+1.0f) * 3.141592653589f) * (MagDec.B / 32768.0f);
    //MagDec.errorNew  = __cos((MagDec.angleObs+1.0f) * 3.141592653589f) * (MagDec.B / 32768.0f) + __sin((MagDec.angleObs+1.0f) * 3.141592653589f) * (MagDec.A / 32768.0f);
    if(MagDec.errorNew > 1.0f)
    {
        MagDec.errorNew -= 2.0f;
    }
    else if(MagDec.errorNew < -1.0f)
    {
        MagDec.errorNew += 2.0f;
    }

    MagDec.errorNew  = MagDec.errorOld + (MagDec.errorNew-MagDec.errorOld) * MagDec.errorWfT;    // error filter

         // Resolver speed estimation - PI controller
    MagDec.rpsObs += (MagDec.picon_K0 * MagDec.errorNew) + (MagDec.picon_K1 * MagDec.errorOld);
    MagDec.rpsObs = FlibLimitul(MagDec.rpsObs, 400.0f, -400.0f);   //

    MagDec.Theta = (ULONG)((MagDec.angleObs + 1.0f) * 32768.0f);

}


USHORT CorrectSaveEn = 0;                  // 校准数据存储使能
USHORT CorrectSaveStep = 0;

void CorrectSave(void)
{
    if((Prm.AutoAIAdj & 0x1000) == 0x1000)
    {
        CorrectSaveEn = 1;
    }

    if( CorrectSaveEn && (CorrectSaveStep  == 0))
    {
        Prm.Pn540 = MagDec.A_Offset;
        Prm.Pn541 = MagDec.B_Offset;
        Prm.Pn542 = MagDec.AB_Gain;

        CorrectSaveStep = 1;
    }
    switch( CorrectSaveStep )
    {
        /*------------------------------------------------------------------------------------------*/
        case 0:
        break;
        /*------------------------------------------------------------------------------------------*/
        case 1:
            (void)RpiFunPrmNvmemUpdate( &pndef_Pn540 );                  /* 16位数据一次写入     */
            CorrectSaveStep  ++;
        break;
        case 20:
            (void)RpiFunPrmNvmemUpdate( &pndef_Pn541 );                   /* 16位数据一次写入     */
            CorrectSaveStep  ++;
        break;
        case 40:
            (void)RpiFunPrmNvmemUpdate( &pndef_Pn542 );                   /* 16位数据一次写入     */
            CorrectSaveStep  ++;
        break;
        case 60:
            CorrectSaveStep  = 0;
            CorrectSaveEn  = 0;
            Prm.AutoAIAdj = 0;
        break;
        /*------------------------------------------------------------------------------------------*/
        default:
            CorrectSaveStep ++;
        break;
    }
}

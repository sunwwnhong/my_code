/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*                                          2018 ~                                                  */
/****************************************************************************************************/
/*文件名:UserC_InnerSourceTrig.c                                                                             */
/*创建时间:2023.02.09                                                                               */
/*版本说明:V1.0                                                                                     */
/*功能描述:                                                                                         */
/****************************************************************************************************/
#include "Main.h"
#include "UserC_InnerSourceTrig.h"


INNERSIGNAL CurSig;  //内部电流信号给定
INNERSIGNAL SpdSig;  //内部速度信号给定

#define CUR_TRIG_PRD  16000
#define SPD_TRIG_PRD  8000


/****************************************************************************************************/
/*Function_Name: InputCurSigParaReset                                                                      */
/*Description : 内部电流信号初始化                                                                      */
/****************************************************************************************************/
void InputCurSigParaReset()
{
#ifdef INNER_INPUT_FUNC
     CurSig.SglTrig = Prm.CurIntrig;
     CurSig.SglType = Prm.CurType;
     CurSig.AmpVal =  (LONG)((SHORT)Prm.CurAmp) * 10;
     CurSig.Tperiod = CUR_TRIG_PRD / Prm.CurFreq;
     CurSig.OffSet = (LONG)((SHORT)Prm.CurOffSet) * 10;
     CurSig.Tcnt = 0;
#endif
}


/****************************************************************************************************/
/*Function_Name: InputSpdSigParaReset                                                          */
/*Description  :内部转速信号初始化                                                                     */
/***********************************************************************************************/

void InputSpdSigParaReset()
{
#ifdef INNER_INPUT_FUNC
     SpdSig.SglTrig = Prm.SpdIntrig;
     SpdSig.SglType = Prm.SpdType;
     SpdSig.AmpVal =  (LONG)((SHORT)Prm.SpdAmp);
     SpdSig.Tperiod = SPD_TRIG_PRD / Prm.SpdFreq;
     SpdSig.OffSet = (LONG)((SHORT)Prm.SpdOffSet);
     SpdSig.Tcnt = 0;
#endif
}



/****************************************************************************************************/
/*Function_Name: InnerInputCal                                                         */
/*Description  :内部信号正弦/方波计算                                                  */
/***********************************************************************************************/
LONG InnerInputCal(INNERSIGNAL *Input)
{
#ifdef INNER_INPUT_FUNC
    LONG OutTmp;
    if(!Input->SglTrig || !CoutV.f.Sv.BaseEnable)
    {
       Input->OutVal = 0;
       Input->Tcnt = 0;
    }
    else
    {
       Input->Tcnt ++;
       if(Input->Tcnt >= Input->Tperiod)
         Input->Tcnt = 0;
       Input->Theta = Input->Tcnt * 1024 /Input->Tperiod;
       if( Input->SglType )  //方波计算
       {
          if(Input->Theta > 512)
             OutTmp = Input->AmpVal;
          else
             OutTmp = 0;
       }
       else     //正弦波计算
       {
          OutTmp =  (Input->AmpVal * MlibFastSinTbl[Input->Theta]) >> 14;
       }
       Input->OutVal = OutTmp + Input->OffSet;

    }
    return Input->OutVal;
#endif
}




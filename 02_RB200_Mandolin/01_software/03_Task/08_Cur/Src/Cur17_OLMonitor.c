/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur17_OLMonitor.c.c
* Version            : V0.1
* Date               : 2024
* Description        : 过载故障保护--电流类故障
***********************************************************************************************/

#include "Main.h"
  
typedef  struct
{
    float fTmid;    // 中间电流运行时，过载检测时间[0.1S]
    float fTmax;    // 最大电流运行时，过载检测时间[0.1S]
    float fIbse;    // 过载检测基极电流[15000]
    float fImid;    // 过载检测中间电流[15000]
    float fImax;    // 过载检测最大电流[15000]
} OLPRM;
  
  
/**********************************************************************************************/
/* Function_Name: LpxPcalOverLoadLevelAmpMot                                                  */
/* Description  : 中间电流运行和最大电流运行时，过载报警值计算        标幺根据15000计算
                  调用位置：初始化调用一次
                  输入：过载设定值、过载管理结构体
                  输出：更新过载管理结构体数据    */
/**********************************************************************************************/
LONG LpxPcalOverLoadLevelAmpMot( OLPRM *OlPrm, CHKOLP *ChkOLP1, CHKOLP *ChkOLP2, CHKOLP *ChkOLP3 )
{
    float fIx;
    float fIbsqr;
    float fIxsqr;
    float fIysqr;
    float fIzsqr;
    float fwk;
    LONG rc = TRUE;
    LONG cflg;

    /*** 过载检测基极电流大于电机最大电流值15000，情况下，若1、2不相等则用2并返回；若相等，则报错返回。 ***/
    cflg = ( ChkOLP1 != ChkOLP2 )? TRUE:FALSE;
    if( OlPrm ->fIbse > 15000.0f )
    {
        //Note：小功率驱动器匹配大功率电机可能导致如下逻辑，最终导致故障误报，避免超出最大电流，电机过载与驱动器过载采用一致的过载时间处理
        if(cflg == TRUE)
        {
            ChkOLP1->fIbsqrmid     = ChkOLP2->fIbsqrmid;               
            ChkOLP1->fAlmLvlmid    = ChkOLP2->fAlmLvlmid;              
            ChkOLP1->fWrnLvlmid    = ChkOLP2->fWrnLvlmid;              
            ChkOLP1->fOlLvlmidGain = ChkOLP2->fOlLvlmidGain;           
            ChkOLP1->fIbsqrmax     = ChkOLP2->fIbsqrmax;               
            ChkOLP1->fAlmLvlmax    = ChkOLP2->fAlmLvlmax;              
            ChkOLP1->fWrnLvlmax    = ChkOLP2->fWrnLvlmax;              
            ChkOLP1->fOlLvlmaxGain = ChkOLP2->fOlLvlmaxGain;           
            return ( TRUE );
        }
        else
        {
            return ( FALSE );                                        
        }
    }
    else     // 过载检测基极电流在正常范围内，进行下一步计算
    {
        fIx = OlPrm->fIbse;
    }
      

    fIbsqr   = fIx * fIx / 65536.0f;                // 基极电流平方
    fIx      = ( OlPrm->fImid > 32767.0f ) ? 32767.0f : OlPrm->fImid;   // 中间电流限幅
    fIxsqr   = fIx * fIx / 65536.0f;                                // 中间电流平方
    fIzsqr                 = fIxsqr - fIbsqr;                // 中间电流平方减去基极电流平方
    ChkOLP1->fIbsqrmid     = fIbsqr;

    /*** 计算中间电流过载报警值：（中间电流平方 - 基极电流平方）* 时间（100ms） ***/
    ChkOLP1->fAlmLvlmid    = fIzsqr * 100.0f * OlPrm->fTmid/ (float)KPI_SCCYCLEMS;
    ChkOLP1->fWrnLvlmid    = ChkOLP1->fAlmLvlmid * (float)Prm.olwarlvl / 100.0f;
    ChkOLP1->fOlLvlmidGain = ChkOLP3->fAlmLvlmid * 1.0f / ChkOLP1->fAlmLvlmid;
    if( ( ChkOLP1->fAlmLvlmid >= 1073741824.0f) || ( ChkOLP1->fAlmLvlmid == 0.0f ) )
    {
        rc = FALSE;
    }
    /*** 过载检测最大电流大于0x7FFF，情况下，若1、2不相等则用2并返回；若相等，则报错返回。 ***/
    if( OlPrm->fImax > 32767.0f )                                    
    {
        if(cflg == TRUE)
        {
            ChkOLP1->fIbsqrmax     = ChkOLP2->fIbsqrmax;             
            ChkOLP1->fAlmLvlmax    = ChkOLP2->fAlmLvlmax;            
            ChkOLP1->fWrnLvlmax    = ChkOLP2->fWrnLvlmax;            
            ChkOLP1->fOlLvlmaxGain = ChkOLP2->fOlLvlmaxGain;         
 
            return ( TRUE );                                         
        }
        else
        {
            return ( FALSE );                                        
        }
    }// 过载检测最大电流在正常范围内，进行下一步计算
    else
    {
        fIx = OlPrm -> fImax;
    }

    fIysqr = fIx * fIx / 65536.0f;        // 最大电流平方
    fwk    = ( fIxsqr * OlPrm->fTmid ) - ( fIysqr * OlPrm->fTmax ); // 中间电流平方*对应时间-最大电流平方*对应时间
    /*** (中间电流平方*对应时间-最大电流平方*对应时间)/(中间电流时间-最大电流时间) ***/
    fIbsqr = fwk * 1.0f / ( OlPrm->fTmid - OlPrm->fTmax );
    /*** 若wk小于0，则最大电流过载相关警告值清零，并返回错误。 ***/
    if( fwk < 0.0f )
    {
        ChkOLP1->fIbsqrmax     = 0.0f;                               
        ChkOLP1->fAlmLvlmax    = 0.0f;                               
        ChkOLP1->fWrnLvlmax    = 0.0f;                               
        ChkOLP1->fOlLvlmaxGain = 0.0f;                               
        return ( FALSE );                                            
    }
    else    // 正常下，进行下一步计算
    {
        /*** Ibsqr合法性判断和处理 ***/
        if( fIbsqr > 32767.0f)
        {
            if( cflg == TRUE )
            {
                fIbsqr = ChkOLP2->fIbsqrmax;              
            }
            else
            {
                return ( FALSE );                       
            }
        }
        /*** 若Ibsqr小于基极电流的平方，则最大电流过载检测和中间电流过载检测报警值一致 ***/
        if( fIbsqr < ChkOLP1->fIbsqrmid )
        {
            ChkOLP1->fIbsqrmax       = ChkOLP1->fIbsqrmid;              
            ChkOLP1->fAlmLvlmax      = ChkOLP1->fAlmLvlmid;             
            ChkOLP1->fWrnLvlmax      = ChkOLP1->fWrnLvlmid;             
            ChkOLP1->fOlLvlmaxGain   = ChkOLP3->fAlmLvlmax / ChkOLP1->fAlmLvlmax; 
        }
        // 若Ibsqr大于基极电流的平方，进行如下计算
        else
        {
            fIzsqr                = fIysqr - fIbsqr;
            ChkOLP1->fIbsqrmax     = fIbsqr;
            /*** 计算最大电流过载报警值：（最大电流平方 - Ibsqr）*时间 ***/
            ChkOLP1->fAlmLvlmax    = fIzsqr * 100.0f * OlPrm->fTmax / (float)KPI_SCCYCLEMS;
            /*** 根据最大电流过载报警值和过载警告百分比，计算最大电流过载警告值 ***/
            ChkOLP1->fWrnLvlmax    = ChkOLP1->fAlmLvlmax * (float)Prm.olwarlvl / 100.0f;
            ChkOLP1->fOlLvlmaxGain = ChkOLP3->fAlmLvlmax * 1.0f / ChkOLP1->fAlmLvlmax;
            /*** 计算最大电流过载报警值合法性检查，超范围则报错 ***/
            if( ChkOLP1->fAlmLvlmax >= 1073741824.0f )
            {
                rc = FALSE;
            }
        }
    }
    return ( rc );
}
  
  
/**********************************************************************************************/
/* Function_Name: IprmcalOverLoadLevelAmpMot                     */
/* Description  : 电机和驱动器过载参数计算
                  调用位置：初始化调用一次
                  输入：各个过载设定参数
                        PnE06   驱动器过载检测电流
                        PnE07   驱动器过载检测时间
                        PnE08   驱动器过载检测时间微调
                        PnE09   电机过载检测时间微调
                  输出：过载执行过程参数       */
/**********************************************************************************************/
void IprmcalOverLoadLevelAmpMot( void )
{
float fks,fks2;
OLPRM Mot,Amp;
    UCHAR prmchk;

    /*** 编码器未连接，直接返回，因为电机参数都存储在编码器中 ***/
    if( MencV.f.EncConnect != TRUE )
    {
        return;
    }

    /*** 电机中间电流运行时，过载检测时间小于1S时，采用驱动器中间电流过载检测百分比+5计算,不是很合理，
        应该是对应的驱动器时间Prm.imdt_mxt.b.l ***/
//    if( Prm.midolt <= 1 )
//    {
//        Prm.midolt = (Prm.ibs_md.b.h) + 5;
//    }
    Mot.fTmid = (float)( Prm.midolt * (Prm.ratmtt_2.b.l & 0x00FF) ) / 10.0f;  // 电机中间电流运行时，过载检测时间微调计算[0.1S]
      
    /*** 电机最大电流运行时，过载检测时间小于3S时，采用驱动器最大电流过载检测时间+5计算 ***/
//    if( Prm.mtolt2 <= 3 )
//    {
//        Prm.mtolt2 = (Prm.imdt_mxt.b.h) + 5;
//    }
    Mot.fTmax = (float)( Prm.mtolt2 * ( Prm.ratmtt_2.b.h ) ) / 10.0;  // 电机最大电流运行时，过载检测时间微调计算
      
    /*** 得到电机相关：基于百分比[0.01%]的，最大转矩的标幺化系数和考虑电机过载检出基极电流降额设定[%]下的标幺化系数 ***/
    fks = 100.0f * Bprm.fPerMaxTrq / 15000.0f;
    fks2 = 10000.0f * Bprm.fPerMaxTrq / (15000.0f * (float)Prm.mtbastrq_drt);
      
     /*** 电机过载检出基极电流为0时，设定基极电流为115%；电机过载检测中间电流为0时，设定为驱动器中间电流
        过载检测时间，这里不合理，应该是对应的驱动器电流Prm.ibs_md.b.l[10%] ***/
    if( Prm.bastrq == 0 ) Prm.bastrq    = 115;
    if( Prm.midtrq == 0 ) Prm.midtrq    = (Prm.imdt_mxt.b.l & 0x00FF) * 10;

    /*** 在最大转矩或电机过载检测最大电流为0情况下，设置电机过载检测最大电流  ***/
    if( Bprm.PerMaxTrq == 0 )
    {
         Prm.mtrq2 = 300;
    }
    else
    {
        if( Prm.mtrq2 == 0 )  Prm.mtrq2     = Bprm.PerMaxTrq;
    }
    /*** 电机过载检测基极电流、中间电流、最大电流的标幺化计算 ***/
    Mot.fIbse = (float)Prm.bastrq * 100.0f / fks2;
    Mot.fImid = (float)Prm.midtrq * 100.0f / fks;                       
    Mot.fImax = (float)Prm.mtrq2 * 100.0f / fks;                        

    /*** 驱动器过载检测中间电流、最大电流的过载检测时间微调计算[0.1S] ***/
    Amp.fTmid = (float)( (Prm.imdt_mxt.b.l & 0x00FF) * ( Prm.ratbt_mt.b.l & 0x00FF )) / 10.0f;
    Amp.fTmax = (float)( (Prm.imdt_mxt.b.h) * (Prm.ratbt_mt.b.h ) ) / 10.0f;

    /*** 得到驱动器相关：基于实际电流[10000*A]的、最大转矩的标幺化系数和考虑单相驱动器过载检出基极电流降额设定[%]下的标幺化系数 ***/
    fks = 100.0f * (float)Prm.irat * Bprm.fPerMaxTrq / 15000.0f;
      
    // 单相电源输入时伺服单元过载检测电流降额百分比
    if( Iprm.f.SnglPhBaseDerate == TRUE )
    {
        fks2 = 10000.0f * (float)Prm.irat * Bprm.fPerMaxTrq / (15000.0f * (float)Prm.snglph_base_drt);
    }
    else
    {
        fks2 = 100.0f * (float)Prm.irat * Bprm.fPerMaxTrq / 15000.0f;
    }

    /*** 驱动器过载检测基极电流、中间电流、最大电流的标幺化计算 ***/
    Amp.fIbse = (float)( Prm.ibs_md.b.l & 0x00FF ) * (float)Prm.irats * 100.0f / fks2;
    Amp.fImid = 10.0f * (float)(Prm.ibs_md.b.h) * (float)Prm.irats * 100.0f / fks;
    Amp.fImax = 100.0f * (float)Prm.imaxs * 100.0f / fks;

    prmchk = TRUE;

    /*** 电机/驱动器过载电流和过载时间合法性检查：中间时间必须大于最大时间，电流大小依次为最大电流、中间电流、基极电流 ***/
    if( Mot.fTmid <= Mot.fTmax )
    {
        KpiSetParamError( &pndef_midolt );
        prmchk = FALSE;
    }
    if( Mot.fImid >= Mot.fImax )
    {
        KpiSetParamError( &pndef_midtrq );
        prmchk = FALSE;
    }
    if( Mot.fImid <= Mot.fIbse )
    {
        KpiSetParamError( &pndef_bastrq );
        prmchk = FALSE;
    }
    if( Amp.fTmid <= Amp.fTmax )
    {
        KpiSetParamError( &pndef_imdt_mxt );
        prmchk = FALSE;
    }
    if( Amp.fImid >= Amp.fImax )
    {
        KpiSetParamError( &pndef_ibs_md );
        prmchk = FALSE;
    }
    if( Amp.fImid <= Amp.fIbse )
    {
        KpiSetParamError( &pndef_ibs_md );
        prmchk = FALSE;
    }

    /*** 参数合法检测通过，则计算过载报警值 ***/
    if( prmchk == TRUE )
    {
        /*** 电机过载和驱动器过载，哪个过载电流小先计算哪个过载阈值，然后计算另一个过载电流大的过载阈值 ***/
        if( Amp.fImax > Mot.fImax )
        {
              
            if( LpxPcalOverLoadLevelAmpMot( &Mot, &ChkAlmP.MotOLP, &ChkAlmP.MotOLP, &ChkAlmP.MotOLP ) != TRUE )
            {
                KpiSetParamError( &pndef_midtrq );
            }

            if( LpxPcalOverLoadLevelAmpMot( &Amp, &ChkAlmP.AmpOLP, &ChkAlmP.MotOLP, &ChkAlmP.AmpOLP ) != TRUE )
            {
                KpiSetParamError( &pndef_ibs_md );
            }
        }
        else
        {
            if( LpxPcalOverLoadLevelAmpMot( &Amp, &ChkAlmP.AmpOLP, &ChkAlmP.AmpOLP, &ChkAlmP.AmpOLP ) != TRUE )
            {
                KpiSetParamError( &pndef_ibs_md );
            }

            if( LpxPcalOverLoadLevelAmpMot( &Mot, &ChkAlmP.MotOLP, &ChkAlmP.AmpOLP, &ChkAlmP.MotOLP ) != TRUE )
            {
                KpiSetParamError( &pndef_midtrq );
            }
        }
    }
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: LpxExeCheckOLAmpMot         */
/* Description  : 电机和驱动器过载检测执行
                  调用位置：SCANC（2msISR）中的故障检测主函数中执行
                  输入：实际运行电流的平方，过载检测变量结构体指针，过载检测参数结构体指针，
                  过载检测类型（电机or驱动器）
                  输出：过载检测执行并条件满足时触发报警       */
/**********************************************************************************************/
void LpxExeCheckOLAmpMot( float fIxsqr, CHKOLV  *ChkOLV, CHKOLP *ChkOLP ,USHORT Type)
{
    float fSumx;
      
    ChkOLV->WrnInfo = 0x00;
 
    /*** 计算最大电流运行下的过载累积量 ***/
    fSumx = ChkOLV->fSumImax + ( fIxsqr - ChkOLP->fIbsqrmax ) * ChkOLP->fOlLvlmaxGain ;
    /*** 最大电流运行下的过载累积量，一旦大于过载故障阈值，则触发报警 ***/
    if( fSumx > ChkOLP->fAlmLvlmax )                             
    {
        ChkOLV->fSumImax = fSumx;
        if( Type == 0 )
        {
            KPI_ALARMSET( ALM_OLM1 );
        }
        else
        {
            KPI_ALARMSET( ALM_OLS1 );
        }
    }
    /*** 最大电流运行下的过载累积量，一旦大于过载警告阈值，则触发警告 ***/
    if( fSumx >= ChkOLP->fWrnLvlmax )
    {
        ChkOLV->fSumImax  = fSumx;
        ChkOLV->WrnInfo |= 0x01;                                 
    }
    else
    {
        /*** 最大电流过载累积量大于0，则执行累积锁存，若小于0，则清零累积锁存值 ***/
        if( fSumx >= 0.0f )                                      
        {
            ChkOLV->fSumImax = fSumx;
        }
        else                                                     
        {
            ChkOLV->fSumImax = 0.0f;
        }
    }
    /*** 计算中间电流运行下的过载累积量 ***/
    fSumx = ChkOLV->fSumImid + ( fIxsqr - ChkOLP->fIbsqrmid ) * ChkOLP->fOlLvlmidGain;
    if( fSumx >= ChkOLP->fAlmLvlmid )
    {
        ChkOLV->fSumImid = fSumx;
        if( Type == 0 )
        {
            KPI_ALARMSET( ALM_OLM2 );
        }
        else
        {
            KPI_ALARMSET( ALM_OLS2 );
        }
    }
    /*** 中间电流运行下的过载累积量，一旦大于过载报警阈值，则触发报警 ***/
    if( fSumx >= ChkOLP->fWrnLvlmid )
    {
        ChkOLV->fSumImid  = fSumx;
        ChkOLV->WrnInfo |= 0x02;                                 
    }
    else
    {
        /*** 中间电流过载累积量大于0，则执行累积锁存，若小于0，则清零累积锁存值 ***/
        if( fSumx >= 0.0f )                                          
        {
            ChkOLV->fSumImid = fSumx;
        }
        else                                                     
        {
            ChkOLV->fSumImid = 0.0f;
        }
    }
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxCheckOverLoadAmpMot         */
/* Description  : 电机和驱动器过载检测及处理
                  调用位置：SCANC（2msISR）中的故障检测主函数中执行
                  输入：d轴电流和q轴电流
                  输出：过载检测并计算过载率     */
/**********************************************************************************************/
void LpxCheckOverLoadAmpMot( void )
{
    float Ixsqr;
    /*** 计算d轴电流和q轴电流的平方和，得到实际电流峰值的平方 ***/
    Ixsqr = ((LONG)CinK.IdRefMon * CinK.IdRefMon + (LONG)CinK.IqRefMon * CinK.IqRefMon) >> 16;

    /*** 电机驱动器过载未屏蔽，且编码器连接情况下，执行过载检测 ***/
    if( ((Prm.almmsk1 & 0x0004) == 0x0000)  && ( MencV.f.EncConnect == TRUE))
    {
        LpxExeCheckOLAmpMot( Ixsqr, &ChkAlmV.MotOLV, &ChkAlmP.MotOLP, 0 );
        LpxExeCheckOLAmpMot( Ixsqr, &ChkAlmV.AmpOLV, &ChkAlmP.AmpOLP, 1 );
          
        // 若电机或驱动器过载警告标志不为0，则触发过载警告
        if( ChkAlmV.MotOLV.WrnInfo || ChkAlmV.AmpOLV.WrnInfo )
        {
            KPI_WARNINGSET  ( WRN_OLF );
        }
        else
        {
            KPI_WARNINGCLR  ( WRN_OLF );
        }
    }
    return;
}
 
 

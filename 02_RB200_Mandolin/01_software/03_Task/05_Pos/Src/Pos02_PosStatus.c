/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos02_PosStatus.c
* Version            : V0.1
* Date               : 2023
* Description        : 位置控制状态判定
***********************************************************************************************/
  
#include "Main.h"
 
TRGTRCH  Trgtrch;
void PositionSignal_6041bit10(void);
  
/**********************************************************************************************/
/* Function_Name: LpxCheckPerrOverFlow                                                        */
/* Description  : 位置偏差过大、伺服位置限制误差偏差过大判定 
       相关功能码： 
            标准机型：Pn264 位置偏差过大故障阈值
                      Pn266 位置偏差过大警告阈值
            EtherCAT/CANopen：
                    【OD_6065】 位置偏差过大阈值（EtherCAT/CANopen）
           输入： PosMngV.PosErrA.per32a 位置偏差
                  u32FollowErrWind：位置偏差过大阈值（EtherCAT机型）
                  ODDatArr[ OD_6065 ]：位置偏差过大阈值（CANopen机型）
                  Gprm.PerAlmLevel：位置偏差过大故障阈值（标准机型）
                  Gprm.PerWrnLevel：位置偏差过大警告阈值（标准机型）
           输出： 位置偏差过大故障标识gPosCtrSts.bit.PosErrOv
                  Er.D00故障、Er.D02故障、 Er.900故障                                         */
/**********************************************************************************************/
void LpxCheckPerrOverFlow( void )
{
	LONG Perr = PosMngV.PosErrA.per32a;

    //控制模式判断,非位置控制模式时,不进行位置偏差过大警报和警告监测处理
 	if( BoutV.CtrlMode.b.cm != CTRLMODE_POS )
	{
		KPI_WARNINGCLR	( WRN_OF );  							 
		return;
	}

 	if( !BinV.f.BaseEnable )
    {
        return;
    }

     //位置偏差过大警报监测    
    if( Kprm.f.EtherCATNet == 1 )
    {
        //6065对象字典为0xFFFF不检测
        if( u32FollowErrWind == 0xFFFF )
        {
              
             BoutV.f.PosFollowErFlg = 0;
        }
        else
        {
              
             if( Perr >= u32FollowErrWind )
            {
                KPI_ALARMSET  ( ALM_OF );					     
                BoutV.f.PosFollowErFlg = 1;
            }
            else
            {
                if( Alm.f.AlmFlag == 0 )
                {
                    BoutV.f.PosFollowErFlg = 0;
                }
            }
        }
        if( Perr >= Gprm.PerAlmLevel )
        {
            KPI_WARNINGSET  ( WRN_OF );
        }

    }
    else if( Kprm.f.CanOpenNet == 1 )
    {
          
         if( Perr >= ODDatArr[ OD_6065 ].all )
        {
            KPI_ALARMSET  ( ALM_OF );					         
            BoutV.f.PosFollowErFlg = 1;
        }
        else
        {
            if( Alm.f.AlmFlag == 0 )
            {
                BoutV.f.PosFollowErFlg = 0;
            }      
        }
    }

    //标准机型增加警告与伺服限速位置偏差过大报警
    else
    {
          
         if( Perr >= Gprm.PerAlmLevel )
        {
            if( BoutV.f.SvonSpdLmtFlag )
            {
                KPI_ALARMSET  ( ALM_BEVLMTOF );  			     
             }
            else
            {
                KPI_ALARMSET  ( ALM_OF );					     
            }
        }
          
         if( Perr >= Gprm.PerWrnLevel )
        {
            KPI_WARNINGSET	( WRN_OF );  						 
        }
        else
        {
            KPI_WARNINGCLR	( WRN_OF );  						 
        }
    }
 	return;
 }
 
  
/**********************************************************************************************/
/* Function_Name: LpxCheckSvonPerrOverFlow                                                    */
/* Description  : 伺服使能位置偏差过大判定 
  相关功能码： Pn267 位置ON时位置偏差过大故障阈值
               Pn269 位置ON时位置偏差过大警告阈值
        输入： PosMngV.PosErrA.per32a 位置偏差
               Gprm.SvonPerAlmLevel Pn267 
               Gprm.SvonPerWrnLevel Pn269 
        输出： 位置偏差过大故障标识gPosCtrSts.bit.PosErrOv
               Er.D01故障、Er.901故障                                    */
/**********************************************************************************************/
void	LpxCheckSvonPerrOverFlow( void )
{
LONG	Perr = PosMngV.PosErrA.per32a;

        //非位置控制模式，清除该故障
 		if( BoutV.CtrlMode.b.cm != CTRLMODE_POS )
		{
			KPI_WARNINGCLR( WRN_BEOF );
			return;
		}
        
         if( Iprm.OtStopMode == OTSTOPMODE_ZSTOPZC )
        {
              
             if( CoutV.f.Sv.BaseEnable == TRUE )
            {
                PosMngV.OTStatus = PosMngV.OTStatus << 1;
                PosMngV.OTStatus &= 0x03;
                if( CoutV.f.Sv.Ot == 1 )
                {
                    PosMngV.OTStatus |= 1;
                }
                 if( PosMngV.OTStatus == 1 )
                {
                    return;
                }
                 else
                {
                    ;
                }
             }
            else
            {
                PosMngV.OTStatus = 0;
            }
        }
          
        if(PosMngV.OTStatus == 0)
        {
            //伺服初次使能下，位置误差判定判定
            //非使能->使能: OTStatus 0->1->3->3->3
            //使能->非使能：OTStatus 3->2->0->0->0
            PosMngV.SOnStatus = PosMngV.SOnStatus << 1;
            PosMngV.SOnStatus &= 0x03;
            if( CoutV.f.Sv.BaseEnable == TRUE )
            {
                PosMngV.SOnStatus |= 1;
            }          
            if( PosMngV.SOnStatus == 1 )
            {
                 if( Perr >= Gprm.SvonPerAlmLevel )
                {
                    KPI_ALARMSET( ALM_BEOF );
                }
                if( Perr >= Gprm.SvonPerWrnLevel )
                {
                    KPI_WARNINGSET( WRN_BEOF );
                }
                else
                {
                    KPI_WARNINGCLR( WRN_BEOF );
                }
             }
            else
            {
                KPI_WARNINGCLR( WRN_BEOF );           
            }
        }
        return;
}
  
  
/**********************************************************************************************/
/* Function_Name: BpxControlPositionSignal                                                   */
/* Description  : 标准机型位置状态获取
            调用：ScanB                                                                    */
/**********************************************************************************************/
void	BpxControlPositionSignal( void )
{
    if( BoutV.CtrlMode.b.cm != CTRLMODE_POS )
    {
        BoutV.f.Ctrl.Coin = FALSE;
        return;
    }
  
    //无故障状态下，位置误差在完成（Coin）范围，根据Pn274位置Coin输出方式设定，执行
    if( ( PosMngV.PosErrA.per32a <= Gprm.CoinLevel ) && Alm.f.AlmFlag == 0 )
    {
        switch( Prm.cmfilsw_3 & 0x000F )         
        {
            //位置误差小于阈值，直接输出Coin
             case 0:                              
                BoutV.f.Ctrl.Coin = TRUE;
                break;
            //经过滤波处理后的位置指令完成后，直接输出Coin
             case 1:                              
                BoutV.f.Ctrl.Coin = ( BoutV.f.Sv.Den )? TRUE : FALSE;
                break;
            //位置指令为0，直接输出Coin
             case 2:                              
                BoutV.f.Ctrl.Coin = ( PosMngV.dPcmda == 0 ) ? TRUE : FALSE;
                break;
        }
    }
     else
    {
        BoutV.f.Ctrl.Coin = FALSE;
    }
  
    //位置误差在位置误差在接近（Near）范围，执行输出
    BoutV.f.Sv.Near = ( PosMngV.PosErrA.per32a <= Gprm.NearLevel )? TRUE : FALSE;
    if( !BinV.f.BaseEnable )
    {
        BoutV.f.Ctrl.Coin   = FALSE;
        BoutV.f.Sv.Near     = FALSE;
    }
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: BpxControlPositionSignal_EtherCat                                           */
/* Description  : EtherCAT机型位置状态获取                                                    */
/**********************************************************************************************/
void	BpxControlPositionSignal_EtherCat( void )
{
    //位置误差（用户单位）在【6067】范围内，输出Coin信号，时滞时间为【6068】
	if(CAN_EXFUNC1_4_DIS)
    {
	    if( BoutV.f.Ctrl.Coin )
	    {
	        PosMngV.PossErrCnt0 = 0;
	        if( PosMngV.PosErrA.per32a > u32PosWindow )
	        {
	            //if( ++PosMngV.PossErrCnt1 >= ( 8UL * u16PosWindowTime ))
	                BoutV.f.Ctrl.Coin = FALSE;
	        }
	        else
	            PosMngV.PossErrCnt1 = 0;
	    }
	    else
	    {
	        PosMngV.PossErrCnt1 = 0;
	        if( PosMngV.PosErrA.per32a < u32PosWindow && Alm.f.AlmFlag == 0)
	        {
	            if( ++PosMngV.PossErrCnt0 > ( 8UL * u16PosWindowTime ))
	                BoutV.f.Ctrl.Coin = TRUE;
	        }
	        else
	            PosMngV.PossErrCnt0 = 0;
	    }
	}
  	else    
	{
        PositionSignal_6041bit10();
    }
    BoutV.f.Sv.Near = ( PosMngV.PosErrA.per32a <= Gprm.NearLevel )? TRUE : FALSE;
    if( !BinV.f.BaseEnable )
    {
        BoutV.f.Ctrl.Coin   = FALSE;
        BoutV.f.Sv.Near     = FALSE;
        PosMngV.PossErrCnt0 = 0;
        PosMngV.PossErrCnt1 = 0;
    }
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: BpxControlPositionSignal_CanOpen                                           */
/* Description  : CANOpen机型位置状态获取                                                    */
/**********************************************************************************************/
void	BpxControlPositionSignal_CanOpen( void )
{
    //位置误差（用户单位）在【6067】范围内，输出Coin信号，时滞时间为【6068】
	if(CAN_EXFUNC1_4_DIS)
    {
	    if( BoutV.f.Ctrl.Coin )
	    {
	        PosMngV.PossErrCnt0 = 0;
	        if( PosMngV.PosErrA.per32a > ODDatArr[ OD_6067 ].all )
	        {
	           // if( ++PosMngV.PossErrCnt1 >= ODDatArr[ OD_6068 ].word.LowWord )     //20240319处理华章6041bit10置位问题
	                BoutV.f.Ctrl.Coin = FALSE;
	        }
	        else
	        {
	            PosMngV.PossErrCnt1 = 0;
	        }
	    }
	    else
	    {
	        PosMngV.PossErrCnt1 = 0;
	        if( PosMngV.PosErrA.per32a < ODDatArr[ OD_6067 ].all && Alm.f.AlmFlag == 0)
	        {
	            if( ++PosMngV.PossErrCnt0 > (8UL * ODDatArr[ OD_6068 ].word.LowWord ) )
	                BoutV.f.Ctrl.Coin = TRUE;
	        }
	        else
	        {
	            PosMngV.PossErrCnt0 = 0;
	        }
	    }
	}
    else
    {
        PositionSignal_6041bit10();
    }
  
  
    BoutV.f.Sv.Near = ( PosMngV.PosErrA.per32a <= Gprm.NearLevel )? TRUE : FALSE;

    if( !BinV.f.BaseEnable )
    {
        BoutV.f.Ctrl.Coin   = FALSE;
        BoutV.f.Sv.Near     = FALSE;
        PosMngV.PossErrCnt0 = 0;
        PosMngV.PossErrCnt1 = 0;
    }
    return;
}


/****************************************************************************************************/
/*                                                                                                  */
/*                           【6041:bit10】位置到达判定标准修改：                                    */
/*                                                                                                  */
/****************************************************************************************************/
void PositionSignal_6041bit10(void)
{
    /*------------------------------------------------------------------------------------------*/
    /* 起始定位以6064值超过6067且在6068时间窗口设定基础上判定，
       停机定位以607A设定所需总路程的一半后再进行位置到达判定。      @ 20250407                    */
    /*------------------------------------------------------------------------------------------*/
    if(Kprm.f.EtherCATNet == 1)
    {
        Trgtrch.Pos6064New = s32PosActVal;
        Trgtrch.Pos6040    = u16ControlWord;
        Trgtrch.Pos6067    = u32PosWindow;
        Trgtrch.Pos6068    = u16PosWindowTime;
        Trgtrch.Pos607A    = s32TargetPos;
    }
    else if(Kprm.f.CanOpenNet == 1)
    {
        Trgtrch.Pos6064New = ODDatArr[ Position_Actual_Value_MM ].all;
        Trgtrch.Pos6040    = ODDatArr[ Control_Word ].all;
        Trgtrch.Pos6067    = ODDatArr[ Position_Window_MM ].all;
        Trgtrch.Pos6068    = ODDatArr[ Position_Window_Time_MS ].all;
        Trgtrch.Pos607A    = ODDatArr[ Targe_Position_MM ].all;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  实时算6064增量                                                                              */
    /*----------------------------------------------------------------------------------------------*/
     Trgtrch.Pos6064Delta = Trgtrch.Pos6064New  - Trgtrch.Pos6064Old;
     Trgtrch.Pos6064Old = Trgtrch.Pos6064New;
     /*----------------------------------------------------------------------------------------------*/
     /*  BIT4上升沿，记录此时的6064起始位置                                                           */
     /*----------------------------------------------------------------------------------------------*/
     if( CanPosV.OB6040Bit4Status == 0x0001 || EthPosV.OB6040Bit4Status == 0x0001)
     {
         Trgtrch.PPOrg = 0;                                       //自锁，释放初始位置记录权
         Trgtrch.PosDelta = 0;                                    //清空应走路程寄存器
         /*----------------------位置判断状态机跳转1--------------------------------------------------*/
         Trgtrch.PPStep = 0;
         /*-------------------每次进入只记录一次初始位置-----------------------------------------------*/
         if(!Trgtrch.PPOrg)
         {
             Trgtrch.Pos6064Org = Trgtrch.Pos6064New; //当前位置记录为运行起始位置
             Trgtrch.Pos6064Sum = 0;    //清空6064累计变化量
             Trgtrch.PPOrg = 1;         //自锁，关闭初始位置记录权
         }
     }
     /*-------------------------     使能后再进行累加  -----------------------------------------------*/
     if((Trgtrch.Pos6040 & 0x008F) == 0x000F)
     {
         Trgtrch.Pos6064Sum += Trgtrch.Pos6064Delta;
     }
     /*-------------------------   均转化为相对所需旋转总脉冲数  --------------------------------------*/
     if((Trgtrch.Pos6040 & 0x0040) == 0x0040)                      //相对位置
     {
         Trgtrch.PosDelta = Trgtrch.Pos607A;
         /*------ 运行结束定位标准：接近目标差值=所需总脉冲数-实际6064走过的脉冲数  ---------------------*/
         Trgtrch.PosDelta1 = Trgtrch.PosDelta - Trgtrch.Pos6064Sum;
     }
     else if((Trgtrch.Pos6040 & 0x0040) == 0x0000)                //绝对位置
     {
         Trgtrch.PosDelta = Trgtrch.Pos607A - Trgtrch.Pos6064Org;
         /*------------------------ 运行结束定位标准：接近目标差值=607A-6064 ---- ---------------------*/
         Trgtrch.PosDelta1 = Trgtrch.Pos607A - Trgtrch.Pos6064New;
     }
     /*----------------------------------------------------------------------------------------------*/
     /*  位置模式定位判断状态机                                                                       */
     /*----------------------------------------------------------------------------------------------*/
     switch(Trgtrch.PPStep)
     {
         case 0:                                                   //未运行
             BoutV.f.Ctrl.Coin = FALSE;
             if(Trgtrch.PosDelta >= 0)
             {
                 if(Trgtrch.Pos6064Sum > (Trgtrch.PosDelta >> 1))  //以所需跑的总路程中点为标记
                 {
                     Trgtrch.PPStep = 1;
                 }
             }
             else if(Trgtrch.PosDelta < 0)
             {
                 if(Trgtrch.Pos6064Sum < (Trgtrch.PosDelta >> 1))  //以所需跑的总路程中点为标记
                 {
                     Trgtrch.PPStep = 1;
                 }
             }
             break;
         case 1:
             if( BoutV.f.Ctrl.Coin )
            {
                PosMngV.PossErrCnt0 = 0;
                if( (Trgtrch.PosDelta1 > Trgtrch.Pos6067) || (Trgtrch.PosDelta1 < -Trgtrch.Pos6067) )
                {
                    BoutV.f.Ctrl.Coin = FALSE;
                }
                else
                  PosMngV.PossErrCnt1 = 0;
            }
             else
            {
                PosMngV.PossErrCnt1 = 0;
                if( (Trgtrch.PosDelta1 <= Trgtrch.Pos6067) && (Trgtrch.PosDelta1 >= -Trgtrch.Pos6067) && (Alm.f.AlmFlag == 0) )
                {
                    if( ++PosMngV.PossErrCnt0 > ( 8UL * Trgtrch.Pos6068 ))
                    {
                        BoutV.f.Ctrl.Coin = TRUE;
                    }
                }
                else
                    PosMngV.PossErrCnt0 = 0;
            }
             break;
         default :
             break;
     }
}







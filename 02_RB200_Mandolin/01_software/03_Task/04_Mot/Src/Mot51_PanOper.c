/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name 		 : PanOper.c
* Version			 : V0.1
* Date				 : 2024
* Description		 : 键盘操作部分（暂时未用）
***********************************************************************************************/

#include "Mot51_PanOper.h"
#include "SvOption.h"
#define	PNLLED_BLINK		0xFF
#define PNLLED_NOBLINK      0x00


/****************************************************************************************************/
/*  16进制数显示:0~9,A,B,C,D,E,F                                                                    */
/****************************************************************************************************/
const	UCHAR	ledcodetbl[] =
{
	LEDCODE_ZERO, LEDCODE_1, LEDCODE_2, LEDCODE_3, LEDCODE_4, LEDCODE_5, LEDCODE_6, LEDCODE_7,
	LEDCODE_8,	  LEDCODE_9, LEDCODE_A, LEDCODE_B, LEDCODE_C, LEDCODE_D, LEDCODE_E, LEDCODE_F
};

/*  -,., ,0~9,A~Z字符编码 */
const	UCHAR	ledconvtbl[] =
{
          	LEDCODE_MINUS,
          	LEDCODE_POINT,
          	LEDCODE_BLANK,
          	LEDCODE_ZERO ,
          	LEDCODE_1    ,
          	LEDCODE_2    ,
          	LEDCODE_3    ,
          	LEDCODE_4    ,
          	LEDCODE_5    ,
          	LEDCODE_6    ,
          	LEDCODE_7    ,
          	LEDCODE_8    ,
          	LEDCODE_9    ,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_A    ,
          	LEDCODE_B    ,
          	LEDCODE_C    ,
          	LEDCODE_D    ,
          	LEDCODE_E    ,
          	LEDCODE_F    ,
          	LEDCODE_G    ,
          	LEDCODE_H    ,
          	LEDCODE_1	 ,
          	LEDCODE_J    ,
          	LEDCODE_BLANK,
          	LEDCODE_L    ,
          	LEDCODE_BLANK,
          	LEDCODE_N    ,
          	LEDCODE_ZERO ,
          	LEDCODE_P    ,
          	LEDCODE_Q    ,
          	LEDCODE_R    ,
          	LEDCODE_5    ,
          	LEDCODE_T    ,
          	LEDCODE_U    ,
          	LEDCODE_sU   ,
          	LEDCODE_BLANK,
          	LEDCODE_BLANK,
          	LEDCODE_Y    ,
          	LEDCODE_BLANK
};

const ULONG decpowertbl[] =
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};
    
OPKEYFLG    OpKeyMk;
OPKEYFLG	OpKeyLvl;
OPKEYFLG    OpKeyBrk;
BLINKFLG	OpBlnkFlg;
BLINKFLG	OpBlnkKickFlg;

#define PNLMODE_STATUS		0
#define PNLMODE_FNNUM		1
#define PNLMODE_FNEXE		2
#define PNLMODE_PNNUM		3
#define PNLMODE_PNDATA		4
#define PNLMODE_UNNUM		5
#define PNLMODE_UNDATA		6
 
PANOPER PanOper;
 void PnlOpMain(void);
void PnlKeyTranslate(void);
void PnlLedSetBlnkSw( LEDDSP *leddsp, UCHAR data, LONG size, LONG flag );
 
/****************************************************************************************************/
/*Function_Name:RpxPnlOpMonInit                                                                    */
/*Description  :默认监视参数                                                                        */
/****************************************************************************************************/
void RpxPnlOpMonInit( void )
{
    if ( (Prm.mondef != 0x0FFF) && (KpiGetAlarmInfo( ) == 0) )
    {
        if ( RpiMonSearch( Prm.mondef, 0, &(PanOper.CurMonIndx), MCHK_ACCS_LVL ) == OK )
        {
            PanOper.DispMode = PNLMODE_UNDATA;
            PanOper.CurPos = 0;
             if ( UnMonTbl[ PanOper.CurMonIndx ].MonDefPtr->IsLong == TRUE )
            {
                PanOper.CurPosMax = 3;
            }
            else
            {
                PanOper.CurPosMax = 1;
            }
        }
    }
    return;
}
 
/****************************************************************************************************/
/*Function_Name:RpxLedSetStr                                                                       */
/*Description  :根据字符串查找相应的字符信息                                                        */
/****************************************************************************************************/
void	RpxLedSetStr(UCHAR *str_ptr, LEDDSP *leddspp, USHORT startdgt, USHORT length)
{
 	USHORT	str_val;
	USHORT	idx_tmp;
	USHORT	str_idx, dgt_tmp;
	UCHAR	*ledbuf_ptr;
 	if((length == 0) || (startdgt >= PNL_LED_NUM ))
		return;
 	ledbuf_ptr = &(leddspp->LedCode[0]);
 	str_idx = 0;
	dgt_tmp = startdgt;
 	while(*(str_ptr + str_idx) != 0)
	{
		str_val = (USHORT)*(str_ptr + str_idx);
		idx_tmp = str_val - '-';
		if(str_val < '-')
			*(ledbuf_ptr + dgt_tmp) = LEDCODE_BLANK;
		else if(str_val <= 'Z')
		{
			if( (str_idx != 0) &&
				('.' == *(str_ptr + str_idx)) &&
				('.' != *(str_ptr + str_idx -1))
			)
			{
				dgt_tmp++;
				*(ledbuf_ptr + dgt_tmp) |= LEDCODE_POINT;
			}
			else	*(ledbuf_ptr + dgt_tmp) = ledconvtbl[idx_tmp];
		}
		else if(('a' <= str_val) && (str_val <= 'z'))
		{
			if('h' == str_val)
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_sH;
			else if('o' == str_val)
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_sO;
			else if('u' == str_val)
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_sU;
			else
				*(ledbuf_ptr + dgt_tmp) = ledconvtbl[idx_tmp - ('a' - 'A')];
		}
		else
		{
			if('_' == str_val)
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_B3;
			else if('~' == str_val)
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_B0;
			else
				*(ledbuf_ptr + dgt_tmp) = LEDCODE_BLANK;
		}
 		if(dgt_tmp == 0)
		{
			if( ((str_idx+1) < length) &&
				('.' == *(str_ptr + str_idx + 1)) &&
				('.' != *(str_ptr + str_idx)) )
			{
				*(ledbuf_ptr + dgt_tmp) |= LEDCODE_POINT;
			}
 			break;
		}
		dgt_tmp--;
 		str_idx++;
		if(str_idx >= length)	break;
	}
}
  
/****************************************************************************************************/
/*Function_Name:RpxLedSetValHex                                                                    */
/*Description  :将数据转换成16进制                                                                  */
/* data     :待转换的十六进制数据                                                                   */
/* leddspp  :LED 存储指针                                                                           */
/* startdgt :转换开始的位置                                                                         */
/* digit    :待转换的个数                                                                           */
/****************************************************************************************************/
void	RpxLedSetValHex(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit)
{
	USHORT	i, var1_tmp, var2_tmp;
	UCHAR	*ledbuf_ptr;
 	if(digit > 4)	return;
 	ledbuf_ptr = &(leddspp->LedCode[startdgt]);
 	if(data >= (0x1 << (digit*4)))	data &= ((0x1 << (digit*4)) -1);
 	for( i = 0; i < digit; i++ )
	{
		var1_tmp = 0x1 << ((digit-1-i)*4);
		var2_tmp = data/var1_tmp;
		*(ledbuf_ptr - i) = ledcodetbl[var2_tmp];
		data -= (var1_tmp * var2_tmp);
	}
 	return;
}
  
 /****************************************************************************************************/
 /*Function_Name:RpxLedSetFlag                                                                      */
 /*Description  :将数据转换成16进制                                                                  */
 /* data     :待转换的十六进制数据                                                                   */
 /* leddspp  :LED 存储指针                                                                           */
 /* startdgt :转换开始的位置                                                                         */
 /* digit    :待转换的个数                                                                           */
 /****************************************************************************************************/
 void	RpxLedSetFlag(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit)
{
	UCHAR	*ledbuf_ptr;
 	if(digit > 4)	return;
    ledbuf_ptr = &(leddspp->LedCode[startdgt]);
    *(ledbuf_ptr) = data;
	return;
}
  
/****************************************************************************************************/
/*																									*/
/*		警报信息取得,返回第一个故障																    */
/*																									*/
/****************************************************************************************************/
USHORT	KpiGetAlarmInfo( void )
{
LONG	i;
  
 		for( i=0; i < Kalm.AlmCnt; i++ )
		{                                        
		    /* Warning(1),Alarm(0)								*/
			if( ( Kalm.AlmTbl[i].AlmDef.AlmAttr & ALMDEF_ATTR_WARNING ) == 0x00 )
			{
				return( Kalm.AlmTbl[i].AlmDef.AlmCode );
			}
		}
		return( Alm.OpWrnCode );
}
  
/****************************************************************************************************/
/*Function_Name:RpxLedSetStatusBits                                                                */
/*Description  :特殊状态位显示处理                                                                  */
/****************************************************************************************************/
void RpxLedSetStatusBits(LEDDSP *leddspp)
{
    /*----------------------------------------------------------------------------------------------*/
    /*  定位完成 || 速度到达 || 转矩模式                                                            */
    /*----------------------------------------------------------------------------------------------*/
 	if( BoutV.f.Ctrl.Coin || CoutV.f.Ctrl.ReachSpd || (BoutV.CtrlMode.b.cm == CTRLMODE_TRQ))
        leddspp->LedCode[4] |= LEDCODE_B0;
      
    /*  伺服使能                                                                                    */
	if( BinV.f.BaseEnable )                     leddspp->LedCode[4] |= LEDCODE_B6;
      
    /* 伺服准备好                                                                                   */
    if(CoutV.f.Seq.ServoReady)                  leddspp->LedCode[4] |=  LEDCODE_B3;
      
    /* 电机在旋转中                                                                                 */
    if(CoutV.f.Ctrl.MotorMoving)				leddspp->LedCode[3] |= LEDCODE_B0;
      
    /* 脉冲指令输入 || 速度指令输入                                                                 */
    if(CoutV.f.Sv.Prefon || CoutV.f.Sv.Vrefon)	leddspp->LedCode[3] |= LEDCODE_B6;
      
    /* 转矩指令输入 || 位置清除指令输入                                                             */
    if(CoutV.f.Sv.Trefon || CoutV.f.Sv.PerrClr)	leddspp->LedCode[3] |= LEDCODE_B3;
      
    /* 主回路电压                                                                                   */
    if(CoutV.f.Seq.MainPowerOn)					leddspp->LedCode[3] |= LEDCODE_B7;
      
    /* 控制模式 显示                                                                                */
    if(      BoutV.CtrlMode.us[0] == CTRLMODE_POS )   leddspp->LedCode[4] |=  LEDCODE_B5;
    else if( BoutV.CtrlMode.us[0] == CTRLMODE_SPD )   leddspp->LedCode[4] |=  LEDCODE_B1;
    else if( BoutV.CtrlMode.us[0] == CTRLMODE_TRQ )   leddspp->LedCode[3] |=  LEDCODE_B5;
    else if((BoutV.CtrlMode.us[0] == CTRLMODE_JOG) || 
            (BoutV.CtrlMode.us[0] == CTRLMODE_PJOG) ) leddspp->LedCode[3] |=  LEDCODE_B1;
    else {;}
      
    /*  STO 功能板状态                                                                              */
    if( Iprm.f.STOSupport == 0 ) leddspp->LedCode[4] |=  LEDCODE_B4;
      
    return;
}
 
  
/****************************************************************************************************/
/*Function_Name:FactTestStatusBits                                                              */
/*Description  :特殊状态位显示处理                                                                  */
/****************************************************************************************************/
void FactTestStatusBits(LEDDSP *leddspp)
{
    leddspp->LedCode[4] = LEDCODE_T;
    leddspp->LedCode[3] = LEDCODE_E;   
    leddspp->LedCode[2] = LEDCODE_5;
    leddspp->LedCode[1] = LEDCODE_T | LEDCODE_B7;
    leddspp->LedCode[0] = LEDCODE_1;
    return;
}
  
  
 void FactTestWaterLamp( void )
{
 
 }
 
/****************************************************************************************************/
/*Function_Name:FactTestLEDBits                                                                 */
/*Description  :特殊状态位显示处理                                                                  */
/****************************************************************************************************/
void FactTestLEDBits(LEDDSP *leddspp)
{
    switch( Prm.FaTestControl & 0x00F0 )
    {
         case 0x0010:
            leddspp->LedCode[4] = LEDCODE_B0;
            leddspp->LedCode[3] = LEDCODE_B0;   
            leddspp->LedCode[2] = LEDCODE_B0;
            leddspp->LedCode[1] = LEDCODE_B0;
            leddspp->LedCode[0] = LEDCODE_B0;
            break;
         case 0x0020:
            leddspp->LedCode[4] = LEDCODE_B1;
            leddspp->LedCode[3] = LEDCODE_B1;   
            leddspp->LedCode[2] = LEDCODE_B1;
            leddspp->LedCode[1] = LEDCODE_B1;
            leddspp->LedCode[0] = LEDCODE_B1;
            break;
         case 0x0030:
            leddspp->LedCode[4] = LEDCODE_B2;
            leddspp->LedCode[3] = LEDCODE_B2;   
            leddspp->LedCode[2] = LEDCODE_B2;
            leddspp->LedCode[1] = LEDCODE_B2;
            leddspp->LedCode[0] = LEDCODE_B2;
            break;            
         case 0x0040:
            leddspp->LedCode[4] = LEDCODE_B3;
            leddspp->LedCode[3] = LEDCODE_B3;   
            leddspp->LedCode[2] = LEDCODE_B3;
            leddspp->LedCode[1] = LEDCODE_B3;
            leddspp->LedCode[0] = LEDCODE_B3;
            break;            
         case 0x0050:
            leddspp->LedCode[4] = LEDCODE_B4;
            leddspp->LedCode[3] = LEDCODE_B4;   
            leddspp->LedCode[2] = LEDCODE_B4;
            leddspp->LedCode[1] = LEDCODE_B4;
            leddspp->LedCode[0] = LEDCODE_B4;
            break;            
         case 0x0060:
            leddspp->LedCode[4] = LEDCODE_B5;
            leddspp->LedCode[3] = LEDCODE_B5;   
            leddspp->LedCode[2] = LEDCODE_B5;
            leddspp->LedCode[1] = LEDCODE_B5;
            leddspp->LedCode[0] = LEDCODE_B5;
            break;            
         case 0x0070:
            leddspp->LedCode[4] = LEDCODE_B6;
            leddspp->LedCode[3] = LEDCODE_B6;   
            leddspp->LedCode[2] = LEDCODE_B6;
            leddspp->LedCode[1] = LEDCODE_B6;
            leddspp->LedCode[0] = LEDCODE_B6;
            break;            
         case 0x0080:
            leddspp->LedCode[4] = LEDCODE_B7;
            leddspp->LedCode[3] = LEDCODE_B7;   
            leddspp->LedCode[2] = LEDCODE_B7;
            leddspp->LedCode[1] = LEDCODE_B7;
            leddspp->LedCode[0] = LEDCODE_B7;
            break;
        case 0x0000:
            leddspp->LedCode[4] = LEDCODE_T;
            leddspp->LedCode[3] = LEDCODE_E;   
            leddspp->LedCode[2] = LEDCODE_5;
            leddspp->LedCode[1] = LEDCODE_T | LEDCODE_B7;
            leddspp->LedCode[0] = LEDCODE_2;
            break;
        case 0x0090:
            leddspp->LedCode[4] = LEDCODE_8 | LEDCODE_B7;
            leddspp->LedCode[3] = LEDCODE_8 | LEDCODE_B7;   
            leddspp->LedCode[2] = LEDCODE_8 | LEDCODE_B7;
            leddspp->LedCode[1] = LEDCODE_8 | LEDCODE_B7;
            leddspp->LedCode[0] = LEDCODE_8 | LEDCODE_B7;
            break;
         case 0x00A0:
             PanOper.LedTestCnt ++;
             if( PanOper.LedTestCnt > 2 )
             {
                    PanOper.LedTestCnt = 0;
                    PanOper.LedDisStep ++;
                    if( PanOper.LedDisStep >= 9 )
                      PanOper.LedDisStep = 0;
             }
              switch( PanOper.LedDisStep )
             {
                 case 0:
                    leddspp->LedCode[4] = LEDCODE_B0;
                    leddspp->LedCode[3] = LEDCODE_B0;   
                    leddspp->LedCode[2] = LEDCODE_B0;
                    leddspp->LedCode[1] = LEDCODE_B0;
                    leddspp->LedCode[0] = LEDCODE_B0;
                    break;
                 case 1:
                    leddspp->LedCode[4] = LEDCODE_B1;
                    leddspp->LedCode[3] = LEDCODE_B1;   
                    leddspp->LedCode[2] = LEDCODE_B1;
                    leddspp->LedCode[1] = LEDCODE_B1;
                    leddspp->LedCode[0] = LEDCODE_B1;
                    break;
                 case 2:
                    leddspp->LedCode[4] = LEDCODE_B2;
                    leddspp->LedCode[3] = LEDCODE_B2;   
                    leddspp->LedCode[2] = LEDCODE_B2;
                    leddspp->LedCode[1] = LEDCODE_B2;
                    leddspp->LedCode[0] = LEDCODE_B2;
                    break;            
                 case 3:
                    leddspp->LedCode[4] = LEDCODE_B3;
                    leddspp->LedCode[3] = LEDCODE_B3;   
                    leddspp->LedCode[2] = LEDCODE_B3;
                    leddspp->LedCode[1] = LEDCODE_B3;
                    leddspp->LedCode[0] = LEDCODE_B3;
                    break;            
                 case 4:
                    leddspp->LedCode[4] = LEDCODE_B4;
                    leddspp->LedCode[3] = LEDCODE_B4;   
                    leddspp->LedCode[2] = LEDCODE_B4;
                    leddspp->LedCode[1] = LEDCODE_B4;
                    leddspp->LedCode[0] = LEDCODE_B4;
                    break;            
                 case 5:
                    leddspp->LedCode[4] = LEDCODE_B5;
                    leddspp->LedCode[3] = LEDCODE_B5;   
                    leddspp->LedCode[2] = LEDCODE_B5;
                    leddspp->LedCode[1] = LEDCODE_B5;
                    leddspp->LedCode[0] = LEDCODE_B5;
                    break;            
                 case 6:
                    leddspp->LedCode[4] = LEDCODE_B6;
                    leddspp->LedCode[3] = LEDCODE_B6;   
                    leddspp->LedCode[2] = LEDCODE_B6;
                    leddspp->LedCode[1] = LEDCODE_B6;
                    leddspp->LedCode[0] = LEDCODE_B6;
                    break;            
                 case 7:
                    leddspp->LedCode[4] = LEDCODE_B7;
                    leddspp->LedCode[3] = LEDCODE_B7;   
                    leddspp->LedCode[2] = LEDCODE_B7;
                    leddspp->LedCode[1] = LEDCODE_B7;
                    leddspp->LedCode[0] = LEDCODE_B7;
                    break;
                default:
                    leddspp->LedCode[4] = LEDCODE_8 | LEDCODE_B7;
                    leddspp->LedCode[3] = LEDCODE_8 | LEDCODE_B7;   
                    leddspp->LedCode[2] = LEDCODE_8 | LEDCODE_B7;
                    leddspp->LedCode[1] = LEDCODE_8 | LEDCODE_B7;
                    leddspp->LedCode[0] = LEDCODE_8 | LEDCODE_B7;
                    break;             
             }
            break;
         default:
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;   
            leddspp->LedCode[2] = LEDCODE_BLANK;
            leddspp->LedCode[1] = LEDCODE_BLANK;
            leddspp->LedCode[0] = LEDCODE_BLANK;
            break;            
    }
     return;
}
 
 
/****************************************************************************************************/
/*Function_Name:PnlStatusDispMode                                                               */
/*Description  :状态显示处理                                                                        */
/****************************************************************************************************/
void PnlStatusDispMode(void)
{
USHORT	CurAlarm = 0;
    CurAlarm = KpiGetAlarmInfo();
     if(Alm.f.AlmFlag)           // 故障时显示故障代码,优先级最高                                 
    {
        RpxLedSetValHex(CurAlarm, &(PanOper.DspData), 2, 3);    // 显示故障代码                          
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );   // 闪烁部分处理        
    }
     else if( CurAlarm != 0 )   // 警告或者正常状态下时显示                                    
    {
        RpxLedSetValHex(CurAlarm, &(PanOper.DspData), 2, 3);    // 将警告信号转换成Hex值     
    }
    else
    {      
         if( BinV.f.BaseEnable )
        {
            if( !MencV.f.PhaseReady)
            {   
                /* 磁极位置未初始化时使能,显示"P-dt"                                                */
                PanOper.DspData.LedCode[3] = LEDCODE_P;
                PanOper.DspData.LedCode[2] = LEDCODE_B6;
                PanOper.DspData.LedCode[1] = LEDCODE_D;
                PanOper.DspData.LedCode[0] = LEDCODE_T;                
            }
            else
            {   
                /* 伺服运行,显示"ON"                                                               */
                PanOper.DspData.LedCode[2] = LEDCODE_BLANK;
                PanOper.DspData.LedCode[1] = LEDCODE_sO;
                PanOper.DspData.LedCode[0] = LEDCODE_N;

                /* 伺服运行时的状态位 1                                                             */
                KnlV.ServoStatus = 1;
            }
        }
        else
        {   
#if 1
            /* 伺服没有运行,显示"bb"                                                                */
#if 0
            PanOper.DspData.LedCode[2] = LEDCODE_BLANK;
            PanOper.DspData.LedCode[1] = LEDCODE_B;
            PanOper.DspData.LedCode[0] = LEDCODE_B;
#else
            if( CoutV.f.Seq.ServoReady )
            {
                PanOper.DspData.LedCode[2] = LEDCODE_sO;
                PanOper.DspData.LedCode[1] = LEDCODE_F;
                PanOper.DspData.LedCode[0] = LEDCODE_F;            
            }
            else
            {
                PanOper.DspData.LedCode[2] = LEDCODE_N;
                PanOper.DspData.LedCode[1] = LEDCODE_R;
                PanOper.DspData.LedCode[0] = LEDCODE_D;            
            }
 #endif
 #else
              
             PanOper.DspData.LedCode[2] = LEDCODE_sO;
            PanOper.DspData.LedCode[1] = LEDCODE_F;
            PanOper.DspData.LedCode[0] = LEDCODE_F;            
#endif
              
              
            KnlV.ServoStatus = 0;
        }
         if(BoutV.CtrlMode.b.cm != CTRLMODE_JOG && BoutV.CtrlMode.b.cm != CTRLMODE_ZSRCH) 
        {
             /* 正向和负向均超程                                                                     */
             if( CinV.f.Sv.Pot && CinV.f.Sv.Not )
            {   
                 /* 正负超程时,"Pot"和"Not"交互显示                                                  */
                 if(!((KpiGetShortTimer( &PanOper.BlnkTime ) / 100) & 0x04))
                {   
                     /* 显示"Pot"                                                                    */
                     PanOper.DspData.LedCode[2] = LEDCODE_P;
                    PanOper.DspData.LedCode[1] = LEDCODE_sO;
                    PanOper.DspData.LedCode[0] = LEDCODE_T;
                }
                 else
                {
                     /* 显示"Not"                                                                    */
                     PanOper.DspData.LedCode[2] = LEDCODE_N;
                    PanOper.DspData.LedCode[1] = LEDCODE_sO;
                    PanOper.DspData.LedCode[0] = LEDCODE_T;
                }
            }
             /* 正向超程                                                                             */
             else if( CinV.f.Sv.Pot )
            {   
                 /* 显示"Pot"                                                                        */
                 PanOper.DspData.LedCode[2] = LEDCODE_P;
                PanOper.DspData.LedCode[1] = LEDCODE_sO;
                PanOper.DspData.LedCode[0] = LEDCODE_T;                
            }
             /* 反向超程                                                                             */
             else if( CinV.f.Sv.Not )
            {   
                 /* 显示"Not"                                                                              */
                 PanOper.DspData.LedCode[2] = LEDCODE_N;
                PanOper.DspData.LedCode[1] = LEDCODE_sO;
                PanOper.DspData.LedCode[0] = LEDCODE_T;                
            }
        }
    }
     PanOper.DspData.LedCode[4] = LEDCODE_B7;
    PanOper.DspData.LedCode[3] = LEDCODE_BLANK;
      
    if( Iprm.FATest1 == 1 )        // 整机测试                                  
    {
        if(Alm.f.AlmFlag == 0)     // 故障时显示故障代码                                  
        {
            FactTestStatusBits(&(PanOper.DspData));                  
        }
    }
     else if(  Iprm.FATest2 == 1 )   // 单板测试                                 
    {
        FactTestLEDBits(&(PanOper.DspData));
    }
     else
    {
        RpxLedSetStatusBits( &(PanOper.DspData) );     // 正常工作时              
    }
 }
  
/****************************************************************************************************/
/*Function_Name:PnlKeyTranslate                                                                 */
/*Description  :按键键值读取                                                                        */
/****************************************************************************************************/
#define PNLKEY_MODE		0x1
#define PNLKEY_UP		0x2
#define PNLKEY_DOWN		0x4
#define PNLKEY_SHUP		0x8
#define PNLKEY_RST		(PNLKEY_UP | PNLKEY_DOWN)        
#define PNLKEY_SWOFF	0x0

void PnlKeyTranslate(void)
{
    *((UINT *)&OpKeyMk) = *((UINT *)&OpKeyBrk) = *((UINT *)&OpKeyLvl) = 0;
      
    PanOper.PnlBtn = KeyValueFeedBack();                 
     if(PanOper.PnlBtn & PNLKEY_MODE)                     
        OpKeyLvl.mode = TRUE;
    if(PanOper.PnlBtn & PNLKEY_UP)                       
        OpKeyLvl.up = TRUE;
    if(PanOper.PnlBtn & PNLKEY_DOWN)                     
        OpKeyLvl.down = TRUE;
    if(PanOper.PnlBtn & PNLKEY_SHUP)                     
        OpKeyLvl.shup = TRUE;
    if((PanOper.PnlBtn & PNLKEY_RST) == PNLKEY_RST)      
        OpKeyLvl.rst = TRUE;
    if(PanOper.PnlBtn != PanOper.PnlBtnLast)     // 按键有更新        
    {
        switch(PanOper.PnlBtn)                   // 键值的分析处理        
        {
             case PNLKEY_MODE:                            
                OpKeyMk.mode = TRUE;
                break;
             case PNLKEY_UP:                              
                OpKeyMk.up = TRUE;
                KpiRstShortTimer(&PanOper.KeyTime);
                break;
             case PNLKEY_DOWN:                            
                OpKeyMk.down = TRUE;
                KpiRstShortTimer(&PanOper.KeyTime);
                break;
             case PNLKEY_SHUP:                            
                OpKeyMk.shift = TRUE;
                KpiRstShortTimer(&PanOper.KeyTime);
                break;
             case PNLKEY_RST:                             
                OpKeyMk.rst = TRUE;
                break;
             default:
                break;
        }
         switch(PanOper.PnlBtnLast)          // 上一次的按键键值            
		{
			case PNLKEY_MODE    :   OpKeyBrk.mode   = TRUE;     break;
			case PNLKEY_UP      :   OpKeyBrk.up     = TRUE;     break;
			case PNLKEY_DOWN    :   OpKeyBrk.down   = TRUE;     break;
			case PNLKEY_SHUP    :   OpKeyBrk.shup   = TRUE;     break;
			case PNLKEY_RST     :   OpKeyBrk.rst    = TRUE;     break;
			default:            break;
		}
    }
    else
    {   
        switch(PanOper.PnlBtn)
        {
             case PNLKEY_UP:            // Up键持续按下400毫秒有效                  
                if(KpiGetShortTimer(&PanOper.KeyTime) >= 400)
                {
                    if(!((KpiGetShortTimer(&PanOper.KeyTime) / 100) & 0x01))
                        OpKeyMk.up = TRUE;      // 置位连续按下标志      
                }
                break;
             case PNLKEY_DOWN:                  // Down键持续按下400毫秒有效          
                if(KpiGetShortTimer(&PanOper.KeyTime) >= 400)
                {
                    if(!((KpiGetShortTimer(&PanOper.KeyTime) / 100) & 0x01))
                        OpKeyMk.down = TRUE;    
                }
                break;
             case PNLKEY_SHUP:                  // Set键持续按下1秒钟时有效          
                if(KpiGetShortTimer(&PanOper.KeyTime) >= 1000)
                {
                    OpKeyMk.data = TRUE;
                    // 需要将相关的变量清零,否则造成这个信号持续存在,引起系统相应的动作异常
                    KpiRstShortTimer(&PanOper.KeyTime);  
                }
                break;
             default:
                break;
        }
    }
     PanOper.PnlBtnLast = PanOper.PnlBtn;       // 保存当前的键值               
}
  
/****************************************************************************************************/
/*Function_Name:PnlFunNoMode                                                                    */
/*Description  :Fn模式下操作处理                                                                    */
/****************************************************************************************************/
void PnlFunNoMode(void)
{
USHORT  fnnum_tmp;
UCHAR i;
     if(OpKeyMk.shift)                      // 一级菜单中shift键处理                
	{
		PanOper.CurPos = ((PanOper.CurPos+1) == 3)? 0: PanOper.CurPos+1;
	}
     else if(OpKeyMk.up)                    // 一级菜单中Up键处理              
    {
        fnnum_tmp = FnFunTbl[PanOper.CurFunIndx].FnNo + (0x01 << (PanOper.CurPos*4));
		if(fnnum_tmp >= 0x1000)	fnnum_tmp = 0x0FFF;
         PanOper.CurFunIndx = RpxFunSearchIdxOp(fnnum_tmp, PanOper.CurFunIndx);
    }
     else if(OpKeyMk.down)                  // 一级菜单中Down键处理              
    {
        if(FnFunTbl[PanOper.CurFunIndx].FnNo < (0x01 << (PanOper.CurPos*4)))
		{
			fnnum_tmp = 0x000;
		}
		else
            fnnum_tmp = FnFunTbl[PanOper.CurFunIndx].FnNo - (0x01 << (PanOper.CurPos*4));
        /* 搜索功能号FnXXX是否存在   */
        PanOper.CurFunIndx = RpxFunSearchIdxOp(fnnum_tmp, PanOper.CurFunIndx);    
    }
    PanOper.DspData.LedCode[4] = LEDCODE_F;         // 一级菜单中显示F            
    PanOper.DspData.LedCode[3] = LEDCODE_N;         // 一级菜单中显示n 
    
     /* FnXXX中的值xxx显示                    */
     RpxLedSetValHex(FnFunTbl[PanOper.CurFunIndx].FnNo, &PanOper.DspData, 2, 3);
     for( i = 0; i < PNL_LED_NUM; i++ )             // 光标当前所在的位置闪烁     
	{
		PanOper.DspData.LedBlnkSw[i] = (i == PanOper.CurPos)?	0xFF: 0;
	}
}
  
/****************************************************************************************************/
/*Function_Name:PnlPrmNoMode                                                                    */
/*Description  :Pn模式下操作处理(一级菜单)                                                          */
/****************************************************************************************************/
void PnlPrmNoMode(void)
{
USHORT	i, pnnum_tmp;
PRMDEF	*prmdef_tmp;
     if(OpKeyMk.shift)                                    
	{
		PanOper.CurPos = ((PanOper.CurPos + 1) == 3)? 0: PanOper.CurPos+1;
	}
     else if(OpKeyMk.up)                                  
    {
		pnnum_tmp = PnPrmTbl[PanOper.CurPrmIndx].PnNo + (0x01 << (PanOper.CurPos * 4));
 		if(pnnum_tmp >= 0x1000)                          
            pnnum_tmp = 0xFFF;
 		PanOper.CurPrmIndx = RpxPrmSearchIdxOp(pnnum_tmp, PanOper.CurPrmIndx);    
    }
     else if(OpKeyMk.down)                                
    {
		if(PnPrmTbl[PanOper.CurPrmIndx].PnNo < (0x01 << (PanOper.CurPos*4)))
		{
			pnnum_tmp = 0x000;
		}
		else
		{
			pnnum_tmp = PnPrmTbl[PanOper.CurPrmIndx].PnNo - (0x01 << (PanOper.CurPos*4));
		}
 		PanOper.CurPrmIndx = RpxPrmSearchIdxOp(pnnum_tmp, PanOper.CurPrmIndx);    
    }
 	prmdef_tmp = (PRMDEF *)PnPrmTbl[PanOper.CurPrmIndx].PrmDefPtr;      // 获取功能码的属性
 	
    /* 数据最大显示位数,32位数据十进制显示时,可以显示10位,16进制时,可以显示8位                      */
	if(prmdef_tmp->Attr.IsLong)
	{
		PanOper.CurPosMax = (prmdef_tmp->Attr.Base == DSPDEF_BASEDEC)? 10: 8;
	}
    /* 数据最大显示位数,16位数据十进制显示时,根据不同最大值和最小值,可以判断显示位数                */
	else
	{
        /* 10进制可以最多显示5位                                                                    */
		if(prmdef_tmp->Attr.Base == DSPDEF_BASEDEC)
            PanOper.CurPosMax = 5;

        /* 16进制和二进制可以显示4位,固定                                                           */
		else
		{
			PanOper.CurPosMax = 4;
		}
	}  
    PanOper.DspData.LedCode[4] = LEDCODE_P;                  
    PanOper.DspData.LedCode[3] = LEDCODE_N;                  
 	RpxLedSetValHex(PnPrmTbl[PanOper.CurPrmIndx].PnNo, &(PanOper.DspData), 2, 3);
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = (i == PanOper.CurPos)?	0xFF: 0;
	}    
}
  
/****************************************************************************************************/
/*Function_Name:PnlMonNoMode                                                                    */
/*Description  :Un模式下操作处理(一级菜单)                                                          */
/****************************************************************************************************/
void PnlMonNoMode(void)
{
USHORT	i, unnum_tmp;
 	if(OpKeyMk.shift)           // 判断是否有Shift键按下
	{
		PanOper.CurPos = ((PanOper.CurPos+1) == 3)? 0: PanOper.CurPos+1;
	}
	else if(OpKeyMk.up)         // 判断是否有UP键按下
	{    
	    // 监控码的索引值为16进制
		unnum_tmp = UnMonTbl[PanOper.CurMonIndx].UnNo + (0x01 << (PanOper.CurPos * 4));
		PanOper.CurMonIndx = RpxMonSearchIdxOp(unnum_tmp, PanOper.CurMonIndx);
	}
	else if(OpKeyMk.down)       // 判断是否有Down键按下
	{
		if(UnMonTbl[PanOper.CurMonIndx].UnNo < (0x01 << (PanOper.CurPos * 4)))
		{
			unnum_tmp = 0x000;  // 最小值     
		}
		else
		{
			unnum_tmp = UnMonTbl[PanOper.CurMonIndx].UnNo - (0x01 << (PanOper.CurPos * 4));
		}
 		PanOper.CurMonIndx = RpxMonSearchIdxOp(unnum_tmp, PanOper.CurMonIndx);
	}
     PanOper.DspData.LedCode[4] = LEDCODE_U;                  
    PanOper.DspData.LedCode[3] = LEDCODE_N;                  
     RpxLedSetValHex(UnMonTbl[PanOper.CurMonIndx].UnNo, &(PanOper.DspData), 2, 3);
	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = (i == PanOper.CurPos)?	0xFF: 0;
	}
}
 
/****************************************************************************************************/
/*Function_Name:RpxLedSetValDec                                                                    */
/*Description  :十进制数显示                                                                        */
/****************************************************************************************************/
void	RpxLedSetValDec(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit, USHORT sup_flg,
		USHORT decimals)
{
	USHORT	i, var1_tmp, var2_tmp;
	UCHAR	*ledbuf_ptr;
 	if(digit > PNL_LED_NUM)	return;
 	ledbuf_ptr = &(leddspp->LedCode[startdgt]);
 	if(data >= decpowertbl[digit])
	{
		var1_tmp = (USHORT)(data / decpowertbl[digit]);
		data -= (USHORT)(var1_tmp*decpowertbl[digit]);
	}
 	for(i = 0; i < digit; i++)
	{
		var1_tmp = (USHORT)decpowertbl[digit-1-i];
		var2_tmp = data/var1_tmp;
 		if(sup_flg)
		{
			if(var2_tmp == 0) *(ledbuf_ptr - i) = LEDCODE_BLANK;
			else
			{
				*(ledbuf_ptr - i) = ledcodetbl[var2_tmp];
				sup_flg = FALSE;
			}
		}
		else
		{
			*(ledbuf_ptr - i) = ledcodetbl[var2_tmp];
		}
		data -= (var1_tmp * var2_tmp);
	}
 	if((0 < (SHORT)decimals) && ((SHORT)decimals < (SHORT)digit))
	{
		*(ledbuf_ptr-( digit - 1 ) + decimals) |= LEDCODE_POINT;
	}
 	return;
}
  
/****************************************************************************************************/
/*Function_Name:RpxLedSetValDec                                                               */
/*Description  :16位十进制数显示                                                                    */
/****************************************************************************************************/
#define PNLOPE_WORDMON_MAX		9999            // 有符号数只能显示 -9999 ~ + 9999    
void	RpxLedDispMonDecWord(USHORT data, LEDDSP *leddspp, USHORT decimals, USHORT sign)
{
	USHORT	data_tmp;
 	data_tmp = ((sign == DSPDEF_W_SIGN) && ((SHORT)data < 0))?	-data: data;
 	if(sign == DSPDEF_W_SIGN)           // 有符号数
	{
        /* 取出数据的大小,判断为正数or负数                                                          */
		data_tmp = ((SHORT)data < 0)?	-data: data;
 		if(data_tmp > 9999)
        {   
            // 五位数据显示处理
            RpxLedSetValDec(data_tmp, leddspp, 4, 5, FALSE, decimals);
            if((SHORT)data < 0)
            {
                leddspp->LedCode[4] |= LEDCODE_POINT;       // 显示负号(用点表示)
                leddspp->LedCode[3] |= LEDCODE_POINT;       // 显示负号(用点表示)
            }
        }
        else if(data_tmp > 999)
        {
            // 4位数据显示处理
            RpxLedSetValDec(data_tmp, leddspp, 3, 4, FALSE, decimals);
            if((SHORT)data < 0)
                leddspp->LedCode[4] = ((SHORT)data < 0)? LEDCODE_MINUS: LEDCODE_BLANK;  // 显示负号  
            else
                leddspp->LedCode[4] = LEDCODE_BLANK;
        }
        else if(data_tmp > 99)
        {
            // 3位数据显示处理
            RpxLedSetValDec(data_tmp, leddspp, 2, 3, FALSE, decimals);
            leddspp->LedCode[4] = LEDCODE_BLANK;
            if((SHORT)data < 0)
                leddspp->LedCode[3] = ((SHORT)data < 0)? LEDCODE_MINUS: LEDCODE_BLANK;  // 显示负号 
            else
                leddspp->LedCode[3] = LEDCODE_BLANK;
        }
        else if(data_tmp >9)
        {
            // 2位数据显示处理
            RpxLedSetValDec(data_tmp, leddspp, 1, 2, FALSE, decimals);
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;
            if((SHORT)data < 0)
                leddspp->LedCode[2] = ((SHORT)data < 0)? LEDCODE_MINUS: LEDCODE_BLANK;  // 显示负号 
            else
                leddspp->LedCode[2] = LEDCODE_BLANK;
        }
        else
        {   
            // 1位数据显示处理
            RpxLedSetValDec(data_tmp, leddspp, 0, 1, FALSE, decimals);
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;
            leddspp->LedCode[2] = LEDCODE_BLANK;
            if((SHORT)data < 0)
                leddspp->LedCode[1] = ((SHORT)data < 0)? LEDCODE_MINUS: LEDCODE_BLANK;  // 显示负号     
            else
                leddspp->LedCode[1] = LEDCODE_BLANK;
        }
	}
    // 无符号数
    else                             
	{
        if(data_tmp > 9999)             // 显示5位 
            RpxLedSetValDec(data, leddspp, 4, 5, FALSE, decimals);
         else if(data_tmp > 999)        // 显示4位      
        {
            leddspp->LedCode[4] = LEDCODE_BLANK;
            RpxLedSetValDec(data, leddspp, 3, 4, FALSE, decimals);
        }
         else if(data_tmp > 99)         // 显示3位   
        {
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;
            RpxLedSetValDec(data, leddspp, 2, 3, FALSE, decimals);            
        }    
         else if(data_tmp > 9)          // 显示2位     
        {
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;
            leddspp->LedCode[2] = LEDCODE_BLANK;
            if( decimals == 2 )
            {
                RpxLedSetValDec(data, leddspp, 2, 3, FALSE, decimals);            
            }
            else
            {
                RpxLedSetValDec(data, leddspp, 1, 2, FALSE, decimals);
            }
        }
         else                           // 显示1位                                               
        {
            leddspp->LedCode[4] = LEDCODE_BLANK;
            leddspp->LedCode[3] = LEDCODE_BLANK;
            leddspp->LedCode[2] = LEDCODE_BLANK;
            if( decimals == 1 )         // 1位小数点                                      
            {
                RpxLedSetValDec(data, leddspp, 1, 2, FALSE, decimals);
            }
            else if( decimals == 2 )    // 2位小数点                                    
            {
                RpxLedSetValDec(data, leddspp, 2, 3, FALSE, decimals);
            }
            else
            {
                leddspp->LedCode[1] = LEDCODE_BLANK;
                RpxLedSetValDec(data, leddspp, 0, 1, FALSE, decimals);
            }
        }
	}
 	PnlLedSetBlnkSw( leddspp, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
 }
  
/****************************************************************************************************/
/*Function_Name:RpxLedDispMonDecLong                                                               */
/*Description  :32位十进制数显示                                                                    */
/****************************************************************************************************/
void RpxLedDispMonDecLong(ULONG ldata, LEDDSP *leddspp, USHORT dsp_pos, USHORT decimals, USHORT sign)
{
	USHORT	sdata_tmp2;
	ULONG	ldata_abs, ldata_tmp2;
 	if(dsp_pos >= 3)	return;                 // 规避数据出现溢出的问题                    
 	PnlLedSetBlnkSw( leddspp, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
	ldata_abs = ((sign == DSPDEF_W_SIGN) && ((LONG)ldata < 0))?	-(LONG)ldata: ldata;
 	switch(dsp_pos)
	{
 		case 0:     // 显示后4位
			ldata_tmp2 = ldata_abs / 10000;
			sdata_tmp2 = (USHORT)(ldata_abs - ldata_tmp2*10000);
			RpxLedSetValDec(sdata_tmp2, leddspp, 3, 4, FALSE, decimals);
			leddspp->LedBlnkSw[4] = leddspp->LedCode[4] = LEDCODE_B3;
			break;
 		case 1:     // 显示中间4位
			ldata_tmp2 = ldata_abs / 100000000;
			sdata_tmp2 = (USHORT)((ldata_abs - ldata_tmp2*100000000)/10000);
			RpxLedSetValDec(sdata_tmp2, leddspp, 3, 4, FALSE, (USHORT)(decimals-4));
			leddspp->LedBlnkSw[4] = leddspp->LedCode[4] = LEDCODE_B6;
			break;
 		case 2:     // 显示前2位
			leddspp->LedCode[3] = LEDCODE_BLANK;
			leddspp->LedCode[2] = LEDCODE_BLANK;
			sdata_tmp2 = (USHORT)(ldata_abs/100000000);
			RpxLedSetValDec(sdata_tmp2, leddspp, 1, 2, FALSE, (USHORT)(decimals-8));
			leddspp->LedBlnkSw[4] = leddspp->LedCode[4] = LEDCODE_B0;
			break;
 		default:
			break;
	}
 	if((sign == DSPDEF_W_SIGN) && ((LONG)ldata < 0))
    {    
        // 32位数据的负号显示处理
		leddspp->LedCode[4] |= LEDCODE_POINT;
        leddspp->LedCode[3] |= LEDCODE_POINT;
    }
	return;
}
  
/****************************************************************************************************/
/*Function_Name:PnlLedDispMonHexWord                                                            */
/*Description  :16进制数显示                                                                        */
/****************************************************************************************************/
void	PnlLedDispMonHexWord( USHORT data)
{
	PanOper.DspData.LedCode[4] = LEDCODE_H | LEDCODE_POINT;
 	RpxLedSetValHex(data, &(PanOper.DspData), 3, 4);
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
}
  
  
 void PnlLedDispMonHexLONGL( USHORT data)
{
	PanOper.DspData.LedCode[4] = LEDCODE_L | LEDCODE_POINT;
 	RpxLedSetValHex(data, &(PanOper.DspData), 3, 4);
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
}
  
  
 void	PnlLedDispMonHexLONGH( USHORT data)
{
	PanOper.DspData.LedCode[4] = LEDCODE_H | LEDCODE_POINT;
 	RpxLedSetValHex(data, &(PanOper.DspData), 3, 4);
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
}
  
  
void	PnlLedDispMonBit(USHORT data)
{
	USHORT	i;
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = PanOper.DspData.LedCode[i] = 0;
	}
 	for(i = 0; i < 9; i++)
	{
		switch(i & 1)
		{
			case 0:PanOper.DspData.LedCode[i/2] |= (data & 1)?LEDCODE_B1: LEDCODE_B2;		break;
			case 1:PanOper.DspData.LedCode[i/2] |= (data & 1)?LEDCODE_B5: LEDCODE_B4;		break;
			default:break;
		}
		data >>= 1;
	}
}
  
  
void PnlMonDataMode(void)
{
ULONG	ldata_tmp;
MONDEF	*mondef_tmp;
      
      
    mondef_tmp = (MONDEF *)UnMonTbl[PanOper.CurMonIndx].MonDefPtr;
      
      
    if(mondef_tmp->IsLong == TRUE)
	{
		PanOper.CurPosMax = 3;
	}
	else
	{
		PanOper.CurPosMax = 1;
	}
     if(OpKeyMk.mode)     
	{
		PanOper.CurPos = 0;
		PanOper.DispMode = PNLMODE_UNNUM;
		return;
	}
    else if(OpKeyMk.shift)   
        PanOper.CurPos = ((PanOper.CurPos+1) == PanOper.CurPosMax)?
			0: PanOper.CurPos+1;
    else if(OpKeyMk.rst)     
        RpxMonClearVarIdx( PanOper.CurMonIndx );
      
    RpiMonRead(mondef_tmp, &ldata_tmp, MCHK_ACCS_LVL);
      
     switch(mondef_tmp->Base)
	{
 		case DSPDEF_BASEDEC:     
			if(mondef_tmp->IsLong == FALSE)      
			{
				RpxLedDispMonDecWord((USHORT)ldata_tmp, &(PanOper.DspData),
					mondef_tmp->Decimals, mondef_tmp->Sign );
			}
			else                                 
			{
				RpxLedDispMonDecLong(ldata_tmp, &(PanOper.DspData), PanOper.CurPos,
					mondef_tmp->Decimals, mondef_tmp->Sign);
			}
			break;
 		case DSPDEF_BASEHEX:     
            if(mondef_tmp->IsLong == FALSE)      
            {
                PnlLedDispMonHexWord((USHORT)ldata_tmp);
            }
            else                                 
            {
                  
                  
                if( PanOper.CurPos >= 2)
                    PanOper.CurPos = 0;
                 if( PanOper.CurPos == 0 )
                {
                    PnlLedDispMonHexLONGL((USHORT)ldata_tmp);            
                }
                else
                {
                    PnlLedDispMonHexLONGH((USHORT)(ldata_tmp >> 16));    
                }
            }
			break;
 		case DSPDEF_BASEBIT:     
			PnlLedDispMonBit((USHORT)ldata_tmp);
			break;
 		default:
			break;
 	}
}
  
  
  
void	PnlLedSetKnlBuffer( LEDDSP *leddsp,UCHAR *dist,LONG size )
{
LONG	i;
     for ( i = 0; i < size; i++ )
    {
        dist[i] = (UCHAR)(leddsp->LedCode[i]) & (~((UCHAR)(leddsp->LedBlnkSw[i])));
    }
    return;
}
  
  
void DispDataToFpga(void)
{
USHORT DataTmp = 0;
      
    PnlLedSetKnlBuffer(&PanOper.DspData,PanOper.LedDisBuf,PNL_LED_NUM);     
     DataTmp = ((USHORT)PanOper.LedDisBuf[3] << 8) | PanOper.LedDisBuf[4];    
    ASIC_WR( MREG_Addr01,DataTmp);
    DataTmp = ((USHORT)PanOper.LedDisBuf[1] << 8) | PanOper.LedDisBuf[2];    
    ASIC_WR( MREG_Addr02, DataTmp );
    DataTmp = (USHORT)PanOper.LedDisBuf[0] |(0x000f << 8);
    ASIC_WR( MREG_Addr03, DataTmp );
}
  
  
void	PnlLedDispPrmDecLong(ULONG ldata, USHORT cur_digit, USHORT decimals, USHORT sign)
{
USHORT	sdata_tmp2;
ULONG	ldata_abs, ldata_tmp2;
 	if(cur_digit >= 10)	return;
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
 	ldata_abs = ((sign == DSPDEF_W_SIGN) && ((LONG)ldata < 0))?	-(LONG)ldata: ldata;
 	if(PanOper.CurPos < 4)
	{
		ldata_tmp2 = ldata_abs/10000;
		sdata_tmp2 = (USHORT)(ldata_abs - ldata_tmp2*10000);
		RpxLedSetValDec(sdata_tmp2, &(PanOper.DspData), 3, 4, FALSE, decimals);
 		PanOper.DspData.LedBlnkSw[cur_digit] = 0xFF;
		PanOper.DspData.LedBlnkSw[4] = PanOper.DspData.LedCode[4] = LEDCODE_B3;
	}
	else if(PanOper.CurPos < 8)
	{
		ldata_tmp2 = ldata_abs/100000000;
		sdata_tmp2 = (USHORT)((ldata_abs - ldata_tmp2*100000000)/10000);
		RpxLedSetValDec(sdata_tmp2, &(PanOper.DspData), 3, 4, FALSE, (USHORT)(decimals-4));
 		PanOper.DspData.LedBlnkSw[cur_digit-4] = 0xFF;
		PanOper.DspData.LedBlnkSw[4] = PanOper.DspData.LedCode[4] = LEDCODE_B6;
	}
	else
	{
		PanOper.DspData.LedCode[3] = ((sign == DSPDEF_W_SIGN) && ((LONG)ldata < 0))?
			LEDCODE_MINUS: LEDCODE_BLANK;
		PanOper.DspData.LedCode[2] = LEDCODE_BLANK;
 		sdata_tmp2 = (USHORT)(ldata_abs/100000000);
		RpxLedSetValDec(sdata_tmp2, &(PanOper.DspData), 1, 2, FALSE, (USHORT)(decimals-8));
 		PanOper.DspData.LedBlnkSw[cur_digit-8] = 0xFF;
		PanOper.DspData.LedBlnkSw[4] = PanOper.DspData.LedCode[4] = LEDCODE_B0;
	}
 	if((sign == DSPDEF_W_SIGN) && ((LONG)ldata < 0))
		PanOper.DspData.LedCode[4] |= LEDCODE_POINT;
 	return;
}
  
  
void	PnlLedDispPrmHexLong(ULONG ldata, USHORT cur_digit)
{
	USHORT	sdata_tmp2;
 	if(cur_digit > 8)	return;
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
 	if(PanOper.CurPos < 4)
	{
		sdata_tmp2 = (USHORT)(ldata & 0xFFFF);
		RpxLedSetValHex(sdata_tmp2, &(PanOper.DspData), 3, 4);
 		PanOper.DspData.LedBlnkSw[cur_digit] = 0xFF;
		PanOper.DspData.LedBlnkSw[4] = PanOper.DspData.LedCode[4] = LEDCODE_B3;
 	}
	else
	{
		sdata_tmp2 = (USHORT)((ldata >> 16) & 0xFFFF);
		RpxLedSetValHex(sdata_tmp2, &(PanOper.DspData), 3, 4);
 		PanOper.DspData.LedBlnkSw[cur_digit-4] = 0xFF;
		PanOper.DspData.LedBlnkSw[4] = PanOper.DspData.LedCode[4] = LEDCODE_B6;
	}
}
  
  
void	PnlLedDispPrmDecWordSigned(SHORT data, USHORT cur_digit, USHORT decimals,
			SHORT llimit, SHORT ulimit)
{
	USHORT	sdata_tmp;
	USHORT	i;
 	if(cur_digit >= 5)	return;
 	PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, TRUE );
 	sdata_tmp = (data < 0)? -data: data;
 
	RpxLedSetValDec(sdata_tmp, &(PanOper.DspData),  PanOper.CurPosMax -1, PanOper.CurPosMax, FALSE, decimals);
    if(data <= -10000)
      PanOper.DspData.LedCode[PanOper.CurPosMax-1] |= LEDCODE_POINT;
    else
    {
        if( data < -9999 )
        {
            PanOper.DspData.LedCode[PanOper.CurPosMax-1] |= LEDCODE_POINT;
         }
        else
            PanOper.DspData.LedCode[PanOper.CurPosMax-1] = (data < 0)? LEDCODE_MINUS: PanOper.DspData.LedCode[PanOper.CurPosMax-1];
    }
 	for(i = PanOper.CurPosMax + 1 ; i <  PNL_LED_NUM ; i++)
	{
		PanOper.DspData.LedCode[i]	= LEDCODE_BLANK;
	}
 	PanOper.DspData.LedBlnkSw[cur_digit] = 0xFF;
}
  
  
void	PnlLedDispPrmDecWordUnsigned(USHORT data, USHORT cur_digit, USHORT decimals)
{
	USHORT	i;
 	if(cur_digit >= 5)	return;
 	RpxLedSetValDec(data, &(PanOper.DspData), PanOper.CurPosMax -1, PanOper.CurPosMax, FALSE, decimals);
 	for(i = PanOper.CurPosMax ; i <  PNL_LED_NUM ; i++)
	{
		PanOper.DspData.LedCode[i]	= LEDCODE_BLANK;
	}
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = (i == cur_digit)?	0xFF: 0;
	}
}
  
  
void	PnlLedDispPrmHexNblWord(USHORT data, USHORT cur_digit, USHORT base)
{
	USHORT	i;
 	if(cur_digit >= 4)	return;
 	RpxLedSetValHex(data, &(PanOper.DspData), PanOper.CurPosMax -1, PanOper.CurPosMax);
 	for(i = PanOper.CurPosMax ; i <  PNL_LED_NUM ; i++)
	{
		PanOper.DspData.LedCode[i]	= LEDCODE_N | LEDCODE_POINT;
	}
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = (i == cur_digit)?	0xFF: 0;
	}
}
  
  
 void	PnlLedDispPrmHexWord(USHORT data, USHORT cur_digit, USHORT base)
{
	USHORT	i;
 	if(cur_digit >= 4)	return;
 	RpxLedSetValHex(data, &(PanOper.DspData), PanOper.CurPosMax -1, PanOper.CurPosMax);
 	for(i = PanOper.CurPosMax ; i <  PNL_LED_NUM ; i++)
	{
		PanOper.DspData.LedCode[i]	= LEDCODE_H | LEDCODE_POINT;
	}
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		PanOper.DspData.LedBlnkSw[i] = (i == cur_digit)?	0xFF: 0;
	}
}
  
  
void PnlPrmDataMode(void)
{
PRMDEF	*prmdef_tmp;
LONG	rc;
    prmdef_tmp = (PRMDEF *)PnPrmTbl[PanOper.CurPrmIndx].PrmDefPtr;       
 	switch(PanOper.PrmWrState)
	{
		case OPWM_None:
 			if( OpKeyMk.mode )                                           
			{
                 rc = RpxPrmWriteRamIdx( PanOper.CurPrmIndx,\
                                        PanOper.ModifyData,\
                                        PCHK_READ | PCHK_RONLY, &PopMsg);
 				if( rc == PERR_CALC )
				{
					OpBlnkKickFlg.error = 1;
				}
 				switch(RpxPrmUpdateEepromIdx(PanOper.CurPrmIndx))
				{
					case OK:
						OpBlnkKickFlg.PrmEewrite = 1;
						break;
 					case PRM_EEPROM_WRITE_FAIL:
						PanOper.PrmWrState = OPWM_UpdtWait;
						break;
 					case PERR_NO:
 					case PRM_EEPROM_RAM_NO_DIFF:
						PanOper.CurPos = 0;
						PanOper.DispMode = PNLMODE_PNNUM;
						return;
					default:
						break;
				}
			}
            else if(OpKeyMk.data)
			{
				PanOper.CurPos = 0;
				PanOper.DispMode = PNLMODE_PNNUM;
			}
 			else if(OpKeyMk.shift)                              
			{
				PanOper.CurPos = ((PanOper.CurPos+1) == PanOper.CurPosMax)? 0: PanOper.CurPos+1;
			}
 			else if(OpKeyMk.up )                                
			{
				PanOper.ModifyData = RpxPrmRamDigitInc( PanOper.CurPrmIndx,\
                                                        PanOper.ModifyData,\
                                                        PanOper.CurPos);
			}
             else if(OpKeyMk.down)                               
            {
                PanOper.ModifyData = RpxPrmRamDigitDec( PanOper.CurPrmIndx,\
                                                        PanOper.ModifyData,\
                                                        PanOper.CurPos);
            }
 			if(prmdef_tmp->Attr.IsLong)                         
			{
				if(prmdef_tmp->Attr.Base == DSPDEF_BASEDEC)
				{
					PnlLedDispPrmDecLong(PanOper.ModifyData, PanOper.CurPos,
						RpxPrmGetDecimals( prmdef_tmp ), (USHORT)prmdef_tmp->Attr.Sign);
				}
				else
				{
					PnlLedDispPrmHexLong(PanOper.ModifyData, PanOper.CurPos);
				}
 			}
 			else                                                
			{
				if(prmdef_tmp->Attr.Base == DSPDEF_BASEDEC)     
				{
					if(prmdef_tmp->Attr.Sign == DSPDEF_W_SIGN)  
					{
						PnlLedDispPrmDecWordSigned((SHORT)PanOper.ModifyData, PanOper.CurPos,
							RpxPrmGetDecimals( prmdef_tmp ),
							(SHORT)RpxPrmLowerLimitIdx(PanOper.CurPrmIndx),
							(SHORT)RpxPrmUpperLimitIdx(PanOper.CurPrmIndx));
					}
					else                                        
					{
						PnlLedDispPrmDecWordUnsigned((USHORT)PanOper.ModifyData, PanOper.CurPos,
							RpxPrmGetDecimals( prmdef_tmp ) );
					}
				}
				else if( prmdef_tmp->Attr.Base == DSPDEF_BASENBL )
				{
					PnlLedDispPrmHexNblWord((USHORT)PanOper.ModifyData, PanOper.CurPos,
						(USHORT)prmdef_tmp->Attr.Base);
				}
                else
                {
					PnlLedDispPrmHexWord((USHORT)PanOper.ModifyData, PanOper.CurPos,
						(USHORT)prmdef_tmp->Attr.Base);                
                }
			}
			break;
 		case OPWM_UpdtWait:
			switch(RpxPrmUpdateEepromIdx(PanOper.CurPrmIndx))
			{
				case OK:
					OpBlnkKickFlg.PrmEewrite = 1;
					PanOper.PrmWrState = OPWM_None;
					break;
 				case PRM_EEPROM_RAM_NO_DIFF:
					PanOper.PrmWrState = OPWM_None;
					PanOper.CurPos = 0;
					PanOper.DispMode = PNLMODE_PNNUM;
					return;
				default:
					break;
			}
			break;
 		default:
			break;
	}
}
  
  
void PnlKeyModelDeal(void)
{
    switch(PanOper.DispMode)
    {
         case PNLMODE_STATUS:                             
                 if(OpKeyMk.mode)                         
				{
					PanOper.DispMode = PNLMODE_FNNUM;
					PanOper.CurPos = 0;
				}
 				else
				{
					PnlStatusDispMode();                 
					if(OpKeyMk.rst)                      
					{
						KpiResetAlarmTable();
 					}
				}
                 break;
         case PNLMODE_FNNUM:                             
                if(OpKeyMk.mode)                        
				{
					PanOper.DispMode = PNLMODE_PNNUM;
					PanOper.CurPos = 0;
				}
                 else if(OpKeyMk.data)                   
                {
                    if(RpxFunExeBeginPnl(PanOper.CurFunIndx) != TRUE)    
                    {
                      OpBlnkKickFlg.no_op = 1;          
                    }
                    else
                    {
                        PanOper.DispMode = PNLMODE_FNEXE;
						PanOper.CurPos = 0;                    
                    }
                }
 				else
				{
                    PnlFunNoMode();
				}  
                 break;
         case PNLMODE_FNEXE:                             
                if(RpxFunEndChkPnl(PanOper.CurFunIndx))
				{
					RpxFunFinishPnl(PanOper.CurFunIndx);
					PanOper.CurPos = 0;
					PanOper.DispMode = PNLMODE_FNNUM;
				}
                else
                     RpxFunExePnl(   OpKeyMk,            \
                                    OpKeyBrk,           \
                                    OpKeyLvl,           \
                                    PanOper.CurFunIndx, \
                                    &(PanOper.DspData), \
                                    &OpBlnkKickFlg );
            break;
         case PNLMODE_PNNUM:                             
                if(OpKeyMk.mode)                        
				{
					PanOper.DispMode = PNLMODE_UNNUM;
					PanOper.CurPos = 0;
				}
                 else if(OpKeyMk.data)                   
                {   
					if(	Access.inhibit == INH_PASWRD )
					{
						OpBlnkKickFlg.no_op = 1;
					}
					else
					{
						PanOper.DispMode = PNLMODE_PNDATA;
						PanOper.PrmWrState = 0;
						PanOper.CurPos = 0;
						RpxPrmReadIdx(PanOper.CurPrmIndx, &PanOper.ModifyData, PCHK_READ);
					}                  
                }
 				else
				{
                    PnlPrmNoMode();
				}
                 break;
         case PNLMODE_PNDATA:                           
                PnlPrmDataMode();
                break;
          
          
         case PNLMODE_UNNUM:                             
                if(OpKeyMk.mode)                        
				{
					PanOper.DispMode = PNLMODE_STATUS;
					PanOper.CurPos = 0;
				}
                 else if(OpKeyMk.data)                   
                {
                    PanOper.DispMode = PNLMODE_UNDATA;
					PanOper.CurPos = 0;
                }
 				else
				{
                    PnlMonNoMode();
				}
                 break;
        case PNLMODE_UNDATA:                            
                PnlMonDataMode();
                break;
         default:break;
     }
}
  
  
void	PnlLedSetBlnkSw( LEDDSP *leddsp, UCHAR data, LONG size, LONG flag )
{
	LONG	i;
    if ( flag != FALSE )
    {
        for ( i = 0; i < size; i++ )
        {
            leddsp->LedBlnkSw[i] = data;
        }
    }
    return;
}
  
  
void PnlLedBlink(void)
{
	if(*((UINT *)&OpBlnkFlg) != 0)                       
	{
		if(KpiGetShortTimer(&PanOper.OpBlnkTime) > 1000)       
		{
			*((UINT *)&OpBlnkFlg) = 0;                  
		}
	}
     if(OpBlnkKickFlg.PrmEewrite)                        
	{
		*((UINT *)&OpBlnkFlg) = *((UINT *)&OpBlnkKickFlg) = 0;
		OpBlnkFlg.PrmEewrite = 1;
		KpiRstShortTimer(&PanOper.OpBlnkTime);
	}
 	else if(OpBlnkKickFlg.no_op)                        
	{
		*((UINT *)&OpBlnkFlg) = *((UINT *)&OpBlnkKickFlg) = 0;
		OpBlnkFlg.no_op = 1;
		KpiRstShortTimer(&PanOper.OpBlnkTime);
	}
 	else if(OpBlnkKickFlg.error)                        
	{
		*((UINT *)&OpBlnkFlg) = *((UINT *)&OpBlnkKickFlg) = 0;
		OpBlnkFlg.error = 1;
		KpiRstShortTimer(&PanOper.OpBlnkTime);
	}
 	else if(OpBlnkKickFlg.done)                         
	{
		*((UINT *)&OpBlnkFlg) = *((UINT *)&OpBlnkKickFlg) = 0;
		OpBlnkFlg.done = 1;
		KpiRstShortTimer(&PanOper.OpBlnkTime);
	}
 	else if(OpBlnkKickFlg.end)                         
	{
		*((UINT *)&OpBlnkFlg) = *((UINT *)&OpBlnkKickFlg) = 0;
		OpBlnkFlg.end = 1;
		KpiRstShortTimer(&PanOper.OpBlnkTime);
	}
 	if(OpBlnkFlg.PrmEewrite)                           
	{
		PanOper.DspData.LedCode[4] = LEDCODE_BLANK;
		PanOper.DspData.LedCode[3] = LEDCODE_D;
		PanOper.DspData.LedCode[2] = LEDCODE_sO;
		PanOper.DspData.LedCode[1] = LEDCODE_N;
		PanOper.DspData.LedCode[0] = LEDCODE_E;
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );
	}
 	else if(OpBlnkFlg.no_op)                            
	{
		PanOper.DspData.LedCode[4] = LEDCODE_N;
		PanOper.DspData.LedCode[3] = LEDCODE_sO;
		PanOper.DspData.LedCode[2] = LEDCODE_B3;
		PanOper.DspData.LedCode[1] = LEDCODE_sO;
		PanOper.DspData.LedCode[0] = LEDCODE_P;
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );
	}
 	else if(OpBlnkFlg.error)                            
	{
		PanOper.DspData.LedCode[4] = LEDCODE_E;
		PanOper.DspData.LedCode[3] = LEDCODE_R;
		PanOper.DspData.LedCode[2] = LEDCODE_R;
		PanOper.DspData.LedCode[1] = LEDCODE_sO;
		PanOper.DspData.LedCode[0] = LEDCODE_R;
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );
	}
 	else if(OpBlnkFlg.done)                            
	{
		PanOper.DspData.LedCode[4] = LEDCODE_BLANK;
		PanOper.DspData.LedCode[3] = LEDCODE_D;
		PanOper.DspData.LedCode[2] = LEDCODE_sO;
		PanOper.DspData.LedCode[1] = LEDCODE_N;
		PanOper.DspData.LedCode[0] = LEDCODE_E;
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );
	}
 	else if(OpBlnkFlg.end)                            
	{
		PanOper.DspData.LedCode[4] = LEDCODE_BLANK;
		PanOper.DspData.LedCode[3] = LEDCODE_E;
		PanOper.DspData.LedCode[2] = LEDCODE_N;
		PanOper.DspData.LedCode[1] = LEDCODE_D;
        PanOper.DspData.LedCode[0] = LEDCODE_BLANK;
		PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_BLINK, PNL_LED_NUM, TRUE );
	}
                                                       
    PnlLedSetBlnkSw( &PanOper.DspData, PNLLED_NOBLINK, PNL_LED_NUM, (((USHORT)(KnlV.ScanBcnt)) & 0x0800) );
}
  
  
 void	RpxLedSetBlnk(LEDDSP *leddspp, UCHAR blnkptn)
{
	SHORT	i;
 	for(i = 0; i < PNL_LED_NUM; i++)
	{
		leddspp->LedBlnkSw[i] = (blnkptn & (1 << i))? 0xFF: 0;
	}
}
  
  
void PnlOpMain(void)
{
USHORT	CurAlarm;
LONG	rc_tmp;
    RpiSetAccsLvl(&Access, PopMsg.AccsLvl);              
    CurAlarm = KpiGetAlarmInfo();                        
 #if 0
    if((CurAlarm != 0) && ((CurAlarm & 0xF00) != 0x900) && (PanOper.LastAlarm == 0) &&
       !(PanOper.DispMode == PNLMODE_FNEXE && CurAlarm == 0xEB9) )
#else
    if((CurAlarm != 0) && ( PanOper.LastAlarm == 0) &&
       !(PanOper.DispMode == PNLMODE_FNEXE && CurAlarm == 0xEB9) )
#endif      
    {
        PanOper.CurPos = 0;
        if(PanOper.DispMode == PNLMODE_FNEXE)	RpxFunFinishPnl(PanOper.CurFunIndx);
        if(PanOper.DispMode == PNLMODE_PNDATA)
        {
            rc_tmp = RpxPrmUpdateEepromIdx(PanOper.CurPrmIndx);
            while(rc_tmp == PRM_EEPROM_WRITE_WAIT || rc_tmp == PRM_EEPROM_WRITE_FAIL)
                rc_tmp = RpxPrmUpdateEepromIdx(PanOper.CurPrmIndx);
        }
        PanOper.DispMode = PNLMODE_STATUS;
    }
    PanOper.LastAlarm = CurAlarm;    
    if( ( Prm.FaTestControl & 0x00F0 ) != 0x00F0 )
        PnlKeyTranslate();                               
    PnlKeyModelDeal();
    PnlLedBlink();                                       
    DispDataToFpga();                                    
    return;
}
  
  
void PanOperManager(void)
{
    if(KnlV.f.Pulse100ms == ON)                          
    {
        PnlOpMain();
    }
    return;
}

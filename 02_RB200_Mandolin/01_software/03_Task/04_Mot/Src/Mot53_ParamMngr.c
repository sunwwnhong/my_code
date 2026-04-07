/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot53_ParamMngr.c
* Version            : V0.1
* Date               : 2024
* Description        : 参数管理
***********************************************************************************************/
  
  
  
  
  
#include "Mot53_ParamMngr.h"
 
  
  
 
ACCESS Access;
MSGIF   PopMsg;
PRMMNGV PrmMngV;
MSGIF UsbMsg;
const ULONG	nbl_mask_table[8] = {0x0000000f, 0x000000f0, 0x00000f00, 0x0000f000,
								 0x000f0000, 0x00f00000, 0x0f000000, 0xf0000000};
const ULONG	dec_power_tbl[] =
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};
  
  
/**********************************************************************************************/
/* Function_Name: APL_PrmGetDecimals         */
/* Description  : 小数点位置的获取
                  调用：键盘操作时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
USHORT	RpxPrmGetDecimals( PRMDEF *pPrmDef )
{
USHORT	Decimals = pPrmDef->Attr.Decimals;       // 获取小数点位置
  
    if( pPrmDef->Attr.ChgDpLsm )
    {
        if( MencP.f.LowSpdMotor ){ ++Decimals;}
    }
    return( Decimals );     // 低速电机，小数点位置加1
}
  
/**********************************************************************************************/
/* Function_Name: GetPrmWriteHandle         */
/* Description  : 参数写入权的取得
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxGetPrmWriteHandle( void *Hmsg )
{
    if( PrmMngV.Hmsg == NULL )
    {
        PrmMngV.Hmsg = Hmsg;	        // 句柄为空时使用输入句柄
        return( TRUE );
    }
    else if( PrmMngV.Hmsg == Hmsg )
    {
        return( TRUE );
    }
    return( FALSE );
}
  
/**********************************************************************************************/
/* Function_Name: RpxFreePrmWriteHandle         */
/* Description  : 参数写入权限释放
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	RpxFreePrmWriteHandle( void *Hmsg )
{
    if( PrmMngV.Hmsg == Hmsg )
    {
        PrmMngV.Hmsg = NULL;	// 句柄清空
    }
 	return;
}
  

/**********************************************************************************************/
/* Function_Name: PrmAttributeChkPdef         */
/* Description  : 参数的属性校验处理
                  根据确定的参数属性，检查指定的参数是否妥当
                  调用：需要时调用
                  输入：功能码结构体指针，检查类型
                  输出：   */
/**********************************************************************************************/
LONG	PrmAttributeChkPdef( CPRMDEF *PdefPtr, UCHAR CheckType )
{
 	if( CheckType & PCHK_MTR_TYPE )
	{
        if( (PdefPtr->ChkSpUse ) == 0x00 )
		{
			return(PERR_MTR_TYPE);
		}
	}
      
	if( CheckType & PCHK_ACCS_LVL )     // 用户权限检测
	{
		if(	PdefPtr->AccessLevel > Access.level )
			return(PERR_LEVEL);
	}
      
	if( CheckType & PCHK_RONLY )        // 读写属性检测
	{
		if(	PdefPtr->Attr.ReadOnly == PRMDEF_READONLY )
			return(PERR_RONLY);
	}
      
	if( CheckType & PCHK_WORD_ORDER )   // 判断是否为32位的高16位
	{
		if(	PdefPtr->Attr.WordOrder != 0 )
			return(PERR_DFIT);
	}
      
	if( CheckType & PCHK_INHIBIT )      // 参数禁止修改判断
	{
		if(	Access.inhibit == INH_PASWRD )
			return(PERR_INH);
	}
 	if( CheckType & PCHK_OPEDSP )
	{
		if(	((PdefPtr->ChkSpUse & KPI_LCDOPEDSPSEL_TUNING) == KPI_LCDOPEDSPSEL_TUNING ) &&
			(Access.OpeDspMode == OPEDSP_SETUPPRM))
			return(PERR_OPEDSP);
	}
 	return(OK);
}
  
  
/**********************************************************************************************/
/* Function_Name: PrmAttributeChkIdx         */
/* Description  : 参数的属性校验处理
                  根据确定的参数属性，检查指定的参数是否妥当
                  调用：需要时调用
                  输入：功能码号，检查类型
                  输出：   */
/**********************************************************************************************/
LONG	PrmAttributeChkIdx( USHORT Index, UCHAR CheckType )
{
LONG	rc;
 	if(Index >= PNPRMTBL_ENTNUM)                                         	
        return(PERR_NO);	    // 功能码号超限,不存在
 	rc = PrmAttributeChkPdef((PnPrmTbl[Index].PrmDefPtr), CheckType);
 	return(rc);
}
  
/**********************************************************************************************/
/* Function_Name: PrmSearchIdxOp         */
/* Description  : 根据参数编码和基础索引号，索引参数编号对应的参数表index
                  调用：键盘操作中使用
                  输入：参数编号，开始搜索索引号
                  输出：   */
/**********************************************************************************************/
USHORT	RpxPrmSearchIdxOp( USHORT SrchNo, USHORT BaseIndex)
{
	USHORT	idx, idx_sv;
	LONG	rc;
	UCHAR	CheckType = PCHK_NONE ;	

	 /*** 创建一个用户显示选定的属性检查条件 ***/
	if((Access.level == ACCLVL_USER1) && (Access.OpeDspMode == OPEDSP_SETUPPRM))
	{
		CheckType = PCHK_OPEDSP ;
	}
	/*** [开始搜索索引号]限幅处理 ***/
 	if(BaseIndex >= PNPRMTBL_ENTNUM)
		BaseIndex = PNPRMTBL_ENTNUM - 1;
 	idx = idx_sv = BaseIndex;

 	 /*** 参数编号限幅处理 ***/
 	if(SrchNo >= 0x1000)
	{
		SrchNo = 0;
	}
    else
    {
        if(SrchNo > PnPrmTbl[PNPRMTBL_ENTNUM - 1].PnNo)
            SrchNo = PnPrmTbl[PNPRMTBL_ENTNUM - 1].PnNo;
	}

 	/*** 参数编号大于等于[开始搜索索引号]对应的参数编号，索引号自加，向上逐个寻找 ***/
 	if (SrchNo >= PnPrmTbl[BaseIndex].PnNo)  
	{
		for( ; idx < PNPRMTBL_ENTNUM; idx++)
		{
			rc = PrmAttributeChkIdx(idx, PCHK_READ | CheckType);									 
			if( rc != OK )
				continue;
 			if(PnPrmTbl[idx].PnNo == SrchNo)	 
				return(idx);
			if(PnPrmTbl[idx].PnNo > SrchNo)		 
				return(idx);
			idx_sv = idx;		 
		}
	}
 	 /*** 参数编号小于[开始搜索索引号]对应的参数编号，索引号自减，向下逐个寻找 ***/
	else 	 
	{
		for( ; (SHORT)idx >= 0; idx--)
		{
 			 
 
 			rc = PrmAttributeChkIdx(idx, PCHK_READ | CheckType);	
			if( rc != OK )
				continue;
 			if(PnPrmTbl[idx].PnNo == SrchNo)	 
				return(idx);
			if( PnPrmTbl[idx].PnNo < SrchNo )	 
				return(idx);
			idx_sv = idx;		 
		}
	}
	return(idx_sv);
}
  

/**********************************************************************************************/
/* Function_Name: APL_PrmDataDigitInc         */
/* Description  : 获得指定位数递增1后的值；超过最大值时，限制到最大值。
                  调用：需要时调用
                  输入：Data：数据，Digit：位数，UpperLimit：上限值，Base：类型，IsLong：是否是32bit，Sign：是否有符号
                  输出：对应位增加后的值   */
/**********************************************************************************************/
ULONG RpiPrmDataDigitInc(ULONG Data, USHORT Digit, ULONG UpperLimit, UCHAR Base, UCHAR IsLong, UCHAR Sign)
{
ULONG	t_data;
CHAR	nbl_data;
 	t_data = Data;
 	if(Base == DSPDEF_BASENBL)	 // 类型：按[16进制位]表示
	{
		nbl_data = (CHAR)((Data & (0x0f << (Digit*4))) >> (Digit*4));
		nbl_data += 1;
		/*** 对应位加1后的限幅处理***/
		if(nbl_data > (CHAR)((UpperLimit & (0x0f << (Digit*4))) >> (Digit*4)))
		{
			nbl_data = (CHAR)((UpperLimit & (0x0f << (Digit*4))) >> (Digit*4));
		}
		t_data = t_data - (t_data & (0x0f << (Digit*4))) + (nbl_data << (Digit*4));
	}
    else
    {
 		if(!IsLong && (Sign == DSPDEF_W_SIGN))          // 类型：16bit数据，有符号数
		{
 			t_data = (LONG)((SHORT)(Data & 0xFFFF));    // 符号位扩展
		}
 		/*** 十进制的话，对应位加1，16进制的话也是对应位加1 ***/
		t_data += ((Base == DSPDEF_BASEDEC)? dec_power_tbl[Digit]: ((ULONG)0x01 << (Digit*4)));
		/*** 限幅处理 ***/
		if(Sign == DSPDEF_NOSIGN)
		{
		    /*** t_data < Data：表示溢出，进行上限位限幅 ***/
			if(t_data < Data || t_data > UpperLimit)
			{	 
				t_data = UpperLimit;
			}
		} 
        else if(Sign == DSPDEF_W_SIGN)
        { 
            /*** (LONG)t_data < (LONG)Data：表示溢出，进行上限位限幅 ***/
			if((LONG)t_data < (LONG)Data || (LONG)t_data > (LONG)UpperLimit)
			{	 
				t_data = UpperLimit;
			}
		}
	}
	return(t_data);
}
  
  
/**********************************************************************************************/
/* Function_Name: PrmUpperLimitIdx         */
/* Description  : 根据功能码表索引号，获取对应功能码的最大值。
                  调用：需要时调用
                  输入：功能码索引号
                  输出：功能码最大值     */
/**********************************************************************************************/
ULONG RpxPrmUpperLimitIdx(USHORT Index)
{
ULONG	Data;
CPRMDEF *PrmDefHW;			 
    /*** 32bit数据 ***/
	if( PnPrmTbl[Index].PrmDefPtr->Attr.IsLong )
	{
 		PrmDefHW = PnPrmTbl[Index + 1].PrmDefPtr;
 		Data = (ULONG)( ((ULONG)PrmDefHW->UpperLimit << 16) | PnPrmTbl[Index].PrmDefPtr->UpperLimit );
	}
	/*** 16bit数据 ***/
	else
	{
	    /*** 16bit有符号数据，需要进行最大值符号位扩展 ***/
		if( PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )	 
		{
 			Data = (LONG)((SHORT)PnPrmTbl[Index].PrmDefPtr->UpperLimit);		 
		}
		else
		{
		    Data = PnPrmTbl[Index].PrmDefPtr->UpperLimit;
		}
	}
	return(Data);
}
  
/**********************************************************************************************/
/* Function_Name: PrmLimitCheckIdx         */
/* Description  : 设定参数时,对功能码的上下限进行相应的判断
                  调用：需要时调用
                  输入：Index：设定功能码索引号，Data：设定值
                  输出：设置值是否超限    */
/**********************************************************************************************/
LONG PrmLimitCheckIdx(USHORT Index, ULONG Data)
{
USHORT  idx;
ULONG	mask;
ULONG	max, min;
CPRMDEF *PrmDefHW;			 
#if defined(M3FSEL_COMPRM_ENABLE)
USHORT	upperData;			 
#endif
    /*** 功能码按照[16进制位]进行组织的情况下，逐个[16进制位]进行上下限判断，都按无符号处理 ***/
	if( PnPrmTbl[Index].PrmDefPtr->Attr.Base == DSPDEF_BASENBL ) 
	{	 
		for( idx = 0; idx < 4; idx++ )
		{
			mask = nbl_mask_table[idx];
			if( (USHORT)(Data & mask) < (PnPrmTbl[Index].PrmDefPtr->LowerLimit & (USHORT)mask) ||
				(USHORT)(Data & mask) > (PnPrmTbl[Index].PrmDefPtr->UpperLimit & (USHORT)mask) ) 
			{
				return(NG);
			}
			/*** 32bit情况下，高字部分单独处理 ***/
			if( PnPrmTbl[Index].PrmDefPtr->Attr.IsLong )
			{
				PrmDefHW = PnPrmTbl[Index + 1].PrmDefPtr;
#if defined(M3FSEL_COMPRM_ENABLE)
				upperData = (Data >> 16);		 
				if( (USHORT)(upperData & mask) < (PrmDefHW->LowerLimit & (USHORT)mask) ||
					(USHORT)(upperData & mask) > (PrmDefHW->UpperLimit & (USHORT)mask) ) 
				{
					return(NG);
				}
#else
				if( (USHORT)(Data & mask) < (PrmDefHW->LowerLimit & (USHORT)mask) ||
					(USHORT)(Data & mask) > (PrmDefHW->UpperLimit & (USHORT)mask) ) 
				{
					return(NG);
				}
#endif
			}
		}
		return(OK);
	}
 	 
	/*** 正常功能码，32bit下，得到最大最小值 ***/
	if( PnPrmTbl[Index].PrmDefPtr->Attr.IsLong )
	{
 		PrmDefHW = PnPrmTbl[Index + 1].PrmDefPtr;
 		 
		max = (ULONG)( ((ULONG)PrmDefHW->UpperLimit << 16) | PnPrmTbl[Index].PrmDefPtr->UpperLimit );
 		 
		min = (ULONG)( ((ULONG)PrmDefHW->LowerLimit << 16) | PnPrmTbl[Index].PrmDefPtr->LowerLimit );
	}
	else
	{    
	    /*** 正常功能码，16bit下，得到最大最小值，对有符号数要进行符号位扩展 ***/
		if( PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )	 
		{    
			max = (LONG)(SHORT)PnPrmTbl[Index].PrmDefPtr->UpperLimit;		 
			min = (LONG)(SHORT)PnPrmTbl[Index].PrmDefPtr->LowerLimit;		 
		}
		else
		{    
			max = PnPrmTbl[Index].PrmDefPtr->UpperLimit;		             
			min = PnPrmTbl[Index].PrmDefPtr->LowerLimit;		             
		}
	}
	 /*** 有符号数进行上下限判断 ***/
	if( PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )	             
	{
		if( (LONG)Data > (LONG)max ||
			(LONG)Data < (LONG)min )
				return(NG);	 
	}
	 /*** 无符号数进行上下限判断 ***/
	else	 
	{
		if( Data > max || Data < min )
			return(NG);	 
	}
 	return(OK);
}
  
/**********************************************************************************************/
/* Function_Name: PrmRamDigitInc         */
/* Description  : 获得指定位数递增1后的值，并执行限幅处理
                  调用：键盘操作时处理
                  输入：Index：设定功能码索引号，Data：设定值，Digit：位数
                  输出：递增后的值  */
/**********************************************************************************************/
ULONG RpxPrmRamDigitInc(USHORT Index, ULONG Data, USHORT Digit)
{
ULONG	t_data;
CPRMDEF *PrmDefPtr = PnPrmTbl[Index].PrmDefPtr;
  
    /*** 获得指定位数递增1后的值；超过最大值时，限制到最大值 ***/
    t_data = RpiPrmDataDigitInc( Data, Digit, RpxPrmUpperLimitIdx(Index),
                (UCHAR)PrmDefPtr->Attr.Base,
                (UCHAR)PrmDefPtr->Attr.IsLong,
                (UCHAR)PrmDefPtr->Attr.Sign		);
    /*** 若参数类型不是按[16bit位]组织的，进一步进行上下限幅判断 ***/
    if( PrmDefPtr->Attr.Base != DSPDEF_BASENBL )
    {
        /*** 对写入数据进行功能码的上下限判断 ***/
        if(PrmLimitCheckIdx(Index, t_data) != OK)
        {
            t_data = RpxPrmUpperLimitIdx(Index);    // 若超限，则使用最大值。
        }
    }
    /*** 操作员输入调整处理 ***/
    if( PrmDefPtr->Attr.AdjOpeIn )
    {
        t_data = PrmDefPtr->FuncPtr( PNCAL_ADJINCDATA, t_data, Digit );
    }
 	return(t_data);
}
  

/**********************************************************************************************/
/* Function_Name: PrmDataDigitDec         */
/* Description  : 获得指定位数的减1值。超过最小值时，限制到最小值。
                  调用：需要时调用
                  输入：Data：数据，Digit：位数，LowerLimit：下限值，Base：类型，IsLong：是否是32bit，Sign：是否有符号
                  输出：递减后的值  */
/**********************************************************************************************/
ULONG RpiPrmDataDigitDec(ULONG Data, USHORT Digit, ULONG LowerLimit, UCHAR Base, UCHAR IsLong, UCHAR Sign)
{
ULONG	t_data;
CHAR	nbl_data;
 	t_data = Data;
 	if(Base == DSPDEF_BASENBL)	    // 类型：按[16进制位]表示
	{
		nbl_data = (CHAR)((Data & (0x0f << (Digit*4))) >> (Digit*4));
		nbl_data -= 1;
		 /*** 对应位减1后的限幅处理***/
		if(nbl_data < (CHAR)((LowerLimit & (0x0f << (Digit*4))) >> (Digit*4)))
		{
			nbl_data = (CHAR)((LowerLimit & (0x0f << (Digit*4))) >> (Digit*4));
		}
		t_data = t_data - (t_data & (0x0f << (Digit*4))) + (nbl_data << (Digit*4));
	}
 	else
 	{
 		if(!IsLong && (Sign == DSPDEF_W_SIGN))  // 类型：16bit数据，有符号数
		{
 			t_data = (LONG)((SHORT)(Data & 0xFFFF));        // 符号位扩展
		}

 		/*** 十进制的话，对应位减1，16进制的话也是对应位减1 ***/
		t_data -= ((Base == DSPDEF_BASEDEC)? dec_power_tbl[Digit]: ((ULONG)0x01 << (Digit*4)));

		/*** 限幅处理 ***/
		if(Sign == DSPDEF_NOSIGN)
		{
		    /*** t_data > Data：表示溢出，进行下限位限幅 ***/
			if(t_data > Data || t_data < LowerLimit)
			{	 
				t_data = LowerLimit;
			}
		}
		else if(Sign == DSPDEF_W_SIGN)
		{
		    /*** (LONG)t_data > (LONG)Data：表示溢出，下限位限幅 ***/
			if((LONG)t_data > (LONG)Data || (LONG)t_data < (LONG)LowerLimit)
			{	 
				t_data = LowerLimit;
			}
		}
	}
	return(t_data);
}
  
/**********************************************************************************************/
/* Function_Name: PrmLowerLimitIdx         */
/* Description  : 根据功能码表索引号，获取对应功能码的最小值。
                  调用：需要时调用
                  输入：功能码索引号
                  输出：功能码最小值     */
/**********************************************************************************************/
ULONG RpxPrmLowerLimitIdx(USHORT Index)
{
ULONG	Data;
CPRMDEF *PrmDefHW;			 
 	 
    /*** 32bit数据 ***/
	if( PnPrmTbl[Index].PrmDefPtr->Attr.IsLong )
	{
 		PrmDefHW = PnPrmTbl[Index + 1].PrmDefPtr;
 		Data = (ULONG)( ((ULONG)PrmDefHW->LowerLimit << 16) | PnPrmTbl[Index].PrmDefPtr->LowerLimit );
	}
	/*** 16bit数据 ***/
	else
	{
	    /*** 16bit有符号数据，需要进行最小值符号位扩展 ***/
		if( PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )	 
		{
 			Data = (LONG)((SHORT)PnPrmTbl[Index].PrmDefPtr->LowerLimit);		 
		}
		else
		{
            Data = PnPrmTbl[Index].PrmDefPtr->LowerLimit;
		}
	}
 	return(Data);
}
  
/**********************************************************************************************/
/* Function_Name: APL_PrmRamDigitDec         */
/* Description  : 获得指定位数递减1后的值，并执行限幅处理
                  调用：键盘操作时处理
                  输入：Index：设定功能码索引号，Data：设定值，Digit：位数
                  输出：递减后的值  */
/**********************************************************************************************/
ULONG RpxPrmRamDigitDec(USHORT Index, ULONG Data, USHORT Digit)
{
ULONG	t_data;
CPRMDEF *PrmDefPtr = PnPrmTbl[Index].PrmDefPtr;
  
    /*** 获得指定位数递减1后的值；低于最小值时，限制到最小值 ***/
    t_data = RpiPrmDataDigitDec( Data, Digit, RpxPrmLowerLimitIdx(Index),
                (UCHAR)PrmDefPtr->Attr.Base,
                (UCHAR)PrmDefPtr->Attr.IsLong,
                (UCHAR)PrmDefPtr->Attr.Sign		);
    /*** 若参数类型不是按[16bit位]组织的，进一步进行上下限幅判断 ***/
    if( PrmDefPtr->Attr.Base != DSPDEF_BASENBL )
    {
        if(PrmLimitCheckIdx(Index, t_data) != OK)
        {
            t_data = RpxPrmLowerLimitIdx(Index);
        }
    }
    /*** 操作员输入调整处理 ***/
    if( PrmDefPtr->Attr.AdjOpeIn )
    {
        t_data = PrmDefPtr->FuncPtr( PNCAL_ADJDECDATA, t_data, Digit );
    }
    return(t_data);
}
 
/**********************************************************************************************/
/* Function_Name: APL_PrmUpperLimit         */
/* Description  : 根据功能码表结构体指针，获取对应功能码的最大值。
                  调用：需要时调用
                  输入：功能码结构体指针
                  输出：功能码最大值     */
/**********************************************************************************************/
ULONG RpiPrmUpperLimit(CPRMDEF *PdefPtr)
{
ULONG	Data;
CPRMDEF *PrmDefHW;			 
    /*** 32bit数据 ***/
	if( PdefPtr->Attr.IsLong )
	{
 		PrmDefHW = PdefPtr + 1;
 		Data = (ULONG)( ((ULONG)PrmDefHW->UpperLimit << 16) | PdefPtr->UpperLimit );
	}
	/*** 16bit数据 ***/
	else
	{
	    /*** 16bit有符号数据，需要进行最大值符号位扩展 ***/
		if( PdefPtr->Attr.Sign == DSPDEF_W_SIGN )	 
		{
 			Data = (LONG)((SHORT)PdefPtr->UpperLimit);		 
		}
		else
		{
 			Data = PdefPtr->UpperLimit;
		}
	}
 	return(Data);
}

/**********************************************************************************************/
/* Function_Name: RpiPrmLowerLimit         */
/* Description  : 根据功能码表结构体指针，获取对应功能码的最小值。
                  调用：需要时调用
                  输入：功能码结构体指针
                  输出：功能码最小值     */
/**********************************************************************************************/
ULONG RpiPrmLowerLimit(CPRMDEF *PdefPtr)
{
ULONG	Data;
CPRMDEF *PrmDefHW;

    /*** 32bit数据 ***/
 	if( PdefPtr->Attr.IsLong )
	{
		PrmDefHW = PdefPtr + 1;
		Data = (ULONG)( ((ULONG)PrmDefHW->LowerLimit << 16) | PdefPtr->LowerLimit );
	}
 	/*** 16bit数据 ***/
	else
	{
	    /*** 16bit有符号数据，需要进行最大值符号位扩展 ***/
		if( PdefPtr->Attr.Sign == DSPDEF_W_SIGN )
		{
			Data = (LONG)((SHORT)PdefPtr->LowerLimit);
		}
		else
		{
			Data = PdefPtr->LowerLimit;
		}
	}
 	return(Data);
}
  
/**********************************************************************************************/
/* Function_Name: APL_PrmReadIdx         */ 
/* Description  : 根据功能码表index，读取功能码ram值。
                  调用：需要时调用
                  输入：Index：功能码表索引号，ResData：读取结果指针，CheckType：检查属性类型
                  输出：ResData：读取结果指针，读取状态 	*/
/**********************************************************************************************/
  
  
  
  
  
  
  
  
  
  
  
 LONG	RpxPrmReadIdx(USHORT Index, ULONG *ResData, UCHAR CheckType)
{
USHORT	i, idx,data_tmp, data_get_cnt_max;
LONG	rc;
 ULONG   lkx;
 	 
	rc = PrmAttributeChkIdx(Index, CheckType);	// 参数的属性校验处理
	if(rc != OK)
		return(rc); // 参数属性校验不通过，返回对应错误码
    
	*ResData = 0;
	data_get_cnt_max = (PnPrmTbl[Index].PrmDefPtr->Attr.IsLong)? 2 : 1;
 	for(i = 0, idx = Index; i < data_get_cnt_max; i++, idx++)
	{
		data_tmp = *(PnPrmTbl[idx].PrmDefPtr->RamPtr);                   
		lkx = data_tmp;
		(*ResData) += (lkx << (16 * i));	    // 双字读取，两个字的结构体位于数组相邻位置
		/*** 若功能码位置位于数组最后元素，读取的还是双字且为双字低字，则错误，因为高字对应地址还要加1 ***/
		if(idx == PNPRMTBL_ENTNUM - 1 && (data_get_cnt_max == 2 && i == 0))
				return(PERR_SIZE);
	}
 	 
	/*** 若是16bit数据，并且是有符号数，要单独进行符号位扩展 ***/
	if(!(PnPrmTbl[Index].PrmDefPtr->Attr.IsLong) &&
		PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN)
	{
 		*ResData = (LONG)((SHORT)(*ResData & 0xFFFF));
	}
 	return(OK);
}

/**********************************************************************************************/
/* Function_Name: PrmBootWarnChkPdef         */ 
/* Description  : 参数写入重启有效检查，若重启有效，报警重启警告
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void PrmBootWarnChkPdef(CPRMDEF *PdefPtr)
{
 	if( PdefPtr->Attr.NeedReboot != PRMDEF_NEEDBOOT )
        return;
	KPI_WARNINGSET(WRN_BOOT); // 若参数是重新上电有效，则报警需要重启警告
}

/**********************************************************************************************/
/* Function_Name: RpxPrmUpdateEepromIdx         */ 
/* Description  : 将功能码ram区域写入的新数据，压入写入队列EEPQUEID_WRPRM_ROUND
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG RpxPrmUpdateEepromIdx(USHORT Index)
{
    LONG	rc;
    ULONG	pn_data;
    PRMDEF	*prm_def;
    USHORT	time;
    
	if(PnPrmTbl[Index].PrmDefPtr->Attr.Place == PRMDEF_ONLY_RAM)
		return(OK);    // 若此功能码是不存eep的，则返回。
		
	rc = RpxPrmReadIdx(Index, &pn_data, PCHK_NONE); // 从RAM中读取当前需要保存的值,更新后的值已经更新到了RAM中 
	if(rc != OK)
		return(rc);
      
	prm_def = (PRMDEF *)PnPrmTbl[Index].PrmDefPtr;
 	 
 #if 0
	pn_edata = PanOperReadEepromPrm(prm_def);
	if(!(PnPrmTbl[Index].PrmDefPtr->Attr.IsLong) &&
		PnPrmTbl[Index].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN)
	{
		if( (pn_data&0xffff) == (pn_edata&0xffff) )
            return(PRM_EEPROM_RAM_NO_DIFF);
	}
	else
	{
		if(pn_data == pn_edata)
        {
            return(PRM_EEPROM_RAM_NO_DIFF);
        }
	}
#endif
 	 
	/*** 将Ram中的新值，加入EEPQUEID_WRPRM_ROUND队列 ***/
 	if(KriAddEepromQueue(pn_data, prm_def, EEPQUEID_WRPRM_ROUND) != TRUE)
        return(PRM_EEPROM_WRITE_FAIL);
 	 
	/*** 参数写入重启有效检查，若重启有效，报警重启警告 ***/
    PrmBootWarnChkPdef((CPRMDEF *)prm_def );
 	 
	KpiRstShortTimer(&time);	// 复位计时器
	/*** 数据写入队列等待：若EEPQUEID_WRPRM_ROUND队列剩余个数为0，等待100各Scanb周期 ***/
	while(KriChkEepromQueue(EEPQUEID_WRPRM_ROUND) <= 0)
	{
        if(KpiGetShortTimer(&time) > 100)	 
            break;
    }
 	return(OK);
}

/**********************************************************************************************/
/* Function_Name: LpxCheckPrmWriteHandle         */ 
/* Description  : 参数写入权检查：写入地址有效性检查
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG LpxCheckPrmWriteHandle( void *Hmsg, UCHAR FnPnChk, CPRMDEF *PefPtr )
{
    ULONG idx ;
    
	if( PrmMngV.Hmsg == NULL ){ return( OK );} // 句柄检查

    /*** 在执行辅助功能时检查不执行，限制参数检查 ***/
	if(FnPnChk != TRUE)
    {
        return( OK );
    }
    /*** 索引功能码表，找到目标功能码结构体指针对应的index ***/
	for(idx=0; idx < PNPRMTBL_ENTNUM; idx++)
	{
		if (PnPrmTbl[idx].PrmDefPtr == PefPtr)	break ;
	}
    
	if(idx == PNPRMTBL_ENTNUM)
        { return( NG );} // 若未找到，返回错误
    
    return( OK );
}
 volatile USHORT FunctionID = 0;
  
/**********************************************************************************************/
/* Function_Name: PrmLimitCheckPdef         */ 
/* Description  : 进行参数ram值设定时的上下限制检查
                  调用：需要时调用
                  输入：PdefPtr：写入功能码结构体指针，Data：待写入数据
                  输出：是否超限状态 	*/
/**********************************************************************************************/
LONG PrmLimitCheckPdef(CPRMDEF *PdefPtr, ULONG Data)
{
USHORT  idx;
ULONG	mask;
ULONG   maxh,maxl;
ULONG   minh,minl;
ULONG	max, min;
	maxh = PnPrmTbl[ FunctionID + 1 ].PrmDefPtr->UpperLimit;
    minh = PnPrmTbl[ FunctionID + 1 ].PrmDefPtr->LowerLimit;
	/*** 按照每个4bit位为一个单元显示。此方式最大是16或10，所以都按照无符号数处理就可以 ***/
 	if( PdefPtr->Attr.Base == DSPDEF_BASENBL )                         
	{	
		for( idx = 0; idx < 4; idx++ )
		{
			mask = nbl_mask_table[idx];
			if( (USHORT)(Data & mask) < (PdefPtr->LowerLimit & (USHORT)mask) ||
				(USHORT)(Data & mask) > (PdefPtr->UpperLimit & (USHORT)mask) ) 
			{
				return(NG);    // 检查出超过范围的话，返回，无法设置。
			}
			/*** 重复限制，这种按位显示，应该只有16bit型数据 ***/
			if( PdefPtr->Attr.IsLong )                               
			{
				if( (USHORT)(Data & mask) < (minh & (USHORT)mask) ||
					(USHORT)(Data & mask) > (maxh & (USHORT)mask) )
				{
					return(NG);// 检查出超过范围的话，返回，无法设置。
				}
			}
		}
		return(OK);
	}
	/*** 32bit数据 ***/
 	if( PdefPtr->Attr.IsLong )                                         
	{
 	     
 		maxl = PdefPtr->UpperLimit;
 		minl = PdefPtr->LowerLimit;
 		max = (((ULONG)maxh) << 16) + maxl;
 		min = (((ULONG)minh) << 16) + minl;
	}
    /*** 16bit数据 ***/
	else
	{
	    /*** 16bit有符号数需要扩展符号位 ***/
		if( PdefPtr->Attr.Sign == DSPDEF_W_SIGN )                   
		{
			max = (LONG)(SHORT)PdefPtr->UpperLimit;                  
			min = (LONG)(SHORT)PdefPtr->LowerLimit;                  
		}
		else                                                         
		{
            max = PdefPtr->UpperLimit;		                     
            min = PdefPtr->LowerLimit;		                     
		}
	}
    /*** 有符号数判断是否超出上下限范围 ***/
	if( PdefPtr->Attr.Sign == DSPDEF_W_SIGN )
	{
		if( (LONG)Data > (LONG)max ||
			(LONG)Data < (LONG)min )
				return(NG);
	}
    /*** 无符号数判断是否超出上下限范围 ***/
	else
	{
		if( Data > max || Data < min )
			return(NG);
	}
	return(OK);
}

/**********************************************************************************************/
/* Function_Name: RpiPrmWriteRam         */ 
/* Description  : 将写入参数写入功能码ram中
                  调用：需要时调用
                  输入：PdefPtr：写入功能码结构体指针，Data：待写入数据，Hmsg：访问句柄，FnPnChk：权限检查
                  输出： 	*/
/**********************************************************************************************/
LONG RpiPrmWriteRam(CPRMDEF *PdefPtr, ULONG Data, HMSGIF Hmsg, UCHAR FnPnChk)
{
LONG	rc;
USHORT	data_lw, data_hw = 0;
CPRMDEF *PrmDefHW = NULL;
ULONG	mode;
 
	/*** 写入地址有效性检查 ***/
 	if( LpxCheckPrmWriteHandle( Hmsg, FnPnChk, PdefPtr ) != OK ) 
		return(PERR_WRITE_HANDLE);
	/*** 若辅助功能正在执行或者是参数禁止写入时，禁止写入 ***/
 	if(RpiFunPrmWriteInhibitChk())                               
		return(PERR_INH);
	/*** 检查是否是双字功能码中的高字，若是，返回错误 ***/
 	rc = PrmAttributeChkPdef(PdefPtr, PCHK_WORD_ORDER);          
	if(rc != OK)
		return(rc);
	/*** 写入参数，大小限制检查 ***/
 	if(PrmLimitCheckPdef(PdefPtr, Data) != OK)                   
        return(PERR_RANGE);    
    
	data_lw = *(PdefPtr->RamPtr);   // 之前检查都通过的话，读取功能码当前数据
    PrmMngV.APRMWrDiff = 0;         // ram和eep内容差异设为0

    /*** 若写入新数据和ram中当前数据不相等，则差异变量置一 ***/
    if( data_lw != (USHORT)Data )
    {
        PrmMngV.APRMWrDiff = 1;
    }    
    
	*(PdefPtr->RamPtr) = (USHORT)Data; // 取低16bit赋值给功能码ram  

    /*** 32bit数据写入 ***/
	if(PdefPtr->Attr.IsLong)                                    
	{	
#if 0
		PrmDefHW = PdefPtr + 1;                                  
		data_hw = *(PrmDefHW->RamPtr);				             
		*(PrmDefHW->RamPtr) = (USHORT)(Data >> 16);	             
         if( data_hw != ((USHORT)(Data >> 16)))
        {
            PrmMngV.APRMWrDiff = 1;
        }
#else
        *(PnPrmTbl[ FunctionID + 1 ].PrmDefPtr->RamPtr) = (USHORT)(Data >> 16);
#endif
	}
	/*** 参数计算处理(即有些功能码更新后,需要将相应的函数进行更新处理) ***/  
 
	if((Hmsg == &SrlMsg) || (Hmsg == &UsbMsg))
	    mode = PNCAL_PRMCALFROMREG ;                            
	else
	    mode = PNCAL_PRMCAL ;          	// 面板操作                           
  
    if( (PdefPtr->ChkSpUse & (KPI_CHKSPUSE_COMMON | KPI_CHKSPUSE_ROTARY)) != 0x00 )
	{
		KriResetParamError();									
		rc = (*PdefPtr->FuncPtr)( mode, 0, 0 );		// 参数计算	
		/*** 参数计算错误的情况下处理：(需要将数据恢复为写入前的数据)   ***/
        if((Alm.PrmErrInfo.ErrFlag == TRUE) || (rc != TRUE)) 
        {
			*(PdefPtr->RamPtr) = data_lw;			// 恢复低16位的数据			
			if( PdefPtr->Attr.IsLong )
			{
				*(PrmDefHW->RamPtr) = data_hw;		// 恢复高16位的数据			
			}
			if( rc == TRUE )
			{
				(*PdefPtr->FuncPtr)( mode, 0, 0 );	// 重新参数计算			
			}
			return( PERR_CALC );
		}
	}
	return(OK);
}

/**********************************************************************************************/
/* Function_Name: RpxPrmWriteRamIdx         */ 
/* Description  : 将写入参数写入功能码ram中
                  调用：需要时调用
                  输入：Index：写入功能码对应index，Data：待写入数据，CheckType：检查类型，Hmsg：访问句柄
                  输出： 	*/
/**********************************************************************************************/
LONG RpxPrmWriteRamIdx(USHORT Index, ULONG Data, UCHAR CheckType, HMSGIF Hmsg)
{
LONG	rc;
	/*** 根据确定的参数属性，检查指定的参数是否妥当 ***/
	rc = PrmAttributeChkIdx(Index, CheckType);                   
	if(rc != OK)
	{
		return(rc);
	}
 	 
	/*** 将写入参数写入功能码ram中 ***/  
 	FunctionID = Index;
	rc = RpiPrmWriteRam(PnPrmTbl[Index].PrmDefPtr, Data, Hmsg, TRUE);
 	return(rc);
}

/**********************************************************************************************/
/* Function_Name: RpxPrmSearchIdxReg         */ 
/* Description  : 根据参数读取地址，索引功能码在其数组中的位置
                  这里的索引算法，采用二分法查找，效率较高。但二分法要求查找表中的查找元素必须升/降序排列。这里是升序的
                  这里的功能码地址随着数组位置增大，也是增大的；双字读取，则双字肯定是在数组相邻位置，并且其地址连续
                  调用：需要时调用
                  输入：RegNo：寄存器号，FindIndex：索引到的index
                  输出：FindIndex：索引到的index，索引是否成功状态 	*/
/**********************************************************************************************/
LONG RpxPrmSearchIdxReg(USHORT RegNo, USHORT *FindIndex)
{
	USHORT	reg_no, low, high, mid;
 	reg_no = (RegNo & 0x0FFF);
	low = 0;
	high = PNPRMTBL_ENTNUM - 1;
	while(low <= high)
	{
		mid = (low + high) >> 1;
		if(reg_no < PnPrmTbl[mid].PnNo)
			high = mid - 1;
		else if(reg_no > PnPrmTbl[mid].PnNo)
			low = mid + 1;
		else {
			*FindIndex = mid;
			return(OK);
		}
	}
	return(PERR_FOUND);
}

/**********************************************************************************************/
/* Function_Name: RpxReadPrmRegister         */ 
/* Description  : 参数读取函数，直接读取功能码ram中的数据
                  调用：需要时调用
                  输入：RegNo：寄存器号，Number：读取个数，RdBuf：读取结果指针，Hmsg：访问句柄
                  输出：RdBuf：读取结果，读取状态反馈 	*/
/**********************************************************************************************/
LONG RpxReadPrmRegister(LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg )
{
	LONG	rc;
	USHORT	idx,i;
	LONG	pn_data;

    /*** 功能码群组越界校验 ***/
	if((((RegNo & 0x0f00) == 0x0700) && (((RegNo + Number) & 0x0f00) == 0x0800)) ||
	   (((RegNo & 0x0f00) == 0x0C00) && (((RegNo + Number) & 0x0f00) == 0x0D00)) ||
	   ((RegNo & 0x0fff) + Number >= 0x1000))
	{
		Hmsg->ErrRno = (USHORT)RegNo;	 // 异常寄存器编号			
		return( REGIF_DAMTHERR );					
	}

    /*** Modbus 通讯地址映射处理：OpeReg.CommType为1表示串口通讯，USB为0  ***/
    if( ( Prm.addmapEn & 0x0001 ) == 0x0001 && OpeReg.CommType == 1) // 1#映射
    {
        if( RegNo == Prm.addmap1s ) RegNo = Prm.addmap1e;
    }
    if( ( Prm.addmapEn & 0x0010 ) == 0x0010 && OpeReg.CommType == 1) // 2#映射
    {
        if( RegNo == Prm.addmap2s ) RegNo = Prm.addmap2e;    
    }
    if( RegNo >= 1000 && RegNo <= 1015 )
    {
        if( 1 == MuxAxis485_Read(RegNo, Number, (USHORT *)RdBuf))
        {
            return( REGIF_COMPLETE );
        }
        else
        {
            Hmsg->ErrRno = (USHORT)RegNo;
            return( REGIF_REGNOERR );
        }
    }
 
  	/*** 这里根据读取参数地址，索引到了功能码所处数组位置。功能码排列方式是：
    结构体数组，每个功能码对应一个结构体，这里idx是功能码结构体在数组中的位置 ***/
 	if(OK != RpxPrmSearchIdxReg((USHORT)(RegNo & 0x0FFF), &idx))
	{
		Hmsg->ErrRno = (USHORT)RegNo;
		return( REGIF_REGNOERR );
	}    

    /*** 如果高字标志位为1,则说明此次读取操作起始地址对应LONG的高字，这样做是禁止的 ***/
	if( PnPrmTbl[idx].PrmDefPtr->Attr.WordOrder != 0 )      
	{                                                       
		Hmsg->ErrRno = (USHORT)RegNo;                       
		return( REGIF_DAMTHERR );
	}

    /*** 连续读取需要获取的功能码 ***/
	for( i=0; i < Number; i++, idx++ )
	{
	    /*** 地址连续性检查 ***/
		if( PnPrmTbl[idx].PnNo != ((RegNo & 0x0FFF) + i) )
		{
			Hmsg->ErrRno = RegNo + i;                           
			return( REGIF_REGNOERR );                           
		}
        /*** 功能码群组越界校验 ***/
 		if((((RegNo & 0x0F00) == 0x0700) && (((RegNo + i) & 0x0F00) == 0x0800)) ||
		   (((RegNo & 0x0F00) == 0x0C00) && (((RegNo + i) & 0x0F00) == 0x0D00)))
		{
			Hmsg->ErrRno = RegNo + i;                           
			return( REGIF_DAMTHERR );                           
		}

        /*** 参数读取函数，根据参数表index，直接读取功能码ram中的数据 ***/
		rc = RpxPrmReadIdx(idx, (ULONG *)(&pn_data), PCHK_DEF); 
		if(rc != OK)
		{
			Hmsg->ErrRno = RegNo + i;				             
			switch(rc)
			{
			case PERR_DFIT:
				return( REGIF_DAMTHERR );			             
			case PERR_PRMCOPY:
				return( REGIF_FOPEERR3 );			             
			default:
				return( REGIF_REGNOERR );			             
			}
		}
		/*** 将读取结果，赋值给对应的读取应答数组 ***/
 		if(PnPrmTbl[idx].PrmDefPtr->Attr.IsLong)                 
		{
			if(i+1 < Number)
			{    
			    /*** 根据设定的32bit双字排列顺序执行对应赋值 ***/
                if( ( Prm.addmapEn & 0xF000 ) == 0x0000 )
                {
#if 0
                    RdBuf[i+0] = (USHORT)(pn_data & 0xffff);
                    RdBuf[i+1] = (USHORT)(pn_data>>16);
#else
                    RdBuf[4*i+0] = (pn_data >> 8) & 0x00ff;
                    RdBuf[4*i+1] = (pn_data     ) & 0x00ff;
                    RdBuf[4*i+2] = (pn_data >>24) & 0x00ff;
                    RdBuf[4*i+3] = (pn_data >>16) & 0x00ff;
#endif
                }
                else
                {
#if 0
                    RdBuf[i+1] = (USHORT)(pn_data & 0xffff);
                    RdBuf[i+0] = (USHORT)(pn_data>>16);
#else
                    RdBuf[4*i+2] = (pn_data >> 8) & 0x00ff;
                    RdBuf[4*i+3] = (pn_data     ) & 0x00ff;
                    RdBuf[4*i+0] = (pn_data >>24) & 0x00ff;
                    RdBuf[4*i+1] = (pn_data >>16) & 0x00ff;
#endif
                }
                /*** 读取的是双字，则读取个数和读取地址加2 ***/
				i++;
				idx++;
			}
			else
			{
				RdBuf[i] = (USHORT)(pn_data & 0xffff); // 最后个数凑不够双字，则发送低字
			}
		}
		else  // 16bit数据直接赋值即可                                                  
		{
			RdBuf[i + 1] = (pn_data    ) & 0x00FF;
			RdBuf[i + 0] = (pn_data >>8) & 0x00FF;
		}
	}

    /*** 如果本次读取中最后一个功能码读取的是双字，自己也在低字位置，则报错 ***/
	if(PnPrmTbl[idx - 1].PrmDefPtr->Attr.IsLong &&
		PnPrmTbl[idx - 1].PrmDefPtr->Attr.WordOrder == 0 )
	{
		Hmsg->ErrRno = PnPrmTbl[idx - 1].PnNo;
		return( REGIF_DAMTHERR );                               
	}
	return( REGIF_COMPLETE );    
}

/**********************************************************************************************/
/* Function_Name: WritePrmRegister         */ 
/* Description  : 参数写入ram函数
                  调用：需要时调用
                  输入：RegNo：寄存器号，Number：写入个数，RdBuf：写入数据指针，Hmsg：访问句柄
                  输出：RdBuf：读取结果，读取状态反馈 	*/
/**********************************************************************************************/
LONG RpxWritePrmRegister(LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg)
{
	LONG	rc;
	USHORT	idx,i;
	ULONG	pn_data;
	USHORT	time;
  
  
	/*** 功能码群组越界校验 ***/
	if((((RegNo & 0x0f00) == 0x0C00) && (((RegNo + Number) & 0x0f00) == 0x0D00) ) || \
	   ((RegNo & 0x0fff) + Number >= 0x1000))
	{
		Hmsg->ErrRno = (USHORT)RegNo;				
		return( REGIF_DAMTHERR );					
	}
       
    /*** Modbus 通讯地址映射处理：OpeReg.CommType为1表示串口通讯，USB为0  ***/
    if( ( Prm.addmapEn & 0x0001 ) == 0x0001 && OpeReg.CommType == 1)    
    {
        if( RegNo == Prm.addmap1s ) RegNo = Prm.addmap1e;
    }
     if( ( Prm.addmapEn & 0x0010 ) == 0x0010 && OpeReg.CommType == 1)     
    {
        if( RegNo == Prm.addmap2s ) RegNo = Prm.addmap2e;    
    }
      
    OpeReg.PrmNo = (USHORT)RegNo;
     if( OpeReg.PrmNo >= 2000 && OpeReg.PrmNo <= 2007 )
    {
        if( 1 == MuxAxis485_Write( RegNo, Number, RdBuf ))
        {
            return( REGIF_COMPLETE );
        }
        else
        {
            return( REGIF_REGNOERR );
        }
    }
  
  
	/*** 这里根据读取参数地址，索引到了功能码所处数组位置。功能码排列方式是：
    结构体数组，每个功能码对应一个结构体，这里idx是功能码结构体在数组中的位置 ***/
	if(OK != RpxPrmSearchIdxReg((USHORT)(RegNo & 0x0fff), &idx))
	{
		Hmsg->ErrRno = (USHORT)RegNo;				
		return( REGIF_REGNOERR );					
	}

    /*** 如果高字标志位为1,则说明此次读取操作起始地址对应LONG的高字，这样做是禁止的 ***/
	if( PnPrmTbl[idx].PrmDefPtr->Attr.WordOrder != 0 )
	{
		Hmsg->ErrRno = (USHORT)RegNo;				
		return( REGIF_DAMTHERR );					
	}

    /*** 连续写入需要写入的功能码 ***/
	for( i=0; i < Number; i++, idx++ )
	{
 		/*** 访问权限：操作寄存器的参数访问打开，或者当前设定访问等级必须高于当前功能码
	    访问等级，0x0D00及以上功能码，访问等级必须是系统等级 ***/ 
 		if ((OpeReg.PrmAccess == FALSE) && (PrmAttributeChkIdx( idx, PCHK_ACCS_LVL ) != OK) )
		{
			Hmsg->ErrRno = RegNo + i;					 
			return( REGIF_REGNOERR );					 
		}
 		 
 		if ((OpeReg.PrmAccess == FALSE) && ((RegNo & 0x0f00) >= 0x0D00 && Hmsg->AccsLvl != ACCLVL_SYSTEM) )
		{
			Hmsg->ErrRno = RegNo + i;					 
			return( REGIF_REGNOERR );					 
		}

        /*** 地址连续性检查 ***/
		if( PnPrmTbl[idx].PnNo != ((RegNo + i) & 0x0fff) )
		{
			Hmsg->ErrRno = RegNo + i;				 
			return( REGIF_REGNOERR );				 
		}
 		 
		/*** 根据32bit或16bit情况下，从通讯数据获取写入数据内容 ***/
		if(PnPrmTbl[idx].PrmDefPtr->Attr.IsLong)
		{	 
			if(i + 1 < Number)
			{
			    /*** 根据设定的32bit双字排列顺序执行对应赋值 ***/
                if(( Prm.addmapEn & 0xF000 ) == 0x0000 )    
                {
                    pn_data = RdBuf[i] + ((ULONG)RdBuf[i + 1] << 16);
                }
                else
                {
                    pn_data = RdBuf[i + 1 ] + ((ULONG)RdBuf[i] << 16);
                }
			}
			else
			{
				Hmsg->ErrRno = RegNo + i;			
				return( REGIF_DAMTHERR );			
			}
		}
		else
		{	
			pn_data = RdBuf[i];
            /*** 16bit有符号数，需要进行符号位扩展 ***/
			if(PnPrmTbl[idx].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN)
			{
				pn_data = (LONG)((SHORT)(pn_data & 0xFFFF));
			}
		}
		/*** 将写入参数写入功能码ram中 ***/
 		rc = RpxPrmWriteRamIdx(idx, pn_data, PCHK_DEF | PCHK_RONLY, Hmsg);
		if(rc != OK)
		{
			Hmsg->ErrRno = RegNo + i;				 
			switch(rc)
			{
			case PERR_DFIT:
				return( REGIF_DAMTHERR );			 
			case PERR_RONLY:
				return( REGIF_REGNOERR );			 
			case PERR_CALC:
				return( REGIF_DACALERR );			 
			case PERR_RANGE:
				return( REGIF_DALMTERR );			 
			case PERR_PRMCOPY:
			case PERR_WRITE_HANDLE:
				return( REGIF_FOPEERR3 );			 
			default:
				return( REGIF_REGNOERR );			 
			}
		}
          
 		if(!(RegNo & 0x1000))	 
		{
 		    //Pn290 bit0设置为4时，不进行EEPROM写入，避免Pn290在写EEPROM之前变化导致Er.020的问题。
 		    if((RegNo & 0x0FFF)  == 0x0290)
 		    {
 		        if((pn_data & 0x0004) == 0x0004)
 		        {
 		           return( REGIF_COMPLETE );
 		        }

 		    }
            if(( Prm.ComSaveEeprom & 0x000F ) == 0x0001 || 	// 若设置的是485通讯写入保存eep，则保存
                    Usbif.f.USBRecFlag == 1             ||	// USB通讯过来的，则保存。此标志是，USB批量接收数据成功时，置1的
                    Iprm.FATest1 == 1                   || 	// 工厂测试模式，要保存。
                    Iprm.FATest2 == 1                   ||
                    (RegNo & 0x0FFF)  == 0x079E         ||	// 整机/单板测试模式密匙，保存的。
                    (RegNo & 0x0FFF)  == 0x0085 )			// 485通讯写入是否保存到EEP选项设置,保存EEP的
            {
                Usbif.f.USBRecFlag = 0;
                rc = PRM_EEPROM_WRITE_FAIL;
                KpiRstShortTimer(&time);	// 写入超时计时开始
                while(rc == PRM_EEPROM_WRITE_FAIL)
                {
					/*** 将功能码ram区域写入的新数据，压入写入队列EEPQUEID_WRPRM_ROUND ***/
                    rc = RpxPrmUpdateEepromIdx(idx);                    
                    if(KpiGetShortTimer(&time) > 100)	 
                    {
                        break;
                    }
                }
                if(rc != OK && rc != PRM_EEPROM_RAM_NO_DIFF)
                {
                    return( REGIF_DAMTHERR );
                }
            }
		}
        /*** 若是long型，则写入word数组和参数数组的索引号额外再加1 ***/
		if(PnPrmTbl[idx].PrmDefPtr->Attr.IsLong)
		{
			i++;
			idx++;
		}
	}
	return( REGIF_COMPLETE );
}
 
/**********************************************************************************************/
/* Function_Name: RpiPrmWriteRamForFn         */ 
/* Description  : Fn功能中参数写入ram函数
                  调用：Fn功能中调用
                  输入：PdefPtr：功能码结构体指针，Data：写入数据，Hmsg：访问句柄
                  输出： 	*/
/**********************************************************************************************/
  
LONG	RpiPrmWriteRamForFn(CPRMDEF *PdefPtr, ULONG Data, HMSGIF Hmsg)
{
LONG	rc ;
	/*** 将写入参数写入功能码ram中 ***/
 	rc = RpiPrmWriteRam(PdefPtr, Data, Hmsg, FALSE) ;
 	return(rc) ;
}
 
/**********************************************************************************************/
/* Function_Name: APL_RpiPrmUpdateNvmem         */ 
/* Description  : 根据ram中的值，判断是否和eep相等，若不等，则更新eep
                  调用：Fn功能中调用
                  输入：PdefPtr：功能码结构体指针
                  输出： 	*/
/**********************************************************************************************/
LONG	RpiPrmUpdateNvmem(CPRMDEF *PdefPtr)
{
LONG	rc;
ULONG	pn_data, pn_edata;
USHORT	time;
	if(PdefPtr->Attr.Place == PRMDEF_ONLY_RAM)	
		return(OK);	 // 不存储EEP参数，不需存储，直接返回

    /*** 根据功能码结构体指针，读取功能码ram值 ***/ 	
	rc = RpiPrmRead(PdefPtr, &pn_data);
	if(rc != OK)
	{
		return(rc);
	}
    /*** 通过参数结构体指针读取eep中的数据并返回 ***/   
 	pn_edata = KriReadEepromPrm((PRMDEF *)PdefPtr);
	if(pn_data == pn_edata)	return(OK);	// 若相等，则直接返回
 	 
	/*** 不相等时需要写入，先检查EEPQUEID_WRPRM_ROUND序列是否已满 ***/
	if(KriChkEepromQueue(EEPQUEID_WRPRM_ROUND) <= 0) return(PRM_EEPROM_WRITE_WAIT);
 	 
	/*** 将待写入数据pn_data填入EEPQUEID_WRPRM_ROUND队列 ***/
	if(KriAddEepromQueue(pn_data, (PRMDEF *)PdefPtr, EEPQUEID_WRPRM_ROUND) != TRUE)
		return(PRM_EEPROM_WRITE_FAIL);
 	 
	/*** 参数写入重启有效检查，若重启有效，报警重启警告 ***/
	PrmBootWarnChkPdef(PdefPtr);
 	 
	/*** 排队检查 ***/
	KpiRstShortTimer(&time);		// 复位计时器
	while(KriChkEepromQueue(EEPQUEID_WRPRM_ROUND) <= 0)
	{
		if(KpiGetShortTimer(&time) > 100)	 
			break;
	}
 	return(OK);
}
  
/**********************************************************************************************/
/* Function_Name: RpiAllPrmCalcMain         */ 
/* Description  : 全参数定义参数计算
                  调用：初始化调用一次
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void	RpiAllPrmCalcMain( void )
{
    LONG	i;
    CPRMDEF	*PrmDefPtr;

    /*** 参数计算循环 ***/
	for( i=0; i < PnPrmTblEntNum; i++ )
	{
		PrmDefPtr = PnPrmTbl[i].PrmDefPtr;
		if( PrmDefPtr->FuncPtr == NULL ){ continue;} // 若参数附加函数指针为空，直接进行下一次判断
        if( (PrmDefPtr->ChkSpUse & (KPI_CHKSPUSE_COMMON | KPI_CHKSPUSE_ROTARY)) == 0x00 )
        {   
            continue;
        }
		(*PrmDefPtr->FuncPtr)( PNCAL_PRMCAL, 0, 0 ); // 进行附加函数计算		
	}
	return;
}

/**********************************************************************************************/
/* Function_Name: RpiPrmReadNvmem         */ 
/* Description  : 根据功能码结构体指针，读取功能码EEP值
                  调用：根据需要调用
                  输入：PdefPtr：功能码结构体指针，ResData：读取结果指针
                  输出：ResData：读取结果，读取状态 	*/
/**********************************************************************************************/
LONG	RpiPrmReadNvmem(CPRMDEF *PdefPtr, ULONG *ResData)
{
LONG	rc;
	/*** 参数的属性校验处理：判断是否为32位的高16位 ***/
 	rc = PrmAttributeChkPdef(PdefPtr, PCHK_WORD_ORDER);
	if(rc != OK)
		return(rc);
	/*** 通过参数结构体指针读取eep中的数据并返回 ***/
 	*ResData = KriReadEepromPrm(PdefPtr);
	/*** 16bit有符号数，需要符号位扩展 ***/
 	if(!(PdefPtr->Attr.IsLong) &&
		PdefPtr->Attr.Sign == DSPDEF_W_SIGN)
	{
		*ResData = (LONG)((SHORT)(*ResData & 0xFFFF));
	}
	return(OK);
}
/**********************************************************************************************/
/* Function_Name: RpiPrmRead         */ 
/* Description  : 根据功能码结构体指针，读取功能码ram值
                  调用：根据需要调用
                  输入：PdefPtr：功能码结构体指针，ResData：读取结果指针
                  输出：ResData：读取结果，读取状态	*/
/**********************************************************************************************/
LONG	RpiPrmRead(CPRMDEF *PdefPtr, ULONG *ResData)
{
USHORT data_tmp;
LONG	rc;
ULONG Data1,Data2;
volatile ULONG addr;
/*** 参数的属性校验处理：判断是否为32位的高16位 ***/
	rc = PrmAttributeChkPdef(PdefPtr, PCHK_WORD_ORDER);
	if(rc != OK)
		return(rc);
 	*ResData = 0;
 #if 1
	if( (PdefPtr->Attr.IsLong) == 1 )
	{
	    addr = (ULONG)(PdefPtr)->RamPtr;
	    Data1 = (*((USHORT *)addr)) & 0xFFFF;
	    addr += 1;
	    Data2 = (*((USHORT *)addr)) & 0xFFFF;
	    *ResData = (Data2 << 16) + Data1;
	}
	else
	{
	    data_tmp = *((PdefPtr)->RamPtr);
	    *ResData = data_tmp;
	}
 #else
 	/*** 读取32bit或16bit数据 ***/
    data_get_cnt_max = (PdefPtr->Attr.IsLong)? 2 : 1;
	for(i = 0; i < data_get_cnt_max; i++)
	{
		data_tmp = *((PdefPtr+i)->RamPtr);
 		*ResData |= data_tmp << (16 * i);
	}
#endif
	/*** 16bit有符号数，需要符号位扩展 ***/
	if(!(PdefPtr->Attr.IsLong) &&
		PdefPtr->Attr.Sign == DSPDEF_W_SIGN)
	{
		*ResData = (LONG)((SHORT)(*ResData & 0xFFFF));
	}
 	return(OK);
}
 
 
 
#define	GET_EEPADR( pDef )		( (pDef)->EepromAddr & PRMDEF_EEPADRMSK )
/**********************************************************************************************/
/* Function_Name: KriInitEepromUserPrm         */ 
/* Description  : EEP的用户参数恢复出厂默认
                  调用：根据需要调用
                  输入：
                  输出：	*/
/**********************************************************************************************/
void	KriInitEepromUserPrm( void )
{
LONG	i;
USHORT	eaddr;
USHORT	rdata[2];
CPRMDEF	*pPrmDef;
 		GetEepromSemaphore( WAIT );		// 获取EEP信号量
          
        Interrupt_disableMaster();		 // 禁止中断
         
		WriteEepromEnable( );			// EEP写使能
 		for( i=0; i < PnPrmTblEntNum; i++ )
		{
			pPrmDef = PnPrmTbl[i].PrmDefPtr;
			/*** 对所有访问等级小于系统级、并且存储EEP的用户参数进行默认值恢复 ***/
			if( (pPrmDef->Attr.Place == PRMDEF_RAM_EEPROM) &&
				(pPrmDef->AccessLevel < ACCLVL_SYSTEM) && (pPrmDef->RamPtr != NULL) )
			{
				eaddr = GET_EEPADR( pPrmDef );
				rdata[0] = ReadEepromWord( eaddr + 0 );
                KlibWaitms( 2 );
				/*** Pn用户参数组，16bit数据占据32bit，高16bit存储的是默认值 ***/
				rdata[1] = ReadEepromWord( eaddr + 1 );
                KlibWaitms( 2 );
				*pPrmDef->RamPtr = rdata[1];		// 默认值赋值给ram地址
				/*** 若EEP值和默认EEP值不相等，则将默认值更新至当前参数EEP区域 ***/
				if( rdata[0] != rdata[1] )
				{
					WriteEepromWord( eaddr, rdata[1], WAIT );
                    KlibWaitms( 8 );
				}
			}
		}
          
          
          
        KlibWaitms( 10 );
        Eephdr.DefChkSum = ReadEepromWord( EEPADR_HEADER + 2 );	 // 读取EEP默认参数的求和校验值
 		Eephdr.UsrChkSum = Eephdr.DefChkSum;
		EepInfo.UsrChkSum = Eephdr.UsrChkSum;			// 将读到的值赋值给用户求和校验值
        KlibWaitms( 10 );
 		WriteEepromWord( EEPADR_USRCHK, Eephdr.UsrChkSum, WAIT );	// 写入用户求和校验值到EEP
		WriteEepromDisable( );		// EEP写禁止
		FreeEepromSemaphore( );		// 释放EEP信号量
 
        Interrupt_enableMaster();	// 使能中断
 		return;
}
  
  
  
/**********************************************************************************************/
/* Function_Name: RpiPrmInitUserParameter         */ 
/* Description  : EEP的用户参数恢复出厂默认
                  调用：Fn恢复出厂默认值调用
                  输入：
                  输出：	*/
/**********************************************************************************************/
void	RpiPrmInitUserParameter( void )
{
 		KriInitEepromUserPrm( );		// EEP的用户参数恢复出厂默认		 	
 		KPI_WARNINGSET(WRN_BOOT);		// 全部恢复出厂默认参数，报警需要重启警告		 
		return;
}
 
  
 

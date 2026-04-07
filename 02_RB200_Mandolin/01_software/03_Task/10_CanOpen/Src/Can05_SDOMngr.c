/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2018 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can05_SDOMngr.c : CANOpen SDO处理部分	 												    */
/*		针对对象 0x1XXX,0x2XXX,0x6XXX 进行相关的处理												*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"


/****************************************************************************************************/
/*Function_Name: ODB2XXX_Check                                                                    	*/
/*Description  : 对厂家定义的厂家参数进行检索处理                                                   */
/****************************************************************************************************/
USHORT ODB2XXX_Check(USHORT OD_Addr,USHORT OD_SubIndex)
{
USHORT RegNo = ((OD_Addr & 0x0F) << 8 ) + OD_SubIndex;
USHORT reg_no, low, high, mid;

	reg_no = (RegNo & 0x0FFF);
	low = 0;
	high = PnPrmTblEntNum - 1;
	while(low <= high)
	{
		mid = (low + high) >> 1;
		if(reg_no < PnPrmTbl[mid].PnNo)
			high = mid - 1;
		else if(reg_no > PnPrmTbl[mid].PnNo)
			low = mid + 1;
		else 
		{
			return mid;
		}
	}
	return 0xFFFF;
}
/****************************************************************************************************/
/*Function_Name: ODB2EXX_Check                                                                    	*/
/*Description  : 对厂家定义的厂家参数进行检索处理(Unxxx)                                            */
/****************************************************************************************************/
USHORT ODB2EXX_Check(USHORT OD_Addr,USHORT OD_SubIndex)
{
USHORT RegNo = ((OD_Addr & 0x0F) << 8 ) + OD_SubIndex;
USHORT reg_no, low, high, mid;

	reg_no = (RegNo & 0x0FFF);
	low = 0;
	high = UnRegTblEntNum - 1;
	while(low <= high)
	{
		mid = (low + high) >> 1;
		if(reg_no < UnRegTbl[mid].UnNo)
			high = mid - 1;
		else if(reg_no > UnRegTbl[mid].UnNo)
			low = mid + 1;
		else 
		{
			return mid;
		}
	}
	return 0xFFFF;
}

/****************************************************************************************************/
/*Function_Name: ODB2XXX_ReadDeal                                                                  	*/
/*Description  : 对厂家定义的厂家参数进行读取处理                                                   */
/****************************************************************************************************/
void ODB2XXX_ReadDeal(USHORT OD_IndexValue,USHORT SDOSendNum)
{
USHORT data_tmp;
	/*----------------------------------------------------------------------------------------------*/
  	/* 回复主机之前,先对该对象字典的数据类型进行判断处理,用来区分为32位或64位						*/
  	/*----------------------------------------------------------------------------------------------*/
  	if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.IsLong == 0)
	{
		/*------------------------------------------------------------------------------------------*/
	  	/* 数据类型为 16 位																			*/
	  	/*------------------------------------------------------------------------------------------*/
	  	OD_V.SendBuf[0] = 0x4B;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
		data_tmp = (USHORT)(*(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr));
        OD_V.SendBuf[4] = data_tmp & 0x00FF;
        OD_V.SendBuf[5] = (data_tmp >> 8) & 0x00FF;
        OD_V.SendLength = 6;
	}
	else
	{
		/*------------------------------------------------------------------------------------------*/
	  	/* 数据类型为 32 位																			*/
	  	/*------------------------------------------------------------------------------------------*/
        OD_V.SendBuf[0] = 0x43;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
		/*------------------------------------------------------------------------------------------*/
		data_tmp = (USHORT)(*(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr));
        OD_V.SendBuf[4] = data_tmp & 0x00FF;
        OD_V.SendBuf[5] = (data_tmp >> 8) & 0x00FF;
		/*------------------------------------------------------------------------------------------*/
		data_tmp = (USHORT)(*(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->RamPtr));
        OD_V.SendBuf[6] = data_tmp & 0x00FF;
        OD_V.SendBuf[7] = (data_tmp >> 8) & 0x00FF;
        OD_V.SendLength = 8;	
	}
}

/****************************************************************************************************/
/*Function_Name: ODB2EXX_ReadDeal                                                                  	*/
/*Description  : 对厂家定义的厂家参数进行读取处理  (Unxxx)                                          */
/****************************************************************************************************/

ULONG ODB2EXX_ReadData( MONDEF *UnDefPtr)
{
ULONG DataTmp  = UnDefPtr->FuncPtr( UnDefPtr );
    return (DataTmp);
}

/****************************************************************************************************/
/*Function_Name: ODB2EXX_ReadDeal                                                                  	*/
/*Description  : 对厂家定义的厂家参数进行读取处理  (Unxxx)                                          */
/****************************************************************************************************/
void ODB2EXX_ReadDeal(USHORT OD_IndexValue,USHORT SDOSendNum)
{
ULONG data_tmp;
MONDEF	*mondef_tmp;
    mondef_tmp = (MONDEF *)UnMonTbl[OD_IndexValue].MonDefPtr;
    
  	if(UnMonTbl[OD_IndexValue].MonDefPtr->IsLong == 0)
	{
	  	OD_V.SendBuf[0] = 0x4B;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
		data_tmp = ODB2EXX_ReadData(mondef_tmp);
        OD_V.SendBuf[4] = data_tmp & 0x00FF;
        OD_V.SendBuf[5] = (data_tmp >> 8) & 0x00FF;
        OD_V.SendLength = 6;
	}
	else
	{
        OD_V.SendBuf[0] = 0x43;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
		/*------------------------------------------------------------------------------------------*/
		data_tmp = ODB2EXX_ReadData(mondef_tmp);
        OD_V.SendBuf[4] = data_tmp & 0x00FF;
        OD_V.SendBuf[5] = (data_tmp >> 8) & 0x00FF;
		/*------------------------------------------------------------------------------------------*/
		data_tmp = data_tmp >> 16;
        OD_V.SendBuf[6] = data_tmp & 0x00FF;
        OD_V.SendBuf[7] = (data_tmp >> 8) & 0x00FF;
        OD_V.SendLength = 8;	
	}
}
/****************************************************************************************************/
/*Function_Name: ODB2XXX_WriteDeal                                                                 	*/
/*Description  : 对厂家定义的厂家参数进行写入处理                                                   */
/****************************************************************************************************/
void ODB2XXX_WriteDeal(USHORT OD_IndexValue,USHORT SDOSendNum,UCHAR TYPE)
{
union ODUnion SDO_WriteData;
ULONG max,min,Data;
PRMDEF	*prm_def;
	/*----------------------------------------------------------------------------------------------*/
	/* 写入的数据临时保存																			*/
	/*----------------------------------------------------------------------------------------------*/
    SDO_WriteData.all = CanVar.SDO[SDOSendNum].SDOData;
    
    /*----------------------------------------------------------------------------------------------*/
    /* 判断数据是否可写,只读数据不写入                                                              */
	/*----------------------------------------------------------------------------------------------*/
    if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.ReadOnly == 1)
    {
        OD_SDOError(SDOSendNum,WRITE_RO_OBJECT);
        return;
    }
    
	/*----------------------------------------------------------------------------------------------*/
	/* 对写入的数据的大小值进行判断处理,先取出功能码的最大值和最小值								                    */
	/*----------------------------------------------------------------------------------------------*/
	if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.IsLong)
	{
		max = (ULONG)( ((ULONG)(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->UpperLimit) << 16) |\
		  				PnPrmTbl[OD_IndexValue].PrmDefPtr->UpperLimit );
		min = (ULONG)( ((ULONG)(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->LowerLimit) << 16) | \
		  				PnPrmTbl[OD_IndexValue].PrmDefPtr->LowerLimit );
	}
    
	/*----------------------------------------------------------------------------------------------*/
	else
	{
		if( PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )
		{
			max = (LONG)(SHORT)PnPrmTbl[OD_IndexValue].PrmDefPtr->UpperLimit;
			min = (LONG)(SHORT)PnPrmTbl[OD_IndexValue].PrmDefPtr->LowerLimit;
		}
		else
		{
			max = PnPrmTbl[OD_IndexValue].PrmDefPtr->UpperLimit;
			min = PnPrmTbl[OD_IndexValue].PrmDefPtr->LowerLimit;
		}
	}
    
	/*----------------------------------------------------------------------------------------------*/
	/* 根据数据是否有符号来判断数据是否有超出最大值和最小值的范畴									*/
	/*----------------------------------------------------------------------------------------------*/
	if( PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )
	{
		if( (LONG)SDO_WriteData.all > (LONG)max )
		{
			OD_SDOError(SDOSendNum,Data_UpLimit);
			return;
		}
		else if((LONG)SDO_WriteData.all < (LONG)min )
		{
			OD_SDOError(SDOSendNum,Data_DownLimit);
			return;
		}
		else
		{
		    ;
		}
	}
	else
	{
		if( SDO_WriteData.all > max)
		{
			OD_SDOError(SDOSendNum,Data_UpLimit);
			return;
		}
		else if(SDO_WriteData.all < min )
		{
			OD_SDOError(SDOSendNum,Data_DownLimit);
			return;
		}
		else
		{
		    ;
		}
	}
	
	/*----------------------------------------------------------------------------------------------*/
	/* 在更新RAM之前,先将目前RAM中的数据取出来,便于后面使用											*/
	/*----------------------------------------------------------------------------------------------*/
	Data = *(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr);
	if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.IsLong )
	{
		Data += (((ULONG)(*(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->RamPtr))) << 16);
	}
	/*----------------------------------------------------------------------------------------------*/
	/* 写入的数据类型为16位																			*/
	/*----------------------------------------------------------------------------------------------*/
	*(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr) = 	SDO_WriteData.word.LowWord;
    
	/*----------------------------------------------------------------------------------------------*/
	/* 写入的数据类型为32位																			*/
	/*----------------------------------------------------------------------------------------------*/	
	if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.IsLong )
	{
		*(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->RamPtr) = 	SDO_WriteData.word.HighWord;
    }
    
	/*----------------------------------------------------------------------------------------------*/
	/* 执行相关的操作功能码值更新操作																*/
	/*----------------------------------------------------------------------------------------------*/
	(*PnPrmTbl[OD_IndexValue].PrmDefPtr->FuncPtr)( 0, 0, 0 );
	/*----------------------------------------------------------------------------------------------*/
	/* 判断数据是否需要存储值Eeprom 中																*/
	/*----------------------------------------------------------------------------------------------*/
    if( ( Prm.ComSaveEeprom & 0x00F0 ) == 0x0010 )
    {
        if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.Place == PRMDEF_RAM_EEPROM)
        {
            if(Data != (ULONG)SDO_WriteData.all)
            {
                prm_def = (PRMDEF *)PnPrmTbl[OD_IndexValue].PrmDefPtr;
                KriAddEepromQueue(SDO_WriteData.all,prm_def,EEPQUEID_WRPRM_ROUND);
            }
        }
    }
    
	/*----------------------------------------------------------------------------------------------*/
	/* 判断功能是否需要重新上电,如需要重新上电,则显示相应的警告信息									*/
	/*----------------------------------------------------------------------------------------------*/
	if( PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.NeedReboot == PRMDEF_NEEDBOOT )
		KPI_WARNINGSET(WRN_BOOT);
    
	/*----------------------------------------------------------------------------------------------*/
	/* 数据写入成功,回复主站																		*/
	/*----------------------------------------------------------------------------------------------*/
	OD_SDOWriteOver(SDOSendNum);
}

/****************************************************************************************************/
/***************************************** End of the file ******************************************/
/****************************************************************************************************/













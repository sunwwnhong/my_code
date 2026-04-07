/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                     */
/*                                          2023 ~                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*                                                                                                  */
/*      EtherCAT08_2000Rw.c : 紧急报文代码                                                              */
/*                                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
#include "Main.h"


#ifdef CPU1
/****************************************************************************************************/
/*Function_Name: DT2XXX_Check                                                                       */
/*Description  : 对厂家定义的厂家参数进行检索处理                                                   */
/****************************************************************************************************/
USHORT DT20XX_Check(USHORT RegNo)
{
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

const UCHAR IndexLength[] = {0x8F,0x90,0x80,0x20,0x3F,0x09,0x33,0xFF,0xFF,
                             0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x20,0xFF,0xFF,
                             0x20,0x20,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};     /* 2000组长度       */

volatile UCHAR SubIndexV = 0;
volatile USHORT IndexV = 0;
/****************************************************************************************************/
/* Function Name:ReadObject0x2000                                                                   */
/****************************************************************************************************/
UINT8 DT2000R( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess )
{
USHORT RegNo;
USHORT *pu8Data = (USHORT*)pData;
USHORT KX;

    IndexV = index;
    SubIndexV = subindex;
    /*----------------------------------------------------------------------------------------------*/
    /*  非2000的对象字典则返回                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( (index & 0xF000)!= 0x2000 )
        return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;            /* 对象字典不存在               */
    if( subindex == 0x00 )
    {
        /*------------------------------------------------------------------------------------------*/
        /*  子索引数更新                                                                            */
        /*------------------------------------------------------------------------------------------*/
        *pu8Data = IndexLength[(index & 0x0FFF)];
        return 0;
    }
    else
    {
        RegNo = ((index & 0x000F) << 8) + (subindex - 1 );
        KX = DT20XX_Check( RegNo );

        if( KX == 0xFFFF )
            return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;        /* 对象字典不存在               */
    }

    if( (index & 0xFF00) == 0x2000 )             // 轴1
    {
        if(PnPrmTbl[KX].PrmDefPtr->Attr.IsLong == 0)
        {
            *pu8Data = (USHORT)(*(PnPrmTbl[KX].PrmDefPtr->RamPtr));
        }
        else
        {
            *pu8Data        = (USHORT)(*(PnPrmTbl[KX + 0].PrmDefPtr->RamPtr));
            *(pu8Data + 1)  = (USHORT)(*(PnPrmTbl[KX + 1].PrmDefPtr->RamPtr));
        }
    }
    return 0;
}

/****************************************************************************************************/
/*Function_Name: ODB2EXX_Check                                                                      */
/*Description  : 对厂家定义的厂家参数进行检索处理(Unxxx)                                            */
/****************************************************************************************************/
USHORT DT201X_Check(USHORT RegNo)
{
USHORT reg_no, low, high, mid;

    reg_no = (RegNo & 0x0FFF);
    low = 0;
    high = UnMonTblEntNum - 1;
    while(low <= high)
    {
        mid = (low + high) >> 1;
        if(reg_no < UnMonTbl[mid].UnNo)
            high = mid - 1;
        else if(reg_no > UnMonTbl[mid].UnNo)
            low = mid + 1;
        else
        {
            return mid;
        }
    }
    return 0xFFFF;
}

ULONG *UnMonTblAddress(USHORT Index, USHORT SubIndex)
{
    USHORT RegNo;
    USHORT KX;
    ULONG *pu8Data = NULL;
    MONDEF  *mondef_tmp;
    RegNo = ((Index & 0x000F) << 8) + (SubIndex - 1 );
    KX = DT201X_Check( RegNo );
    mondef_tmp = (MONDEF *)UnMonTbl[KX].MonDefPtr;

    //*pu8Data  = mondef_tmp->FuncPtr( mondef_tmp );  //PDO值更改一次，无法反复获取
    pu8Data  = mondef_tmp->Var.Pulong;              //只适用于直接返回数值的Un变量

    return pu8Data;
}


USHORT *UnPnTblAddress(USHORT Index, USHORT SubIndex)
{
    USHORT *pu8Data = NULL;
    USHORT RegNo;
    USHORT KX;
    RegNo = ((Index & 0x000F) << 8) + (SubIndex - 1 );
    KX = DT20XX_Check( RegNo );

    pu8Data = PnPrmTbl[KX].PrmDefPtr->RamPtr;
    return pu8Data;
}

/****************************************************************************************************/
/* Function Name:ReadObject0x2E00                                                                   */
/****************************************************************************************************/
UCHAR DT2010R( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess )
{
USHORT RegNo;
USHORT *pu8Data = (USHORT*)pData;
USHORT KX;
MONDEF  *mondef_tmp;
UCHAR SubIndexNum = 0;
    /*----------------------------------------------------------------------------------------------*/
    /*  非2010的对象字典则返回                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( (index & 0xF0F0)!= 0x2010 )
    {
        return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;            /* 对象字典不存在               */
    }
    if( subindex == 0x00 )
    {
        /*------------------------------------------------------------------------------------------*/
        /*  子索引数更新                                                                            */
        /*------------------------------------------------------------------------------------------*/
        switch( index )
        {
            case 2010:
                SubIndexNum = 0x8F;
                break;
            case 2011:
                SubIndexNum = 0x9F;
                break;
            case 2012:
                SubIndexNum = 0x9F;
                break;
            case 2013:
                SubIndexNum = 0x20;
                break;
            case 2014:
                SubIndexNum = 0x3F;
                break;
            case 2015:
                SubIndexNum = 0x12;
                break;
            case 2016:
                SubIndexNum = 0x3F;
                break;
            default:
                SubIndexNum = 0x3F;
                break;
        }

        /*------------------------------------------------------------------------------------------*/
        *pu8Data = SubIndexNum;
        /*------------------------------------------------------------------------------------------*/
        return 0;
    }
    else
    {
        RegNo = ((index & 0x000F) << 8) + (subindex - 1 );
        KX = DT201X_Check( RegNo );

        if( KX == 0xFFFF )
            return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;        /* 对象字典不存在               */
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 回复主机之前,先对该对象字典的数据类型进行判断处理,用来区分为16位或32位                       */
    /*----------------------------------------------------------------------------------------------*/
    if( (index & 0xFFF0) == 0x2010 )     // 轴1
    {
        mondef_tmp = (MONDEF *)UnMonTbl[KX].MonDefPtr;
        ULONG DataTmp  = mondef_tmp->FuncPtr( mondef_tmp );
        if(UnMonTbl[KX].MonDefPtr->IsLong == 0)
        {
            /*------------------------------------------------------------------------------------------*/
            /* 数据类型为 16 位                                                                           */
            /*------------------------------------------------------------------------------------------*/
            *pu8Data = (USHORT)DataTmp;
        }
        else
        {
            /*------------------------------------------------------------------------------------------*/
            /* 数据类型为 32 位                                                                           */
            /*------------------------------------------------------------------------------------------*/
            *pu8Data        = (USHORT)(DataTmp);
            *(pu8Data + 1)  = (USHORT)(DataTmp >> 16);
        }
    }
    return 0;
}

/****************************************************************************************************/
/* Function Name:Object0x60E1                                                                       */
/* Function Description: 对象字典0x60E1 相关变量更新                                                      */
/****************************************************************************************************/
UINT8 DT2000W( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess )
{
USHORT KX,RegNo;
ULONG max,min,Data;
PRMDEF  *prm_def;

USHORT DataTmpL = *(pData + 0);
USHORT DataTmpH = *(pData + 1);
ULONG WriteData = ULONGOF( DataTmpL, DataTmpH );

    /*----------------------------------------------------------------------------------------------*/
    /*  非2000的对象字典则返回                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( (index & 0xF000)!= 0x2000 )
        return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;            /* 对象字典不存在               */
    if( subindex == 0x00 )
    {
        /*------------------------------------------------------------------------------------------*/
        /*  子索引数只读,不能写                                                                     */
        /*------------------------------------------------------------------------------------------*/
        return ABORTIDX_READ_ONLY_ENTRY;
    }
    else
    {
        RegNo = ((index & 0x000F) << 8) + (subindex - 1 );

        KX = DT20XX_Check( RegNo );
        if( KX == 0xFFFF )
            return ABORTIDX_NO_OBJECT_DICTIONARY_IS_PRESENT;        /* 对象字典不存在               */
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 判断数据是否可写,只读数据不写入                                                              */
    /*----------------------------------------------------------------------------------------------*/
    if(PnPrmTbl[KX].PrmDefPtr->Attr.ReadOnly == 1)
    {
        return ABORTIDX_READ_ONLY_ENTRY;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 对写入的数据的大小值进行判断处理,先取出功能码的最大值和最小值                              */
    /*----------------------------------------------------------------------------------------------*/
    if(PnPrmTbl[KX].PrmDefPtr->Attr.IsLong )
    {
        max = (ULONG)( ((ULONG)(PnPrmTbl[KX + 1].PrmDefPtr->UpperLimit) << 16) |\
                        PnPrmTbl[KX].PrmDefPtr->UpperLimit );
        min = (ULONG)( ((ULONG)(PnPrmTbl[KX + 1].PrmDefPtr->LowerLimit) << 16) | \
                        PnPrmTbl[KX].PrmDefPtr->LowerLimit );
    }
    /*----------------------------------------------------------------------------------------------*/
    else
    {
        if( PnPrmTbl[KX].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )
        {
            max = (LONG)(SHORT)PnPrmTbl[KX].PrmDefPtr->UpperLimit;
            min = (LONG)(SHORT)PnPrmTbl[KX].PrmDefPtr->LowerLimit;
        }
        else
        {
            max = PnPrmTbl[KX].PrmDefPtr->UpperLimit;
            min = PnPrmTbl[KX].PrmDefPtr->LowerLimit;
        }
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 根据数据是否有符号来判断数据是否有超出最大值和最小值的范畴                                    */
    /*----------------------------------------------------------------------------------------------*/
    if( PnPrmTbl[KX].PrmDefPtr->Attr.Sign == DSPDEF_W_SIGN )
    {
        if( (LONG)WriteData > (LONG)max )
        {
            return ABORTIDX_VALUE_TOO_GREAT;
        }
        else if((LONG)WriteData < (LONG)min )
        {
            return ABORTIDX_VALUE_TOO_SMALL;
        }
        else
        {
            ;
        }
    }
    else
    {
        if( WriteData > max)
        {
            return ABORTIDX_VALUE_TOO_GREAT;
        }
        else if(WriteData < min )
        {
            return ABORTIDX_VALUE_TOO_SMALL;
        }
        else
        {
            ;
        }
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 在更新RAM之前,先将目前RAM中的数据取出来,便于后面使用                                           */
    /*----------------------------------------------------------------------------------------------*/
    Data = *(PnPrmTbl[KX].PrmDefPtr->RamPtr);
    if(PnPrmTbl[KX].PrmDefPtr->Attr.IsLong )
    {
        Data += ((ULONG)((*(PnPrmTbl[KX + 1].PrmDefPtr->RamPtr))) << 16);
    }

    if( (index & 0xFF00) == 0x2000 )             // 轴1
    {
        *(PnPrmTbl[KX].PrmDefPtr->RamPtr) = *pData;
        if( PnPrmTbl[KX].PrmDefPtr->Attr.IsLong )
        {
            *(PnPrmTbl[KX + 1].PrmDefPtr->RamPtr) = *(pData + 1);
        }

        /*----------------------------------------------------------------------------------------------*/
        /* 执行相关的操作功能码值更新操作                                                              */
        /*----------------------------------------------------------------------------------------------*/
        (*PnPrmTbl[KX].PrmDefPtr->FuncPtr)( 0, 0, 0 );

        /*----------------------------------------------------------------------------------------------*/
        /* 判断数据是否需要存储值Eeprom 中                                                              */
        /*----------------------------------------------------------------------------------------------*/
        if( ( Prm.ComSaveEeprom & 0x0F00 ) == 0x0100 )
        {
            if(PnPrmTbl[KX].PrmDefPtr->Attr.Place == PRMDEF_RAM_EEPROM)
            {
                if(Data != WriteData)
                {
                    prm_def = (PRMDEF *)PnPrmTbl[KX].PrmDefPtr;
                    KriAddEepromQueue(WriteData,prm_def,EEPQUEID_WRPRM_ROUND);
                }
            }
        }

        /*----------------------------------------------------------------------------------------------*/
        if( PnPrmTbl[KX].PrmDefPtr->Attr.NeedReboot == PRMDEF_NEEDBOOT )
        {
            KPI_WARNINGSET(WRN_BOOT);
        }
    }
    else
    {;}

    return 0;
}
#endif



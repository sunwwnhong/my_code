/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can04_PDOMngr.c : CANOpen PDO管理部分	 												    */
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"
#include "Can02_ODBDef.h"
#include "Can04_PDOMngr.h"

PDO_STRUCT PDO_Var;


/****************************************************************************************************/
/*																									*/
/*		PDO   初始化                     													        */
/*																									*/
/****************************************************************************************************/
void PDO_Dataclr(void)
{
    MlibResetSHORTMemory((void *)&PDO_Var, sizeof(PDO_Var));        /* 相关数据清零处理              */
    MlibResetSHORTMemory((void *)&OD_AttrVar, sizeof(OD_AttrVar));
}

/****************************************************************************************************/
/*																									*/
/*		PDO 映射                           													        */
/*																									*/
/*      8 7 6 5 4 3 2 1																			    */
/*      ------- --- ---																			    */
/*         ①     ②   ③																		        */
/*  ①:索引																		                    */
/*  ②:子索引																		                */
/*  ③:数据长度																		                */
/****************************************************************************************************/
void RPDO_Map(USHORT Address,UCHAR PDOGroup,UCHAR SubGroup)
{
USHORT   Index = ODDatArr[Address].word.HighWord;
UCHAR SubIndex = (UCHAR)ODDatArr[Address].byte.SecondByte;
UCHAR DataLengthSet = (UCHAR)ODDatArr[Address].byte.FirstByte;
UCHAR DataTmp = 0;
USHORT IndexValue;
    /*----------------------------------------------------------------------------------------------*/
    /* 索引地址为0时退出                                                                            */
	/*----------------------------------------------------------------------------------------------*/
    if(Index == 0x0000)
        return;
    /*----------------------------------------------------------------------------------------------*/
    IndexValue = ODB_Check(Index,SubIndex);
    PDO_Var.PDO_ErrFlag = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 判断映射对象是否存在                                                                         */
	/*----------------------------------------------------------------------------------------------*/
    if(IndexValue == OD_NULL)
    {
        if( SubIndex == 0 )
        {
            PDO_Var.PDO_ErrFlag = 1;
        }
        else
        {
            PDO_Var.PDO_ErrFlag = 8;
        }
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 判断数据长度是否匹配                                                                         */
	/*----------------------------------------------------------------------------------------------*/
    if( Index == 0x60FF )
    {
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            DataTmp = 1;
        }
        else
        {
            DataTmp = 2;
        }
    }
    else
    {
        DataTmp = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 7) & 0x03;
    }
   /*----------------------------------------------------------------------------------------------*/
    /* 映射数据长度检测                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    if((DataLengthSet == 0x08 && DataTmp == 0) || \
       (DataLengthSet == 0x10 && DataTmp == 1) || \
       (DataLengthSet == 0x20 && DataTmp == 2))
    {
        if(DataTmp == 0)
        {
            DataLengthSet = 1;
        }
        else
        {
            DataLengthSet = DataTmp * 2;
        }
    }
    else
    {
        PDO_Var.PDO_ErrFlag = 2;
        return;    
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 检查是否可以映射                                                                             */
	/*----------------------------------------------------------------------------------------------*/
    DataTmp = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 1) & 0x01;
    if(DataTmp == 0)
    {
        PDO_Var.PDO_ErrFlag = 3;
        return;         
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 检查PDO映射对象是否可写                                                                      */
	/*----------------------------------------------------------------------------------------------*/
    DataTmp = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 5) & 0x03;
    if(DataTmp == 0x00 || DataTmp == 0x03)
    {
        PDO_Var.PDO_ErrFlag = 4;
        return;     
    }
    /*----------------------------------------------------------------------------------------------*/
    /* RPDO 映射的数据长度是否超出8个检测                                                           */
    /*----------------------------------------------------------------------------------------------*/
    PDO_Var.RPDO_ByteNum[PDOGroup]  += DataLengthSet;           /* 字节总数计算                     */
    if( PDO_Var.RPDO_ByteNum[PDOGroup] > 8 )
    {
        PDO_Var.PDO_ErrFlag = 7;
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 索引值                                                                                       */
	/*----------------------------------------------------------------------------------------------*/
    PDO_Var.RPDO_Map[PDOGroup][SubGroup].PDO_Index = IndexValue;
    PDO_Var.RPDO_Map[PDOGroup][SubGroup].DataLgth  = DataLengthSet;
    
}
/****************************************************************************************************/
/*																									*/
/*		PDO 映射                           													        */
/*																									*/
/*      8 7 6 5 4 3 2 1																			    */
/*      ------- --- ---																			    */
/*         ①     ②   ③																			    */
/*  ①:索引																		                    */
/*  ②:子索引																		                */
/*  ③:数据长度																		                */
/****************************************************************************************************/
void TPDO_Map(USHORT Address,UCHAR PDOGroup,UCHAR SubGroup)
{
USHORT   Index = ODDatArr[Address].word.HighWord;                       /* 主索引值                 */
UCHAR SubIndex = (UCHAR)ODDatArr[Address].byte.SecondByte;              /* 子索引                   */
UCHAR DataLengthSet = (UCHAR)ODDatArr[Address].byte.FirstByte;          /* 数据长度                 */
UCHAR DataTmp = 0;
USHORT IndexValue;
    /*----------------------------------------------------------------------------------------------*/
    /* 索引地址为0时退出                                                                            */
	/*----------------------------------------------------------------------------------------------*/
    if(Index == 0x0000)
        return;
    /*----------------------------------------------------------------------------------------------*/
    IndexValue = ODB_Check(Index,SubIndex);
    PDO_Var.PDO_ErrFlag = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 判断映射对象是否存在                                                                         */
    /*----------------------------------------------------------------------------------------------*/
    if(IndexValue == OD_NULL)
    {
       if( SubIndex == 0 )
        {
            PDO_Var.PDO_ErrFlag = 1;
        }
        else
        {
            PDO_Var.PDO_ErrFlag = 8;
        }
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 检查是否可以映射                                                                             */
	/*----------------------------------------------------------------------------------------------*/
    DataTmp = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 1) & 0x01;
    if(DataTmp == 0)
    {
        PDO_Var.PDO_ErrFlag = 3;
        return;         
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 数据长度                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    if( Index == 0x60FF )
    {
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            DataLengthSet = 1;
        }
        else
        {
            DataLengthSet = 2;
        }
    }
    else
    {
        DataLengthSet = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 7) & 0x03;
    }    
    
    if(DataLengthSet == 0)
      DataLengthSet = 1;
    else
      DataLengthSet *= 2;
    /*----------------------------------------------------------------------------------------------*/
    /* 检查是否可以读                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    DataTmp = (UCHAR)(ObjectDictionaryAttriub[IndexValue][0] >> 5) & 0x03;
    if(DataTmp == 0x02)
    {
        PDO_Var.PDO_ErrFlag = 3;
        return;         
    }
     /*----------------------------------------------------------------------------------------------*/
    /* TPDO 映射的数据长度是否超出8个检测                                                           */
    /*----------------------------------------------------------------------------------------------*/
    PDO_Var.TPDO_ByteNum[PDOGroup]  += DataLengthSet;           /* 字节总数计算                     */
    if( PDO_Var.TPDO_ByteNum[PDOGroup] > 8 )
    {
        PDO_Var.PDO_ErrFlag = 7;
        return;
    }
	
   /*----------------------------------------------------------------------------------------------*/
	    /* 索引值                                                                                       */
    /*----------------------------------------------------------------------------------------------*/
    PDO_Var.TPDO_Map[PDOGroup][SubGroup].PDO_Index = IndexValue;
    PDO_Var.TPDO_Map[PDOGroup][SubGroup].DataLgth  = DataLengthSet;
    
}

/****************************************************************************************************/
/*																									*/
/*		PDO   映射相关寄存器初始化         													        */
/*																									*/
/****************************************************************************************************/
void PDO_MapUpdate(USHORT IndexValue)
{
    switch(IndexValue)
    {
        /*------------------------------------------------------------------------------------------*/

        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_COB_ID:
          
            ODDatArr[PDO1_Receive_COB_ID].all &= 0xFFFFFF80;
            ODDatArr[PDO1_Receive_COB_ID].all += Prm.Address;
          
            if((ODDatArr[PDO1_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[0] = 0;
            else
                PDO_Var.RPDO_En[0] = 1;
            PDO_Var.RPDO_CobId[0] = ( ODDatArr[PDO1_Receive_COB_ID].all) & 0x7FFF;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Type:
            PDO_Var.RPDO_Type[0] = ODDatArr[PDO1_Receive_Type].byte.FirstByte;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Map_Num:                              /* RPDO1长度                        */
                PDO_Var.RPDO_MapNum[0] = ODDatArr[PDO1_Receive_Map_Num].byte.FirstByte;
                if( PDO_Var.RPDO_MapNum[0] == 0 )
                {
                    PDO_Var.RPDO_ByteNum[0] = 0;                /* 清除字节长度和                   */
                    CanVar.NMTV.f.PDO1600Flg = 1;               /* 可写标志位                       */
                }
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Map1:                                  /* RPDO1 映射初始化                */
                RPDO_Map(PDO1_Receive_Map1,0,0);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Map2:                                  /* RPDO1 映射初始化                */
                RPDO_Map(PDO1_Receive_Map2,0,1);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Map3:                                  /* RPDO1 映射初始化                */
                RPDO_Map(PDO1_Receive_Map3,0,2);
            break;            
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Receive_Map4:                                  /* RPDO1 映射初始化                */
                RPDO_Map(PDO1_Receive_Map4,0,3);
            break;            
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_COB_ID:
          
            ODDatArr[PDO2_Receive_COB_ID].all &= 0xFFFFFF80;
            ODDatArr[PDO2_Receive_COB_ID].all += Prm.Address;
            
            if((ODDatArr[PDO2_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[1] = 0;
            else
                PDO_Var.RPDO_En[1] = 1;
            PDO_Var.RPDO_CobId[1] = ODDatArr[PDO2_Receive_COB_ID].all & 0x7FFF;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Type:
            PDO_Var.RPDO_Type[1] = ODDatArr[PDO2_Receive_Type].byte.FirstByte;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Map_Num:                               /* RPDO2长度                       */
                PDO_Var.RPDO_MapNum[1] = ODDatArr[PDO2_Receive_Map_Num].byte.FirstByte;
                if( PDO_Var.RPDO_MapNum[1] == 0 )
                {
                    PDO_Var.RPDO_ByteNum[1] = 0;                /* 清除字节长度和                   */
                    CanVar.NMTV.f.PDO1601Flg = 1;               /* 可写标志位                       */
                }
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Map1:                                  /* RPDO2 映射初始化                */
                RPDO_Map(PDO2_Receive_Map1,1,0);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Map2:                                  /* RPDO2 映射初始化                */
                RPDO_Map(PDO2_Receive_Map2,1,1);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Map3:                                  /* RPDO2 映射初始化                */
                RPDO_Map(PDO2_Receive_Map3,1,2);
            break;            
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Receive_Map4:                                  /* RPDO2 映射初始化                */
                RPDO_Map(PDO2_Receive_Map4,1,3);
            break;
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------------------------------------------------------*/

        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_COB_ID:
          
            ODDatArr[PDO3_Receive_COB_ID].all &= 0xFFFFFF80;
            ODDatArr[PDO3_Receive_COB_ID].all += Prm.Address;         
            if((ODDatArr[PDO3_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[2] = 0;
            else
                PDO_Var.RPDO_En[2] = 1;
            PDO_Var.RPDO_CobId[2] = ODDatArr[PDO3_Receive_COB_ID].all & 0x7FFF;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Type:
            PDO_Var.RPDO_Type[2] = ODDatArr[PDO3_Receive_Type].byte.FirstByte;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Map_Num:                               /* RPDO3长度                       */
            PDO_Var.RPDO_MapNum[2] = ODDatArr[PDO3_Receive_Map_Num].byte.FirstByte;
            if( PDO_Var.RPDO_MapNum[2] == 0 )
            {
                PDO_Var.RPDO_ByteNum[2] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1602Flg = 1;                   /* 可写标志位                       */
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Map1:                                  /* RPDO3 映射初始化                */
                RPDO_Map(PDO3_Receive_Map1,2,0);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Map2:                                  /* RPDO3 映射初始化                */
                RPDO_Map(PDO3_Receive_Map2,2,1);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Map3:                                  /* RPDO3 映射初始化                */
                RPDO_Map(PDO3_Receive_Map3,2,2);
            break;            
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Receive_Map4:                                  /* RPDO3 映射初始化                */
                RPDO_Map(PDO3_Receive_Map4,2,3);
            break;
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_COB_ID:
          
            ODDatArr[PDO4_Receive_COB_ID].all &= 0xFFFFFF80;
            ODDatArr[PDO4_Receive_COB_ID].all += Prm.Address;
          
            if((ODDatArr[PDO4_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[3] = 0;
            else
                PDO_Var.RPDO_En[3] = 1;
            PDO_Var.RPDO_CobId[3] = ODDatArr[PDO4_Receive_COB_ID].all & 0x7FFF;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Type:
            PDO_Var.RPDO_Type[3] = ODDatArr[PDO4_Receive_Type].byte.FirstByte;
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Map_Num:                               /* RPDO4长度                       */
            PDO_Var.RPDO_MapNum[3] = ODDatArr[PDO4_Receive_Map_Num].byte.FirstByte;
            if( PDO_Var.RPDO_MapNum[3] == 0 )
            {
                PDO_Var.RPDO_ByteNum[3] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1603Flg = 1;                   /* 可写标志位                       */
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Map1:                                  /* RPDO4 映射初始化                */
                RPDO_Map(PDO4_Receive_Map1,3,0);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Map2:                                  /* RPDO4 映射初始化                */
                RPDO_Map(PDO4_Receive_Map2,3,1);
            break;
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Map3:                                  /* RPDO4 映射初始化                */
                RPDO_Map(PDO4_Receive_Map3,3,2);
            break;            
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Receive_Map4:                                  /* RPDO4 映射初始化                */
                RPDO_Map(PDO4_Receive_Map4,3,3);
            break;
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------------------------------------------------------*/
        case PDO1_Trans_COB_ID:                                 /* TPDO ID                          */
                ODDatArr[PDO1_Trans_COB_ID].all &= 0xFFFFFF80;
                ODDatArr[PDO1_Trans_COB_ID].all += Prm.Address;   
                
                if((ODDatArr[PDO1_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                    PDO_Var.TPDO_En[0] = 0;
                else
                    PDO_Var.TPDO_En[0] = 1;
                PDO_Var.TPDO_ID[0] = ODDatArr[PDO1_Trans_COB_ID].all & 0x7FF;
            break;   
        case PDO1_Trans_Type:                                   /* TPDO 发送类型                    */
                PDO_Var.TPDO_TYPE[0] = ODDatArr[PDO1_Trans_Type].byte.FirstByte;
            break;
        case PDO1_Trans_Inhibt_Time:                            /* 禁止时间                         */
            PDO_Var.TPDO_PROBIT[0] = (ULONG)8 * ODDatArr[PDO1_Trans_Inhibt_Time].word.LowWord / 10;
            break;
        case PDO1_Trans_Event_Time:                             /* 事件时间                         */
            PDO_Var.TPDO_EVENTT[0] = (ULONG)8 * ODDatArr[PDO1_Trans_Event_Time].word.LowWord;
            break;
        case PDO1_Trans_Map_Num:                                /* TPDO1 映射数                     */
                PDO_Var.TPDO_MapNum[0] = ODDatArr[PDO1_Trans_Map_Num].byte.FirstByte;
            if( PDO_Var.TPDO_MapNum[0] == 0 )
            {
                PDO_Var.TPDO_ByteNum[0] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1A00Flg = 1;                   /* 可写标志位                       */
            }
            break;
        case PDO1_Trans_Map1:
                TPDO_Map(PDO1_Trans_Map1,0,0);                  /* TPDO1 映射初始化                 */
            break;
        case PDO1_Trans_Map2:
                TPDO_Map(PDO1_Trans_Map2,0,1);                  /* TPDO1 映射初始化                 */
            break;
        case PDO1_Trans_Map3:
                TPDO_Map(PDO1_Trans_Map3,0,2);                  /* TPDO1 映射初始化                 */
            break;
        case PDO1_Trans_Map4:
                TPDO_Map(PDO1_Trans_Map4,0,3);                  /* TPDO1 映射初始化                 */
            break; 
        /*------------------------------------------------------------------------------------------*/
        case PDO2_Trans_COB_ID:                                 /* TPDO ID                          */
          
                ODDatArr[PDO2_Trans_COB_ID].all &= 0xFFFFFF80;
                ODDatArr[PDO2_Trans_COB_ID].all += Prm.Address;            
          
                if((ODDatArr[PDO2_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                    PDO_Var.TPDO_En[1] = 0;
                else
                    PDO_Var.TPDO_En[1] = 1;
                PDO_Var.TPDO_ID[1] = ODDatArr[PDO2_Trans_COB_ID].all & 0x7FF;
            break;  
        case PDO2_Trans_Type:                                   /* TPDO 发送类型                    */
            PDO_Var.TPDO_TYPE[1] = ODDatArr[PDO2_Trans_Type].byte.FirstByte;
            break;
        case PDO2_Trans_Inhibt_Time:                            /* 禁止时间                         */
            PDO_Var.TPDO_PROBIT[1] = (ULONG)8 * ODDatArr[PDO2_Trans_Inhibt_Time].word.LowWord / 10;
            break;
        case PDO2_Trans_Event_Time:                             /* 事件时间                         */
            PDO_Var.TPDO_EVENTT[1] = (ULONG)8 * ODDatArr[PDO2_Trans_Event_Time].word.LowWord;
            break;        
        case PDO2_Trans_Map_Num:                                /* TPDO1 映射数                     */
                PDO_Var.TPDO_MapNum[1] = ODDatArr[PDO2_Trans_Map_Num].byte.FirstByte;
            if( PDO_Var.TPDO_MapNum[1] == 0 )
            {
                PDO_Var.TPDO_ByteNum[1] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1A01Flg = 1;                   /* 可写标志位                       */
            }
            break;
        case PDO2_Trans_Map1:
                TPDO_Map(PDO2_Trans_Map1,1,0);                  /* TPDO2 映射初始化                 */
            break;
        case PDO2_Trans_Map2:
                TPDO_Map(PDO2_Trans_Map2,1,1);                  /* TPDO2 映射初始化                 */
            break;
        case PDO2_Trans_Map3:
                TPDO_Map(PDO2_Trans_Map3,1,2);                  /* TPDO2 映射初始化                 */
            break;
        case PDO2_Trans_Map4:
                TPDO_Map(PDO2_Trans_Map4,1,3);                  /* TPDO2 映射初始化                 */
            break;             
        /*------------------------------------------------------------------------------------------*/
        case PDO3_Trans_COB_ID:                                 /* TPDO ID                          */
          
                ODDatArr[PDO3_Trans_COB_ID].all &= 0xFFFFFF80;
                ODDatArr[PDO3_Trans_COB_ID].all += Prm.Address;  
          
            if((ODDatArr[PDO3_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                PDO_Var.TPDO_En[2] = 0;
            else
                PDO_Var.TPDO_En[2] = 1;
            PDO_Var.TPDO_ID[2] = ODDatArr[PDO3_Trans_COB_ID].all & 0x7FF;
            break;
         case PDO3_Trans_Type:                                   /* TPDO 发送类型                    */
            PDO_Var.TPDO_TYPE[2] = ODDatArr[PDO3_Trans_Type].byte.FirstByte;
            break;
        case PDO3_Trans_Inhibt_Time:                            /* 禁止时间                         */
            PDO_Var.TPDO_PROBIT[2] = (ULONG)8 * ODDatArr[PDO3_Trans_Inhibt_Time].word.LowWord / 10;
            break;
        case PDO3_Trans_Event_Time:                             /* 事件时间                         */
            PDO_Var.TPDO_EVENTT[2] = (ULONG)8 * ODDatArr[PDO3_Trans_Event_Time].word.LowWord;
            break;
        case PDO3_Trans_Map_Num:                                /* TPDO3 映射数                     */
                PDO_Var.TPDO_MapNum[2] = ODDatArr[PDO3_Trans_Map_Num].byte.FirstByte;
            if( PDO_Var.TPDO_MapNum[2] == 0 )
            {
                PDO_Var.TPDO_ByteNum[2] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1A02Flg = 1;                   /* 可写标志位                       */
            }
            break;
        case PDO3_Trans_Map1:
                TPDO_Map(PDO3_Trans_Map1,2,0);                  /* TPDO3 映射初始化                 */
            break;
        case PDO3_Trans_Map2:
                TPDO_Map(PDO3_Trans_Map2,2,1);                  /* TPDO3 映射初始化                 */
            break;
        case PDO3_Trans_Map3:
                TPDO_Map(PDO3_Trans_Map3,2,2);                  /* TPDO3 映射初始化                 */
            break;
        case PDO3_Trans_Map4:
                TPDO_Map(PDO3_Trans_Map4,2,3);                  /* TPDO3 映射初始化                 */
            break;             
        /*------------------------------------------------------------------------------------------*/
        case PDO4_Trans_COB_ID:                                 /* TPDO ID                          */
          
                ODDatArr[PDO4_Trans_COB_ID].all &= 0xFFFFFF80;
                ODDatArr[PDO4_Trans_COB_ID].all += Prm.Address;  
          
                if((ODDatArr[PDO4_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                    PDO_Var.TPDO_En[3] = 0;
                else
                    PDO_Var.TPDO_En[3] = 1;
                PDO_Var.TPDO_ID[3] = ODDatArr[PDO4_Trans_COB_ID].all & 0x7FF;
            break;
         case PDO4_Trans_Type:                                   /* TPDO 发送类型                    */
            PDO_Var.TPDO_TYPE[3] = ODDatArr[PDO4_Trans_Type].byte.FirstByte;
            break;
        case PDO4_Trans_Inhibt_Time:                            /* 禁止时间                         */
            PDO_Var.TPDO_PROBIT[3] = (ULONG)8 * ODDatArr[PDO4_Trans_Inhibt_Time].word.LowWord / 10;
            break;
        case PDO4_Trans_Event_Time:                             /* 事件时间                         */
            PDO_Var.TPDO_EVENTT[3] = (ULONG)8 * ODDatArr[PDO4_Trans_Event_Time].word.LowWord;
            break;            
        case PDO4_Trans_Map_Num:                                /* TPDO4 映射数                     */
                PDO_Var.TPDO_MapNum[3] = ODDatArr[PDO4_Trans_Map_Num].byte.FirstByte;
            if( PDO_Var.TPDO_MapNum[3] == 0 )
            {
                PDO_Var.TPDO_ByteNum[3] = 0;                    /* 清除字节长度和                   */
                CanVar.NMTV.f.PDO1A03Flg = 1;                   /* 可写标志位                       */
            }
            break;
        case PDO4_Trans_Map1:
                TPDO_Map(PDO4_Trans_Map1,3,0);                  /* TPDO4 映射初始化                 */
            break;
        case PDO4_Trans_Map2:
                TPDO_Map(PDO4_Trans_Map2,3,1);                  /* TPDO4 映射初始化                 */
            break;
        case PDO4_Trans_Map3:
                TPDO_Map(PDO4_Trans_Map3,3,2);                  /* TPDO4 映射初始化                 */
            break;
        case PDO4_Trans_Map4:
                TPDO_Map(PDO4_Trans_Map4,3,3);                  /* TPDO4 映射初始化                 */
            break;             
        /*------------------------------------------------------------------------------------------*/    
        default:
            break;
    }
}
/****************************************************************************************************/
/*																									*/
/*		RPDO   接收PDO 映射处理    													                */
/*																									*/
/****************************************************************************************************/
void RPDO_MapDeal(UCHAR PDO_Num)
{
UCHAR i = 0;
CHAR Length = 8;
UCHAR WriteCnt = 0;
    for(i = 0;i< PDO_Var.RPDO_MapNum[PDO_Num];i++)
    {
        /*------------------------------------------------------------------------------------------*/
        Length -= PDO_Var.RPDO_Map[PDO_Num][i].DataLgth;
        /*------------------------------------------------------------------------------------------*/
        if(Length < 0 )
        {
            //写入数据异常
        }
        else
        {         
            /*--------------------------------------------------------------------------------------*/
            if(PDO_Var.RPDO_Map[PDO_Num][i].DataLgth == 0x01)
            {
                //写入的数据为1个字节
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte  = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
            }
            /*--------------------------------------------------------------------------------------*/
            else if(PDO_Var.RPDO_Map[PDO_Num][i].DataLgth == 0x02)
            {
                //写入的数据为2个字节
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte  = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.SecondByte = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
            }
            /*--------------------------------------------------------------------------------------*/
            else
            {
                //写入的数据为4个字节
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte  = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.SecondByte = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.ThirdByte  = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
                ODDatArr[PDO_Var.RPDO_Map[PDO_Num][i].PDO_Index].byte.FourthByte = \
                  PDO_Var.RPDO_SyncBuf[PDO_Num][WriteCnt++];
            }
        }
    }
}


/****************************************************************************************************/
/*																									*/
/*		RPDO   同步接收更新处理    													                */
/*																									*/
/****************************************************************************************************/
void RPDO_SynchDeal(void)
{
UCHAR i = 0;
    for(i = 0;i< 4;i++)
    {
        if(PDO_Var.RPDO_Synch[i] == 1)
        {
            //有数据需要同步更新处理
            RPDO_MapDeal(i);
            PDO_Var.RPDO_Synch[i] = 0;
        }
    }
}

/****************************************************************************************************/
/*																									*/
/*		RPDO   接收PDO 处理        													                */
/*																									*/
/****************************************************************************************************/
void RPDO_Deal(UCHAR PDO_Num)
{
    /*----------------------------------------------------------------------------------------------*/
    /* RPDO 未指定接收数,收到数据则异常,直接退出                                                    */
    if(PDO_Var.RPDO_MapNum[PDO_Num] == 0)
    {
        //驱动器报警
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    if(PDO_Var.RPDO_En[PDO_Num] == 0)                               /* 未开启,则直接退出            */
        return;
    /*----------------------------------------------------------------------------------------------*/
    /* 数据缓存处理                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
#ifdef CPU1
    PDO_Var.RPDO_SyncBuf[PDO_Num][0] = RxMsg.data[0];
    PDO_Var.RPDO_SyncBuf[PDO_Num][1] = RxMsg.data[1];
    PDO_Var.RPDO_SyncBuf[PDO_Num][2] = RxMsg.data[2];
    PDO_Var.RPDO_SyncBuf[PDO_Num][3] = RxMsg.data[3];
    PDO_Var.RPDO_SyncBuf[PDO_Num][4] = RxMsg.data[4];
    PDO_Var.RPDO_SyncBuf[PDO_Num][5] = RxMsg.data[5];
    PDO_Var.RPDO_SyncBuf[PDO_Num][6] = RxMsg.data[6];
    PDO_Var.RPDO_SyncBuf[PDO_Num][7] = RxMsg.data[7];
#endif

    /*----------------------------------------------------------------------------------------------*/
    
    if(PDO_Var.RPDO_Type[PDO_Num] < 254 )
    {
        //同步
        PDO_Var.RPDO_Synch[PDO_Num] = 1;
    }
    else
    {
        //异步,立即更新
        RPDO_MapDeal(PDO_Num);
    }

  //  CanVar.ConsumerTCnt = 0;     //魔仓掉线问题验证
}
/****************************************************************************************************/
/*																									*/
/*		RPDO   接收PDO1 处理        												                */
/*																									*/
/****************************************************************************************************/
void RPDO1(void)
{
    RPDO_Deal(0);
}

/****************************************************************************************************/
/*																									*/
/*		RPDO2   接收PDO 处理        													            */
/*																									*/
/****************************************************************************************************/
void RPDO2(void)
{
    RPDO_Deal(1);
}
/****************************************************************************************************/
/*																									*/
/*		RPDO3   接收PDO 处理        													            */
/*																									*/
/****************************************************************************************************/
void RPDO3(void)
{
    RPDO_Deal(2);
}

/****************************************************************************************************/
/*																									*/
/*		RPDO4   接收PDO 处理        													            */
/*																									*/
/****************************************************************************************************/
void RPDO4(void)
{
    RPDO_Deal(3);
}

/****************************************************************************************************/
/*																									*/
/*		TPDO   发送PDO 处理        													                */
/*																									*/
/****************************************************************************************************/
void TPDO_Deal(UCHAR PDO_Num)
{
UCHAR i = 0;
CHAR Length = 8;
UCHAR WriteCnt = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 禁止时间检测                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
#if 0
    if(PDO_Var.TPDO_PROBIT[PDO_Num] != 0)
    {
        if(++ PDO_Var.TPDO_PROBITCnt[PDO_Num] < PDO_Var.TPDO_PROBIT[PDO_Num])
            return;
        else
        {
            PDO_Var.TPDO_PROBITCnt[PDO_Num] = 0;
        }
    }
    else
    {
        PDO_Var.TPDO_PROBITCnt[PDO_Num] = 0;
    }
#endif
    /*----------------------------------------------------------------------------------------------*/
    /* 判断同步帧是否发送                                                                           */
    /*----------------------------------------------------------------------------------------------*/
    if(PDO_Var.TPDO_TRIGEn[PDO_Num])
    {
        PDO_Var.TPDO_TRIGEn[PDO_Num] = 0;
    }
    else
    {
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* RPDO 未指定接收数,收到数据则异常,直接退出                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if(PDO_Var.TPDO_En[PDO_Num] == 0)
    {
        //驱动器报警(是否有报警)
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------*/
    if(PDO_Var.PDOBuff_Cnt >= PDOBuff_Max)                    /* 条件1                              */
	{
        PDO_Var.PDOBuff_Cnt = 0;
	}
    PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].DataLength = 0; /* 发送数据长度清零(必须在条件1后清零)*/
    /*----------------------------------------------------------------------------------------------*/
    for(i = 0;i< PDO_Var.TPDO_MapNum[PDO_Num];i++)
    {
        /*------------------------------------------------------------------------------------------*/
        Length -= PDO_Var.TPDO_Map[PDO_Num][i].DataLgth;
        /*------------------------------------------------------------------------------------------*/
        if(Length < 0 )
        {
            //写入数据异常
        }
        else
        {    
            /*--------------------------------------------------------------------------------------*/
            if(PDO_Var.TPDO_Map[PDO_Num][i].DataLgth == 0x01)
            {
                //写入的数据为1个字节
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].DataLength += 1;
            }
            /*--------------------------------------------------------------------------------------*/
            else if(PDO_Var.TPDO_Map[PDO_Num][i].DataLgth == 0x02)
            {
                //写入的数据为2个字节
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.SecondByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].DataLength += 2;
            }
            /*--------------------------------------------------------------------------------------*/
            else
            {
                //写入的数据为4个字节
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.FirstByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.SecondByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.ThirdByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].Data[WriteCnt++] = ODDatArr[PDO_Var.TPDO_Map[PDO_Num][i].PDO_Index].byte.FourthByte;
                PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].DataLength += 4;
            }
        }
//        PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].ID = PDO_Var.TPDO_ID[PDO_Num];
//        PDO_Var.PDOBuff_Cnt += 1;
//        PDO_Var.PDOBuff_Remain ++;
    }
        PDO_Var.PDO_SendBuff[PDO_Var.PDOBuff_Cnt].ID = PDO_Var.TPDO_ID[PDO_Num];
        PDO_Var.PDOBuff_Cnt += 1;
        PDO_Var.PDOBuff_Remain ++;
}

//-------------------------------------------------------------------------------------------------
//
//		TPDO   数据传送至邮箱处理
//
//-------------------------------------------------------------------------------------------------
void TPDOData_MailBox(void)
{
    //---------------------------------------------------------------------------------------------
    // 数据发送
    //---------------------------------------------------------------------------------------------
    if(PDO_Var.PDOBuff_Remain > 0)
    {
        //-----------------------------------------------------------------------------------------
        // 邮箱有空闲,数据可以发送
        //-----------------------------------------------------------------------------------------
        if(PDO_Var.PDOSend_Cnt >= PDOBuff_Max)
            PDO_Var.PDOSend_Cnt = 0;
        //-----------------------------------------------------------------------------------------
        CAN1_Tx_Msg(PDO_Var.PDO_SendBuff[PDO_Var.PDOSend_Cnt].ID,   \
                    PDO_Var.PDO_SendBuff[PDO_Var.PDOSend_Cnt].DataLength,   \
                    PDO_Var.PDO_SendBuff[PDO_Var.PDOSend_Cnt].Data);
        //-----------------------------------------------------------------------------------------
        PDO_Var.PDOBuff_Remain --;                             // 每发送一帧则减 1
        PDO_Var.PDOSend_Cnt ++;                                // 发送的帧数进行累加
    }
}
/****************************************************************************************************/
/*																									*/
/*		TPDO   接收到同步帧或数据变化时数据发送 							                        */
/*																									*/
/****************************************************************************************************/
void TPDO_SynchVar(UCHAR TPDO_Num)
{
LONG DataTemp = 0;
UCHAR i = 0;
    //---------------------------------------------------------------------------------------------
    // 同步帧是否有? 同时数据是否有改变有则启动TPDO
    //---------------------------------------------------------------------------------------------
    if(PDO_Var.SYNCUpFlag)
    {
        //-----------------------------------------------------------------------------------------
		// 判断数据是否有变化,有变化则发送数据
        //-----------------------------------------------------------------------------------------
		for(i = 0;i < PDO_Var.TPDO_MapNum[TPDO_Num];i++)
		{
			 DataTemp += ODDatArr[PDO_Var.TPDO_Map[TPDO_Num][i].PDO_Index].all;
		}
		if(DataTemp != PDO_Var.TPDO_DataVarBuff[TPDO_Num])
		{
			PDO_Var.TPDO_DataVarBuff[TPDO_Num] = DataTemp;
			PDO_Var.TPDO_TRIGEn[TPDO_Num] = 1;
		}
	}
}
/****************************************************************************************************/
/*																									*/
/*		TPDO   若干同步报文后发送    										                            */
/*																									*/
/****************************************************************************************************/
void TPDO_SynchCnt(UCHAR TPDO_Num)
{
    if( PDO_Var.TPDO_TYPE[TPDO_Num] >=1 && PDO_Var.TPDO_TYPE[TPDO_Num] <= 240 )
    {
        if(PDO_Var.TPDO_SynchCnt[TPDO_Num] >= PDO_Var.TPDO_TYPE[TPDO_Num])
        {
            PDO_Var.TPDO_SynchCnt[TPDO_Num] = 0;
            PDO_Var.TPDO_TRIGEn[TPDO_Num]   = 1;
        }
    }
}
/****************************************************************************************************/
/*																									*/
/*		TPDO   异步定时发送    												                            */
/*																									*/
/****************************************************************************************************/
void TPDO_AsynchCnt(UCHAR TPDO_Num)
{
LONG DataTemp = 0;
UCHAR i = 0;
    PDO_Var.TPDO_Asynch[TPDO_Num] ++;
	/*----------------------------------------------------------------------------------------------*/
	/* 定时时间到																					    */
	/*----------------------------------------------------------------------------------------------*/
    if( PDO_Var.TPDO_EVENTT[TPDO_Num] == 0  )
    {
        PDO_Var.TPDO_TRIGEn[TPDO_Num] = 0;     
    }
    else
    {
        if( PDO_Var.TPDO_PROBIT[TPDO_Num] >= PDO_Var.TPDO_EVENTT[TPDO_Num] )
        {
            if( PDO_Var.TPDO_Asynch[TPDO_Num] > PDO_Var.TPDO_PROBIT[TPDO_Num] )
            {
//                PDO_Var.TPDO_Asynch[TPDO_Num] = 0;
                PDO_Var.TPDO_TRIGEn[TPDO_Num] = 1;    
            }
        }
        else
        {
            if(PDO_Var.TPDO_Asynch[TPDO_Num] > PDO_Var.TPDO_EVENTT[TPDO_Num])
            {
//                PDO_Var.TPDO_Asynch[TPDO_Num] = 0;
                PDO_Var.TPDO_TRIGEn[TPDO_Num] = 1;
            }
        }
    }
	/*----------------------------------------------------------------------------------------------*/
	/* 数据是否有变化( 禁止时间也对数据变化有效 )													            */
	/*----------------------------------------------------------------------------------------------*/
    PDO_Var.TPDO_AsyProbitcnt[ TPDO_Num ] ++;
    if( PDO_Var.TPDO_PROBIT[TPDO_Num] == 0 )
    {
        if( PDO_Var.TPDO_AsyProbitcnt[ TPDO_Num ] > 7 )                 //事件变化至少1ms才发送
        {
            for( i = 0;i < PDO_Var.TPDO_MapNum[TPDO_Num];i++ )
            {
                DataTemp += ODDatArr[PDO_Var.TPDO_Map[TPDO_Num][i].PDO_Index].all;
            }
            /*--------------------------------------------------------------------------------------*/
            /* 在异步模式下,需要发送一帧数据,不然,当数据没变化时,主站不知道从站数据 @2021.12.15                      */
            /*--------------------------------------------------------------------------------------*/
            if( ( DataTemp != PDO_Var.TPDO_DataVarBuff[TPDO_Num] ) || \
                            ( PDO_Var.TPDO_TRIGFlg[ TPDO_Num ] == 0) )
            {
                PDO_Var.TPDO_DataVarBuff[TPDO_Num]  = DataTemp;
                PDO_Var.TPDO_TRIGEn[TPDO_Num]       = 1;
                PDO_Var.TPDO_TRIGFlg[ TPDO_Num ]    = 1;
            }
        }
    }
    else
    {
        if( PDO_Var.TPDO_AsyProbitcnt[ TPDO_Num ] > PDO_Var.TPDO_PROBIT[TPDO_Num] )
        {
            /*--------------------------------------------------------------------------------------*/
            for( i = 0;i < PDO_Var.TPDO_MapNum[TPDO_Num];i++ )
            {
                DataTemp += ODDatArr[PDO_Var.TPDO_Map[TPDO_Num][i].PDO_Index].all;
            }    
            /*--------------------------------------------------------------------------------------*/
            if(DataTemp != PDO_Var.TPDO_DataVarBuff[TPDO_Num])
            {
                PDO_Var.TPDO_DataVarBuff[TPDO_Num] = DataTemp;
                PDO_Var.TPDO_TRIGEn[TPDO_Num] = 1;
            }
        }
    }
    /*----------------------------------------------------------------------------------------------*/    
    if(PDO_Var.TPDO_TRIGEn[TPDO_Num]==1)
    {
        PDO_Var.TPDO_Asynch[TPDO_Num]       = 0;
        PDO_Var.TPDO_AsyProbitcnt[TPDO_Num] = 0;
    }
    
}
/****************************************************************************************************/
/*																									*/
/*		TPDO   发送PDO数据发送检索    												                */
/*																									*/
/****************************************************************************************************/
void TPDO_DataSendChk(void)
{
UCHAR i;
    for(i = 0;i<4;i++)
    {
        if(PDO_Var.TPDO_En[i] == 1)
        {
            switch(PDO_Var.TPDO_TYPE[i])
            {
                /*----------------------------------------------------------------------------------*/
                case 0:     //同步
                    TPDO_SynchVar(i);
                    /*------------------------------------------------------------------------------*/
                    /* V1220 修复:由0切换至1~254同步事件时,如果0时的事件未清零,造成对其它           */
                    /*  同步事件的影响.                                                             */
                    /*------------------------------------------------------------------------------*/
					PDO_Var.TPDO_SynchCnt[i] = 0;
                    break;
                /*----------------------------------------------------------------------------------*/
                case 254:   //异步事件
                case 255:
                    TPDO_AsynchCnt(i);
					PDO_Var.TPDO_SynchCnt[i] = 0;
                  break;
                /*----------------------------------------------------------------------------------*/
                default:    //若干个同步事件
                    TPDO_SynchCnt(i);
                    break;
                /*----------------------------------------------------------------------------------*/
            }
        }
    }
    
    PDO_Var.SYNCUpFlag = 0;
}
/****************************************************************************************************/
/*																									*/
/*		同步发生器处理                 												                    */
/*		同步帧在预运行和运行阶段都需要发送															        */
/****************************************************************************************************/
void SYNC_Deal(void)
{
    //20221230
}

/****************************************************************************************************/
/*																									*/
/*		TPDO   发送PDO主函数        												                */
/*																									*/
/****************************************************************************************************/
void TPDO_DataSendDeal(void)
{ 
    /*----------------------------------------------------------------------------------------------*/
    /* 同步发生器(生产者)                                                                           */
    /*----------------------------------------------------------------------------------------------*/
    SYNC_Deal();
    /*----------------------------------------------------------------------------------------------*/
    if(!CanVar.NMTV.f.PDO_En)                           /* PDO 没有开启                             */
        return;
    /*----------------------------------------------------------------------------------------------*/
    TPDOData_MailBox();                                 /* 检查TPDO中是否有数据送至MailBox          */
    
    /*----------------------------------------------------------------------------------------------*/
    /* 发送条件检查(定时 or 同步)                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    TPDO_DataSendChk();
    //----------------     解决PDO数据跳动问题，使用中断保护@20240618 ---------------------------------
    Interrupt_disableMaster();
    /*----------------------------------------------------------------------------------------------*/
    /* 发送数据更新(定时或周期时间到时,发送数据更新)                                                */
    /*----------------------------------------------------------------------------------------------*/
    TPDO_Deal(0);                                       /*  发送PDO1                                */
    TPDO_Deal(1);                                       /*  发送PDO2                                */
    TPDO_Deal(2);                                       /*  发送PDO3                                */
    TPDO_Deal(3);                                       /*  发送PDO4                                */
    /*----------------------------------------------------------------------------------------------*/
    Interrupt_enableMaster();
}

/****************************************************************************************************/
/***************************************** End of the file ******************************************/
/****************************************************************************************************/

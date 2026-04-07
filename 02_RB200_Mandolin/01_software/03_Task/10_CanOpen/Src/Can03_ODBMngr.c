/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can3_ODBMngr.c : CANOpen 对象字典操作     												    */
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"

OD_OPERATION OD_V;
/*--------------------------------------------------------------------------------------------------*/
void CANOpen_SDODeal(void);                                /* SDO 报文处理                          */
void SDO_Recived(UCHAR AddIndex);            /* SDO 报文接收处理                      */
USHORT SDO_1XXXX(USHORT OD_Addr,UCHAR OD_SubIndex);        /* 对象字典0x1XXX 检索                   */
void SDO_2XXXX( void );									   /* 对象字典0x2XXX 的处理					*/
USHORT SDO_6XXXX(USHORT OD_Addr,UCHAR OD_SubIndex);        /* 对象字典0x6XXX 的处理                 */
void OD_Attriubte(USHORT Addr);                            /* 对象字典属性值                        */
USHORT OD_AttriubteCheck(USHORT Addr,UCHAR SubIndex);      /* 对象属性值监控                        */
void OD_DataRead(USHORT Addr,USHORT SubIndex,UCHAR SDOSendNum);            /* 对象字典数据读        */
void OD_SDOError(UCHAR AddIndex,ULONG ErrorCode);          /* SDO 错误处理                      */
void OD_DataWrite(USHORT OD_Addr,UCHAR SDOSendNum ,UCHAR TYPE);
void CANopen_SiteGuard(void);                              /* 主站节点保护                          */
void HeartBeat(void);                                      /* 心跳帧                                */
void EMCY(void);                                           /* 紧急报文(EMCY)                        */
UCHAR CANopen_SiteInitOK(void);                            /* ARM 初始化完成标志                    */
void Init_EMCY(void);                                      /* 网络初始化是否发送相关的数据报文      */
/*--------------------------------------------------------------------------------------------------*/


/****************************************************************************************************/
/*																									*/
/*		CanOpen对象字典管理初始化          															*/
/*																									*/
/****************************************************************************************************/
void ODBMange_Init(void)
{
        PDO_Dataclr();                                     /* 必须在此进行清零,在后面的话会有问题   */
        DB_InitialValue();                                 /* DS301 & DS402 对象字典默认值初始化    */
        /*------------------------------------------------------------------------------------------*/
        OD_V.SDO_580  = 0x580 + Prm.Address;               /* SDO 发送 ID                           */
        OD_V.PDO1_180 = 0x180 + Prm.Address;               /* PDO1 发送 ID                          */
        OD_V.PDO2_280 = 0x280 + Prm.Address;               /* PDO2 发送 ID                          */
        OD_V.PDO3_380 = 0x380 + Prm.Address;               /* PDO3 发送 ID                          */
        OD_V.PDO4_480 = 0x480 + Prm.Address;               /* PDO4 发送 ID                          */
        OD_V.Heart_Beat = 0x700+ Prm.Address;              /* 心跳报文                              */
        OD_V.EMCY_ID  = 0x80 + Prm.Address;                /* 紧急报文                              */

        ODDatArr[ OD_6063 ].all = 0;                        // @2023.11.23
        ODDatArr[ OD_6064 ].all = 0;
}

/****************************************************************************************************/
/*																									*/
/*		Can 接收报文处理                   															*/
/* Attention:   125us查询一次																		*/
/*																									*/
/****************************************************************************************************/
void Can_Deal(void)
{
    CANOpen_SDODeal();                                     /* CANopen SDO 报文处理                  */
    CANopen_SiteGuard();                                   /* CANopen 主站节点保护                  */
    HeartBeat();                                           /* CANopen 心跳                          */
    EMCY();                                                /* CANopen 紧急报文                      */
	Init_EMCY( );
}
/****************************************************************************************************/
/*																									*/
/*		CanOpen 紧急对象更新处理1(驱动器侧故障)   												    */
/*      在故障报警函数中调用      																	*/
/****************************************************************************************************/
void CanOpenEMCY_Update(USHORT Errcode)
{
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        ODDatArr[Error_Code].all = EmcyCode[Errcode][1];           /*  对象字典【603F】    */
    }
    else
    {
        ODDatArr[Error_Code].all = EmcyCode[Errcode][0];           /*  对象字典【603F】    */
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 停止状态不发送紧急报文                                                                       */
  	/*----------------------------------------------------------------------------------------------*/
  	if(CanVar.NMTV.f.NMTStatus == 0x04 )
	{
        return;
	}
    /*----------------------------------------------------------------------------------------------*/
    /* 判断是否有存储满                                                                             */
  	/*----------------------------------------------------------------------------------------------*/
    if(OD_V.EMCY_SavedCnt >= EMCYBuff_Num)
        OD_V.EMCY_SavedCnt = 0;
    if(OD_V.EMCY_Num >= 4)
        OD_V.EMCY_Num = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 查表获取相应的故障码                                                                         */
    /*----------------------------------------------------------------------------------------------*/
    OD_V.EMCY_Buff[OD_V.EMCY_SavedCnt].Errcode = EmcyCode[Errcode][0];  
    OD_V.EMCY_Buff[OD_V.EMCY_SavedCnt].Auxiliary = EmcyCode[Errcode][1];
    ODDatArr[OD_1003].all = OD_V.EMCY_Num;
    ODDatArr[OD_1003 + 1 + OD_V.EMCY_Num].all = ((ULONG)EmcyCode[Errcode][1] << 16) + EmcyCode[Errcode][0];
    /*----------------------------------------------------------------------------------------------*/
    if(OD_V.EMCY_En == 0)
    {
        OD_V.EMCY_Remain = 1;
        OD_V.EMCY_SendCnt = OD_V.EMCY_SavedCnt;
    }
    else
    {
        OD_V.EMCY_Remain ++;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 为下一次做准备                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    OD_V.EMCY_SavedCnt ++;
    
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 紧急对象报文(EMCY)        														    */
/*                                 																	*/
/****************************************************************************************************/
void EMCY(void)
{
uint16_t SendBuf[8];
	/*----------------------------------------------------------------------------------------------*/
	/* 在节点停止时不发送数据																		*/
	/*----------------------------------------------------------------------------------------------*/
	if(CanVar.NMTV.f.NMTStatus == 0x04)
    {
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    if(OD_V.EMCY_En == 0)
    {
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 紧急报文发送允许                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    if(OD_V.EMCY_Remain > 0)
    {
        /*------------------------------------------------------------------------------------------*/
        /* 数据可以发送                                                                             */
        if(OD_V.EMCY_SendCnt >= EMCYBuff_Num )
        {
            OD_V.EMCY_SendCnt = 0;
        }
#if 0
        SendBuf[1] = (OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Errcode >> 8) & 0x00FF;
        SendBuf[0] = OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Errcode & 0x00FF;
        SendBuf[2] = 0x81;
        SendBuf[3] = 0x00;
        SendBuf[4] = 0x00;
        SendBuf[5] = 0;
        SendBuf[6] = (OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Auxiliary >> 8) & 0x00FF;
        SendBuf[7] = OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Auxiliary & 0x00FF;
#else
        /*--------错误码为0xFF00，寄存器0x81，辅助字节0000XXXX--------------------------------------*/
        SendBuf[0] = 0x00;
        SendBuf[1] = 0xFF;
        SendBuf[2] = 0x81;
        SendBuf[3] = OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Auxiliary & 0x00FF;
        SendBuf[4] = (OD_V.EMCY_Buff[OD_V.EMCY_SendCnt].Auxiliary >> 8) & 0x00FF;
        SendBuf[5] = 0;
        SendBuf[6] = 0;
        SendBuf[7] = 0;
#endif
        OD_V.EMCY_SendCnt ++;   //地址递增
        OD_V.EMCY_Remain  --;   //发送完成一个则地址需要减1
        /*------------------------------------------------------------------------------------------*/
        CAN1_Tx_Msg(OD_V.EMCY_ID,8,SendBuf);                    /* 数据发送到CAN1中         */
    }
}        

/****************************************************************************************************/
/*																									*/
/*		CanOpen 紧急对象报文【CanOpen 网络复位时紧急报文发送】         							    */
/*                                 																	*/
/****************************************************************************************************/
void Init_EMCY(void)
{
uint16_t SendBuf[8];

    /*----------------------------------------------------------------------------------------------*/
    /* 1.判断初始化时是否有故障,有则发送                                                            */
    /*----------------------------------------------------------------------------------------------*/
    if( CanVar.NMTV.f.NETInitEmcy == 0 )
    {
        return;
    }

    /*--------------------错误码为0xFF00，寄存器0x81，辅助字节0000XXXX------------------------------*/
    SendBuf[0] = 0x00;
    SendBuf[1] = 0xFF;
    SendBuf[2] = 0x81;
    SendBuf[3] = 0x00;
    SendBuf[4] = OD_V.EMCY_Buff[OD_V.EMCY_SavedCnt - 1 ].Auxiliary & 0x00FF;
    SendBuf[5] = (OD_V.EMCY_Buff[OD_V.EMCY_SavedCnt - 1].Auxiliary >> 8) & 0x00FF;
    SendBuf[6] = 0;
    SendBuf[7] = 0;
    /*----------------------------------------------------------------------------------------------*/
    CAN1_Tx_Msg(OD_V.EMCY_ID,8,SendBuf);                        /* 数据发送到CAN1中         */
    
    /*----------------------------------------------------------------------------------------------*/
    /* 清除相关标志位                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    CanVar.NMTV.f.NETInitEmcy = 0;
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 紧急对象报文【CanOpen 网络复位时紧急报文发送】         							            */
/*                                 																	*/
/****************************************************************************************************/
void EMCY_Clear(void)
{
uint16_t SendBuf[8];

    /*----------------------------------------------------------------------------------------------*/
    /* 1.判断初始化时是否有故障,有则发送                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if( CanVar.NMTV.f.ErrReset == 0 )
    {
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 判断故障是否清除完成                                                                              */
    /*----------------------------------------------------------------------------------------------*/
    if( Alm.f.AlmFlag == 1 )
    {
        CanVar.NMTV.f.ErrReset = 0;
        return;
    }

    /*--------------------错误码为0xFF00，寄存器0x81，辅助字节0000XXXX------------------------------*/
    SendBuf[0] = 0x00;
    SendBuf[1] = 0x00;
    SendBuf[2] = 0x00;
    SendBuf[3] = 0x00;
    SendBuf[4] = 0x00;
    SendBuf[5] = 0x00;
    SendBuf[6] = 0x00;
    SendBuf[7] = 0x00;
    /*----------------------------------------------------------------------------------------------*/
    CAN1_Tx_Msg(OD_V.EMCY_ID,8,SendBuf);                                /* 数据发送到CAN1中         */
    
    /*----------------------------------------------------------------------------------------------*/
    /* 清除相关标志位                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    CanVar.NMTV.f.ErrReset = 0;
    
}


//*************************************************************************************************
//
//		CanOpen 的SDO报文处理(接收 & 发送)
//
//*************************************************************************************************
void CANOpen_SDODeal(void)
{
    if(CanVar.SDORemain > 0)
    {
        //-----------------------------------------------------------------------------------------
        // 当前有空闲的邮箱,可以发送数据
        //-----------------------------------------------------------------------------------------
        CanVar.SDORemain --;                               // 每处理一组报文,则计数器减少一个
        if(CanVar.SDOSendNum >= SDOBuff_Max)
        {
            CanVar.SDOSendNum = 0;
        }
        //-----------------------------------------------------------------------------------------
        // SDO 报文接收处理
        //-----------------------------------------------------------------------------------------
        SDO_Recived( CanVar.SDOSendNum );                  // SDO 报文接收处理
        //-----------------------------------------------------------------------------------------
        // 处理完成一帧后,相应的周期寄存器值需要+1
        //-----------------------------------------------------------------------------------------
        CanVar.SDOSendNum ++;
    }
}

/****************************************************************************************************/
/*																									*/
/*		对象字典检索                   															    */
/*      SDO 读操作不高于4 个字节的对象报文时，采用加速方式    										*/
/*																									*/
/****************************************************************************************************/
USHORT ODB_Check(USHORT Index,UCHAR SubIndex)
{
USHORT kx = (Index >> 8) & 0xF0;
USHORT OD_IndexValue = 0;
    switch(kx)
    {
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典组 0x1XXXX 组检索                                                                */
	  	/*------------------------------------------------------------------------------------------*/
        case 0x10:
            OD_IndexValue = SDO_1XXXX(Index,SubIndex);
            break;
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典组 0x6XXXX 组检索                                                                */  
		/*------------------------------------------------------------------------------------------*/
        case 0x60:
            OD_IndexValue = SDO_6XXXX(Index,SubIndex);
            break;
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典组 不存在,报错                                                                   */
		/*------------------------------------------------------------------------------------------*/
        default:
            OD_IndexValue = 0xFFFF;
            break;
    }
    return OD_IndexValue;
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的SDO报文接收处理     															    */
/*      SDO 读操作不高于4 个字节的对象报文时，采用加速方式    										*/
/*																									*/
/****************************************************************************************************/
void SDO_Recived( UCHAR SDOSendNum )
{
USHORT OD_IndexValue = 0xFFFF;
VUSHORT OD_Addr = (USHORT)(((USHORT)CanVar.SDO[SDOSendNum].OD[1]) << 8) + \
                           (USHORT)CanVar.SDO[SDOSendNum].OD[0];                        /* 对象字典 */
USHORT OD_SubIndex = CanVar.SDO[SDOSendNum].Index;                                      /* 子索引   */
UCHAR FLAG = 0;
UCHAR PDOMapType = 0;
USHORT PDOMap_Addr = 0;
UCHAR PDOMapSubIndex = 0;
	/*----------------------------------------------------------------------------------------------*/
	/* 为了软件上使用的方便,SDO部分进行数据的分类处理,即驱动器功能码部分和CanOpen的301和402协议部分                     */
	/* 即软件上使用0x2XXX的部分进行专门的特殊处理													            */
	/*----------------------------------------------------------------------------------------------*/
    if((OD_Addr & 0xF000) == 0x2000)        // @20230803
    {
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            if( OD_Addr == 0x2004 )
            {
                if( OD_SubIndex == 0x0A )       // 电压 1V
                {
                    OD_V.SendBuf[0] = 0x4B;
                    OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
                    OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
                    OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
                    OD_V.SendBuf[4] = BinK.UnDcVolt & 0x00FF;
                    OD_V.SendBuf[5] = 0x00;
                    OD_V.SendBuf[6] = 0x00;
                    OD_V.SendBuf[7] = 0x00;
                    OD_V.SendLength = 8;
                    CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);
                    return;
                }
                else if( OD_SubIndex == 0x0B )  // 温度 1℃
                {
                    OD_V.SendBuf[0] = 0x4B;
                    OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
                    OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
                    OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
                    OD_V.SendBuf[4] = (CoutV.UnHeatSinkTemp / 10) & 0x00FF;
                    OD_V.SendBuf[5] = 0x00;
                    OD_V.SendBuf[6] = 0x00;
                    OD_V.SendBuf[7] = 0x00;
                    OD_V.SendLength = 8;
                    CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);
                    return;
                }
                else
                {
                    ;
                }
            }
        }
    }
	if((OD_Addr & 0xF000) == 0x2000)
	{
	  	/*------------------------------------------------------------------------------------------*/
		/* 对象字典检索处理 0x2XXXX																	*/
	  	/*------------------------------------------------------------------------------------------*/
        if( OD_SubIndex == 0 ) 
        {
            switch(CanVar.SDO[SDOSendNum].FCmd & 0xFF)
            {
                case 0x40:
                    /*------------------------------------------------------------------------------*/
                    /* 子索引为00，按读1个字节方式处理，且不能写									*/
                    /*------------------------------------------------------------------------------*/
                    OD_V.SendBuf[0] = 0x4F;
                    OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
                    OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
                    OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
                    OD_V.SendBuf[4] = 0xFF;
                    OD_V.SendLength = 5;
                    CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);
                    break;
                default:
                    OD_SDOError(SDOSendNum,WRITE_RO_OBJECT);    /* 故障:对只读参数进行写操作  */
            }
            return;
        }
		else
		{
		  	/*--------------------------------------------------------------------------------------*/
		  	/* 根据相关的需求,所有的厂家参数 0x2XXXX的子索引均需要+1访问,相应底层需要-1进行处理		*/
		  	/*--------------------------------------------------------------------------------------*/
		  	OD_SubIndex -= 1;
            if( ( OD_Addr & 0xFF00 ) == 0x2E00 )
            {
                OD_IndexValue = ODB2EXX_Check(OD_Addr,OD_SubIndex);
            }
            else
            {
                OD_IndexValue = ODB2XXX_Check(OD_Addr,OD_SubIndex);
            }
            
		}
	  	/*------------------------------------------------------------------------------------------*/
	  	if( OD_IndexValue == OD_NULL )
		{
        	/*--------------------------------------------------------------------------------------*/
        	/* 对象字典查找不到                                                                     */
	  		/*--------------------------------------------------------------------------------------*/
        	OD_SDOError(SDOSendNum,OD_NOT_FOUNT);      /* 故障:对象字典不存在               */
        	return;		
		}
		else
		{
		  	/*--------------------------------------------------------------------------------------*/
			/* 判断读取的数据是否是低16位或者32位数据的低16位,不是则报警							*/
			/*--------------------------------------------------------------------------------------*/
            if((OD_Addr & 0xFFF0) == 0x2000)
            {
				if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.WordOrder != 0 )
				{
	  				OD_SDOError(SDOSendNum,WRITE_AD_Error);
					return;
				}
			}
        	/*--------------------------------------------------------------------------------------*/
        	/* 对象字典可以查询到,则进行读写处理                                                    */
	  		/*--------------------------------------------------------------------------------------*/		
			switch(CanVar.SDO[SDOSendNum].FCmd & 0xFF)
			{
			  	/*----------------------------------------------------------------------------------*/
			  	/* 数据读功能																		*/
			  	/*----------------------------------------------------------------------------------*/
				case 0x40:
                    if((OD_Addr & 0xFF00) == 0x2E00)
                    {
                        ODB2EXX_ReadDeal(OD_IndexValue,SDOSendNum);
                    }
                    else
                    {
                        ODB2XXX_ReadDeal(OD_IndexValue,SDOSendNum);
                    }
					CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);
					break;
				/*----------------------------------------------------------------------------------*/
				/* 数据写功能(16位数据写入)															*/
				/*----------------------------------------------------------------------------------*/
        		case 0x2B:                                     /* 向对象字典写入2个字节(16位)的数据 */
        		    if( ( OD_Addr & 0xFF00 ) == 0x2E00 )
        		    {
        		        OD_SDOError(SDOSendNum,OD_PDO_Read_ONLY);
        		    }
        		    else
        		    {
        		        if( CAN_EXFUNC0_10_DIS )
        		        {
        		            ODB2XXX_WriteDeal(OD_IndexValue,SDOSendNum ,0);
        		        }
        		    }
            		break;
				/*----------------------------------------------------------------------------------*/
				/* 数据写功能(32位数据写入)															*/
				/*----------------------------------------------------------------------------------*/					
        		case 0x23:                                     /* 向对象字典写入4个字节(32位)的数据 */
                    if( ( OD_Addr & 0xFF00 ) == 0x2E00 )
                    {
                        OD_SDOError(SDOSendNum,OD_PDO_Read_ONLY);
                    }
                    else
                    {
                        if( CAN_EXFUNC0_10_DIS )
                        {
                            ODB2XXX_WriteDeal(OD_IndexValue,SDOSendNum ,1);
                        }
                    }
            		break;
				/*----------------------------------------------------------------------------------*/
				/* 其它命令码,报错处理																*/
				/*----------------------------------------------------------------------------------*/					
        		default:
            		OD_SDOError(SDOSendNum,OD_CONTROL_WORD_INVALID);    /* 故障:控制字无效  */
			}
		}
	  	return;
	}
    /*----------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典检索       0x1XXX & 0x6XXX                                                           */
	/*----------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------*/
    OD_IndexValue = ODB_Check(OD_Addr,OD_SubIndex);
    
    /*----------------------------------------------------------------------------------------------*/
    if(OD_IndexValue == OD_NULL)
    {
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典查找不到                                                                         */
	  	/*------------------------------------------------------------------------------------------*/
        OD_SDOError(SDOSendNum,OD_NOT_FOUNT);          /* 故障:对象字典不存在               */
        return;
    }
    else if( OD_IndexValue == OD_IndexNULL)
    {
        /*------------------------------------------------------------------------------------------*/
        /* 对象字典查找不到                                                                         */
	  	/*------------------------------------------------------------------------------------------*/
        OD_SDOError(SDOSendNum,SUBINDEX_NOT_EXIST);          /* 故障:对象字典不存在               */
        return;    
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 1600 和 1A00 写入异常处理(160X,1A0X只支持32位写入)                                           */
    /*----------------------------------------------------------------------------------------------*/
    else if( ( (( OD_Addr >= 0x1A00 && OD_Addr <= 0x1A03 ) && OD_SubIndex >=1) || \
                (( OD_Addr >= 0x1600 && OD_Addr <= 0x1603 ) && OD_SubIndex >=1) ) && \
                 CanVar.SDO[SDOSendNum].FCmd == 0x23 )
    {
        /*------------------------------------------------------------------------------------------*/
        if( OD_Addr == 0x1600 && CanVar.NMTV.f.PDO1600Flg == 0 ) FLAG = 1;
        else if( OD_Addr == 0x1601 && CanVar.NMTV.f.PDO1601Flg == 0 ) FLAG = 1;
        else if( OD_Addr == 0x1602 && CanVar.NMTV.f.PDO1602Flg == 0 ) FLAG = 1;
        else if( OD_Addr == 0x1603 && CanVar.NMTV.f.PDO1603Flg == 0 ) FLAG = 1;
        else if( OD_Addr == 0x1A00 && CanVar.NMTV.f.PDO1A00Flg == 0 ) FLAG = 1;        
        else if( OD_Addr == 0x1A01 && CanVar.NMTV.f.PDO1A01Flg == 0 ) FLAG = 1;        
        else if( OD_Addr == 0x1A02 && CanVar.NMTV.f.PDO1A02Flg == 0 ) FLAG = 1;        
        else if( OD_Addr == 0x1A03 && CanVar.NMTV.f.PDO1A03Flg == 0 ) FLAG = 1;
        else FLAG = 0;
        if( FLAG == 1 )
        {
            OD_SDOError(SDOSendNum,OD_NOT_ACCESS);             /* 故障:对象字典类型不对             */
            return;        
        }
        /*------------------------------------------------------------------------------------------*/
        PDOMapType = CanVar.SDO[SDOSendNum].SDOData & 0x00FF;
        if( PDOMapType == 0x08 || PDOMapType == 0x10 || PDOMapType == 0x20 )
        {
            FLAG = 0;
        }
        else
        {
            FLAG = 1;
        }
        if( FLAG == 1 )
        {
            OD_SDOError(SDOSendNum,OD_DATA_LENGTH_ERROR);      /* 故障:对象字典类型不对             */
            return;        
        }
        /*------------------------------------------------------------------------------------------*/
        /* 检测映射的对象字典是否存在                                                               */
        /*------------------------------------------------------------------------------------------*/
        PDOMap_Addr     = (USHORT)(CanVar.SDO[SDOSendNum].SDOData >> 16);
        PDOMapSubIndex  = (UCHAR)((CanVar.SDO[SDOSendNum].SDOData >> 8) & 0x0000000F );
        if( OD_NULL == ODB_Check(PDOMap_Addr,PDOMapSubIndex) )
        {
            OD_SDOError(SDOSendNum,OD_NOT_FOUNT);              /* 故障:对象字典不存在               */
            return;        
        }
        /*------------------------------------------------------------------------------------------*/
        /* 只读属性不能映射到写寄存器                                                               */
        /*------------------------------------------------------------------------------------------*/
        if(( OD_Addr >= 0x1600 && OD_Addr <= 0x1603 ) && OD_SubIndex >=1 )
        {
            if( OD_AttrVar.Access == 0 )
            {
                OD_SDOError(SDOSendNum,OD_PDO_MAP_INVALID);    /* 故障:对象字典非法                 */
                return;    
            }
        }
        /*------------------------------------------------------------------------------------------*/
        OD_IndexValue = ODB_Check(OD_Addr,OD_SubIndex);
    }
    else if(OD_IndexValue == OD_IndexNULL)
    {
        /*------------------------------------------------------------------------------------------*/
        /* 子索引不存在                                                                             */
	  	/*------------------------------------------------------------------------------------------*/
        OD_SDOError(SDOSendNum,SUBINDEX_NOT_EXIST);    /* 故障:对象字典不存在               */
        return;    
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典存在,进行相应的处理                                                                  */
    /* 无错误时进行如下处理                                                                         */
    /*----------------------------------------------------------------------------------------------*/
    switch(CanVar.SDO[SDOSendNum].FCmd & 0xFF)
    {
        /*------------------------------------------------------------------------------------------*/
        case 0x40:                                             /* 数据读                            */
            OD_DataRead(OD_Addr,OD_IndexValue,SDOSendNum);
                                                               /* 数据应答                          */
            CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);
            break;
        /*------------------------------------------------------------------------------------------*/
        case 0x2F:                                             /* 向对象字典写入1个字节的数据       */
            OD_DataWrite(OD_IndexValue,SDOSendNum ,0);
            break;
        case 0x2B:                                             /* 向对象字典写入2个字节的数据       */
            OD_DataWrite(OD_IndexValue,SDOSendNum ,1);
            break;
        case 0x23:                                             /* 向对象字典写入4个字节的数据       */
            OD_DataWrite(OD_IndexValue,SDOSendNum ,2);
            break;
        default:
            OD_SDOError(SDOSendNum,OD_CONTROL_WORD_INVALID);    /* 故障:控制字无效          */
            break;
        /*------------------------------------------------------------------------------------------*/
    }
    return;
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的1XXXX对象字典检索处理															    */
/*                                                          										*/
/****************************************************************************************************/
USHORT SDO_1XXXX( USHORT OD_Addr,UCHAR SubIndex )
{
USHORT ODAddr_IndexValue = OD_NULL;
USHORT ODAddr_Index = OD_Addr & 0x000F;
    switch(OD_Addr & 0x0FF0)
    {
        case 0x0000:    //0x100X
            ODAddr_IndexValue = ADDR100X[ODAddr_Index];
            break;
        case 0x0010:    //0x101X
            ODAddr_IndexValue = ADDR101X[ODAddr_Index];
            break;
        case 0x0020:    //0x102X
            ODAddr_IndexValue = ADDR102X[ODAddr_Index];
            break;
        case 0x0200:    //0x120X            
            ODAddr_IndexValue = ADDR120X[ODAddr_Index];
            break;
        case 0x0400:    //0x140X            
            ODAddr_IndexValue = ADDR140X[ODAddr_Index];
            break;
        case 0x0600:    //0x160X            
            ODAddr_IndexValue = ADDR160X[ODAddr_Index];
            break;
        case 0x0800:    //0x180X            
            ODAddr_IndexValue = ADDR180X[ODAddr_Index];
            break;
        case 0x0A00:    //0x1A0X            
            ODAddr_IndexValue = ADDR1A0X[ODAddr_Index];
            break;
        default:
            ODAddr_IndexValue = OD_NULL;                       /* 对象字典不存在                    */
            break;
    }
    /*----------------------------------------------------------------------------------------------*/
    if( OD_Addr == 0x1018 )
    {
        if( SubIndex >= 4 )
        {
            return OD_IndexNULL;
        }
    }
    else if( OD_Addr == 0x1010 )
    {
        if( SubIndex >= 2 )
        {
            return OD_IndexNULL;
        }    
    }
    else if( OD_Addr == 0x1011 )
    {
        if( SubIndex >= 2 )
        {
            return OD_IndexNULL;
        }    
    }
    else if( OD_Addr == 0x1016 )
    {
        if( SubIndex >= 5 )
        {
            return OD_IndexNULL;
        }    
    }
    else if( OD_Addr == 0x1029 )
    {
        if( SubIndex >= 1 )
        {
            return OD_IndexNULL;
        }    
    }
    else
    {;}
    /*----------------------------------------------------------------------------------------------*/
    if( ODAddr_IndexValue  == OD_NULL)
    {
        return ODAddr_IndexValue;                              /* 对象字典不存在,返回               */
    }
    /*----------------------------------------------------------------------------------------------*/
    else
    {
        return OD_AttriubteCheck( ODAddr_IndexValue,SubIndex); /* 属性值的获取                      */    
    }
}


/****************************************************************************************************/
/*																									*/
/*		CanOpen 的 2XXXX对象字典检索处理														    */
/*                                                          										*/
/****************************************************************************************************/
void SDO_2XXXX( void )
{
	
}


/****************************************************************************************************/
/*																									*/
/*		CanOpen 的6XXXX对象字典检索处理															    */
/*                                                          										*/
/****************************************************************************************************/
USHORT SDO_6XXXX(USHORT OD_Addr, UCHAR SubIndex )
{
USHORT ODAddr_IndexValue = 0xFFFF;
USHORT ODAddr_Index = OD_Addr & 0x000F;
    switch(OD_Addr & 0x0FF0)
    {
        case 0x0030:    //0x603X
            ODAddr_IndexValue = ADDR603X[ODAddr_Index];
            break;
        case 0x0040:    //0x604X
            ODAddr_IndexValue = ADDR604X[ODAddr_Index];
            break;
        case 0x0050:    //0x605X
            ODAddr_IndexValue = ADDR605X[ODAddr_Index];
            break;            
        case 0x0060:    //0x606X
            ODAddr_IndexValue = ADDR606X[ODAddr_Index];
            break;            
        case 0x0070:    //0x607X
            ODAddr_IndexValue = ADDR607X[ODAddr_Index];
            break;            
        case 0x0080:    //0x608X
            ODAddr_IndexValue = ADDR608X[ODAddr_Index];
            break;            
        case 0x0090:    //0x609X
            ODAddr_IndexValue = ADDR609X[ODAddr_Index];
            break;
        case 0x00A0:    //0x60AX
            ODAddr_IndexValue = ADDR60AX[ODAddr_Index];
            break;
        case 0x00B0:    //0x60BX
            ODAddr_IndexValue = ADDR60BX[ODAddr_Index];
            break;
        case 0x00C0:    //0x60CX
            ODAddr_IndexValue = ADDR60CX[ODAddr_Index];
            break;
        case 0x00D0:    //0x60DX
            ODAddr_IndexValue = ADDR60DX[ODAddr_Index];
            break;            
        case 0x00E0:    //0x60EX
            ODAddr_IndexValue = ADDR60EX[ODAddr_Index];
            break;
        case 0x00F0:    //0x60FX
            ODAddr_IndexValue = ADDR60FX[ODAddr_Index];
            break;
        case 0x0100:    //0x610X
            ODAddr_IndexValue = ADDR610X[ODAddr_Index];
            break;
        case 0x0500:
            ODAddr_IndexValue = ADDR650X[ODAddr_Index];
            break;
        default:
            ODAddr_IndexValue = OD_NULL;                       /* 对象字典不存在                    */
            break;
    }
    /*----------------------------------------------------------------------------------------------*/
    if( ODAddr_IndexValue == OD_NULL )
    {
        return ODAddr_IndexValue;                              /* 对象字典不存在,直接返回           */
    }
    /*----------------------------------------------------------------------------------------------*/
    else
    {
        return OD_AttriubteCheck( ODAddr_IndexValue,SubIndex); /* 属性值的获取                      */    
    }
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的对象字典属性处理   															    */
/*                                                          										*/
/****************************************************************************************************/
void OD_Attriubte(USHORT Addr)
{
    OD_AttrVar.ODType       = ObjectDictionaryAttriub[Addr][0] & 0x0001;     /* 是否有子索引        */
    OD_AttrVar.Mapping      = ObjectDictionaryAttriub[Addr][0] & 0x0002;     /* 是否可映射          */
    OD_AttrVar.DataSign     = (ObjectDictionaryAttriub[Addr][0] >> 2) & 0x01;/* 数据符号            */
    OD_AttrVar.DataType     = ObjectDictionaryAttriub[Addr][0] & 0x001C;     /* 数据类型            */
    OD_AttrVar.Access       = ObjectDictionaryAttriub[Addr][0] & 0x0060;     /* 读写属性            */
    OD_AttrVar.DataLength   = ObjectDictionaryAttriub[Addr][0] & 0x0180;     /* 数据长度            */
    OD_AttrVar.Rang         = ObjectDictionaryAttriub[Addr][0] & 0xFE00;     /* 范围代码            */
    OD_AttrVar.MaxData      = MaxCheck(OD_AttrVar.Rang);                     /* 最大值              */
    OD_AttrVar.MinData      = MinCheck(OD_AttrVar.Rang);                     /* 最小值              */
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的对象字典属性处理   															    */
/*                                                          										*/
/****************************************************************************************************/
USHORT OD_AttriubteCheck(USHORT Addr,UCHAR SubIndex)
{
    OD_Attriubte(Addr);                                        /* 对象字典属性的获取                */
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典是否带为带索引                                                                       */
    if(OD_AttrVar.ODType == ODARR)                             /* 对象字典为数组型                  */
    {
        if(SubIndex > OD_AttrVar.MaxData)                      /* 判断子索引值是否在正确的范围内    */
            return OD_IndexNULL;                               /* 无效返回0xFFFF                    */
        else
        {
            OD_Attriubte(Addr + SubIndex);
            return (Addr+SubIndex);                            /* 返回正确地址值+子索引值           */
        }
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典为不带索引                                                                           */
    else                                                      /* 对象字典为数据型                   */
    {
        if(SubIndex == 0)                                     /* 数值型对象字典的子索引只能为0      */
            return Addr;
        else
            return OD_NULL;                                   /* 无效返回0xFFFF                     */
    }
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的对象字典数据读处理(0x40指令)   													*/
/*                                                          										*/
/****************************************************************************************************/
void OD_DataRead(USHORT Addr,USHORT SubIndex,UCHAR SDOSendNum )
{
#if 0   //20230803
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        if( Addr == 0x606C )
        {
            OD_AttrVar.DataLength = BYTE2;
        }
    }
#endif
    /*----------------------------------------------------------------------------------------------*/
    /* 读取1个字节(8位)                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    if(OD_AttrVar.DataLength == BYTE1)
    {
        OD_V.SendBuf[0] = 0x4F;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
        OD_V.SendBuf[4] = ODDatArr[SubIndex].byte.FirstByte;
        OD_V.SendBuf[5] = 0;
        OD_V.SendBuf[6] = 0;
        OD_V.SendBuf[7] = 0;
        OD_V.SendLength = 8;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 读取2个字节(16位)                                                                            */
    /*----------------------------------------------------------------------------------------------*/    
    else if(OD_AttrVar.DataLength == BYTE2)
    {
        OD_V.SendBuf[0] = 0x4B;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
        OD_V.SendBuf[4] = ODDatArr[SubIndex].byte.FirstByte;
        OD_V.SendBuf[5] = ODDatArr[SubIndex].byte.SecondByte;
        OD_V.SendBuf[6] = 0;
        OD_V.SendBuf[7] = 0;
        OD_V.SendLength = 8;

    }
    /*----------------------------------------------------------------------------------------------*/
    /* 读取4个字节(32位)                                                                            */
    /*----------------------------------------------------------------------------------------------*/
    else if(OD_AttrVar.DataLength == BYTE4)
    {
        OD_V.SendBuf[0] = 0x43;
        OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
        OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
        OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
        OD_V.SendBuf[4] = ODDatArr[SubIndex].byte.FirstByte;
        OD_V.SendBuf[5] = ODDatArr[SubIndex].byte.SecondByte;
        OD_V.SendBuf[6] = ODDatArr[SubIndex].byte.ThirdByte;
        OD_V.SendBuf[7] = ODDatArr[SubIndex].byte.FourthByte;
        OD_V.SendLength = 8;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 读取字节异常                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    else
    {
        return;
    }
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的对象字典数据异常处理            													*/
/*                                                          										*/
/****************************************************************************************************/
void OD_SDOError(UCHAR SDOSendNum,ULONG ErrorCode)
{
union ODUnion OD_Error;
    OD_Error.all = ErrorCode;
    
    OD_V.SendBuf[0] = 0x80;                                             /* 异常命令码:固定0x80      */
    OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
    OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
    OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
    OD_V.SendBuf[4] = OD_Error.byte.FirstByte;
    OD_V.SendBuf[5] = OD_Error.byte.SecondByte;
    OD_V.SendBuf[6] = OD_Error.byte.ThirdByte;
    OD_V.SendBuf[7] = OD_Error.byte.FourthByte;
    
    OD_V.SendLength = 8;
    
    CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);     /* 数据发送到CAN1中         */
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的对象字典SDO写入成功标志位        													*/
/*                                                          										*/
/****************************************************************************************************/
void OD_SDOWriteOver(UCHAR SDOSendNum)
{ 
    OD_V.SendBuf[0] = 0x60;                                             /* 固定0x60                 */
    OD_V.SendBuf[1] = CanVar.SDO[SDOSendNum].OD[0];
    OD_V.SendBuf[2] = CanVar.SDO[SDOSendNum].OD[1];
    OD_V.SendBuf[3] = CanVar.SDO[SDOSendNum].Index;
    OD_V.SendBuf[4] = 0;
    OD_V.SendBuf[5] = 0;
    OD_V.SendBuf[6] = 0;
    OD_V.SendBuf[7] = 0;
    OD_V.SendLength = 8;
    
    CAN1_Tx_Msg(OD_V.SDO_580,OD_V.SendLength,OD_V.SendBuf);     /* 数据发送到CAN1中         */
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 的SDO对象字典数据写入处理            												*/
/*                                                          										*/
/****************************************************************************************************/
void OD_DataWrite(USHORT OD_Addr,UCHAR SDOSendNum ,UCHAR TYPE)
{
union ODUnion SDO_WriteData;
USHORT ErrFlag = 0;
SHORT DataTmp = 0;
SHORT DataChar = 0;
    SDO_WriteData.all = CanVar.SDO[SDOSendNum].SDOData;
    /*----------------------------------------------------------------------------------------------*/
    /* 判断数据是否可写,只读数据不写入                                                              */
    if(OD_AttrVar.Access == RO)
    {
        OD_SDOError(SDOSendNum,WRITE_RO_OBJECT);
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    PDO_Var.PDO_ErrFlag = 0;
    switch(TYPE)
    {
        /*------------------------------------------------------------------------------------------*/
        case 0:                                                         /* 写入1个字节              */
            if(OD_AttrVar.DataLength == BYTE1)
            {
                //参数范围判断
                if(OD_AttrVar.DataSign == 0x00)
                {
                    //无符号数
                    if((ULONG)SDO_WriteData.byte.FirstByte > (ULONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((ULONG)SDO_WriteData.byte.FirstByte < (ULONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].byte.FirstByte = SDO_WriteData.byte.FirstByte;
                }
                else
                {
                    //有符号数
                    DataChar = (SHORT)SDO_WriteData.byte.FirstByte;
                    //-----------------------------------------------------------------------------
                    if( DataChar >= 128 )
                    {
                        DataChar -= 256;
                    }
                    //-----------------------------------------------------------------------------
                    if((LONG)(DataChar) > (LONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((LONG)DataChar < (LONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].byte.FirstByte = SDO_WriteData.byte.FirstByte;
                }
                ErrFlag = 0;
            }
            else
            {
                ErrFlag = 1;
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        case 1:                                                         /* 写入2个字节              */
            /*--------------------------------------------------------------------------------------*/
            if(OD_AttrVar.DataLength == BYTE2 )
            {
                //参数范围正常与否判断
                if(OD_AttrVar.DataSign == 0x00)
                {
                    //无符号数
                    if((ULONG)SDO_WriteData.word.LowWord > (ULONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((ULONG)SDO_WriteData.word.LowWord < (ULONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].word.LowWord = SDO_WriteData.word.LowWord;
                }
                else
                {
                    //有符号数
                    DataTmp = (SHORT)SDO_WriteData.word.LowWord;
                    if((LONG)DataTmp> (LONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((LONG)DataTmp < (LONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].word.LowWord = SDO_WriteData.word.LowWord;
                }
                ErrFlag = 0;
            }
            else if(OD_AttrVar.DataLength == BYTE4 )
            {
                if(OD_AttrVar.DataSign == 0x00)
                {
                    //无符号数
                    if((ULONG)SDO_WriteData.all > (ULONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((ULONG)SDO_WriteData.all < (ULONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].all = SDO_WriteData.word.LowWord;
                }
                else
                {
                    //有符号数
                    if((LONG)SDO_WriteData.all > (LONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((LONG)SDO_WriteData.all < (LONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].all = SDO_WriteData.word.LowWord;
                }            
            }
            else
            {
                ErrFlag = 1;          
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        default:                                                        /* 写入4个字节              */
            if(OD_AttrVar.DataLength == BYTE4)
            {
                if(OD_AttrVar.DataSign == 0x00)
                {
                    //无符号数
                    if((ULONG)SDO_WriteData.all > (ULONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((ULONG)SDO_WriteData.all < (ULONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].all = SDO_WriteData.all;
                }
                else
                {
                    //有符号数
                    if((LONG)SDO_WriteData.all > (LONG)OD_AttrVar.MaxData)
                        PDO_Var.PDO_ErrFlag = 5;
                    else if((LONG)SDO_WriteData.all < (LONG)OD_AttrVar.MinData)
                        PDO_Var.PDO_ErrFlag = 6;
                    else
                        ODDatArr[OD_Addr].all = SDO_WriteData.all;
                }

            }
            else
            {
                ErrFlag = 1;            
            }
            break;
    }
    /*----------------------------------------------------------------------------------------------*/
    if(ErrFlag == 1)                                                    /* 错误时应答               */
    {
        OD_SDOError(SDOSendNum,OD_DATA_LENGTH_INMATCH);         /* 故障:写入长度不匹配      */
    }
    /*----------------------------------------------------------------------------------------------*/
    else                                                                /* 正常时应答               */
    {
        /*------------------------------------------------------------------------------------------*/
        if(PDO_Var.PDO_ErrFlag == 0)
		{
            ODB_Update(OD_Addr);                                        /* 写入后,相关对象字典值更新*/
		}
        /*------------------------------------------------------------------------------------------*/
        /* 数据正常写入                                                                             */
        if(PDO_Var.PDO_ErrFlag == 0)
            OD_SDOWriteOver(SDOSendNum);
        /*------------------------------------------------------------------------------------------*/
        else if(PDO_Var.PDO_ErrFlag == 1)                               /* 写入的映射对象不存在     */
            OD_SDOError(SDOSendNum,OD_PDO_MAP_NOFOUND);
        else if(PDO_Var.PDO_ErrFlag == 2)                               /* 映射对象数据长度不匹配   */
            OD_SDOError(SDOSendNum,OD_DATA_LENGTH_ERROR);
        else if(PDO_Var.PDO_ErrFlag == 3)                               /* 分配映射对象不可映射     */
            OD_SDOError(SDOSendNum,OD_PDO_MAP_INVALID);
        else if(PDO_Var.PDO_ErrFlag == 4)                               /* 映射对象不可写           */
            OD_SDOError(SDOSendNum,OD_PDO_Read_ONLY);
        else if(PDO_Var.PDO_ErrFlag == 5)                               /* 大于上限                 */
            OD_SDOError(SDOSendNum,Data_UpLimit);
        else if(PDO_Var.PDO_ErrFlag == 6)                               /* 小于下限                 */
            OD_SDOError(SDOSendNum,Data_DownLimit);
        else if(PDO_Var.PDO_ErrFlag == 7)
            OD_SDOError(SDOSendNum,OD_PDO_DATA_LENGTH_INVALID);
        else if(PDO_Var.PDO_ErrFlag == 8)
            OD_SDOError(SDOSendNum,SUBINDEX_NOT_EXIST);
        else  
        {;}
    }
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 对象字典的值更新                    												*/
/*                                                          										*/
/****************************************************************************************************/
void ODB_Update(USHORT IndexAddr)
{
    switch(IndexAddr)
    {
        /*------------------------------------------------------------------------------------------*/
        case EMCY_COB_ID:
            if(ODDatArr[EMCY_COB_ID].all & 0x80000000)
            {
                OD_V.EMCY_En = 0;
            }
            else
            {
                OD_V.EMCY_En = 1;
            }
        /*------------------------------------------------------------------------------------------*/
        case SYNC_COB_ID:
            if(ODDatArr[SYNC_COB_ID].all & 0x40000000)
            {
                OD_V.SYNC_En = 1;
            }
            else
            {
                OD_V.SYNC_En = 0;
            }
            break;
        case SYNC_Period:
            OD_V.SYNC_Priod = (ULONG)8 * ODDatArr[SYNC_Period].all;
            break;
        /*------------------------------------------------------------------------------------------*/
        case Guard_Time:                                                /* 节点保护时间             */
            OD_V.SiteGuardTime = (ULONG)8 * ODDatArr[Guard_Time].word.LowWord * \
                                            ODDatArr[Life_Time].byte.FirstByte;
            CanVar.SiteGuardCnt     = 0;
            
            CanVar.NMTV.f.NMTUpFlag = 0;
            CanVar.NMTV.f.NMTGardEn = 0;
            
            break;
        case Life_Time:                                                 /*  寿命因子                */
            OD_V.SiteGuardTime = (ULONG)8 * ODDatArr[Guard_Time].word.LowWord * \
                                            ODDatArr[Life_Time].byte.FirstByte;
            CanVar.SiteGuardCnt     = 0;
            CanVar.NMTV.f.NMTUpFlag = 0;
            CanVar.NMTV.f.NMTGardEn = 0;
            break;
        /*------------------------------------------------------------------------------------------*/
        case Consumer_HeartBeat_Time:                                   /* 消费者时间               */
            OD_V.ConsumerTime = (ULONG)8 * ODDatArr[Consumer_HeartBeat_Time].word.LowWord;
            OD_V.ConsumerAddr = ODDatArr[Consumer_HeartBeat_Time].word.HighWord;
            break;
        case Producer_HeartBeat_Time:                                   /* 生产者时间               */
            OD_V.PoroductTime = (ULONG)8 * ODDatArr[Producer_HeartBeat_Time].all;
            break;
        /*------------------------------------------------------------------------------------------*/
        default:
            break;
    }
    PDO_MapUpdate(IndexAddr);

}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 主站节点保护                    												    */
/*                                                          										*/
/* 125us 执行一次                                                                                   */
/****************************************************************************************************/
void CANopen_SiteGuard(void)
{
  
    /*----------------------------------------------------------------------------------------------*/
    if(CanVar.NMTV.f.NMTInitOK == 1)
    {
      if( CANopen_SiteInitOK() == 0xFF)
      {
          //数据没有发送成功,等待下一次发送
          CanVar.NMTV.f.NMTInitOK = 1;
      }
      else
      {
          CanVar.NMTV.f.NMTInitOK = 0;
      }
    }  
    /*----------------------------------------------------------------------------------------------*/
    if(OD_V.SiteGuardTime == 0)
      return;
    /*----------------------------------------------------------------------------------------------*/
    /* 节点保护开启后,在第一个远程帧有效后开始监控主站                                              */
    if( CanVar.NMTV.f.NMTUpFlag == 1 )
    {
        CanVar.NMTV.f.NMTGardEn = 1;
    }
    /*----------------------------------------------------------------------------------------------*/
    if((CanVar.NMTV.f.NMTGardEn == 1) && (++CanVar.SiteGuardCnt > OD_V.SiteGuardTime))
    {
        //Er.E20 节点保护超时
        CanVar.SiteGuardCnt = 0;
        KPI_ALARMSET( ALM_CAN_MOFF );
        NMT_StationMnge(0x80);
    }
    /*----------------------------------------------------------------------------------------------*/
    if(CanVar.NMTV.f.NMTUpFlag == 1)
    {
        if(CANopen_SiteResponse(0) == 0xFF)
          return;
        else
          CanVar.NMTV.f.NMTUpFlag = 0;
    }

}
/****************************************************************************************************/
/*																									*/
/*		CanOpen 心跳报文                        												    */
/*                                                          										*/
/* 125us 执行一次                                                                                   */
/****************************************************************************************************/
void HeartBeat(void)
{
    /*----------------------------------------------------------------------------------------------*/
    /* 启动后,没有接收到第一帧心跳报文时,不对心跳监测     <V0120>                                   */
	/*----------------------------------------------------------------------------------------------*/  
  	if( CanVar.NMTV.f.HeartBFlag == 0 )
	{
		CanVar.ConsumerTCnt = 0;	
	}
    /*----------------------------------------------------------------------------------------------*/
    /* 消费者时间                                                                                   */
	/*----------------------------------------------------------------------------------------------*/
    if( OD_V.ConsumerTime != 0 && CanVar.NMTV.f.HeartB_En == 1 )
    {
        if(++CanVar.ConsumerTCnt > OD_V.ConsumerTime)
        {
            CanVar.ConsumerTCnt = 0;
            KPI_ALARMSET( ALM_CAN_COMTOV );
            NMT_StationMnge(0x80);
        }
    }
    else
    {
        CanVar.ConsumerTCnt = 0;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if( CanVar.BeatHrtFlg == 1 )
    {
        (void)CANopen_SiteResponse(1);
    }    
    /* 生产者时间                                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    if(OD_V.PoroductTime != 0 && CanVar.NMTV.f.HeartB_En == 1)
    {
        if(++CanVar.ProductrTCnt > OD_V.PoroductTime)
        {
            CanVar.ProductrTCnt = 0;
            CanVar.BeatHrtFlg = 1;
        }
    }
    else
    {
        CanVar.ProductrTCnt = 0;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  状态监控                                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if( CanVar.NMTV.f.HeartB_En )
    {
        /*------------------------------------------------------------------------------------------*/
        if( OD_V.ConsumerTime != 0 ) CanVar.NMTV.f.ConsumHeart = 1;
        else                         CanVar.NMTV.f.ConsumHeart = 0;
        /*------------------------------------------------------------------------------------------*/
        if( OD_V.PoroductTime != 0 ) CanVar.NMTV.f.ConsumHeart = 1;
        else                         CanVar.NMTV.f.PoroduHeart = 0;
        /*------------------------------------------------------------------------------------------*/
    }
    else
    {
        CanVar.NMTV.f.ConsumHeart = 0;
        CanVar.NMTV.f.PoroduHeart = 0;
    }
}
/****************************************************************************************************/
/*																									*/
/*		CanOpen 心跳和节点保护应答                												    */
/*                                                          										*/
/* 125us 执行一次                                                                                   */
/* Input:0:节点应答                                                                                 */
/*       1:心跳                                                                                     */
/****************************************************************************************************/
UCHAR CANopen_SiteResponse(UCHAR Type)
{
uint16_t SendBuf[8];
    /*----------------------------------------------------------------------------------------------*/
    /* 有空闲邮箱                                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    SendBuf[0] = CanVar.NMTV.f.NMTStatus & 0x7F;
    if(Type == 0)
    {   //节点/寿命,最高位需要0<->1切换
        CanVar.NMTV.f.NMTChange = ~CanVar.NMTV.f.NMTChange;
        SendBuf[0] |= CanVar.NMTV.f.NMTChange << 7;
    }
    else if( Type == 2 )
    {
        CanVar.NMTV.f.NMTChange = ~CanVar.NMTV.f.NMTChange;
        SendBuf[0] = 0;    
    }
    CAN1_Tx_Msg(OD_V.Heart_Beat,1,SendBuf);                     /* 数据发送到CAN1中         */
    CanVar.BeatHrtFlg   = 0;
    
    /*----------------------------------------------------------------------------------------------*/
    /* 在预操作模式下,PDO需要关闭 @2021.09.24                                                       */
    /*----------------------------------------------------------------------------------------------*/
    if( CanVar.NMTV.f.NMTStatus == 0x7F )
    {   
        CanVar.NMTV.f.PDO_En = 0;
    }
    /*----------------------------------------------------------------------------------------------*/
    return 0;
}

/****************************************************************************************************/
/*																									*/
/*		CanOpen 初始化启动完成                    												    */
/*                                                          										*/
/* 125us 执行一次                                                                                   */
/* Input:0:节点应答                                                                                 */
/*       1:心跳                                                                                     */
/****************************************************************************************************/
UCHAR CANopen_SiteInitOK(void)
{
uint16_t SendBuf[8];
    /*----------------------------------------------------------------------------------------------*/
    /* 有空闲邮箱                                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    SendBuf[0] = 0x00;
    CAN1_Tx_Msg(OD_V.Heart_Beat,1,SendBuf);                     /* 数据发送到CAN1中         */
    return 0;
}

#if 0
void ODB6XXXX_EEPROM_Update(USHORT OD_Addr,USHORT OD_SubIndex )
{
    UCHAR OD_IndexValue;
    PRMDEF  *prm_def;
    switch (OD_Addr)
    {
        case OD_605A:
            OD_IndexValue = 569;
            break;
        case OD_605D:
            OD_IndexValue = 570;
            break;
        case OD_6060:
            OD_IndexValue = 571;
            break;
        case OD_6065:
            OD_IndexValue = 572;
            break;
        case OD_6067:
            OD_IndexValue = 574;
            break;
        case OD_6068:
            OD_IndexValue = 576;
            break;
        case OD_606D:
            OD_IndexValue = 578;
            break;
        case OD_606E:
            OD_IndexValue = 579;
            break;
        case OD_606F:
            OD_IndexValue = 579;
            break;
        case OD_606F:
            OD_IndexValue = 580;
            break;
        case OD_6070:
            OD_IndexValue = 580;
            break;
        case OD_6071:
            OD_IndexValue = 582;
            break;
        case OD_6072:
            OD_IndexValue = 582;
            break;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 在更新RAM之前,先将目前RAM中的数据取出来,便于后面使用                                           */
    /*----------------------------------------------------------------------------------------------*/
    Data = *(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr);
    if(PnPrmTbl[OD_IndexValue].PrmDefPtr->Attr.IsLong )
    {
        Data += (((ULONG)(*(PnPrmTbl[OD_IndexValue + 1].PrmDefPtr->RamPtr))) << 16);
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 写入的数据类型为16位                                                                          */
    /*----------------------------------------------------------------------------------------------*/
    *(PnPrmTbl[OD_IndexValue].PrmDefPtr->RamPtr) =  SDO_WriteData.word.LowWord;
    /*----------------------------------------------------------------------------------------------*/
    /* 判断数据是否需要存储值Eeprom 中                                                              */
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
}
#endif

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/

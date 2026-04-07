/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can01_Can.c : Can 数据接收和发送管理            											*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"


#ifdef CPU2
typedef union   {
    struct  {
        uint32_t    Mailbox1         :1;         // Mailbox 1
        uint32_t    Mailbox2         :1;         // Mailbox 2
        uint32_t    Mailbox3         :1;         // Mailbox 3
        uint32_t    Mailbox4         :1;         // Mailbox 4
        uint32_t    Mailbox5         :1;         // Mailbox 5
        uint32_t    Mailbox6         :1;         // Mailbox 6
        uint32_t    Mailbox7         :1;         // Mailbox 7
        uint32_t    Mailbox8         :1;         // Mailbox 8
        uint32_t    Reserved         :24;        // Reserved
    } f;
    uint32_t dw;
}CANMAILBOXR;
#endif
CANSTRUCT CanVar;
void SDO_FrameRecive(void);                                /* SDO帧报文接收处理                    */
void NMT_StationMnge(UCHAR NMTStatus);					    /* 状态机管理							*/
/****************************************************************************************************/
/*																									*/
/*		Can 初始化(相关变量清零)           															*/
/*                                                                                                  */
/****************************************************************************************************/
void CAN_Init(void)
{
    MlibResetSHORTMemory((void *)&CanVar, sizeof(CanVar)); /* 相关数据清零处理                      */
    CanVar.NMTV.f.NMT_En = 1;                              /* 上电则开启NMT接收                     */
	CanVar.NMTV.f.HeartBFlag = 0;						   /*  清除第一次心跳报文					*/
    
    if( ( Prm.Mode & 0x1000) == 0x0000 )
    {
        OD_V.Heart_Beat = 0x700+ Prm.Address;
        (void)CANopen_SiteResponse(1);                     /* 上电第一次发送心跳                    */
    }
    
	NMT_StationMnge(0x80);								   /*  上电进入预处理状态					*/
}


/****************************************************************************************************/
/* RPDO 接收Buff 清空                                                                               */
/****************************************************************************************************/
void RPDOBuffClr( void )
{
    UCHAR i,j;
    for( i = 0; i < 4; i++ )
    {
        for( j = 0; j < 8; j++ )
        {
            PDO_Var.RPDO_SyncBuf[i][j] = 0;
        }
    }
}



/****************************************************************************************************/
/*                                                                                                  */
/*  网络状态 0x80 操作处理                                                                          */
/*                                                                                                  */
/****************************************************************************************************/
void NMT_80Task( void )
{
    CanVar.NMTV.f.SDO_En        = 1;
    CanVar.NMTV.f.PDO_En        = 0;
    CanVar.NMTV.f.HeartB_En     = 1;
    CanVar.NMTV.f.NMTStatus     = 0x7F;
    CanVar.NMTStatus            = 2;
    
    CanVar.NMTV.f.NMT_En        = 1;

    PDO_Var.TPDO_En[0]          = 0;
    PDO_Var.TPDO_En[1]          = 0;
    PDO_Var.TPDO_En[2]          = 0;
    PDO_Var.TPDO_En[3]          = 0;

    PDO_Var.TPDO_Asynch[0]      = 0;
    PDO_Var.TPDO_Asynch[1]      = 0;
    PDO_Var.TPDO_Asynch[2]      = 0;
    PDO_Var.TPDO_Asynch[3]      = 0;
    PDO_Var.TPDO_SynchCnt[0]    = 0;
    PDO_Var.TPDO_SynchCnt[1]    = 0;
    PDO_Var.TPDO_SynchCnt[2]    = 0;
    PDO_Var.TPDO_SynchCnt[3]    = 0;

    PDO_Var.TPDO_AsyProbitcnt[ 0 ] = 0;
    PDO_Var.TPDO_AsyProbitcnt[ 1 ] = 0;
    PDO_Var.TPDO_AsyProbitcnt[ 2 ] = 0;
    PDO_Var.TPDO_AsyProbitcnt[ 3 ] = 0;

    PDO_Var.TPDO_TRIGFlg[ 0 ] = 0;
    PDO_Var.TPDO_TRIGFlg[ 1 ] = 0;
    PDO_Var.TPDO_TRIGFlg[ 2 ] = 0;
    PDO_Var.TPDO_TRIGFlg[ 3 ] = 0;

    RPDOBuffClr();
}


/****************************************************************************************************/
/*																									*/
/*		NMT 状态管理                   															    */
/*																									*/
/* 01h	启动远程节点指令                                                                                */
/* 02h	停止远程节点指令                                                                                */
/* 80h	进入预操作状态指令                                                                               */
/* 81h	复位节点指令                                                                                   */
/* 82h	复位通信指令                                                                                   */
/****************************************************************************************************/
void NMT_StationMnge(UCHAR NMTStatus)
{
    CanVar.CanCmdStatus = NMTStatus;
    switch( NMTStatus )
    {
        /*------------------------------------------------------------------------------------------*/
	  	case 0x00:
        case 0x01:  //启动远程节点指令(启动从站所有的SDO,PDO,心跳)
            CanVar.NMTV.f.SDO_En        = 1;
            CanVar.NMTV.f.PDO_En        = 1;
			CanVar.NMTV.f.PDOSyncFlg    = 1;
            CanVar.NMTV.f.HeartB_En     = 1;
            CanVar.NMTV.f.NMTStatus     = 5;
			CanVar.NMTV.f.NMT_En        = 0;
            CanVar.NMTStatus            = 8;
            //-------------------------------------------------------------- 
            if((ODDatArr[PDO1_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[0] = 0;
            else
                PDO_Var.RPDO_En[0] = 1;
            //-------------------------------------------------------------- 
            if((ODDatArr[PDO2_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[1] = 0;
            else
                PDO_Var.RPDO_En[1] = 1;
            //-------------------------------------------------------------- 
            if((ODDatArr[PDO3_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[2] = 0;
            else
                PDO_Var.RPDO_En[2] = 1;
            //-------------------------------------------------------------- 
            if((ODDatArr[PDO4_Receive_COB_ID].word.HighWord & 0x8000) == 0x8000)
                PDO_Var.RPDO_En[3] = 0;
            else
                PDO_Var.RPDO_En[3] = 1;
            //--------------------------------------------------------------            
            if((ODDatArr[PDO1_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                PDO_Var.TPDO_En[0] = 0;
            else
                PDO_Var.TPDO_En[0] = 1;
            //--------------------------------------------------------------
            if((ODDatArr[PDO2_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                PDO_Var.TPDO_En[1] = 0;
            else
                PDO_Var.TPDO_En[1] = 1;
            //--------------------------------------------------------------
            if((ODDatArr[PDO3_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                PDO_Var.TPDO_En[2] = 0;
            else
                PDO_Var.TPDO_En[2] = 1;
            //--------------------------------------------------------------
            if((ODDatArr[PDO4_Trans_COB_ID].all & 0x80000000) == 0x80000000)
                PDO_Var.TPDO_En[3] = 0;
            else
                PDO_Var.TPDO_En[3] = 1;
            //--------------------------------------------------------------
			break;
        /*------------------------------------------------------------------------------------------*/          
        case 0x02:  //停止远程节点指令(只有心跳工作)
            CanVar.NMTV.f.SDO_En        = 0;
            CanVar.NMTV.f.PDO_En        = 0;
            CanVar.NMTV.f.HeartB_En     = 1;
            CanVar.NMTV.f.NMTStatus     = 4;
            PDO_Var.TPDO_En[0]          = 0;
            PDO_Var.TPDO_En[1]          = 0;
            PDO_Var.TPDO_En[2]          = 0;
            PDO_Var.TPDO_En[3]          = 0;
          break;
        /*------------------------------------------------------------------------------------------*/          
        case 0x80:  //进入预操作状(除PDO外,都工作)
            NMT_80Task( );
            break;
        /*------------------------------------------------------------------------------------------*/
        case 0x81:  //所有报文都不接收(重启Can总线)
            CanVar.NMTV.f.SDO_En        = 0;
            CanVar.NMTV.f.PDO_En        = 0;
            CanVar.NMTV.f.HeartB_En     = 0;
			CanVar.NMTV.f.HeartBFlag    = 0;
            CanVar.NMTV.f.NMTInitOK     = 1;        //置位发送Can启动标志
            PDO_Var.TPDO_Asynch[0]      = 0;
            PDO_Var.TPDO_Asynch[1]      = 0;
            PDO_Var.TPDO_Asynch[2]      = 0;
            PDO_Var.TPDO_Asynch[3]      = 0;
            PDO_Var.TPDO_SynchCnt[0]    = 0;
            PDO_Var.TPDO_SynchCnt[1]    = 0;
            PDO_Var.TPDO_SynchCnt[2]    = 0;
            PDO_Var.TPDO_SynchCnt[3]    = 0;
            PDO_Var.TPDO_AsyProbitcnt[ 0 ] = 0;
            PDO_Var.TPDO_AsyProbitcnt[ 1 ] = 0;
            PDO_Var.TPDO_AsyProbitcnt[ 2 ] = 0;
            PDO_Var.TPDO_AsyProbitcnt[ 3 ] = 0;
            
            PDO_Var.TPDO_En[0]          = 0;
            PDO_Var.TPDO_En[1]          = 0;
            PDO_Var.TPDO_En[2]          = 0;
            PDO_Var.TPDO_En[3]          = 0;
            if(CAN_EXFUNC0_15_DIS)                      /* 复位节点不初始化PDO  20240924     */
            {
                DB_InitialValue();		                //对象字典初始化为默认值
            }
           /*--------------------------------------------------------------------------------------*/
            CanVar.NMTV.f.PDO1600Flg = 0;
            CanVar.NMTV.f.PDO1601Flg = 0;
            CanVar.NMTV.f.PDO1602Flg = 0;
            CanVar.NMTV.f.PDO1603Flg = 0;
            CanVar.NMTV.f.PDO1A00Flg = 0;
            CanVar.NMTV.f.PDO1A01Flg = 0;
            CanVar.NMTV.f.PDO1A02Flg = 0;
            CanVar.NMTV.f.PDO1A03Flg = 0;
            /*--------------------------------------------------------------------------------------*/
			NMT_80Task();	                //进入预操作
            /*--------------------------------------------------------------------------------------*/
            /* 检测当前是否有故障码                                                                 */
            /*--------------------------------------------------------------------------------------*/
            if( Alm.f.AlmFlag == 1 )
            {
                CanVar.NMTV.f.NETInitEmcy = 1;
            }
            else
            {
                CanVar.NMTV.f.NETInitEmcy = 0;
            } 
            break;
        /*------------------------------------------------------------------------------------------*/
        case 0x82:  //对象字典初始化  (复位通讯)
            CanVar.NMTV.f.SDO_En        = 0;
            CanVar.NMTV.f.PDO_En        = 0;
            CanVar.NMTV.f.HeartB_En     = 0;
			CanVar.NMTV.f.HeartBFlag    = 0;
			if(CAN_EXFUNC0_15_DIS)                      /* 复位节点不初始化PDO  20240924     */
			{
			    DB1000_InitialValue( );
			}
            PDO_Var.TPDO_Asynch[0]      = 0;
            PDO_Var.TPDO_Asynch[1]      = 0;
            PDO_Var.TPDO_Asynch[2]      = 0;
            PDO_Var.TPDO_Asynch[3]      = 0;
            PDO_Var.TPDO_SynchCnt[0]    = 0;
            PDO_Var.TPDO_SynchCnt[1]    = 0;
            PDO_Var.TPDO_SynchCnt[2]    = 0;
            PDO_Var.TPDO_SynchCnt[3]    = 0;

			NMT_80Task();	    //进入预操作
            
            OD_V.Heart_Beat = 0x700+ Prm.Address;
            (void)CANopen_SiteResponse( 2 );               /* 上电第一次发送心跳                    */

            break;
        /*------------------------------------------------------------------------------------------*/
        default:
            CanVar.NMTStatus            = 1;
            break;
        /*------------------------------------------------------------------------------------------*/
    }
}
volatile USHORT CanFlag = 0;
volatile USHORT CanFlagCnt = 0;
//*************************************************************************************************
//
//		Can 接收(查询)
// Attention:   62.5us查询一次
//
//*************************************************************************************************
void CAN1_RXCheck(void)
{
#ifdef CPU1
    ULONG Id = 0;
    UCHAR Data1,Data2;
    UCHAR RemuteFlag = 0;
    UCHAR i;
    RxFS.num = 1;

    //----------------------------------------------------------------------------------------------
    // 自动开启节点
    //----------------------------------------------------------------------------------------------
#if 1
    if( CanFlag == 0 )
    {
        CanFlagCnt++;
        if( CanFlagCnt >= 32000 )
        {
            if( CAN_EXFUNC0_0_EN )
            {
                NMT_StationMnge(0x01);
            }
            CanFlag = 1;
        }
    }
#endif

    MCAN_getRxFIFOStatus(MCAN0_BASE, &RxFS);
    if( RxFS.fillLvl == 0 )
    {
        CanVar.CanStatusCnt ++;
        if( CanVar.CanStatusCnt < 32000)
        {
            CanVar.CanStatusCnt = 32000;
        }
        return;
    }

    CanVar.CanStatusCnt = 0;
    //---------------------------------------------------------------------------------------------
    // 判断Can是否有接收到数据
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    // CAN 有接收到数据,需要进行处理
    //---------------------------------------------------------------------------------------------
    RxMsg.data[ 0 ] = 0;
    RxMsg.data[ 1 ] = 0;
    MCAN_readMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_FIFO, 0U, MCAN_RX_FIFO_NUM_1, &RxMsg);
    MCAN_writeRxFIFOAck(MCAN0_BASE, MCAN_RX_FIFO_NUM_1, RxFS.getIdx);

    for( i = RxMsg.dlc; i < 8; i ++ )
    {
        RxMsg.data[ i ] = 0;
    }

    RemuteFlag = RxMsg.rtr;                 //远程帧和数据帧标志(0:数据帧;1:远程帧)
    Id = (RxMsg.id >> 18) & 0x0FFF;         // 标准帧
    //---------------------------------------------------------------------------------------------
    if( CanVar.NMTV.f.PDO_En == 1 )
    {
        if( Id == 0x00000080 )
        {
            RPDO_SynchDeal();                               // RPDO 同步更新处理
            PDO_Var.TPDO_SynchCnt[0] ++;
            PDO_Var.TPDO_SynchCnt[1] ++;
            PDO_Var.TPDO_SynchCnt[2] ++;
            PDO_Var.TPDO_SynchCnt[3] ++;

            PDO_Var.SYNCUpFlag = 1;
            PDO_Var.SYNCUpFlag1 = 1;
        }
        //-----------------------------------------------------------------------------------------
        else if(Id == ((ULONG)PDO1ID_R + Prm.Address))     // RPDO1 接收
        {
            RPDO1();
        }
        //-----------------------------------------------------------------------------------------
        else if(Id == ((ULONG)PDO2ID_R + Prm.Address))     // RPDO2 接收
        {
            RPDO2();
        }
        //-----------------------------------------------------------------------------------------
        else if(Id == ((ULONG)PDO3ID_R + Prm.Address))     // RPDO3 接收
        {
            RPDO3();
        }
        //-----------------------------------------------------------------------------------------
        else if(Id == ((ULONG)PDO4ID_R + Prm.Address))     // RPDO4 接收
        {
            RPDO4();
        }
        else
        {
            ;
        }
    }
    //---------------------------------------------------------------------------------------------
    if(Id == 0)                                           // NMT
    {
        Data1 = RxMsg.data[ 0 ];
        Data2 = RxMsg.data[ 1 ];
        if(Data2 == 0x00 || Data2 == (UCHAR)Prm.Address)
        {
            NMT_StationMnge(Data1);
        }
    }
    //---------------------------------------------------------------------------------------------
    else if((Id == ((ULONG)SDOID_R + Prm.Address)) && CanVar.NMTV.f.SDO_En)      // SDO 接收
    {
        SDO_FrameRecive();
    }
    //---------------------------------------------------------------------------------------------
    else if((Id == ((ULONG)BEAT + Prm.Address)) && RemuteFlag)  // NMT 节点保护
    {
        CanVar.NMTV.f.NMTUpFlag = 1;                            // NMT 节点保护到达信号
        CanVar.SiteGuardCnt = 0;                                // 节点/寿命保护计时器清零
    }
    //---------------------------------------------------------------------------------------------
    else if((Id == ((ULONG)BEAT + OD_V.ConsumerAddr)) && CanVar.NMTV.f.HeartB_En)
    {
        CanVar.ConsumerTCnt = 0;                                // 心跳帧,消费者发送
        CanVar.NMTV.f.HeartBFlag = 1;                           // 心跳标志(第一次)
        //-----------------------------------------------------------------------------------------
        if( ( Prm.Mode & 0xF000 ) == 0x1000 && ( ( Prm.almmsk1 & 0x0040 ) == 0x0000 ))
        {
            CanVar.NMTV.f.NMTUpFlag = 1;                        // NMT 节点保护到达信号
            CanVar.SiteGuardCnt = 0;                            // 节点/寿命保护计时器清零
            OD_V.SiteGuardTime = ( OD_V.PoroductTime * 3 ) >> 1;
        }
    }
    //---------------------------------------------------------------------------------------------
    else
    {
        ;
    }
#endif
}

//*************************************************************************************************
//
//		SDO 帧报文接收缓存
//
//*************************************************************************************************
void SDO_FrameRecive(void)
{

    if( CanVar.SDOSavedNum >= SDOBuff_Max )
    {
        CanVar.SDOSavedNum = 0;
    }
    //*********************************************************************************************
    // 数据缓存
    //*********************************************************************************************
#ifdef CPU1
    CanVar.SDO[CanVar.SDOSavedNum].FCmd    =  RxMsg.data[0];
    CanVar.SDO[CanVar.SDOSavedNum].OD[0]   =  RxMsg.data[1];
    CanVar.SDO[CanVar.SDOSavedNum].OD[1]   =  RxMsg.data[2];
    CanVar.SDO[CanVar.SDOSavedNum].Index   =  RxMsg.data[3];
    
    CanVar.SDO[CanVar.SDOSavedNum].SDOData = (((uint32_t)RxMsg.data[4]) << 0) + \
                                             (((uint32_t)RxMsg.data[5]) << 8) + \
                                             (((uint32_t)RxMsg.data[6]) << 16) + \
                                             (((uint32_t)RxMsg.data[7]) << 24);
#endif
    
    //*********************************************************************************************
    // 缓存数量计数器 +1
    //*********************************************************************************************
    CanVar.SDOSavedNum ++;
    CanVar.SDORemain += 1;
    //*********************************************************************************************

}

//*************************************************************************************************
//
//		Can 数据发送
//
//*************************************************************************************************
void CAN1_Tx_Msg(ULONG id,uint16_t len,uint16_t *dat)
{
#ifdef CPU1
USHORT i;
    //
    // 发送数据处理
    //
    TxMsg.id       = id << 18U; // STDID[28:18];
    TxMsg.dlc      = len;

    for( i = 0; i < len;i++ )
    {
        TxMsg.data[ i ] = dat[ i ];
    }

    //
    // Write message to Message RAM.
    //
    MCAN_writeMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_BUF, MCFIFOIndex, &TxMsg);
    //
    // Add request for all transmission.
    //
    HWREG(MCAN0_BASE + MCAN_TXBAR) = ( 0x00000001 << MCFIFOIndex );
    MCFIFOIndex++;
    if( MCFIFOIndex >= 15 )
    {
        MCFIFOIndex = 0;
    }
#endif

}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/


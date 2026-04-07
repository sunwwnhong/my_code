/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : User16_USBifMbus.c
* Version            : V0.1
* Date               : 2024
* Description        : USB通讯处理部分
***********************************************************************************************/
#include "Main.h"

#ifdef CPU1
#include "USB00_Main.h"
#endif

RMNGV   Usb_RmngV = {0,0};
USBIF   Usbif;      // USB通信IF变量



/**********************************************************************************************/
/* Function_Name: DpiInitUsbMbusMsg         */ 
/* Description  : USB通信IF变量初始化处理
                  调用：上电初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void DpiInitUsbMbusMsg( void )
{
    //
    //Reset All Data to Zero
    //
    MlibResetLONGMemory( &Usbif, sizeof( Usbif ) / 2 );

    return;
}

/*** 数据接收和发送步骤 ***/
#define     USTEP_INITIAL               0x00
#define     USTEP_CheckRec              0x01
#define     USTEP_WAIT_OUT              0x02
#define     USTEP_BKOUT_CMP             0x03
#define     USTEP_WAIT_START_IN         0x04
#define     USTEP_WAIT_START_IN2        0x05
#define     USTEP_WAIT_START_IN3        0x06
#define     USB_MSG_TIMEOUT             20000


/**********************************************************************************************/
/* Function_Name: DpxUsbifMsgManager         */ 
/* Description  : USB通讯实时监控：定周期监视处理(ScanB Cycle)
                  调用：ScanB任务中调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void DpxUsbifMsgManager( void )
{
#ifdef CPU1
    /*** USB通信发送/接收监视序列 ***/
    switch( Usbif.SqStep )
    {
        // 步骤0：初始步骤
        case USTEP_INITIAL:
                Usbif.SqStep = USTEP_CheckRec;
        break;

        case USTEP_CheckRec:
            if( Usbif.f.BlkInFlag == 1 )
            {
                Usbif.f.BlkInFlag = 0;
                Usbif.OutCmpWait  = 0;
                Usbif.SqStep = USTEP_WAIT_OUT;
            }
        break;

        case USTEP_WAIT_OUT:
            Usbif.OutCmpWait ++;
            if( Usbif.f.BlkInFlag == 1 )
            {
                Usbif.f.BlkInFlag = 0;
                Usbif.OutCmpWait  = 0;
            }
            if( Usbif.OutCmpWait > 5 )
            {
                Usbif.SqStep = USTEP_BKOUT_CMP;
            }
            break;

        case USTEP_BKOUT_CMP:
            if( ( UsbRecBuf.ReciveBuf[0] == 0x00 )||( UsbRecBuf.ReciveBuf[0] == 0x01 ))
            {
                Usbif.f.USBRecFlag = 1;                     
                Usbif.MbusRcvLength = Usbif.UsbRecLenth;    
                Usbif.SqStep = USTEP_WAIT_START_IN;
            }
            else if( UsbRecBuf.ReciveBuf[0] == 0x02 && Kprm.f.AxisNum == 1 )
			{
                UsbRecBuf.RecivedSum ++;
                UsbRecBuf.MbusDataLen = Usbif.UsbRecLenth;
                Usbif.Tick = UsbTrsBuf.TransSum;
                Usbif.SkipTick = UsbTrsBuf.SkipSum;
                Usbif.SqStep = USTEP_WAIT_START_IN3;
            }
            else
            {
                Usbif.SqStep = USTEP_INITIAL;
            }
            Usbif.UsbRecLenth = 0;
        break;

        case USTEP_WAIT_START_IN:
            break;
        case USTEP_WAIT_START_IN2:

            if( Usbif.f.BlkInStart == TRUE )
            {
                UsbDataSend( 0 );
            }
            Usbif.SqStep = USTEP_INITIAL;
            break;

        case USTEP_WAIT_START_IN3:
            if( UsbTrsBuf.TransSum != Usbif.Tick)
            {
                UsbDataSend( 1 );
                Usbif.SqStep = USTEP_INITIAL;
            }
            if( UsbTrsBuf.SkipSum != Usbif.SkipTick)
            {
                Usbif.SqStep = USTEP_INITIAL;
            }
            break;

        default :
            Usbif.SqStep = USTEP_INITIAL;
            break;
    }
#endif

}

/**********************************************************************************************/
/* Function_Name: DpxSetUsbMbusTrnsStart         */ 
/* Description  : Modbus开始应答指令(通知通信时序中开始发送数据)(Round用)
                  调用：USB/串口通讯开始应答指令-函数调用
                  输入：应答长度(Byte)、应答类型(应答/不应答)
                  输出：   */
/**********************************************************************************************/
UCHAR   DpxSetUsbMbusTrnsStart( USHORT  MsgLength, USHORT   MsgType )
{

    UCHAR   rc = COMDEV_UNDEF;

        /*** 消息处理时序：SQSTEP_WAITSTX状态时进行应答处理 ***/
        if( Usbif.SqStep == USTEP_WAIT_START_IN )
        {
            /*** 发送数据长度合法性检查 ***/
            if(( MsgLength > (USHORT)MBUS_TRN_MAXSIZEB ) || ( MsgLength < 5 ) )
            {
                Usbif.f.BlkInStart = TRUE;              // 指示序列开始发送
#ifdef CPU1
                Usbif.MbusTrnLength = 0;                // 发送长度为0
#endif
            Usbif.SqStep = USTEP_WAIT_START_IN2;    // 消息序列进入：发送请求和执行阶段
                rc = COMDEV_NGSIZE;                     // 函数返回消息异常
            }
            else
            {
#ifdef CPU1
                Usbif.MbusTrnLength = MsgLength;         // 发送字节数
#endif

                /*** 信息类型检查 ***/
                switch( MsgType )
                {
                    case RESMT_COMPLETE :               // 完成响应消息
                        rc = COMDEV_OK;                 // 返回OK
                        Usbif.f.BlkInStart = TRUE;      // 指示序列开始发送
                        break;
                    case RESMT_NORESPONSE :             // 无需响应
                        rc = COMDEV_OK;                 // 返回OK
                        Usbif.f.BlkInSkip = TRUE;       // 无需应答
                        break;
                    default :
                        rc = COMDEV_UNDEF;              // 消息类型异常
                        break;
                }
                // 切换至数据开始发送步骤
                Usbif.SqStep = USTEP_WAIT_START_IN2;
            }
        }
        // 未到达发送时机
        else
        {
            rc = COMDEV_NGTIME;
        }

        return( rc );

}

/**********************************************************************************************/
/* Function_Name: RpxUsbMsgManager         */ 
/* Description  : USB消息管理
                  调用：主循环2ms任务
                  输入：
                  输出：   */
/**********************************************************************************************/
void    RpxUsbMsgManager( void )
{
        /*** USB接收数据完成检查 ***/
        /*** 通过实时监控函数自动完成数据的接收，然后进入等待状态，此函数通过判断是否进入
        等待状态来确定是否接收完成。并获取接收数据长度。 ***/
        if( COM_ACK == DriComGetRcvComplete( COM1_USB, &UsbMsg.RcvLen ))    // USB接收数据完成
        {
            /*** 根据接收数据指针和接收数据长度，检查crc校验是否通过 ***/
            if( RpxSmsgCheckRecvMessage( &UsbMsg ) == OK )
            {
                KpiRstLongTimer( &UsbMsg.ComTimeLong );     // 正常收到数据时,计时器清零
                RpiSetAccsLvl( &Access, UsbMsg.AccsLvl );   // 设置访问权限
                OpeReg.CommType = 0;                        // 设置寄存器操作的通讯类型：USB通讯
                RpxSmsgMainProcedure( &UsbMsg );            // Modbus 协议处理
                Usb_RmngV.SerComMode = SMSGCOM;             // 设置通讯类型为通讯接入
            }
            else
            {
                DriComSetTrnsStart( COM1_USB, 5, RESMT_NORESPONSE );
            }
        }
        else
        {
           switch( Usb_RmngV.SerComMode ) 
            { 
              case SMSGCOM:         // 串口有接入
                if( KpiGetLongTimer( &UsbMsg.ComTimeLong ) > USB_MSG_TIMEOUT )  // 串口20s没有输入，则退出串口接入
                { 
                    RpxSmsgFinishProcedure( &UsbMsg );                          // 串口断开时,自动退出处理
                    DriComSetTrnsStart( COM1_USB, 5, RESMT_NORESPONSE );        // 接收数据异常，无需应答
                    Usb_RmngV.SerComMode = NOCOM;                               // 无连接设备
                } 
                break; 
            default: 
                break; 
            } 
        }
        return;
}

/**********************************************************************************************/
/* Function_Name: DpxGetUsbMbusRcvACK         */ 
/* Description  : 判断Modbus消息是否接收完毕，并获取消息长度(Round用,判断是否开始处理消息)
                  调用：判断通信端口是否接收数据完毕-函数中调用
                  输入：
                  输出：   */
/**********************************************************************************************/
UCHAR   DpxGetUsbMbusRcvACK( USHORT *RcvbLength )
{
UCHAR   rc = FALSE;

        if( Usbif.SqStep == USTEP_WAIT_START_IN )
        {
#ifdef CPU1
            *RcvbLength = Usbif.MbusRcvLength;
#endif
            rc = COM_ACK;
        }
        else
        {
            rc = ALL_NAK;
        }
        return( rc );
}

/**********************************************************************************************/
/* Function_Name: RpxInitUsbMsgInterface         */ 
/* Description  : USB通讯对应Modbus管理变量-初始化处理
                  USB通讯收发接口和modbus协议接口对接函数
                  调用：上电初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void    RpxInitUsbMsgInterface( void )
{

        MlibResetLONGMemory( &UsbMsg, sizeof( UsbMsg ) / 2 );   // USB消息管理变量复位

        UsbMsg.CmdBuf  = DriComGetRcvBufferAdr( COM1_USB );     // 通信端口接收buffer地址指针赋值
        UsbMsg.ResBuf  = DriComGetTrnsBufferAdr( COM1_USB );    // 通信端口发送buffer地址指针赋值
        UsbMsg.RcvBufSize = DriComGetRcvBufferSize( COM1_USB ); // 获取通信端口接收buffer大小
        UsbMsg.SndBufSize = DriComGetTrnsBufferSize( COM1_USB );// 获取通信端口发送buffer大小
        UsbMsg.StxFunc = NULL;                                  // 响应Message发送开始API函数
        UsbMsg.ResFunc = RpxSmsgFuncExecResponse;               // Fn执行结果响应Message处理函数
        UsbMsg.LstErrRno = 0xFFFF;                              // 上次异常寄存器编号
        UsbMsg.ErrRno  = 0xFFFF;                                // 异常寄存器编号
        UsbMsg.ComPortType = COM1_USB;                          // 通信信道类型设定：USB

        return;
}

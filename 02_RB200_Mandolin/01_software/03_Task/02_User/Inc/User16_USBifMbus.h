/*
 * User16_USBifMbus.h
 *
 *  Created on: 2019年08月12日
 *      Author: zhuxc
 */

#ifndef User16_USBifMbus_H
#define User16_USBifMbus_H

typedef	struct
{
	struct 
	{
	    USHORT	BlkInStart	:1;				// 发送开始请求
	    USHORT	BlkInSkip	:1;				// （在无应答的情况下）接收不发送
	    USHORT  BlkInFlag   :1;             // USB 数据接收标志
	    USHORT  USBRecFlag  :1;
	}f;
	USHORT	SqStep;							// 发送和接收的步骤
	USHORT	MbusRcvLength;					// MEMOBUS接收到的数据的长度（以字节为单位）
#ifdef CPU1
	USHORT	MbusTrnLength;					// MEMOBUS发送数据长度（以字节为单位）
	USHORT	InBuf[MBUS_TRN_MAXSIZEB];	    // 发送数据缓冲区
	USHORT  Axis2TimeOut;                   // 轴2超时
    USHORT  SkipTick;                       //
#endif
	USHORT  UsbRecLenth;
	USHORT  UsbAddr;
	USHORT  OutCmpWait;
	USHORT  Tick;                           // 收发心跳
} USBIF;
extern USBIF Usbif;

extern void DpiInitUsbMbusMsg( void );
extern void DpxUsbifMsgManager( void );
extern void	RpxUsbMsgManager( void );
extern UCHAR DpxSetUsbMbusTrnsStart( USHORT MsgLength, USHORT MsgType );
extern UCHAR DpxGetUsbMbusRcvACK( USHORT *RcvbLength );
extern void	RpxInitUsbMsgInterface( void );
#endif

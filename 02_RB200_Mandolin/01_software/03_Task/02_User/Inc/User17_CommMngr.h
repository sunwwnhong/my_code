/*
 * User17_CommMngr.h
 *
 *  Created on: 2017年08月05日
 *      Author: zhuxc
 */
#ifndef __User17_CommMngr_H__
#define __User17_CommMngr_H__


/****************************************************************************************************/
/*																									*/
/*		variable definition																	        */
/*																									*/
/****************************************************************************************************/
typedef struct	{
		USHORT	SerComMode;             /*	 < 串行通信模式:无、数字操作器、sigma >					*/
		ULONG	SerComTimeLong;         /*	 < 串行通信超时测量 >								    */
} RMNGV;
/*--------------------------------------------------------------------------------------------------*/
/*		Serial Modes (for SerComMode)																*/
/*--------------------------------------------------------------------------------------------------*/
#define  	NOCOM		0				/*< 无连接设  >  									        */
#define  	LCDCOM		1				/*< LCD操作   									            */
#define  	SMSGCOM  	2				/* < SigmaMessage機器 >							            */
/*--------------------------------------------------------------------------------------------------*/


//--------------------------------------------------------------------------------------------------
//		判断通信端口是否接收数据完毕函数DriComGetRcvComplete()的返回值定义
//--------------------------------------------------------------------------------------------------
#define	ALL_NAK			0x01				// 未接收(正常应答)
#define	COM_ACK			0x02				// 确认接收数据无误(正常应答)
//--------------------------------------------------------------------------------------------------
//		开始应答指令函数DriComSetTrnsStart()的输入参数
//--------------------------------------------------------------------------------------------------
#define	RESMT_COMPLETE		0x01			// MsgType : 消息处理完毕,开始应答
#define	RESMT_NORESPONSE	0x00			// MsgType : 消息异常,无需应答
//--------------------------------------------------------------------------------------------------
//		通信通道端口常量定义
//--------------------------------------------------------------------------------------------------
#define	COM0_UART		0x00				// CH0 : UART通信端口
#define	COM1_USB		0x01				// CH1 : USB通信端口
#define	COM2_OPT1		0x02				// CH2 : 选配模块通信端口1
#define	COM3_OPT2		0x03				// CH3 : 选配模块通信端口2
//--------------------------------------------------------------------------------------------------
//		函数返回值定义(低4位详细定义)
//--------------------------------------------------------------------------------------------------
#define	COMDEV_OK		0x00				// 正常应答						
#define	COMDEV_NG		0x10				// 异常应答：USB没有详细情报	
#define	COMDEV_NONPORT	0x20				// 异常应答：无此对象端口		
#define	COMDEV_UNDEF	0x30				// 异常应答：USB未定义异常		
#define	COMDEV_NGSIZE	0x40				// 异常应答：USB发送数据长度异常
#define	COMDEV_NGDATA	0x50				// 异常应答：サイズに関する異常	
#define	COMDEV_NGTIME	0x60				// 异常应答：USB发送时机异常	
#define	COMDEV_SETLOCK	0x70				// 异常应答：锁定设置异常	


extern MSGIF	SrlMsg;

extern void SerialMsgManager( void );
extern UCHAR DriComSetTrnsStart( UCHAR Channel, USHORT TrnsbLength, USHORT MsgType );
extern UCHAR	DpiComSetAxisNumber( UCHAR Channel, UCHAR AxisNumber );
extern void	LpxInitMsgInterface( void );
extern UCHAR	DriComGetRcvComplete( UCHAR Channel, USHORT *RcvbLength );
extern void	RpxSmsgFinishProcedure( HMSGIF Hmsg );
#endif

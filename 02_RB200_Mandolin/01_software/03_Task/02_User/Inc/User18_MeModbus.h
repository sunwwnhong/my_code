/*
 * User18_MeModbus.h
 *
 *  Created on: 2017Äê08ÔÂ05ÈÕ
 *      Author: zhuxc
 */



#ifndef __User18_MeModbus_H__
#define __User18_MeModbus_H__

#include "Main.h"





typedef struct	{
		USHORT	ErrReg;
} MBUSMNGV;

extern LONG	RpxSmsgCheckRecvMessage( HMSGIF Hmsg );
extern void	RpxSmsgMainProcedure( HMSGIF Hmsg );
extern void	RpxSmsgFuncExecResponse( HMSGIF Hmsg );

#endif

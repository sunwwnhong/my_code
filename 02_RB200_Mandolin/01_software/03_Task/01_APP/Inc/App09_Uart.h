/*
 * App09_Uart.h
 *
 *  Created on: 2022Äê7ÔÂ13ÈÕ
 *      Author: zhuxc
 */

#ifndef App09_Uart_H
#define App09_Uart_H

//GPIO37
#define Rx485_TxMODE()  HWREG( GPIODATA_BASE + GPIO_O_GPBSET )   = 1UL << 5;
#define Rx485_RxMODE()  HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR ) = 1UL << 5;


/*-------------------------------------------------------------------------------------------------*/

extern void InitCpu1_Uart( void );
extern void RS485MsgManager( void );
/*-------------------------------------------------------------------------------------------------*/


#endif


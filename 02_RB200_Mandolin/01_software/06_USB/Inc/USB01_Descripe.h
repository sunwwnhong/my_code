/*
 * USB01_Descripe.h
 *
 *  Created on: 2022Äê11ÔÂ22ÈÕ
 *      Author: zhuxc
 */

#ifndef USB01_Descripe_H
#define USB01_Descripe_H


/*-------------------------------------------------------------------------------------------------*/

//
// Included Files
//
#include <stdint.h>
#include <stdbool.h>
//#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
//#include "usb_ids.h"
#include "usbdevice.h"
#include "usbdbulk.h"

//
// Defines
//

//
// The size of the transmit and receive buffers used. 256 is chosen pretty
// much at random though the buffer should be at least twice the size of
// a maximum-sized USB packet.
//
#define BULK_BUFFER_SIZE 256

//
// Globals
//
extern tUSBBuffer g_sTxBuffer;
extern tUSBBuffer g_sRxBuffer;
extern tUSBDBulkDevice g_sBulkDevice;
extern uint8_t g_pui8USBTxBuffer[];
extern uint8_t g_pui8USBRxBuffer[];

//
// Function Prototypes
//
extern uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData);
extern uint32_t TxHandler(void *pvi32CBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData);

/*-------------------------------------------------------------------------------------------------*/


#endif

//*************************************************************************************************
//文件名:USB01_Descripe.c
//创建时间:2022.11.22
//版本说明:V1.0
//功能描述: USB 描述符
//*************************************************************************************************
#include "Main.h"
#include "USB01_Descripe.h"
//******************************************************************************
//
// The languages supported by this device.
//
//******************************************************************************
const uint8_t g_pui8LangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//******************************************************************************
//
// The manufacturer string.
//
//******************************************************************************
const uint8_t g_pui8ManufacturerString[] =
{
#if 0
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0, 's', 0,
    't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0, 's', 0,
#else
    (27 + 1) * 2,
    USB_DTYPE_STRING,
    'V', 0, 'E', 0, 'I', 0, 'C', 0, 'H', 0, 'I', 0, ' ', 0, 'E', 0, 'L', 0,
    'E', 0, 'C', 0, 'T', 0, 'R', 0, 'I', 0, 'C', 0, ' ', 0, 'C', 0, 'O', 0,
    'R', 0, 'P', 0, 'O', 0, 'R', 0, 'A', 0, 'T', 0, 'I', 0, 'O', 0, 'N', 0,
#endif
};

//******************************************************************************
//
// The product string.
//
//******************************************************************************
const uint8_t g_pui8ProductString[] =
{
#if 0
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'G', 0, 'e', 0, 'n', 0, 'e', 0, 'r', 0, 'i', 0, 'c', 0, ' ', 0, 'B', 0,
    'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0,
    'e', 0
#else
    2 + (19 * 2),
    USB_DTYPE_STRING,
    'V', 0, 'E', 0, 'I', 0, 'C', 0, 'H', 0, 'I', 0, ' ', 0, 'S', 0,
    'D', 0, '7', 0, '0', 0, '0', 0, ' ', 0, 'S', 0, 'E', 0, 'R', 0,
    'I', 0, 'E', 0, 'S', 0,
#endif
};

//******************************************************************************
//
// The serial number string.
//
//******************************************************************************
const uint8_t g_pui8SerialNumberString[] =
{
#if 0
    (8 + 1) * 2,
    USB_DTYPE_STRING,
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0
#else
    2 + (12 * 2),
    USB_DTYPE_STRING,
    '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0,
    '0', 0, '1', 0, '1', 0, 'C',
#endif
};

//******************************************************************************
//
// The data interface description string.
//
//******************************************************************************
const uint8_t g_pui8DataInterfaceString[] =
{
#if 0
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'B', 0, 'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'a', 0, 't', 0,
    'a', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0,
    'a', 0, 'c', 0, 'e', 0
#else
    2 + (14 * 2),
    USB_DTYPE_STRING,
    'U', 0, 'S', 0, 'B', 0, ' ', 0,'C', 0, 'D', 0, 'C', 0, ' ', 0,
    'C', 0, 'o', 0, 'n', 0, 'f', 0,'i', 0, 'g', 0,
#endif
};

//******************************************************************************
//
// The configuration description string.
//
//******************************************************************************
const uint8_t g_pui8ConfigString[] =
{
#if 0
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'B', 0, 'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'a', 0, 't', 0,
    'a', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0, 'g', 0,
    'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0
#else
    2 + (26 * 2),
    USB_DTYPE_STRING,
    'U', 0, 'S', 0, 'B', 0, ' ', 0,'C', 0, 'D', 0, 'C', 0, ' ', 0,
    'I', 0, 'n', 0, 't', 0, 'e', 0,'r', 0, 'f', 0, 'a', 0, 'c', 0,
    'e', 0,
#endif
};

//******************************************************************************
//
// The descriptor string table.
//
//******************************************************************************
const uint8_t *const g_ppui8StringDescriptors[] =
{
    g_pui8LangDescriptor,
    g_pui8ManufacturerString,
    g_pui8ProductString,
    g_pui8SerialNumberString,
    g_pui8DataInterfaceString,
    g_pui8ConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_ppui8StringDescriptors) /            \
                                sizeof(uint8_t *))

//******************************************************************************
//
// The bulk device initialization and customization structures. In this case,
// we are using USBBuffers between the bulk device class driver and the
// application code. The function pointers and callback data values are set
// to insert a buffer in each of the data channels, transmit and receive.
//
// With the buffer in place, the bulk channel callback is set to the relevant
// channel function and the callback data is set to point to the channel
// instance data. The buffer, in turn, has its callback set to the application
// function and the callback data set to our bulk instance structure.
//
//******************************************************************************
tUSBDBulkDevice g_sBulkDevice =
{
    0x1706,         //0x1cbe
    0x0700,         //0x0003
    500,
    USB_CONF_ATTR_SELF_PWR,
    USBBufferEventCallback,
    (void *)&g_sRxBuffer,
    USBBufferEventCallback,
    (void *)&g_sTxBuffer,
    g_ppui8StringDescriptors,
    NUM_STRING_DESCRIPTORS
};

//******************************************************************************
//
// Receive buffer (from the USB perspective).
//
//******************************************************************************
uint8_t g_pui8USBRxBuffer[BULK_BUFFER_SIZE];
uint8_t g_pui8RxBufferWorkspace[USB_BUFFER_WORKSPACE_SIZE];
tUSBBuffer g_sRxBuffer =
{
    false,                           // This is a receive buffer.
    RxHandler,                       // pfnCallback
    (void *)&g_sBulkDevice,          // Callback data is our device pointer.
    USBDBulkPacketRead,              // pfnTransfer
    USBDBulkRxPacketAvailable,       // pfnAvailable
    (void *)&g_sBulkDevice,          // pvHandle
    g_pui8USBRxBuffer,               // pi8Buffer
    BULK_BUFFER_SIZE                 // ui32BufferSize
};

//******************************************************************************
//
// Transmit buffer (from the USB perspective).
//
//******************************************************************************

uint8_t g_pui8USBTxBuffer[BULK_BUFFER_SIZE];
uint8_t g_pui8TxBufferWorkspace[USB_BUFFER_WORKSPACE_SIZE];
tUSBBuffer g_sTxBuffer =
{
    true,                            // This is a transmit buffer.
    TxHandler,                       // pfnCallback
    (void *)&g_sBulkDevice,          // Callback data is our device pointer.
    USBDBulkPacketWrite,             // pfnTransfer
    USBDBulkTxPacketAvailable,       // pfnAvailable
    (void *)&g_sBulkDevice,          // pvHandle
    g_pui8USBTxBuffer,               // pi8Buffer
    BULK_BUFFER_SIZE                 // ui32BufferSize
};


//
// End of file
//

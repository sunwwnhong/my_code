//*************************************************************************************************
//文件名:USB00_Main.c
//创建时间:2022.11.22
//版本说明:V1.0
//功能描述: USB 主函数
//*************************************************************************************************
#include "Main.h"
#include "USB00_Main.h"
#include "usb_hal.h"

//
// Defines
//
#define COMMAND_PACKET_RECEIVED 0x00000001
#define COMMAND_STATUS_UPDATE   0x00000002

tUSBMode g_eCurrentUSBMode;   // The current USB operating mode - Host, Device
                              // or unknown.

//******************************************************************************
//
// Globals
//
//******************************************************************************
static volatile bool g_bUSBConfigured = false; // Global flag indicating that a
                                               // USB configuration has been
                                               // set.



//*************************************************************************************************
// ModeCallback - USB Mode callback
//
// \param ui32Index is the zero-based index of the USB controller making the
//        callback.
// \param eMode indicates the new operating mode.
//
// This function is called by the USB library whenever an OTG mode change
// occurs and, if a connection has been made, informs us of whether we are to
// operate as a host or device.
//
// \return None.
//
//*************************************************************************************************
void ModeCallback(uint32_t ui32Index, tUSBMode eMode)
{
    //
    // Save the new mode.
    //
    g_eCurrentUSBMode = eMode;
}


//*************************************************************************************************
//
//    USB 初始化
//
//*************************************************************************************************
void CPU1_USBInit( void )
{
    //
    // Set the clocking to run from the PLL at 60MHz
    //
    //SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG_USB);

    //
    // Not configured initially.
    //
    g_bUSBConfigured = false;

    //
    // Enable the GPIO peripheral used for USB, and configure the USB
    // pins.
    //
    USBGPIOEnable();

    //
    // Register the interrupt handler for USB Interrupts.
    //
    Interrupt_register(INT_USBA, f28x_USB0DeviceIntHandler);

    //
    // Initialize the transmit and receive buffers.
    //
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);

    USBStackModeSet(0, eUSBModeForceDevice, ModeCallback);

    //
    // Pass our device information to the USB library and place the device
    // on the bus.
    //
    USBDBulkInit(0, &g_sBulkDevice);
}

//*************************************************************************************************
//
// USB 数据发送处理
//
//*************************************************************************************************
void UsbDataSend( USHORT Axis )
{
    tUSBRingBufObject sTxRing;
    uint_fast32_t ui32WriteIndex;
    uint_fast16_t i;
    uint_fast16_t len;
    //
    // Get the current buffer information to allow us to write directly to
    // the transmit buffer (we already have enough information from the
    // parameters to access the receive buffer directly).
    //
    USBBufferInfoGet(&g_sTxBuffer, &sTxRing);

    ui32WriteIndex = sTxRing.ui32WriteIndex;

    if( Axis == 0 )
    {
        len = Usbif.MbusTrnLength;
        for( i = 0; i < len;i ++ )
        {
            g_pui8USBTxBuffer[ui32WriteIndex] = Usbif.InBuf[ i ];
            ui32WriteIndex ++;
            ui32WriteIndex = (ui32WriteIndex == BULK_BUFFER_SIZE) ? 0 : ui32WriteIndex;
        }
    }
    else
    {
        len = UsbTrsBuf.MbusTrnLength;
        for( i = 0; i < len;i ++ )
        {
            g_pui8USBTxBuffer[ui32WriteIndex] = UsbTrsBuf.TransBuf[ i ];
            ui32WriteIndex ++;
            ui32WriteIndex = (ui32WriteIndex == BULK_BUFFER_SIZE) ? 0 : ui32WriteIndex;
        }
    }

    USBBufferDataWritten(&g_sTxBuffer, len);
}

//*************************************************************************************************
//
// EchoNewDataToHost - Receive new data and echo it back to the host.
//
// \param psDevice points to the instance data for the device whose data is to
// be processed.
// \param pi8Data points to the newly received data in the USB receive buffer.
// \param ui32NumBytes is the number of bytes of data available to be processed.
//
// This function is called whenever we receive a notification that data is
// available from the host. We read the data, byte-by-byte and swap the case
// of any alphabetical characters found then write it back out to be
// transmitted back to the host.
//
// \return Returns the number of bytes of data processed.
//
//*************************************************************************************************
static uint32_t ReadUsbBuff(tUSBDBulkDevice *psDevice, uint8_t *pi8Data,uint_fast32_t ui32NumBytes)
{
    uint_fast32_t ui32Loop, ui32Count;
    uint_fast32_t ui32ReadIndex;
    uint16_t RecNum = 0;
    uint16_t RecDataTmp = 0;

    //
    // How many characters can we process this time round?
    //
    ui32Loop = ui32NumBytes;//(ui32Space < ui32NumBytes) ? ui32Space : ui32NumBytes;
    ui32Count = ui32Loop;

    //
    // Set up to process the characters by directly accessing the USB buffers.
    //
    ui32ReadIndex = (uint32_t)(pi8Data - g_pui8USBRxBuffer);

    while(ui32Loop)
    {
        //
        // Copy from the receive buffer
        //
        RecDataTmp = (g_pui8USBRxBuffer[ui32ReadIndex] & 0x00FF);

//        Usbif.OutBuf[ Usbif.MbusDataLen + RecNum ] = RecDataTmp;

        UsbRecBuf.ReciveBuf[ Usbif.UsbRecLenth + RecNum] = RecDataTmp;

        RecNum ++;
        ui32ReadIndex++;
        ui32ReadIndex = (ui32ReadIndex == BULK_BUFFER_SIZE) ? 0 : ui32ReadIndex;

        ui32Loop--;
    }

    Usbif.f.BlkInFlag = 1;
    Usbif.UsbRecLenth += ui32NumBytes;

    if( OpeReg.EepromErStatus == 1 )
    {
        Usbif.UsbRecLenth = 0;
        Usbif.f.BlkInFlag = 0;
    }

    return(ui32Count);
}

//*************************************************************************************************
//
// TxHandler - Handles bulk driver notifications related to the transmit
//             channel (data to the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
//*************************************************************************************************
uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData)
{
    //
    // We are not required to do anything in response to any transmit event
    // in this example. All we do is update our transmit counter.
    //

    return(0);
}

//*************************************************************************************************
//
// Handles bulk driver notifications related to the receive channel (data from
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
//*************************************************************************************************
uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData)
{
    //
    // Which event are we being sent?
    //
    switch(ui32Event)
    {
        //
        // We are connected to a host and communication is now possible.
        //
        case USB_EVENT_CONNECTED:
        {
            g_bUSBConfigured = true;
//            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            //
            // Flush our buffers.
            //
            USBBufferFlush(&g_sTxBuffer);
            USBBufferFlush(&g_sRxBuffer);

            break;
        }
        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bUSBConfigured = false;
//            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            break;
        }

        //
        // A new packet has been received.
        //
        case USB_EVENT_RX_AVAILABLE:
        {
            tUSBDBulkDevice *psDevice;

            //
            // Get a pointer to our instance data from the callback data
            // parameter.
            //
            psDevice = (tUSBDBulkDevice *)pvCBData;

            //
            // Read the new packet and echo it back to the host.
            //
            return(ReadUsbBuff(psDevice, pvMsgData, ui32MsgValue));
        }

        //
        // Ignore SUSPEND and RESUME for now.
        //
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
            break;

        //
        // Ignore all other events and return 0.
        //
        default:
            break;
    }

    return(0);
}

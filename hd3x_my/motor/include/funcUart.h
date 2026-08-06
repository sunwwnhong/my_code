
#ifndef _FUNC_UART_H_
#define _FUNC_UART_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "f_comm.h"
#include "m_interfaceModify.h"
#include "afe.h"

#define SCIA_RE             (GpioDataRegs.GPACLEAR.bit.GPIO26 = 1)
#define SCIA_DE             (GpioDataRegs.GPASET.bit.GPIO26 = 1)
#define SCIB_RE             (GpioDataRegs.GPACLEAR.bit.GPIO27 = 1)
#define SCIB_DE             (GpioDataRegs.GPASET.bit.GPIO27 = 1)
#define SCIC_RE             (GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1)
#define SCIC_DE             (GpioDataRegs.GPBSET.bit.GPIO61 = 1)

#define SCI_TIMEOUT         5 // + 5 // 2.5ms + 2.5ms
#define SCI_SEND_WAIT       3 // + 3 // 1.5ms + 1.5ms
#define SCI_RCV_FREME_SIZE  16

#define COMM_RECT_ADDR0     0x2005 // 四象限整流控制
#define COMM_RECT_ADDR1     0x2006 // 四象限整流控制
#define COM_ID_252          252

struct SCIA_DATA
{   
	// Recive
    Uint16 rcvFrame[SCI_RCV_FREME_SIZE];
    Uint16 rcvOver;
    Uint16 rcvCount;
    Uint16 rcvTimeout;
    // Send
    Uint16 sndFrame[72]; // Min = 72
    Uint16 sndOver;    
    Uint16 sndCount;  
    Uint16 sndIndex; 
    Uint16 sndWait;
};
extern struct SCIA_DATA SciAData;

struct SCIB_DATA
{   
	// Recive
    Uint16 rcvFrame[SCI_RCV_FREME_SIZE];
    Uint16 rcvOver;
    Uint16 rcvCount;
    Uint16 rcvTimeout;
    // Send
    Uint16 sndFrame[72]; // Min = 72
    Uint16 sndOver;    
    Uint16 sndCount;  
    Uint16 sndIndex; 
    Uint16 sndWait;
};
extern struct SCIB_DATA SciBData;
extern struct SCIB_DATA SciCData;

extern const Uint32 CommBaud[];
extern Uint16 SCI_Baud;
extern Uint16 SCI_Timeout;
extern Uint16 SCI_SendWait;

/////////////////////////////////////////////////////////// LS_20211220
extern Uint16 frq2Core;
extern Uint16 speedMotor;
extern Uint16 encoderFdb;
extern Uint16 generatrixVoltage;
extern Uint16 outCurrent;
extern union CORE_TO_FUNC_DATA c2fData;
extern union DSP_STATUS coreStatus;
extern Uint16 CrcValueByteCalc(const Uint16 *, Uint16);

extern Uint16 CommPCenable;
extern Uint32 ChannelSelect;

typedef union
{
    Uint16   Data[6];
    Uchar    Buf[12];
} TChannelData;

extern TChannelData ChannelData[];
extern Uint16 ChannelIndex;
extern Uint16 SwapCmd;
extern Uint16 MSCommError;
extern Uint16 HMICmd;
extern Uint16 sysStatus;
extern Uint16 AFECmd;
extern Uint16 AFEStatus;
extern Uint16 SwapRes;
extern Uint16 ModbusFunc;

extern void CommOsc2ms(void);
///////////////////////////////////////////////////////////

extern void SCIA_Init(Uint32, Uint16);
extern void SCIA_RecvProc(void);

extern void SCIB_Init(Uint32, Uint16);
extern void SCIB_RecvProc(void);

extern void SCIC_Init(Uint32, Uint16);
extern void SCIC_RecvProc(void);

extern void SCI_Safeguard(void);
extern void SCI_SendCmd(Uint16, Uint16);
extern void CommAFE2ms(void);

#endif /* _FUNC_UART_H_ */

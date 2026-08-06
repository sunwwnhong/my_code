
#ifndef _FUNC_CAN_H_
#define _FUNC_CAN_H_


#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"


#define EXT_ID          0x80000000L
#define HOST_ID         0x0CFF0008L
#define SLAVE_ID        0x0CFF0109L
#define MBOX_BUF_CNT    4

typedef struct
{
    Uint16 BRPREG;
    Uint16 TSEG2REG;
    Uint16 TSEG1REG;
} ECAN_BAUD_T;

typedef struct
{
    union CANMDL_REG Lo4Byte;
    union CANMDL_REG Hi4Byte;
    union CANMSGID_REG MsgID;
} ECAN_RX_BUF_T;

extern volatile Uint16 Mbox_rIdx;
extern volatile Uint16 Mbox_wIdx;
extern ECAN_RX_BUF_T Mbox_RxBuf[];

extern void CANA_Init(Uint16);
extern void CanASend(Uint32, Uint16, Uint32, Uint32);

#endif /* _FUNC_CAN_H_ */

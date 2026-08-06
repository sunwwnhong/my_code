#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include "socket.h"
#include "w5500.h"
#include "w5500_conf.h"
#include "main.h"

struct STATUS_BITS
{
    Uint16 init :1;         // 0        W5500 Init
    Uint16 busy :1;         // 1        OSC UDP Sending
    Uint16 wIndex :2;       // 2:3      Write buffer index
    Uint16 rIndex :2;       // 4:5      Read buffer index
    Uint16 active :2;       // 6:7      Active ethernet
    Uint16 step :4;         // 8:11     Run step
    Uint16 tcpLink :1;      // 12       TCP Linked
    Uint16 rsvd :3;         // 13:15    reserved
};

union ETH_STATUS
{
    Uint16 all;
    struct STATUS_BITS bit;
};

#define TCP_LINK_CHK_TMR    2500 // 5000ms

//#define EN_TIMING

/* DATA_BUF_SIZE define for Loopback example */
#ifndef DATA_BUF_SIZE
#define DATA_BUF_SIZE       1472 // 2048
#endif

#define OSC_START_CMD       0xAA
#define IDX_CMD             0
#define IDX_CHAN0           1
#define IDX_CHAN1           2
#define IDX_CHAN2           3
#define IDX_CHAN3           4
#define IDX_CHAN4           5
#define IDX_CHAN5           6

#define MAX_CHAN_NUM        6

#define DSP_CONDITION_TRIGGER_NUM   6   // DSP 6个通道
#define FAST_LOOP_NUM               12  // 快环每 2ms 传递过来的数据个数最大值

extern Uint16 sampleFastNum;
extern Uint16 sampleFastD[DSP_CONDITION_TRIGGER_NUM][FAST_LOOP_NUM];

extern Uint16 DBGCmd;
extern union ETH_STATUS ETH_Status;
extern Uint16 ETH_Timerout;
extern Uint16 ModbusFunc;

extern void CpuTimerSample(Uint16);

/* App */
extern void OSC_DataUpdate(void);
extern void funcEthernet(void);

/* TCP server */
extern void do_tcp_server(void);
extern void do_tcp_server_listen(void);

/* UDP */
extern void do_udp(void);
extern void do_osc(void);

/* Init */
extern void EthernetInit(void);

#endif

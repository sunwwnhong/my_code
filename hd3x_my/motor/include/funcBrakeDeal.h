//----------------------------------------------------------//
// File Name		: funcBrakeDeal.c	
// Description		: 输出制动电阻柜控制
// Time				: 2017.3.7
// Editor			: xxxxxxxxxx
// Co.				: xxxxx
//----------------------------------------------------------//
#ifndef __F_FUNC_BRAKE_DEAL_H__
#define __F_FUNC_BRAKE_DEAL_H__

extern void BrakeCanbinetDeal(void);
extern void BrakeContactorDeal(void);

struct BRAKE_CANBINET_STATUS_BITS
{
    Uint16 fanStatus:1;         // 0 -- 风扇理论状态
    Uint16 contactorFdb:1;      // 1 -- 接触器理论状态
    Uint16 resBrakeOverTime:1;  // 2 -- 制动电阻接入超时故障

    Uint16 fcbResOverTemp:1;    // 3 制动电阻柜电阻超温
    Uint16 fcbFanErr:1;         // 4 制动电阻柜风机故障
    Uint16 fcbConErr:1;         // 5 制动柜接触器异常
    Uint16 fcbRollBack:1;       // 6 FCB状态不做速度控制
    
    Uint16 rsvd:9;              // 7-15 保留
};

union BRAKE_CANBINET_STATUS
{
    Uint16 all;
    struct BRAKE_CANBINET_STATUS_BITS bit;
};
extern union BRAKE_CANBINET_STATUS brakeStatus;

enum BRAKE_PROCESS_STATUS
{
    BRAKE_NONE,             // 0 无FCB制动
    BRAKE_ENERGY_CONSUMP,   // 2 能耗制动
    BRAKE_DUAL_FRQ         // 3 叠频制动
};
extern enum BRAKE_PROCESS_STATUS brakeProcSta;


#endif 

// END

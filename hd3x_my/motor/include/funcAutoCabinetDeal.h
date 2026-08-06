#ifndef __F_AUTO_CABINET_DEAL_H__
#define __F_AUTO_CABINET_DEAL_H__

extern void AutoBypassCabinetContactorControl(void);
extern void CanbinetFdbOffLine(void);
extern void CanbietStatusInit(void);

struct CANBINET_FDB_ABNORMAL_BITS
{
    Uint16 lineContAbn:1;       // 0  -- 工频接触器异常
    Uint16 inletContAbn:1;      // 1  -- 进线接触器反馈异常
    Uint16 outletContAbn:1;     // 2  -- 出现接触器反馈异常

    Uint16 rsvd:11;             // 3 - 15 保留
    
};

union CANBINET_FDB_ABNORMAL
{
    Uint16 all;
    struct CANBINET_FDB_ABNORMAL_BITS bit;
};

extern union CANBINET_FDB_ABNORMAL canbiFdbAbn;


struct CANBINET_CONTACTOR_STATUS_BIT
{
    Uint16 inletCon1Sta:1;             // 0 0-进线接触器1断开 1-进线接触器1闭合
    Uint16 outletCon1Sta:1;            // 1 0-出线接触器1断开 1-出线接触器1闭合
    Uint16 inletCon2Sta:1;             // 2 0-进线接触器2断开 1-进线接触器2闭合
    Uint16 outletCon2Sta:1;            // 3 0-出线接触器2断开 1-出线接触器2闭合
    
    Uint16 rsvd:12;                    // 15:4
};
union CANBINET_CONTACTOR_STATUS
{
    Uint16  all;
    struct CANBINET_CONTACTOR_STATUS_BIT bit;
};
extern union CANBINET_CONTACTOR_STATUS canbiConStatus;

#endif


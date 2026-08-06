
#ifndef __F_ERROR_FLAG_H__
#define __F_ERROR_FLAG_H__

// ----------------函数声明---------------------------------------------- 
extern void ErrorDeal(void);        //故障处理
extern void ErrorReset(void);       //故障复位
extern Uint16 GetErrorAttribute(Uint16 errCode);
// ----------------函数声明结束------------------------------------------

extern Uint16 errorOther;
extern Uint16 errorCode;

//--------------------------故障子码--------------------------
#define ERROR_OTHER_INFO_NONE           0       // 故障不含故障子码
// 预充故障-故障子码
#define PRECHARGE_NONE_FAULT            0       // 预充过程无故障
#define CELL_UDC_LOW                    1       // 预充过程中单元母线电压偏低
#define INPUT_VOLTAGE_LOW               2       // 预充过程中整机输入电压偏低
#define VACUUM_FDB_FAULT                5       // 预充接触器反馈异常
#define BYPASS_FDB_FAULT                6       // 电阻旁路接触器反馈异常

#define INPUT_CURRENT_FAULT             10      // 二次预充过程中有输入电流
#define VOL_REGULATOR_FAULT             11      // 二次预充调压器故障
#define LV_FDB_FAULT                    12      // 二次预充接触器反馈异常
#define LV_BYP_RES_FDB_FAULT            13      // 二次预充旁路电阻接触器反馈异常

#define HV_AT_TESTMODE                  20      // 测试模式上高压故障 // LS_20240229

#define CELL_UDC_LOW_STEP2              100     // 凯撒四象限 电阻旁路后单元母线电压偏低

//CM3000 输入过压-故障子码
#define GENERATRIX_VOL_OVER             1       // 停机状态下母线采样超过A5-25 ALARM7-报警
#define INPUT_VOL_OVER                  2       // 输入电压超过F9-44的阈值，报故障停机
//--------------------------END--------------------------------

// 故障信息
// 更改故障代码时需要注意故障的动作选择处理部分 有些不连续故障的处理可能会导致溢出
#define ERROR_NONE                      0       // 0  -- 无
#define ERROR_INVERTER_UNIT             1       // 1  -- 逆变单元保护
#define ERROR_OC_ACC_SPEED              2       // 2  -- 加速过电流
#define ERROR_OC_DEC_SPEED              3       // 3  -- 减速过电路
#define ERROR_OC_CONST_SPEED            4       // 4  -- 恒速过电流
#define ERROR_OV_ACC_SPEED              5       // 5  -- 加速过电压
#define ERROR_OV_DEC_SPEED              6       // 6  -- 减速过电压
#define ERROR_OV_CONST_SPEED            7       // 7  -- 恒速过电压
#define ERROR_BUFFER_RES                8       // 8  -- 缓冲电阻过载故障
#define ERROR_UV                        9       // 9  -- 欠压故障

#define ERROR_OL_INVERTER               10      // 10 -- 变频器过载
#define ERROR_OL_MOTOR                  11      // 11 -- 电机过载
#define ERROR_LOSE_PHASE_INPUT          12      // 12 -- 输入缺相
#define ERROR_LOSE_PHASE_OUTPUT         13      // 13 -- 输出缺相
#define ERROR_OT_IGBT                   14      // 14 -- 散热器过热
#define ERROR_EXTERNAL                  15      // 15 -- 外部故障
#define ERROR_COMM                      16      // 16 -- 通讯(超时)故障
#define COMM_ERROR_MODBUS               131     // 131 --MODBUS 通信故障
#define ERROR_CONTACTOR                 17      // 17 -- 接触器故障
#define ERROR_CURRENT_SAMPLE            18      // 18 -- 电流检测故障
#define ERROR_TUNE                      19      // 19 -- 电机调谐故障

#define ERROR_ENCODER                   20      // 20 -- 码盘故障
#define ERROR_EEPROM                    21      // 21 -- EEPORM读写故障
#define ERROR_22                        22      // 22 -- 变频器硬件故障
#define ERROR_MOTOR_SHORT_TO_GND        23      // 23 -- 电机对地阻抗偏小故障
#define ERROR_24                        24      // 24 -- 电机励磁故障
#define ERROR_25                        25      // 25 -- 电机过热
#define ERROR_RUN_TIME_OVER             26      // 26 -- 运行时间到达
#define ERROR_USER_1                    27      // 27 -- 用户自定义故障1
#define ERROR_USER_2                    28      // 28 -- 用户自定义故障2
#define ERROR_POWER_ON_TIME_OVER        29      // 29 -- 上电时间到达

#define ERROR_LOSE_LOAD                 30      // 30 -- 掉载
#define ERROR_FDB_LOSE                  31      // 31 -- 运行时PID反馈丢失
#define ERROR_32                        32      // 32 -- 输入阻抗偏小故障-DSP
#define ERROR_INV_CONTACT_FDB           33      // 33 -- 保留  //变频接触器反馈异常故障
#define ERROR_FORMER_OVERLOAD           34      // 34 -- 输入变压器过载
#define ERROR_IDLECURRENT_ABNORMAL      35      // 35 -- 变压器空载电流异常
#define ERROR_INCURRENT_NO_BALANCE      36      // 36 -- 输入电流不对称
#define ERROR_INVOLTAGE_OVER_LIMIT      37      // 37 -- 输入高压超限
#define ERROR_OUTCURRENT_NO_BALANCE     38      // 38 -- 输出电流不对称
#define ERROR_PLC                       39      // 39 -- 内部plc通讯

#define ERROR_AFE_GENVOL                40      // 40 -- AFE整流未运行故障
#define ERROR_SWITCH_MOTOR_WHEN_RUN     41      // 41 -- 运行时切换电机
#define ERROR_DEV                       42      // 42 -- 速度偏差过大
#define ERROR_OS                        43      // 43 -- 电机超速度
#define ERROR_PRECHARGE                 44      // 44 -- 预充故障
#define ERROR_MOTOR_OT                  45      // 45 -- 电机过温故障
#define ERROR_CONTROL_POWER             46      // 46 -- 控制电源异常
#define ERROR_IO_POWER                  47      // 47 -- IO板电源异常
#define ERROR_ARM_DSP_DATA              48      // 48 -- 交互数据错误
//#define ERROR_REVFWD_ALL                49      // 49 -- 正反转同时有效
#define ERROR_WATER_COOLING_SYS         49      // 49 -- 水冷系统故障

#define ERROR_BRAKE_FDB                 50      // 50 -- 抱闸反馈故障
#define ERROR_INIT_POSITION             51      // 51 -- 磁极位置检测失败
#define ERROR_DP_PLC                    52      // 52 -- DP卡通讯故障
#define ERROR_UVW_FDB                   53      // 53 -- uvw信号反馈错误
#define ERROR_EXCITATION                54      // 54 -- 励磁柜故障
#define ERROR_OV_MOTOR                  55      // 55 -- 电机过压
#define ERROR_INSPECT_TIME_ARRIVE       56      // 56 -- 检修时间到达
#define ERROR_OVER_TEMP                 57      // 57 -- 变压器过热
#define ERROR_DOOR_LIMIT                58      // 58 -- 门限位异常
#define ERROR_WIND_MOTOR                59      // 59 -- 风机故障

// -- 单元故障在60到79之间 不可随意用或更改 -- //
#define ERROR_CELL_START                60
#define ERROR_CELL_END                  79

#define ERROR_CELL                      60      // 60 -- 单元故障
#define ERROR_CELL_LINK                 61      // 61 -- 单元通讯故障
#define ERROR_CELL_BLOCK                62      // 62 -- 单元block测试故障
#define ERROR_CELL_OOS                  63      // 63 -- 单元过流故障
#define ERROR_CELL_LOSE_IN				64      // 64 -- 单元输入缺相
#define ERROR_CELL_CAP_SHARE            65      // 65 -- 单元均压故障
#define ERROR_CELL_OVER_VOL             66      // 66 -- 单元过压故障
#define ERROR_CELL_RSVD					67      // 67 -- 保留   //单元其他故障
#define ERROR_CELL_OVER_TEMP            68      // 68 -- 单元过温故障
#define ERROR_CELL_UNDER_VOL            69      // 69 -- 单元欠压故障
#define ERROR_CELL_BYPASS               70      // 70 -- 单元旁路接触器
#define ERROR_CELL_DRIVE_POWER          71		// 71 -- 单元驱动电源故障
#define ERROR_CELL_FUSE                 72      // 72 -- 单元熔丝故障
#define ERROR_AFE                       73      // 73 -- AFE故障
#define ERROR_CELL_BUS_LIMIT_OV			74		// 74 -- 单元母线超限  跳高压
#define ERROR_CELL_DISCHARGE			75		// 75 -- 单元放电故障
#define ERROR_CELL_SAMPLE_BOARD         76      // 76 -- 单元采样板故障
#define ERROR_CELL_BRAKERES             77      // 77 -- 制动电阻故障

//------------------报警-----------------//
#define DEFINE_ALARM_START              80
#define DEFINE_ALARM_END                89
#define ALARM_CELL_OVER_TEMP            80      // 80 -- 单元温度报警
#define ALARM_CELL_LOSE_IN              81      // 81 -- 单元输入缺相
#define ALARM_AI_OFF                    82      // 82 -- 模拟量断线
#define ALARM_BYPASS                    83      // 83 -- 单元旁路报警
#define ALARM_TRANSFER					84      // 84 -- 同步切换报警
#define ALARM_PREOL_INVERTER            85      // 85 -- 变频器预过载
#define ALARM_PREOL_MOTOR               86      // 86 -- 电机预过载
#define ALARM_OVER_TEMP                 87      // 87 -- 过温报警
#define ALARM_CROSS_CURRENT_WIND_MOTOR  88      // 88 -- 横流风机报警
#define ALARM_WIND_MOTOR                89      // 89 -- 风机报警
//-------------------算法故障------------//
#define ERROR_PG_PARA_ERROR             90      // 90 -- 编码器线数设定错误 
#define ERROR_PG_LOST                   91      // 91 -- 未接编码器
#define ERROR_FORMER_BAD_INSULATION     93      // 93 -- 变压器副边绝缘下降
#define ERROR_EXCESSIVE_DRIVE_LOSSES    97      // 97 -- 变频器损耗过大
#define ERROR_PROGRAM_LOGIC             99      // 99 -- 程序执行逻辑错误

#define ERROR_INVOLTAGE_NO_BALANCE      120     // 120 -- 输入电压不平衡
#define ERROR_OUTVOLTAGE_NO_BALANCE     121     // 121 -- 输出电压不平衡
#define ERROR_RSVD122                   122     // 122 -- 保留
#define ERROR_MOTOR_STALL               123     // 123 -- 电机堵转故障
#define ERROR_MOTOR_DIAGNOSE            124     // 124 -- 机侧自检故障
#define ERROR_STS_REVERSE_POWER         125     // 125 -- 逆功率保护故障 -- 岸电专有故障
#define ERROR_CELL_INPUT_ABNORMAL       126     // 126 -- 单元输入缺相故障
#define ERROR_STS_FREQUECY              127     // 127 -- 频率异常       -- 岸电专有故障
#define ERROR_STS_OUT_UV                128     // 128 -- 输出欠压故障   -- 岸电专有故障
#define ERROR_CELL_BYPASS_FAIL          129     // 129 -- 单元旁路失败故障
#define ERROR_OUT_FLITER_C_SHORT        130     // 130 -- 输出滤波电容短路故障(岸用电源)

//------------------HD33-----------------//
#define ERROR_SILICON                   100     // 100 - 可控硅故障
#define ERROR_3X_IGBT                   101     // 101 - IGBT故障
#define ERROR_DISCHARGE					102     // 102 - 放电
#define ERROR_POWER_UDC_CREAT_OT        103     // 103 - 母线电压建立超时
#define ERROR_POS_NEG_POWER_DEV         104     // 104 - 正负母线偏差过大
#define ERROR_SAMPLE_BOARD              106     // 106 - 采样板异常 fpga 
#define ERROR_HALF_GENVOL_OVER          108     // 108 - 母线电压超限 高压跳闸
#define ERROR_INPUT_OV                  109     // 109 - 用户输入过电压

//-------------------功能故障------------//

#define ERROR_PARALELL_FIBER1           151     // 151 -- 并联光纤1故障
#define ERROR_PARALELL_FIBER2           152     // 152 -- 并联光纤2故障
#define ERROR_PARALELL_FIBER3           153     // 153 -- 并联光纤3故障
#define ERROR_MASTER_SLAVE              154     // 154 -- 主从机故障

#define ERROR_SLAVE1_NOT_RUN            155     // 155 -- 从机故障 // LS_20240229
#define ERROR_SLAVE2_NOT_RUN            156     // 156 -- 废弃 // LS_20240229
#define ERROR_MSCOMM_ERROR              157     // 157 -- 四象限联动故障 // LS_20220325
#define ERROR_SCR_ERROR                 158     // 158 -- 晶闸管故障 // LS_20220429

#define ERROR_INPUTVOL                  160     // 160 -- 输入电压异常故障
#define ERROR_REACTOR_OVER_TEMP         161     // 161 -- 电抗器过温故障
#define ERROR_BACK_EMF_TIMEOUT          162     // 162 -- 反电势衰减超时故障
#define ERROR_TRANSFER_TIMEOUT          163     // 163 -- 切换超时故障
//#define ERROR_MULTI_CELL_OVER_VOL       164     // 164 -- 多单元过压异常
#define ERROR_HEAT_FAN                  165     // 165 -- 散热风机故障
#define ERROR_BRAKE_KNIFE_SWITCH        166     // 166 -- 制动电阻柜刀闸反馈异常
#define ERROR_CANBINET_POWER_OFF        167     // 167 -- 开关柜电源异常

//-------------------隔离变压器故障------------//
#define ERROR_TRANSFORMER_OT            170     // 170 -- 隔离变压器过温故障
#define ERROR_TRANSFORMER_TOP_FAN       171     // 171 -- 隔离变压器柜顶风机故障
#define ERROR_TRANSFORMER_FLOW_FAN      172     // 172 -- 隔离变压器横流风机故障
#define ERROR_TRANSFORMER_LIMIT_SWITCH  173     // 173 -- 隔离变压器门限位开关状态异常

#define ERROR_OUT_CONTACTOR_STATUS      174     // 174 -- 输出接触器状态冲突(岸用电源)
#define ERROR_OUT_PRE_CONTACTOR_STATUS  175     // 175 -- 输出预充接触器状态冲突(岸用电源)
#define ERROR_OUT_PRE_CONTACTOR_OV_TEMP 176     // 176 -- 输出预充电阻温度过高(岸用电源)

#define ERROR_OUT_FILTER_LCL_OT         177     // 177 -- 输出滤波柜电抗器过温故障
#define ERROR_OUT_PRE_POWER_STATUS      178     // 178 -- 输出预充柜电源状态异常

//------------------报警2-----------------//
#define DEFINE_ALARM_START2             180
#define DEFINE_ALARM_END2               199

#define ALARM_BYPASS_CABINET			180     // 180 -- 自动旁路柜接触器报警
#define ALARM_INSAMPLE_WIRING           181     // 181 -- 输入采样接线错误
#define ALARM_CELL_BYPASS_CONTACTOR     182     // 182 -- 单元旁路接触器报警
#define ALARM_REACTOR_CONTACT           183     // 183 -- 电抗器旁路接触器报警
#define ALARM_MOTOR_EXCITATION          184     // 184 -- 电机励磁报警
#define ALARM_CELL_LINK                 185     // 185 -- 单元通讯不良
#define ALARM_LVRT                      186     // 186 -- 输入电压跌落报警
#define ALARM_SAMPLEBOARD               187     // 187 -- 温湿度采样板断线短路报警
#define ALARM_SAMPLE_BOARD_COM          188     // 188 -- 温湿度采样板通信异常

#define ALARM_TRANSFORMER_OT            189     // 189 -- 隔离变压器过温报警
#define ALARM_OUT_PRE_CONTACTOR_AL_TEMP 190     // 190 -- 输出预充电阻温度告警(岸用电源)
#define ALARM_FCB_RES_OVTEMP            191     // 191 -- 快速制动电阻过温
#define ALARM_FCB_FAN                   192     // 192 -- 快速制动风机反馈异常
#define ALARM_BRAKE_CONTACTOR           193     // 193 -- 制动电阻柜接触器反馈异常
#define ALARM_OUT_FILTER_LCL_OT         194     // 194 -- 输出滤波柜电抗器过温告警

//---------------------------------------------------------
#define ERROR_LEVEL_NO_ERROR                0   // 无故障
#define ERROR_LEVEL_HIGHVOL_DISJUCTION      1   // 故障，高压紧急分断
#define ERROR_LEVEL_FREE_STOP               2   // 故障，自由停车
#define ERROR_LEVEL_STOP                    3   // 故障，减速停车(按功能码停车)
#define ERROR_LEVEL_RUN                     4   // 故障，继续运行
#define ERROR_LEVEL_LOW                     5   // 无故障等级


#define ERROR_ENCODER_FREE_STOP         0   // 编码器故障，自由停车
#define ERROR_ENCODER_CHANGE_SVC1       2   // 编码器故障，切换为SVC1
#define ERROR_ENCODER_CHANGE_SVC2       4   // 编码器故障，切换为SVC2


struct ERROR_ATTRIBUTE_BITS
{
    Uint16 reset:1;     // 复位方式，0-必须手动复位，1-自动复位
    Uint16 level:3;     // 000-无故障，001-自由停车，010-按停机方式停机，011-继续运行，
};
union ERROR_ATTRIBUTE
{
    Uint16 all;
    struct ERROR_ATTRIBUTE_BITS bit;
};

extern union ERROR_ATTRIBUTE errorAttribute;

// 指定故障使能选择
struct SPEC_FAULT_ENABLE_BITS
{
	Uint16 fibreFault:1;            // 0 - 单元通讯故障自动复位后重启
	Uint16 currentOv:1;             // 1 - 整机过流故障 即F02/F03/F04

	Uint16 rsvd:14;                 // 2-15 保留
};

union SPEC_FAULT_ENABLE
{
    Uint16 all;
    struct SPEC_FAULT_ENABLE_BITS bit;
};
extern union SPEC_FAULT_ENABLE specFaultEnable;
/****************************************************
 * 故障时时间记忆
 *    上电时间、运行时间
****************************************************/
struct CUR_TIME
{
    Uint16 runTimeM;        // 运行时间-分
    Uint16 runTimeSec;      // 运行时间-秒

    Uint16 powerOnTimeM;    // 上电时间-分
    Uint16 powerOnTimeSec;  // 上电时间-秒

    Uint16 runTime;
    Uint16 powerOnTime;
    
};
extern struct CUR_TIME curTime;   // 故障时时间记忆


enum ERROR_DEAL_STATUS
{
    ERROR_DEAL_PREPARE_FOR_WRITE_EEPROM,    // 准备故障记录保存
    ERROR_DEAL_WAIT_FOR_WRITE_EEPROM,       // 故障处理，等待保存故障记录完成
    ERROR_DEAL_WRITE_EEPROM_OK,             // 完成了故障记录保存。等待清除故障
    ERROR_DEAL_OK                           // 
};
extern enum ERROR_DEAL_STATUS errorDealStatus;

extern Uint16 errorCodeFromMotor;
extern Uint16 errorInfoFromMotor;
extern Uint16 errorFuncInfo;   // 功能故障子码

//纯报警等级判定
#define ALARM_LEVEL(err)		(((err >= DEFINE_ALARM_START) && (err <= DEFINE_ALARM_END)) || ((err >= DEFINE_ALARM_START2) && (err <= DEFINE_ALARM_END2)))

#endif












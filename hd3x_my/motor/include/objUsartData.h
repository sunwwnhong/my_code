
#ifndef __F_USART_DATA_H__
#define __F_USART_DATA_H__

#include "objUsartData.h"

// ----------------函数声明----------------------------------------------
extern void ProfibusRcvDataDeal(void);
extern void ModbusRcvDataDeal(void);
extern void PCRcvDataDeal(void);
extern void HMIRcvDataDeal(void);
extern void PLCRcvDataDeal(void);

extern Uint16 ModbusStartDeal(Uint16 tmp);
extern Uint16 ProfibusStartDeal(Uint16 tmp);
extern Uint16 PCStartDeal(Uint16 tmp);
extern Uint16 PLCStartDeal(Uint16 tmp);
extern Uint16 HMIStartDeal(Uint16 tmp);

#if 0
extern void UpdateModbusCommFormat(Uint16 baudRate);
extern void UpdateProfibusCommFormat(Uint16 baudRate);
extern void UpdatePCCommFormat(Uint16 baudRate);
extern void UpdateHMICommFormat(Uint16 baudRate);
#endif

extern void ModbusSendDataDeal(Uint16 err);
extern void ProfibusSendDataDeal(Uint16 err);
extern void PCSendDataDeal(Uint16 err);
extern void HMISendDataDeal(Uint16 err);
extern void PLCSendDataDeal(Uint16 err);

extern Uint16 ModbusCommErrCheck(void);
extern Uint16 ProfibusCommErrCheck(void);
extern Uint16 PCCommErrCheck(void);
extern Uint16 HMICommErrCheck(void);
extern Uint16 PLCCommErrCheck(void);

//extern Uint16 CrcValueByteCalc(const Uchar *data, Uchar length);
//extern Uint16 CrcValueWordCalc(const Uint16 *data, Uint16 length);


extern void SciDeal(void);
extern void SendDataDeal(Uint16 err, Uchar comm);
extern void RcvDataDeal(Uchar comm);
extern Uint16 CommWrite(Uint16 addr, Uint16 data, Uchar comm);
extern void UpdateCommFormat(void);
extern void CommErrCal(Uint16 com, Uint16 err);
extern void SciFlagReset(Uint16 com);
// ----------------函数声明结束------------------------------------------


#define COMM_NUM        5

#define COMM_PC         0
#define COMM_PLC        1
#define COMM_RS485      2
#define COMM_PROFIBUS   3
#define COMM_HMI        4

#define SCI_CMD_READ                0x03
#define SCI_CMD_READONLY            0x04    // 用于处理特殊协议的数据解析
#define SCI_CMD_WRITE               0x06
#define SCI_CMD_WRITE_RAM           0x07
#define SCI_CMD_WRITE_MORE          0x10

#define COMM_FRAME_ADDRESS          0x0     // 广播帧地址
#define COMM_HMI_SLAVE_ADDRESS      0x01    // HMI通讯站号 

#define FRAME_SPACE_TIME            6       // 接收间隔时间     6为3ms左右 对应的19200波特率
#define COMM_OVER_TIME              2000    // 通讯失联后1秒复位一次端口配置 1.0*2*100 = 2000
//===========================================================
//
// 通讯协议地址
//
//===========================================================
/*
#define COMM_SET_VALUE_ADDR         0x1000      // 通讯设定值 频率
#define COMM_SET_VALUE_SUB_ADDR     0x1001      // 通讯设定值 频率sub
#define COMM_SET_VALUE_ADDR_NOFRQ   0x1002      // 通讯设定 转矩上限 频率上限等
#define COMM_CMD1_ADDR              0x2000      // 通讯控制命令1，控制命令，启停等
#define COMM_STATUS_ADDR            0x3000      // 变频器运行状态
#define COMM_INV_ERROR              0x8000      // 变频器故障
#define COMM_CHECK_SUPER_PASSWORD   0x1010      // 超级密码解码值地址

#define COMM_READ_CHECK_UP          0X1011      // 用户更改参数UP命令
#define COMM_READ_CHECK_DOWN        0X1012      // 用户更改参数DOWN命令

#define COMM_TRANSFORMER_STATUS     0x1020      // 移相变压器状态字
#define COMM_TRANSFORMER_TEMPA      0x1021      // 移相变压器A相温度
#define COMM_TRANSFORMER_TEMPB      0x1022      // 移相变压器B相温度
#define COMM_TRANSFORMER_TEMPC      0x1023      // 移相变压器C相温度
#define COMM_TRANSFORMER_WIND_ON    0x1024      // 移相变压器定时开风机时间(小时)

#define COMM_HMI_NEED_RESET         0x1025      // HMI时间到达需要重置显示

// HMI曲线显示辅助协议
#define COMM_HMI_CURVE_ADD		    0x5000		// HMI曲线读取地址
#define COMM_HMI_CURVE1_ADDR        0x5100      // HMI曲线1地址定位 
#define COMM_HMI_CURVE2_ADDR        0x5200      // HMI曲线2地址定位
#define COMM_HMI_CURVE3_ADDR        0x5300      // HMI曲线3地址定位
#define COMM_HMI_CURVE4_ADDR        0x5400      // HMI曲线4地址定位
#define COMM_HMI_CURVE1_STOP_ADDR   0x5500      // HMI曲线1停止地址
#define COMM_HMI_CURVE2_STOP_ADDR   0x5501      // HMI曲线2停止地址
#define COMM_HMI_CURVE3_STOP_ADDR   0x5502      // HMI曲线3停止地址
#define COMM_HMI_CURVE4_STOP_ADDR   0x5503      // HMI曲线4停止地址
// 系统故障时HMI上传故障参数地址
#define COMM_HMI_ERR_CURVE_ADDR     0x5600
// 日志巡检帧首地址
#define COMM_HMI_LOG_ADDR           0x7300
// 光纤误码读取标记
#define COMM_HMI_FIBRE_ADDR         0x7200

// HMI版本号地址
#define COMM_HMI_VERSION            0x7105      // HMI版本号
// 通讯更改系统时间地址
#define COMM_TIME_YEAR              0xF708      // 系统时间 年 
#define COMM_TIME_SECOND            0xF70B      // 系统时间 秒

// PLC使用标准modbus协议时的地址定义
#define PLC_WRITE_DO_ADDR           0x0010      // 写PLC的DO状态地址
#define PLC_READ_DI_ADDR            0x0012      // 读PLC的DI状态地址
#define PLC_WRITE_AO_ADDR           0x0014      // 写PLC的AO状态地址
#define PLC_READ_AI_ADDR            0x0018      // 读PLC的AI状态地址
// 以下地址从0x0022开始用
// TemAmhSample使用标准modbus协议时的地址定义
#define TemAmhSample_READ_ADDR            0x0022      // 读TemAmhSample 状态地址
*/
//===============================END==================================//
#define SCI_WRITE_NO_EEPROM         0
#define SCI_WRITE_WITH_EEPROM       1

#define RTU_READ_DATA_NUM_MAX       100    // 最多读取数据个数 不能改小HMI PC用了16个
#define DP_WRITE_DATA_NUM_MAX       12     // profibus-DP最多写数据个数
#define RTU_MULIT_WRITE_DATA_NUM_MAX    6  // MODBUS-RTU 

#define COMM_ERR_NONE               0           //
#define COMM_ERR_PWD                1           // 密码错误
#define COMM_ERR_CMD                2           // 读写命令错误
#define COMM_ERR_CRC                3           // CRC校验错误
#define COMM_ERR_ADDR               4           // 无效地址
#define COMM_ERR_PARA               5           // 无效参数
#define COMM_ERR_READ_ONLY          6           // 参数更改无效
#define COMM_ERR_SYSTEM_LOCKED      7           // 系统锁定
#define COMM_ERR_SAVE_FUNCCODE_BUSY 8           // 正在存储参数

#define COMM_RUN_CMD_NUM    COMM_NUM   
extern Uint16 commRunCmd[COMM_RUN_CMD_NUM];      //

// HMI给定ARM的控制命令
#define SCI_RUN_CMD_NONE	            0       // 无命令
#define SCI_CMD_FWD_RUN		            1       // 正转运行
#define SCI_CMD_REV_RUN		            2       // 反转运行
#define SCI_CMD_JOG_FWD_RUN	            3       // 正转点动
#define SCI_CMD_JOG_REV_RUN         	4       // 反转点动
#define SCI_CMD_FREE_STOP	            5       // 自由停车
#define SCI_CMD_DEC_STOP	            6       // 减速停车
#define SCI_CMD_ERROR_RESET	            7       // 故障复位
#define SCI_CMD_PRECHARGE	            8       // 预充命令
#define SCI_CMD_INVCONTACT_CLOSE        9       // 手动闭合变频接触器
#define SCI_CMD_PRECHARGE_RES_OFF	    10      // 电阻预充柜 分闸命令
#define SCI_CMD_OUT_CONTACTOR_CLOSE     11      // 输出接触器合闸(岸电)
#define SCI_CMD_OUT_CONTACTOR_OFF       12      // 输出接触器分闸(岸电)

#define HMI_CURVE_LEN	1       // HMI曲线功能辅助

#define TRANSFORMER_TEMP_OFFSET     0x23    // 移相变压器采样温度零偏
#define TRANSFORMER_TEMP_MIN        -30     // 移相变压器采样温度最小值
#define TRANSFORMER_TEMP_MAX        200     // 移相变压器采样温度最大值

// 通讯设定上下限
#define COMM_SET_VALUE_MIN          -32000 
#define COMM_SET_VALUE_MAX          32000
// 通讯给定频率上下限--客户485专用
#define COMM_SET_FIGURE1_MIN        -30000
#define COMM_SET_FIGURE1_MAX        30000
// 通讯给定频率上下限--PC HMI专用
#define COMM_SET_FIGURE2_MIN        -60000
#define COMM_SET_FIGURE2_MAX        60000
// 通讯设定百分比上下限
#define COMM_SET_PERCENTAGE_MIN     -10000
#define COMM_SET_PERCENTAGE_MAX     10000

//extern const Uint16 COMM_ERR_INDEX[8];

// 通讯标志字
struct SCI_FLAG
{                                   
    Uchar read;                  // 0    读取功能标志位
    Uchar write;                 // 1    写功能码标志位
    Uchar crcChkErr;             // 2    CRC校验故障 Err3
    Uchar multiWrite;            // 3    连续写多个参数

    Uchar send;                  // 4    有数据发送标志位，区别广播模式和非广播模式，目前未使用
    Uchar sendDataStart;         // 5
    Uchar paraOver;              // 6    无效参数 Err5
    Uchar addrOver;              // 7    无效地址 Err4

    Uchar cmdErr;                // 8    读写命令错误 Err2
    Uchar paraReadOnly;          // 9    参数更改无效。参数只读，不能修改错误 Err6
    Uchar pwdErr;                // 10   密码输入错误 Err1
    Uchar pwdPass;               // 11   密码校验通过

    Uchar systemLocked;          // 12   系统锁定 Err7
    Uchar saveFunccodeBusy;      // 13   正在储存功能码 Err8
};


//extern union SCI_FLAG sciFlag;
//--------------串口状态-------------//
struct UART_FLAG
{
	Uchar sendOverFlag;			// 0 发送完成
	Uchar receOverFlag;			// 1 接收完成
	Uchar sendEnableFlag;       // 2 发送完成
	Uchar commErrFlag;		    // 3 通讯正常
	Uchar pwdCheckErr;          // 4 密码校验不通过
	Uchar dmaSending;           // 5dma 发送中
	
};

/****************************串口数据****************************/
#define DATA_LENGTH		255		 //char ,不超过256
#define USART_INIT_TIME 20000    // 异常时20S初始化一次

struct UART_DATA
{
    
	struct UART_FLAG uartFlag;
    struct SCI_FLAG sciFlag;
    Uchar sendNumber;
    
	Uchar baud;
	//Uchar sendDataLength;		
    Uchar rcvFrame[DATA_LENGTH];
    Uchar sendFrame[DATA_LENGTH];
	Uchar rxCounter;
	Uchar txCounter;
	Uint16 uartTimer;
    Uint16 rcvNumMax;
    Uint16 sendNumMax;
	
	Uchar uartSendLength;
    Uchar sendOverDelay;

    Uint16 uartShineCounter; 	//通讯灯处理
	Uint16 ledShineCounter;
	Uint16 sendDelay;    
	Uint16 uartCheckTime;       //判定通讯是否正常
    Uint16 frameSpaceTime;
    Uint16 sendDelaySet;
	Uint16 commStatusTime; 		// 串口状态计时
//	Uint16 CommCmdResetCount;   // 串口通讯异常 清运行命令计数

    Uint16 commData;
    Uint16 commAddr;
    Uchar commCmd;
    Uchar commCmdSaveEeprom;
    Uint16 slaveAddr;
    Uint16 moreWriteNum;                 // 字节数
};
extern struct UART_DATA uartData[COMM_NUM];


typedef struct 
{
	Uint16 HmiCurveAdd;	//曲线地址
	int32 HmiCurveData;	//读取对应量
}HMI_CURVE_OBJ;
extern HMI_CURVE_OBJ HmiCurveObj[4];	//HMI曲线缓冲

/*
typedef struct CommProtocolDeal
{
    void (*RcvDataDeal)(void);          // 接收数据处理 
    Uint16 (*StartDeal)(Uint16 tmp);    // 帧头判断
    //void (*UpdateCommFormat)();       // 更新通讯配置
    void (*SendDataDeal)(Uint16 err);   // 发送数据处理
    Uint16 (*CommErrCheck)(void);       // 通讯出错
}protocolDeal;
#define PROTOCOL_NUM    2
*/
//extern const protocolDeal protocolFunc[PROTOCOL_NUM];


//------通讯故障信息--------//
struct COMM_ERR_STATUS_BITS
{
    Uint16 modbusErr:1;         // 0 客户端485
    Uint16 canErr:1;            // 1 can主从
    Uint16 innerPLCErr:1;       // 2 内部plc
    Uint16 HmiRestart:1;        // 3 重启hmi
    Uint16 profibusErr:1;       // 4 profibus通讯中断
    Uint16 hmiResetFlag:3;      // 5-7 HMI每周下发重启请求
    Uint16 sampleBoardErr:1;    // 8
    
    Uint16 rsvd:7;              // 9-15保留
};

union COMM_ERR_STATUS
{
    Uint16 all;
    struct COMM_ERR_STATUS_BITS bit;
};
extern union COMM_ERR_STATUS commErrStatus;


struct DP_CONTROL_CMD_BITS
{
    Uint16 cmd:4;           // bit0-3 0:无效
 	Uint16 rsvd:11;         // bit4-14
	Uint16 plcDpErr:1;      // bit15:PLC故障V5.00-30
};
union DP_CONTROL_CMD
{
    Uint16 all;
    struct DP_CONTROL_CMD_BITS bit;
};
extern union DP_CONTROL_CMD dpControlCmd;                     // DP控制命令字

// -----------------plc 或继电器板的一些标记
struct PERIPHERAL_STYLE_BITS
{                                   // bits  description
    Uint16 plc:1;                   // 0 是否接入PLC 1有效
    Uint16 plcDataStyle:2;          // 1-2 8plc数据类型 1dido 2aiao 3温度
    Uint16 diOrTemp:1;              // 3 温度拍或是dido拍 

    Uint16 diOrDo:1;                // 4 标准协议 0:读DI 1:写DO
    Uint16 sampleBorad:1;           // 5 温湿度采样板是否接入
    Uint16 checkOver:1;             // 6 上电识别完毕 1-完毕
    
    Uint16 rsvd:9;                  // 7-15 保留
};

union PERIPHERAL_STYLE
{
   Uint16 all;
   struct PERIPHERAL_STYLE_BITS bit;
};

extern union PERIPHERAL_STYLE peripheralStyle;

//
//extern const Uint16 crc16Table[256];
extern Uchar commBaudCode[COMM_NUM];
extern Uint16 commReadData[RTU_READ_DATA_NUM_MAX];     // 读取的数据
//extern Uint16 commReadData[15];     // 读取的数据
//extern Uint32 commTicker;               // *_0.5ms
extern const Uint32 commBaud[13];
extern u16 plcVersion;
extern Uint16 hmiVersion;
extern Uint32 hmiErrCnt;
extern Uint16 dataOldComm;                 
//示波器相关变量
extern Uchar PcRxFlag;
extern Uchar OscDataCheck;
extern Uchar  frame;    //帧编号
//移相变压器信息
extern Uchar transformerStatus;    // 移相变压器状态字
//extern int16 transfTempA;         // 移相变压器A相温度
extern int16 transfTempB;         // 移相变压器B相温度
extern int16 transfTempC;         // 移相变压器C相温度
//extern Uint16 tWindOnTim;          // 移相变压器风机开启定时时间，单位小时
//通讯口波特率
extern Uchar commBaudProDp;
//FF组两级密码
extern bool companyPwdPass4Comm;     // 1-一级厂家密码通过，FF组使用

extern Uint16 rs485Protocol, plcProtocol;

///extern Uint16 dpCardType,dpCardVersion;
extern const Uint16 Modbus_Standard_ErrInfo[];
/*************************************示波器相关数据配置****************************************************/
#define         OSC_MIN_SAMPLE_TIME         4           // 示波器支持的最小采样间隔时间
#define         OSC_DATA_LENGTH             68

// 数据帧帧头
#define			OSC_DATA_FRAME_HEAD_A		0xA5		
#define			OSC_DATA_FRAME_HEAD_B		0xCD		
		
// 内部常数与命令
#define			OSC_BUF_DATA_LEN			64			// 示波器发送缓冲数据长度
#define			FC_FRAME_LEN				8			// 命令帧、响应帧长度

// 示波器串口控制命令
#define			FC_CHANNL_SEL				0x31		// 通道选择命令
#define			FC_PARA_CFG					0x32		// 参数配置
#define			FC_START_OSC				0x33		// 启动
#define			FC_STOP_OSC					0x34		// 停止	


// 示波器后台模块控制块声明
typedef struct
{
	Uchar	status;				// 采样状态(0-停止采样  1-开始采样) 
    Uchar 	interval;			// 采样间隔(*0.5ms) 	1~8								
    Uchar	ch1Addr;			// 通道1地址(采样数据1地址), 写入“0xFF”禁用该通道
    Uchar	ch2Addr;			// 通道2地址(采样数据2地址)
    Uchar	ch3Addr;			// 通道3地址(采样数据3地址)
    Uchar	ch4Addr;			// 通道4地址(采样数据4地址)   
	Uchar   chSum;				// 通道总数
} OSC_CON_DATA;
extern OSC_CON_DATA		OscCongData;			// 示波器配置参数 

// 示波器发送数据结构
typedef	struct
{
	Uchar	frameHead1;						// 数据帧头
	Uchar 	frameHead2;
	Uchar 	frameNum;						// 帧号
	Uchar	oscDataBuf[OSC_BUF_DATA_LEN];	// 数据缓存区
	Uchar	check;							// 校验
	Uchar	rwPI;							// 数据读写索引
	Uchar	full;							// 满标志					
} OSC_DATA_TYPE;
extern OSC_DATA_TYPE	OscDataBufA, OscDataBufB;	// 数据缓冲区义，双缓存模式

extern	Uchar	OscCfg;
/*************************************示波器相关数据配置****************************************************/
// 温度和湿度采样板相关
typedef struct
{
    int16 a_break_Flag:1;   // 断路时温度为-40度
    int16 b_break_Flag:1;               
    int16 c_break_Flag:1; 
    int16 a_short_Flag:1;   // 短路时温度为200度     
    int16 b_short_Flag:1;               
    int16 c_short_Flag:1;  
    int16 overTmp_Flag:1; 
    int16 rvd:9;
}SAMPLE_BOARD_BIT;

typedef union
{
   int16               all;
   SAMPLE_BOARD_BIT    bit;
}SAMPLE_BOARD_FLAG;
typedef	struct
{
	int16	temperature_A;				    // A相温度
	int16 	temperature_B;                  // A相温度
	int16 	temperature_C;					// A相温度
	int16	encir_humidity;	                // 环境湿度
	int16	temperature_envir;			    // 环境温度
	int16	sample_board_ver;				// 版本号
	SAMPLE_BOARD_FLAG sampleBoardFlag;	    // 断线/短路标志					lost_line_flag
} SAMPLE_BOARD_DATA;
extern SAMPLE_BOARD_DATA sampleBoardData;	// 数据缓冲区义，双缓存模式
// 温度和湿度采样板结束


#endif


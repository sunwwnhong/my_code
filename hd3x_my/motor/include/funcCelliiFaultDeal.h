/*
#ifndef __F_CELL_II_H__
#define __F_CELL_II_H__

#include "funcCaesar.h"

#define CELL_II_TEMP_ERROR_DATA     100     // II代机故障值


//extern void CelliiErrorDeal(void);

struct CELL_NEW_GENE_INFO_BITS
{
    u16 genFault:1;			// 00 单元总故障
    u16 upErr:1;				// 01 上行通讯故障
    u16 downErr:1;			// 02 下行通讯故障
    u16 rsvd1:1;		        // 03 保留
    u16 overVolErr:1;		// 04 单元过压故障
    u16 inLosePhase1:1;      // 05 单相输入缺相报警
    u16 inLosePhase2:1;      // 06 多相输入缺相报警
    u16 powerFromBypass:1;   // 07 单元旁路板供电状态
    
    u16 cellCtlPowerErr:1;   // 08 单元控制板电源异常
    u16 bypassCheck:1;       // 09 旁路接触器自检结果
    u16 bypassEnable:1;      // 10 旁路接触器可用
    u16 bypassFdb:1;         // 11 旁路接触器状态反馈
    u16 oos:4;				// 12 - 15 Q1 Q2 Q3 Q4 过流

    u16 rsvd5:16;			// 16 - 31 保留
};

typedef union 
{
	u16 all;
	struct CELL_NEW_GENE_INFO_BITS bit;
}CELL_NEW_GENE_INFO;
extern CELL_NEW_GENE_INFO  cell2ErrInfo[CELL_NUM];

struct CELL_TEMP_BITS
{
    Uint16 enviroTemp:8;    // 环境温度
    Uint16 radiatorTemp:8;  // 散热器温度
};
union CELL_TEMP
{
    Uint16 all;
    struct CELL_TEMP_BITS bit;
};

typedef struct 
{
	union Q_STATUS qStatusH1;	// 00 H1相IGBT状态
	Uint16 rsvd1;				// 01 保留
	union Q_STATUS qStatusH2;	// 02 H2相IGBT状态
	Uint16 rsvd3;		        // 03 保留
	Uint16 BusbarSample;		// 04 母线电压采样值 采样板进行采样 AD7606->FPGA->FPGA
	union CELL_TEMP cellTemp;	// 05 环境温度
	Uint16 rsvd2[2];		    // 06 - 07 保留
	Uint16 fpgaVersion;			// 08 FPGA版本号
	Uint16 Info[2];             // 09 - 10 故障代码(故障代码1 和 故障代码2)

	Uint16 rsvd[13];			// 11 - 23 保留
}CELL_NEW_GENE_STRUCT;

extern CELL_NEW_GENE_STRUCT cellNewGen[CELL_NUM];
#define CELL_NEW_GENE_DATA_LEN	(SIZEOF(CELL_NEW_GENE_STRUCT))


extern Uint32 cellFault;

extern Uint16 cellGenUvFilter[CELL_NUM];               // 单元欠压故障滤波
extern Uint16 cellGenUvRstFilter[CELL_NUM];            // 单元欠压故障复位滤波

#endif
*/

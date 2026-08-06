/*
 * funcMcbsp.h
 *
 *  Created on: 2018-2-3
 *      Author: Administrator
 */

#ifndef _FUNC_MCBSP_H_
#define _FUNC_MCBSP_H_

#include "DSP2833x_Device.h"     // DSP2833x 头文件
#include "DSP2833x_Examples.h"   // DSP2833x 例子相关头文件

#include "w5500_conf.h"

#define MCBSP_DMA
// #define MCBSP_INT

#define DAT_MAX_LEN    16

extern Uint16 sdata[];    // Sent Data
extern Uint16 rdata[];    // Received Data

extern void start_dma(void);
extern void init_mcbsp_spi(void);
extern Uint16 McBSP_SendReciveData(Uint16 dat);
extern void McBSP_DMA_Transfer(Uint16 Len);

#endif /* _FUNC_MCBSP_H_ */

/**********************************************************************
功能描述（Function Description）:
最后修改日期（Date）：
修改日志（History）:（以下记录为第一次转测试后，开始记录）
	作者 		时间 		更改说明
1 	xx 		xxxxx 		xxxxxxx
2 	yy 		yyyyy 		yyyyyyy
***********************************************************************/
#ifndef DEBUG_INCLUDE_H
#define DEBUG_INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

#define HOUTAI_ALONE_TEST           1

//#define DEBUG_COMMUNICATE_TO_PC   // PC后台监控使能


/* Includes ------------------------------------------------------------------*/
//#include "DataTypeDef.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct CPU_TIME_STRUCT_DEF {
    u16     DetaTime;
	u32 	Motor2MsBase;
	u32	    Function2MsBase;
    u32	    ADCIntBase;
	u32	    Main05msBase;
	u32	    Main0msBase;

	u16 	Motor2Ms;				//电机控制2ms执行时间
	u16	    Function2Ms;			//功能部分2摸索执行时间
	u16	    ADCInt;				    //ADC中断执行时间
	u16	    Main05ms;
	u16	    Main0ms;
}CPU_TIME_STRUCT;	//统计模块执行时间的数据结构



/* Private define ------------------------------------------------------------*/

#ifdef DEBUG_COMMUNICATE_TO_PC
/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
extern void SelectSCIFunc(void);
extern u32 SaveDataLimit(void);
extern CPU_TIME_STRUCT  gCpuTime;
extern s32 gSVCVMPhi;
//extern u16 gDebugSaveBuffer[];	//调试缓冲区
extern u16 * const gDebugSaveTable[];
extern u16 * const gDebugStatusTable[];
extern u16 const gDebugSaveTableCoff[];
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of definition

/******************************* END OF FILE***********************************/


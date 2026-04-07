/*
 * User06_ErrorDef.h
 *
 *  Created on: 2017年7月10日
 *      Author: zhuxc
 */




#ifndef User06_ErrorDef_H
#define User06_ErrorDef_H

#include "Svoption.h"
   
/*  【TI】为TI机型支持的故障与警告                                                                           */
/****************************************************************************************************/
/*																									*/
/*		故障代码定义  																		            */
/*																									*/
/****************************************************************************************************/
#define	ALM_EEPROM1			0		/* A.020 : 参数和校验异常:初始化时用户或默认参数校验异常      【TI】	*/
#define	ALM_EEPROM2			1		/* A.021 : 参数格式化异常: 版本号不匹配					【TI】	*/
#define	ALM_EEPROM3			2		/* A.022 : 系统和校验异常:                              【TI】	*/
#define	ALM_WRITEERR1		3		/* A.023 : MCU与FPGA通讯异常							【】	*/
#define	ALM_FPGAMODE2		4		/* A.030 : FPGA 运行于模式备份区域                      【】	*/
#define	ALM_PRM				5		/* A.040 : 参数设定异常: 超出设定范围					【TI】	*/
#define	ALM_DIVPRM			6		/* A.041 : 单管机型未开启自动充电功能                   【TI】  */
#define	ALM_PRMUNMATCH		7		/* A.042 : 参数组合异常								【TI】		*/
#define	ALM_ADRREPLAY		8		/* A.044 : B轴与A轴地址重复		                     【TI】       */
#define	ALM_UNMATCH			9		/* A.050 : 驱动器与电机电压不一致或功率相差4倍以上		【TI】	*/
#define	ALM_NOTSUPPORT		10		/* A.051 : 驱动器型号设定异常                            【TI】       */
#define	ALM_PROGERR			11		/* A.080 : 程序异常                         			【】  */
#define	ALM_SVONCMD			12		/* A.0B0 : 伺服on指令无效报警                           【TI】	*/
#define	ALM_OC				13      /* A.100 : 过电流(OC)                      				【】	*/
#define	ALM_OCH				14      /* A.101 :                                                      */
#define	ALM_MosErr			15		/* A.102 : 单管失效                                     【】  */
#define	ALM_RGOL			16		/* A.320 : 再生过载									    【TI】  */
#define	ALM_WIR				17		/* A.330 :                                              【】	*/
#define	ALM_OV				18		/* A.400 : 主回路过电压(OV)                             【TI】  */
#define	ALM_PUV				19		/* A.410 : 主回路欠电压                                 【TI】	*/
#define	ALM_CONVFLT			20		/* A.42A :  KTY型温度传感器过温                        	【】	*/
#define	ALM_XERROR			21		/* A.450 :  X端子配置重复                               【TI】  */
#define	ALM_YERROR			22		/* A.451 :  Y端子配置重复                               【TI】  */
#define	ALM_TAIERROR		23		/* A.452 :  转矩模式下AI分配重复                        【】 	*/
#define	ALM_VIB				24		/* A.520 : 振动警报                             		【TI】	*/
#define	ALM_AT				25		/* A.521 : 自动调谐报警                                 【TI】	*/
#define ALM_OLS1            26      /* A.710 : 驱动器过载(瞬时最大负载)					    【TI】	*/
#define	ALM_OLM1			27		/* A.711 : 电机过载(瞬间最大负载)						【TI】	*/
#define	ALM_OLS2			28		/* A.720 : 驱动器过载(连续最大负载)						【TI】	*/
#define	ALM_OLM2			29		/* A.721 : 电机过载(连续最大负载)						【TI】	*/
#define	ALM_DBOL			30		/* A.730 : DB过载										【TI】	*/
#define	ALM_DBOL_LVL		31		/* A.731 :      												*/
#define	ALM_OH				32		/* A.7A0 : 散热片过热                                   【TI】  */
#define	ALM_STOLOCK 		33		/* A.7AA : STO 输入保护                                 【】  */
#define	ALM_STOError		34		/* A.7AB : STO 异常                                     【】  */
#define	ALM_PG1				35		/* A.810 : 编码器备份报警                                【TI】	*/
#define	ALM_PG2				36		/* A.820 : 编码器Eeprom中数据异常                        【TI】	*/
#define	ALM_PG3				37		/* A.830 : 编码器电池欠压报警                            【TI】 */
#define	ALM_PG4				38		/* A.840 : 编码器圈数上限时方向异常                      【TI】 */
#define	ALM_PG5				39		/* A.850 :                                                      */
#define	ALM_PG6				40		/* A.860 : 编码器过热                                    【TI】 */
#define	ALM_SCL_ERR			41		/* A.890 : 电机编号不存在								 【TI】	*/
#define	ALM_MOD_ERR			42		/* A.891 :                                                      */
#define	ALM_FPGFSCALE		43		/* A.8A0 :                                                      */
#define	ALM_ORGOVTIME		44		/* A.8A1 :  原点回归超时                                 【TI】 */
#define	ALM_FPGSEN			45		/* A.8A2 :                                                      */
#define	ALM_FPGPOS			46		/* A.8A3 :                                                      */
#define	ALM_FPGOVSPD		47		/* A.8A5 :                                                      */
#define	ALM_FPGOVHEAT		48		/* A.8A6 :                                                      */
#define	ALM_VREFADERR		49		/* A.B10 :                                              		*/
#define	ALM_VREFADCHK		50		/* A.B11 :                                                  	*/
#define	ALM_TREFADERR		51		/* A.B20 :                              						*/
#define	ALM_CURAD_U			52		/* A.B31 : 电流检出故障1(U相)                             【TI】*/
#define	ALM_CURAD_V			53		/* A.B32 : 电流检出故障2(V相)                             【TI】*/
#define	ALM_CURAD_W         54		/* A.B33 : 电流检出故障3(W相)                             【TI】*/
#define	ALM_HWBB_UNSUPPORT	55		/* A.B40 :                                                      */
#define	ALM_PAR_UPDATE  	56		/* A.BE0 : 参数批量导入                                   */
#define	ALM_SAMP_OVER		57		/* A.BF0 : 系统报警0: ScanB检出ScanC停止2ms				 【TI】	*/
#define	ALM_STACK_OVF		58		/* A.BF1 :                                                      */
#define	ALM_UPROG			59		/* A.BF2 : ARM写入数据至FPGA侧异常                        【】 */
#define	ALM_PCMDSEL 		60		/* A.BF3 : 脉冲指令源选择异常              				 【】	*/
#define	ALM_HARD_OC 		61		/* A.BF4 : 硬件过流                        						*/
#define	ALM_RWF				62		/* A.C10 : 防止失控检出									 【TI】	*/
#define	ALM_PHASE			63		/* A.C20 :          											*/
#define	ALM_ENCMTOV		    64		/* A.C21 : 绝对值编码器多圈溢出       					 【TI】 */
#define	ALM_PHASEANGLE		65		/* A.C22 : 位相情報不一致										*/
#define	ALM_POLE			66		/* A.C50 :          											*/
#define	ALM_PFINDSTOP		67		/* A.C51 :                              						*/
#define	ALM_PDET			68		/* A.C52 :          											*/
#define	ALM_PDET_MOVEOVER	69		/* A.C53 :                  									*/
#define	ALM_PDET_NG			70		/* A.C54 :              										*/
#define	ALM_PGOV			71		/* A.C80 : 增量式编码器分频设置过大                     【】  */
#define	ALM_PGCOM			72		/* A.C90 : 编码器通信故障: 断线							【】	*/
#define	ALM_PGCOM1			73		/* A.C91 : 编码器通信位置数据加速度异常:ScanA中读取位置时判断	*/
#define	ALM_PGCOM2			74		/* A.C92 : 编码器 Z 信号丢失                            【】  */
#define	ALM_PGUVW			75		/* A.C95 : 增量式编码器UVW信号异常                         【TI】    	*/
#define	ALM_PGECHO			76		/* A.CA0 : 串行编码器数据和校验异常                            	*/
#define	ALM_TREACH			77		/* A.CC0 : 目标转矩到达                                 【TI】       */
#define	ALM_SPDERR			78		/* A.CC1 : 转速异常                                    【TI】       */
#define	ALM_ExFault		    79		/* A.CF2 : 外部故障信号输入有效                                                   	*/
#define	ALM_OF				80		/* A.D00 : 位置偏差过大								    【TI】  */
#define	ALM_BEOF			81		/* A.D01 : 伺服ON时位置偏差过大        					【TI】	*/
#define	ALM_BEVLMTOF		82		/* A.D02 : 伺服ON时速度限制所引起的位置偏差过大警报     【TI】	        */
#define	ALM_FSOF			83		/* A.D03 : 电机-负载位置间偏差过大:ScanC中全闭环控制检测【】	            */
#define	ALM_GEAR			84		/* A.D04 :  电子齿轮比设置超限         					【TI】	*/
#define	ALM_EET_ESC0		85		/* A.E00 :  EtherCAT 芯片工作异常配置失败               【TI】  */
#define	ALM_EET_Eeprom		86		/* A.E01 :  EtherCAT Eeprom装载异常                     【TI】  */
#define	ALM_EET_SM01ER		87		/* A.E02 :  EtherCAT SM0和SM1数据长度异常               【】  */
#define	ALM_EET_HomeErr		88		/* A.E03 :  回零方式设置异常( 不支持 )                  【TI】  */
#define	ALM_EET_SYNCH0		89		/* A.E04 :  synch0 同步周期异常                         【TI】  */
#define	ALM_EET_OPER		90		/* A.E05 :  EtherCat 操作模式异常                       【TI】  */
#define	ALM_EET_RError		91		/* A.E06 :  EtherCat 数据读取异常                               */
#define	ALM_EET_WError		92		/* A.E07 :  EtherCat 数据写入异常                               */
#define	ALM_EET_Sycht		93		/* A.E12 :  EtherCat 同步帧异常                                 */
#define	ALM_EET_SYNC0		94		/* A.E73 :  EtherCat断线报警                                    */
#define	ALM_SFTOP_NSUP		95		/* A.E74 :                                                      */
#define	ALM_FBKOP_NSUP		96		/* A.E75 :                                                      */
#define	ALM_CMDOP_UNMATCH	97		/* A.E80 :                                                      */
#define	ALM_SOM_NIDERR		98		/* A.E81 :                                                      */
#define	ALM_SOM_STALL		99		/* A.EB0 : 堵转保护                                              */
#define ALM_CAN_MOFF        100     /* A.E20 : CAN 主站掉线(寿命因子)                      【TI】         */
#define ALM_CAN_COMTOV      101     /* A.E21 : CAN 主站掉线(消费者时间)                     【TI】        */
#define ALM_CAN_CONFLIC     102     /* A.E22 : CAN 主站掉监测线配置冲突                      【TI】       */
#define	ALM_SOM_PLSERR		103		/* A.EB4 :                                                      */
#define	ALM_SOM_SRIAERR		104		/* A.EB5 :                                                      */
#define	ALM_SOM_SRIBERR		105		/* A.EB6 :                                                      */
#define	ALM_SOM_SFAERR		106		/* A.EB7 :                                                      */
#define	ALM_SOM_SFBERR		107		/* A.EB8 :                                                      */
#define	ALM_SOM_PRMCHGERR	108		/* A.EB9 :                                                      */
#define	ALM_SOM_PRMCHKERR	109		/* A.EC0 :                                                      */
#define	ALM_SOM_PRMMTCERR	110		/* A.EC1 :                                                      */
#define	ALM_SOM_ACTPRMERR	111		/* A.EC2 :                                                      */
#define	ALM_AXIS_ERRSYN		112		/* A.EC3 : 双轴同步故障                              【TI】          */
#define	ALM_SOM_RSVERR1		113		/* A.EC4 :                                                      */
#define	ALM_SOM_RSVERR2		114		/* A.EC5 :                                                      */
#define	ALM_SOM_RSVERR3		115		/* A.EC6 :                                                      */
#define	ALM_SOM_RSVERR4		116		/* A.EC7 :                                                      */
#define	ALM_SOM_RSVERR5		117		/* A.EC8 :                                                      */
#define	ALM_SOM_RSVERR6		118		/* A.EC9 :                                                      */
#define	ALM_PWPHASE			119		/* A.F10 :                                                      */
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		警告故障代码定义         																			*/
/*																									*/
/****************************************************************************************************/
#define	WRN_OF				0		/* A.900 : 位置偏差过大                           【TI】		*/
#define	WRN_BEOF			1		/* A.901 : 伺服ON时位置偏差过大                   【TI】	    */
#define	WRN_OLF				2		/* A.910 : 过载						              【TI】		*/
#define	WRN_VIB				3		/* A.911 : 振动                                   【TI】		*/
#define	WRN_RGOLF			4		/* A.920 : 再生过载					              【TI】		*/
#define	WRN_DBOL_LVL		5		/* A.921 : DB过载					              【TI】		*/
#define	WRN_PGBAT			6		/* A.930 : 绝对值编码器的电池故障	              【TI】		*/
#define	WRN_JOG 			7		/* A.931 : 外部端子点动异常	                      【TI】        */
#define	WRN_SERVOON			8		/* A.940 : 伺服ON信号无效				          【TI】        */
#define	WRN_BOOT			9		/* A.941 : 需要重新接通电源的参数变更	          【TI】		*/
#define	WRN_PUMP			10		/* A.950 : 自举时电机旋转                         【TI】        */
#define	WRN_POWEROFF		11		/* A.955 : 外部电源掉电                           【】        */
#define	WRN_UV				12		/* A.971 : 欠电压	                              【TI】        */
#define	WRN_POT				13		/* A.9A0 : 正向超程警告		                      【TI】		*/
#define	WRN_NOT				14		/* A.9A1 : 负向超程警告		                      【TI】		*/
#define	WRN_SYNC0			15		/* A.9F0 : EtherCat Sync0 丢失    		          【TI】        */
#define WRN_SERVOONE        16      /* A.9A2 : 伺服ON时速度限制                       【TI】        */
#define WRN_EMSTOP          17      /* A.902 : 紧急停机                               【TI】        */
#define WRN_STO             18      /* A.9B1 : STO警告                               【TI】        */
#define WRN_SPDERR_WARN     19      /* A.9B2 : 速度误差过大警告                          【TI】        */
#define WRN_STALL           20      /* A.9B3 : 堵转软警告                          【TI】        */

/*--------------------------------------------------------------------------------------------------*/


extern  const   USHORT  AlmDefTblEntNum;            /*故障代码数量                                  */
extern  const   USHORT  WrnDefTblEntNum;            /*警告代码数量                                  */
extern  const   ALMDEF  AlmDefTbl[];			    /* 警报定义表       						    */
extern  const   ALMDEF  WrnDefTbl[];			    /* 警告定义表           						*/



#endif

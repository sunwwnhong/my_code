/*
 * Mot40_ALMDeal.h
 *
 *  Created on: 2017骞?08鏈?22鏃?
 *      Author: zhuxc
 */
#ifndef Mot40_ALMDeal_H
#define Mot40_ALMDeal_H
 
/**********************************过载故障参数结构体定义****************************************/
typedef struct {
    float    fIbsqrmid;         //基极电流平方
    float    fIbsqrmax;         //瞬时过载基值   (中间电流平方*对应时间-最大电流平方*对应时间)/(中间电流时间-最大电流时间)
    float    fAlmLvlmid;        //中间电流过载报警值  （中间电流平方 - 基极电流平方）* 时间（100ms）
    float    fWrnLvlmid;        //中间电流过载警告值  （中间电流平方 - 基极电流平方）* 时间（100ms）* Pn015
    float    fAlmLvlmax;        //最大电流过载报警值  （最大电流平方 - 瞬时过载基值）*时间
    float    fWrnLvlmax;        //最大电流过载警告值  （最大电流平方 - 瞬时过载基值）*时间 * Pn015
    float    fOlLvlmidGain;     //中间电流过载增益系数
    float    fOlLvlmaxGain;     //最大电流过载增益系数
} CHKOLP;

/**********************************过载故障变量结构体定义****************************************/
typedef struct {
    UCHAR	WrnInfo;            //过载代码信息
    float   fSumImid;           //中间电流过载累计值
    float   fSumImax;           //瞬时电流过载累计值
} CHKOLV;


/**********************************故障参数结构体定义****************************************/
typedef	struct
{
    CHKOLP	MotOLP;             // 电机过载参数
    CHKOLP	AmpOLP;             // 驱动器过载参数
    LONG	Krgpower;           // 再生电阻实际功率
    LONG	RgolPowBase;        // 再生过载累加热量参考值
    LONG	RgolAlmLevel;       // 再生过载故障阈值
    LONG	Kunrgpower;         // 再生电阻设定功率
    LONG	Kdbpower;           // DB功率计算增益
    LONG	DbolPowMax;         // DB累加热量锁存值
    LONG	DbolPowBase;        // DB抵抗容量(默认值)
    LONG	DbolSpdLevel;       // DB过载检测电流变极点速度
    LONG	DbolAlmLevel;       // DB过载故障阈值
    LONG	OvrTrqLevel;        // 飞车检出转矩
    LONG	OvrSpdLevel;        // 飞车检出速度
} CHKALMP;

/**********************************故障变量参数结构体定义****************************************/
typedef	struct
{
    struct {
        USHORT	OperatorDrive	:1;     // 单模块内调用
        USHORT	SpareBit		:15;
    } f;
    CHKOLV	MotOLV;             // 电机过载变量
    CHKOLV	AmpOLV;             // 驱动器过载变量
    LONG	RgolPowSum;         // 再生累加热量锁存值
    LONG	RgPowerSum;         // 再生电阻累加热量
    LONG	RgMeanCycle;        // 再生电阻累加周期次数
    LONG	DbolPowSum;         // DB累加热量锁存值
    LONG	DbHeat;             // ???未用到的变量
    USHORT	HeatSinkSum;        // 温度累加和
    USHORT	HeatSinkSumCnt;     // 温度累加计数器
    USHORT	HeatSincErrCnt;     // 过温检测滤波时间计数
    USHORT	OvrChkCnt;          // 飞车监测计数值
    USHORT	OvrAlmCnt;          // 飞车检出计数值
    LONG	OvrTrqRef;          // 飞车参考转矩
    LONG	OvrAbsMotSpd;       // 飞车电机绝对转速
    LONG	OvrPeakMotSpd;      // 飞车检出最大速度
	UCHAR   FSOFAlmCnt;
} CHKALMV;

extern CHKALMP	ChkAlmP;
extern CHKALMV	ChkAlmV;
 
 extern void	CpxCheckAlarm( void );
 #endif

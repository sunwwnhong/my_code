/*
 * Mot22_GainSel.h
 *
 *  Created on: 2018年5月14日
 *      Author: zhuxc
 */
 #ifndef Mot22_GainSel_H
#define Mot22_GainSel_H
 #define	GAIN1			0x0400000
#define	GAIN2			0x0800000
#define	GAIN3			0x0C00000
#define	GAIN4			0x1000000

/**********************************伺服增益切换用变量定义*************************************/
typedef	struct	{
    LONG	Kp;                 // 位置环比例增益
    LONG	Kv;                 // 速度环比例增益
    LONG	Kv2;                // 速度环比例增益^2
    LONG	Kv2Inv;             // 速度环比例增益^2的逆数
    LONG	Kvi;                // 速度环积分增益
    LONG	Klpf;               // 1阶转矩延迟滤波器增益
    LONG	KpInv;              // 位置环比例增益逆数 SvCycle单位
    LONG	VirtualPosKp;       // 虚拟位置偏差计算用增益
    LONG	ZcKp;               // 零位固定时位置增益，与Kp一样大
    LONG    SFCoeff;            // 速度前馈系数
    float   fKv2Inv;
} GSELGAINS;

/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
    LONG	Ks;				    // 干扰观测器Ks增益
    LONG	Ksj;			    // 干扰观测器Ksj增益
    float   fKs;
    float   fKsj;
} GSELDOBS;
extern GSELGAINS GselGains[6];
extern	GSELDOBS GselDobs[3];
 
extern void	BpxInitServoGainChange( void );
extern void PcalAtGseldKlpfSet( void );
extern void	PcalAtGseldKviSet( void );
extern void	PcalAtGseldKsSet( void );
extern void	PcalGainChange( void );
extern void	PcalAtGseldKpSet( void );
extern void	PcalAutoGainChange( void );
extern void	BpxServoGainChange( void );
 
 #endif

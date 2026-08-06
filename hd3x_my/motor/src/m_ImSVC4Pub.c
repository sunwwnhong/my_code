#include "m_ImSVC4CalcFlux.h"
#include "m_frqSrc.h"
#include "main.h"
#include "m_output.h"
#include "m_main.h"


MOTOR_STRUCT 			gMotorInfo;	    //电机信息
MOTOR_EXTERN_STRUCT		gMotorExtInfo;	//电机扩展信息（实际值表示）
MOTOR_EXTERN_STRUCT		gMotorExtPer;	//电机扩展信息（标么值表示）

BASE_PAR_STRUCT			gBasePar;	    //基本运行参数
BASE_COMMAND_STRUCT		gMainCmd;		//主命令
extern struct OutputProcessType OutputProcess;


extern struct CommandGeneratorType CommandGenerator;
extern MotorPara motorPara;                // 电机参数
extern f32 statorInductanceH;
extern f32 lSigmas;
extern Uint16 coreMaxFrq;
extern f32 coreCarrierFrqAct;
extern f32 DeltaImSvc4;
extern f32 ImSvc4FluxRFrq;
extern Uint16 cfGroup[];
extern f32 idFdbSVC4;// id反馈
extern f32 iqFdbSVC4;// iq反馈
extern f32 udcFil;
extern int32 coreFrqHz;
extern f32 VMPhiOB;

f32 volLineMaxIMSVC4;
f32 volLineMaxCntIMSVC4 = 1.0;
f32 fluxlimittest;
f32 PhiRefOB;

//u16 InitFlag = 0;

u16 spdfilcoef = 1;
u16 lowspdfilcoef1 = 10;
u16 lowspdfilcoef2 = 5;
u16 lowspdfilcoef3 = 1;


u16 VCWsCoff = 100;

/**********************************************************
函数描述：将浮点的电机铭牌参数换算成观测器需要的定点参数（SVC3/SVC4公用）

***********************************************************/
void IMMotorParaChangeSVC34(void)
{	
	//异步电机额定参数
	gMotorInfo.Votage = (Uint)(motorPara.ratingVoltage);//V
	gMotorInfo.Current = (Uint)(motorPara.ratingCurrent*100.0);//0.01A
	gMotorInfo.Frequency = (Uint)(motorPara.ratingFrq*100.0);//0.01hz
	gMotorExtInfo.R1 = (Uint)(motorPara.rsOhms*1000.0);//0.001欧姆
	gMotorExtInfo.R2 = (Uint)(motorPara.rrOhms*1000.0);
	//gMotorExtInfo.R2 = cfGroup[18];
	gMotorExtInfo.LM = (Uint)(statorInductanceH*10000.0);//0.1mH
	gMotorExtInfo.L0 = (Uint)(lSigmas*100000.0*0.5);//0.01mH
	gMotorExtInfo.Rpm = (Uint)(motorPara.ratingSpeed);//1rpm
	gMotorExtInfo.I0 = (Uint)(motorPara.iNoloadA * 100.0 / SQRT2);//0.01A 有效值
}

/**********************************************************
函数描述：准备SVC3观测器需要的函数

***********************************************************/
u16 spdfilcofftest = 1;

void PrepareSVC4Par(void)
{	
	long data,OmgFliter,data1;
	//long m_ImLimit;

	
	//小于3Hz,加大滤波，不然0hz观测器频率正负波动
	//会导致转矩电流也波动，电机启动会震动
	if((abs(coreFrqHz)) < 100)
	{
		spdfilcoef = lowspdfilcoef1;
	}
	else if((abs(coreFrqHz)) < 300)
	{
		spdfilcoef = lowspdfilcoef2;
	}
	else
	{
		spdfilcoef = lowspdfilcoef3;
	}

	gImSVC.FunctionCode[0] = 15*spdfilcoef;//速度滤波系数
	//gImSVC.FcSet = (long)(0.5/T/100.0);//0.1kHz
	gImSVC.FcSet = (long)(coreCarrierFrqAct*0.02);//0.1kHz
	
	data = (long)gImSVC.FunctionCode[0] * gImSVC.FcSet/10;//gImSVC.FunctionCode[0] = 15									  //gImSVC.FcSet = 40 4KHz
	if(data >= 400)
	{
		data = 400;
	}
	OmgFliter = 32768/data;
	if(OmgFliter > 4096)
	{
		OmgFliter = 4096;
	}
	
	if(gImSVC.FluxWeakFlag == 0)
	{
		gImSVC.OmgSLFliter = OmgFliter;
		gImSVC.OmgFliter = OmgFliter;
	}
	else
	{
		gImSVC.OmgSLFliter = OmgFliter>>2;
		gImSVC.OmgFliter = OmgFliter<<1;
	}

	gImSVC.LmSet0 = (long)gMotorExtInfo.LM * 104;
	gImSVC.L00 = (long)gMotorExtInfo.L0 * 10L;
	gImSVC.Rs0 = (long)gMotorExtInfo.R1 * 32767L/1000;
	gImSVC.Rr0 = (long)gMotorExtInfo.R2 * 32767L/1000;
	
	gImSVC.LmSet = gImSVC.LmSet0;
	gImSVC.L0 = gImSVC.L00;
	gImSVC.Rs = gImSVC.Rs0;
	gImSVC.Rr = gImSVC.Rr0;
	//gImSVC.I0Q = gMotorExtPer.I0;           // 空载电流 Q12格式
	//好像不对？
	data = (u32)gMotorInfo.Votage * 425818L/gMotorInfo.Frequency;
	//data = (u32)gMotorInfo.Votage * 301108L/gMotorInfo.Frequency;//301108L = 32768*100/(2*3.14*1.732)
    data1 = gImSVC.L0 * (long)gMotorExtInfo.I0/3052;//1000*1000*100/32768
    //data1 = gImSVC.L0 * (long)gMotorExtInfo.I0/3200;//2^20*100/32768
    data = data - data1;
    gImSVC.PhiRef0 = data;                  //Q15

	gImSVC.LrVLm = (long)gMotorExtInfo.L1 * 1024/gMotorExtInfo.LM;
	gImSVC.LmVLr = (long)gMotorExtInfo.LM * 1024/gMotorExtInfo.L1;
	gImSVC.PhiRef = gImSVC.PhiRef0;
	PhiRefOB = gImSVC.PhiRef;
	gImSVC.VMPhiMax = gImSVC.PhiRef * 3L>>1;
	//gImSVC.VMPhiMin = gImSVC.PhiRef>>4;
	if(gImSVC.FluxWeakFlag == 0)
	{
		gImSVC.VMPhiMin = gImSVC.PhiRef>>1;
	}
	else if(gImSVC.FluxWeakFlag == 1)
	{
		gImSVC.VMPhiMin = gImSVC.PhiRef>>4;
	}

	data  = (long)1024L * (gImSVC.LmSet + gImSVC.L0) / gImSVC.Rr;//20+10-15
	gImSVC.EstPerTr = 32768L * 1024L/data;//10=15+10-15;
	gImSVC.OmgEMax = gImSVC.FullFreq * 240L;//242 = 1608*1.5/10;//1.5倍最大频率
	/*
	if(InitFlag < 10)
	{
		InitFlag++;

		data = (gImSVC.PhiRef>>1);
		gImSVC.VMPhi = data;
		gImSVC.VMPhiL = gImSVC.VMPhi * 100L;
		gImSVC.VMPhiLpf = gImSVC.VMPhiMin * 256L;
		gImSVC.g1 = 1000;
		gImSVC.g2 = 0;
	}*/
	if(OutputProcess.Enable == FALSE)
	{
		data = (gImSVC.PhiRef>>1);
		gImSVC.VMPhi = data;
		gImSVC.VMPhiL = gImSVC.VMPhi * 100L;
		gImSVC.VMPhiLpf = gImSVC.VMPhiMin * 256L;
		gImSVC.g1 = 1000;
		gImSVC.g2 = 0;
	}

	gImSVC.VCWsCoff = VCWsCoff;

	//gImSVC.KAngel = 6835653L/gImSVC.FcSet;//6835653L = 2^32/2/pi/100
	gImSVC.KAngel = 6835653L/gImSVC.FcSet;

	//磁链闭环用，暂时写这里
	/*
	m_ImLimit = gImSVC.I0Q * 3;
    if(m_ImLimit > 4000)
	{
		m_ImLimit = 4000;
	}

	if(driveParameterMenu.ratingOutputCurrent < motorPara.ratingCurrent)
	{
        m_ImLimit = (u32)(m_ImLimit * (driveParameterMenu.ratingOutputCurrent/motorPara.ratingCurrent));
	}
    gImSVC.ImLimit = m_ImLimit;
    */
}

/**********************************************************
函数描述：准备SVC3、SVC4观测器公共的参数

***********************************************************/

void ChangeMotorParSVC34(void)
{
	Uint m_UData,m_BaseL,m_FreThreshold;
	Ulong m_Ulong;
	//Uint m_AbsFreq;
    gMainCmd.si2puCoeff = 100;       // si 2 pu
    gMainCmd.pu2siCoeff = 1;         // pu 2 si
        
	gBasePar.FullFreq01 = (Ulong)coreMaxFrq * (Ulong)gMainCmd.pu2siCoeff + 2000;//最大频率+20 单位0.01Hz
	gBasePar.FullFreq =   coreMaxFrq + 20 * gMainCmd.si2puCoeff;	//频率基值
	gMotorInfo.FreqPer =  ((Ulong)gMotorInfo.Frequency <<15) / gBasePar.FullFreq;

	gImSVC.FullFreq = gBasePar.FullFreq/10;
	
	//电感基值为：阻抗基?2*pi*最大频率
	m_BaseL = ((Ulong)gMotorInfo.Votage * 3678)/gMotorInfo.Current;
	m_BaseL = ((Ulong)m_BaseL * 5000)/gBasePar.FullFreq01;
    
    
	//阻抗基值为相电压/相电流，电阻标么值Q16格式
	// sqrt(3)/1000/100 <<16 = 18597 >>14
	m_UData = ((Ulong)gMotorExtInfo.R1 * (Ulong)gMotorInfo.Current)/gMotorInfo.Votage;	
	gMotorExtPer.R1 = ((Ulong)m_UData * 18597)>>14;                 // 异步机定子电阻
    
	m_UData = ((Ulong)gMotorExtInfo.R2 * (Ulong)gMotorInfo.Current)/gMotorInfo.Votage;	
	gMotorExtPer.R2 = ((Ulong)m_UData * 18597)>>14;                 // 异步机定子电阻

	gMotorExtInfo.L1 = 	gMotorExtInfo.LM + ((Ulong)gMotorExtInfo.L0 * 102 >> 10);
	gMotorExtInfo.L2 = gMotorExtInfo.L1;

	m_Ulong = (((Ulong)gMotorExtInfo.L1<<11) + m_BaseL)>>1;		
	gMotorExtPer.L1 = m_Ulong/m_BaseL;
	gMotorExtPer.L2 = gMotorExtPer.L1;							//定子、转子电感标么值Q9格式
	m_Ulong = (((Ulong)gMotorExtInfo.LM<<11) + m_BaseL)>>1;
	gMotorExtPer.LM = m_Ulong/m_BaseL;							//漏感标么值Q14格式
	gMotorExtPer.L0 = (gMotorExtPer.L1 - gMotorExtPer.LM)<<5;

    gMotorExtPer.I0 = (((Ulong)gMotorExtInfo.I0)<<12)/gMotorInfo.Current;	//空载电流

    //m_Ulong = 4096L * 4096L - (long)gMotorExtPer.I0 * gMotorExtPer.I0;
    //gMotorExtPer.ItRated = qsqrt(m_Ulong);
    //gPowerTrq.rpItRated = (1000L<<12) / gMotorExtPer.ItRated;

	//....计算电机极对数
	//m_Ulong = (((Ullong)gMotorInfo.Frequency * (Ullong)gMainCmd.pu2siCoeff * 19661L)>>15);

	//gMotorExtInfo.Poles = (m_Ulong + (gMotorExtInfo.Rpm>>3)) / gMotorExtInfo.Rpm;          

    //m_FreThreshold = ((long)gMotorExtInfo.Poles * gMainCmd.si2puCoeff * 500) / gPGData.PulseNum + 5;   //外加0.05Hz
    //gRotorSpeed.FreThreshold = ((long)m_FreThreshold << 15) / gBasePar.FullFreq01;  //chzq18111
    //0.01Hz为单位的额定转差率
    //m_Ulong = ((Ulong)gMotorExtInfo.Rpm * gMotorExtInfo.Poles * 100L)/60;
    //m_Ulong = gMotorExtInfo.Rpm * gMotorExtInfo.Poles * 6830L >> 12;
    //gMotorExtInfo.RatedComp = (Ulong)gMotorInfo.Frequency * gMainCmd.pu2siCoeff - m_Ulong;                             
    //标么化的额定转差率       
    //gMotorExtPer.RatedComp = ((long)gMotorExtInfo.RatedComp << 15)/gBasePar.FullFreq01; 
	gMotorExtInfo.Tr = ((u32)gMotorExtInfo.L2 * 100UL)/gMotorExtInfo.R2;    /*ms单位的转子时间常数*/ 
}

void ReSetImSVC4Data()
{
	gImSVC.Id = (long)(idFdbSVC4 * SQRT2 * motorPara.ratingCurrent * 4096.0);
	gImSVC.Iq = (long)(iqFdbSVC4 * SQRT2 * motorPara.ratingCurrent * 4096.0);
	gImSVC.Id1 = gImSVC.Id;
	gImSVC.Iq1 = gImSVC.Iq;
	gImSVC.Ud = 0;
	gImSVC.Uq = 0;
	gImSVC.UdQ = 0;
	gImSVC.UqQ = 0;
	gImSVC.Ed = 0;
	gImSVC.Ed1 = 0;
	gImSVC.Eq = 0;
	gImSVC.IqLpf = 0;
	gImSVC.IqQLpf = 0;
	gImSVC.Wr = 0;
	gImSVC.OmgE1 = 0;
	gImSVC.OmgE = 0;
	gImSVC.WrQ = 0;
	gImSVC.OmgSL = 0;
	gImSVC.WeQ = 0;
	gImSVC.OmgSLQ = 0;

	gImSVC.VMPhase32 = 0;
	//gImSVC.VMPhaseS = 0;
	//gImSVC.Direction = 0;
	gImSVC.EqLpf = 0;
	//gImSVC.PhaseOpen = 0;
	

	gImSVC.Ed1 = 0;
	gImSVC.Ed = 0;
	gImSVC.Eq = 0;

	//gImSVC.ImSetLpf = 0;
	gImSVC.OmgE1Lpf = 0;
	//gImSVC.WeQForSwitch = 0;
	//gImSVC.FsSetQ = 0;

	DeltaImSvc4 = 0;
	ImSvc4FluxRFrq = 0;
	gImSVC.VMPhiL = 0;
	gImSVC.VMPhi = 0;
	VMPhiOB = 0;
}

f32 RVolDrop,lSigmaVolDrop;//电阻压降和漏感压降
f32 LVolDrop1;
extern f32 lcLPu;

//磁链幅值和d轴电流成正比关系
f32 FieldWeakeningIMSVC4(f32 input)
{
    f32 fluxlimit;
    f32 spd;
    f32 tmp;
    f32 tmp1;
	f32 output;

    if(cfGroup[16] != 0)
	{
		tmp = fabs(OutputProcess.FrequencyFiltered / motorPara.ratingFrq * I_TWO_PI);
	}
	else
	{
    	tmp = fabs(CommandGenerator.SpeedReference / motorPara.ratingFrq * I_TWO_PI);
	}
    spd = GetMax(tmp, 0.05);

	//fluxlimit = OutputProcess.RatedFrequency / spd;
    {
        //f32 LVolDrop;
        
        // 最大的输出电压上限，考虑输出电感
        LVolDrop1 = fabs(OutputProcess.WsFilPu) * lcLPu * OutputProcess.IdsFil * SQRT3;
        RVolDrop = OutputProcess.TotalCurrent * motorPara.rs * SQRT3;//线电压上定子电阻压降
        lSigmaVolDrop = fabs(OutputProcess.WsFilPu) * motorPara.lSigma * OutputProcess.IdsFil * SQRT3;//*0.5 暂时不×0.5，输出电压和520比较接近 线电压上漏感压降
        volLineMaxIMSVC4 = udcFil * driveParameterMenu.ratingInputVoltage;
		if(motorPara.ratingVoltage != 0)
		{
		    //tmp1 = volLineMaxIMSVC4 / motorPara.ratingVoltage - LVolDrop - (f32)((s32)(s16)funcCode.code.WeakFluxdepth)*0.01
		    
			tmp1 = volLineMaxIMSVC4 / motorPara.ratingVoltage - LVolDrop1 - RVolDrop - lSigmaVolDrop - 
														(f32)((s32)(s16)funcCode.code.WeakFluxdepth)*0.01;//考虑输出电感、定子电阻、漏感压降
        	volLineMaxCntIMSVC4 = LPF_K(tmp1, volLineMaxCntIMSVC4, 15.0/MAIN_LOOP_TIME_MS);
		}

    }
	fluxlimit = volLineMaxCntIMSVC4 / spd;
	fluxlimittest = fluxlimit;
	
	if(fluxlimit < 1.0)
	{
		gImSVC.FluxWeakFlag = 1;
	}

	output = input*fluxlimit;

    input = GetMin(output, input);

    return input;
}



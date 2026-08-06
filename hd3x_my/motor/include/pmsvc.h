#include "m_main.h"
typedef struct PMSVC_EST_SPEED_DATA_DEF
{
//************************************
//中间变量	
	f32 id;
	f32 iq; 
	f32 id1; 
	f32 iq1;
	f32 vd;
	f32 vq;
	
	f32 vd1;
	f32 vq1; 
	f32 est_id;
	f32 est_iq;
	f32 est_delt_id;
	f32 est_delt_iq;
	f32 est_bem;
	f32 est_bem1;
	long est_omgm;
	long est_omgm1;
	f32 coef_d0;
	f32 coef_d1;
	f32 coef_d2;
	f32 coef_q0;
	f32 coef_q1;
	f32 coef_q2;
	long coef_angel;
	f32 coef_alfa;
	f32 coef_beta;
	f32 coef_bem;
	long coef_ks;	
	
//************************************
//输出变量
	long est_omg;//辨识的电角速度，等于电角速度实际值乘以256，rad/s
	long est_omg_lpf;//大滤波电角速度，等于电角速度实际值乘以256，rad/s
	long est_angel;//辨识的电角度，2^32 = 360度	
	int  low_speed_idset;//低速下D轴电流设定,以变频器额定电流为基值，Q12;
//**********************************
//中断中更新，在调用速度识别函数之前赋值。
	long csrvd;//D轴电压给定,以变频器额定电压为基值，Q12;
	long csrvq;//Q轴电压给定,以变频器额定电压为基值，Q12;
	long fdbid;//D轴电流反馈,以变频器额定电流为基值，Q12;
	long fdbiq;//Q轴电流反馈,以变频器额定电流为基值，Q12;
	long fcset;//载频，1HZ
//**********************************
//2MS更新
	long ld;//D轴电感，uH;
	long lq;//Q轴电感，uH;
	long r;//电阻,mΩ
	long bemf;//反电动势系数,1mv/rad,峰值;
	int  coef_beta_set;//调试系数1，20，需要设置成功能码，用户不需要更改
	int  coef_bem_set;//调试系数2，30，需要设置成功能码，用户不需要更改
	long  motor_curr;//电机额定电流,0.1A
	long  motor_volt;//电机额定电压，1V 
	int  pmsvc_control;//等于1,同步机SVC控制
	long speed_lpf_k;//转速滤波系数，需要设置成功能码，用户需要更改
					//出场值100，设定范围16~512;
	int  low_speed_idmax;//以电机额定电流的百分比设置低速下D轴电流设定最大值，0.1%
						//需要设置成功能码，用户需要更改，出场值0%，设定范围0~100.0%;
	int  low_speed_fcset;//低速下载频，单位100HZ，出厂20，需要设置成功能码
}PMSVC_EST_SPEED_DATA;
/*
typedef struct PM_CALC_INIT_POS_DEF
{

//中间变量	
	int  step;
	int  period_cnt;
	int  section;
//记录每相零点电流大小	
	long cur_first;
//发出U+,V-,W-/U-,V+,W+的脉冲电压,记录U相绝对值最大电流，保存在PmCalcInitPos.cur[1],PmCalcInitPos.cur[2]
///V+、U-、W-/V-、U+、W+,记录V相绝对值最大电流，保存在PmCalcInitPos.cur[3],PmCalcInitPos.cur[4]
//W+、U-、V-/W-、U+、V+,记录W相绝对值最大电流，保存在PmCalcInitPos.cur[5],PmCalcInitPos.cur[6]
	long cur[7];

	int  num;
	int  pwm_period;   //初始位置检测时PWM时间
	
*****************************************************************************
//控制变量
	int  control_flag;      //正在执行初始位置检测程序标志，calc_mode不等于0时，
							//需要在电机启动初始时置1，
							//初始位置检测结束置2,
//功能码输入变量
	int  calc_mode;		//初始位置检测方式,需要设置功能码,0:不检测初始位置，
						//1:检测方式1，对于绝大多数电机，需要设置为1
						//2:检测方式2，如果检测方式1不行，设置为2.
	int  pwm_period_set;//初始位置检测设置的EPwmXRegs.TBPRD时间，等于发出额定电机电流
						//IGBT开通的时间，需要参数辨识时检测出来，需要设置功能码显示
						//参数辨识时，时钟寄存器的设置要与初始位置检测时设置的一致
					
	
	int  check_curr;   //以电机额定电流的百分比确定初始位置检测的电流大小，0.1%
					   //需要设置功能码，出厂值120.0，范围0~200.0
	
*******************************************************************************
	int init_phase; //检测到的磁场初始位置，65536 = 360度
}PM_CALC_INIT_POS;
extern PM_CALC_INIT_POS  PmCalcInitPos;
*/
extern PMSVC_EST_SPEED_DATA PmSvcData;


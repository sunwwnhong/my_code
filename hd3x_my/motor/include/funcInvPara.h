//----------------------------------------------------------//
// File Name		: funcInvParaDeal.h	
// Description		: 电机参数
// Time				: 2011.03.02
// Editor			: xxxxx
// Co.				: xxxxx
//----------------------------------------------------------//

#ifndef __F_FUNC_INV_PARA_H__
#define __F_FUNC_INV_PARA_H__

// ----------------函数声明----------------------------------------------
extern void SaveTuneData(void);
extern void UpdateMotorPara(void);
extern void UpdateInvType(void);
// ----------------函数声明结束------------------------------------------

extern struct MOTOR_FC motorFc;
extern enum MOTOR_SN motorSn;

extern enum MOTOR_SN validMotorNo;

#if 0
struct INV_TYPE_LIMIT
{
    Uint16 vol;     // 本电压等级的电压

    Uint16 lower;   // 本电压等级的机型下限
    Uint16 upper;   // 本电压等级的机型上限
};
extern const struct INV_TYPE_LIMIT invTypeLimitTable[];
#endif

//------------------------------------------------

#endif













//----------------------------END-------------------------//




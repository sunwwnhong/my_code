/*
 * Cur14_ZeroPhase.h
 *
 *  Created on: 2018年5月19日
 *      Author: zhuxc
 */
 #ifndef Cur14_ZeroPhase_H
#define Cur14_ZeroPhase_H
typedef struct
{
    SHORT PhaseCurCmd;       // 磁极辨识时电流大小 0.1%
    SHORT PhaseCurOut;       // 磁极辨识时输出电流大小
    USHORT Angle;            // 磁极辨识时角度
    USHORT DelayCnt;         // 磁极辨识时延时
    USHORT Step;             // 磁极辨识时步骤
    SHORT  Angle1;           // 角度1
    SHORT  Angle2;           // 角度2
    SHORT  AngleOld;         // 角度旧值
    SHORT  AngleSum;         // 角度变化值
    SHORT  AngleSumOld;      // 角度变化值
    USHORT PhaseOld;         // 角度方向
    USHORT FirstFlag;        // 第一次进入标志
    USHORT WaitStillStep;    // 等待静止过程                          
}ZEROPHASE_STRUCT;
extern ZEROPHASE_STRUCT ZeroPhaseV;
 extern void ZeroPhaseInit( void );
extern void ZeroPhaseDeal( void );
#endif

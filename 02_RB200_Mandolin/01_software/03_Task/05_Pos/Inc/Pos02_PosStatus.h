/*
 * Pos02_PosStatus.h
 *
 *  Created on: 2018年06月20日
 *      Author: zhuxc
 */
 #ifndef Pos02_PosStatus_H
#define Pos02_PosStatus_H




typedef struct{
    LONG Pos6064Org;
    LONG Pos6064New;                 //6064新值
    LONG Pos6064Old;                 //6064旧值
    LONG Pos6064Delta;               //6064增量
    LONG Pos6064Sum;                 //6064累计量
    LONG Pos6067;
    LONG Pos6068;
    LONG Pos607A;
    LONG Pos6040;
    LONG PosDelta;                   //位置模式下，607A设定的值所需跑过的位置
    LONG PosDelta1;                  //6064实际增量和607A设定所需增量差
    USHORT PPStep;
    USHORT PPOrg;
}TRGTRCH;
extern TRGTRCH  Trgtrch;


 extern void LpxCheckPerrOverFlow( void );
extern void LpxCheckSvonPerrOverFlow( void );
extern void	BpxControlPositionSignal( void );
extern void BpxControlPositionSignal_EtherCat( void );
extern void BpxControlPositionSignal_CanOpen( void );
 #endif

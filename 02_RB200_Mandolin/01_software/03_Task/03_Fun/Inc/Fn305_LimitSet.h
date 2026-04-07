/*
 * Fn305_LimitSet.h
 *
 *  Created on: 2019Äê09ÔÂ29ÈÕ
 *      Author: zhuxc
 */
 #include "Main.h"
 #ifndef Fn305_LimitSet_H
#define Fn305_LimitSet_H
 extern LONG SoftLimitSetBegin(FUNEXE *pfexe);
extern LONG SoftLimitSetExe(FUNEXE *pfexe);
extern void SoftLimitSetEnd(FUNEXE *pfexe, UCHAR method);
 #endif

/*
 * Fn010_PrmAccess.h
 *
 *  Created on: 2019Äê6ÔÂ20ÈÕ
 *      Author: zhuxc
 */
 #ifndef Fn010_PrmAccess_H
#define Fn010_PrmAccess_H
 
#define USR1_PASWRD			0x1002                   
#define USR2_PASWRD  		0x2001                   
#define SYS_PASWRD			0x1706                   
 
extern void FunAccessSetInit( void );
extern void FunAccessSetEnd(FUNEXE *pfexe, UCHAR method);
extern LONG FunAccessSetExe(FUNEXE *pfexe);
extern LONG RpiFunSetAccesslvl(USHORT PswdData, HMSGIF Hmsg);
 #endif
 
 
 

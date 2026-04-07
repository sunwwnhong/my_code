/*
 * Pr05_OrgS.h
 *
 *  Created on: 2019年11月29日
 *      Author: xuezs
 */

#ifndef Pr05_OrgS_H
#define Pr05_OrgS_H
#include "Pos_OrigSearch.h"
//鍙橀噺瀹氫箟,Pos_OrigSearch.h涓凡瀹氫箟杩�
//#define ORG_IDL               0
//#define ORG_SPDH              1
//#define ORG_SPDH_DEC          2
//#define ORG_SPDL              3
//#define ORG_SPDL_DEC          4
//#define ORG_SWITCH_CHECK      5
//#define ORG_OFFSET            6
//#define ORG_ZERO              7
//#define ORG_OK                8
//#define ORG_FAIL              9
#define ORG_ZERO                6

#define SpeedHigh               0               //楂橀�熷洖闆舵爣蹇楋紙鍘熺偣鍋忕疆涓嶄负0鎴栧洖闆舵柟寮�8~10锛�
#define SpeedLow                1               //浣庨�熷洖闆舵爣蹇楋紙鍘熺偣鍋忕疆涓�0涓斿洖闆舵柟寮忎负0~7锛�
extern void OrgEnCheck(void);
extern void F_OrgFunction(void);
extern void OrgDiCheck(void);
extern void OrgOutput(void);
extern UCHAR ZeroRunSpeed;

#endif /* FUN_INCLUDE_FUN23_ORGSEACH_H_ */

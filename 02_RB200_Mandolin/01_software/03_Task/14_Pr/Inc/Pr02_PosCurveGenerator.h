/*
 * Pr02_PosCurveGenerator.h
 *
 *  Created on: 2018骞�07鏈�02鏃�
 *      Author: zhuxc
 */

#ifndef Pr02_PosCurveGenerator_H
#define Pr02_PosCurveGenerator_H

/* 鍗曚綅涓� rpm,杞崲鎴愭壂鎻忓懆鏈熷唴鑴夊啿鏁�                                                                */
/*             1rpm 脳 Den 脳 125 us                                                                  */
/* ACC = -------------------------------                                                            */
/*        60 脳 1000 脳 1000  (min -->us)                                                             */
/* 杞崲鎴愯剦鍐睶15鏍煎紡,浜庢槸绠�鍖栨湁:                                                                    */
/*     3000 脳 20000 脳 125       125                                                                 */
/* = ---------------------- = --------                                                              */
/*      60 脳 1000 脳 1000         1                                                                  */
/*--------------------------------------------------------------------------------------------------*/
//#define AccDecBasicSpd  3000              /* 鍔犲噺閫熸椂闂村搴旂殑鏈�澶ч�熷害鍊�                           */
//#define EGearDen        20000             /* 瀹氫箟鐢靛瓙榻胯疆鐨勫垎姣嶅浐瀹氫负20000                        */
//#define ACCDECCoeff     125               /* ((AccDecBasicSpd * EGearDen * 125) / 60000000 )      */
//extern LONG PrModeSpdMax;        //鏈�澶ч�熷害闄愬埗
extern LONG EGearDen;
extern LLONG ACCDECCoeffQ15;
extern ULONG EncoderNum;         //鐢靛瓙榻胯疆姣斿垎瀛�;       
extern ULONG EncoderDen;         //鐢靛瓙榻胯疆姣斿垎姣�

extern void PosVelocityCoeffCount( void );
extern void PrSpeed_AccDec_CoefCount(void);
#endif

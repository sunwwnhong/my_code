 /*
 * Mot56_STO.h
 *
 *  Created on: 2024年12月16日
 *      Author: syhu
 */
 #ifndef Mot56_STO_H
#define Mot56_STO_H


#define STO_EN                  ((Prm.syssw1 & 0x0010) == 0x0010)    /* 功能码开启STO             */
#define STO_24VAlmResetMode     ((Prm.syssw1 & 0x0020) == 0x0020)    /* 故障复位方式选择             */
#define STO_ALM_WRN             ((Prm.syssw1 & 0x0040) == 0x0040)    /* 不使能报警方式，0故障,1警告  */


extern void STO_FaultOutOff( void );
//extern void STO_FaultReset( void );

#endif
 
/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/

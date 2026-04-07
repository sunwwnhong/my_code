/*
 * MotB_TEncCLB.h
 *
 *  Created on: 2022Äê12ÔÂ24ÈÕ
 *      Author: zhuxc
 */
#ifndef MOTB_TEncCLB_H
#define MOTB_TEncCLB_H
 #include <stdint.h>
 #ifdef __cplusplus
extern "C" {                 
#endif
 extern void MOTB_TileTformat(uint32_t base);
extern void MOTB_TileTformatRxCRC(uint32_t base);
extern void MOTB_TFORMAT_RX_CRC_init1( void );
extern void MOTB_TFORMAT_CLB_init1( void );
#ifdef __cplusplus
}
#endif
 #endif

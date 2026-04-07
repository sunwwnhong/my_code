/*
 * MotA_TEncCLB.h
 *
 *  Created on: 2022Äê12ÔÂ24ÈÕ
 *      Author: zhuxc
 */
#ifndef MOTA_TEncCLB_H
#define MOTA_TEncCLB_H
 #include <stdint.h>
 #ifdef __cplusplus
extern "C" {                 
#endif
 extern void MOTA_TileTformat(uint32_t base);
extern void MOTA_TileTformatRxCRC(uint32_t base);
extern void MOTA_TFORMAT_RX_CRC_init1( void );
extern void MOTA_TFORMAT_CLB_init1( void );
 #ifdef __cplusplus
}
#endif
 #endif

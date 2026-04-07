/*
 * CLA02_Encode.h
 *
 *  Created on: 2022Äê11ÔÂ17ÈÕ
 *      Author: zhuxc
 */
 #ifndef CLA02_Encode_H
#define CLA02_Encode_H
 
 extern void InitCpu1_SPI( void );
 extern void TFormat_WriteByteCmd( uint16_t, uint16_t);
extern uint16_t TFormat_WriteByteCheck( void );
extern uint16_t TFormat_ReadByte( uint16_t );
extern uint16_t TFormat_OnlineCheck( void );
extern void EncErrorClr_Cmd( void );
extern uint16_t EncErrClr_Check( void );
extern void TFormatEncDataRead_ID3( void );
extern void TFormat_ID3( void );
#endif

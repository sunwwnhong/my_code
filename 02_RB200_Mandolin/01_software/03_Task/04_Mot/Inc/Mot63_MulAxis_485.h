/*
 * Mot63_MulAxis_485.h
 *
 *  Created on: 2019Äê4ÔÂ26ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot63_MulAxis_485_H
#define Mot63_MulAxis_485_H

extern void MuxAxis485_Init( void );
extern USHORT MuxAxis485_Write( LONG RegNo, LONG Number, USHORT *RdBuf );
extern USHORT MuxAxis485_Read( LONG RegNo, LONG Number, USHORT *RdBuf );
extern SHORT MuxAxis485_SpdCmd( void );
extern SHORT MuxAxis485_ServoOnoff( void );
extern void MuxAxis485_LineOff( void );
#endif

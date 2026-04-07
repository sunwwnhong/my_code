/*
 * Mot38_AI12Deal.h
 *
 *  Created on: 2018Äê 09ÔÂ27ÈÕ
 *      Author: zhuxc
 */
#ifndef Mot38_AI12Deal_H
#define Mot38_AI12Deal_H
typedef struct
{
    SHORT ADCChannel10;                                      
    SHORT ADCChannel11;                                      
    SHORT ADCChannel20;                                      
    SHORT ADCChannel21;                                      
    LONG AI1LPFil;                                           
    LONG AI1LPFilo;                                          
    LONG AI2LPFil;                                           
    LONG AI2LPFilo;                                          
    UCHAR AI12AutoAdj;                                       
    UCHAR AI12Type;                                          
    USHORT AI12AutoAdjCnt;                                   
    LONG  AI1AutoSum;                                        
    LONG  AI2AutoSum;                                        
}ADCCHANNEL;
extern ADCCHANNEL AdcV;
extern void AI12DataInit( void );
extern void ADCChannel1And2Deal( void );
extern void AI1LPFilterInit( void );
extern void AI2LPFilterInit( void );
#endif

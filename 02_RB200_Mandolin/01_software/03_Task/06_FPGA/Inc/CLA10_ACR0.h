/*
 * CLA10_ACR0.h
 *
 *  Created on: 2022Äê8ÔÂ19ÈÕ
 *      Author: zhuxc
 */
#ifndef CLA10_ACR0_H
#define CLA10_ACR0_H
 
extern void CLA_TaskA( void );

#ifdef CPU1
extern void CLA_TaskB( void );
#endif
 extern void BrakePWM_Control( void );
 extern void ComLedStatu( void );
 #endif

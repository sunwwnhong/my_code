/*
 * CLA00_Main.h
 *
 *  Created on: 2022Äê8ÔÂ19ÈÕ
 *      Author: zhuxc
 */
 #ifndef CLA00_Main_H
#define CLA00_Main_H
 
#include "CLA01_Task.h"
#include "CLA02_Encode.h"
#include "CLA05_DSPUpdate.h"
#include "CLA06_IcHaus.h"
#include "CLA06_MotEncoder.h"
#include "CLA07_CTek5900.h"
#include "CLA07_MT6709.h"
#include "CLA08_Emif.h"
#include "CLA09_CLAVar.h"
#include "CLA10_ACR0.h"
 
extern void InitCLA1( void );
extern void CLA_init( void );
extern void CLA00_Task( void );
 #endif

/*
 * Enc07_TamagawaEnc.h
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: zhuxc
 */
 #ifndef Enc07_TamagawaEnc_H
#define Enc07_TamagawaEnc_H
 
extern void TawagamaEncSel(void);								 
extern void TawagamaEncControl_FPGA(void);						 
extern void TawagamaEncControlCmd_WriteToFPGA(void);			 
extern SHORT TamagawaEeprom_DataReadDeal(void);					 
extern void TawagamaEnc_CD_3(void);								 
extern UCHAR TamakawaMencClrStep(void);							 
extern void TamagawaEncWriteMnge(void);							 
extern void TamagawaEncTemperatureMnge(void);
#endif

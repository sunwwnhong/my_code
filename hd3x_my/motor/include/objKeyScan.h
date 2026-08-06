#ifndef __F_OBJ_KEYBOARD_SCAN_H__
#define __F_OBJ_KEYBOARD_SCAN_H__

// ----------------函数声明----------------------------------------------
extern void DisplayScan(void);
extern void DisplayScanPrepareRts(void);
extern void UpdateDisplayBuffer(void);
extern void WinkDeal(void);

extern void SPI_KEY_Configuration(void);
// ----------------函数声明结束------------------------------------------

#define DISPLAY_8LED_NUM    5   // 数码管个数
#define DISPLAY_LED_NUM     7   // LED个数

#endif


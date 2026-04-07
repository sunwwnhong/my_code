/*
 * Can08_TorqCmd.h
 *
 *  Created on: 2019骞�10鏈�10鏃�
 *      Author: xuezhushan
 */

#ifndef Can08_TorqCmd_H
#define Can08_TorqCmd_H

typedef struct
{
    LONG    TorCmdQ15;              //杞煩鎸囦护
    LONG    TargetTorqQ15;          //鐩爣杞煩
    LLONG   TorqRatioQ15;           //杞煩鏂滅巼
    LONG    MaxTorq;                //鏈�澶ц浆鐭╋紙鏍囧购鍊硷級
    LONG    PosTorqLimt;            //姝ｅ悜杞煩闄愬埗锛堟爣骞哄�硷級
    LONG    NegTorqLimt;            //璐熷悜杞煩闄愬埗锛堟爣骞哄�硷級
    UCHAR   TorqReachFlg;           //杞煩鍒拌揪鏍囧織
}CANOPENTORQ;
extern CANOPENTORQ CanTorq; 

extern LONG KpiCanOpenInputTrqRef(void);

#endif

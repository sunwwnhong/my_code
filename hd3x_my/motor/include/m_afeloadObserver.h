


#include "main.h"
#include "m_control.h"


typedef struct Load_Current_Observe_DEF
{
    f32 kin;
	f32 in;
	f32 udc_dev;
	f32 udc_dev_last;
	f32 udc_exp;
	f32 out;
	f32 out_last;
	f32 ka;
	f32 kb;
	f32 kc;

} Load_Current_Observe;

extern void LoadObserveLoop(void);
extern void LoadObserveStopStatus(void);




























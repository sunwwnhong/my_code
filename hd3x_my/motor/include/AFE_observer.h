

#include "main.h"
#include "m_control.h"




typedef struct Afe_Current_Observer_DEF{

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


} Afe_Current_Observer;

extern void AFE_LoadObserverLoop(void);
extern void AFE_LoadObserverInit(void);


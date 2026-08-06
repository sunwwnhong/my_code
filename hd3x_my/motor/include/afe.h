
#ifndef AFE_H_
#define AFE_H_

extern Uint16 SoftType;

#define AFE_INV_CON         ((1 == SoftType) && (0 == funcCode.code.AfeCommMode))
#define AFE_INV_485         ((1 == SoftType) && (1 == funcCode.code.AfeCommMode))
#define AFE_RECT            ((3 == SoftType))

struct BLACKBOX_CTRL_BITS
{
	Uint16 aCmpOper     :2;
	Uint16 bCmpOper     :2;
    Uint16 abLogicOper  :2;
	Uint16 aResult      :1;
    Uint16 bResult      :1;
    
	Uint16 aChannel     :3;
	Uint16 bChannel     :3;
    Uint16 sync         :1;
    Uint16 Enable       :1;
};

union BLACKBOX_CTRL
{
	Uint16 all;
	struct BLACKBOX_CTRL_BITS bit;
};
extern union BLACKBOX_CTRL BlackBoxCtrl;
extern int16 BlackBoxACmpValue;
extern int16 BlackBoxBCmpValue;
extern Uint16 BlackBoxDelayBeforeTrig;
extern Uint16 BlackBoxDelayAfterTrig;

#endif /* AFE_H_ */

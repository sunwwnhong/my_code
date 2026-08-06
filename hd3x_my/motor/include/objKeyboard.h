
#ifndef __F_KEYBOARD_H__
#define __F_KEYBOARD_H__

#include "main.h"



extern Uint16 LimitDeal(Uint16 signal,Uint16,Uint16,Uint16,int16);
extern void UpdateErrorDisplayBuffer(void);
extern void UpdataFuncCodeGrade(Uint16 funcCodeGrade[]);
extern Uint16 ModifyFunccodeUpDown(Uint16 index,Uint16 *data,int16 delta);
extern Uint16 ModifyFunccodeEnter(Uint16 index, Uint16 dataNew);
extern void KeyButtonOnDeal(void);      //显示操作处理
extern void Menu1OnPrg(void);
extern void DealCheckMenuModeGroupGrade(Uint16 flag);
extern void DispDataDeal(void);
extern void MenuInit(void);
extern union FUNC_ATTRIBUTE GetUxGroupAttribute(Uint16 group, Uint16 grade);

#define UP_KEY					1
#define DOWN_KEY				2
#define PRG  					0x0004
#define UP						0x0020
#define DOWN					0x0040
#define SHIFT  					0x0010
#define MFK  					0x0002
#define RUN  					0x0001
#define STOP  					0x0080
#define ENTER   				0x0008
#define QUICK					0x0100

#define SHIFTUP					0X0200
#define SHIFTDOWN				0X0400

// ====================================================================
// 8段式数码管的编码
#define DISPLAY_8LED_CODE_NUM       38  // 8段式数码管显示的字符个数
// 显示字符段码在数组中对应的下标
#define DISPLAY_0       0   // 0
#define DISPLAY_1       1   // 1
#define DISPLAY_2       2   // 2
#define DISPLAY_3       3   // 3
#define DISPLAY_4       4   // 4

#define DISPLAY_5       5   // 5
#define DISPLAY_6       6   // 6
#define DISPLAY_7       7   // 7
#define DISPLAY_8       8   // 8
#define DISPLAY_9       9   // 9

#define DISPLAY_A       10  // A
#define DISPLAY_B       11  // b
#define DISPLAY_C       12  // C
#define DISPLAY_D       13  // d
#define DISPLAY_E       14  // E

#define DISPLAY_F       15  // F
#define DISPLAY_P       16  // P
#define DISPLAY_H       17  // H
#define DISPLAY_J       18  // J
#define DISPLAY_L       19  // L

#define DISPLAY_n       20  // n
#define DISPLAY_r       21  // r
#define DISPLAY_U       22  // U
#define DISPLAY_y       23  // y
#define DISPLAY_G       24  // G

#define DISPLAY_h       25  // h
#define DISPLAY_I       26  // I
#define DISPLAY_N       27  // N
#define DISPLAY_o       28  // o
#define DISPLAY_q       29  // q

#define DISPLAY_T       30  // T
#define DISPLAY_t       31  // t
#define DISPLAY_u       32  // u/v，小写u/V
#define DISPLAY_NULL    33  // 全灭
#define DISPLAY_LINE    34  // -

#define DISPLAY_DOT     35  // 显示小数点，其他编码&即可
#define DISPLAY_ALL     36  // 全亮
//#define DISPLAY_c      (DISPLAY_8LED_CODE_NUM-1)  // 小写c



#define KEY_SWITCH		(1)  // MFK-switch
#define KEY_REV         (2)  // MFK-REV
#define KEY_FWD_JOG		(3)  // MFK-JOG
#define KEY_REV_JOG     (4)  // MFK-JOG
#define KEY_CLOSEPWM    (5)  // MFK-STOP
/*
// 用户密码检查
#define USER_PASSWORD_INPUT_HINT    0  // 显示-----
#define USER_PASSWORD_INPUT         1  // 输入用户密码
#define USER_PASSWORD_CHECK_OK      2  // 用户密码检验通过
*/
extern u16 chkUserPwdStep;
extern Uint16 superPassword;
extern Uint16 superPasswordData, otherPasswordData;

//#define USER_PARA_SAVE_FLAG1   1
//#define USER_PARA_SAVE_FLAG2   (0xFFFF - USER_PARA_SAVE_FLAG1)

//功能码密码检查
#define FUNC_PASSWORD_INPUT         0  // 输入用户密码
#define FUNC_PASSWORD_CHECK_OK      1  // 用户密码检验通过
extern Uint16 chkFuncPwdStep;


extern const Uint16 funcCodeGradeUser[];
extern const Uint16 funcCodeGradeSum[];
extern Uint16 limitedByOtherCodeIndex[];
extern Uint16 limitedByOtherCodeIndexNum;  // 上下限受其他功能码限制的功能码总数

extern Uint16 displayBits;			//显示位数
extern Uint16 keyMfkFlag;
extern Uint16 displayBuffer[];
extern const Uint16 LED_CODE[];
extern const Uint16 DISPLAY_CODE[];

extern Uint16 keyFlag;

extern Uint16 bOnShift;
//extern Uint16 ticker4LowerDisp;  // 运行时显示，最后2位不要更新过快

#define ON_UP_KEY       ACC_SPEED
#define ON_DOWN_KEY     DEC_SPEED

#define STOP_DISPLAY_NUM 16     // 停机时，LED显示参数的总数
#define RUN_DISPLAY_NUM  32     // 运行时，LED显示参数的总数
#define COMM_PARA_NUM    33     // 通讯读取停机或运行显示参数的个数

extern Uint16 checkMenuModePara;
extern Uint16 checkMenuModeCmd;
extern const union FUNC_ATTRIBUTE dispAttributeU0[];
extern const union FUNC_ATTRIBUTE dispAttributeU1[];
extern const union FUNC_ATTRIBUTE dispAttributeU2[];
extern const union FUNC_ATTRIBUTE dispAttributeU3[];
extern const union FUNC_ATTRIBUTE dispAttributeU4[];
extern const union FUNC_ATTRIBUTE dispAttributeU7[];
extern const union FUNC_ATTRIBUTE dispAttributeU8[];
extern const union FUNC_ATTRIBUTE dispAttributeU9[];
extern const union FUNC_ATTRIBUTE dispAttributeUA[];
extern const union FUNC_ATTRIBUTE dispAttributeUB[];
extern const union FUNC_ATTRIBUTE dispAttributeUF[];
extern Uint16 funcCodeGradeCurMenuMode[];
extern const Uint16 funcCodeGradeAll[];
extern Uint16 checkMenuModeSerachNone; 
//extern enum  CHECK_MENU_MODE_DEAL checkMenuModeDealStatus;

/*
enum MENU_MODE_OPERATE
{
    MENU_MODE_NONE,         // 
    MENU_MODE_ON_QUICK      // 按下QUICK键
};
extern enum MENU_MODE_OPERATE menuModeStatus;
*/
enum INVERTER_CODE_PWD_STATUS
{
    INVERTER_CODE_PWD_LOCK,          // 变频器密码, lock状态
    INVERTER_CODE_PWD_UNLOCK         // 变频器密码, unlock状态
};
extern enum INVERTER_CODE_PWD_STATUS inverterCodePwdStatus;     // 厂家密码，默认为0(lock)

//=================================
/*enum MENU_MODE
{
    MENU_MODE_NULL,         // 0, 空菜单
    MENU_MODE_BASE,         // 1, 基本菜单，主要为目前320功能码(出厂)
    MENU_MODE_ADVANCE,      // 2, 高级菜单，显示全部功能码
    MENU_MODE_MONITOR,      // 3, 监视菜单
    MENU_MODE_USER,         // 4, 用户定制菜单
    MENU_MODE_CHECK,        // 5, 校验菜单，仅显示与出厂值不同的功能码
    MENU_MODE_LAST          // 6, 最近更改的10个功能码
};

enum MENU_MODE
{
    MENU_MODE_NULL,
    MENU_MODE_BASE,         // 1, 基本菜单，主要为目前320功能码(出厂)
    MENU_MODE_USER,         // 2, 用户定制菜单
    MENU_MODE_CHECK        // 3, 校验菜单，仅显示与出厂值不同的功能码
};
//=================================
*/
//=================================
enum MENU_INDEX
{
    MENU_INDEX_0,            // 0, 零级索引
    MENU_INDEX_1,            // 1, 一级索引
    MENU_INDEX_2,            // 2, 二级索引
    MENU_INDEX_3,            // 3, 三级索引
    MENU_INDEX_4             // 4, 四级索引
};
extern enum MENU_MODE menuModeTmp; 
extern enum MENU_MODE menuMode; 
/*
// 将菜单操作封装在一起
typedef struct tagSysMenu
{
    void (*onPrgFunc)();         // 在当前菜单按下 PRG   键的处理函数指针
    void (*onUpFunc)();          // 在当前菜单按下 UP    键的处理函数指针
    void (*onEnterFunc)();       // 在当前菜单按下 ENTER 键的处理函数指针
    void (*onMfkFunc)();         // 在当前菜单按下 MF.K  键的处理函数指针
    void (*onDownFunc)();        // 在当前菜单按下 DOWN  键的处理函数指针
    void (*onShiftFunc)();       // 在当前菜单按下 SHIFT 键的处理函数指针
    void (*onRunFunc)();         // 在当前菜单按下 RUN   键的处理函数指针
    void (*onStopFunc)();        // 在当前菜单按下 STOP  键的处理函数指针
    void (*onQuickFunc)();       // 在当前菜单按下 QUICK 键的处理函数指针

    void (*UpdateDisplayBuffer)(); // 当前菜单下更新显示数据缓冲的函数指针
}sysMenu, *sysMenuHandle;

extern const sysMenu menu[];
*/
/*
struct MENU_ATTRIBUTE
{
    Uint16 operateDigit;    // 各级菜单下，当前操作位. 0-4
    
    Uint16 winkFlag;        // 数码管闪烁控制寄存器, 对应位为1时闪烁.
// bit7,数码管左边第1个(最左边); bit3, 数码管左边第5个(最右边)

    Uint16 winkFlagLed;     // led闪烁控制寄存器. bit0-Led0; bit1-Led1,...
// 可以将winkFlag和winkFlagLed放在一起
};
extern struct MENU_ATTRIBUTE menuAttri[];
*/
/*
enum MENU0_DISP_STATUS
{
    MENU0_DISP_STATUS_RUN_STOP,     // 运行/停机显示
    MENU0_DISP_STATUS_UP_DOWN,      // up/down时显示
    MENU0_DISP_STATUS_ERROR,        // 故障/告警显示
    MENU0_DISP_STATUS_ESTOP,        // 急停显示
    MENU0_DISP_STATUS_ANTIRUN,      // 反转禁止显示
    MENU0_DISP_STATUS_TUNE,         // 调谐显示
    MENU0_DISP_STATUS_DIAGNOSE		// 自检显示
};
extern enum MENU0_DISP_STATUS menu0DispStatus;     // 0级菜单的显示状态

// 电压等级与额定电压的关系见 invTypeLimitTable[]
struct INV_PARA
{
    Uint16 type;                // 变频器机型
    
    Uint16 ratingVoltage;       // 变频器的额定电压
    Uint16 volLevel;            // 变频器的电压等级
    Uint16 pointLimit;          // 电流、电机参数的小数点
    Uint16 bitAccDecStart;      // 加减速时间出厂值为大值的起始机型
};
extern struct INV_PARA invPara;
*/
/*
#define MENU_LEVEL_NUM  6   // 一共有_级菜单
enum MENU_LEVEL
{        
    MENU_LEVEL_0,           // 0级菜单
    MENU_LEVEL_1,           // 1级菜单
    MENU_LEVEL_2,           // 2级菜单
    MENU_LEVEL_3,           // 3级菜单
    MENU_LEVEL_PWD_HINT,    // 提示输入密码
    MENU_LEVEL_PWD_INPUT    // 输入密码
};
extern enum MENU_LEVEL menuLevel;
*/
// LED灯的编码
//#define DISPLAY_LED_CODE_NUM    11   // LED灯的显示方式个数
// LED在数组中对应的下标

// ====================================================================
// LED灯的编码
//#define DISPLAY_LED_CODE_NUM    11   // LED灯的显示方式个数
// LED在数组中对应的下标
#define LED_RUN      0   // Run
#define LED_LOCAL    1   // Local/Remote
#define LED_DIR      2   // FWD/REV
#define LED_TUNE     3   // TUNE/TC
#define LED_V        4   // V
#define LED_A        5   // A
#define LED_HZ       6   // Hz
#define LED_RPM      7   // RPM
#define LED_PERCENT  8   // %
#define LED_ALL      9   // 全亮
#define LED_NULL     (DISPLAY_LED_CODE_NUM-1)  // 全灭
#if 0	
#define LED_RUN		0   // Run
#define LED_LOCAL	1   // Local/Remote
#define LED_V		2   // V
#define LED_A		3   // A
#define LED_HZ		4   // Hz
#define LED_RPM		5   // RPM
#define LED_PERCENT	6   // %
#define LED_ALL		7   // 全亮
#define LED_NULL	8	// 全灭
#define LED_FWD		9
#define LED_TUNE	10
#endif
/*
enum CHECK_MENU_MODE_DEAL
{
    CHECK_MENU_MODE_DEAL_CMD,           // 指令，准备开始
    CHECK_MENU_MODE_DEAL_SERACHING,     // 正在搜索
    CHECK_MENU_MODE_DEAL_END_NONE,      // 搜索全部功能码，没有发现与出厂值不同的功能码
    CHECK_MENU_MODE_DEAL_END_ONCE       // 搜索找到一个
};
*/
extern Uint16 mainLoopTicker;

struct CURRENT_FUNC_CODE
{
    Uint16 index;               // 当前功能码在funcCode.all[]数组的下标

    Uint16 group;               // 当前功能码的group
    Uint16 grade;               // 当前功能码的grade
};
extern struct CURRENT_FUNC_CODE curFc; // 当前功能码
#endif









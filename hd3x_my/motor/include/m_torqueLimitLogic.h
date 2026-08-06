//==================================================================================================
//
// 转矩限制逻辑
//
//
//
// Time-stamp: <2012-2-15 16:19:45  author, 0000>
//
//==================================================================================================


#ifndef __M_TORQUE_LIMIT_LOGIC_H__
#define __M_TORQUE_LIMIT_LOGIC_H__



#include "main.h"




enum LimitStates
{
    MENU_LIMIT,             // 0  菜单设定的转矩限幅
    SINGLE_PHASING,         // 1  
    UNDERVOLTAGE,           // 2  低电压
    THERMAL_OVERLOAD,       // 3  变压器过载
    FIELD_WEAKENING,        // 4  弱磁
    BRAKING,                // 5  叠频制动
    CELL_OVERLOAD,          // 6  单元过载 
    OV_REGEN_LIMIT          // 7  
};






void LimitLogic(
    f32 *max,                       // pointer to maximum limit
    f32 *min,                       // pointer to minimum limit
    enum LimitStates *limitUsed     // pointer to limit used 
    )
;








#endif  //__M_TORQUE_LIMIT_LOGIC_H__













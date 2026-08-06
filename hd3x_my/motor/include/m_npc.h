//==================================================================================================
//
// 三电平中点箝位
//
//
//
// Time-stamp: <2012-11-13 14:36:22  author, 0000>
//
//==================================================================================================


#ifndef __M_NPC_H__
#define __M_NPC_H__



#include "main.h" 




struct NPC_DATA
{
    f32 upn;    // 正负母线偏差

    f32 ua;
    f32 ub;
    f32 uc;

    f32 ia;
    f32 ib;
    f32 ic;

    f32 v0;     // 输出

    
};
extern struct NPC_DATA npcData;

//void NpcDeal(struct NPC_DATA *p);
void NpcDeal1(struct NPC_DATA *p);


#endif  //__M_NPC_H__





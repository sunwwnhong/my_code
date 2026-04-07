  
  
  
#include "Main.h"
#include "MotB_TEncCLB.h"
 #define MOTB_TFORMAT_CLB_BASE                               CLB2_BASE
#define MOTB_TFORMAT_RX_CRC_BASE                            CLB4_BASE
  
#define HLC_OPCODE_R0 0x0
#define HLC_OPCODE_R1 0x1
#define HLC_OPCODE_R2 0x2
#define HLC_OPCODE_R3 0x3
#define HLC_OPCODE_C0 0x4
#define HLC_OPCODE_C1 0x5
#define HLC_OPCODE_C2 0x6
 #define HLC_OPCODE_MOV    0x00
#define HLC_OPCODE_MOV_T1 0x01
#define HLC_OPCODE_MOV_T2 0x02
#define HLC_OPCODE_PUSH   0x03
#define HLC_OPCODE_PULL   0x04
#define HLC_OPCODE_ADD    0x05
#define HLC_OPCODE_SUB    0x06
#define HLC_OPCODE_INTR   0x07
  
  
#define MOTB_TileTformat_PIPELINE_MODE 0
#define MOTB_TileTformat_CFG_OUTLUT_0 0x5fb986
#define MOTB_TileTformat_CFG_OUTLUT_1 0x55000d
#define MOTB_TileTformat_CFG_OUTLUT_2 0x55000c
#define MOTB_TileTformat_CFG_OUTLUT_3 0x550003
#define MOTB_TileTformat_CFG_OUTLUT_4 0x55001a
#define MOTB_TileTformat_CFG_OUTLUT_5 0x4401d6
#define MOTB_TileTformat_CFG_OUTLUT_6 0x0
#define MOTB_TileTformat_CFG_OUTLUT_7 0x0
 #define MOTB_TileTformat_CFG_LUT4_IN0   0x331b
#define MOTB_TileTformat_CFG_LUT4_IN1   0x372c
 #define MOTB_TileTformat_CFG_LUT4_IN2   0x658d
#define MOTB_TileTformat_CFG_LUT4_IN3   0x1a1
#define MOTB_TileTformat_CFG_LUT4_FN10  ((0xaeaa0000) | 0xffa0)
#define MOTB_TileTformat_CFG_LUT4_FN2   0x4040
 
#define MOTB_TileTformat_CFG_FSM_EXT_IN0      0x2de3
#define MOTB_TileTformat_CFG_FSM_EXT_IN1      0x6122
#define MOTB_TileTformat_CFG_FSM_EXTRA_IN0    0x0
#define MOTB_TileTformat_CFG_FSM_EXTRA_IN1    0x0
#define MOTB_TileTformat_CFG_FSM_NEXT_STATE_0 ((0xcccc0000) | 0x50fa)
#define MOTB_TileTformat_CFG_FSM_NEXT_STATE_1 ((0x66cc0000) | 0x50fa)
#define MOTB_TileTformat_CFG_FSM_NEXT_STATE_2 ((0xcccc0000) | 0x5f0a)
#define MOTB_TileTformat_CFG_FSM_LUT_FN10     ((0xeeee0000) | 0xaa)
#define MOTB_TileTformat_CFG_FSM_LUT_FN2      0xaaaa
#define MOTB_TileTformat_FSM_MISC_CONTROL     0x0
 #define MOTB_TileTformat_CFG_COUNTER_RESET   0x127
#define MOTB_TileTformat_CFG_COUNTER_EVENT   0x0
#define MOTB_TileTformat_CFG_COUNTER_MODE_0  0x6e
#define MOTB_TileTformat_CFG_COUNTER_MODE_1  0x108
#define MOTB_TileTformat_CFG_TAP_SEL          0x0
#define MOTB_TileTformat_CFG_MISC_CONTROL    (0x0 | MOTB_TileTformat_FSM_MISC_CONTROL)
 #define MOTB_TileTformat_COUNTER_0_MATCH1_VAL  23
#define MOTB_TileTformat_COUNTER_0_MATCH2_VAL  47
#define MOTB_TileTformat_COUNTER_0_LOAD_VAL    0
#define MOTB_TileTformat_COUNTER_1_MATCH1_VAL  10
#define MOTB_TileTformat_COUNTER_1_MATCH2_VAL  19
#define MOTB_TileTformat_COUNTER_1_LOAD_VAL    10
#define MOTB_TileTformat_COUNTER_2_MATCH1_VAL  0
#define MOTB_TileTformat_COUNTER_2_MATCH2_VAL  0
#define MOTB_TileTformat_COUNTER_2_LOAD_VAL    0
 
#define MOTB_TileTformat_HLC_EVENT_SEL 0x17
#define MOTB_TileTformat_HLC_R0_INIT 110
#define MOTB_TileTformat_HLC_R1_INIT 0
#define MOTB_TileTformat_HLC_R2_INIT 0
#define MOTB_TileTformat_HLC_R3_INIT 0
 #define MOTB_TileTformat_HLCINSTR_0 (0 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_C1<<3 | HLC_OPCODE_R2)
#define MOTB_TileTformat_HLCINSTR_1 (0 << 11 | HLC_OPCODE_ADD << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R2)
#define MOTB_TileTformat_HLCINSTR_2 (1 << 11 | HLC_OPCODE_MOV_T2 << 6 | HLC_OPCODE_R2<<3 | HLC_OPCODE_C1)
#define MOTB_TileTformat_HLCINSTR_3 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_4 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_5 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_6 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_7 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_8 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_9 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_10    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_11    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_12    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_13    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_14    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_15    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_16    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_17    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_18    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_19    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_20    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_21    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_22    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_23    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_24    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_25    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_26    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_27    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_28    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_29    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_30    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformat_HLCINSTR_31    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
 
 
#define MOTB_TileTformat_OUTPUT_COND_CTR_0 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_1 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_2 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_3 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_4 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_5 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_6 0x0
#define MOTB_TileTformat_OUTPUT_COND_CTR_7 0x0
  
 #define MOTB_TileTformatRxCRC_PIPELINE_MODE 0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_0 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_1 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_2 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_3 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_4 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_5 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_6 0x0
#define MOTB_TileTformatRxCRC_CFG_OUTLUT_7 0x0
 #define MOTB_TileTformatRxCRC_CFG_LUT4_IN0   0x3b78
#define MOTB_TileTformatRxCRC_CFG_LUT4_IN1   0x6c99
#define MOTB_TileTformatRxCRC_CFG_LUT4_IN2   0x140
#define MOTB_TileTformatRxCRC_CFG_LUT4_IN3   0x160
#define MOTB_TileTformatRxCRC_CFG_LUT4_FN10  ((0x80000) | 0x7777)
#define MOTB_TileTformatRxCRC_CFG_LUT4_FN2   0x4444
 #define MOTB_TileTformatRxCRC_CFG_FSM_EXT_IN0      0x383
#define MOTB_TileTformatRxCRC_CFG_FSM_EXT_IN1      0x21
#define MOTB_TileTformatRxCRC_CFG_FSM_EXTRA_IN0    0x0
#define MOTB_TileTformatRxCRC_CFG_FSM_EXTRA_IN1    0x0
#define MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_0 ((0x00000) | 0xa0fa)
#define MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_1 ((0x99080000) | 0xffa8)
#define MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_2 ((0x00000) | 0x0)
#define MOTB_TileTformatRxCRC_CFG_FSM_LUT_FN10     ((0xaaaa0000) | 0x0)
#define MOTB_TileTformatRxCRC_CFG_FSM_LUT_FN2      0x0
#define MOTB_TileTformatRxCRC_FSM_MISC_CONTROL     0x0
 #define MOTB_TileTformatRxCRC_CFG_COUNTER_RESET   0xee
#define MOTB_TileTformatRxCRC_CFG_COUNTER_EVENT   0x6877
#define MOTB_TileTformatRxCRC_CFG_COUNTER_MODE_0  0x3c00
#define MOTB_TileTformatRxCRC_CFG_COUNTER_MODE_1  0x2108
#define MOTB_TileTformatRxCRC_CFG_TAP_SEL          0x0
#define MOTB_TileTformatRxCRC_CFG_MISC_CONTROL    (0x400083f | MOTB_TileTformatRxCRC_FSM_MISC_CONTROL)
 #define MOTB_TileTformatRxCRC_COUNTER_0_MATCH1_VAL  1
#define MOTB_TileTformatRxCRC_COUNTER_0_MATCH2_VAL  9
#define MOTB_TileTformatRxCRC_COUNTER_0_LOAD_VAL    1
#define MOTB_TileTformatRxCRC_COUNTER_1_MATCH1_VAL  11
#define MOTB_TileTformatRxCRC_COUNTER_1_MATCH2_VAL  0
#define MOTB_TileTformatRxCRC_COUNTER_1_LOAD_VAL    1
#define MOTB_TileTformatRxCRC_COUNTER_2_MATCH1_VAL  0x7
#define MOTB_TileTformatRxCRC_COUNTER_2_MATCH2_VAL  0x101
#define MOTB_TileTformatRxCRC_COUNTER_2_LOAD_VAL    0
 
#define MOTB_TileTformatRxCRC_HLC_EVENT_SEL 0x2f20
#define MOTB_TileTformatRxCRC_HLC_R0_INIT 0
#define MOTB_TileTformatRxCRC_HLC_R1_INIT 0
#define MOTB_TileTformatRxCRC_HLC_R2_INIT 0
#define MOTB_TileTformatRxCRC_HLC_R3_INIT 0
 #define MOTB_TileTformatRxCRC_HLCINSTR_0    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_1    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_2    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_3    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_4    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_5    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_6    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_7    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_8    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R2<<3 | HLC_OPCODE_C2)
#define MOTB_TileTformatRxCRC_HLCINSTR_9    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_10   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_11   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_12   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_13   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_14   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_15   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_16   (1 << 11 | HLC_OPCODE_INTR << 6 | 5)
#define MOTB_TileTformatRxCRC_HLCINSTR_17   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_18   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_19   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_20   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_21   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_22   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_23   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_24   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_25   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_26   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_27   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_28   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_29   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_30   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTB_TileTformatRxCRC_HLCINSTR_31   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
 #define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_0 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_1 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_2 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_3 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_4 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_5 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_6 0x0
#define MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_7 0x0
 
uint16_t MOTB_TileTformatHLCInst[CLB_NUM_HLC_INSTR + 1] =
{
    MOTB_TileTformat_HLCINSTR_0,
    MOTB_TileTformat_HLCINSTR_1,
    MOTB_TileTformat_HLCINSTR_2,
    MOTB_TileTformat_HLCINSTR_3,
    MOTB_TileTformat_HLCINSTR_4,
    MOTB_TileTformat_HLCINSTR_5,
    MOTB_TileTformat_HLCINSTR_6,
    MOTB_TileTformat_HLCINSTR_7,
    MOTB_TileTformat_HLCINSTR_8,
    MOTB_TileTformat_HLCINSTR_9,
    MOTB_TileTformat_HLCINSTR_10,
    MOTB_TileTformat_HLCINSTR_11,
    MOTB_TileTformat_HLCINSTR_12,
    MOTB_TileTformat_HLCINSTR_13,
    MOTB_TileTformat_HLCINSTR_14,
    MOTB_TileTformat_HLCINSTR_15,
    MOTB_TileTformat_HLCINSTR_16,
    MOTB_TileTformat_HLCINSTR_17,
    MOTB_TileTformat_HLCINSTR_18,
    MOTB_TileTformat_HLCINSTR_19,
    MOTB_TileTformat_HLCINSTR_20,
    MOTB_TileTformat_HLCINSTR_21,
    MOTB_TileTformat_HLCINSTR_22,
    MOTB_TileTformat_HLCINSTR_23,
    MOTB_TileTformat_HLCINSTR_24,
    MOTB_TileTformat_HLCINSTR_25,
    MOTB_TileTformat_HLCINSTR_26,
    MOTB_TileTformat_HLCINSTR_27,
    MOTB_TileTformat_HLCINSTR_28,
    MOTB_TileTformat_HLCINSTR_29,
    MOTB_TileTformat_HLCINSTR_30,
    MOTB_TileTformat_HLCINSTR_31
};
 
uint16_t MOTB_TileTformatRxCRCHLCInst[CLB_NUM_HLC_INSTR + 1] =
{
    MOTB_TileTformatRxCRC_HLCINSTR_0,
    MOTB_TileTformatRxCRC_HLCINSTR_1,
    MOTB_TileTformatRxCRC_HLCINSTR_2,
    MOTB_TileTformatRxCRC_HLCINSTR_3,
    MOTB_TileTformatRxCRC_HLCINSTR_4,
    MOTB_TileTformatRxCRC_HLCINSTR_5,
    MOTB_TileTformatRxCRC_HLCINSTR_6,
    MOTB_TileTformatRxCRC_HLCINSTR_7,
    MOTB_TileTformatRxCRC_HLCINSTR_8,
    MOTB_TileTformatRxCRC_HLCINSTR_9,
    MOTB_TileTformatRxCRC_HLCINSTR_10,
    MOTB_TileTformatRxCRC_HLCINSTR_11,
    MOTB_TileTformatRxCRC_HLCINSTR_12,
    MOTB_TileTformatRxCRC_HLCINSTR_13,
    MOTB_TileTformatRxCRC_HLCINSTR_14,
    MOTB_TileTformatRxCRC_HLCINSTR_15,
    MOTB_TileTformatRxCRC_HLCINSTR_16,
    MOTB_TileTformatRxCRC_HLCINSTR_17,
    MOTB_TileTformatRxCRC_HLCINSTR_18,
    MOTB_TileTformatRxCRC_HLCINSTR_19,
    MOTB_TileTformatRxCRC_HLCINSTR_20,
    MOTB_TileTformatRxCRC_HLCINSTR_21,
    MOTB_TileTformatRxCRC_HLCINSTR_22,
    MOTB_TileTformatRxCRC_HLCINSTR_23,
    MOTB_TileTformatRxCRC_HLCINSTR_24,
    MOTB_TileTformatRxCRC_HLCINSTR_25,
    MOTB_TileTformatRxCRC_HLCINSTR_26,
    MOTB_TileTformatRxCRC_HLCINSTR_27,
    MOTB_TileTformatRxCRC_HLCINSTR_28,
    MOTB_TileTformatRxCRC_HLCINSTR_29,
    MOTB_TileTformatRxCRC_HLCINSTR_30,
    MOTB_TileTformatRxCRC_HLCINSTR_31
};
 
 void MOTB_TileTformat(uint32_t base)
{
    uint16_t i;
     CLB_disablePipelineMode(base);
     CLB_configOutputLUT(base, CLB_OUT0, MOTB_TileTformat_CFG_OUTLUT_0);
    CLB_configOutputLUT(base, CLB_OUT1, MOTB_TileTformat_CFG_OUTLUT_1);
    CLB_configOutputLUT(base, CLB_OUT2, MOTB_TileTformat_CFG_OUTLUT_2);
    CLB_configOutputLUT(base, CLB_OUT3, MOTB_TileTformat_CFG_OUTLUT_3);
    CLB_configOutputLUT(base, CLB_OUT4, MOTB_TileTformat_CFG_OUTLUT_4);
    CLB_configOutputLUT(base, CLB_OUT5, MOTB_TileTformat_CFG_OUTLUT_5);
    CLB_configOutputLUT(base, CLB_OUT6, MOTB_TileTformat_CFG_OUTLUT_6);
    CLB_configOutputLUT(base, CLB_OUT7, MOTB_TileTformat_CFG_OUTLUT_7);
     CLB_configAOC(base, CLB_AOC0, MOTB_TileTformat_OUTPUT_COND_CTR_0);
    CLB_configAOC(base, CLB_AOC1, MOTB_TileTformat_OUTPUT_COND_CTR_1);
    CLB_configAOC(base, CLB_AOC2, MOTB_TileTformat_OUTPUT_COND_CTR_2);
    CLB_configAOC(base, CLB_AOC3, MOTB_TileTformat_OUTPUT_COND_CTR_3);
    CLB_configAOC(base, CLB_AOC4, MOTB_TileTformat_OUTPUT_COND_CTR_4);
    CLB_configAOC(base, CLB_AOC5, MOTB_TileTformat_OUTPUT_COND_CTR_5);
    CLB_configAOC(base, CLB_AOC6, MOTB_TileTformat_OUTPUT_COND_CTR_6);
    CLB_configAOC(base, CLB_AOC7, MOTB_TileTformat_OUTPUT_COND_CTR_7);
      
    CLB_selectLUT4Inputs(base, MOTB_TileTformat_CFG_LUT4_IN0, MOTB_TileTformat_CFG_LUT4_IN1, MOTB_TileTformat_CFG_LUT4_IN2, MOTB_TileTformat_CFG_LUT4_IN3);
    CLB_configLUT4Function(base, MOTB_TileTformat_CFG_LUT4_FN10, MOTB_TileTformat_CFG_LUT4_FN2);
      
    CLB_selectFSMInputs(base, MOTB_TileTformat_CFG_FSM_EXT_IN0, MOTB_TileTformat_CFG_FSM_EXT_IN1, MOTB_TileTformat_CFG_FSM_EXTRA_IN0, MOTB_TileTformat_CFG_FSM_EXTRA_IN1);
    CLB_configFSMNextState(base, MOTB_TileTformat_CFG_FSM_NEXT_STATE_0, MOTB_TileTformat_CFG_FSM_NEXT_STATE_1, MOTB_TileTformat_CFG_FSM_NEXT_STATE_2);
    CLB_configFSMLUTFunction(base, MOTB_TileTformat_CFG_FSM_LUT_FN10, MOTB_TileTformat_CFG_FSM_LUT_FN2);
      
    CLB_selectCounterInputs(base, MOTB_TileTformat_CFG_COUNTER_RESET, MOTB_TileTformat_CFG_COUNTER_EVENT, MOTB_TileTformat_CFG_COUNTER_MODE_0, MOTB_TileTformat_CFG_COUNTER_MODE_1);
    CLB_configMiscCtrlModes(base, MOTB_TileTformat_CFG_MISC_CONTROL);
    CLB_configCounterLoadMatch(base, CLB_CTR0, MOTB_TileTformat_COUNTER_0_LOAD_VAL, MOTB_TileTformat_COUNTER_0_MATCH1_VAL, MOTB_TileTformat_COUNTER_0_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR1, MOTB_TileTformat_COUNTER_1_LOAD_VAL, MOTB_TileTformat_COUNTER_1_MATCH1_VAL, MOTB_TileTformat_COUNTER_1_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR2, MOTB_TileTformat_COUNTER_2_LOAD_VAL, MOTB_TileTformat_COUNTER_2_MATCH1_VAL, MOTB_TileTformat_COUNTER_2_MATCH2_VAL);
    CLB_configCounterTapSelects(base, MOTB_TileTformat_CFG_TAP_SEL);
      
    CLB_configHLCEventSelect(base, MOTB_TileTformat_HLC_EVENT_SEL);
    CLB_setHLCRegisters(base, MOTB_TileTformat_HLC_R0_INIT, MOTB_TileTformat_HLC_R1_INIT, MOTB_TileTformat_HLC_R2_INIT, MOTB_TileTformat_HLC_R3_INIT);
     for(i = 0; i <= CLB_NUM_HLC_INSTR; i++)
    {
        CLB_programHLCInstruction(base, i, MOTB_TileTformatHLCInst[i]);
    }
}
 void MOTB_TileTformatRxCRC(uint32_t base)
{
    uint16_t i;
     CLB_disablePipelineMode(base);
     CLB_configOutputLUT(base, CLB_OUT0, MOTB_TileTformatRxCRC_CFG_OUTLUT_0);
    CLB_configOutputLUT(base, CLB_OUT1, MOTB_TileTformatRxCRC_CFG_OUTLUT_1);
    CLB_configOutputLUT(base, CLB_OUT2, MOTB_TileTformatRxCRC_CFG_OUTLUT_2);
    CLB_configOutputLUT(base, CLB_OUT3, MOTB_TileTformatRxCRC_CFG_OUTLUT_3);
    CLB_configOutputLUT(base, CLB_OUT4, MOTB_TileTformatRxCRC_CFG_OUTLUT_4);
    CLB_configOutputLUT(base, CLB_OUT5, MOTB_TileTformatRxCRC_CFG_OUTLUT_5);
    CLB_configOutputLUT(base, CLB_OUT6, MOTB_TileTformatRxCRC_CFG_OUTLUT_6);
    CLB_configOutputLUT(base, CLB_OUT7, MOTB_TileTformatRxCRC_CFG_OUTLUT_7);
     CLB_configAOC(base, CLB_AOC0, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_0);
    CLB_configAOC(base, CLB_AOC1, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_1);
    CLB_configAOC(base, CLB_AOC2, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_2);
    CLB_configAOC(base, CLB_AOC3, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_3);
    CLB_configAOC(base, CLB_AOC4, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_4);
    CLB_configAOC(base, CLB_AOC5, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_5);
    CLB_configAOC(base, CLB_AOC6, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_6);
    CLB_configAOC(base, CLB_AOC7, MOTB_TileTformatRxCRC_OUTPUT_COND_CTR_7);
      
    CLB_selectLUT4Inputs(base, MOTB_TileTformatRxCRC_CFG_LUT4_IN0, MOTB_TileTformatRxCRC_CFG_LUT4_IN1, MOTB_TileTformatRxCRC_CFG_LUT4_IN2, MOTB_TileTformatRxCRC_CFG_LUT4_IN3);
    CLB_configLUT4Function(base, MOTB_TileTformatRxCRC_CFG_LUT4_FN10, MOTB_TileTformatRxCRC_CFG_LUT4_FN2);
      
    CLB_selectFSMInputs(base, MOTB_TileTformatRxCRC_CFG_FSM_EXT_IN0, MOTB_TileTformatRxCRC_CFG_FSM_EXT_IN1, MOTB_TileTformatRxCRC_CFG_FSM_EXTRA_IN0, MOTB_TileTformatRxCRC_CFG_FSM_EXTRA_IN1);
    CLB_configFSMNextState(base, MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_0, MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_1, MOTB_TileTformatRxCRC_CFG_FSM_NEXT_STATE_2);
    CLB_configFSMLUTFunction(base, MOTB_TileTformatRxCRC_CFG_FSM_LUT_FN10, MOTB_TileTformatRxCRC_CFG_FSM_LUT_FN2);
      
    CLB_selectCounterInputs(base, MOTB_TileTformatRxCRC_CFG_COUNTER_RESET, MOTB_TileTformatRxCRC_CFG_COUNTER_EVENT, MOTB_TileTformatRxCRC_CFG_COUNTER_MODE_0, MOTB_TileTformatRxCRC_CFG_COUNTER_MODE_1);
    CLB_configMiscCtrlModes(base, MOTB_TileTformatRxCRC_CFG_MISC_CONTROL);
    CLB_configCounterLoadMatch(base, CLB_CTR0, MOTB_TileTformatRxCRC_COUNTER_0_LOAD_VAL, MOTB_TileTformatRxCRC_COUNTER_0_MATCH1_VAL, MOTB_TileTformatRxCRC_COUNTER_0_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR1, MOTB_TileTformatRxCRC_COUNTER_1_LOAD_VAL, MOTB_TileTformatRxCRC_COUNTER_1_MATCH1_VAL, MOTB_TileTformatRxCRC_COUNTER_1_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR2, MOTB_TileTformatRxCRC_COUNTER_2_LOAD_VAL, MOTB_TileTformatRxCRC_COUNTER_2_MATCH1_VAL, MOTB_TileTformatRxCRC_COUNTER_2_MATCH2_VAL);
    CLB_configCounterTapSelects(base, MOTB_TileTformatRxCRC_CFG_TAP_SEL);
      
    CLB_configHLCEventSelect(base, MOTB_TileTformatRxCRC_HLC_EVENT_SEL);
    CLB_setHLCRegisters(base, MOTB_TileTformatRxCRC_HLC_R0_INIT, MOTB_TileTformatRxCRC_HLC_R1_INIT, MOTB_TileTformatRxCRC_HLC_R2_INIT, MOTB_TileTformatRxCRC_HLC_R3_INIT);
     for(i = 0; i <= CLB_NUM_HLC_INSTR; i++)
    {
        CLB_programHLCInstruction(base, i, MOTB_TileTformatRxCRCHLCInst[i]);
    }
}
 void MOTB_TFORMAT_CLB_init1( void )
{
    CLB_setOutputMask(MOTB_TFORMAT_CLB_BASE,
                (0UL << 0UL) |
                (1UL << 13UL) |
                (1UL << 17UL) |
                (1UL << 18UL) |
                (1UL << 19UL) |
                (1UL << 20UL) |
                (1UL << 24UL), true);
    CLB_enableOutputMaskUpdates(MOTB_TFORMAT_CLB_BASE);
    CLB_disableSPIBufferAccess(MOTB_TFORMAT_CLB_BASE);
    CLB_configSPIBufferLoadSignal(MOTB_TFORMAT_CLB_BASE, 0);
    CLB_configSPIBufferShift(MOTB_TFORMAT_CLB_BASE, 0);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN0, CLB_GP_IN_MUX_GP_REG);
     CLB_selectInputFilter(MOTB_TFORMAT_CLB_BASE, CLB_IN0, CLB_FILTER_RISING_EDGE);
    CLB_disableInputPipelineMode(MOTB_TFORMAT_CLB_BASE, CLB_IN0);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_INPUT8);
    CLB_configGlobalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTB_TFORMAT_CLB_BASE, CLB_IN1);
    CLB_selectInputFilter(MOTB_TFORMAT_CLB_BASE, CLB_IN1, CLB_FILTER_FALLING_EDGE);
    CLB_disableInputPipelineMode(MOTB_TFORMAT_CLB_BASE, CLB_IN1);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_INPUT8);
    CLB_configGlobalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTB_TFORMAT_CLB_BASE, CLB_IN2);
    CLB_selectInputFilter(MOTB_TFORMAT_CLB_BASE, CLB_IN2, CLB_FILTER_NONE);
    CLB_disableInputPipelineMode(MOTB_TFORMAT_CLB_BASE, CLB_IN2);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_INPUT8);
    CLB_configGlobalInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTB_TFORMAT_CLB_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTB_TFORMAT_CLB_BASE, CLB_IN3);
    CLB_selectInputFilter(MOTB_TFORMAT_CLB_BASE, CLB_IN3, CLB_FILTER_ANY_EDGE);
    CLB_disableInputPipelineMode(MOTB_TFORMAT_CLB_BASE, CLB_IN3);
    CLB_setGPREG(MOTB_TFORMAT_CLB_BASE,0);
    CLB_enableCLB(MOTB_TFORMAT_CLB_BASE);
}
void MOTB_TFORMAT_RX_CRC_init1( void )
{
    CLB_setOutputMask(MOTB_TFORMAT_RX_CRC_BASE,
                (0UL << 0UL), true);
    CLB_enableOutputMaskUpdates(MOTB_TFORMAT_RX_CRC_BASE);
    CLB_disableSPIBufferAccess(MOTB_TFORMAT_RX_CRC_BASE);
    CLB_configSPIBufferLoadSignal(MOTB_TFORMAT_RX_CRC_BASE, 0);
    CLB_configSPIBufferShift(MOTB_TFORMAT_RX_CRC_BASE, 0);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB2_OUT18);
    CLB_configGPInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN0);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB2_OUT17);
    CLB_configGPInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN1);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_CLB2_OUT20);
    CLB_configGPInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN2);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_CLB2_OUT19);
    CLB_configGPInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN3);
      
     CLB_configLocalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_CLB2_OUT20);
    CLB_configGPInputMux(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_FILTER_FALLING_EDGE);
    CLB_enableInputPipelineMode(MOTB_TFORMAT_RX_CRC_BASE, CLB_IN4);
    CLB_setGPREG(MOTB_TFORMAT_RX_CRC_BASE,0);
    CLB_enableCLB(MOTB_TFORMAT_RX_CRC_BASE);
}

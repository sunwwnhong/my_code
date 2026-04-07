  
  
  
#include "Main.h"
#include "MotA_TEncCLB.h"
 #define MOTA_TFORMAT_CLB_BASE                               CLB1_BASE
#define MOTA_TFORMAT_RX_CRC_BASE                            CLB3_BASE
  
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
  
  
#define MOTA_TileTformat_PIPELINE_MODE 0
#define MOTA_TileTformat_CFG_OUTLUT_0 0x5fb986
#define MOTA_TileTformat_CFG_OUTLUT_1 0x55000d
#define MOTA_TileTformat_CFG_OUTLUT_2 0x55000c
#define MOTA_TileTformat_CFG_OUTLUT_3 0x550003
#define MOTA_TileTformat_CFG_OUTLUT_4 0x55001a
#define MOTA_TileTformat_CFG_OUTLUT_5 0x4401d6
#define MOTA_TileTformat_CFG_OUTLUT_6 0x0
#define MOTA_TileTformat_CFG_OUTLUT_7 0x0
 #define MOTA_TileTformat_CFG_LUT4_IN0   0x331b
#define MOTA_TileTformat_CFG_LUT4_IN1   0x372c
 
#define MOTA_TileTformat_CFG_LUT4_IN2   0x658d
#define MOTA_TileTformat_CFG_LUT4_IN3   0x1a1
#define MOTA_TileTformat_CFG_LUT4_FN10  ((0xaeaa0000) | 0xffa0)
#define MOTA_TileTformat_CFG_LUT4_FN2   0x4040
 
#define MOTA_TileTformat_CFG_FSM_EXT_IN0      0x2de3
#define MOTA_TileTformat_CFG_FSM_EXT_IN1      0x6122
#define MOTA_TileTformat_CFG_FSM_EXTRA_IN0    0x0
#define MOTA_TileTformat_CFG_FSM_EXTRA_IN1    0x0
#define MOTA_TileTformat_CFG_FSM_NEXT_STATE_0 ((0xcccc0000) | 0x50fa)
#define MOTA_TileTformat_CFG_FSM_NEXT_STATE_1 ((0x66cc0000) | 0x50fa)
#define MOTA_TileTformat_CFG_FSM_NEXT_STATE_2 ((0xcccc0000) | 0x5f0a)
#define MOTA_TileTformat_CFG_FSM_LUT_FN10     ((0xeeee0000) | 0xaa)
#define MOTA_TileTformat_CFG_FSM_LUT_FN2      0xaaaa
#define MOTA_TileTformat_FSM_MISC_CONTROL     0x0
 #define MOTA_TileTformat_CFG_COUNTER_RESET   0x127
#define MOTA_TileTformat_CFG_COUNTER_EVENT   0x0
#define MOTA_TileTformat_CFG_COUNTER_MODE_0  0x6e
#define MOTA_TileTformat_CFG_COUNTER_MODE_1  0x108
#define MOTA_TileTformat_CFG_TAP_SEL          0x0
#define MOTA_TileTformat_CFG_MISC_CONTROL    (0x0 | MOTA_TileTformat_FSM_MISC_CONTROL)
 #define MOTA_TileTformat_COUNTER_0_MATCH1_VAL  23
#define MOTA_TileTformat_COUNTER_0_MATCH2_VAL  47
#define MOTA_TileTformat_COUNTER_0_LOAD_VAL    0
#define MOTA_TileTformat_COUNTER_1_MATCH1_VAL  10
#define MOTA_TileTformat_COUNTER_1_MATCH2_VAL  19
#define MOTA_TileTformat_COUNTER_1_LOAD_VAL    10
#define MOTA_TileTformat_COUNTER_2_MATCH1_VAL  0
#define MOTA_TileTformat_COUNTER_2_MATCH2_VAL  0
#define MOTA_TileTformat_COUNTER_2_LOAD_VAL    0
 
#define MOTA_TileTformat_HLC_EVENT_SEL 0x17
#define MOTA_TileTformat_HLC_R0_INIT 110
#define MOTA_TileTformat_HLC_R1_INIT 0
#define MOTA_TileTformat_HLC_R2_INIT 0
#define MOTA_TileTformat_HLC_R3_INIT 0
 #define MOTA_TileTformat_HLCINSTR_0 (0 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_C1<<3 | HLC_OPCODE_R2)
#define MOTA_TileTformat_HLCINSTR_1 (0 << 11 | HLC_OPCODE_ADD << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R2)
#define MOTA_TileTformat_HLCINSTR_2 (1 << 11 | HLC_OPCODE_MOV_T2 << 6 | HLC_OPCODE_R2<<3 | HLC_OPCODE_C1)
#define MOTA_TileTformat_HLCINSTR_3 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_4 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_5 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_6 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_7 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_8 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_9 (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_10    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_11    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_12    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_13    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_14    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_15    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_16    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_17    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_18    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_19    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_20    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_21    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_22    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_23    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_24    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_25    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_26    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_27    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_28    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_29    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_30    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformat_HLCINSTR_31    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
 
 
#define MOTA_TileTformat_OUTPUT_COND_CTR_0 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_1 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_2 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_3 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_4 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_5 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_6 0x0
#define MOTA_TileTformat_OUTPUT_COND_CTR_7 0x0
  
 #define MOTA_TileTformatRxCRC_PIPELINE_MODE 0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_0 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_1 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_2 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_3 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_4 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_5 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_6 0x0
#define MOTA_TileTformatRxCRC_CFG_OUTLUT_7 0x0
 #define MOTA_TileTformatRxCRC_CFG_LUT4_IN0   0x3b78
#define MOTA_TileTformatRxCRC_CFG_LUT4_IN1   0x6c99
#define MOTA_TileTformatRxCRC_CFG_LUT4_IN2   0x140
#define MOTA_TileTformatRxCRC_CFG_LUT4_IN3   0x160
#define MOTA_TileTformatRxCRC_CFG_LUT4_FN10  ((0x80000) | 0x7777)
#define MOTA_TileTformatRxCRC_CFG_LUT4_FN2   0x4444
 #define MOTA_TileTformatRxCRC_CFG_FSM_EXT_IN0      0x383
#define MOTA_TileTformatRxCRC_CFG_FSM_EXT_IN1      0x21
#define MOTA_TileTformatRxCRC_CFG_FSM_EXTRA_IN0    0x0
#define MOTA_TileTformatRxCRC_CFG_FSM_EXTRA_IN1    0x0
#define MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_0 ((0x00000) | 0xa0fa)
#define MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_1 ((0x99080000) | 0xffa8)
#define MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_2 ((0x00000) | 0x0)
#define MOTA_TileTformatRxCRC_CFG_FSM_LUT_FN10     ((0xaaaa0000) | 0x0)
#define MOTA_TileTformatRxCRC_CFG_FSM_LUT_FN2      0x0
#define MOTA_TileTformatRxCRC_FSM_MISC_CONTROL     0x0
 #define MOTA_TileTformatRxCRC_CFG_COUNTER_RESET   0xee
#define MOTA_TileTformatRxCRC_CFG_COUNTER_EVENT   0x6877
#define MOTA_TileTformatRxCRC_CFG_COUNTER_MODE_0  0x3c00
#define MOTA_TileTformatRxCRC_CFG_COUNTER_MODE_1  0x2108
#define MOTA_TileTformatRxCRC_CFG_TAP_SEL          0x0
#define MOTA_TileTformatRxCRC_CFG_MISC_CONTROL    (0x400083f | MOTA_TileTformatRxCRC_FSM_MISC_CONTROL)
 #define MOTA_TileTformatRxCRC_COUNTER_0_MATCH1_VAL  1
#define MOTA_TileTformatRxCRC_COUNTER_0_MATCH2_VAL  9
#define MOTA_TileTformatRxCRC_COUNTER_0_LOAD_VAL    1
#define MOTA_TileTformatRxCRC_COUNTER_1_MATCH1_VAL  11
#define MOTA_TileTformatRxCRC_COUNTER_1_MATCH2_VAL  0
#define MOTA_TileTformatRxCRC_COUNTER_1_LOAD_VAL    1
#define MOTA_TileTformatRxCRC_COUNTER_2_MATCH1_VAL  0x7
#define MOTA_TileTformatRxCRC_COUNTER_2_MATCH2_VAL  0x101
#define MOTA_TileTformatRxCRC_COUNTER_2_LOAD_VAL    0
 
#define MOTA_TileTformatRxCRC_HLC_EVENT_SEL 0x2f20
#define MOTA_TileTformatRxCRC_HLC_R0_INIT 0
#define MOTA_TileTformatRxCRC_HLC_R1_INIT 0
#define MOTA_TileTformatRxCRC_HLC_R2_INIT 0
#define MOTA_TileTformatRxCRC_HLC_R3_INIT 0
 #define MOTA_TileTformatRxCRC_HLCINSTR_0    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_1    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_2    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_3    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_4    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_5    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_6    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_7    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_8    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R2<<3 | HLC_OPCODE_C2)
#define MOTA_TileTformatRxCRC_HLCINSTR_9    (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_10   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_11   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_12   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_13   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_14   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_15   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_16   (1 << 11 | HLC_OPCODE_INTR << 6 | 5)
#define MOTA_TileTformatRxCRC_HLCINSTR_17   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_18   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_19   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_20   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_21   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_22   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_23   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_24   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_25   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_26   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_27   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_28   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_29   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_30   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
#define MOTA_TileTformatRxCRC_HLCINSTR_31   (1 << 11 | HLC_OPCODE_MOV << 6 | HLC_OPCODE_R0<<3 | HLC_OPCODE_R0)
 
 
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_0 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_1 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_2 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_3 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_4 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_5 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_6 0x0
#define MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_7 0x0
 
uint16_t MOTA_TileTformatHLCInst[CLB_NUM_HLC_INSTR + 1] =
{
    MOTA_TileTformat_HLCINSTR_0,
    MOTA_TileTformat_HLCINSTR_1,
    MOTA_TileTformat_HLCINSTR_2,
    MOTA_TileTformat_HLCINSTR_3,
    MOTA_TileTformat_HLCINSTR_4,
    MOTA_TileTformat_HLCINSTR_5,
    MOTA_TileTformat_HLCINSTR_6,
    MOTA_TileTformat_HLCINSTR_7,
    MOTA_TileTformat_HLCINSTR_8,
    MOTA_TileTformat_HLCINSTR_9,
    MOTA_TileTformat_HLCINSTR_10,
    MOTA_TileTformat_HLCINSTR_11,
    MOTA_TileTformat_HLCINSTR_12,
    MOTA_TileTformat_HLCINSTR_13,
    MOTA_TileTformat_HLCINSTR_14,
    MOTA_TileTformat_HLCINSTR_15,
    MOTA_TileTformat_HLCINSTR_16,
    MOTA_TileTformat_HLCINSTR_17,
    MOTA_TileTformat_HLCINSTR_18,
    MOTA_TileTformat_HLCINSTR_19,
    MOTA_TileTformat_HLCINSTR_20,
    MOTA_TileTformat_HLCINSTR_21,
    MOTA_TileTformat_HLCINSTR_22,
    MOTA_TileTformat_HLCINSTR_23,
    MOTA_TileTformat_HLCINSTR_24,
    MOTA_TileTformat_HLCINSTR_25,
    MOTA_TileTformat_HLCINSTR_26,
    MOTA_TileTformat_HLCINSTR_27,
    MOTA_TileTformat_HLCINSTR_28,
    MOTA_TileTformat_HLCINSTR_29,
    MOTA_TileTformat_HLCINSTR_30,
    MOTA_TileTformat_HLCINSTR_31
};
 
uint16_t MOTA_TileTformatRxCRCHLCInst[CLB_NUM_HLC_INSTR + 1] =
{
    MOTA_TileTformatRxCRC_HLCINSTR_0,
    MOTA_TileTformatRxCRC_HLCINSTR_1,
    MOTA_TileTformatRxCRC_HLCINSTR_2,
    MOTA_TileTformatRxCRC_HLCINSTR_3,
    MOTA_TileTformatRxCRC_HLCINSTR_4,
    MOTA_TileTformatRxCRC_HLCINSTR_5,
    MOTA_TileTformatRxCRC_HLCINSTR_6,
    MOTA_TileTformatRxCRC_HLCINSTR_7,
    MOTA_TileTformatRxCRC_HLCINSTR_8,
    MOTA_TileTformatRxCRC_HLCINSTR_9,
    MOTA_TileTformatRxCRC_HLCINSTR_10,
    MOTA_TileTformatRxCRC_HLCINSTR_11,
    MOTA_TileTformatRxCRC_HLCINSTR_12,
    MOTA_TileTformatRxCRC_HLCINSTR_13,
    MOTA_TileTformatRxCRC_HLCINSTR_14,
    MOTA_TileTformatRxCRC_HLCINSTR_15,
    MOTA_TileTformatRxCRC_HLCINSTR_16,
    MOTA_TileTformatRxCRC_HLCINSTR_17,
    MOTA_TileTformatRxCRC_HLCINSTR_18,
    MOTA_TileTformatRxCRC_HLCINSTR_19,
    MOTA_TileTformatRxCRC_HLCINSTR_20,
    MOTA_TileTformatRxCRC_HLCINSTR_21,
    MOTA_TileTformatRxCRC_HLCINSTR_22,
    MOTA_TileTformatRxCRC_HLCINSTR_23,
    MOTA_TileTformatRxCRC_HLCINSTR_24,
    MOTA_TileTformatRxCRC_HLCINSTR_25,
    MOTA_TileTformatRxCRC_HLCINSTR_26,
    MOTA_TileTformatRxCRC_HLCINSTR_27,
    MOTA_TileTformatRxCRC_HLCINSTR_28,
    MOTA_TileTformatRxCRC_HLCINSTR_29,
    MOTA_TileTformatRxCRC_HLCINSTR_30,
    MOTA_TileTformatRxCRC_HLCINSTR_31
};
 
 void MOTA_TileTformat(uint32_t base)
{
    uint16_t i;
     CLB_disablePipelineMode(base);
     CLB_configOutputLUT(base, CLB_OUT0, MOTA_TileTformat_CFG_OUTLUT_0);
    CLB_configOutputLUT(base, CLB_OUT1, MOTA_TileTformat_CFG_OUTLUT_1);
    CLB_configOutputLUT(base, CLB_OUT2, MOTA_TileTformat_CFG_OUTLUT_2);
    CLB_configOutputLUT(base, CLB_OUT3, MOTA_TileTformat_CFG_OUTLUT_3);
    CLB_configOutputLUT(base, CLB_OUT4, MOTA_TileTformat_CFG_OUTLUT_4);
    CLB_configOutputLUT(base, CLB_OUT5, MOTA_TileTformat_CFG_OUTLUT_5);
    CLB_configOutputLUT(base, CLB_OUT6, MOTA_TileTformat_CFG_OUTLUT_6);
    CLB_configOutputLUT(base, CLB_OUT7, MOTA_TileTformat_CFG_OUTLUT_7);
     CLB_configAOC(base, CLB_AOC0, MOTA_TileTformat_OUTPUT_COND_CTR_0);
    CLB_configAOC(base, CLB_AOC1, MOTA_TileTformat_OUTPUT_COND_CTR_1);
    CLB_configAOC(base, CLB_AOC2, MOTA_TileTformat_OUTPUT_COND_CTR_2);
    CLB_configAOC(base, CLB_AOC3, MOTA_TileTformat_OUTPUT_COND_CTR_3);
    CLB_configAOC(base, CLB_AOC4, MOTA_TileTformat_OUTPUT_COND_CTR_4);
    CLB_configAOC(base, CLB_AOC5, MOTA_TileTformat_OUTPUT_COND_CTR_5);
    CLB_configAOC(base, CLB_AOC6, MOTA_TileTformat_OUTPUT_COND_CTR_6);
    CLB_configAOC(base, CLB_AOC7, MOTA_TileTformat_OUTPUT_COND_CTR_7);
      
    CLB_selectLUT4Inputs(base, MOTA_TileTformat_CFG_LUT4_IN0, MOTA_TileTformat_CFG_LUT4_IN1, MOTA_TileTformat_CFG_LUT4_IN2, MOTA_TileTformat_CFG_LUT4_IN3);
    CLB_configLUT4Function(base, MOTA_TileTformat_CFG_LUT4_FN10, MOTA_TileTformat_CFG_LUT4_FN2);
      
    CLB_selectFSMInputs(base, MOTA_TileTformat_CFG_FSM_EXT_IN0, MOTA_TileTformat_CFG_FSM_EXT_IN1, MOTA_TileTformat_CFG_FSM_EXTRA_IN0, MOTA_TileTformat_CFG_FSM_EXTRA_IN1);
    CLB_configFSMNextState(base, MOTA_TileTformat_CFG_FSM_NEXT_STATE_0, MOTA_TileTformat_CFG_FSM_NEXT_STATE_1, MOTA_TileTformat_CFG_FSM_NEXT_STATE_2);
    CLB_configFSMLUTFunction(base, MOTA_TileTformat_CFG_FSM_LUT_FN10, MOTA_TileTformat_CFG_FSM_LUT_FN2);
      
    CLB_selectCounterInputs(base, MOTA_TileTformat_CFG_COUNTER_RESET, MOTA_TileTformat_CFG_COUNTER_EVENT, MOTA_TileTformat_CFG_COUNTER_MODE_0, MOTA_TileTformat_CFG_COUNTER_MODE_1);
    CLB_configMiscCtrlModes(base, MOTA_TileTformat_CFG_MISC_CONTROL);
    CLB_configCounterLoadMatch(base, CLB_CTR0, MOTA_TileTformat_COUNTER_0_LOAD_VAL, MOTA_TileTformat_COUNTER_0_MATCH1_VAL, MOTA_TileTformat_COUNTER_0_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR1, MOTA_TileTformat_COUNTER_1_LOAD_VAL, MOTA_TileTformat_COUNTER_1_MATCH1_VAL, MOTA_TileTformat_COUNTER_1_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR2, MOTA_TileTformat_COUNTER_2_LOAD_VAL, MOTA_TileTformat_COUNTER_2_MATCH1_VAL, MOTA_TileTformat_COUNTER_2_MATCH2_VAL);
    CLB_configCounterTapSelects(base, MOTA_TileTformat_CFG_TAP_SEL);
      
    CLB_configHLCEventSelect(base, MOTA_TileTformat_HLC_EVENT_SEL);
    CLB_setHLCRegisters(base, MOTA_TileTformat_HLC_R0_INIT, MOTA_TileTformat_HLC_R1_INIT, MOTA_TileTformat_HLC_R2_INIT, MOTA_TileTformat_HLC_R3_INIT);
     for(i = 0; i <= CLB_NUM_HLC_INSTR; i++)
    {
        CLB_programHLCInstruction(base, i, MOTA_TileTformatHLCInst[i]);
    }
}
 
void MOTA_TileTformatRxCRC(uint32_t base)
{
    uint16_t i;
     CLB_disablePipelineMode(base);
     CLB_configOutputLUT(base, CLB_OUT0, MOTA_TileTformatRxCRC_CFG_OUTLUT_0);
    CLB_configOutputLUT(base, CLB_OUT1, MOTA_TileTformatRxCRC_CFG_OUTLUT_1);
    CLB_configOutputLUT(base, CLB_OUT2, MOTA_TileTformatRxCRC_CFG_OUTLUT_2);
    CLB_configOutputLUT(base, CLB_OUT3, MOTA_TileTformatRxCRC_CFG_OUTLUT_3);
    CLB_configOutputLUT(base, CLB_OUT4, MOTA_TileTformatRxCRC_CFG_OUTLUT_4);
    CLB_configOutputLUT(base, CLB_OUT5, MOTA_TileTformatRxCRC_CFG_OUTLUT_5);
    CLB_configOutputLUT(base, CLB_OUT6, MOTA_TileTformatRxCRC_CFG_OUTLUT_6);
    CLB_configOutputLUT(base, CLB_OUT7, MOTA_TileTformatRxCRC_CFG_OUTLUT_7);
     CLB_configAOC(base, CLB_AOC0, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_0);
    CLB_configAOC(base, CLB_AOC1, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_1);
    CLB_configAOC(base, CLB_AOC2, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_2);
    CLB_configAOC(base, CLB_AOC3, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_3);
    CLB_configAOC(base, CLB_AOC4, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_4);
    CLB_configAOC(base, CLB_AOC5, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_5);
    CLB_configAOC(base, CLB_AOC6, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_6);
    CLB_configAOC(base, CLB_AOC7, MOTA_TileTformatRxCRC_OUTPUT_COND_CTR_7);
      
    CLB_selectLUT4Inputs(base, MOTA_TileTformatRxCRC_CFG_LUT4_IN0, MOTA_TileTformatRxCRC_CFG_LUT4_IN1, MOTA_TileTformatRxCRC_CFG_LUT4_IN2, MOTA_TileTformatRxCRC_CFG_LUT4_IN3);
    CLB_configLUT4Function(base, MOTA_TileTformatRxCRC_CFG_LUT4_FN10, MOTA_TileTformatRxCRC_CFG_LUT4_FN2);
      
    CLB_selectFSMInputs(base, MOTA_TileTformatRxCRC_CFG_FSM_EXT_IN0, MOTA_TileTformatRxCRC_CFG_FSM_EXT_IN1, MOTA_TileTformatRxCRC_CFG_FSM_EXTRA_IN0, MOTA_TileTformatRxCRC_CFG_FSM_EXTRA_IN1);
    CLB_configFSMNextState(base, MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_0, MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_1, MOTA_TileTformatRxCRC_CFG_FSM_NEXT_STATE_2);
    CLB_configFSMLUTFunction(base, MOTA_TileTformatRxCRC_CFG_FSM_LUT_FN10, MOTA_TileTformatRxCRC_CFG_FSM_LUT_FN2);
      
    CLB_selectCounterInputs(base, MOTA_TileTformatRxCRC_CFG_COUNTER_RESET, MOTA_TileTformatRxCRC_CFG_COUNTER_EVENT, MOTA_TileTformatRxCRC_CFG_COUNTER_MODE_0, MOTA_TileTformatRxCRC_CFG_COUNTER_MODE_1);
    CLB_configMiscCtrlModes(base, MOTA_TileTformatRxCRC_CFG_MISC_CONTROL);
    CLB_configCounterLoadMatch(base, CLB_CTR0, MOTA_TileTformatRxCRC_COUNTER_0_LOAD_VAL, MOTA_TileTformatRxCRC_COUNTER_0_MATCH1_VAL, MOTA_TileTformatRxCRC_COUNTER_0_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR1, MOTA_TileTformatRxCRC_COUNTER_1_LOAD_VAL, MOTA_TileTformatRxCRC_COUNTER_1_MATCH1_VAL, MOTA_TileTformatRxCRC_COUNTER_1_MATCH2_VAL);
    CLB_configCounterLoadMatch(base, CLB_CTR2, MOTA_TileTformatRxCRC_COUNTER_2_LOAD_VAL, MOTA_TileTformatRxCRC_COUNTER_2_MATCH1_VAL, MOTA_TileTformatRxCRC_COUNTER_2_MATCH2_VAL);
    CLB_configCounterTapSelects(base, MOTA_TileTformatRxCRC_CFG_TAP_SEL);
      
    CLB_configHLCEventSelect(base, MOTA_TileTformatRxCRC_HLC_EVENT_SEL);
    CLB_setHLCRegisters(base, MOTA_TileTformatRxCRC_HLC_R0_INIT, MOTA_TileTformatRxCRC_HLC_R1_INIT, MOTA_TileTformatRxCRC_HLC_R2_INIT, MOTA_TileTformatRxCRC_HLC_R3_INIT);
     for(i = 0; i <= CLB_NUM_HLC_INSTR; i++)
    {
        CLB_programHLCInstruction(base, i, MOTA_TileTformatRxCRCHLCInst[i]);
    }
}
 void MOTA_TFORMAT_CLB_init1()
{
    CLB_setOutputMask(MOTA_TFORMAT_CLB_BASE,
                (0UL << 0UL) |
                (1UL << 13UL) |
                (1UL << 17UL) |
                (1UL << 18UL) |
                (1UL << 19UL) |
                (1UL << 20UL) |
                (1UL << 24UL), true);
    CLB_enableOutputMaskUpdates(MOTA_TFORMAT_CLB_BASE);
    CLB_disableSPIBufferAccess(MOTA_TFORMAT_CLB_BASE);
    CLB_configSPIBufferLoadSignal(MOTA_TFORMAT_CLB_BASE, 0);
    CLB_configSPIBufferShift(MOTA_TFORMAT_CLB_BASE, 0);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN0, CLB_GP_IN_MUX_GP_REG);
     CLB_selectInputFilter(MOTA_TFORMAT_CLB_BASE, CLB_IN0, CLB_FILTER_RISING_EDGE);
    CLB_disableInputPipelineMode(MOTA_TFORMAT_CLB_BASE, CLB_IN0);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_INPUT7);
    CLB_configGlobalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTA_TFORMAT_CLB_BASE, CLB_IN1);
    CLB_selectInputFilter(MOTA_TFORMAT_CLB_BASE, CLB_IN1, CLB_FILTER_FALLING_EDGE);
    CLB_disableInputPipelineMode(MOTA_TFORMAT_CLB_BASE, CLB_IN1);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_INPUT7);
    CLB_configGlobalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTA_TFORMAT_CLB_BASE, CLB_IN2);
    CLB_selectInputFilter(MOTA_TFORMAT_CLB_BASE, CLB_IN2, CLB_FILTER_NONE);
    CLB_disableInputPipelineMode(MOTA_TFORMAT_CLB_BASE, CLB_IN2);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_INPUT7);
    CLB_configGlobalInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGPInputMux(MOTA_TFORMAT_CLB_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_enableSynchronization(MOTA_TFORMAT_CLB_BASE, CLB_IN3);
    CLB_selectInputFilter(MOTA_TFORMAT_CLB_BASE, CLB_IN3, CLB_FILTER_ANY_EDGE);
    CLB_disableInputPipelineMode(MOTA_TFORMAT_CLB_BASE, CLB_IN3);
    CLB_setGPREG(MOTA_TFORMAT_CLB_BASE,0);
    CLB_enableCLB(MOTA_TFORMAT_CLB_BASE);
}
void MOTA_TFORMAT_RX_CRC_init1()
{
    CLB_setOutputMask(MOTA_TFORMAT_RX_CRC_BASE,
                (0UL << 0UL), true);
    CLB_enableOutputMaskUpdates(MOTA_TFORMAT_RX_CRC_BASE);
    CLB_disableSPIBufferAccess(MOTA_TFORMAT_RX_CRC_BASE);
    CLB_configSPIBufferLoadSignal(MOTA_TFORMAT_RX_CRC_BASE, 0);
    CLB_configSPIBufferShift(MOTA_TFORMAT_RX_CRC_BASE, 0);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB1_OUT18);
    CLB_configGPInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN0, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN0);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB1_OUT17);
    CLB_configGPInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN1, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN1);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_CLB1_OUT20);
    CLB_configGPInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN2, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN2);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_CLB1_OUT19);
    CLB_configGPInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN3, CLB_FILTER_NONE);
    CLB_enableInputPipelineMode(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN3);
      
     CLB_configLocalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configGlobalInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_CLB1_OUT20);
    CLB_configGPInputMux(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_GP_IN_MUX_EXTERNAL);
     CLB_selectInputFilter(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN4, CLB_FILTER_FALLING_EDGE);
    CLB_enableInputPipelineMode(MOTA_TFORMAT_RX_CRC_BASE, CLB_IN4);
    CLB_setGPREG(MOTA_TFORMAT_RX_CRC_BASE,0);
    CLB_enableCLB(MOTA_TFORMAT_RX_CRC_BASE);
}

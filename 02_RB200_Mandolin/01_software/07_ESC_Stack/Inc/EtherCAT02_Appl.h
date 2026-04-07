/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup CiA402appl CiA402 Sample Application
 * @{
 */

/**
\file cia402appl.h
\author EthercatSSC@beckhoff.com
\brief CiA402 specific defines; objects; Axes structure

\version 5.12

<br>Changes to version V5.11:<br>
V5.12 CIA402 1: change define value STATUSWORD_STATE_SWITCHEDONDISABLED<br>
V5.12 CIA402 2: update control word mask for transition 3 (Ready to switch on  to Switched on)<br>
V5.12 CiA402 3: add 16bit padding to process data of csv and csp mode<br>
<br>Changes to version V5.01:<br>
V5.11 CiA402 1: "append padding byte to ""csv/csp"" process data (basic process data has odd word length), add pack directive"<br>
V5.11 COE1: update invalid end entry in the object dictionaries (error with some compilers)<br>
<br>Changes to version - :<br>
V5.01 : Start file change log
 */

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "EtherCAT04_ObjDeal.h"



#ifndef _CIA402_H_
#define _CIA402_H_

/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/
/*---------------------------------------------
-    ControlWord Commands Mask (IEC61800_184e)
-----------------------------------------------*/
#define CONTROLWORD_COMMAND_SHUTDOWN_MASK                    0x0087 /**< \brief Shutdown command mask*/
/*ECATCHANGE_START(V5.12) CIA402 2*/
#define CONTROLWORD_COMMAND_SWITCHON_MASK                    0x008F /**< \brief Switch on command mask*/
/*ECATCHANGE_END(V5.12) CIA402 2*/
#define CONTROLWORD_COMMAND_SWITCHON_ENABLEOPERATION_MASK    0x008F /**< \brief Switch on & Enable command mask*/
#define CONTROLWORD_COMMAND_DISABLEVOLTAGE_MASK              0x0082 /**< \brief Disable voltage command mask*/
#define CONTROLWORD_COMMAND_QUICKSTOP_MASK                   0x0086 /**< \brief Quickstop command mask*/
#define CONTROLWORD_COMMAND_DISABLEOPERATION_MASK            0x008F /**< \brief Disable operation command mask*/
#define CONTROLWORD_COMMAND_ENABLEOPERATION_MASK             0x008F /**< \brief Enable operation command mask*/
#define CONTROLWORD_COMMAND_FAULTRESET_MASK                  0x0080 /**< \brief Fault reset command mask*/


/*---------------------------------------------
-    ControlWord Commands (IEC61800_184e)
-----------------------------------------------*/
#define CONTROLWORD_COMMAND_SHUTDOWN                         0x0006 /**< \brief Shutdown command*/
#define CONTROLWORD_COMMAND_SWITCHON                         0x0007 /**< \brief Switch on command*/
#define CONTROLWORD_COMMAND_SWITCHON_ENABLEOPERATION         0x000F /**< \brief Switch on & Enable command*/
#define CONTROLWORD_COMMAND_DISABLEVOLTAGE                   0x0000 /**< \brief Disable voltage command*/
#define CONTROLWORD_COMMAND_QUICKSTOP                        0x0002 /**< \brief Quickstop command*/
#define CONTROLWORD_COMMAND_DISABLEOPERATION                 0x0007 /**< \brief Disable operation command*/
#define CONTROLWORD_COMMAND_ENABLEOPERATION                  0x000F /**< \brief Enable operation command*/
#define CONTROLWORD_COMMAND_FAULTRESET                       0x0080 /**< \brief Fault reset command*/


/*---------------------------------------------
-    StatusWord Masks and Flags
-----------------------------------------------*/
#define STATUSWORD_STATE_MASK                                0x006F /**< \brief State mask*/
#define STATUSWORD_VOLTAGE_ENABLED                           0x0010 /**< \brief Indicate high voltage enabled*/
#define STATUSWORD_WARNING                                   0x0080 /**< \brief Warning active*/
#define STATUSWORD_MANUFACTORSPECIFIC                        0x0100 /**< \brief Manufacturer specific*/
#define STATUSWORD_INTERNAL_LIMIT                            0x0800 /**< \brief Internal limit*/
#define STATUSWORD_REMOTE                                    0x0200 /**< \brief Set if the control word is processed*/
#define STATUSWORD_TARGET_REACHED                            0x0400 /**< \brief Target reached*/
#define STATUSWORD_INTERNALLIMITACTIVE                       0x0800 /**< \brief Internal limit active*/
#define STATUSWORD_DRIVE_FOLLOWS_COMMAND                     0x1000 /**< \brief Drive follows command (used in cyclic synchronous modes)*/


/*---------------------------------------------
-    StatusWord
-----------------------------------------------*/
#define STATUSWORD_STATE_NOTREADYTOSWITCHON                  0x0000 /**< \brief Not ready to switch on*/
/* ECATCHANGE_START(V5.12) CIA402 1*/
#define STATUSWORD_STATE_SWITCHEDONDISABLED                  0x0040 /**< \brief Switched on but disabled*/
/* ECATCHANGE_END(V5.12) CIA402 1*/
#define STATUSWORD_STATE_READYTOSWITCHON                     0x0021 /**< \brief Ready to switch on*/
#define STATUSWORD_STATE_SWITCHEDON                          0x0023 /**< \brief Switched on*/
#define STATUSWORD_STATE_OPERATIONENABLED                    0x0027 /**< \brief Operation enabled*/
#define STATUSWORD_STATE_QUICKSTOPACTIVE                     0x0007 /**< \brief Quickstop active*/
#define STATUSWORD_STATE_FAULTREACTIONACTIVE                 0x000F /**< \brief Fault reaction active*/
#define STATUSWORD_STATE_FAULT                               0x0008 /**< \brief Fault state*/


/*---------------------------------------------
-    CiA402 State machine
-----------------------------------------------*/
#define STATE_NOT_READY_TO_SWITCH_ON        0x0001 /**< \brief Not ready to switch on (optional)*/
#define STATE_SWITCH_ON_DISABLED            0x0002 /**< \brief Switch on but disabled (optional)*/
#define STATE_READY_TO_SWITCH_ON            0x0004 /**< \brief Ready to switch on (mandatory)*/
#define STATE_SWITCHED_ON                   0x0008 /**< \brief Switch on (mandatory)*/
#define STATE_OPERATION_ENABLED             0x0010 /**< \brief Operation enabled (mandatory)*/
#define STATE_QUICK_STOP_ACTIVE             0x0020 /**< \brief Quick stop active (optional)*/
#define STATE_FAULT_REACTION_ACTIVE         0x0040 /**< \brief Fault reaction active (mandatory)*/
#define STATE_FAULT                         0x0080 /**< \brief Fault state (mandatory)*/


/*---------------------------------------------
-    CiA402 Modes of Operation (object 0x6060) (IEC61800_184e)
-----------------------------------------------*/
// -128 to -1 Manufacturer-specific operation modes
#define NO_MODE                     0 /**< \brief No mode*/
#define PROFILE_POSITION_MODE       1 /**< \brief Position Profile mode*/
#define VELOCITY_MODE               2 /**< \brief Velocity mode*/
#define PROFILE_VELOCITY_MOCE       3 /**< \brief Velocity Profile mode*/
#define PROFILE_TORQUE_MODE         4 /**< \brief Torque Profile mode*/
//5 reserved                          
#define HOMING_MODE                 6 /**< \brief Homing mode*/
#define INTERPOLATION_POSITION_MODE 7 /**< \brief Interpolation Position mode*/
#define CYCLIC_SYNC_POSITION_MODE   8 /**< \brief Cyclic Synchronous Position mode*/
#define CYCLIC_SYNC_VELOCITY_MODE   9 /**< \brief Cyclic Synchronous Velocity mode*/
#define CYCLIC_SYNC_TORQUE_MODE     10/**< \brief Cyclic Synchronous Torque mode*/
//+11 to +127 reserved


/***************************************
 CiA402 Error Codes (object 0x603F) (IEC61800_184e)
 ***************************************/
#define ERROR_SHORT_CIRCUIT_EARTH_LEAKAGE_INPUT             0x2110 /**< \brief Short circuit/earth leakage (input)*/
#define ERROR_EARTH_LEAKAGE_INPUT                           0x2120 /**< \brief Earth leakage (input)*/
#define ERROR_EARTH_LEAKAGE_PHASE_L1                        0x2121 /**< \brief Earth leakage phase L1*/
#define ERROR_EARTH_LEAKAGE_PHASE_L2                        0x2122 /**< \brief Earth leakage phase L2*/
#define ERROR_EARTH_LEAKAGE_PHASE_L3                        0x2123 /**< \brief Earth leakage phase L3*/
#define ERROR_SHORT_CIRCUIT_INPUT                           0x2130 /**< \brief Short circuit (input)*/
#define ERROR_SHORT_CIRCUIT_PHASES_L1_L2                    0x2131 /**< \brief Short circuit phases L1-L2*/
#define ERROR_SHORT_CIRCUIT_PHASES_L2_L3                    0x2132 /**< \brief Short circuit phases L2-L3*/
#define ERROR_SHORT_CIRCUIT_PHASES_L3_L1                    0x2133 /**< \brief Short circuit phases L3-L1*/
#define ERROR_INTERNAL_CURRENT_NO1                          0x2211 /**< \brief Internal current no 1*/
#define ERROR_INTERNAL_CURRENT_NO2                          0x2212 /**< \brief Internal current no 2*/
#define ERROR_OVER_CURRENT_IN_RAMP_FUNCTION                 0x2213 /**< \brief Over-current in ramp function*/
#define ERROR_OVER_CURRENT_IN_THE_SEQUENCE                  0x2214 /**< \brief Over-current in the sequence*/
#define ERROR_CONTINUOUS_OVER_CURRENT_DEVICE_INTERNAL       0x2220 /**< \brief Continuous over current (device internal)*/
#define ERROR_CONTINUOUS_OVER_CURRENT_DEVICE_INTERNAL_NO1   0x2221 /**< \brief Continuous over current no 1*/
#define ERROR_CONTINUOUS_OVER_CURRENT_DEVICE_INTERNAL_NO2   0x2222 /**< \brief Continuous over current no 2*/
#define ERROR_SHORT_CIRCUIT_EARTH_LEAKAGE_DEVICE_INTERNAL   0x2230 /**< \brief Short circuit/earth leakage (device internal)*/
#define ERROR_EARTH_LEAKAGE_DEVICE_INTERNAL                 0x2240 /**< \brief Earth leakage (device internal)*/
#define ERROR_SHORT_CIRCUIT_DEVICE_INTERNAL                 0x2250 /**< \brief Short circuit (device internal)*/
#define ERROR_CONTINUOUS_OVER_CURRENT                       0x2310 /**< \brief Continuous over current*/
#define ERROR_CONTINUOUS_OVER_CURRENT_NO1                   0x2311 /**< \brief Continuous over current no 1*/
#define ERROR_CONTINUOUS_OVER_CURRENT_NO2                   0x2312 /**< \brief Continuous over current no 2*/
#define ERROR_SHORT_CIRCUIT_EARTH_LEAKAGE_MOTOR_SIDE        0x2320 /**< \brief Short circuit/earth leakage (motor-side)*/
#define ERROR_EARTH_LEAKAGE_MOTOR_SIDE                      0x2330 /**< \brief Earth leakage (motor-side)*/
#define ERROR_EARTH_LEAKAGE_PHASE_U                         0x2331 /**< \brief Earth leakage phase U*/
#define ERROR_EARTH_LEAKAGE_PHASE_V                         0x2332 /**< \brief Earth leakage phase V*/
#define ERROR_EARTH_LEAKAGE_PHASE_W                         0x2333 /**< \brief Earth leakage phase W*/
#define ERROR_SHORT_CIRCUIT_MOTOR_SIDE                      0x2340 /**< \brief Short circuit (motor-side)*/
#define ERROR_SHORT_CIRCUIT_PHASES_U_V                      0x2341 /**< \brief Short circuit phases U-V*/
#define ERROR_EARTH_LEAKAGE_PHASE_V_W                       0x2342 /**< \brief Earth leakage phase V-W*/
#define ERROR_EARTH_LEAKAGE_PHASE_W_U                       0x2343 /**< \brief Earth leakage phase W-U*/
#define ERROR_LOAD_LEVEL_FAULT_I2T_THERMAL_STATE            0x2350 /**< \brief Load level fault (I2t, thermal state)*/
#define ERROR_LOAD_LEVEL_WARNING_I2T_THERMAL_STATE          0x2351 /**< \brief Load level warning (I2t, thermal state)*/
#define ERROR_MAINS_OVER_VOLTAGE                            0x3110 /**< \brief Mains over-voltage*/
#define ERROR_MAINS_OVER_VOLTAGE_PHASE_L1                   0x3111 /**< \brief Mains over-voltage phase L1*/
#define ERROR_MAINS_OVER_VOLTAGE_PHASE_L2                   0x3112 /**< \brief Mains over-voltage phase L2 */
#define ERROR_MAINS_OVER_VOLTAGE_PHASE_L3                   0x3113 /**< \brief Mains over-voltage phase L3*/
#define ERROR_MAINS_UNDER_VOLTAGE                           0x3120 /**< \brief Mains under-voltage*/
#define ERROR_MAINS_UNDER_VOLTAGE_PHASE_L1                  0x3121 /**< \brief Mains under-voltage phase L1*/
#define ERROR_MAINS_UNDER_VOLTAGE_PHASE_L2                  0x3122 /**< \brief Mains under-voltage phase L2*/
#define ERROR_MAINS_UNDER_VOLTAGE_PHASE_L3                  0x3123 /**< \brief Mains under-voltage phase L3*/
#define ERROR_PHASE_FAILURE                                 0x3130 /**< \brief Phase failure*/
#define ERROR_PHASE_FAILURE_L1                              0x3131 /**< \brief Phase failure L1*/
#define ERROR_PHASE_FAILURE_L2                              0x3132 /**< \brief Phase failure L2*/
#define ERROR_PHASE_FAILURE_L3                              0x3133 /**< \brief Phase failure L3*/
#define ERROR_PHASE_SEQUENCE                                0x3134 /**< \brief Phase sequence*/
#define ERROR_MAINS_FREQUENCY                               0x3140 /**< \brief Mains frequency*/
#define ERROR_MAINS_FREQUENCY_TOO_GREAT                     0x3141 /**< \brief Mains frequency too great*/
#define ERROR_MAINS_FREQUENCY_TOO_SMALL                     0x3142 /**< \brief Mains frequency too small*/
#define ERROR_DC_LINK_OVER_VOLTAGE                          0x3210 /**< \brief DC link over-voltage*/
#define ERROR_OVER_VOLTAGE_NO_1                             0x3211 /**< \brief Over-voltage no  1*/
#define ERROR_OVER_VOLTAGE_NO_2                             0x3212 /**< \brief Over voltage no  2 */
#define ERROR_DC_LINK_UNDER_VOLTAGE                         0x3220 /**< \brief DC link under-voltage*/
#define ERROR_UNDER_VOLTAGE_NO_1                            0x3221 /**< \brief Under-voltage no  1*/
#define ERROR_UNDER_VOLTAGE_NO_2                            0x3222 /**< \brief Under-voltage no  2*/
#define ERROR_LOAD_ERROR                                    0x3230 /**< \brief Load error*/
#define ERROR_OUTPUT_OVER_VOLTAGE                           0x3310 /**< \brief Output over-voltage*/
#define ERROR_OUTPUT_OVER_VOLTAGE_PHASE_U                   0x3311 /**< \brief Output over-voltage phase U*/
#define ERROR_OUTPUT_OVER_VOLTAGE_PHASE_V                   0x3312 /**< \brief Output over-voltage phase V*/
#define ERROR_OUTPUT_OVER_VOLTAGE_PHASE_W                   0x3313 /**< \brief Output over-voltage phase W*/
#define ERROR_ARMATURE_CIRCUIT                              0x3320 /**< \brief Armature circuit*/
#define ERROR_ARMATURE_CIRCUIT_INTERRUPTED                  0x3321 /**< \brief Armature circuit interrupted*/
#define ERROR_FIELD_CIRCUIT                                 0x3330 /**< \brief Field circuit error */
#define ERROR_FIELD_CIRCUIT_INTERRUPTED                     0x3331 /**< \brief Field circuit interrupted*/
#define ERROR_EXCESS_AMBIENT_TEMPERATURE                    0x4110 /**< \brief Excess ambient temperature*/
#define ERROR_TOO_LOW_AMBIENT_TEMPERATURE                   0x4120 /**< \brief Too low ambient temperature*/
#define ERROR_TEMPERATURE_SUPPLY_AIR                        0x4130 /**< \brief Temperature supply air*/
#define ERROR_TEMPERATURE_AIR_OUTLET                        0x4140 /**< \brief Temperature air outlet*/
#define ERROR_EXCESS_TEMPERATURE_DEVICE                     0x4210 /**< \brief Excess temperature device*/
#define ERROR_TOO_LOW_TEMPERATURE_DEVICE                    0x4220 /**< \brief Too low temperature device*/
#define ERROR_TEMPERATURE_DRIVE                             0x4300 /**< \brief Temperature drive error*/
#define ERROR_EXCESS_TEMPERATURE_DRIVE                      0x4310 /**< \brief Excess temperature drive error*/
#define ERROR_TOO_LOW_TEMPERATURE_DRIVE                     0x4320 /**< \brief Too low temperature drive error*/
#define ERROR_TEMPERATURE_SUPPLY                            0x4400 /**< \brief Temperature supply error*/
#define ERROR_EXCESS_TEMPERATURE_SUPPLY                     0x4410 /**< \brief Excess temperature supply*/
#define ERROR_TOO_LOW_TEMPERATURE_SUPPLY                    0x4420 /**< \brief Too low temperature supply*/
#define ERROR_SUPPLY_ERROR                                  0x5100 /**< \brief Supply error*/
#define ERROR_SUPPLY_LOW_VOLTAGE                            0x5110 /**< \brief Supply low voltage*/
#define ERROR_U1_SUPPLY_15V                                 0x5111 /**< \brief U1 = supply +15V/-15V*/
#define ERROR_U2_SUPPLY_24_V                                0x5112 /**< \brief U2 = supply +24 V*/
#define ERROR_U3_SUPPLY_5_V                                 0x5113 /**< \brief U3 = supply +5 V*/
#define ERROR_U4_MANUFACTURER_SPECIFIC                      0x5114 /**< \brief U4 = manufacturer-specific error*/
#define ERROR_U5_MANUFACTURER_SPECIFIC                      0x5115 /**< \brief U5 = manufacturer-specific error*/
#define ERROR_U6_MANUFACTURER_SPECIFIC                      0x5116 /**< \brief U6 = manufacturer-specific error*/
#define ERROR_U7_MANUFACTURER_SPECIFIC                      0x5117 /**< \brief U7 = manufacturer-specific error*/
#define ERROR_U8_MANUFACTURER_SPECIFIC                      0x5118 /**< \brief U8 = manufacturer-specific error*/
#define ERROR_U9_MANUFACTURER_SPECIFIC                      0x5119 /**< \brief U9 = manufacturer-specific error*/
#define ERROR_SUPPLY_INTERMEDIATE_CIRCUIT                   0x5120 /**< \brief Supply intermediate circuit*/
//#define ERROR_CONTROL                                     0x5200
#define ERROR_CONTROL_MEASUREMENT_CIRCUIT                   0x5210 /**< \brief Measurement circuit*/
#define ERROR_CONTROL_COMPUTING_CIRCUIT                     0x5220 /**< \brief Computing circuit*/
#define ERROR_OPERATING_UNIT                                0x5300 /**< \brief Operating unit error*/
#define ERROR_POWER_SECTION                                 0x5400 /**< \brief Power section error*/
#define ERROR_OUTPUT_STAGES                                 0x5410 /**< \brief Output stages error*/
#define ERROR_CHOPPER                                       0x5420 /**< \brief Chopper error*/
#define ERROR_INPUT_STAGES                                  0x5430 /**< \brief Input stages error*/
#define ERROR_CONTACTS_ERROR                                0x5440 /**< \brief Contacts error*/
#define ERROR_CONTACT_1_MANUFACTURER_SPECIFIC               0x5441 /**< \brief Contact 1 = manufacturer-specific error*/
#define ERROR_CONTACT_2_MANUFACTURER_SPECIFIC               0x5442 /**< \brief Contact 2 = manufacturer-specific error*/
#define ERROR_CONTACT_3_MANUFACTURER_SPECIFIC               0x5443 /**< \brief Contact 3 = manufacturer-specific error*/
#define ERROR_CONTACT_4_MANUFACTURER_SPECIFIC               0x5444 /**< \brief Contact 4 = manufacturer-specific error*/
#define ERROR_CONTACT_5_MANUFACTURER_SPECIFIC               0x5445 /**< \brief Contact 5 = manufacturer-specific error*/
#define ERROR_FUSES_ERROR                                   0x5450 /**< \brief Fuses error*/
#define ERROR_S1_L1                                         0x5451 /**< \brief S1 = l1 error*/
#define ERROR_S2_L2                                         0x5452 /**< \brief S2 = l2 error*/
#define ERROR_S3_L3                                         0x5453 /**< \brief S3 = l3 error*/
#define ERROR_S4_MANUFACTURER_SPECIFIC                      0x5454 /**< \brief S4 = manufacturer-specific error*/
#define ERROR_S5_MANUFACTURER_SPECIFIC                      0x5455 /**< \brief S5 = manufacturer-specific error*/
#define ERROR_S6_MANUFACTURER_SPECIFIC                      0x5456 /**< \brief S6 = manufacturer-specific error*/
#define ERROR_S7_MANUFACTURER_SPECIFIC                      0x5457 /**< \brief S7 = manufacturer-specific error*/
#define ERROR_S8_MANUFACTURER_SPECIFIC                      0x5458 /**< \brief S8 = manufacturer-specific error*/
#define ERROR_S9_MANUFACTURER_SPECIFIC                      0x5459 /**< \brief S9 = manufacturer-specific error*/
#define ERROR_HARDWARE_MEMORY                               0x5500 /**< \brief Hardware memory error*/
#define ERROR_RAM                                           0x5510 /**< \brief RAM error*/
#define ERROR_ROM_EPROM                                     0x5520 /**< \brief ROM/EPROM error*/
#define ERROR_EEPROM                                        0x5530 /**< \brief EEPROM error*/
#define ERROR_SOFTWARE_RESET_WATCHDOG                       0x6010 /**< \brief Software reset (watchdog)*/
//0x6301_TO_0x630F        ERROR_DATA_RECORD_NO_1_TO_NO_15          
#define ERROR_LOSS_OF_PARAMETERS                            0x6310 /**< \brief Loss of parameters*/
#define ERROR_PARAMETER_ERROR                               0x6320 /**< \brief Parameter error*/
#define ERROR_POWER_ERROR                                   0x7100 /**< \brief Power error*/
#define ERROR_BRAKE_CHOPPER                                 0x7110 /**< \brief Brake chopper*/
#define ERROR_FAILURE_BRAKE_CHOPPER                         0x7111 /**< \brief Failure brake chopper*/
#define ERROR_OVER_CURRENT_BRAKE_CHOPPER                    0x7112 /**< \brief Over current brake chopper*/
#define ERROR_PROTECTIVE_CIRCUIT_BRAKE_CHOPPER              0x7113 /**< \brief Protective circuit brake chopper error*/
#define ERROR_MOTOR_ERROR                                   0x7120 /**< \brief Motor error*/
#define ERROR_MOTOR_BLOCKED                                 0x7121 /**< \brief Motor blocked error*/
#define ERROR_MOTOR_ERROR_OR_COMMUTATION_MALFUNC            0x7122 /**< \brief Motor error or commutation malfunc */
#define ERROR_MOTOR_TILTED                                  0x7123 /**< \brief Motor tilted*/
#define ERROR_MEASUREMENT_CIRCUIT                           0x7200 /**< \brief Measurement circuit*/
#define ERROR_SENSOR_ERROR                                  0x7300 /**< \brief Sensor error*/
#define ERROR_TACHO_FAULT                                   0x7301 /**< \brief Tacho fault*/
#define ERROR_TACHO_WRONG_POLARITY                          0x7302 /**< \brief Tacho wrong polarity*/
#define ERROR_RESOLVER_1_FAULT                              0x7303 /**< \brief Resolver 1 fault*/
#define ERROR_RESOLVER_2_FAULT                              0x7304 /**< \brief Resolver 2 fault*/
#define ERROR_INCREMENTAL_SENSOR_1_FAULT                    0x7305 /**< \brief Incremental sensor 1 fault*/
#define ERROR_INCREMENTAL_SENSOR_2_FAULT                    0x7306 /**< \brief Incremental sensor 2 fault*/
#define ERROR_INCREMENTAL_SENSOR_3_FAULT                    0x7307 /**< \brief Incremental sensor 3 fault*/
#define ERROR_SPEED                                         0x7310 /**< \brief Speed error*/
#define ERROR_POSITION                                      0x7320 /**< \brief Position error*/
#define ERROR_COMPUTATION_CIRCUIT                           0x7400 /**< \brief Computation circuit*/
#define ERROR_COMMUNICATION                                 0x7500 /**< \brief Communication error*/
#define ERROR_SERIAL_INTERFACE_NO_1                         0x7510 /**< \brief Serial interface no  1 error*/
#define ERROR_SERIAL_INTERFACE_NO_2                         0x7520 /**< \brief Serial interface no  2 error*/
#define ERROR_DATA_STORAGE_EXTERNAL                         0x7600 /**< \brief Data storage (external) error*/
#define ERROR_TORQUE_CONTROL                                0x8300 /**< \brief Torque control error*/
#define ERROR_EXCESS_TORQUE                                 0x8311 /**< \brief Excess torque error*/
#define ERROR_DIFFICULT_START_UP                            0x8312 /**< \brief Difficult start up error*/
#define ERROR_STANDSTILL_TORQUE                             0x8313 /**< \brief Standstill torque error*/
#define ERROR_INSUFFICIENT_TORQUE                           0x8321 /**< \brief Insufficient torque error*/
#define ERROR_TORQUE_FAULT                                  0x8331 /**< \brief Torque fault*/
#define ERROR_VELOCITY_SPEED_CONTROLLER                     0x8400 /**< \brief Velocity speed controller*/
#define ERROR_POSITION_CONTROLLER                           0x8500 /**< \brief Position controller*/
#define ERROR_POSITIONING_CONTROLLER                        0x8600 /**< \brief Positioning controller*/
#define ERROR_FOLLOWING_ERROR                               0x8611 /**< \brief Following error*/
#define ERROR_REFERENCE_LIMIT                               0x8612 /**< \brief Reference limit*/
#define ERROR_SYNC_CONTROLLER                               0x8700 /**< \brief Sync controller*/
#define ERROR_WINDING_CONTROLLER                            0x8800 /**< \brief Winding controller*/
#define ERROR_PROCESS_DATA_MONITORING                       0x8900 /**< \brief Process data monitoring*/
//#define ERROR_CONTROL                                     0x8A00
#define ERROR_DECELERATION                                  0xF001 /**< \brief Deceleration error*/
#define ERROR_SUB_SYNCHRONOUS_RUN                           0xF002 /**< \brief Sub-synchronous run error*/
#define ERROR_STROKE_OPERATION                              0xF003 /**< \brief Stroke operation error*/
//#define ERROR_CONTROL                                     0xF004
//0xFF00_TO_0xFFFF        MANUFACTURER_SPECIFIC                   


/*---------------------------------------------
-    CiA402 generic error option code values
        Note: Not all values are valid for each error option code.
        A detailed description of the option code values are listed in the specification IEC 61800-7-200
        0x605B    : action in state transition 8
        0x605C    : action in state transition 5
-----------------------------------------------*/
#define DISABLE_DRIVE                    0 /**< \brief Disable drive (options: 0x605B; 0x605C; 0x605E)*/
#define SLOW_DOWN_RAMP                   1 /**< \brief Slow down ramp (options: 0x605B; 0x605C; 0x605E)*/
#define QUICKSTOP_RAMP                   2 /**< \brief Quick stop ramp (options: 0x605E)*/
#define STOP_ON_CURRENT_LIMIT            3 /**< \brief Stop on current limit (options: 0x605E)*/
#define STOP_ON_VOLTAGE_LIMIT            4 /**< \brief Stop on voltage limit (options: 0x605E)*/


/*---------------------------------------------
-    Specific values for Quick stop option code (object 0x605A) (IEC61800_184e)
        indicated the quick stop function
-----------------------------------------------*/
//-32768 to -1        MANUFACTURER_SPECIFIC
#define SLOWDOWN_RAMP_NO_TRANSIT                5 /**< \brief Slow down on slow down ramp and stay in Quick Stop Active*/
#define QUICKSTOP_RAMP_NO_TRANSIT               6 /**< \brief Slow down on quick stop ramp and stay in Quick Stop Active*/
#define CURRENT_LIMIT_NO_TRANSIT                7 /**< \brief Slow down on current limit and stay in Quick Stop Active*/
#define VOLTAGE_LIMIT_NO_TRANSIT                8 /**< \brief Slow down on voltage limit and stay in Quick Stop Active*/
//9 to 32767        RESERVED


#define MAX_AXES    2 /**< \brief Number of supported axes*/



/*---------------------------------------------
-    Module Identifications (each supported operation mode has a module)
-----------------------------------------------*/
#define CSV_CSP_MODULE_ID       0x00000100 /**< \brief Module Id for cyclic synchronous position/velocity mode (dynamic switching supported)*/
#define CSP_MODULE_ID           0x00000200 /**< \brief Module Id for cyclic synchronous position mode*/
#define CSV_MODULE_ID           0x00000300 /**< \brief Module Id for cyclic synchronous velocity mode*/


/**
 * \addtogroup PdoMappingObjects PDO Mapping Objects
 * csp/csv mode RxPDO mapping : 0x1600<br>
 * csp     mode RxPDO mapping : 0x1601<br>
 * csv     mode RxPDO mapping : 0x1602<br>
 * csp/csv mode TxPDO mapping : 0x1A00<br>
 * csp     mode TxPDO mapping : 0x1A01<br>
 * csv     mode TxPDO mapping : 0x1A02
 * @{
 */
/** \brief 0x1600 (csp/csv RxPDO) data structure*/



/** \brief 0x1601 (csp RxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[3]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1601;


/** \brief 0x1602 (csv RxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[3]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1602;

typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0;
   UINT32   aEntries[3];
} OBJ_STRUCT_PACKED_END
TOBJ1A01;


typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0;
   UINT32   aEntries[3];
} OBJ_STRUCT_PACKED_END
TOBJ1A02;



/**
 * \addtogroup SmAssignObjects SyncManager Assignment Objects
 * SyncManager 2 : 0x1C12<br>
 * SyncManager 3 : 0x1C13
 * @{
 */
/** \brief 0x1C12 (SyncManager 2 assignment) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT16   aEntries[2]; /**< \brief Entry buffer (number of entries depends on the supported axis, each axis requires one entry)*/
} OBJ_STRUCT_PACKED_END
TOBJ1C12;


/** \brief 0x1C13 (SyncManager 3 assignment) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT16   aEntries[2]; /**< \brief Entry buffer (number of entries depends on the supported axis, each axis requires one entry)*/
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
/** @}*/


/**
 * \addtogroup CiA402Objects CiA402 Axis Objects
 * @{
 */
/** \brief 0x607D (Software Position Limit) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   INT32    aEntries[2];
} OBJ_STRUCT_PACKED_END
TOBJ607D;


/** \brief Object 0x60C2 (Interpolation Time Period) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT8    u8InterpolationPeriod; /**< \brief Interpolation period*/
   INT8     i8InterpolationIndex; /**< \brief Interpolation index*/
} OBJ_STRUCT_PACKED_END
TOBJ60C2;
/** @}*/


/**
 * \addtogroup DeviceParaObjects Device Parameter Objects
 * Modular Device Profile : 0xF000<br>
 * Module Profile List : 0xF010<br>
 * Configured Modules Ident List : 0xF030<br>
 * Detected Modules Ident List : 0xF050<br>
 * @{
 */
/** \brief 0xF000 (Modular Device Profile) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT16   u16Moduleindexdistance; /**< \brief Module Index distance
                                     * 
                                     * Index distance between two modules.<br>
                                     * According to ETG.6010 the object index distance is 0x800*/
   UINT16   u16Maximumnumberofmodules; /**< \brief Maximum number of modules*/
} OBJ_STRUCT_PACKED_END
TOBJF000;


/** \brief 0xF010 (Module Profile List) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT32   aEntries[MAX_AXES];/**< \brief Module profile information buffer
                                  * 
                                  * Bit 00..15: Profile number of the module on position 1<br>
                                  * Bit 16..31: Profile specific<br>
                                  * The number of entries depends on the number of supported axes.
                                  */
} OBJ_STRUCT_PACKED_END
TOBJF010;


/** \brief 0xF030 (Configured Modules Ident List) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT32   aEntries[MAX_AXES];/**< \brief Module Ident List buffer
                                  * The number of entries depends on the number of supported axes.
                                  */
} OBJ_STRUCT_PACKED_END
TOBJF030;


/** \brief 0xF050 (Detected Modules Ident List) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT32   aEntries[MAX_AXES];/**< \brief Module Ident List buffer
                                  * The number of entries depends on the number of supported axes.
                                  */
} OBJ_STRUCT_PACKED_END
TOBJF050;
/** @}*/


/*---------------------------------------------
-    Generic Axis structure
-----------------------------------------------*/
/**
 * \addtogroup PDO Process Data Objects
 * @{
 */
/** \brief Data structure to handle the process data transmitted via 0x1A00 (csp/csv TxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjStatusWord; /**< \brief Status word (0x6041)*/
    INT32 ObjPositionActualValue; /**< \brief Actual position (0x6064)*/
    INT32 ObjVelocityActualValue; /**< \brief Actual velocity (0x606C)*/
    INT16 ObjModesOfOperationDisplay; /**< \brief Current mode of operation (0x6061)*/
}STRUCT_PACKED_END
TCiA402PDO1A00;


/** \brief Data structure to handle the process data transmitted via 0x1A01 (csp TxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjStatusWord; /**< \brief Status word (0x6041)*/
    INT32 ObjPositionActualValue; /**< \brief Actual position (0x6064)*/
/*ECATCHANGE_START(V5.12) CiA402 3*/
    UINT16 Padding16Bit; /**< \brief 16bit padding*/
/*ECATCHANGE_END(V5.12) CiA402 3*/
}STRUCT_PACKED_END
TCiA402PDO1A01;


/** \brief Data structure to handle the process data transmitted via 0x1A02 (csv TxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjStatusWord; /**< \brief Status word (0x6041)*/
    INT32 ObjPositionActualValue; /**< \brief Actual position (0x6064)*/
/*ECATCHANGE_START(V5.12) CiA402 3*/
    UINT16 Padding16Bit; /**< \brief 16bit padding*/
/*ECATCHANGE_END(V5.12) CiA402 3*/
}STRUCT_PACKED_END
TCiA402PDO1A02;


/** \brief Data structure to handle the process data transmitted via 0x1600 (csp/csv RxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjControlWord; /**< \brief Control word (0x6040)*/
    INT32 ObjTargetPosition; /**< \brief Target position (0x607A)*/
    INT32 ObjTargetVelocity; /**< \brief Target velocity (0x60FF)*/
    INT16 ObjModesOfOperation; /**< \brief Mode of operation (0x6060)*/
}STRUCT_PACKED_END
TCiA402PDO1600;


/** \brief Data structure to handle the process data transmitted via 0x1601 (csp RxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjControlWord; /**< \brief Control word (0x6040)*/
    INT32 ObjTargetPosition; /**< \brief Target position (0x607A)*/
/*ECATCHANGE_START(V5.12) CiA402 3*/
    UINT16 Padding16Bit; /**< \brief 16bit padding*/
/*ECATCHANGE_END(V5.12) CiA402 3*/
}STRUCT_PACKED_END
TCiA402PDO1601;


/** \brief Data structure to handle the process data transmitted via 0x1602 (csv RxPDO)*/
typedef struct STRUCT_PACKED_START
{
    UINT16 ObjControlWord; /**< \brief Control word (0x6040)*/
    INT32 ObjTargetVelocity; /**< \brief Target velocity (0x60FF)*/
/*ECATCHANGE_START(V5.12) CiA402 3*/
    UINT16 Padding16Bit; /**< \brief 16bit padding*/
/*ECATCHANGE_END(V5.12) CiA402 3*/
}STRUCT_PACKED_END
TCiA402PDO1602;
/** @}*/





#endif //_CIA402_H_

#ifdef _CiA402_
    #define PROTO
#else
    #define PROTO extern
#endif


/*---------------------------------------------
-    Entry Descriptions and object names
-----------------------------------------------*/
#ifdef _CiA402_
/**
 * \addtogroup SmAssignObjects SyncManager Assignment Objects
 * @{
 */

/**
 * \brief Entry descriptions of SyncManager assign objects
 *
 * SubIndex0<br>
 * SubIndex1 (for all other entries the same description will be used (because the object code is ARRAY))
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asPDOAssignEntryDesc[] = {
   {DEFTYPE_UNSIGNED8, 0x08, (ACCESS_READ|ACCESS_WRITE_PREOP)},
   {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READ|ACCESS_WRITE_PREOP)}};

   
/**
 * \brief Object 0x1C12 (Sync Manager 2 assign) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */   
OBJCONST UCHAR OBJMEM aName0x1C12[] = "RxPDO assign";

/**
 * \brief Object 0x1C13 (Sync Manager 3 assign) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1C13[] = "TxPDO assign";
/** @}*/

/**
 * \addtogroup CiA402Objects CiA402 Axis Objects
 * @{
 */

/** 
 * \brief Object 0x607D (Software Position Limit) entry description
 * 
 * Subindex 0<br>
 * Subindex 1 : Min Position range limit<br>
 * Subindex 2 : Max Position range limit
 */

/** @}*/
#endif




//*************************************************************************************************
//
//                                          Object 0x1C12
//
//*************************************************************************************************
// 0x1C12 (SyncManager 2 assignment) variable to handle object data
// SubIndex 0 : 1
// SubIndex 1 : 0x1600
// SubIndex 2 : 0x1610
PROTO TOBJ1C12 sRxPDOassign
#ifdef _CiA402_
= {2,{0x1600,0x1610}}
#endif
;

//*************************************************************************************************
//
//                                          Object 0x1C13
//
//*************************************************************************************************
//0x1C13 (SyncManager 3 assignment) variable to handle object data
// SubIndex 0 : 1
// SubIndex 1 : 0x1A00
// SubIndex 2 : 0x1A10
PROTO TOBJ1C13 sTxPDOassign
#ifdef _CiA402_
= {2,{0x1A00,0x1A10}}
#endif
;

//*************************************************************************************************
//
//                                          Object 0xF000
//
//*************************************************************************************************
//Object 0xF000 (Modular Device Profile) variable to handle object data
// SubIndex 0 : 2
// SubIndex 1 : 0x800 (index distance)<br>
// SubIndex 2 : MAX_AXES (number of modules depends on the number of axes)
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[3] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ},
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ}};
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000Index distance\000Maximum number of modules\000\377";
#endif

PROTO TOBJF000 sModulardeviceprofile
#ifdef _CiA402_
= {2, 0x800, MAX_AXES}
#endif
;

//*************************************************************************************************
//
//                                          Object 0xF010
//
//*************************************************************************************************
// Object 0xF010 (Module profile list) variable to handle object data
// SubIndex 0 : 1
// SubIndex 1 : 2 (Low Word)
// SubIndex 2 : 0
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF010[3] = {
   {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}};
OBJCONST UCHAR OBJMEM aName0xF010[] = "Module Profile List";
#endif

PROTO TOBJF010 sModuleProfileInfo
#ifdef _CiA402_
= {1,{2,0}}
#endif
;

//*************************************************************************************************
//
//                                          Object 0xF030
//
//*************************************************************************************************
// Object 0xF030 (Configured Module List) variable to handle object data
// SubIndex 0 : 1
// SubIndex 1 : csv Module is set by default
// SubIndex 2 : 0
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF030[3] = {
   {DEFTYPE_UNSIGNED8, 0x08, (ACCESS_READ|ACCESS_WRITE_PREOP)},
   {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READ|ACCESS_WRITE_PREOP)},
   {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READ|ACCESS_WRITE_PREOP)}};
OBJCONST UCHAR OBJMEM aName0xF030[] = "Configured module Ident list";
#endif

PROTO TOBJF030 sConfiguredModuleIdentList
#ifdef _CiA402_
= {2,{0x00000100,0x00000100}}
#endif
;
PROTO UINT8 Write0xF030( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess );


//*************************************************************************************************
//
//                                          Object 0xF050
//
//*************************************************************************************************
// Subindex 0
// SubIndex x
// (x > 0)
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF050[] = {
   {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}};
OBJCONST UCHAR OBJMEM aName0xF050[] = "Module detected list";
#endif

PROTO TOBJF050 sDetectedModuleIdentList
#ifdef _CiA402_
= {2,{0x00000100,0x00000100}}
#endif
;

//*************************************************************************************************
//
//                                          Object 0x1600
//
//*************************************************************************************************
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /* SubIndex 0   */
   UINT32   aEntries[10];  /* Entry buffer */
} OBJ_STRUCT_PACKED_END
TOBJ16xx;
PROTO TOBJ16xx sRPDO1Map
#ifdef _CiA402_
= {10, {0x60400010, 0x607A0020, 0x60FF0020, 0x60710010,0x60600008,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000}};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x16xx[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READWRITE },      /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 001 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 002 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 003 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 004 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 005 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 006 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 007 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 008 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},     /* SubIndex 009 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE}};    /* SubIndex 00A */
OBJCONST UCHAR OBJMEM aName0x16xx[] = "csp/csv RxPDO\000\377";
#endif


//*************************************************************************************************
//
//                                          Object 0x1610
//
//*************************************************************************************************
PROTO TOBJ16xx sRPDO2Map
#ifdef _CiA402_
= {10, {0x60400010,0x607A0020,0x00000010,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000}}
#endif
;


//*************************************************************************************************
//
//                                          Object 0x1A00
//
//*************************************************************************************************
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0;   /* SubIndex 0   */
   UINT32   aEntries[10];    /* Entry buffer */
} OBJ_STRUCT_PACKED_END
TOBJ1Axx;
PROTO TOBJ1Axx sTPDO1Map
#ifdef _CiA402_
= {10, {0x60410010,0x60640020,0x606C0020,0x60610008,0x00000008,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000}};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1Axx[] = {
   {DEFTYPE_UNSIGNED8,  0x8,  ACCESS_READWRITE }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 001 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 002 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 003 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 004 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 005 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 006 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 007 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 008 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},  /* SubIndex 009 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE}}; /* SubIndex 00A */
OBJCONST UCHAR OBJMEM aName0x1Axx[] = "csp/csv TxPDO\000\377";

/*--------------------------------------------------------------------------------------------------*/
/*  Object entry descriptions               Pnxxx                                                   */
/*--------------------------------------------------------------------------------------------------*/
const TSDOINFOENTRYDESC   asDT20XXEntryDesc[] = {
    {DEFTYPE_UNSIGNED8,  0x08, ACCESS_READWRITE},   /* Index    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX00    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX01    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX02    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX03    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX04    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX05    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX06    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX07    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX08    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX09    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX0F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX10    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX11    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX12    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX13    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX14    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX15    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX16    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX17    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX18    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX19    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX1F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX20    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX21    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX22    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX23    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX24    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX25    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX26    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX27    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX28    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX29    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX2F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX30    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX31    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX32    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX33    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX34    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX35    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX36    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX37    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX38    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX39    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX3F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX40    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX41    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX42    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX43    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX44    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX45    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX46    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX47    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX48    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX49    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX4F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX50    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX51    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX52    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX53    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX54    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX55    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX56    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX57    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX58    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX59    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX5F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX60    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX61    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX62    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX63    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX64    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX65    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX66    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX67    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX68    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX69    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX6F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX70    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX71    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX72    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX73    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX74    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX75    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX76    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX77    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX78    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX79    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX7F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX80    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX81    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX82    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX83    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX84    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX85    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX86    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX87    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX88    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX89    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX8F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX90    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX91    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX92    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX93    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX94    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX95    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX96    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX97    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX98    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX99    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9A    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9B    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9C    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9D    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9E    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnX9F    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXA9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAD    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXAF    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXB9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBD    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXBF    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXC9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCD    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXCF    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXD9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDD    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXDF    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXE9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXEA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXEB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXEC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXED    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXEE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXEF    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF0    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF1    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF2    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF3    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF4    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF5    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF6    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF7    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF8    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXF9    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFA    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFB    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFC    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFD    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFE    */
    {DEFTYPE_UNSIGNED32, 0x10, ACCESS_READWRITE},   /* PnXFF    */
    };

/*--------------------------------------------------------------------------------------------------*/
/*  Object entry descriptions               UnXXX                                                   */
/*--------------------------------------------------------------------------------------------------*/
const TSDOINFOENTRYDESC   asDT2ExxEntryDesc[] = {
    {DEFTYPE_UNSIGNED8,  0x08, ACCESS_READWRITE},   /* Index    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX00    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX01    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX02    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX03    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX04    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX05    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX06    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX07    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX08    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX09    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX0F    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX10    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX11    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX12    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX13    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX14    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX15    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX16    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX17    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX18    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX19    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX1F    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX20    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX21    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX22    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX23    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX24    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX25    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX26    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX27    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX28    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX29    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX2F    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX30    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX31    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX32    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX33    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX34    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX35    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX36    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX37    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX38    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX39    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX3F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX40    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX41    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX42    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX43    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX44    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX45    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX46    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX47    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX48    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX49    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX4F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX50    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX51    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX52    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX53    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX54    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX55    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX56    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX57    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX58    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX59    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX5F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX60    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX61    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX62    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX63    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX64    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX65    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX66    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX67    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX68    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX69    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX6F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX70    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX71    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX72    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX73    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX74    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX75    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX76    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX77    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX78    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX79    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX7F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX80    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX81    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX82    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX83    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX84    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX85    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX86    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX87    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX88    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX89    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX8F    */
	{DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX90    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX91    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX92    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX93    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX94    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX95    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX96    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX97    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX98    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX99    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9A    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9B    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9C    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9D    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9E    */
    {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE},   /* UnX9F    */
    };

#endif
//*************************************************************************************************
//
//                                          Object 0x1A10
//
//*************************************************************************************************
PROTO TOBJ1Axx sTPDO2Map
#ifdef _CiA402_
= {10, {0x60410010,0x60640020,0x00000010,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000,0x0000000000}};
#endif
;

/****************************************************************************************************/
/*                                          Object 0x603F                                           */
/*                                          < Error Code >                                          */
/****************************************************************************************************/
PROTO UINT16 u16ErrCode
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC OBJMEM sEntryDesc0x603F = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ};
OBJCONST UCHAR OBJMEM aName0x603F[] = "Error Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x6040                                           */
/*                                         < Control Word >                                         */
/****************************************************************************************************/
PROTO UINT16 u16ControlWord
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6040 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};
OBJCONST UCHAR OBJMEM aName0x6040[] = "Control Word";
#endif


/****************************************************************************************************/
/*                                          Object 0x6041                                           */
/*                                          < StatusWord >                                          */
/****************************************************************************************************/
PROTO UINT16 u16StatusWord
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6041 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};
OBJCONST UCHAR OBJMEM aName0x6041[] = "Status Word";
#endif

/****************************************************************************************************/
/*                                          Object 0x605A                                           */
/*                                      < Quick Shutdown Option Code >                              */
/****************************************************************************************************/
PROTO INT16 s16QuickShutdownOpt
#ifdef _CiA402_
= 2;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605A = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR OBJMEM aName0x605A[] = "Quickstop Option Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x605B                                           */
/*                                      < Shutdown Option Code >                                    */
/****************************************************************************************************/
PROTO INT16 s16ShutdownOpt
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605B = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR OBJMEM aName0x605B[] = "Shutdown Option Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x605C                                           */
/*                              < Disable Operation Option Cod >                                    */
/****************************************************************************************************/
PROTO INT16 s16DisOperationOpt
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605C = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR OBJMEM aName0x605C[] = "Disable Operation Option Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x605D                                           */
/*                                          < Halt Option Code >                                    */
/****************************************************************************************************/
PROTO INT16 s16HaltOptioncode
#ifdef _CiA402_
= 1;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605D = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR OBJMEM aName0x605D[] = "Halt Option Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x605E                                           */
/*                                   < Fault Reaction Option Code >                                 */
/****************************************************************************************************/
PROTO INT16 s16FaultReactOpt
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605E = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR OBJMEM aName0x605E[] = "Fault Reaction Code";
#endif

/****************************************************************************************************/
/*                                          Object 0x6060                                           */
/*                                      < Modes of Operation >                                      */
/****************************************************************************************************/
PROTO CHAR s8ModeofOP
#ifdef _CiA402_
= 8;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6060 = {DEFTYPE_INTEGER8, 0x08, (ACCESS_READWRITE)};
OBJCONST UCHAR OBJMEM aName0x6060[] = "Modes of Operation";
#endif

/****************************************************************************************************/
/*                                          Object 0x6061                                           */
/*                                   < Modes of Operation Display >                                 */
/****************************************************************************************************/
PROTO CHAR s8ModeofOPDis
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6061 = {DEFTYPE_INTEGER8, 0x08, (ACCESS_READ)};
OBJCONST UCHAR OBJMEM aName0x6061[] = "Modes of Operation Display";
#endif

/****************************************************************************************************/
/*                                          Object 0x6062                                           */
/*                                      < Position Demand Value >                                   */
/****************************************************************************************************/
PROTO INT32 s32PosDemandValPUU
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6062[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6062[] = "Position Demand Value";
#endif

/****************************************************************************************************/
/*                                          Object 0x6063                                           */
/*                                  < Modes of Operation Display >                                  */
/****************************************************************************************************/
PROTO INT32 s32PosActValInc
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6063[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6063[] = "Modes of Operation Display";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6064                                           */
/*                                      < Position Actual Vale >                                    */
/****************************************************************************************************/
PROTO INT32 s32PosActVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6064 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR OBJMEM aName0x6064[] = "Position Actual Value";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6065                                           */
/*                                      < Following Error Windows >                                 */
/****************************************************************************************************/
PROTO UINT32 u32FollowErrWind
#ifdef _CiA402_
= 10000;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6065[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6065[] = "Following Error Windows";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6067                                           */
/*                                       < Position window >                                        */
/****************************************************************************************************/
PROTO UINT32 u32PosWindow
#ifdef _CiA402_
= 100;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6067[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6067[] = "Position window";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6068                                           */
/*                                      < Position window time >                                    */
/****************************************************************************************************/
PROTO UINT16 u16PosWindowTime
#ifdef _CiA402_
= 2;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6068[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6068[] = "Position window time";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x606B                                           */
/*                                      < Velocity Demand Value >                                   */
/****************************************************************************************************/
PROTO INT32 s32VelDemandVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x606B[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x606B[] = "Velocity Demand Value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x606C                                           */
/*                                      < Velocity Actual Value >                                   */
/****************************************************************************************************/
PROTO INT32 s32VelActualVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x606C[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x606C[] = "Velocity Actual Value";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x606D                                           */
/*                                      < Velocity window >                                         */
/****************************************************************************************************/
PROTO UINT16 u16VelWindow
#ifdef _CiA402_
= 10;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x606D[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x606D[] = "Velocity window";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x606E                                           */
/*                                      < Velocity window time >                                    */
/****************************************************************************************************/
PROTO UINT16 u16VelWindowTime
#ifdef _CiA402_
= 2;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x606E[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x606E[] = "Velocity window time";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x606F                                           */
/*                                       < Velocity threshold >                                     */
/****************************************************************************************************/
PROTO UINT16 u16Velthresd
#ifdef _CiA402_
= 10;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x606F[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x606F[] = "Velocity threshold";
#endif



/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6070                                           */
/*                                      < Velocity threshold  time >                                */
/****************************************************************************************************/
PROTO UINT16 u16VelthresdTime
#ifdef _CiA402_
= 2;
#endif
;

#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6070[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6070[] = "Velocity threshold time";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6071                                           */
/*                                          <Targe Torque>                                          */
/****************************************************************************************************/
PROTO INT16 s16TargTorq
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6071[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6071[] = "Targe Torque";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6072                                           */
/*                                           <Max Torque>                                           */
/****************************************************************************************************/
PROTO UINT16 u16MaxTorq
#ifdef _CiA402_
= 3000;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6072[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6072[] = "Max Torque";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6074                                           */
/*                                      <Torque demand Value>                                       */
/****************************************************************************************************/
PROTO INT16 s16TorqDemandVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6074[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READ};
OBJCONST UCHAR aName0x6074[] = "Torque demand Value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6075                                           */
/*                                       <Motor Rate Current>                                       */
/****************************************************************************************************/
PROTO UINT32 u32MotorRateCur
#ifdef _CiA402_
= 2800;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6075[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6075[] = "Motor Rate Current";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6076                                           */
/*                                       <Motor Rate Torque>                                        */
/****************************************************************************************************/
PROTO UINT32 u32MotorRateTorq
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6076[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6076[] = "Motor Rate Torque";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6077                                           */
/*                                       <Torque actual value>                                      */
/****************************************************************************************************/
PROTO INT16 u16TorqActVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6077[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READ};
OBJCONST UCHAR aName0x6077[] = "Torque actual value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6078                                           */
/*                                       <Current actual value>                                     */
/****************************************************************************************************/
PROTO INT16 s16CurrentActVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6078[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READ};
OBJCONST UCHAR aName0x6078[] = "Current actual value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x607A                                           */
/*                                        <Target position>                                         */
/****************************************************************************************************/
PROTO UINT32 s32TargetPos
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x607A[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x607A[] = "Target position";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x607C                                           */
/*                                          <Home Offset>                                           */
/****************************************************************************************************/
PROTO INT32 s32HomeOffset
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x607C[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x607C[] = "Home Offset";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x607D                                           */
/*                                      <Software Position Limit>                                   */
/****************************************************************************************************/
PROTO TOBJ607D SoftPosLimit
#ifdef _CiA402_
= {2,-2147483648,2147483647};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x607D[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};
OBJCONST UCHAR aName0x607D[] = "Software Position Limit\000Min Position limit\000Max Position limit\000\377";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x607E                                           */
/*                                           <Polarity>                                             */
/****************************************************************************************************/
PROTO UCHAR u8Polarity
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x607E[] = {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READWRITE};
OBJCONST UCHAR aName0x607E[] = "Polarity";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x607F                                           */
/*                                       <Max Profile Velocity>                                     */
/****************************************************************************************************/
PROTO UINT32 u32MaxProfileVel
#ifdef _CiA402_
= 13107200;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x607F[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x607F[] = "Max Profile Velocity";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6080                                           */
/*                                        <Max Motor Speed>                                         */
/****************************************************************************************************/
PROTO UINT32 u32MaxMotorSpd
#ifdef _CiA402_
= 1310720;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6080[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6080[] = "Max Motor Speed";
#endif


/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6081                                           */
/*                                        <Profile Velocity>                                        */
/****************************************************************************************************/
PROTO UINT32 u32ProfileVel
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6081[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6081[] = "Profile Velocity";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6083                                           */
/*                                       <Profile Acceleration>                                     */
/****************************************************************************************************/
PROTO UINT32 u32ProfileAcc
#ifdef _CiA402_
= 131072;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6083[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6083[] = "Profile Acceleration";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6084                                           */
/*                                       <Profile Deceleration>                                     */
/****************************************************************************************************/
PROTO UINT32 u32ProfileDec
#ifdef _CiA402_
= 131072;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6084[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6084[] = "Profile Deceleration";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6085                                           */
/*                                     < Quick Stop Deceleration >                                  */
/****************************************************************************************************/
PROTO UINT32 u32QuickStopDec
#ifdef _CiA402_
= 131072;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6085[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6085[] = "Quick Stop Deceleration";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6086                                           */
/*                                       <Motion Profile Type>                                      */
/****************************************************************************************************/
PROTO INT16 s16MotionProfileType
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6086[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6086[] = "Motion Profile Type";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6087                                           */
/*                                          < Torque Slope >                                        */
/****************************************************************************************************/
PROTO UINT32 u32TorqueSlope
#ifdef _CiA402_
= 1000;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6087[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6087[] = "Torque Slope";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6091                                           */
/*                                         <Gear ratio>                                             */
/****************************************************************************************************/
typedef struct {
   UCHAR   u16SubIndex0;                    /*  SubIndex 0  */
   INT32   aEntries[2];
} TOBJ6091;

PROTO TOBJ6091 PositionFactor
#ifdef _CiA402_
= {2,0x01,0x01};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6091[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};
OBJCONST UCHAR aName0x6091[] = "Gear ratio \000Motor revolutions\000Shaft revolutions\000\377";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6098                                           */
/*                                         <Homing method>                                          */
/****************************************************************************************************/
PROTO CHAR s8HomingMethod
#ifdef _CiA402_
= 35;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6098[] = {DEFTYPE_INTEGER8, 0x08, ACCESS_READWRITE};
OBJCONST UCHAR aName0x6098[] = "Homing method";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6099                                           */
/*                                         <Homing Speed>                                           */
/****************************************************************************************************/
typedef struct {
   UCHAR   u16SubIndex0;                    /*  SubIndex 0  */
   INT32     aEntries[2];
} TOBJ6099;
PROTO TOBJ6099 HomingSpeed
#ifdef _CiA402_
= {2,27962026,5592405};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x6099[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};
OBJCONST UCHAR aName0x6099[] = "Homing Speed\000Speed during search for switch\000Speed during search for zero";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x609A                                           */
/*                                      < Homing Acceleration >                                     */
/****************************************************************************************************/
PROTO UINT32 u32HomingAcc
#ifdef _CiA402_
= 131072;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x609A[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x609A[] = "Homing Acceleration";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60B0                                           */
/*                                        < Position Offset >                                       */
/****************************************************************************************************/
PROTO INT32 s32PositionOffset
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60B0[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60B0[] = "Position Offset";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60B1                                           */
/*                                        < Velocity Offset >                                       */
/****************************************************************************************************/

PROTO INT32 s32VelocityOffset
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60B1[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60B1[] = "Velocity Offset";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60B2                                           */
/*                                        < Torque Offset >                                         */
/****************************************************************************************************/
PROTO INT16 s16TorqueOffset
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60B2[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60B2[] = "Torque Offset";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60B8                                           */
/*                                      < Touch probe function >                                    */
/****************************************************************************************************/
PROTO UINT16 u16TouchProbeFun
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60B8[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60B8[] = "Touch probe function";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60B9                                           */
/*                                      < Touch probe status >                                      */
/****************************************************************************************************/
PROTO UINT16 u16TouchProbeSts
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60B9[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ};
OBJCONST UCHAR aName0x60B9[] = "Touch probe status";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60BA                                           */
/*                                   < Touch probe pos1 pos value >                                 */
/****************************************************************************************************/
PROTO INT32 s32TouchProbePos1PVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60BA[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60BA[] = "Touch probe pos1 pos value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60BB                                           */
/*                                   < Touch probe pos1 neg value >                                 */
/****************************************************************************************************/
PROTO INT32 s32TouchProbePos1NVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60BB[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60BB[] = "Touch probe pos1 neg value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60BC                                           */
/*                                   < Touch probe pos2 pos value >                                 */
/****************************************************************************************************/
PROTO INT32 s32TouchProbePos2PVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC     OBJMEM asEntryDesc0x60BC[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60BC[] = "Touch probe pos2 pos value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60BD                                           */
/*                                   < Touch probe pos2 neg value >                                 */
/****************************************************************************************************/
PROTO INT32 s32TouchProbePos2NVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60BD[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60BD[] = "Touch probe pos1 neg value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60C0                                           */
/*                                 < Interpolation sub mode select >                                */
/****************************************************************************************************/
PROTO INT16 s16InterPolSubModeSel
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C0[] = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60C0[] = "Interpolation sub mode select";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60C1                                           */
/*                                  < Interpolation data record>                                    */
/****************************************************************************************************/
typedef struct {
   UCHAR   u16SubIndex0;                    /*  SubIndex 0  */
   UINT32   u32PosCmd;
   UINT16   u16SymmDiff;
} TOBJ60C1;
extern TOBJ60C1 InterPolDataRecord;
PROTO TOBJ60C1 InterPolDataRecord
#ifdef _CiA402_
= {2,0,0};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C1[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE}};
OBJCONST UCHAR aName0x60C1[] = "Interpolation data record\000Position Command\000Symmetrical diff";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60C2                                           */
/*                                  < Interpolation time period>                                    */
/****************************************************************************************************/
PROTO TOBJ60C2 InterPolTimePeriod
#ifdef _CiA402_
= {2,1,-3};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C2[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER8,  0x8, ACCESS_READWRITE}};
OBJCONST UCHAR OBJMEM aName0x60C2[] = "Interpolation Time Period\000Interpolation period \000Interpolation Index\000\377";
#endif




/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60C5                                           */
/*                                       < Max acceleration >                                       */
/****************************************************************************************************/
PROTO UINT32 u32MaxAcc
#ifdef _CiA402_
= 429496729;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC   OBJMEM  asEntryDesc0x60C5[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60C5[] = "Max acceleration";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60C6                                           */
/*                                       < Max Deceleration >                                       */
/****************************************************************************************************/
PROTO UINT32 u32MaxDec
#ifdef _CiA402_
= 429496729;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C6[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60C6[] = "Max Deceleration";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60E0                                           */
/*                                     < Positive torque limit >                                    */
/****************************************************************************************************/
PROTO UINT16 u16PositTorqLimit
#ifdef _CiA402_
= 3000;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60E0[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60E0[] = "Positive torque limit";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60E1                                           */
/*                                     < Negtive torque limit >                                     */
/****************************************************************************************************/
PROTO UINT16 u16NegtiTorqLimit
#ifdef _CiA402_
= 3000;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60E1[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60E1[] = "Negtive torque limit";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60F2                                           */
/*                                    < Positioning option Code >                                   */
/****************************************************************************************************/
PROTO UINT16 u16PositionOptCode
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC   OBJMEM asEntryDesc0x60F2[] = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60F2[] = "Positioning option Code";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60F4                                           */
/*                                 < Following Error Actual Value >                                 */
/****************************************************************************************************/
PROTO INT32 s32FollowErrActVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60F4[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60F4[] = "Following Error Actual Value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60FC                                           */
/*                                     < Position Demand Value >                                    */
/****************************************************************************************************/
PROTO INT32 s32PosDemandVal
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FC[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60FC[] = "Position Demand Value";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60FD                                           */
/*                                        < Digital Input >                                         */
/****************************************************************************************************/
PROTO UINT32 u32DigitalInput
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FD[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x60FD[] = "Digital Input";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60FE                                           */
/*                                        < Digital Output>                                         */
/****************************************************************************************************/
typedef struct {
   UCHAR   u16SubIndex0;                    /*  SubIndex 0  */
   INT32    aEntries[2];
} TOBJ60FE;
PROTO TOBJ60FE u32DigitOutput
#ifdef _CiA402_
= {2,0x00,0x00};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FE[] = {
                        {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
                        {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE}};
OBJCONST UCHAR aName0x60FE[] = "Digital Output\000Physical output\000BitMask";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x60FF                                           */
/*                                        < Target velocity >                                       */
/****************************************************************************************************/

PROTO INT32 s32TargetVel
#ifdef _CiA402_
= 0;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FF[] = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
OBJCONST UCHAR aName0x60FF[] = "Target velocity";
#endif
/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6100                                           */
/*                                        < MIT_Mode_Entry>                                         */
/****************************************************************************************************/
typedef struct {
   UCHAR   u16SubIndex0;                    /*  SubIndex 0  */
   UINT16    aEntries[17];

#define     EMIT_TorqueFF                0x00
#define     EMIT_Given_Angle             0x01
#define     EMIT_GivenAngVel             0x02
#define     EMIT_PosO_FTC                0x03
#define     EMIT_TorqueO_FTC             0x04
#define     EMIT_Kp_Set                  0x05
#define     EMIT_Kd_Set                  0x06
#define     EMIT_Red_Num                 0x07
#define     EMIT_Red_Den                 0x08
#define     EMIT_TorqueFF_Un             0x09
#define     EMIT_Given_Angle_Un          0x0A
#define     EMIT_GivenAngVel_Un          0x0B
#define     EMIT_Kp_Un                   0x0C
#define     EMIT_Kd_Un                   0x0D
#define     EMIT_Angular_Fbk             0x0E
#define     EMIT_AngVel_Fbk              0x0F
#define     EMIT_Torque_Fbk              0x10
} TOBJ6100;
PROTO TOBJ6100 u16MITMode
#ifdef _CiA402_
= {17,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6100[] = {
                        {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READWRITE},
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     },
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READ     },
                        {DEFTYPE_UNSIGNED16,0x10, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     },
                        {DEFTYPE_INTEGER16, 0x10, ACCESS_READ     }};   //TODO
OBJCONST UCHAR aName0x6100[] = "MIT Mode Entry"
                               "\000MIT Torque feedforward                  "
                               "\000MIT Given angle                         "
                               "\000MIT Given angular velocity              "
                               "\000MIT Position Output Filter Time Constant"
                               "\000MIT Torque Output Filter Time Constant  "
                               "\000MIT Kp Set                              "
                               "\000MIT Kd Set                              "
                               "\000Reducer Numerator                       "
                               "\000Reducer Denominator                     "
                               "\000MIT Torque feedforward Un               "
                               "\000MIT Given angle Un                      "
                               "\000MIT Given angular velocity Un           "
                               "\000MIT Kp Un                               "
                               "\000MIT Kd Un                               "
                               "\000MIT Angular Feedback                    "
                               "\000MIT Angular velocity feedback           "
                               "\000MIT Torque feedback";
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*                                          Object 0x6502                                           */
/*                                      < Supported drive modes >                                   */
/****************************************************************************************************/
PROTO UINT32 u32SuppDriveModes
#ifdef _CiA402_
= 0x3ED;
#endif
;
#ifdef _CiA402_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6502[] = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};
OBJCONST UCHAR aName0x6502[] = "Supported drive modes";
#endif


//*************************************************************************************************
//  ¶ÔÏó×Öµä
//*************************************************************************************************
// Object0x6060

PROTO TOBJECT    OBJMEM ApplicationObjDic[]
#ifdef _CiA402_
= {
   //*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
   {NULL,NULL,0x1C12,{DEFTYPE_UNSIGNED16, MAX_AXES | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc,  aName0x1C12, &sRxPDOassign,                 NULL, NULL,         0x0000 },
   {NULL,NULL,0x1C13,{DEFTYPE_UNSIGNED16, MAX_AXES | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc,  aName0x1C13, &sTxPDOassign,                 NULL, NULL,         0x0000 },
   {NULL,NULL,0xF000,{DEFTYPE_RECORD,     2        | (OBJCODE_REC << 8)}, asEntryDesc0xF000,     aName0xF000, &sModulardeviceprofile,        NULL, NULL,         0x0000 },
   {NULL,NULL,0xF010,{DEFTYPE_UNSIGNED32, MAX_AXES | (OBJCODE_ARR << 8)}, asEntryDesc0xF010,     aName0xF010, &sModuleProfileInfo,           NULL, NULL,         0x0000 },
   {NULL,NULL,0xF030,{DEFTYPE_UNSIGNED32, MAX_AXES | (OBJCODE_ARR << 8)}, asEntryDesc0xF030,     aName0xF030, &sConfiguredModuleIdentList,   NULL, Write0xF030,  0x0000 },
   {NULL,NULL,0xF050,{DEFTYPE_UNSIGNED32, MAX_AXES | (OBJCODE_ARR << 8)}, asEntryDesc0xF050,     aName0xF050, &sDetectedModuleIdentList,     NULL, NULL,         0x0000 },
   //*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
   {NULL,NULL,0x1600,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x16xx, aName0x16xx, &sRPDO1Map,             NULL, NULL, 0x0000 },
   {NULL,NULL,0x1610,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x16xx, aName0x16xx, &sRPDO2Map,             NULL, NULL, 0x0000 },
//   {NULL,NULL,0x1620,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x16xx, aName0x16xx, &sRPDO3Map,             NULL, NULL, 0x0000 },
   {NULL,NULL,0x1A00,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x1Axx, aName0x1Axx, &sTPDO1Map,             NULL, NULL, 0x0000 },
   {NULL,NULL,0x1A10,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x1Axx, aName0x1Axx, &sTPDO2Map,             NULL, NULL, 0x0000 },
//   {NULL,NULL,0x1A20,{DEFTYPE_PDOMAPPING, 10 | (OBJCODE_REC << 8)}, asEntryDesc0x1Axx, aName0x1Axx, &sTPDO3Map,             NULL, NULL, 0x0000 },
   //*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
   {NULL,NULL,0x2000,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2001,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2002,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2003,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2004,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2005,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2006,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2007,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x200A,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x200F,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x200E,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT20XXEntryDesc,        NULL,         NULL,       DT2000R, DT2000W, 0x0000 },
   {NULL,NULL,0x2010,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT2ExxEntryDesc,        NULL,         NULL,       DT2010R, NULL, 0x0000 },
   {NULL,NULL,0x2011,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT2ExxEntryDesc,        NULL,         NULL,       DT2010R, NULL, 0x0000 },
   {NULL,NULL,0x2018,{DEFTYPE_UNSIGNED16, 0xFF | (OBJCODE_REC << 8)},asDT2ExxEntryDesc,        NULL,         NULL,       DT2010R, NULL, 0x0000 },       // Un8xx
   //*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

   {NULL,NULL,0x603F,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x603F, aName0x603F, &u16ErrCode,            NULL, NULL, 0x0000 },
   {NULL,NULL,0x6040,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6040, aName0x6040, &u16ControlWord,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x6041,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6041, aName0x6041, &u16StatusWord,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x605A,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x605A, aName0x605A, &s16QuickShutdownOpt,   NULL, NULL, 0x0000 },
   {NULL,NULL,0x605B,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x605B, aName0x605B, &s16ShutdownOpt,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x605C,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x605C, aName0x605C, &s16DisOperationOpt,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x605D,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x605D, aName0x605D, &s16HaltOptioncode,     NULL, NULL, 0x0000 },
   {NULL,NULL,0x605E,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x605E, aName0x605E, &s16FaultReactOpt,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6060,{DEFTYPE_INTEGER8,   0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6060, aName0x6060, &s8ModeofOP,            NULL, NULL, 0x0000 },
   {NULL,NULL,0x6061,{DEFTYPE_INTEGER8,   0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6061, aName0x6061, &s8ModeofOPDis,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x6062,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6062, aName0x6062, &s32PosDemandValPUU,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x6063,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6063, aName0x6063, &s32PosActValInc,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x6064,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6064, aName0x6064, &s32PosActVal,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x6065,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6065, aName0x6065, &u32FollowErrWind,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6067,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6067, aName0x6067, &u32PosWindow,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x6068,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6068, aName0x6068, &u16PosWindowTime,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x606B,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x606B, aName0x606B, &s32VelDemandVal,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x606C,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x606C, aName0x606C, &s32VelActualVal,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x606D,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x606D, aName0x606D, &u16VelWindow,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x606E,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x606E, aName0x606E, &u16VelWindowTime,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x606F,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x606F, aName0x606F, &u16Velthresd,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x6070,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6070, aName0x6070, &u16VelthresdTime,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6071,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6071, aName0x6071, &s16TargTorq,           NULL, NULL, 0x0000 },
   {NULL,NULL,0x6072,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6072, aName0x6072, &u16MaxTorq,            NULL, NULL, 0x0000 },
   {NULL,NULL,0x6074,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6074, aName0x6074, &s16TorqDemandVal,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6075,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6075, aName0x6075, &u32MotorRateCur,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x6076,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6076, aName0x6076, &u32MotorRateTorq,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6077,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6077, aName0x6077, &u16TorqActVal,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x6078,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6078, aName0x6078, &s16CurrentActVal,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x607A,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x607A, aName0x607A, &s32TargetPos,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x607C,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x607C, aName0x607C, &s32HomeOffset,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x607D,{DEFTYPE_INTEGER32,  2 | (OBJCODE_ARR << 8)}, asEntryDesc0x607D, aName0x607D, &SoftPosLimit,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x607E,{DEFTYPE_UNSIGNED8,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x607E, aName0x607E, &u8Polarity,            NULL, NULL, 0x0000 },
   {NULL,NULL,0x607F,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x607F, aName0x607F, &u32MaxProfileVel,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x6080,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6080, aName0x6080, &u32MaxMotorSpd,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x6081,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6081, aName0x6081, &u32ProfileVel,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x6083,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6083, aName0x6083, &u32ProfileAcc,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x6084,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6084, aName0x6084, &u32ProfileDec,         NULL, NULL, 0x0000 },
   {NULL,NULL,0x6085,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6085, aName0x6085, &u32QuickStopDec,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x6086,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6086, aName0x6086, &s16MotionProfileType,  NULL, NULL, 0x0000 },
   {NULL,NULL,0x6087,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6087, aName0x6087, &u32TorqueSlope,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x6091,{DEFTYPE_INTEGER32,  2 | (OBJCODE_ARR << 8)}, asEntryDesc0x6091, aName0x6091, &PositionFactor,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x6098,{DEFTYPE_INTEGER8,   0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6098, aName0x6098, &s8HomingMethod,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x6099,{DEFTYPE_INTEGER32,  2 | (OBJCODE_ARR << 8)}, asEntryDesc0x6099, aName0x6099, &HomingSpeed,           NULL, NULL, 0x0000 },
   {NULL,NULL,0x609A,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x609A, aName0x609A, &u32HomingAcc,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x60B0,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60B0, aName0x60B0, &s32PositionOffset,     NULL, NULL, 0x0000 },
   {NULL,NULL,0x60B1,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60B1, aName0x60B1, &s32VelocityOffset,     NULL, NULL, 0x0000 },
   {NULL,NULL,0x60B2,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60B2, aName0x60B2, &s16TorqueOffset,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x60B8,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60B8, aName0x60B8, &u16TouchProbeFun,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x60B9,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60B9, aName0x60B9, &u16TouchProbeSts,      NULL, NULL, 0x0000 },
   {NULL,NULL,0x60BA,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60BA, aName0x60BA, &s32TouchProbePos1PVal, NULL, NULL, 0x0000 },
   {NULL,NULL,0x60BB,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60BB, aName0x60BB, &s32TouchProbePos1NVal, NULL, NULL, 0x0000 },
   {NULL,NULL,0x60BC,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60BC, aName0x60BC, &s32TouchProbePos2PVal, NULL, NULL, 0x0000 },
   {NULL,NULL,0x60BD,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60BD, aName0x60BD, &s32TouchProbePos2NVal, NULL, NULL, 0x0000 },
   {NULL,NULL,0x60C0,{DEFTYPE_INTEGER16,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60C0, aName0x60C0, &s16InterPolSubModeSel, NULL, NULL, 0x0000 },
   {NULL,NULL,0x60C1,{DEFTYPE_INTEGER32,  2 | (OBJCODE_REC << 8)}, asEntryDesc0x60C1, aName0x60C1, &InterPolDataRecord,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x60C2,{DEFTYPE_UNSIGNED8,  2 | (OBJCODE_REC << 8)}, asEntryDesc0x60C2, aName0x60C2, &InterPolTimePeriod,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x60C5,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60C5, aName0x60C5, &u32MaxAcc,             NULL, NULL, 0x0000 },
   {NULL,NULL,0x60C6,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60C6, aName0x60C6, &u32MaxDec,             NULL, NULL, 0x0000 },
   {NULL,NULL,0x60E0,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60E0, aName0x60E0, &u16PositTorqLimit,     NULL, NULL, 0x0000 },
   {NULL,NULL,0x60E1,{DEFTYPE_UNSIGNED16, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60E1, aName0x60E1, &u16NegtiTorqLimit,     NULL, NULL, 0x0000 },
   {NULL,NULL,0x60F2,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60F2, aName0x60F2, &u16PositionOptCode,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x60F4,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60F4, aName0x60F4, &s32FollowErrActVal,    NULL, NULL, 0x0000 },
   {NULL,NULL,0x60FC,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60FC, aName0x60FC, &s32PosDemandVal,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x60FD,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60FD, aName0x60FD, &u32DigitalInput,       NULL, NULL, 0x0000 },
   {NULL,NULL,0x60FE,{DEFTYPE_UNSIGNED32, 2 | (OBJCODE_ARR << 8)}, asEntryDesc0x60FE, aName0x60FE, &u32DigitOutput,        NULL, NULL, 0x0000 },
   {NULL,NULL,0x60FF,{DEFTYPE_INTEGER32,  0 | (OBJCODE_VAR << 8)}, asEntryDesc0x60FF, aName0x60FF, &s32TargetVel,          NULL, NULL, 0x0000 },
   {NULL,NULL,0x6100,{DEFTYPE_UNSIGNED16, 17| (OBJCODE_ARR << 8)}, asEntryDesc0x6100, aName0x6100, &u16MITMode,            NULL, NULL, 0x0000 },
   {NULL,NULL,0x6502,{DEFTYPE_UNSIGNED32, 0 | (OBJCODE_VAR << 8)}, asEntryDesc0x6502, aName0x6502, &u32SuppDriveModes,     NULL, NULL, 0x0000 },
   /*------------------------------------------------------------------------------------------------------------------------------------------*/
   {NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL, NULL, 0x000}}
#endif
;


PROTO void APPL_Application(void);

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);

//PROTO void MotorB_ObjInit( void );

#undef PROTO
/** @}*/

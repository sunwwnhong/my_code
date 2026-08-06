/**
******************************************************************************
* @file         types.h
* @version      V1.0
* @date         2020-06-05
* @brief        常用类型重定义
*
* @company      深圳炜世科技有限公司
* @information  WIZnet W5500官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com
* @forum        www.w5500.cn
* @qqGroup      579842114
* @Support      QQ:2571856470；Mob:18998931307
* @Email        support@wisioe.com
******************************************************************************
*/
#ifndef _TYPE_H_
#define _TYPE_H_

#define MAX_SOCK_NUM 8 // Maxmium number of socket

typedef Uint16 uint8_t;

typedef int16 int8;
typedef Uint16 uint8;
typedef volatile int16 vint8;
typedef volatile Uint16 vuint8;

typedef uint8  u_char;    /**< 8-bit value */
typedef uint8  SOCKET;
typedef uint16 u_short;   /**< 16-bit value */
typedef uint16 u_int;     /**< 16-bit value */
typedef uint32 u_long;    /**< 32-bit value */

// LS_20230602
typedef volatile Uint16 vu8;
typedef volatile Uint32 vu32;
typedef int16 int8_t;
typedef Uint16 u8;


typedef union _un_l2cval 
{
 u_long lVal;
 u_char cVal[4];
}un_l2cval;

typedef union _un_i2cval 
{
 u_int iVal;
 u_char cVal[2];
}un_i2cval;

#endif /* _TYPE_H_ */

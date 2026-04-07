 
 
 
 
 
 
 
 
 
 
 
 

#ifndef __CLAMATH_H__
#define __CLAMATH_H__

 
 
 
 
 
 
#ifdef __cplusplus
extern "C"
{
#endif
 
 
 
 
 
#include <stdint.h>

 
 
 
 
 
#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float         float32_t;
typedef double        float64_t;
#else  
typedef float         float32_t;
typedef long double   float64_t;
#endif  
#endif  

 
 
 
 
 
 
#ifdef __TMS320C28XX_CLA__

 
 
 
 
 
#ifdef __TMS320C28XX_CLA2__
 
 
 
#define acosf              CLAacos_inline
#define asinf              CLAasin_inline
#define atanf              CLAatan_inline
#define atan2f             CLAatan2_inline
#define cosf               CLAcos_inline
#define expf               CLAexp_inline
#define logf               CLAln_inline
#define log10f             CLAlog10_inline
#define sinf               CLAsin_inline
#define sqrtf              CLAsqrt_inline
#define tanf(m)            (CLAsin_inline(m)/CLAcos_inline(m))

 
 
 
#define __divf32           CLAdiv_inline
#define __sqrt             CLAsqrt_inline
#define __sin              CLAsin_inline
#define __cos              CLAcos_inline
#define __atan             CLAatan_inline
#define __atan2            CLAatan2_inline
#define __sinpuf32         CLAsinPU_inline
#define __cospuf32         CLAcosPU_inline

#else
 
 
 
#define acosf              CLAacos
#define asinf              CLAasin
#define atanf              CLAatan
#define atan2f             CLAatan2
#define cosf               CLAcos
#define expf               CLAexp
#define logf               CLAln
#define log10f             CLAlog10
#define sinf               CLAsin
#define sqrtf              CLAsqrt
#define tanf(m)            (CLAsin(m)/CLAcos(m))

 
 
 
#define __divf32           CLAdiv
#define __sqrt             CLAsqrt
#define __sin              CLAsin
#define __cos              CLAcos
#define __atan             CLAatan
#define __atan2            CLAatan2
#define __sinpuf32         CLAsinPU
#define __cospuf32         CLAcosPU

#endif

 
 
 
#define fmaxf              __mmaxf32
#define fminf              __mminf32

 
 
 
#define __eallow           __meallow
#define __edis             __medis

 
 
 
#define __einvf32          __meinvf32
#define __eisqrtf32        __meisqrtf32
#define __f32toi16r        __mf32toi16r
#define __f32toui16r       __mf32toui16r
#define __fmax             __mmaxf32
#define __fmin             __mminf32
#define __fracf32          __mfracf32
#define __swapf            __mswapf
#define __swapff           __mswapf
#endif

 
 
 
 
 

 
extern float32_t CLAsincosTable[];
extern float32_t CLAsinTable[];
extern float32_t *CLAsincosTable_Sin0;
extern float32_t CLAcosTable[];
extern float32_t *CLAsincosTable_Cos0;
extern float32_t *CLAsinTableEnd;
extern float32_t *CLAcosTableEnd;
extern float32_t *CLAsincosTableEnd;
extern float32_t CLAsincosTable_TABLE_SIZE;
extern float32_t CLAsincosTable_TABLE_SIZEDivTwoPi;
extern float32_t CLAsincosTable_TwoPiDivTABLE_SIZE;
extern float32_t CLAsincosTable_TABLE_MASK;
extern float32_t CLAsincosTable_Coef0;
extern float32_t CLAsincosTable_Coef1;
extern float32_t CLAsincosTable_Coef1_pos;
extern float32_t CLAsincosTable_Coef2;
extern float32_t CLAsincosTable_Coef3;
extern float32_t CLAsincosTable_Coef3_neg;

 
extern float32_t CLAatan2HalfPITable[];
extern float32_t CLAatan2Table[];
extern float32_t *CLAatan2TableEnd;
extern float32_t *CLAINV2PI;

 
extern float32_t CLAacosinHalfPITable[];
extern float32_t CLAacosinTable[];
extern float32_t *CLAacosinTableEnd;

 
extern float32_t CLAasinHalfPITable[];
extern float32_t CLAasinTable[];
extern float32_t *CLAasinTableEnd;

 
extern float32_t CLAINV1,CLAINV2,CLAINV3,CLAINV4;
extern float32_t CLAINV5,CLAINV6,CLAINV7,CLALOG10;
extern float32_t CLAExpTable[];
extern float32_t *CLAExpTableEnd;

 
extern float32_t CLALNV2,CLALNVe,CLALNV10,CLABIAS;
extern long CLALN_TABLE_MASK1,CLALN_TABLE_MASK2;
extern float32_t CLALnTable[];
extern float32_t *CLALnTableEnd;

 
extern uint16_t  _cla_scratchpad_start;
extern uint16_t  _cla_scratchpad_end;

 
 
 
 
 
extern float32_t CLAacos( float32_t fVal );
extern float32_t CLAacos_spc( float32_t fVal );
extern float32_t CLAasin( float32_t fVal );
extern float32_t CLAatan( float32_t fVal );
extern float32_t CLAatan2( float32_t fVal1, float32_t fVal2 );
extern float32_t CLAatan2PU( float32_t fVal1, float32_t fVal2 );
extern float32_t CLAcos( float32_t fAngleRad);
extern float32_t CLAcosPU( float32_t fAngleRadPU );
extern float32_t CLAdiv( float32_t fNum, float32_t fDen);
extern float32_t CLAexp( float32_t fVal);
extern float32_t CLAexp10( float32_t fVal);
extern float32_t CLAexp2( float32_t fNum, float32_t fDen );
extern float32_t CLAisqrt( float32_t fVal );
extern float32_t CLAln( float32_t fVal);
extern float32_t CLAlog10( float32_t fVal);
extern float32_t CLAsin( float32_t fAngleRad );
extern float32_t CLAsinPU( float32_t fAngleRadPU);
extern float32_t CLAsqrt( float32_t fVal);
extern void CLAsincos(float32_t fAngleRad, float32_t *y_sin, float32_t *y_cos);
extern float32_t CLAexpN(float32_t fVal, float32_t N);
extern float32_t CLAlogN(float32_t fVal, float32_t N);

 
 
 
 
 
#define CLAMATH_TWOPI_DIV_TABLE_SIZE   0.04908738521234f
#define CLAMATH_LN_2                   0.693147181f
#define CLAMATH_LN_10                  2.302585093f
#define CLAMATH_TABLE_SIZE             64f
#define CLAMATH_TABLE_SIZE_M_1         63.0f
#define CLAMATH_PI                     3.141592653589f
#define CLAMATH_PI_DIV_TWO             1.570796327f

#ifdef __TMS320C28XX_CLA__

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAdiv_inline)
static inline float32_t CLAdiv_inline( float32_t fNum, float32_t fDen )
{
     
    float32_t Ye,Yee;    
    float32_t result;

    Ye = __meinvf32(fDen);

    Yee = Ye*fDen;
    Yee = 2 - Yee;
    Ye = Ye * Yee;

    Yee = Ye*fDen;
    Yee = 2 - Yee;
    Ye = Ye * Yee;

    result = Ye * fNum;

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAacos_inline)
static inline float32_t CLAacos_inline(float32_t fVal)
{
    int32_t xTblIdx;     
    float32_t A0, A1, A2;  
    float32_t *entry;
    float32_t result;

    xTblIdx = fabsf(fVal) * CLAMATH_TABLE_SIZE_M_1;
    xTblIdx = xTblIdx * 3;
     
     

    entry = &CLAacosinTable[xTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + (fabsf(fVal) * (A1 + (A2 * fabsf(fVal))));

    if(fVal < 0.0f)
    {
       result = CLAMATH_PI - result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAasin_inline)
static inline float32_t CLAasin_inline(float32_t fVal)
{
    int32_t xTblIdx;     
    float32_t A0, A1, A2;  
    float32_t *entry;
    float32_t result;
    float32_t temp;
    temp = fabsf(fVal);
    xTblIdx = temp * CLAMATH_TABLE_SIZE_M_1;
    xTblIdx = xTblIdx * 3;
     
     

    entry = &CLAasinTable[xTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + (fabsf(fVal) * (A1 + (A2 * fabsf(fVal))));

    if(fVal < 0.0f)
    {
       result = - result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAatan_inline)
static inline float32_t CLAatan_inline(float32_t fVal)
{
    uint32_t uxTblIdx;     
    float32_t ratio;
    float32_t num,den;
    float32_t A0, A1, A2;  
    float32_t *entry;
    float32_t result;

    num = __mminf32(fabsf(fVal), 1.0f);
    den = __mmaxf32(fabsf(fVal), 1.0f);
    ratio = (num/den);  
                        
    uxTblIdx = ratio * CLAMATH_TABLE_SIZE_M_1;
    uxTblIdx = uxTblIdx * 3;
     
     

    entry = &CLAatan2Table[uxTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + ratio * (A1 + A2 * ratio);
    if(fabsf(fVal) > 1.0f)
    {
       result = CLAMATH_PI_DIV_TWO - result;
    }
    if(fVal < 0.0f)
    {
       result = - result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAatan2_inline)
static inline float32_t CLAatan2_inline( float32_t fVal1, float32_t fVal2 )
{
    uint32_t uxTblIdx;     
    float32_t ratio;
    float32_t num,den;
    float32_t A0, A1, A2;  
    float32_t *entry;
    float32_t result;

    num = __mminf32(fabsf(fVal1), fabsf(fVal2));
    den = __mmaxf32(fabsf(fVal1), fabsf(fVal2));

    ratio = CLAdiv_inline(num, den);

    uxTblIdx = ratio * CLAMATH_TABLE_SIZE_M_1;
    uxTblIdx = uxTblIdx * 3;
     
     

    entry = &CLAatan2Table[uxTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + ratio * (A1 + A2 * ratio);

    if((fVal1 < 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = result - CLAMATH_PI;
    }
    else if((fVal1 < 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = -result - CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 < 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = result - CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 < 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = -result;
    }
    else if((fVal1 > 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = CLAMATH_PI_DIV_TWO - result;
    }
    else if((fVal1 > 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = result + CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 > 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = CLAMATH_PI - result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAatan2PU_inline)
static inline float32_t CLAatan2PU_inline( float32_t fVal1, float32_t fVal2)
{
    float32_t result = CLAatan2_inline(fVal1, fVal2)/(2*CLAMATH_PI);

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAcos_inline)
static inline float32_t CLAcos_inline(float32_t fAngleRad)
{
    float32_t tblIdx;
    float32_t X;           
    float32_t SinK,CosK;
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index = (((int16_t)tblIdx) & (int16_t)0x007F);

    SinK = CLAsincosTable[index];        
    CosK = CLAsincosTable[index+32];     

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

     
    return(CosK + X * (-SinK                           \
                + X * (CLAsincosTable_Coef0 * CosK     \
                + X * (CLAsincosTable_Coef1_pos * SinK \
                + X * (CLAsincosTable_Coef2 * CosK     \
                + X * (CLAsincosTable_Coef3_neg * SinK))))));
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAcosPU_inline)
static inline float32_t CLAcosPU_inline(float32_t fAngleRadPU)
{
    float32_t tblIdx;
    float32_t X;             
    float32_t SinK, CosK;
    int16_t index;

    tblIdx = fAngleRadPU * 2 * CLAMATH_PI * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index=(((int16_t)tblIdx) & (int16_t)0x007F);

    SinK = CLAsincosTable[index];        
    CosK = CLAsincosTable[index+32];     

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

     
    return(CosK + X * (-SinK                           \
                + X * (CLAsincosTable_Coef0 * CosK     \
                + X * (CLAsincosTable_Coef1_pos * SinK \
                + X * (CLAsincosTable_Coef2 * CosK     \
                + X * (CLAsincosTable_Coef3_neg * SinK))))));
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAexp_inline)
static inline float32_t CLAexp_inline(float32_t fVal)
{
    float32_t X;         
    float32_t Xm;        
    int16_t Idx;         
    float32_t Ei,Em;     
    float32_t result;

     
    X = fabsf(fVal);

     
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

     
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1+Xm*CLAINV2*(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(fVal < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAexp10_inline)
static inline float32_t CLAexp10_inline(float32_t fVal)
{
    float32_t CLALOG10_E = 2.30258509f;
    float32_t X;         
    float32_t Xm;        
    int16_t Idx;         
    float32_t Ei,Em;     
    float32_t result;

     
    X = fabsf(fVal*CLALOG10_E);

     
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

     
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1 + Xm*CLAINV2 *(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(fVal < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAexp2_inline)
static inline float32_t CLAexp2_inline( float32_t fNum, float32_t fDen)
{
    float32_t X;         
    float32_t Y;
    float32_t Xm;        
    int16_t Idx;         
    float32_t Ei,Em;     
    float32_t result;

     
    Y = fNum/fDen;
    X = fabsf(Y);

     
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

     
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1+Xm*CLAINV2*(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(Y < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAisqrt_inline)
static inline float32_t CLAisqrt_inline(float32_t fVal)
{
    float32_t Ye, Yee, Yeee;
    float32_t result;

    Ye = __meisqrtf32(fVal);  

    if(fVal  == 0.0f)
    {
        Ye = 0.0f;
    }

    Yee = Ye * (1.5f - Ye * Ye * fVal * 0.5f);   
    Yeee = Yee * (1.5f - Yee * Yee * fVal * 0.5f);  

    result = Yeee;

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAln_inline)
static inline float32_t CLAln_inline(float32_t fVal)
{
    float32_t Xm,E;
    float32_t A0,A1,A2;
    float32_t result;
    int32_t Idx;
    int32_t tmp;
    union{
        uint32_t mem_i;
        float32_t mem_f;
    }X;

     
    X.mem_f = fVal;

     
    tmp = (X.mem_i >> 23) - 127;
    E = tmp * CLAMATH_LN_2;

     
    X.mem_i = (X.mem_i & 0x3FFFFFFF) | 0x3F800000;
     
     
     
     
     

    Xm = __mfracf32(X.mem_f);
     
     

     
     
    Idx = (int32_t)(Xm * 32.0f);
    Idx *= 3;  
               
    A0 = CLALnTable[Idx];
    A1 = CLALnTable[Idx+1];
    A2 = CLALnTable[Idx+2];

    result = A0 + Xm * (A1 + A2 * Xm) + E;

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAlog10_inline)
static inline float32_t CLAlog10_inline(float32_t fVal)
{
    float32_t Xm,E;
    float32_t A0,A1,A2;
    float32_t ln_fVal;
    float32_t result;
    int32_t Idx;
    int32_t tmp;
    union{
        uint32_t mem_i;
        float32_t mem_f;
    }X;

     
    X.mem_f = fVal;

     
    tmp = (X.mem_i >> 23) - 127;
    E = tmp * CLAMATH_LN_2;

     
    X.mem_i = (X.mem_i & 0x3FFFFFFF)| 0x3F800000;
     
     
     
     
     

    Xm = __mfracf32(X.mem_f);
     
     

     
     
    Idx = (int32_t)(Xm * 32.0f);
    Idx *= 3;  
               
    A0 = CLALnTable[Idx];
    A1 = CLALnTable[Idx+1];
    A2 = CLALnTable[Idx+2];

    ln_fVal = A0 + Xm * (A1 + A2 * Xm) + E;
    result = ln_fVal / CLAMATH_LN_10;

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAsin_inline)
static inline float32_t CLAsin_inline(float32_t fAngleRad)
{
    float32_t tblIdx;      
    float32_t X;           
    float32_t SinK,CosK;   
                           
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index= (((int16_t)tblIdx) & (int16_t)0x007F);
    SinK = CLAsincosTable[(int16_t)index];
    CosK = CLAsincosTable[index+32];

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

     
    return(SinK + X * (CosK                        \
                + X * (CLAsincosTable_Coef0 * SinK \
                + X * (CLAsincosTable_Coef1 * CosK \
                + X * (CLAsincosTable_Coef2 * SinK \
                + X * (CLAsincosTable_Coef3 * CosK))))));
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAsinPU_inline)
static inline float32_t CLAsinPU_inline(float32_t fAngleRadPU)
{
    float32_t tblIdx;      
    float32_t X;           
    float32_t SinK,CosK;   
                           
    int16_t index;

    tblIdx = fAngleRadPU * 2 * CLAMATH_PI * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index= (((int16_t)tblIdx)&(int16_t)0x007F);
    SinK = CLAsincosTable[(int16_t)index];
    CosK = CLAsincosTable[index+32];

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

     
    return(SinK + X * (CosK                        \
                + X * (CLAsincosTable_Coef0 * SinK \
                + X * (CLAsincosTable_Coef1 * CosK \
                + X * (CLAsincosTable_Coef2 * SinK \
                + X * (CLAsincosTable_Coef3 * CosK))))));
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAsqrt_inline)
static inline float32_t CLAsqrt_inline(float32_t fVal)
{
    float32_t y0, y1, y2;

    y0 = __meisqrtf32(fVal);    


    if(fVal == 0.0f)
    {
        y0 = 0.0f;
    }

    y1 = y0*((float32_t)1.5f - y0*y0*fVal*(float32_t)0.5f);
     
    y2 = y1*((float32_t)1.5f - y1*y1*fVal*(float32_t)0.5f);
     
    y2 = y2 * fVal;
     

    return(y2);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAsincos_inline)
static inline void CLAsincos_inline(float32_t fAngleRad,
                                    float32_t *y_sin,
                                    float32_t *y_cos)
{
    float32_t tblIdx;      
    float32_t X;           
    float32_t SinK, CosK;  
                           
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index=(((int16_t)tblIdx)&(int16_t)0x007F);

    SinK = CLAsincosTable[index];     
    CosK = CLAsincosTable[index+32];  

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

     
    *y_cos = CosK + X * (-SinK             \
            + X * (CLAsincosTable_Coef0 * CosK   \
            + X * (CLAsincosTable_Coef1_pos * SinK   \
            + X * (CLAsincosTable_Coef2 * CosK   \
            + X * (CLAsincosTable_Coef3_neg * SinK)))));

    *y_sin = SinK + X * (CosK                 \
            + X * (CLAsincosTable_Coef0 * SinK   \
            + X * (CLAsincosTable_Coef1 * CosK   \
            + X * (CLAsincosTable_Coef2 * SinK   \
            + X * (CLAsincosTable_Coef3 * CosK)))));
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAexpN_inline)
static inline float32_t CLAexpN_inline(float32_t fVal, float32_t N)
{
    float32_t ln_N;    
    float32_t Exp;     
    float32_t result;

     
    ln_N = CLAln_inline(N);

     
    Exp = fVal*ln_N;

     
    result = CLAexp_inline(Exp);

    return(result);
}

 
 
 
#pragma FUNC_ALWAYS_INLINE(CLAlogN_inline)
static inline float32_t CLAlogN_inline(float32_t fVal, float32_t N)
{
    float32_t ln_fVal;
    float32_t ln_N;
    float32_t result;

     
    ln_fVal = CLAln_inline(fVal);

     
    ln_N = CLAln_inline(N);

     
    result = CLAdiv_inline(ln_fVal, ln_N);

    return(result);
}

 
 
 
static inline float32_t CLA_floor(float32_t val)
{
    volatile uint32_t temp = (uint32_t)val;

    if(val < 0.0f)
    {
        temp = temp - 1;
    }

    return((float32_t)temp);
}

 
 
 
static inline float32_t CLA_ceil(float32_t val)
{
    volatile uint32_t temp = (uint32_t)val;

    if(val > 0.0f)
    {
        temp = temp + 1;
    }

    return((float32_t)temp);
}

#endif

 
 
 
 
 
#ifdef __cplusplus
}
#endif  

#endif  

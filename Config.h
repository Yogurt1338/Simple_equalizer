#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include <math.h>

// Определение
typedef unsigned int                      UINT16;
typedef unsigned long                     UINT32;
typedef unsigned char                     UINT8;
typedef int                               INT16;
typedef long                              INT32;
typedef char                              INT8;

typedef float                             FP32;
typedef double                            FP64;

typedef unsigned long                     uint40_t;
typedef unsigned int                      uint32_t;
typedef unsigned short                    uint16_t;
typedef unsigned char                     uint8_t;
typedef long                              int40_t;
typedef int                               int32_t;
typedef short                             int16_t;

typedef float                             fp32_t;
typedef double                            fp64_t;

typedef long long                         int64_t;

typedef struct {
    float real;
	float imag;
} COMPLEX;

/* Constants */
#define PI                                (3.1416f)
#define PI_DIV2                           (1.5708f)

/* Function Define */
#ifndef ClrBit
#define ClrBit(reg, bit)                  reg &= ~(1 << bit)
#endif

#ifndef SetBit
#define SetBit(reg, bit)                  reg |= (1 << bit)
#endif 

/* Constants */
#define ZX_SUCCESS                        (1)
#define ZX_FAILURE                        (0)

#define LEVEL_HIGH                        (1)
#define LEVEL_LOW                         (0)

/* ASSERT */
// uncomment line below to 
#define USE_FULL_ASSERT
#ifdef USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed function
 *   which reports the name of the source file and the source
 *   line number of the call that failed. 
 *   If expr is true, it returns no value.
 * @retval None
 */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  extern void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif

#endif
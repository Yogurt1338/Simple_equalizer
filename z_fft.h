#ifndef _Z_FFT_H
#define _Z_FFT_H

#include "Config.h"
#include "math.h"

// Определение типа для элементов FFT
#define TYPE_FFT_E     float    /* Тип совпадает с типом члена COMPLEX */     

#ifndef PI
#define PI             (3.14159265f)
#endif

// Определение типа COMPLEX из Config.h
typedef COMPLEX TYPE_FFT;  /* Определение COMPLEX в Config.h */

// Прототипы функций для FFT и обратного FFT
extern int fft(TYPE_FFT *x, uint32_t N);          // Функция для вычисления FFT
extern int fft_real(TYPE_FFT *x, uint32_t N);     // Функция для вычисления FFT для действительных чисел
extern int ifft(TYPE_FFT *x, uint32_t N);         // Функция для вычисления обратного FFT
extern int ifft_real(TYPE_FFT *x, uint32_t N);    // Функция для вычисления обратного FFT для действительных чисел

#endif /* _Z_FFT_H_ */
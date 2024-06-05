#ifndef _Z_MATH_H
#define _Z_MATH_H

#include "Config.h"

// Определение типа COMPLEX из Config.h
typedef COMPLEX TYPE_FFT;  /* Определение COMPLEX в Config.h */

/* Определения типов */
typedef float TYPE_SCALE; // Определение типа для масштабирования
typedef float TYPE_MAX;   // Определение типа для максимального значения

/* Прототипы глобальных функций */
uint32_t floor_log2_32(uint32_t x); // Прототип функции для нахождения логарифма по основанию 2 от числа x
uint32_t reverse_bits(uint32_t num, uint32_t bit_size); // Прототип функции для обращения битов в числе
void butterfly(TYPE_FFT *x, int le, int le2, float sR, float sI, uint32_t N); // Прототип вспомогательной функции для выполнения операций "бабочки" в FFT

#endif /* _Z_MATH_H */

#ifndef _IIR_H_
#define _IIR_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// // Структура для хранения параметров фильтра
// typedef struct {
//     double fc; // Частота среза
//     double Q; // Фактор добротности
//     double a0, a1, a2, b1, b2; // Коэффициенты фильтра
//     double x1, x2, y1, y2; // Предыдущие значения входа и выхода
// } BiQuadFilter;


// void filter(unsigned char *buffer, size_t i);
// void applyFilters(BiQuadFilter* filters, double* input, double* output, int numSamples);

// void initFilter(BiQuadFilter* f, double fc, double Q);



// Определите размерность фильтра
// #define N 5 // Порядок числителя
// #define M 5 // Порядок знаменателя

// // Структура для хранения состояния фильтра
// typedef struct {
//     double a[M + 1]; // Коэффициенты знаменателя (a[0] = 1.0 обычно)
//     double b[N + 1]; // Коэффициенты числителя
//     double x[N + 1]; // Входные задержки
//     double y[M + 1]; // Выходные задержки
// } IIRFilter;

// void filter(unsigned char *buffer, size_t inputLength);

#endif
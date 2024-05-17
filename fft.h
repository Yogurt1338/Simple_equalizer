#ifndef _FFT_H_
#define _FFT_H_
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "z_fft.h" 
#include "Config.h" 
void fftProcessRadix2(float *real, float *imag, size_t N, float rate);
void ifftProcessRadix2(float *real, float *imag, size_t N, float rate);

// void fftProcessRadix2(complex float *data, size_t N, float rate);
// void ifftProcessRadix2(complex float *data, size_t N, float rate);
void saveToExcel(const char *filename,TYPE_FFT *x, const size_t N, const float rate);

void chaaf(TYPE_FFT *x, size_t N, float rate);
void mltp(TYPE_FFT *x, size_t i, float q);
void s_mltp(TYPE_FFT *x, size_t i, float q);

#define COF 1
#define M_PI 3.14159265358979323846264338327950288

#endif
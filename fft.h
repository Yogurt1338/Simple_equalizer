#ifndef _FFT_H_
#define _FFT_H_

void fftProcessRadix2(float *real, float *imag, size_t N, float rate);
void ifftProcessRadix2(float *real, float *imag, size_t N, float rate);

void chaaf(float *real, float *imag, size_t N, float rate);

#define M_PI 3.14159265358979323846264338327950288

#endif
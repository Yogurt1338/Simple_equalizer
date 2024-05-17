// reference
// https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
//
#include "fft.h"
#include "main.h"

void saveToExcel(const char *filename,TYPE_FFT *x, const size_t N, const float rate) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write header
    fprintf(file, "Frequency, Amplitude\n");

    for (size_t i = 0; i < N; i++) {
        float frequency = i * rate / N; // Вычисление частоты
        float amplitude = 2.0 * sqrt(x[i].real * x[i].real + x[i].imag * x[i].imag) / N; // Вычисление амплитуды
        fprintf(file, "%.5f  %.5f\n", frequency, amplitude);
    }

    fclose(file);
}

static size_t reverseBits(size_t x, const int n)
{
    size_t ret = 0;
    for (int i = 0; i < n; i++) {
        ret = (ret << 1) | (x & 0x1);
        x >>= 1;	
    } 
    return ret;
}

void fftProcessRadix2(float *real, float *imag, const size_t N, const float rate)
{
    const int nStages = log2(N);

    float *w_real = calloc(N / 2, sizeof(float));
    float *w_imag = calloc(N / 2, sizeof(float));

    for (size_t i = 0; i < N / 2; i ++) {
        const float theta = -2.0 * M_PI * i / N;
        w_real[i] = cosf(theta);
        w_imag[i] = sinf(theta);
    }

    for (size_t i = 0; i < N; i++) {
        const size_t j = reverseBits(i, nStages);
        if (j > i) {
            float temp = real[i];
            real[i] = real[j];
            real[j] = temp;

            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
    }

    for (size_t stage = 2; stage <= N; stage <<= 1) {
        const size_t halfSize = stage >> 1;
        const size_t wStep = N / stage;
        for (size_t group = 0; group < N; group += stage) {
            for (size_t pair = group, w = 0; pair < group + halfSize; pair++, w += wStep) {
                const size_t match = pair + halfSize;
                const float tempRe = real[match] * w_real[w] + imag[match] * w_imag[w];
                const float tempIm = -real[match] * w_imag[w] + imag[match] * w_real[w];
                real[match] = real[pair] - tempRe;
                imag[match] = imag[pair] - tempIm;
                real[pair] += tempRe;
                imag[pair] += tempIm;
            }
        }
    }

    free(w_real);
    free(w_imag);
}

void ifftProcessRadix2(float *real, float *imag, const size_t N, const float rate)
{
    for (size_t i = 0; i < N; i++) {
        imag[i] = -imag[i];
    }

    fftProcessRadix2(real, imag, N, rate);

    for (size_t i = 0; i < N; i++) {
        real[i] /= N;
        imag[i] /= N;
    }
}

void chaaf(TYPE_FFT *x, size_t N, float rate)
{

    // for (size_t i = 0; i < N / 2; i++) 
    // {    
    //     float frequency = i * rate / N; // Вычисление частоты
    //     float amplitude = 2.0 * sqrt(x[i].real * x[i].real + x[i].imag * x[i].imag) / N; // Вычисление амплитуды
    
    // void chaaf(COMPLEX *x, uint32_t N, float rate) {
    //     // Определяем частоту 3600 Гц в отсчетах FFT
    float freq_3600 = 3600.0f * N / rate;

    // Применение фильтра для исключения частот ниже 3600 Гц
    for (size_t i = 0; i < N; i++) {
        // Исключаем частоты ниже 3600 Гц
        if (i < freq_3600) {
            x[i].real = 0.0f;
            x[i].imag = 0.0f;
        }
    }
// }

        // if (3600 < frequency && frequency < 7200)
        // {
        //     if (sliders[1].value > 0) mltp(real, imag, i, sliders[1].value);
        //     else if (sliders[1].value < 0) s_mltp(real, imag, i, sliders[1].value);
        // }

        // if (7200 < frequency && frequency < 10800)
        // {
        //     if (sliders[2].value > 0) mltp(real, imag, i, sliders[2].value);
        //     else if (sliders[2].value < 0) s_mltp(real, imag, i, sliders[2].value);
        // }

        // if (10800 < frequency && frequency < 14400)
        // {
        //     if (sliders[3].value > 0) mltp(real, imag, i, sliders[3].value);
        //     else if (sliders[3].value < 0) s_mltp(real, imag, i, sliders[3].value);
        // }
        
        // if (14400 < frequency && frequency < 18000)
        // {
        //     if (sliders[4].value > 0) mltp(real, imag, i, sliders[4].value);
        //     else if (sliders[4].value < 0) s_mltp(real, imag, i, sliders[4].value);
        // }

        // if (frequency > 18000)
        // {  
        //     if (sliders[5].value > 0) mltp(real, imag, i, sliders[5].value);
        //     else if (sliders[5].value < 0) s_mltp(real, imag, i, sliders[5].value);
        // }
    
        #if DEBUG == 4
            printf("freq: %.5f, value: %.5f \n", frequency, amplitude);
        #endif
    // }
}

void mltp(TYPE_FFT *x, size_t i, float q)
{   
    #if DEBUG == 2
        printf("Before mltp - Real: %.2f, Imag: %.2f \n", x[i].real,  x[i].imag);
    #endif
    // printf("ra: %.2f, value: %.2f \n", real[i], q);
    x[i].real = 0.0f;
    x[i].imag = 0.0f;
    // printf("rea: %.2f, value: %.2f \n", real[i], q);
    #if DEBUG == 2
        printf("After mltp - Real: %.2f, Imag: %.2f \n", x[i].real,  x[i].imag);
    #endif
}

// void s_mltp(TYPE_FFT *x, size_t i, float q)
// {
//     real[i] = real[i] / q;
//     imag[i] = imag[i] / q;
// }



/*
static size_t reverseBits(size_t x, const int n)
{
    size_t ret = 0;
    for (int i = 0; i < n; i++) {
        ret = (ret << 1) | (x & 0x1);
        x >>= 1;	
    } 
    return ret;
}

void fftProcessRadix2(float *real, float *imag, const size_t N, const float rate)
{
    const int nStages = log2(N);

    float *w_real = calloc(N / 2, sizeof(float));
    float *w_imag = calloc(N / 2, sizeof(float));

    for (size_t i = 0; i < N / 2; i ++) {
        const float theta = -2.0 * M_PI * i / N;
        w_real[i] = cosf(theta);
        w_imag[i] = sinf(theta);
    }

    for (size_t i = 0; i < N; i++) {
        const size_t j = reverseBits(i, nStages);
        if (j > i) {
            float temp = real[i];
            real[i] = real[j];
            real[j] = temp;

            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
    }

    for (size_t stage = 2; stage <= N; stage <<= 1) {
        const size_t halfSize = stage >> 1;
        const size_t wStep = N / stage;
        for (size_t group = 0; group < N; group += stage) {
            for (size_t pair = group, w = 0; pair < group + halfSize; pair++, w += wStep) {
                const size_t match = pair + halfSize;
                const float tempRe = real[match] * w_real[w] + imag[match] * w_imag[w];
                const float tempIm = -real[match] * w_imag[w] + imag[match] * w_real[w];
                real[match] = real[pair] - tempRe;
                imag[match] = imag[pair] - tempIm;
                real[pair] += tempRe;
                imag[pair] += tempIm;
            }
        }
    }
        for (size_t i = 0; i < N; i++) 
        {    
            float amplitude = 2.0 * sqrtf(real[i] * real[i] + imag[i] * imag[i]) / N;

            float frequency = i * rate / N;

            // printf("freq: %.5f, value: %.5f \n", frequency, amplitude);
            saveToExcel("output.csv", real, imag, N, rate);
        }

    free(w_real);
    free(w_imag);
}

void ifftProcessRadix2(float *real, float *imag, const size_t N, const float rate)
{
    for (size_t i = 0; i < N; i++) {
        imag[i] = -imag[i];
    }

    fftProcessRadix2(real, imag, N, rate);

    for (size_t i = 0; i < N; i++) {
        real[i] /= N;
        imag[i] /= N;
    }
}
*/
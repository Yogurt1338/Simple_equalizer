#include "z_math.h"
#include <limits.h>

// Вспомогательная функция для выполнения операций "бабочки" в FFT
void butterfly(TYPE_FFT *x, int le, int le2, float sR, float sI, uint32_t N) {
    float tR, tI, uR, uI;
    uR = 1;
    uI = 0;

    // Цикл по каждому поддиапазону DFT
    for (int j = 1; j <= le2; j++) {
        // Цикл по каждой "бабочке"
        for (int i = j - 1; i < N; i += le) {
            int ip = i + le2;
            tR = x[ip].real * uR - x[ip].imag * uI;
            tI = x[ip].real * uI + x[ip].imag * uR;
            x[ip].real = x[i].real - tR;
            x[ip].imag = x[i].imag - tI;
            x[i].real += tR;
            x[i].imag += tI;
        }
        // Обновление коэффициентов вращения
        tR = uR;
        uR = tR * sR - uI * sI;
        uI = tR * sI + uI * sR;
    }
}

// Функция для нахождения логарифма по основанию 2 от числа x
uint32_t floor_log2_32(uint32_t x) {
    int log = 0;
    while (x >>= 1) ++log; // Сдвиг x вправо до тех пор, пока он не станет 0
    return log;
}

// Функция для обращения битов в числе
uint32_t reverse_bits(uint32_t num, uint32_t bit_size) {
    uint32_t reverse_num = 0;
    for (uint32_t i = 0; i < bit_size; i++) {
        if (num & (1 << i)) { // Проверка, установлен ли бит на позиции i
            reverse_num |= 1 << ((bit_size - 1) - i); // Установка соответствующего бита в обратном порядке
        }
    }
    return reverse_num;
}

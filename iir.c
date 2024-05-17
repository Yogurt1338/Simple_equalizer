// #include "iir.h"

// // #define NUM_BANDS 6
// // #define SAMPLING_RATE 22050

// // // Инициализация параметров фильтра
// // void initFilter(BiQuadFilter* f, double fc, double Q) {
// //     double K = tan(M_PI * fc / SAMPLING_RATE);
// //     double norm = 1 / (1 + K / Q + K * K);
// //     f->a0 = K * K * norm;
// //     f->a1 = 2 * f->a0;
// //     f->a2 = f->a0;
// //     f->b1 = 2 * (K * K - 1) * norm;
// //     f->b2 = (1 - K / Q + K * K) * norm;
// //     f->x1 = f->x2 = f->y1 = f->y2 = 0;
// // }

// // // Применение фильтра к входным данным
// // double filterSample(BiQuadFilter* f, double x0) {
// //     double y0 = f->a0 * x0 + f->a1 * f->x1 + f->a2 * f->x2 - f->b1 * f->y1 - f->b2 * f->y2;
// //     f->x2 = f->x1;
// //     f->x1 = x0;
// //     f->y2 = f->y1;
// //     f->y1 = y0;
// //     return y0;
// // }

// // void applyFilters(BiQuadFilter* filters, double* input, double* output, int numSamples) {
// //     for (int i = 0; i < numSamples; ++i) {
// //         output[i] = 0;
// //         for (int j = 0; j < NUM_BANDS; ++j) {
// //             output[i] += filterSample(&filters[j], input[i]);
// //         }
// //     }
// // }

// // void filter(unsigned char *buffer, size_t i) {
// //     // Частоты среза и факторы добротности для каждого фильтра
// //     double centerFreqs[NUM_BANDS] = {100, 200, 400, 800, 1600, 3200};
// //     double Q = 1.0; // Общий фактор добротности для всех фильтров

// //     // Инициализация фильтров
// //     BiQuadFilter filters[NUM_BANDS];
// //     for (int j = 0; j < NUM_BANDS; ++j) {
// //         initFilter(&filters[j], centerFreqs[j], Q);
// //     }

// //     // unsigned char *output = (float*)malloc(i * sizeof(float));
// //     double* output = (double*)malloc(i * sizeof(double));
// //     // Применение фильтров к входным данным и вывод результата
// //     applyFilters(filters, buffer, output, i);

// //     // Вывод результата
// //     printf("Filtered output:\n");
// //     for (int j = 0; j < i; ++j) {
// //         buffer[j] = output[j];
// //     }

// //     free(output);
// // }


// // Инициализация фильтра
// void initFilter(IIRFilter *filter, double *a_coeffs, double *b_coeffs) {
//     for (int i = 0; i <= M; i++) {
//         filter->a[i] = a_coeffs[i];
//         filter->y[i] = 0.0;
//     }
//     for (int i = 0; i <= N; i++) {
//         filter->b[i] = b_coeffs[i];
//         filter->x[i] = 0.0;
//     }
// }

// // Функция фильтрации одного значения
// double filterValue(IIRFilter *filter, double input) {
//     // Сдвигаем значения задержек
//     for (int i = N; i > 0; i--) {
//         filter->x[i] = filter->x[i - 1];
//     }
//     filter->x[0] = input;

//     // Вычисляем выходной сигнал
//     double output = 0.0;
//     for (int i = 0; i <= N; i++) {
//         output += filter->b[i] * filter->x[i];
//     }
//     for (int i = 1; i <= M; i++) {
//         output -= filter->a[i] * filter->y[i];
//     }

//     // Сдвигаем значения выходных задержек
//     for (int i = M; i > 0; i--) {
//         filter->y[i] = filter->y[i - 1];
//     }
//     filter->y[0] = output;

//     return output;
// }

// // Пример использования фильтра
// void filter(unsigned char *buffer, size_t inputLength) {
//     // Коэффициенты передаточной функции
//     double a_coeffs[] = {1,	1, 0}; // Примерные коэффициенты знаменателя
//     double b_coeffs[] = {1, 0.978854486367669, 0}; // Примерные коэффициенты числителя

//     // Инициализируем фильтр
//     IIRFilter filter;
//     initFilter(&filter, a_coeffs, b_coeffs);

//     // Применяем фильтр к входному сигналу и выводим результаты
//     for (int i = 0; i < inputLength; i++) {
//         buffer[i] = filterValue(&filter, buffer[i]);
//         // printf("Output[%d] = %f\n", i, output);
//     }

// }
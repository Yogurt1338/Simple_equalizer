#include <gtk/gtk.h>
#include "buttons.h"
#include "audio.h"

#define DEBUG 2
#define OUTPUT 1

#define CHUNK_SIZE 32768

GtkWidget *window;
GtkWidget *button;
GtkWidget *hbox;
GtkWidget *vbox;
GtkWidget *slider;
GtkWidget *progress_bar;

GtkWidget *vbox_main;

// Структура для хранения имени слайдера и его значения 
typedef struct {
    int value_name;
    int value;
} Slider;
Slider sliders[6];

// Структура для хранения амплитуды и частоты
typedef struct {
    float amplitude;
    float frequency;
} AmplitudeFrequency;

AmplitudeFrequency afArray[32768];

void extractNumber(const char *str, int *num);
Slider* add_slider_value(const char* slider_name, int slider_value);

void w_slider(GtkWidget *widget, gpointer data);
void main_window(void);
void slider_array(void);

void default_value_sliders();

/*
#include <stdio.h>

// Определите размерность фильтра
#define N 2 // Порядок числителя
#define M 2 // Порядок знаменателя

// Структура для хранения состояния фильтра
typedef struct {
double a[M + 1]; // Коэффициенты знаменателя (a[0] = 1.0 обычно)
double b[N + 1]; // Коэффициенты числителя
double x[N + 1]; // Входные задержки
double y[M + 1]; // Выходные задержки
} IIRFilter;

// Инициализация фильтра
void initFilter(IIRFilter *filter, double *a_coeffs, double *b_coeffs) {
for (int i = 0; i <= M; i++) {
filter->a[i] = a_coeffs[i];
filter->y[i] = 0.0;
}
for (int i = 0; i <= N; i++) {
filter->b[i] = b_coeffs[i];
filter->x[i] = 0.0;
}
}

// Функция фильтрации одного значения
double filterValue(IIRFilter *filter, double input) {
// Сдвигаем значения задержек
for (int i = N; i > 0; i--) {
filter->x[i] = filter->x[i - 1];
}
filter->x[0] = input;

// Вычисляем выходной сигнал
double output = 0.0;
for (int i = 0; i <= N; i++) {
output += filter->b[i] * filter->x[i];
}
for (int i = 1; i <= M; i++) {
output -= filter->a[i] * filter->y[i];
}

// Сдвигаем значения выходных задержек
for (int i = M; i > 0; i--) {
filter->y[i] = filter->y[i - 1];
}
filter->y[0] = output;

return output;
}

// Пример использования фильтра
int main() {
// Коэффициенты передаточной функции
double a_coeffs[] = {1.0, -0.2985, 0.9431}; // Примерные коэффициенты знаменателя
double b_coeffs[] = {1.0, 2.0, 1.0}; // Примерные коэффициенты числителя

// Инициализируем фильтр
IIRFilter filter;
initFilter(&filter, a_coeffs, b_coeffs);

// Пример входного сигнала
double inputSignal[] = {1.0, 0.0, 0.0, 0.0, 0.0}; // Дельта-функция
int inputLength = sizeof(inputSignal) / sizeof(inputSignal[0]);

// Применяем фильтр к входному сигналу и выводим результаты
for (int i = 0; i < inputLength; i++) {
double output = filterValue(&filter, inputSignal[i]);
printf("Output[%d] = %f\n", i, output);
}

return 0;
}
*/



/*

*/
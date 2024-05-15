#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "audio.h"
#include "fft.h"
#include "main.h"

int play(const char *file_name) 
{
    g_print("Processing file: %s\n", file_name);
    char filename[256];
    sprintf(filename, "%s", file_name);

    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;


    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){

        // Подготовка буферов для FFT
        float *real = malloc(buffer_size * sizeof(float));
        float *imag = calloc(buffer_size, sizeof(float));

        // Нормализация и преобразование в действительные числа для FFT
        for (size_t i = 0; i < buffer_size; i++) {
            real[i] = (float)(buffer[i] - 128) / 128.0f;
        }

        // Вызов функции FFT
        fftProcessRadix2(real, imag, NN, rate);
        
        // chaaf(real, imag, NN, rate);

        ifftProcessRadix2(real, imag, NN, rate);

        for (size_t i = 0; i < buffer_size; i++) {
            buffer[i] = (uint8_t)((real[i] * 128.0f) + 128);
        }

        // Освобождение памяти
        free(real);
        free(imag);

        ao_play(dev, buffer, done);
    }
        
    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "audio.h"
#include "fft.h"
#include "iir.h"
#include "main.h"

size_t findNearestIndexTo1kHz(float sampleRate, size_t N) {
    return (size_t)(N * 1000 / sampleRate + 0.5); // Округление до ближайшего целого
}

float measureAmplitudeAt1kHz(float *real, float *imag, size_t N, float rate) {
    size_t index = findNearestIndexTo1kHz(rate, N);
    return 2.0 * sqrtf(real[index] * real[index] + imag[index] * imag[index]) / N;
}


int play(const char *file_name) {
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
    buffer = (unsigned char*) malloc(SAMPLE_NODES * sizeof(unsigned char));

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

    // Open an output file for writing
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(sfinfo));
    sfinfo.samplerate = rate;
    sfinfo.channels = channels;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Output file format (WAV)
    SNDFILE *outfile = sf_open("output.wav", SFM_WRITE, &sfinfo);

    /* decode and play */
    
    while ((mpg123_read(mh, buffer, SAMPLE_NODES, &done) == MPG123_OK) && done > 0) {

        // Нормализация и преобразование в действительные числа для FFT
        short *samples = (short*) buffer;
        size_t sample_count = done / sizeof(short);

        
        // Запись значений в CSV файл
        for (size_t i = 0; i < sample_count; i++) {
            x[i].real = samples[i] / 32768.0f;  // Нормализация 16-битных данных
            x[i].imag = 0.0f;
            // printf("%f\n", x[i].real);
        }

        fft_real(x,sample_count);  

        saveToExcel("output.csv", x, sample_count, rate);
    
        chaaf(x, sample_count, rate);

        ifft_real(x,sample_count);  

        for (size_t i = 0; i < sample_count; i++) {
            printf("%f\n", x[i].real);
        }

        #if OUTPUT == 1
            sf_write_raw(outfile, buffer, done);
        #endif

        ao_play(dev, buffer, done);
    }

    // Close the output file
    sf_close(outfile);

    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return 0;
}

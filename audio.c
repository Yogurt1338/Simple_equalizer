#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "audio.h"
#include "fft.h"
#include "iir.h"
#include "main.h"


// int play(const char *file_name) 
// {
//     g_print("Processing file: %s\n", file_name);
//     char filename[256];
//     snprintf(filename, sizeof(filename), "%s", file_name);

//     mpg123_handle *mh;
//     unsigned char *buffer;
//     size_t buffer_size;
//     size_t done;
//     int err;

//     int driver;
//     ao_device *dev;

//     ao_sample_format format;
//     int channels, encoding;
//     long rate;

//     /* initializations */
//     ao_initialize();
//     driver = ao_default_driver_id();
//     mpg123_init();
//     mh = mpg123_new(NULL, &err);
//     buffer_size = mpg123_outblock(mh);
//     buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

//     /* open the file and get the decoding format */
//     if (mpg123_open(mh, filename) != MPG123_OK) {
//         fprintf(stderr, "Unable to open file: %s\n", filename);
//         return -1;
//     }
//     mpg123_getformat(mh, &rate, &channels, &encoding);

//     /* set the output format and open the output device */
//     format.bits = mpg123_encsize(encoding) * BITS;
//     format.rate = rate;
//     format.channels = channels;
//     format.byte_format = AO_FMT_NATIVE;
//     format.matrix = 0;
//     dev = ao_open_live(driver, &format, NULL);
//     if (dev == NULL) {
//         fprintf(stderr, "Error opening device.\n");
//         return -1;
//     }

//     // Open an output file for writing
//     SF_INFO sfinfo;
//     memset(&sfinfo, 0, sizeof(sfinfo));
//     sfinfo.samplerate = rate;
//     sfinfo.channels = channels;
//     sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Output file format (WAV)

//     SNDFILE *outfile = sf_open("output.wav", SFM_WRITE, &sfinfo);
//     if (outfile == NULL) {
//         fprintf(stderr, "Error opening output file.\n");
//         return -1;
//     }

//     /* decode and play */
//     while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){
        
//        // Ensure we have enough data for FFT
//         size_t sample_count = done / sizeof(short);
//         if (sample_count > SAMPLE_NODES) sample_count = SAMPLE_NODES;

//         // Convert buffer to complex numbers
//         for (size_t i = 0; i < sample_count; ++i) {
//             short sample = ((short*)buffer)[i];
//             x[i].real = (float)sample;
//             x[i].imag = 0.0f;
//         }

//         // Perform FFT
//         fft(x, SAMPLE_NODES);
        
//         saveToExcel("output.csv", x, done, rate);
       
//         #if OUTPUT == 1
//             /* Write buffer to the output file */
//             sf_write_raw(outfile, buffer, done);
//         #endif

//         /* Play the buffer */
//         ao_play(dev, (char *)buffer, done);
//     }        

//     // Close the output file
//     sf_close(outfile);

//     /* clean up */
//     free(buffer);
//     ao_close(dev);
//     mpg123_close(mh);
//     mpg123_delete(mh);
//     mpg123_exit();
//     ao_shutdown();
    
//     return 0;
// }


// int play(const char *file_name) 
// {
//     g_print("Processing file: %s\n", file_name);
//     char filename[256];
//     sprintf(filename, "%s", file_name);

//     mpg123_handle *mh;
//     unsigned char *buffer;
//     size_t buffer_size;
//     size_t done;
//     int err;

//     int driver;
//     ao_device *dev;

//     ao_sample_format format;
//     int channels, encoding;
//     long rate;

//     /* initializations */
//     ao_initialize();
//     driver = ao_default_driver_id();
//     mpg123_init();
//     mh = mpg123_new(NULL, &err);
//     // buffer_size = mpg123_outblock(mh);
//     buffer_size = 32768;
//     buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

//     /* open the file and get the decoding format */
//     mpg123_open(mh, filename);
//     mpg123_getformat(mh, &rate, &channels, &encoding);

//     /* set the output format and open the output device */
//     format.bits = mpg123_encsize(encoding) * BITS;
//     format.rate = rate;
//     format.channels = channels;
//     format.byte_format = AO_FMT_NATIVE;
//     format.matrix = 0;
//     dev = ao_open_live(driver, &format, NULL);

//     // Open an output file for writing
//     SF_INFO sfinfo;
//     memset(&sfinfo, 0, sizeof(sfinfo));
//     sfinfo.samplerate = rate;
//     sfinfo.channels = channels;
//     sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Output file format (WAV)

//     SNDFILE *outfile = sf_open("output.wav", SFM_WRITE, &sfinfo);

//     size_t total_done = 0;

//     /* Allocate a temporary buffer for reading new audio data */
//     unsigned char *temp_buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

//     /* decode and play */
//     while (mpg123_read(mh, temp_buffer, buffer_size, &done) == MPG123_OK){
//         /* Allocate memory for the combined buffer */
//         unsigned char *combined_buffer = (unsigned char*)malloc((total_done + done) * sizeof(unsigned char));

//         /* Copy existing data to the combined buffer */
//         memcpy(combined_buffer, buffer, total_done);

//         /* Copy new data to the combined buffer after the existing data */
//         memcpy(combined_buffer + total_done, temp_buffer, done);

//         /* Update the total number of bytes read */
//         total_done += done;

//         /* Free the old buffer */
//         free(buffer);

//         /* Use the combined buffer as the new buffer */
//         buffer = combined_buffer;
//     }

//     // Подготовка буферов для FFT
//     float *real = malloc(total_done * sizeof(float));
//     float *imag = calloc(total_done, sizeof(float));

//     // // Нормализация и преобразование в действительные числа для FFT
//     for (size_t i = 0; i < total_done; i++) {
//         real[i] = (float)(buffer[i] - 128) / 128.0f;
//         // printf("%f\n", (float)buffer[i]);
//     }
    
//     for (long long loop = 0; loop < total_done; loop +=buffer_size){

//         // Вызов функции FFT
//         fftProcessRadix2(real, imag, buffer_size, format.rate);

//         chaaf(real, imag, buffer_size, format.rate);

//         // Allocate a new buffer for IFFT output
//         float *ifft_real = malloc(total_done * sizeof(float));
//         float *ifft_imag = malloc(total_done * sizeof(float));

//         // Вызов функции IFFT
//         ifftProcessRadix2(real, imag, buffer_size, format.rate);

//         // Копирование результатов IFFT в новый буфер
//         memcpy(ifft_real, real, total_done * sizeof(float));
//         memcpy(ifft_imag, imag, total_done * sizeof(float));

//         // from iift to buffer
//         for (size_t i = 0; i < total_done; i++) {
//             buffer[i] = (float)((ifft_real[i] * 128.0f) + 128);
//         }

//         // Освобождение памяти
//         free(real);
//         free(imag);
//         free(ifft_real);
//         free(ifft_imag);
//         // filter(buffer, buffer_size);
            

//         #if OUTPUT == 1
//             /* Write the combined buffer to the output file */
//             sf_write_raw(outfile, buffer, total_done);
//         #endif

//         /* Play the combined buffer */
//         ao_play(dev, buffer, total_done);
        
//         /* Free the temporary buffer */
//         free(temp_buffer);
            
//         // Close the output file
//         sf_close(outfile);

//         /* clean up */
//         free(buffer);
//         ao_close(dev);
//         mpg123_close(mh);
//         mpg123_delete(mh);
//         mpg123_exit();
//         ao_shutdown();

//     }

    
//     return 0;
// }


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
    buffer = (unsigned char*) malloc(CHUNK_SIZE * sizeof(unsigned char));

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
    
    while ((mpg123_read(mh, buffer, CHUNK_SIZE, &done) == MPG123_OK) && done > 0) {
        // Подготовка буферов для FFT
        // float *real = malloc(done * sizeof(float));
        // float *imag = calloc(done, sizeof(float));
        // printf("%d\n", done);
        // Нормализация и преобразование в действительные числа для FFT
        // амплитуда каждого сэмпла находится в диапазоне от -1 до 1
        // for (size_t i = 0; i < done; i++) {
        //     // x[i].real = (float)(buffer[i] - 128) / 128.0f;
        // }

        // // Находим максимальное абсолютное значение в сигнале
        // float max_abs_value = 0.0f;
        // for (size_t i = 0; i < done; i++) {
        //     float abs_value = fabsf((float)buffer[i] - 128);
        //     if (abs_value > max_abs_value) {
        //         max_abs_value = abs_value;
        //     }
        // }

        // // Нормализуем сигнал и преобразуем в действительные числа для FFT
        // for (size_t i = 0; i < done; i++) {
        //     x[i].real = ((float)buffer[i] - 128) / max_abs_value;
        //     x[i].imag = 0.0f; // Инициализация мнимой части нулем
        // }

        // // Переводим обратно в буфер
        // for (size_t i = 0; i < done; i++) {
        //     buffer[i] = x[i].real * max_abs_value;
        // }


        // Вызов функции FFT
        // fftProcessRadix2(real, imag, done, rate);

        /* TEST FFT with REAL INPUTS */
        
        // for (size_t i = 0; i < done; i++) {
        //     x[i].real = real[i];
        //     x[i].imag = imag[i];
        // }

        // saveToExcel("output_do.csv", x, done, rate);

        // fft_real(x,done);  

        // saveToExcel("output.csv", x, done, rate);
    
        // chaaf(x, done, rate);

        // saveToExcel("output1.csv", x, done, rate);

        // ifft_real(x,done);  

        // saveToExcel("output_pos.csv", x, done, rate);

        // for (size_t i = 0; i < done; i++) {
        //     real[i] = x[i].real;
        //     imag[i] = x[i].imag;
        // }

        // for (int i = 0; i<done; i++) {
        //     printf("%.5f %.5f\n", x[i].real, x[i].imag);
        // }

        // int a = 1000;
        // // // printf("%f\n", real[100]);
        
        // float amplitude = 2.0 * sqrtf(real[a] * real[a] + imag[a] * imag[a]) / CHUNK_SIZE ;
        // float freq = (size_t)(N * 1000 / rate + 0.5);
        // printf("Befor freq: %.5f, value: %.5f \n", freq, amplitude);


            // Измерение амплитуды на частоте 1 кГц до применения chaaf
    // float amplitude_before = measureAmplitudeAt1kHz(real, imag, done, rate);
    // printf("Before chaaf: %.5f\n", amplitude_before);
        
        // chaaf(real, imag, done, rate);

        // amplitude = 2.0 * sqrtf(real[a] * real[a] + imag[a] * imag[a]) / CHUNK_SIZE ;
        // freq = (size_t)(N * 1000 / rate + 0.5);
        // printf("After freq: %.5f, value: %.5f \n", freq, amplitude);

   // Измерение амплитуды на частоте 1 кГц после применения chaaf
    // float amplitude_after = measureAmplitudeAt1kHz(real, imag, done, rate);
    // printf("After chaaf: %.5f\n", amplitude_after);
    
        // // Вызов функции IFFT
        // ifftProcessRadix2(real, imag, done, rate);




        // // Нормализуем сигнал
        // for (size_t i = 0; i < done; i++) {
        //     x[i].real = buffer[i] / max_abs_value;
        // }

        // // Переводим обратно в буфер
        // for (size_t i = 0; i < done; i++) {
        //     buffer[i] = x[i].real * max_abs_value;
        // }
        
        // Освобождение памяти
        // free(real);
        // free(imag);
        // // filter(buffer, done);

        #if OUTPUT == 1
            // Write the buffer to the output file
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

// gcc main.c -o main `pkg-config gtk+-2.0 --cflags pkg-config gtk+-2.0 --libs`

/*
Разработать программное обеспечение с графическим пользовательским интерфейсом на любом языке программирования. 
Входные тестовые данные для каждого варианта ДЗ должны загружаться из текстового, 
либо звукового файла (в зависимости от условия задания). 
Генерирование входных тестовых файлов допускается осуществлять с помощью скриптов Matlab. 
Использование библиотечных функций для реализации алгоритмов обработки 
сигналов не допускается (если в задании не указано иное).
*/

/*
Разработать шестиканальный цифровой эквалайзер звукового сигнала. 
Должна быть возможность регулировки параметров ослабления или усиления каждого из каналов. 
Ширина полосы пропускания всех каналов должна быть одинаковой. 
Для чтения и записи данных аудиофайлов допускается использовать сторонние библиотеки. 
Обработка звука в реальном времени и его воспроизведение не требуются. 
Для демонстрации работы эквалайзера допускается использовать готовую библиотеку БПФ.
*/

#include <gtk/gtk.h>
#include "buttons.h"
#include "audio.h"

GtkWidget *window;
GtkWidget *button;
GtkWidget *hbox;
GtkWidget *vbox;
GtkWidget *slider;
GtkWidget *progress_bar;

GtkWidget *vbox_main;



// Function to handle slider value change event
void w_slider(GtkWidget *widget, gpointer data) {
    gint value = gtk_range_get_value(GTK_RANGE(widget));
    gchar *slider_name = g_object_get_data(G_OBJECT(widget), "name");
    g_print("%s slider value: %d\n", slider_name, value);
}

// Function to update the progress bar
gboolean update_progress(GtkProgressBar *progress_bar) {
    double progress = gtk_progress_bar_get_fraction(progress_bar);

    // Update the progress by a small increment
    progress += 0.1;

    // If the progress reaches 100%, reset it to 0%
    if (progress >= 1.0) {
        progress = 0.0;
    }

    gtk_progress_bar_set_fraction(progress_bar, progress);

    return TRUE;
}

// Window
void main_window(void)
{
    window =  gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Эквалайзер");
    gtk_window_set_default_size (GTK_WINDOW (window), 1100, 700);
    gtk_widget_show(window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void slider_array(void)
{
    const gchar *slider_names[] = {"Slider 1", "Slider 2", "Slider 3", "Slider 4", "Slider 5", "Slider 6"};

    for (int i = 0; i < 6; i++) {
        
        vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

        // Create a label to display the slider value
        gchar *label_text = g_strdup_printf("Slider %d:", i+1);
        GtkWidget *label = gtk_label_new(label_text);
        printf("%s",label_text );
        g_free(label_text);
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

        // Create a slider
        slider = gtk_vscale_new_with_range(-50, 50, 1);
        gtk_range_set_inverted(slider, TRUE);
        gtk_range_set_value(slider, 0);
        gtk_box_pack_start(GTK_BOX(vbox), slider, TRUE, TRUE, 0);

        // Connect the slider's "value-changed" signal to the callback function
        g_signal_connect(slider, "value-changed", G_CALLBACK(w_slider), label);
    }
}

void bar()
{
    progress_bar = gtk_progress_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox_main), progress_bar, FALSE, FALSE, 0);
}

int main(int argc, char **argv) {

    gtk_init(&argc, &argv);
    main_window();
    
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 50);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // Feature - bar
    // vbox_main = gtk_vbox_new(FALSE, 5);
    // gtk_box_pack_start(GTK_BOX(hbox), vbox_main, TRUE, TRUE, 0);
    // bar();

    slider_array();

    button_array(hbox);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

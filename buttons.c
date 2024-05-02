#include "buttons.h"
#include "audio.h"

GtkWidget *b_load;
GtkWidget *b_play;
GtkWidget *b_pause;
GtkWidget *b_stop;

// Load
void load_button(GtkWidget *widget, gpointer data) {
    g_print("Load!\n");
}

// Play
void play_button(GtkWidget *widget, gpointer data) {
    g_print("Play!\n");
    play();
}

// Pause
void pause_button(GtkWidget *widget, gpointer data) {
    g_print("Pause!\n");
}

// Stop
void stop_button(GtkWidget *widget, gpointer data) {
    g_print("Stop!\n");
}

void button_array(GtkWidget *hbox){

    GtkWidget *right_section = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), right_section, FALSE, FALSE, 0);

    b_load = gtk_button_new_with_label("Load");
    g_signal_connect(b_load, "clicked", G_CALLBACK(load_button), NULL);
    gtk_box_pack_start(GTK_BOX(right_section), b_load, TRUE, TRUE, 0);

    b_play = gtk_button_new_with_label("Play");
    g_signal_connect(b_play, "clicked", G_CALLBACK(play_button), NULL);
    gtk_box_pack_start(GTK_BOX(right_section), b_play, TRUE, TRUE, 0);

    b_pause = gtk_button_new_with_label("Pause");
    g_signal_connect(b_pause, "clicked", G_CALLBACK(pause_button), NULL);
    gtk_box_pack_start(GTK_BOX(right_section), b_pause, TRUE, TRUE, 0);

    b_stop = gtk_button_new_with_label("Stop");
    g_signal_connect(b_stop, "clicked", G_CALLBACK(stop_button), NULL);
    gtk_box_pack_start(GTK_BOX(right_section), b_stop, TRUE, TRUE, 0);
}
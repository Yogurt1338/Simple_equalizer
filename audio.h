#ifndef AUDIO_H
#define AUDIO_H

#include <gtk/gtk.h>
#include <mpg123.h>
#include <ao/ao.h>

#define BITS 8

int play(const char *file_name);

#endif /* AUDIO_H */
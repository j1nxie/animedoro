#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    double minutes;
    double seconds;
    int pomodoros;
    bool running;
} AppState;

AppState initialize_app(int minutes, int seconds, int pomodoros, bool running);

#endif

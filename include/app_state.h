#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    double minutes;
    double seconds;
    int pomodoros;
} AppState;

AppState initialize_app(int minutes, int seconds, int pomodoros);

#endif

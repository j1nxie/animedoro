#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef enum { POMODORO, SHORT_BREAK, LONG_BREAK } PomodoroState;

typedef struct {
    double minutes;
    double seconds;
    int pomodoros;
    bool running;
    PomodoroState state;
} AppState;

AppState initialize_app(int minutes, int seconds, int pomodoros, bool running,
                        PomodoroState state);

#endif

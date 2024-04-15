#ifndef APP_STATE_H
#define APP_STATE_H

#include <stdbool.h>

typedef enum {
    POMODORO_CLOCK,
    POMODORO_SHORT_BREAK,
    POMODORO_LONG_BREAK
} PomodoroState;

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

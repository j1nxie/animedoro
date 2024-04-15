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

typedef struct {
    double pomodoro_length;
    double short_break_length;
    double long_break_length;
} AppConfig;

AppState initialize_app(AppConfig *app_config);

#endif

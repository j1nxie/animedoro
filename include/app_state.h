#ifndef APP_STATE_H_
#define APP_STATE_H_

#include <stdbool.h>

typedef enum {
    POMODORO_CLOCK,
    POMODORO_SHORT_BREAK,
    POMODORO_LONG_BREAK
} PomodoroState;

typedef enum { CLOCK_SCREEN, SETTINGS_SCREEN } AppScreen;

typedef struct {
        double minutes;
        double seconds;
        int pomodoros;
        bool running;
        PomodoroState pomodoro_state;
        AppScreen current_screen;
} AppState;

typedef struct {
        double pomodoro_length;
        double short_break_length;
        double long_break_length;
} AppConfig;

AppState initialize_app(AppConfig *app_config);

#endif

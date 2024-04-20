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
        int pomodoro_length;
        int short_break_length;
        int long_break_length;
        bool auto_start_timer;
} AppConfig;

AppState initialize_app(AppConfig *app_config);

#endif

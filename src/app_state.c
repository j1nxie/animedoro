#include "../include/app_state.h"

AppState initialize_app(AppConfig *app_config) {
    return (AppState){
        app_config->pomodoro_length, 0, 3, false, POMODORO_CLOCK, CLOCK_SCREEN};
}

AppConfig app_config = (AppConfig){45, 5, 15, false};
AppState app_state = (AppState){25, 0, 3, false, POMODORO_CLOCK, CLOCK_SCREEN};

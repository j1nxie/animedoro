#include "../include/app_state.h"

AppState initialize_app(AppConfig *app_config) {
    return (AppState){
        app_config->pomodoro_length, 0, 3, false, POMODORO_CLOCK, CLOCK_SCREEN};
}

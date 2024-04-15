#include "../include/app_state.h"

AppState initialize_app(AppConfig *app_config) {
    return (AppState){app_config->pomodoro_length, 0, 4, false, POMODORO_CLOCK};
}

#include "../include/app_state.h"

AppState initialize_app(int minutes, int seconds, int pomodoros) {
    return (AppState){minutes, seconds, pomodoros};
}
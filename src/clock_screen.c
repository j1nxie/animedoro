#include "../include/app_state.h"
#include <raylib.h>

void ClockScreen(AppState *app_state, AppConfig *app_config) {
    const char *minutes = TextFormat((app_state->minutes < 10 ? "0%d" : "%d"),
                                     (int)app_state->minutes);

    const char *seconds = TextFormat((app_state->seconds < 10 ? "0%d" : "%d"),
                                     (int)app_state->seconds);

    const char *string = TextFormat("%s:%s", minutes, seconds);
    const char *status;
    Vector2 size = MeasureTextEx(GetFontDefault(), "00:00", 40, 40 / 10);
    Vector2 text_pos = (Vector2){GetScreenWidth() / 2 - size.x / 2,
                                 GetScreenHeight() / 2 - size.y / 2};

    if (app_state->running) {
        status = "pause";
        app_state->seconds -= GetFrameTime();
        if (app_state->seconds <= 0) {
            app_state->seconds = 60;
            app_state->minutes--;
        }

        if (app_state->minutes == 0) {
            switch (app_state->state) {
            case (POMODORO_CLOCK):
                app_state->minutes = app_config->pomodoro_length;
                break;
            case (POMODORO_SHORT_BREAK):
                app_state->minutes = app_config->short_break_length;
                break;
            case (POMODORO_LONG_BREAK):
                app_state->minutes = app_config->long_break_length;
                break;
            }
            app_state->running = false;
        }

        SetWindowTitle(
            TextFormat("clock running :3 - time remaining: %s", string));
    } else {
        status = "start";
        SetWindowTitle(
            TextFormat("clock paused >:c - time remaining: %s", string));
    }

    // FIXME: placeholder for proper buttons
    Vector2 status_size = MeasureTextEx(GetFontDefault(), status, 40, 40 / 10);
    Vector2 status_text_pos =
        (Vector2){GetScreenWidth() / 2 - status_size.x / 2,
                  GetScreenHeight() / 2 - status_size.y / 2};

    DrawText(string, (int)text_pos.x, (int)text_pos.y, 40, BLUE);
    DrawText(status, (int)status_text_pos.x, (int)status_text_pos.y + 80, 40,
             BLUE);
}

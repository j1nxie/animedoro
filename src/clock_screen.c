#include "../include/app_state.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>

void ClockScreen(AppState *app_state) {
    app_state->seconds -= GetFrameTime();
    if (app_state->seconds <= 0) {
        app_state->seconds = 60;
        app_state->minutes--;
    }

    const char *minutes = TextFormat((app_state->minutes < 10 ? "0%d" : "%d"),
                                     (int)app_state->minutes);

    const char *seconds = TextFormat((app_state->seconds < 10 ? "0%d" : "%d"),
                                     (int)app_state->seconds);

    const char *string = TextFormat("%s:%s", minutes, seconds);
    Vector2 size = MeasureTextEx(GetFontDefault(), "00:00", 40, 40 / 10);
    Vector2 text_pos = (Vector2){GetScreenWidth() / 2 - size.x / 2,
                                 GetScreenHeight() / 2 - size.y / 2};
    DrawText(string, (int)text_pos.x, (int)text_pos.y, 40, BLUE);
}
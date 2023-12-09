#include "../include/config.h"
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
    const char *minutes, *seconds;
    if (app_state->minutes < 10) {
        minutes = TextFormat("0%d", (int)app_state->minutes);
    } else {
        minutes = TextFormat("%d", (int)app_state->minutes);
    }

    if (app_state->seconds < 10) {
        seconds = TextFormat("0%d", (int)app_state->seconds);
    } else {
        seconds = TextFormat("%d", (int)app_state->seconds);
    }

    const char *string = TextFormat("%s:%s", minutes, seconds);
    Vector2 size = MeasureTextEx(GetFontDefault(), string, 20, 20 / 10);
    Vector2 text_pos = (Vector2){GetScreenWidth() / 2 - size.x / 2,
                                 GetScreenHeight() / 2 - size.y / 2};
    DrawText(string, (int)text_pos.x, (int)text_pos.y, 40, BLUE);
}
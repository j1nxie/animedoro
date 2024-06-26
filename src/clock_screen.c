#include "../deps/raygui.h"
#include "../include/app_state.h"
#include <raylib.h>

void NextState(AppState *app_state, AppConfig *app_config) {
    switch (app_state->pomodoro_state) {
        case (POMODORO_CLOCK):
            if (app_state->pomodoros > 0) {
                app_state->pomodoros--;
                app_state->pomodoro_state = POMODORO_SHORT_BREAK;
                app_state->minutes = app_config->short_break_length;
            } else {
                app_state->pomodoros = 3;
                app_state->pomodoro_state = POMODORO_LONG_BREAK;
                app_state->minutes = app_config->long_break_length;
            }
            break;
        case (POMODORO_SHORT_BREAK):
        case (POMODORO_LONG_BREAK):
            app_state->pomodoro_state = POMODORO_CLOCK;
            app_state->minutes = app_config->pomodoro_length;
            break;
    }
    app_state->seconds = 0.0f;
}

// FIXME: the string for the current time is allocated twice, once here and once
// in ClockScreen(). would be really nice if the string is deduplicated somehow.
void TickClock(AppState *app_state, AppConfig *app_config) {
    const char *string = TextFormat("%02i:%02i", (int)app_state->minutes,
                                    (int)app_state->seconds);

    if (app_state->running) {
        app_state->seconds -= GetFrameTime();
        if (app_state->seconds <= 0.0f) {
            app_state->seconds = 60;
            if (app_state->minutes > 0) {
                app_state->minutes--;
            } else if (app_state->minutes == 0) {
                NextState(app_state, app_config);
                app_state->running = app_config->auto_start_timer;
            }
        }

        if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - 32.0f,
                                  GetScreenHeight() / 2.0f + 45.0f - 16.0f, 32,
                                  32},
                      GuiIconText(ICON_PLAYER_PAUSE, ""))) {
            app_state->running = !app_state->running;
        }

        switch (app_state->pomodoro_state) {
            case (POMODORO_CLOCK):
                SetWindowTitle(TextFormat("%s - clock running :3", string));
                break;
            case (POMODORO_SHORT_BREAK):
            case (POMODORO_LONG_BREAK):
                SetWindowTitle(TextFormat("%s - break time!!", string));
                break;
        }
    } else {
        if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - 32.0f,
                                  GetScreenHeight() / 2.0f + 45.0f - 16.0f, 32,
                                  32},
                      GuiIconText(ICON_PLAYER_PLAY, ""))) {
            app_state->running = !app_state->running;
        }

        switch (app_state->pomodoro_state) {
            case (POMODORO_CLOCK):
                SetWindowTitle(TextFormat("%s - clock paused >:c", string));
                break;
            case (POMODORO_SHORT_BREAK):
            case (POMODORO_LONG_BREAK):
                SetWindowTitle(TextFormat("%s - break paused...?", string));
                break;
        }
    }
}

void ClockScreen(AppState *app_state, AppConfig *app_config) {
    // drawing a progress bar-esque background
    float time = app_state->minutes * 60 + app_state->seconds;
    switch (app_state->pomodoro_state) {
        case (POMODORO_CLOCK):
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          CLITERAL(Color){246, 126, 125, 255});
            DrawRectangle(
                0, 0,
                GetScreenWidth() *
                    (1.0f - (time / (app_config->pomodoro_length * 60))),
                GetScreenHeight(), CLITERAL(Color){179, 255, 179, 255});
            break;
        case (POMODORO_SHORT_BREAK):
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          CLITERAL(Color){139, 209, 139, 255});
            DrawRectangle(
                0, 0,
                GetScreenWidth() *
                    (1.0f - (time / (app_config->short_break_length * 60))),
                GetScreenHeight(), CLITERAL(Color){246, 126, 125, 255});
            break;
        case (POMODORO_LONG_BREAK):
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          CLITERAL(Color){139, 209, 139, 255});
            DrawRectangle(
                0, 0,
                GetScreenWidth() *
                    (1.0f - (time / (app_config->long_break_length * 60))),
                GetScreenHeight(), CLITERAL(Color){246, 126, 125, 255});
            break;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        app_state->running = !app_state->running;
    }

    TickClock(app_state, app_config);

    const char *string = TextFormat("%02i:%02i", (int)app_state->minutes,
                                    (int)app_state->seconds);
    Vector2 size = MeasureTextEx(GetFontDefault(), string, 40, 40.0f / 10.0f);
    Vector2 text_pos =
        (Vector2){GetScreenWidth() / 2.0f - size.x / 2.0f,
                  GetScreenHeight() / 2.0f - size.y / 2.0f - 16.0f};

    DrawText(string, (int)text_pos.x, (int)text_pos.y, 40, WHITE);

    // settings button
    if (GuiButton((Rectangle){GetScreenWidth() - 32.0f, 0, 32, 32},
                  GuiIconText(ICON_GEAR, ""))) {
        app_state->current_screen = SETTINGS_SCREEN;
    }

    // skip button
    if (GuiButton((Rectangle){GetScreenWidth() / 2.0f,
                              GetScreenHeight() / 2.0f + 45.0f - 16.0f, 32, 32},
                  GuiIconText(ICON_PLAYER_NEXT, ""))) {
        NextState(app_state, app_config);
        app_state->running = app_config->auto_start_timer;
    }
}

#include "../deps/raygui.h"
#include "../include/app_state.h"
#include <raylib.h>

void NextState(AppState *app_state, AppConfig *app_config) {
    switch (app_state->state) {
    case (POMODORO_CLOCK):
        if (app_state->pomodoros > 0) {
            app_state->pomodoros--;
            app_state->state = POMODORO_SHORT_BREAK;
            app_state->minutes = app_config->short_break_length;
        } else {
            app_state->pomodoros = 3;
            app_state->state = POMODORO_LONG_BREAK;
            app_state->minutes = app_config->long_break_length;
        }
        break;
    case (POMODORO_SHORT_BREAK):
    case (POMODORO_LONG_BREAK):
        app_state->state = POMODORO_CLOCK;
        app_state->minutes = app_config->pomodoro_length;
        break;
    }
    app_state->seconds = 0.0f;
}

void ClockScreen(AppState *app_state, AppConfig *app_config) {
    float time = app_state->minutes * 60 + app_state->seconds;
    switch (app_state->state) {
    case (POMODORO_CLOCK):
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      CLITERAL(Color){246, 126, 125, 255});
        DrawRectangle(0, 0,
                      GetScreenWidth() *
                          (1.0f - (time / (app_config->pomodoro_length * 60))),
                      GetScreenHeight(), CLITERAL(Color){179, 255, 179, 255});
        break;
    case (POMODORO_SHORT_BREAK):
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      CLITERAL(Color){179, 255, 179, 255});
        DrawRectangle(
            0, 0,
            GetScreenWidth() *
                (1.0f - (time / (app_config->short_break_length * 60))),
            GetScreenHeight(), CLITERAL(Color){246, 126, 125, 255});
        break;
    case (POMODORO_LONG_BREAK):
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      CLITERAL(Color){179, 255, 179, 255});
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

    const char *minutes = TextFormat((app_state->minutes < 10 ? "0%d" : "%d"),
                                     (int)app_state->minutes);

    const char *seconds = TextFormat((app_state->seconds < 10 ? "0%d" : "%d"),
                                     (int)app_state->seconds);

    const char *string = TextFormat("%s:%s", minutes, seconds);
    const char *status;
    Vector2 size = MeasureTextEx(GetFontDefault(), string, 40, 40.0f / 10.0f);
    Vector2 text_pos = (Vector2){GetScreenWidth() / 2.0f - size.x / 2.0f,
                                 GetScreenHeight() / 2.0f - size.y / 2.0f};

    if (app_state->running) {
        app_state->seconds -= GetFrameTime();
        if (app_state->seconds <= 0.0f) {
            app_state->seconds = 60;
            if (app_state->minutes > 0) {
                app_state->minutes--;
            } else if (app_state->minutes == 0) {
                NextState(app_state, app_config);
                app_state->running = false;
            }
        }

        if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - 32.0f,
                                  GetScreenHeight() / 2.0f + 45.0f, 32, 32},
                      GuiIconText(ICON_PLAYER_PAUSE, ""))) {
            app_state->running = !app_state->running;
        }

        SetWindowTitle(
            TextFormat("clock running :3 - time remaining: %s", string));
    } else {
        if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - 32.0f,
                                  GetScreenHeight() / 2.0f + 45.0f, 32, 32},
                      GuiIconText(ICON_PLAYER_PLAY, ""))) {
            app_state->running = !app_state->running;
        }

        SetWindowTitle(
            TextFormat("clock paused >:c - time remaining: %s", string));
    }

    DrawText(string, (int)text_pos.x, (int)text_pos.y, 40, BLUE);
    if (GuiButton((Rectangle){GetScreenWidth() / 2.0f,
                              GetScreenHeight() / 2.0f + 45.0f, 32, 32},
                  GuiIconText(ICON_PLAYER_NEXT, ""))) {
        NextState(app_state, app_config);
        app_state->running = false;
    }
}

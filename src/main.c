#include "../deps/raygui.h"
#include "../include/app_state.h"
#include "../include/clock_screen.h"
#include "../include/settings_screen.h"
#include <raylib.h>

int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 225;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "animedoro - v0.1.0");
    GuiEnable();
    SetWindowMinSize(200, 150);

    SetTargetFPS(60);

    app_state.minutes = app_config.pomodoro_length;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (app_state.current_screen) {
            case (CLOCK_SCREEN):
                ClockScreen(&app_state, &app_config);
                break;
            case (SETTINGS_SCREEN):
                TickClock(&app_state, &app_config);
                SettingsScreen(&app_state, &app_config);
                break;
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

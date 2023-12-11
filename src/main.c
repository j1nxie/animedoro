#include "../deps/raygui.h"
#include "../include/app_state.h"
#include "../include/clock_screen.h"
#include <raylib.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "animedoro - v0.1.0");

    SetTargetFPS(60);

    AppState app_state = initialize_app(25, 0, 4);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        ClockScreen(&app_state);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
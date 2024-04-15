#include "../deps/raygui.h"
#include "../include/app_state.h"
#include "../include/clock_screen.h"
#include <raylib.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "animedoro - v0.1.0");

    SetTargetFPS(60);

    AppConfig app_config = (AppConfig){25, 5, 15};
    AppState app_state = initialize_app(&app_config);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            app_state.running = !app_state.running;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        ClockScreen(&app_state, &app_config);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

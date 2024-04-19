#include "../deps/raygui.h"
#include "../include/app_state.h"
#include <raylib.h>

void SettingsScreen(AppState *app_state, AppConfig *app_config) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);
    if (GuiButton((Rectangle){GetScreenWidth() - 32.0f, 0, 32, 32},
                  GuiIconText(ICON_CROSS, ""))) {
        app_state->current_screen = CLOCK_SCREEN;
    }
}

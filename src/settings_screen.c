#include "../deps/raygui.h"
#include "../include/app_state.h"
#include <raylib.h>
#include <stdint.h>

const int LINE_PADDING = 8;

// i am truly sorry to all who dislikes global states.
bool pomodoro_edit = false;
int *pomodoro_edit_value = &app_config.pomodoro_length;

bool short_break_edit = false;
int *short_break_edit_value = &app_config.short_break_length;

bool long_break_edit = false;
int *long_break_edit_value = &app_config.long_break_length;

void SettingsScreen(AppState *app_state, AppConfig *app_config) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);
    if (GuiButton((Rectangle){GetScreenWidth() - 32.0f, 0, 32, 32},
                  GuiIconText(ICON_CROSS, ""))) {
        app_state->current_screen = CLOCK_SCREEN;
    }

    GuiSetStyle(VALUEBOX, TEXT_PADDING, 4);
    GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (GuiValueBox((Rectangle){32, 32, 32, 32}, "pomodoro length",
                    pomodoro_edit_value, 1, INT32_MAX, pomodoro_edit)) {
        app_config->pomodoro_length = *pomodoro_edit_value;
        pomodoro_edit = !pomodoro_edit;
    }

    if (GuiValueBox((Rectangle){32, 32 * 2 + LINE_PADDING, 32, 32},
                    "short break length", short_break_edit_value, 1, INT32_MAX,
                    short_break_edit)) {
        app_config->short_break_length = *short_break_edit_value;
        short_break_edit = !short_break_edit;
    }

    if (GuiValueBox((Rectangle){32, 32 * 3 + 2 * LINE_PADDING, 32, 32},
                    "long break length", long_break_edit_value, 1, INT32_MAX,
                    long_break_edit)) {
        app_config->long_break_length = *long_break_edit_value;
        long_break_edit = !long_break_edit;
    }

    GuiCheckBox((Rectangle){32, 32 * 4 + 3 * LINE_PADDING, 32, 32},
                "automatically start timer", &app_config->auto_start_timer);
}

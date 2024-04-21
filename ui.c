#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"

Color *ui_selection_color;

Rectangle ui_picker_bounds;

static unsigned char _consumed_buttons;

void init_ui(void)
{
	ui_picker_bounds = (Rectangle) {
	0, 0, 256, 256};
}

void ui_handle_input(void)
{
	if (IsKeyPressed(KEY_SPACE))
		TraceLog(LOG_DEBUG, TextFormat("%b", _consumed_buttons));

	for (MouseButton button = MOUSE_BUTTON_LEFT;
	     button <= MOUSE_BUTTON_BACK; button++) {
		if (IsMouseButtonPressed(button)) {
			if (CheckCollisionPointRec
			    (GetMousePosition(), ui_picker_bounds))
				_consumed_buttons |= 1 << button;
		}
		if (IsMouseButtonReleased(button))
			_consumed_buttons &= ~(1 << button);;
	}
}

void ui_render(void)
{
	GuiColorPicker(ui_picker_bounds, "Color Picker", ui_selection_color);
}

bool ui_button_available(MouseButton button)
{
	return !((_consumed_buttons >> button) & 1);
}

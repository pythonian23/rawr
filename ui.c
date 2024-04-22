#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"

Color *ui_selection_color;

Rectangle ui_picker_bounds;
Rectangle ui_button_pen_bounds;
Rectangle ui_button_fill_bounds;
Rectangle ui_button_eraser_bounds;

static unsigned char _consumed_buttons;

void init_ui(void)
{
	ui_picker_bounds = (Rectangle) {
	0, 0, 256, 256};
	ui_button_pen_bounds = (Rectangle) {
	0, 256, 64, 64};
	ui_button_fill_bounds = (Rectangle) {
	64, 256, 64, 64};
	ui_button_eraser_bounds = (Rectangle) {
	128, 256, 64, 64};
}

bool _ui_bound_check(Vector2 coord)
{
	return CheckCollisionPointRec(coord, ui_picker_bounds)
	    || CheckCollisionPointRec(coord, ui_button_pen_bounds)
	    || CheckCollisionPointRec(coord, ui_button_fill_bounds)
	    || CheckCollisionPointRec(coord, ui_button_eraser_bounds);
}

void ui_handle_input(void)
{
	if (IsKeyPressed(KEY_SPACE))
		TraceLog(LOG_DEBUG, TextFormat("%b", _consumed_buttons));

	for (MouseButton button = MOUSE_BUTTON_LEFT;
	     button <= MOUSE_BUTTON_BACK; button++) {
		if (IsMouseButtonPressed(button))
			if (_ui_bound_check(GetMousePosition()))
				_consumed_buttons |= 1 << button;
		if (IsMouseButtonReleased(button))
			_consumed_buttons &= ~(1 << button);
	}
}

void ui_render(void)
{
	GuiColorPicker(ui_picker_bounds, "Color Picker", ui_selection_color);

	GuiButton(ui_button_pen_bounds, GuiIconText(ICON_PENCIL_BIG, ""));
	GuiButton(ui_button_fill_bounds, GuiIconText(ICON_COLOR_BUCKET, ""));
	GuiButton(ui_button_eraser_bounds, GuiIconText(ICON_RUBBER, ""));
}

bool ui_button_available(MouseButton button)
{
	return !((_consumed_buttons >> button) & 1);
}

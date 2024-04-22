#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"

Color *ui_selection_color;

static Rectangle _bnd_picker;
static Rectangle _bnd_bttn_pen;
static Rectangle _bnd_bttn_fill;
static Rectangle _bnd_bttn_eraser;

static unsigned char _consumed_buttons;

void init_ui(void)
{
	_bnd_picker = (Rectangle) {
	0 + 4, 0 + 4, 256 - 4, 256 - 4};
	_bnd_bttn_pen = (Rectangle) {
	0 + 4, 256 + 4, 128 - 4, 128 - 4};
	_bnd_bttn_fill = (Rectangle) {
	128 + 4, 256 + 4, 128 - 4, 128 - 4};
	_bnd_bttn_eraser = (Rectangle) {
	0 + 4, 384 + 4, 128 - 4, 128 - 4};
}

bool _ui_bound_check(Vector2 coord)
{
	return CheckCollisionPointRec(coord, _bnd_picker)
	    || CheckCollisionPointRec(coord, _bnd_bttn_pen)
	    || CheckCollisionPointRec(coord, _bnd_bttn_fill)
	    || CheckCollisionPointRec(coord, _bnd_bttn_eraser);
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
	GuiColorPicker(_bnd_picker, "Color Picker", ui_selection_color);

	GuiButton(_bnd_bttn_pen, GuiIconText(ICON_PENCIL_BIG, ""));
	GuiButton(_bnd_bttn_fill, GuiIconText(ICON_COLOR_BUCKET, ""));
	GuiButton(_bnd_bttn_eraser, GuiIconText(ICON_RUBBER, ""));
}

bool ui_button_available(MouseButton button)
{
	return !((_consumed_buttons >> button) & 1);
}

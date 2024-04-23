#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"
#include "gui.h"

EditMode ui_edit_mode;
Color *ui_selection_color;

static Rectangle _bnd_picker;

static grid_t _grid;
static button_t _bttn_pen;
static button_t _bttn_fill;
static button_t _bttn_eraser;

static unsigned char _consumed_buttons;

void init_ui(void)
{
	gui_theme_back = LIGHTGRAY;
	gui_theme_fore = DARKGRAY;

	ui_edit_mode = MODE_DRAW;

	_bnd_picker = (Rectangle) {
	0 + 4, 0 + 4, 256 - 4, 256 - 4};
	_grid = (grid_t) {
		(Vector2) {
	0, 256}, 128, 128, 4};
	_bttn_pen = (button_t) {
		&_grid, (Rectangle) {
	0, 0, 1, 1}, LoadTextureFromImage(LoadImage("res/pen.png"))};
	_bttn_fill = (button_t) {
		&_grid, (Rectangle) {
	1, 0, 1, 1}, LoadTextureFromImage(LoadImage("res/fill.png"))};
	_bttn_eraser = (button_t) {
		&_grid, (Rectangle) {
	0, 1, 1, 1}, LoadTextureFromImage(LoadImage("res/eraser.png"))};
}

void ui_handle_input(void)
{
	if (IsKeyPressed(KEY_SPACE))
		TraceLog(LOG_DEBUG, TextFormat("%b", _consumed_buttons));

	Vector2 cursor = GetMousePosition();
	for (MouseButton button = MOUSE_BUTTON_LEFT;
	     button <= MOUSE_BUTTON_BACK; button++) {
		if (IsMouseButtonPressed(button)) {
			if (CheckCollisionPointRec(cursor, _bnd_picker)) ;
			else if (gui_button_inside(&_bttn_pen, cursor))
				ui_edit_mode = MODE_DRAW;
			else if (gui_button_inside(&_bttn_fill, cursor))
				ui_edit_mode = MODE_FILL;
			else if (gui_button_inside(&_bttn_eraser, cursor))
				ui_edit_mode = MODE_ERASE;
			else
				continue;
			_consumed_buttons |= 1 << button;
		}
		if (IsMouseButtonReleased(button))
			_consumed_buttons &= ~(1 << button);
	}
}

void ui_render(void)
{
	GuiColorPicker(_bnd_picker, "Color Picker", ui_selection_color);

	gui_button_draw(&_bttn_pen);
	gui_button_draw(&_bttn_fill);
	gui_button_draw(&_bttn_eraser);
}

bool ui_button_available(MouseButton button)
{
	return !((_consumed_buttons >> button) & 1);
}

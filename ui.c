#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"
#include "gui.h"

EditMode ui_edit_mode;
Color *ui_selection_color;
void (*ui_save_fn)(void);

static Rectangle _bnd_picker;

static grid_t _grid;
static button_t _bttn_pen;
static button_t _bttn_line;
static button_t _bttn_fill;
static button_t _bttn_eraser;
static button_t _bttn_picker;
static button_t _bttn_save;
static textbox_t _txtbx_test;

static unsigned char _consumed_buttons;

void init_ui(void)
{
	gui_theme_back = LIGHTGRAY;
	gui_theme_fore = DARKGRAY;

	ui_edit_mode = MODE_DRAW;

	_bnd_picker = (Rectangle) {
	0 + 4, 0 + 4, 192 - 4, 192 - 4};
	_grid = (grid_t) {
		(Vector2) {
	0, 192}, 96, 96, 4};
	_bttn_pen = (button_t) {
		&_grid, (Rectangle) {
	0, 0, 1, 1}, LoadTextureFromImage(LoadImage("res/pen.png"))};
	_bttn_line = (button_t) {
		&_grid, (Rectangle) {
	1, 0, 1, 1}, LoadTextureFromImage(LoadImage("res/line.png"))};
	_bttn_fill = (button_t) {
		&_grid, (Rectangle) {
	0, 1, 1, 1}, LoadTextureFromImage(LoadImage("res/fill.png"))};
	_bttn_eraser = (button_t) {
		&_grid, (Rectangle) {
	1, 1, 1, 1}, LoadTextureFromImage(LoadImage("res/eraser.png"))};
	_bttn_picker = (button_t) {
		&_grid, (Rectangle) {
	0, 2, 1, 1}, LoadTextureFromImage(LoadImage("res/picker.png"))};
	_bttn_save = (button_t) {
		&_grid, (Rectangle) {
	0, 3, 2, 1}, LoadTextureFromImage(LoadImage("res/save.png"))};
	_txtbx_test = (textbox_t) {
		&_grid, (Rectangle) {
	0, 4, 2, 0.5}, "Hello world!", false, 32};
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
			else if (gui_button_inside(&_bttn_line, cursor))
				ui_edit_mode = MODE_LINE;
			else if (gui_button_inside(&_bttn_picker, cursor))
				ui_edit_mode = MODE_PICKER;
			else if (gui_button_inside(&_bttn_save, cursor))
				ui_save_fn();
			else
				continue;
			_consumed_buttons |= 1 << button;
		}
		if (IsMouseButtonReleased(button))
			_consumed_buttons &= ~(1 << button);
	}

	if (IsKeyPressed(KEY_D))
		ui_edit_mode = MODE_DRAW;
	if (IsKeyPressed(KEY_F))
		ui_edit_mode = MODE_FILL;
	if (IsKeyPressed(KEY_E))
		ui_edit_mode = MODE_ERASE;
	if (IsKeyPressed(KEY_L))
		ui_edit_mode = MODE_LINE;
	if (IsKeyPressed(KEY_P))
		ui_edit_mode = MODE_PICKER;
}

void ui_render(void)
{
	GuiColorPicker(_bnd_picker, "Color Picker", ui_selection_color);

	gui_button_draw(&_bttn_pen);
	gui_button_draw(&_bttn_line);
	gui_button_draw(&_bttn_fill);
	gui_button_draw(&_bttn_eraser);
	gui_button_draw(&_bttn_picker);
	gui_button_draw(&_bttn_save);
	gui_textbox_draw(&_txtbx_test);
}

bool ui_button_available(MouseButton button)
{
	return !((_consumed_buttons >> button) & 1);
}

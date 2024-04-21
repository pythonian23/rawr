#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"

Color *ui_selection_color;

Rectangle ui_picker_bounds;

void init_ui(void)
{
	ui_picker_bounds = (Rectangle) {
	0, 0, 256, 256};
}

void ui_render(void)
{
	GuiColorPicker(ui_picker_bounds, "Color Picker", ui_selection_color);
}

bool ui_has_cursor(void)
{
	return (CheckCollisionPointRec(GetMousePosition(), ui_picker_bounds));
}

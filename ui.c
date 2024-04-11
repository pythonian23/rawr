#include "ui.h"
#include "raylib.h"
#include "raygui/src/raygui.h"

Rectangle ui_picker_bounds = { 0, 0, 256, 256 };

void init_ui(void)
{
}

void ui_render(void)
{
}

bool ui_has_cursor(void)
{
	return (CheckCollisionPointRec(GetMousePosition(), ui_picker_bounds));
}

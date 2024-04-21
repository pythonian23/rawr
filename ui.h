#ifndef UI_H_
#define UI_H_
#include "raylib.h"

extern Color *ui_selection_color;

extern Rectangle ui_picker_bounds;

extern void init_ui(void);
extern void ui_render(void);

extern bool ui_has_cursor(void);

#endif
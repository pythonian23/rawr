#ifndef UI_H_
#define UI_H_
#include "raylib.h"

typedef enum {
	MODE_DRAW,
	MODE_FILL,
	MODE_ERASE,
	MODE_PICKER,
} EditMode;

extern EditMode ui_edit_mode;
extern Color *ui_selection_color;

extern void init_ui(void);
extern void ui_handle_input(void);
extern void ui_render(void);

extern bool ui_button_available(MouseButton button);

#endif

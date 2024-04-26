#ifndef GUI_H
#define GUI_H
#include "raylib.h"

typedef struct {
	Vector2 pos;
	int width, height;
	int gap;
} grid_t;

typedef struct {
	grid_t *grid;
	Rectangle bounds;
	char buffer[64];
	bool activated;
	int fontsize;
} textbox_t;

typedef struct {
	grid_t *grid;
	Rectangle bounds;
	Texture texture;
} button_t;

extern Color gui_theme_back;
extern Color gui_theme_fore;

extern Rectangle gui_grid_rect(grid_t * g, Rectangle r);

extern void gui_textbox_draw(textbox_t * t);
extern void gui_button_draw(button_t * button);
extern bool gui_button_inside(button_t * b, Vector2 pos);

#endif

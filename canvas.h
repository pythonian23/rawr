#ifndef CANVAS_H_
#define CANVAS_H_
#include "raylib.h"

extern void init_canvas(void);

extern Texture cvs_get_texture(void);
extern int cvs_get_width(void);
extern int cvs_get_height(void);
extern void cvs_set_pixel(int x, int y, Color color);
extern void cvs_set_pixel(Vector2 vec, Color color);
extern void cvs_draw_line(Vector2 vec1, Vector2 vec2, Color color);

#endif				// CANVAS_H_

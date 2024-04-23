#include "gui.h"
#include "raylib.h"
#define MAX_ITEMS

Color gui_theme_back;
Color gui_theme_fore;

Rectangle gui_grid_rect(grid_t *g, Rectangle r)
{
	return (Rectangle) {
	g->pos.x + g->width * r.x + g->gap * (r.x + 1),
		    g->pos.y + g->height * r.y + g->gap * (r.y + 1),
		    g->width * r.width - g->gap,
		    g->height * r.height - g->gap,};
}

void gui_button_draw(button_t *b)
{
	Rectangle rect = gui_grid_rect(b->grid, b->bounds);
	DrawRectangleRec(rect, gui_theme_back);
	DrawTexturePro(b->texture, (Rectangle) {
		       0, 0,
		       b->texture.width, b->texture.height}, rect, (Vector2) {
		       0}, 0, gui_theme_fore);
}

bool gui_button_inside(button_t *b, Vector2 p)
{
	return CheckCollisionPointRec(p, gui_grid_rect(b->grid, b->bounds));
}

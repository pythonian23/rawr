#include "canvas.h"
#include <stdbool.h>
#include "raylib.h"

static Image _bg_image;
static Image _image;
static Texture _texture;

static bool _updated;

static void flood_fill(int x, int y, Color target, Color color,
		       bool (*proceed)(Color, Color))
{
	if ((x < 0) || (_image.width <= x))
		return;
	if ((y < 0) || (_image.height <= y))
		return;
	if (ColorIsEqual(target, color))
		return;
	if (!proceed(GetImageColor(_image, x, y), target))
		return;

	ImageDrawPixel(&_image, x, y, color);

	flood_fill(x - 1, y, target, color, proceed);
	flood_fill(x + 1, y, target, color, proceed);
	flood_fill(x, y - 1, target, color, proceed);
	flood_fill(x, y + 1, target, color, proceed);
}

void init_canvas(void)
{
	_bg_image = GenImageChecked(64, 64, 1, 1, DARKGRAY, GRAY);
	_image = GenImageColor(64, 64, (Color) {
			       0, 0, 0, 0});
	_texture = LoadTextureFromImage(_bg_image);
	_updated = true;
}

void cvs_update(void)
{
	static Image output;

	output = ImageCopy(_bg_image);

	ImageDraw(&output, _image, (Rectangle) {
		  0, 0, _bg_image.width, _bg_image.height}
		  , (Rectangle) {
		  0, 0, _image.width, _image.height}
		  , WHITE);
	UpdateTexture(_texture, output.data);
	_updated = false;

	UnloadImage(output);
}

Texture cvs_get_texture(void)
{
	if (_updated)
		cvs_update();
	return _texture;
}

int cvs_get_width(void)
{
	return _image.width;
}

int cvs_get_height(void)
{
	return _image.height;
}

Color cvs_get_pixel(Vector2 vec)
{
	return GetImageColor(_image, vec.x, vec.y);
}

void cvs_set_pixel(Vector2 vec, Color color)
{
	ImageDrawPixelV(&_image, vec, color);
	_updated = true;
}

void cvs_draw_line(Vector2 vec1, Vector2 vec2, Color color)
{
	ImageDrawLineV(&_image, vec1, vec2, color);
	_updated = true;
}

void cvs_fill(Vector2 origin, Color color)
{
	flood_fill(origin.x, origin.y,
		   GetImageColor(_image, origin.x, origin.y), color,
		   &ColorIsEqual);
	_updated = true;
}

bool cvs_save_to(char *filename)
{
	return ExportImage(_image, filename);
}

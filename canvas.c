#include "canvas.h"
#include <stdbool.h>
#include "raylib.h"

static Image _bg_image;
static Image _image;
static Texture _texture;

static bool _updated;

void init_canvas(void)
{
	_bg_image = GenImageChecked(64, 64, 1, 1, DARKGRAY, GRAY);
	_image = GenImageColor(64, 64, (Color) {
			       0, 0, 0, 0});
	_updated = true;
}

Texture cvs_get_texture(void)
{
	if (_updated) {
		static Image output;

		UnloadTexture(_texture);
		output = ImageCopy(_bg_image);

		ImageDraw(&output, _image, (Rectangle) {
			  0, 0, _bg_image.width, _bg_image.height}
			  , (Rectangle) {
			  0, 0, _image.width, _image.height}
			  , WHITE);
		_texture = LoadTextureFromImage(output);
		_updated = false;

		UnloadImage(output);
	}
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

bool cvs_save_to(char *filename)
{
	return ExportImage(_image, filename);
}

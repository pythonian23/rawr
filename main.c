#include "raylib.h"
#include "raymath.h"
#include "raygui/src/raygui.h"
#include "canvas.h"
#include "ui.h"

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_DEBUG
#endif

static int _tps;
static Camera2D _camera;
static Vector2 _pan;
static float _scale;

static Color _main_color;

static void init_raylib(void)
{
	SetTraceLogLevel(LOG_LEVEL);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
	InitWindow(1280, 720, "rawr Pixel Art Editor");
	SetExitKey(KEY_Q);

	_camera = (Camera2D) {
	0};
}

static void init(void)
{
	init_raylib();
	init_canvas();
	init_ui();
	ui_selection_color = &_main_color;

	_scale = 1;
	_main_color = (Color) {
	255, 0, 255, 255};
}

static Vector2 _mouse_position(void)
{
	return GetScreenToWorld2D(GetMousePosition(), _camera);
}

static void _handle_input(void)
{
	ui_handle_input();

	static Vector2 draw_position;
	static Vector2 draw_position_prev;

	if (IsKeyPressed(KEY_MINUS))
		_scale /= 1.2;
	if (IsKeyPressed(KEY_EQUAL))
		_scale *= 1.2;
	if (IsKeyPressed(KEY_ZERO))
		_scale = 1;

	if (IsKeyPressed(KEY_LEFT))
		_pan.x -= 4;
	if (IsKeyPressed(KEY_RIGHT))
		_pan.x += 4;
	if (IsKeyPressed(KEY_UP))
		_pan.y -= 4;
	if (IsKeyPressed(KEY_DOWN))
		_pan.y += 4;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
	    && ui_button_available(MOUSE_BUTTON_LEFT)) {
		switch (ui_edit_mode) {
		case MODE_DRAW:
			draw_position = _mouse_position();
			draw_position_prev = draw_position;
			break;
		case MODE_FILL:
			cvs_fill(_mouse_position(), _main_color);
			break;
		case MODE_ERASE:
			for (int x = 0; x < cvs_get_width(); x++)
				cvs_draw_line((Vector2) {
					      x, 0}, (Vector2) {
					      x, cvs_get_height() - 1}, (Color) {
					      0, 0, 0, 0});
				break;
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)
	    && ui_button_available(MOUSE_BUTTON_LEFT)) {
		switch (ui_edit_mode) {
		case MODE_DRAW:
			draw_position = _mouse_position();
			cvs_draw_line(draw_position_prev, draw_position,
				      _main_color);
			draw_position_prev = draw_position;
			break;
		case MODE_FILL:
			break;
		case MODE_ERASE:
			break;
		}
	}

	if (IsKeyPressed(KEY_S))
		if (!cvs_save_to("img.png"))
			TraceLog(LOG_WARNING, "Image save failed!");
}

static void _handle_camera(void)
{
	//TODO: clamp pan to screen edge

	_camera.target = (Vector2) {
	cvs_get_width() * 0.5, cvs_get_height() * 0.5};
	_camera.target = Vector2Add(_camera.target, _pan);
	_camera.offset = (Vector2) {
	GetScreenWidth() * 0.5, GetScreenHeight() * 0.5};
	_camera.zoom =
	    (GetScreenWidth() <
	     GetScreenHeight()? GetScreenWidth() * _scale /
	     cvs_get_width() : GetScreenHeight() * _scale / cvs_get_height());
}

static void _render(void)
{
	BeginDrawing();
	{
		ClearBackground(BLACK);

		BeginMode2D(_camera);
		{
			DrawTexture(cvs_get_texture(), 0, 0, WHITE);
		}
		EndMode2D();

		ui_render();

		DrawFPS(0, 0);
	}

	EndDrawing();
}

int main(void)
{
	init();

	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Raylib window init failed!");
		return -1;
	}

	while (!WindowShouldClose()) {
		_handle_input();
		_handle_camera();
		_render();
	}

	CloseWindow();

	return 0;
}

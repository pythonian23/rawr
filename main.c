#include "raylib.h"
#include "raymath.h"
#include "raygui/src/raygui.h"
#include "canvas.h"

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_DEBUG
#endif

static int tps;
static Camera2D camera;
static float scale;

static bool ui_focused = false;
static Rectangle picker_bounds = { 0, 0, 256, 256 };

static Color main_colour = { 255, 0, 255, 255 };

static void init_raylib(void)
{
	SetTraceLogLevel(LOG_LEVEL);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
	InitWindow(1280, 720, "rawr Pixel Art Editor");
	SetExitKey(KEY_Q);

	camera = (Camera2D) {
	0};
}

static void init(void)
{
	init_raylib();
	init_canvas();

	scale = 1;
}

static bool mouse_in_ui()
{
	return (CheckCollisionPointRec(GetMousePosition(), picker_bounds));
}

static Vector2 mouse_position(void)
{
	return GetScreenToWorld2D(GetMousePosition(), camera);
}

static void handle_input(void)
{

	static Vector2 draw_position;
	static Vector2 draw_position_prev;

	if (IsKeyPressed(KEY_MINUS))
		scale /= 1.2;
	if (IsKeyPressed(KEY_EQUAL))
		scale *= 1.2;
	if (IsKeyPressed(KEY_ZERO))
		scale = 1;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (mouse_in_ui())
			ui_focused = true;
		else {
			draw_position = mouse_position();
			draw_position_prev = draw_position;
		}
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !ui_focused) {
		draw_position = mouse_position();
		cvs_draw_line(draw_position_prev, draw_position, main_colour);
		draw_position_prev = draw_position;
	}
	if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		ui_focused = false;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
		cvs_fill(mouse_position(), main_colour);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		for (int x = 0; x < cvs_get_width(); x++)
			cvs_draw_line((Vector2) {
				      x, 0}
				      , (Vector2) {
				      x, cvs_get_height() - 1}, (Color) {
				      0, 0, 0, 0});

	if (IsKeyPressed(KEY_S))
		if (!cvs_save_to("img.png"))
			TraceLog(LOG_WARNING, "Image save failed!");
}

static void handle_camera(void)
{
	camera.target = (Vector2) {
	cvs_get_width() * 0.5, cvs_get_height() * 0.5};
	camera.offset = (Vector2) {
	GetScreenWidth() * 0.5, GetScreenHeight() * 0.5};
	camera.zoom =
	    (GetScreenWidth() < GetScreenHeight()?
	     GetScreenWidth() * scale / cvs_get_width() :
	     GetScreenHeight() * scale / cvs_get_height());
}

static void render(void)
{
	BeginDrawing();
	{
		ClearBackground(BLACK);

		BeginMode2D(camera);
		{
			DrawTexture(cvs_get_texture(), 0, 0, WHITE);
		}
		EndMode2D();

		GuiColorPanel(picker_bounds, "Colour Picker", &main_colour);

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
		handle_input();
		handle_camera();
		render();
	}

	CloseWindow();

	return 0;
}

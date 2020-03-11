#pragma once
#include <iostream>
#include "SDL.h"
class Screen
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer;
	int* m_color;
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
public:
	Screen();
	bool init();
	bool process_events();
	void close();
	void update();
	void set_color(unsigned char r, unsigned char g, unsigned char b);
	void draw_pixel(int x, int y);
	void draw_background();
	void draw_line(int x_start, int y_start, int x_end, int y_end);
};


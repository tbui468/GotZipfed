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
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
public:
	Screen();
	bool init();
	bool process_events();
	void close();
};


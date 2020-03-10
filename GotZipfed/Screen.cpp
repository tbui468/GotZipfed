#include "Screen.h"

Screen::Screen()
	: m_window(nullptr), m_renderer(nullptr), m_texture(nullptr), m_buffer(nullptr) {};

bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL\n";
		return false;
	}

	m_window = SDL_CreateWindow("Zipf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_window == nullptr) {
		std::cout << "Could not create window\n";
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		std::cout << "Could not create renderer\n";
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_texture == nullptr) {
		std::cout << "Could not create texture\n";
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
		return false;
	}
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(m_buffer, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT);

	return true;
}

bool Screen::process_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}

void Screen::close() {
	if(m_window != nullptr) SDL_DestroyWindow(m_window);
	if(m_renderer != nullptr) SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}
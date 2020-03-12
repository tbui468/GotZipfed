#include "Screen.h"
#include <iomanip>

Screen::Screen()
	: m_window(nullptr), m_renderer(nullptr), m_texture(nullptr), m_buffer(nullptr), m_color(nullptr) {};

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

	m_color = new int(0);

	memset(m_buffer, 0x000000FF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	set_color(0,0,0);
	draw_background();
	update();

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
	if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
	if (m_buffer != nullptr) delete m_buffer;
	if (m_color != nullptr) delete m_color;
	SDL_Quit();
}

void Screen::update() {
	SDL_UpdateTexture(m_texture, nullptr, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
}


void Screen::draw_pixel(int x, int y) {
	if(inside_window(x, y))
		m_buffer[y * SCREEN_WIDTH + x] = *m_color;
}

void Screen::draw_background() {
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
		m_buffer[i] = *m_color;
	}
}

void Screen::set_color(unsigned char r, unsigned char g, unsigned char b) {
	*m_color = r;
	*m_color <<= 8;
	*m_color += g;
	*m_color <<= 8;
	*m_color += b;
	*m_color <<= 8;
	*m_color += 0xFF;
}

void Screen::draw_line(int x_start, int y_start, int x_end, int y_end) {
	int x_delta = x_end - x_start;
	int y_delta = y_end - y_start;
	int longest_dis = abs(x_delta) < abs(y_delta) ? abs(y_delta) : abs(x_delta);
	double x_shift = (double)x_delta / longest_dis;
	double y_shift = (double)y_delta / longest_dis;
	//x_shift = (x_end - x_start) > 0 ? x_shift : -x_shift;
	//y_shift = (y_end - y_start) > 0 ? y_shift : -y_shift;

	for (int i = 0; i < longest_dis; ++i) {
		int x = (int)(x_start + x_shift * i);
		int y = (int)(y_start + y_shift * i);
		draw_pixel(x, y);
	}
}

bool Screen::inside_window(int x, int y) {
	if (y < 0) return false;
	if (y >= SCREEN_HEIGHT) return false;
	if (x < 0) return false;
	if (x >= SCREEN_WIDTH) return false;
	return true;
}
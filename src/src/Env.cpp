#include "Env.hpp"

#include <iostream>



Env::Env()
	: m_renderer{ nullptr },
	m_window{ nullptr },
	m_is_running{ false },
	m_ticks_count{ 0 },
	m_grid{}
{

}

int Env::initialize()
{
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);
	if (sdl_result != 0) {
		SDL_Log("SDL init failed: %s", SDL_GetError());
		return sdl_result;
	}

	m_window = SDL_CreateWindow(
		"game-of-life", // title
		100, // top left x pos
		100, // top left y pos
		WINDOW_WIDTH, // .
		WINDOW_HEIGHT, // .
		0 // no flags
	);

	if (m_window == nullptr) {
		SDL_Log("Window init failed: %s", SDL_GetError());
		return 1;
	}

	m_renderer = SDL_CreateRenderer(
		m_window, // where we render
		-1, // .
		SDL_RENDERER_ACCELERATED // hardware accel
		| SDL_RENDERER_PRESENTVSYNC //vsync
	);

	if (m_renderer == nullptr) {
		SDL_Log("Renderer init failed: %s", SDL_GetError());
		return 1;
	}

	std::cout << "Initalization successful...\n";
	//finish init members
	m_is_running = true;
	int rows = WINDOW_HEIGHT / CELL_SIZE;
	int cols = WINDOW_WIDTH / CELL_SIZE;
	m_grid.initialize(rows, cols);
	return 0;
}

void Env::shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	std::cout << "Shutdown successful...\n";
}

void Env::runLoop()
{

	std::cout << "Entering Loop...\n";
	unsigned long int loop_counter = 0;
	while (m_is_running) {
		loop_counter++;
		if (loop_counter % 100'000 == 0)
			std::cout << ".";
		if (loop_counter % 5 == 0) {
			m_grid.update();
		}
		processInput();
		updateEnv();
		generateOutput();
	}
	std::cout << "\n";
}

void Env::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_is_running = false;
				break;

			default:
				break;
		}
	}

	//we grab the entire keyboard
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		m_is_running = false;
	}
}

void Env::updateEnv()
{
	// wait so we have target fps
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + MS_PER_FRAME));

	// find time elipsed & clamp it
	float delta_time = (SDL_GetTicks() - m_ticks_count) / 1000.0f;
	delta_time = fmin(delta_time, FRAMES_PER_MS);

	//update ticks
	m_ticks_count = SDL_GetTicks();


}

void Env::generateOutput()
{
	SDL_SetRenderDrawColor(
		m_renderer,
		0,
		0,
		0,
		255
	);
	SDL_RenderClear(m_renderer);

	SDL_SetRenderDrawColor(
		m_renderer,
		255,
		255,
		255,
		255
	);

	auto [rows, cols] = m_grid.dim();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int val = m_grid.get(i, j);
			if (val == 1) {
				SDL_Rect w = {
					j * CELL_SIZE,
					i * CELL_SIZE,
					CELL_SIZE,
					CELL_SIZE
				};
				SDL_RenderFillRect(m_renderer, &w);
			}
		}
	}

	// TODO draw grid lines
	SDL_RenderPresent(m_renderer);

}

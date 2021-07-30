#pragma once


#include <SDL2/SDL.h>
#include "Grid.hpp"

//constants
inline const int WINDOW_WIDTH = 1280;
inline const int WINDOW_HEIGHT = 800;

inline const int CELL_SIZE = 4;

inline const int FRAMES_PER_SECOND = 60;
inline const float FRAMES_PER_MS = FRAMES_PER_SECOND / 1000.0;
inline const float MS_PER_FRAME = 1000.0 / FRAMES_PER_SECOND;

class Env {
public:
	Env();

	//sets
	int initialize();
	void shutdown();

	//main
	void runLoop();

private:
	//beg loop helpers
	void processInput();
	void updateEnv();
	void generateOutput();
	//end looop helpers

	//SDL members
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	//utility
	bool m_is_running;
	unsigned long int m_ticks_count;

	//State
	Grid m_grid;
};

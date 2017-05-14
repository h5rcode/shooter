#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Event event;

	bool goOn = true;
	while (goOn) {
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			goOn = false;
			break;

		default:
			break;
		}
	}

	SDL_Quit();
	return 0;
}
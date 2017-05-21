#include "SdlRenderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SdlRenderer::SdlRenderer()
{
	int resultCode = SDL_Init(SDL_INIT_VIDEO);
	if (resultCode != 0) {
		throw std::exception(SDL_GetError());
	}

	_sdlWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_sdlWindow == NULL) {
		throw std::exception(SDL_GetError());
	}

	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (_sdlRenderer == NULL) {
		throw std::exception(SDL_GetError());
	}

	int flags = IMG_INIT_PNG;
	int initializedFlags = IMG_Init(flags);
	if (initializedFlags != flags) {
		throw std::exception(IMG_GetError());
	}
}

void SdlRenderer::render(IGameState& gameState) {
	SDL_RenderClear(_sdlRenderer);

	IGameSet& gameSet = gameState.getGameSet();
	Player& player = gameState.getPlayer();

	SDL_RenderPresent(_sdlRenderer);
}

void SdlRenderer::quit() {
	SDL_DestroyWindow(_sdlWindow);
	SDL_Quit();
}

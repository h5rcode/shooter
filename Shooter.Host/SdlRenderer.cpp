#include "SdlRenderer.h"

#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SdlRenderer::SdlRenderer()
{
	SDL_Init(SDL_INIT_VIDEO);

	_sdlWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
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

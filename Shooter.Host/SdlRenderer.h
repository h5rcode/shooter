#pragma once

#include <SDL.h>
#include "IRenderer.h"

class SdlRenderer : public IRenderer
{
public:
	SdlRenderer();

	void render(IGameState& gameState);
	void quit();

private:
	SDL_Renderer* _sdlRenderer;
	SDL_Window* _sdlWindow;
};


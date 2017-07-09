#pragma once

#include <SDL.h>
#include "Player.h"
#include "IRenderer.h"
#include "Wall.h"
#include "Prop.h"

class SdlRenderer : public IRenderer
{
public:
	SdlRenderer();

	void render(IGameState& gameState);
	void quit();

private:
	void render(IGameSet& gameSet, Vector2& camera);
	void render(Crosshair& crosshair, Vector2& camera);
	void render(Player& player, Vector2& camera);
	void render(Prop& prop, Vector2& camera);
	void render(Wall& wall, Vector2& camera);
	void render(std::string &texture, Vector2 & position, Vector2 & camera, double orientation);

private:
	SDL_Renderer* _sdlRenderer;
	SDL_Window* _sdlWindow;
};


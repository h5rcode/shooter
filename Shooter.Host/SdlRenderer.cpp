#include "SdlRenderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

#include "Crosshair.h"

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

	SDL_ShowCursor(SDL_DISABLE);
}

void SdlRenderer::render(IGameState& gameState) {
	SDL_RenderClear(_sdlRenderer);

	IGameSet& gameSet = gameState.getGameSet();
	Vector2& camera = gameState.getCamera();
	Player& player = gameState.getPlayer();
	Crosshair& crosshair = gameState.getCrosshair();

	render(player, camera);
	render(crosshair, camera);

	SDL_RenderPresent(_sdlRenderer);
}

void SdlRenderer::render(Crosshair& crosshair, Vector2 & camera)
{
	Vector2& position = crosshair.getPosition();
	std::string& texture = crosshair.getTexture();
	double orientation = 0;
	render(texture, position, camera, orientation);
}

void SdlRenderer::render(Player& player, Vector2& camera) {
	Vector2& position = player.getPosition();
	std::string& texture = player.getTexture();
	double orientation = player.getOrientation();
	render(texture, position, camera, orientation);
}

// TODO Do not load the texture each call, buffer it instead.
void SdlRenderer::render(std::string &texture, Vector2 & position, Vector2 & camera, double orientation)
{
	SDL_Surface* sdlSurface = IMG_Load(texture.c_str());
	SDL_SetColorKey(sdlSurface, SDL_TRUE, SDL_MapRGB(sdlSurface->format, 0, 0, 255));
	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(_sdlRenderer, sdlSurface);

	int w, h;
	SDL_QueryTexture(sdlTexture, NULL, NULL, &w, &h);

	SDL_FreeSurface(sdlSurface);

	SDL_Rect sdlRectangle;
	sdlRectangle.w = w;
	sdlRectangle.h = h;
	sdlRectangle.x = position.x - sdlRectangle.w / 2 - camera.x;
	sdlRectangle.y = position.y - sdlRectangle.h / 2 - camera.y;

	int angle = -180 * (orientation - M_PI / 2) / M_PI;
	SDL_RenderCopyEx(_sdlRenderer, sdlTexture, NULL, &sdlRectangle, angle, NULL, SDL_FLIP_NONE);

	SDL_DestroyTexture(sdlTexture);
}

void SdlRenderer::quit() {
	SDL_DestroyWindow(_sdlWindow);
	SDL_Quit();
}

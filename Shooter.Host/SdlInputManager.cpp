
#include "SdlInputManager.h"

#include <SDL.h>
#include <stdexcept>

SdlInputManager::SdlInputManager()
{
}

void SdlInputManager::getMouseState(int* mouseX, int* mouseY) {
	SDL_GetMouseState(mouseX, mouseY);
}

bool SdlInputManager::isKeyDown(Key key) {
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	SDL_Scancode sdlScanCode = getSdlScanCode(key);

	return keys[sdlScanCode] == 1;
}

bool SdlInputManager::pollEvent(Event* event) {
	SDL_Event sdlEvent;
	int pendingEventAvailable = SDL_PollEvent(&sdlEvent);

	if (pendingEventAvailable) {
		switch (sdlEvent.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			event->setType(MOUSE_BUTTON_DOWN);
			break;

		case SDL_QUIT:
			event->setType(QUIT);
			break;

		default:
			break;
		}
	}

	return pendingEventAvailable == 1;
}

SDL_Scancode SdlInputManager::getSdlScanCode(Key key) const {
	switch (key)
	{
	case DOWN:
		return SDL_SCANCODE_S;

	case LEFT:
		return SDL_SCANCODE_W;

	case RIGHT:
		return SDL_SCANCODE_A;

	case UP:
		return SDL_SCANCODE_W;
	}

	throw std::invalid_argument("Invalid key.");
}
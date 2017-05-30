#pragma once

#include "IInputManager.h"
#include "SDL.h"

class SdlInputManager : public IInputManager
{
public:
	SdlInputManager();

	void getMouseState(int& mouseX, int& mouseY);
	bool isKeyDown(Key key);
	bool pollEvent(Event& event);

private:
	SDL_Scancode getSdlScanCode(Key key) const;
};


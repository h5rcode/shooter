#include <SDL.h>
#include <stdexcept>

#include "GameSet.h"
#include "GameSettings.h"
#include "GameState.h"
#include "SdlInputManager.h"
#include "SdlRenderer.h"

int main(int argc, char** argv) {
	try {
		GameSet gameSet;
		GameSettings gameSettings;
		SdlInputManager inputManager;
		std::string crosshairTexture = "D:\\Projets\\Shooter\\Resources\\img\\Crosshair.png";
		std::string playerTexture = "D:\\Projets\\Shooter\\Resources\\img\\Player.png";
		Crosshair crosshair(crosshairTexture);
		Player player(playerTexture);
		GameState gameState(gameSet, gameSettings, inputManager, crosshair, player);

		SdlRenderer sdlRenderer;

		bool goOn = true;
		Uint32 lastTicks = SDL_GetTicks();
		while (goOn) {
			Uint32 ticks = SDL_GetTicks();
			Uint32 elapsed = ticks - lastTicks;

			gameState.processInput();

			if (gameState.isStopped()) {
				sdlRenderer.quit();
				goOn = false;
				break;
			}

			gameState.update(elapsed);
			sdlRenderer.render(gameState);

			lastTicks = ticks;
		}

		return 0;
	}
	catch (std::exception& e) {
		const char* what = e.what();
		return -1;
	}
	catch (...) {
		return -1;
	}
}
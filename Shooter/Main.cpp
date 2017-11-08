#include <stdexcept>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "GameSet.h"
#include "GameSettings.h"
#include "GameState.h"
#include "SfmlInputManager.h"
#include "SfmlRenderer.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	try
	{
		// TODO Handle screen dimensions.
		sf::Vector2i screenDimensions(800, 600);
		sf::RenderWindow renderWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Shooter");
		renderWindow.setMouseCursorVisible(false);

		GameSet gameSet;
		GameSettings gameSettings;
		SfmlInputManager inputManager(renderWindow);

		std::string crosshairTexture = "Resources/textures/Crosshair.png";
		std::string playerTexture = "Resources/textures/character.png";
		Crosshair crosshair(crosshairTexture);
		Player player(playerTexture);
		GameState gameState(gameSet, gameSettings, inputManager, crosshair, player);

		SfmlRenderer sfmlRenderer(renderWindow);

		sf::Clock frameClock;

		bool goOn = true;
		while (goOn) {

			sf::Time frameTime = frameClock.restart();

			gameState.processInput();

			if (gameState.isStopped()) {
				sfmlRenderer.quit();
				goOn = false;
				break;
			}

			gameState.update(frameTime.asMilliseconds());
			sfmlRenderer.render(gameState);
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
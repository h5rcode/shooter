#include <stdexcept>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "AnimatedRenderable.h"
#include "GameSet.h"
#include "GameSettings.h"
#include "GameState.h"
#include "Inventory.h"
#include "LevelDescriptor.h"
#include "SfmlInputManager.h"
#include "SfmlRenderer.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	try
	{
		std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
		if (fullscreenModes.size() == 0) {
			throw std::runtime_error("Not suitable fullscreen mode found.");
		}

		sf::VideoMode videoMode = fullscreenModes.at(0);
		sf::RenderWindow renderWindow(videoMode, "Shooter", sf::Style::Fullscreen);
		renderWindow.setMouseCursorVisible(false);

		std::string level01FileName = "Levels/level-01.json";
		LevelDescriptor levelDescriptor;
		levelDescriptor.loadFromFile(level01FileName);

		std::vector<std::shared_ptr<IItem>> items = levelDescriptor.getItems();
		std::vector<std::shared_ptr<Wall>> walls = levelDescriptor.getWalls();
		std::vector<std::shared_ptr<Prop>> props = levelDescriptor.getProps();

		GameSet gameSet(items, walls, props);
		GameSettings gameSettings;
		SfmlInputManager inputManager(renderWindow);

		std::string crosshairTexture = "Resources/textures/Crosshair.png";
		Crosshair crosshair(crosshairTexture);

		PlayerInitialStateDescriptor playerInitialState = levelDescriptor.playerInitialStateDescriptor;

		AnimatedRenderable playerRenderable;
		Inventory inventory;
		Player player(playerInitialState.getPosition(), playerRenderable, inventory);
		Camera camera(videoMode.width, videoMode.height);
		GameState gameState(gameSet, gameSettings, inputManager, crosshair, player, camera);

		SfmlRenderer sfmlRenderer(gameState, renderWindow);

		sf::Clock frameClock;

		bool goOn = true;
		while (goOn) {

			sf::Time frameTime = frameClock.restart();

			gameState.processInput();

			if (gameState.isStopped()) {
				goOn = false;
				break;
			}

			gameState.update(frameTime);
			sfmlRenderer.render();
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
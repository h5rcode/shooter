#include <stdexcept>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "GameSet.h"
#include "GameSetRenderer.h"
#include "GameSettings.h"
#include "GameState.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "ItemFactory.h"
#include "ItemRenderer.h"
#include "LevelDescriptor.h"
#include "Player.h"
#include "PlayerRenderer.h"
#include "ProjectileRenderer.h"
#include "PropRenderer.h"
#include "ResourceManager.h"
#include "SfmlAudioSystem.h"
#include "SfmlInputManager.h"
#include "SfmlRenderer.h"
#include "WallRenderer.h"

using namespace Shooter::Audio;
using namespace Shooter::Inventory;
using namespace Shooter::ItemDatabase;
using namespace Shooter::LevelDescriptors;
using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;
using namespace Shooter::World;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	try
	{
		std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
		if (fullscreenModes.size() == 0) {
			throw std::runtime_error("Not suitable fullscreen mode found.");
		}

		sf::VideoMode videoMode = fullscreenModes.at(0);
		sf::RenderWindow renderWindow(videoMode, "Shooter", sf::Style::Default);
		renderWindow.setMouseCursorVisible(false);

		ResourceManager resourceManager;

		std::string itemDatabasePath = "ItemDatabase/items.json";
		ItemDatabase itemDatabase(itemDatabasePath);

		std::string level01FileName = "Levels/level-01.json";

		ItemFactory itemFactory(itemDatabase);
		LevelDescriptor levelDescriptor(itemFactory);
		levelDescriptor.loadFromFile(level01FileName);

		std::vector<std::shared_ptr<IItem>> items = levelDescriptor.getItems();
		std::vector<std::shared_ptr<Wall>> walls = levelDescriptor.getWalls();
		std::vector<std::shared_ptr<Prop>> props = levelDescriptor.getProps();

		GameSet gameSet(items, walls, props);
		GameSettings gameSettings;
		SfmlInputManager inputManager(renderWindow);

		sf::Texture* crosshairTexture = resourceManager.getTexture("Resources/textures/Crosshair.png");
		Crosshair crosshair(*crosshairTexture);

		PlayerInitialStateDescriptor playerInitialState = levelDescriptor.playerInitialStateDescriptor;

		sf::Texture* playerTexture = resourceManager.getTexture("Resources/textures/character.png");
		sf::Texture* projectileTexture = resourceManager.getTexture("Resources/textures/bullet.png");
		Inventory inventory;
		Player player(playerInitialState.getPosition(), 100, inventory);
		Camera camera(videoMode.width, videoMode.height);
		GameState gameState(gameSet, gameSettings, inputManager, crosshair, player, camera);

		ItemRenderer itemRenderer(itemDatabase, renderWindow, resourceManager);
		PropRenderer propRenderer(renderWindow, resourceManager);
		WallRenderer wallRenderer(renderWindow, resourceManager);
		GameSetRenderer gameSetRenderer(itemRenderer, propRenderer, wallRenderer);
		PlayerRenderer playerRenderer(renderWindow, *playerTexture);
		ProjectileRenderer projectileRenderer(renderWindow, *projectileTexture);
		SfmlRenderer sfmlRenderer(gameSetRenderer, gameState, playerRenderer, projectileRenderer, renderWindow, resourceManager);
		SfmlAudioSystem sfmlAudioSystem(gameState, renderWindow, resourceManager);

		sf::Clock frameClock;

		bool goOn = true;
		while (goOn) {

			sf::Time frameTime = frameClock.restart();

			gameState.getGameEvents().clear();

			gameState.processInput();

			if (gameState.isStopped()) {
				goOn = false;
				break;
			}

			gameState.update(frameTime);
			sfmlRenderer.render(frameTime);
			sfmlAudioSystem.update();
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
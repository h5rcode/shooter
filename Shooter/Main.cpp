#include <stdexcept>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "GameEvent.h"
#include "GameSet.h"
#include "GameSetRenderer.h"
#include "GameSettings.h"
#include "GameState.h"
#include "InputEventHandler.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "ItemFactory.h"
#include "ItemRenderer.h"
#include "LevelDescriptor.h"
#include "Player.h"
#include "PlayerRenderer.h"
#include "ProjectileRenderer.h"
#include "PropDatabase.h"
#include "PropRenderer.h"
#include "ResourceManager.h"
#include "SfmlAudioSystem.h"
#include "SfmlInputManager.h"
#include "SfmlRenderer.h"
#include "SoundDatabase.h"
#include "WallRenderer.h"

using namespace Shooter::Audio;
using namespace Shooter::Inventory;
using namespace Shooter::WorldDatabase::Items;
using namespace Shooter::LevelDescriptors;
using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;
using namespace Shooter::World;
using namespace Shooter::WorldDatabase::Props;
using namespace Shooter::WorldDatabase::Sounds;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	try
	{
		std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
		if (fullscreenModes.size() == 0)
		{
			throw std::runtime_error("Not suitable fullscreen mode found.");
		}

		sf::VideoMode videoMode = fullscreenModes.at(0);
		sf::RenderWindow renderWindow(videoMode, "Shooter", sf::Style::Default);
		renderWindow.setMouseCursorVisible(false);

		ItemDatabase itemDatabase("WorldDatabase/items.json");
		PropDatabase propDatabase("WorldDatabase/props.json");
		SoundDatabase soundDatabase("WorldDatabase/sounds.json");

		std::string level01FileName = "Levels/level-01.json";

		ItemFactory itemFactory(itemDatabase);
		LevelDescriptor levelDescriptor(itemFactory, propDatabase);
		levelDescriptor.loadFromFile(level01FileName);

		std::vector<std::shared_ptr<IItem>> items = levelDescriptor.getItems();
		std::vector<std::shared_ptr<Wall>> walls = levelDescriptor.getWalls();
		std::vector<std::shared_ptr<Prop>> props = levelDescriptor.getProps();

		GameSet gameSet(items, walls, props);
		GameSettings gameSettings;
		SfmlInputManager inputManager(renderWindow);
		InputEventHandler inputEventHandler;

		PlayerInitialStateDescriptor playerInitialState = levelDescriptor.playerInitialStateDescriptor;

		ResourceManager resourceManager;

		resourceManager.loadSoundBuffer(soundDatabase.getBulletImpactFilename());
		resourceManager.loadSoundBuffer(soundDatabase.getFootstepFilename());
		resourceManager.loadSoundBuffer(soundDatabase.getGruntFilename());
		resourceManager.loadSoundBuffer(soundDatabase.getPickupItemFilename());

		std::vector<std::string> allsoundFilenames = itemDatabase.getAllSoundFilenames();
		for each (const std::string& soundFilename in allsoundFilenames)
		{
			resourceManager.loadSoundBuffer(soundFilename);
		}

		sf::Texture* playerTexture = resourceManager.getTexture("character.png");
		sf::Texture* projectileTexture = resourceManager.getTexture("bullet.png");
		Inventory inventory;
		Crosshair crosshair;
		Player player(playerInitialState.getPosition(), 100, inventory);
		Camera camera(videoMode.width, videoMode.height);
		GameState gameState(gameSet, gameSettings, inputEventHandler, inputManager, crosshair, player, camera);

		ItemRenderer itemRenderer(itemDatabase, renderWindow, resourceManager);
		PropRenderer propRenderer(propDatabase, renderWindow, resourceManager);
		WallRenderer wallRenderer(renderWindow, resourceManager);
		GameSetRenderer gameSetRenderer(itemRenderer, propRenderer, wallRenderer);
		PlayerRenderer playerRenderer(renderWindow, *playerTexture);
		ProjectileRenderer projectileRenderer(renderWindow, *projectileTexture);
		SfmlRenderer sfmlRenderer(gameSetRenderer, gameState, playerRenderer, projectileRenderer, renderWindow, resourceManager);
		SfmlAudioSystem sfmlAudioSystem(gameState, itemDatabase, renderWindow, resourceManager, soundDatabase);

		sf::Clock frameClock;

		bool goOn = true;
		while (goOn)
		{
			sf::Time frameTime = frameClock.restart();

			std::vector<sf::Event> events;
			sf::Event event;
			while (inputManager.pollEvent(event))
			{
				events.push_back(event);
			}

			if (gameState.isStopped())
			{
				goOn = false;
				break;
			}

			std::vector<GameEvent> gameEvents = gameState.update(frameTime, events);

			sfmlRenderer.render(frameTime);
			sfmlAudioSystem.update(gameEvents);
		}

		return 0;
	}
	catch (std::exception& e)
	{
		const char* what = e.what();
		return -1;
	}
	catch (...)
	{
		return -1;
	}
}
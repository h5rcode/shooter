#include <stdexcept>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "BoundingBoxRenderer.h"
#include "FloorRenderer.h"
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
#include "NonPlayingCharacterDatabase.h"
#include "NonPlayingCharacterRenderer.h"
#include "Player.h"
#include "PlayerRenderer.h"
#include "ProjectileRenderer.h"
#include "PropDatabase.h"
#include "PropRenderer.h"
#include "RenderingOptions.h"
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
		NonPlayingCharacterDatabase npcDatabase("WorldDatabase/npcs.json");
		PropDatabase propDatabase("WorldDatabase/props.json");
		SoundDatabase soundDatabase("WorldDatabase/sounds.json");

		std::string level01FileName = "Levels/level-01.json";

		ItemFactory itemFactory(itemDatabase);
		NonPlayingCharacterFactory npcFactory(npcDatabase);
		LevelDescriptor levelDescriptor(itemFactory, npcFactory, propDatabase);
		levelDescriptor.loadFromFile(level01FileName);

		std::vector<std::shared_ptr<Floor>> floors = levelDescriptor.getFloors();
		std::vector<std::shared_ptr<IItem>> items = levelDescriptor.getItems();
		std::vector<std::shared_ptr<Wall>> walls = levelDescriptor.getWalls();
		std::vector<std::shared_ptr<Prop>> props = levelDescriptor.getProps();
		std::vector<std::shared_ptr<INonPlayingCharacter>> nonPlayingCharacters = levelDescriptor.getNonPlayingCharacters();

		GameSet gameSet(floors, items, walls, props);
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
		for each (const std::string & soundFilename in allsoundFilenames)
		{
			resourceManager.loadSoundBuffer(soundFilename);
		}

		for each (const std::shared_ptr<Floor> & floor in floors)
		{
			resourceManager.loadTexture(floor->getTexture(), true);
		}

		sf::Texture* playerTexture = resourceManager.getTexture("character.png");
		sf::Texture* projectileTexture = resourceManager.getTexture("bullet.png");
		Inventory inventory;
		Crosshair crosshair;
		Player player(playerInitialState.getPosition(), 100, inventory);
		Camera camera(videoMode.width, videoMode.height);
		GameState gameState(gameSet, gameSettings, inputEventHandler, inputManager, crosshair, nonPlayingCharacters, player, camera);

		RenderingOptions renderingOptions;
		renderingOptions.DrawSpeed = true;
		renderingOptions.DrawBoundingBoxes = true;

		BoundingBoxRenderer boundingBoxRenderer(renderWindow);
		FloorRenderer floorRenderer(renderWindow, resourceManager);
		ItemRenderer itemRenderer(itemDatabase, renderWindow, resourceManager);
		PropRenderer propRenderer(boundingBoxRenderer, propDatabase, renderingOptions, renderWindow, resourceManager);
		WallRenderer wallRenderer(renderWindow, resourceManager);
		GameSetRenderer gameSetRenderer(floorRenderer, itemRenderer, propRenderer, wallRenderer);
		NonPlayingCharacterRenderer npcRenderer(npcDatabase, renderWindow, resourceManager);
		PlayerRenderer playerRenderer(renderingOptions, renderWindow, *playerTexture);
		ProjectileRenderer projectileRenderer(renderWindow, *projectileTexture);
		SfmlRenderer sfmlRenderer(gameSetRenderer, gameState, npcRenderer, playerRenderer, projectileRenderer, renderWindow, resourceManager);
		SfmlAudioSystem sfmlAudioSystem(gameState, itemDatabase, renderWindow, resourceManager, soundDatabase);

		sf::Clock frameClock;

		bool goOn = true;

		const int updatesPerSecond = 60;
		const sf::Time maximumUpdateTimeStep = sf::milliseconds(1000 / updatesPerSecond);

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

			std::vector<GameEvent> gameEvents;
			sf::Time lag = frameTime;
			while (lag > sf::Time::Zero) {
				sf::Time updateTimeStep = lag < maximumUpdateTimeStep ? lag : maximumUpdateTimeStep;
				gameEvents = gameState.update(updateTimeStep, events);
				lag -= maximumUpdateTimeStep;
			}

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
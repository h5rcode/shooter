#include "SfmlAudioSystem.h"

using namespace Shooter::Audio;

const int MAX_SOUNDS = 256;

SfmlAudioSystem::SfmlAudioSystem(IGameState& gameState, IResourceManager& resourceManager) :
	_gameState(gameState),
	_resourceManager(resourceManager)
{
}

SfmlAudioSystem::~SfmlAudioSystem() {
	for each (sf::Sound* sound in _sounds)
	{
		delete sound;
	}
}

void SfmlAudioSystem::deleteStoppedSounds() {
	std::vector<sf::Sound*>::iterator soundIterator = _sounds.begin();
	while (soundIterator != _sounds.end())
	{
		sf::Sound* sound = *soundIterator;

		if (sound->getStatus() == sf::SoundSource::Status::Stopped) {
			soundIterator = _sounds.erase(soundIterator);
			delete sound;
		}
		else {
			++soundIterator;
		}
	}
}

void SfmlAudioSystem::update() {
	std::vector<GameEvent>& gameEvents = _gameState.getGameEvents();

	for each (GameEvent gameEvent in gameEvents)
	{
		switch (gameEvent.GameEventType)
		{
		case GameEventType::PlayerAttacked:
			playSound("Resources/sounds/180961__kleeb__gunshots.wav");
			break;

		case GameEventType::PlayerHurt:
			playSound("Resources/sounds/262279__dirtjm__grunts-male.wav");
			break;

		case GameEventType::PlayerPickedUpItem:
			playSound("Resources/sounds/177054__woodmoose__lowerguncock.wav");
			break;

		default:
			break;
		}
	}

	deleteStoppedSounds();
}

void SfmlAudioSystem::playSound(std::string filename)
{
	if (_sounds.size() >= MAX_SOUNDS) {
		return;
	}

	sf::SoundBuffer* soundBuffer = _resourceManager.getSoundBuffer(filename);

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*soundBuffer);
	sound->play();

	_sounds.push_back(sound);
}
#include "SfmlAudioSystem.h"

#include "FirearmDescriptor.h"
#include "WeaponDescriptor.h"

using namespace Shooter::Audio;

const int MAX_SOUNDS = 256;
const std::string SOUND_PATH = "Resources/sounds/";

SfmlAudioSystem::SfmlAudioSystem(IGameState& gameState,
	IItemDatabase& itemDatabase,
	sf::RenderWindow& renderWindow,
	IResourceManager& resourceManager) :
	_gameState(gameState),
	_itemDatabase(itemDatabase),
	_renderWindow(renderWindow),
	_resourceManager(resourceManager)
{
	sf::SoundBuffer* soundBuffer = _resourceManager.getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav");
	_playerFootstepsSound.setBuffer(*soundBuffer);
	_playerFootstepsSound.setRelativeToListener(true);
	_playerFootstepsSound.setLoop(true);
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

	IPlayer& player = _gameState.getPlayer();
	Vector2& playerPosition = player.getPosition();
	sf::Vector2i playerPositionInWindow = _renderWindow.mapCoordsToPixel(sf::Vector2f(playerPosition.x, playerPosition.y));
	sf::Listener::setPosition(playerPositionInWindow.x, 0., playerPositionInWindow.y);

	for each (GameEvent gameEvent in gameEvents)
	{
		switch (gameEvent.GameEventType)
		{
		case GameEventType::PlayerAttacked:
		{
			std::shared_ptr<IWeapon> weapon = player.getEquipedWeapon();
			std::shared_ptr<IItem> item = std::dynamic_pointer_cast<IItem>(weapon);
			ItemDescriptor* itemDescriptor = _itemDatabase.getItem(item->getId());
			WeaponDescriptor* weaponDescriptor = static_cast<WeaponDescriptor*>(itemDescriptor);

			if (weaponDescriptor->weaponType == WeaponType::Firearm) {
				FirearmDescriptor* firearmDescriptor = static_cast<FirearmDescriptor*>(weaponDescriptor);
				playSound(SOUND_PATH + firearmDescriptor->gunshotSound, playerPosition, true);
			}
		}
		break;

		case GameEventType::PlayerHurt:
			playSound("Resources/sounds/262279__dirtjm__grunts-male.wav", playerPosition, true);
			break;

		case GameEventType::PlayerPickedUpItem:
			playSound("Resources/sounds/177054__woodmoose__lowerguncock.wav", playerPosition, true);
			break;

		case GameEventType::PlayerStartedMoving:
			_playerFootstepsSound.play();
			break;

		case GameEventType::PlayerStoppedMoving:
			_playerFootstepsSound.stop();
			break;

		case GameEventType::ProjectileImpact:
			playSound("Resources/sounds/150839__toxicwafflezz__bullet-impact-3.wav", gameEvent.ProjectileImpactEvent.Projectile->getPosition(), false);
			break;

		default:
			break;
		}
	}

	deleteStoppedSounds();
}

void SfmlAudioSystem::playSound(std::string filename, Vector2 position, bool relativeToListener, bool loop)
{
	if (_sounds.size() >= MAX_SOUNDS) {
		return;
	}

	sf::SoundBuffer* soundBuffer = _resourceManager.getSoundBuffer(filename);

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*soundBuffer);
	sound->setLoop(loop);
	sound->play();

	sf::Vector2i soundPosition = _renderWindow.mapCoordsToPixel(sf::Vector2f(position.x, position.y));

	// TODO Make the min distance and attenuation values properties of each sound.
	sound->setMinDistance(30);
	sound->setAttenuation(0.1);

	sound->setRelativeToListener(relativeToListener);
	sound->setPosition(soundPosition.x, 0, soundPosition.y);

	_sounds.push_back(sound);
}
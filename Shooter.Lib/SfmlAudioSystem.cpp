#include "SfmlAudioSystem.h"

#include "FirearmDescriptor.h"
#include "WeaponDescriptor.h"

using namespace Shooter::Audio;

const int MAX_SOUNDS = 256;

SfmlAudioSystem::SfmlAudioSystem(
	IGameState& gameState,
	IItemDatabase& itemDatabase,
	sf::RenderWindow& renderWindow,
	IResourceManager& resourceManager,
	ISoundDatabase& soundDatabase) :
	_gameState(gameState),
	_itemDatabase(itemDatabase),
	_renderWindow(renderWindow),
	_resourceManager(resourceManager),
	_soundDatabase(soundDatabase)
{
	std::string filename = _soundDatabase.getFootstepFilename();
	sf::SoundBuffer* soundBuffer = _resourceManager.getSoundBuffer(filename);
	_playerFootstepsSound.setBuffer(*soundBuffer);
	_playerFootstepsSound.setRelativeToListener(true);
	_playerFootstepsSound.setLoop(true);
}

SfmlAudioSystem::~SfmlAudioSystem()
{
	for each (sf::Sound* sound in _sounds)
	{
		delete sound;
	}
}

void SfmlAudioSystem::deleteStoppedSounds()
{
	std::vector<sf::Sound*>::iterator soundIterator = _sounds.begin();
	while (soundIterator != _sounds.end())
	{
		sf::Sound* sound = *soundIterator;

		if (sound->getStatus() == sf::SoundSource::Status::Stopped)
		{
			soundIterator = _sounds.erase(soundIterator);
			delete sound;
		}
		else
		{
			++soundIterator;
		}
	}
}

void SfmlAudioSystem::update(std::vector<GameEvent>& gameEvents)
{
	IPlayer& player = _gameState.getPlayer();
	Vector2& playerPosition = player.getPosition();
	sf::Vector2i playerPositionInWindow = _renderWindow.mapCoordsToPixel(sf::Vector2f((float)playerPosition.x, (float)playerPosition.y));
	sf::Listener::setPosition((float)playerPositionInWindow.x, 0., (float)playerPositionInWindow.y);

	for each (GameEvent gameEvent in gameEvents)
	{
		switch (gameEvent.Type)
		{
		case GameEventType::PlayerAttacked:
		{
			std::shared_ptr<IWeapon> weapon = player.getEquipedWeapon();
			std::shared_ptr<IItem> item = std::dynamic_pointer_cast<IItem>(weapon);
			ItemDescriptor& itemDescriptor = _itemDatabase.getItem(item->getId());
			std::shared_ptr<WeaponDescriptor> weaponDescriptor = itemDescriptor.weapon;

			if (weaponDescriptor->weaponType == WeaponType::Firearm)
			{
				std::shared_ptr<FirearmDescriptor> firearmDescriptor = weaponDescriptor->Firearm;
				playSound(firearmDescriptor->gunshotSound, playerPosition, true);
			}
		}
		break;

		case GameEventType::PlayerHurt:
		{
			std::string& filename = _soundDatabase.getGruntFilename();
			playSound(filename, playerPosition, true);
		}
		break;

		case GameEventType::PlayerPickedUpItem:
		{
			std::string& filename = _soundDatabase.getPickupItemFilename();
			playSound(filename, playerPosition, true);
		}
		break;

		case GameEventType::PlayerStartedMoving:
		{
			_playerFootstepsSound.play();
		}
		break;

		case GameEventType::PlayerStoppedMoving:
		{
			_playerFootstepsSound.stop();
		}
		break;

		case GameEventType::ProjectileImpact:
		{
			std::string& filename = _soundDatabase.getBulletImpactFilename();
			playSound(filename, gameEvent.ProjectileImpact.Projectile->getPosition(), false);
		}
		break;
		}
	}

	deleteStoppedSounds();
}

void SfmlAudioSystem::playSound(std::string filename, Vector2 position, bool relativeToListener, bool loop)
{
	if (_sounds.size() >= MAX_SOUNDS)
	{
		return;
	}

	sf::SoundBuffer* soundBuffer = _resourceManager.getSoundBuffer(filename);

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*soundBuffer);
	sound->setLoop(loop);
	sound->play();

	sf::Vector2i soundPosition = _renderWindow.mapCoordsToPixel(sf::Vector2f((float)position.x, (float)position.y));

	// TODO Make the min distance and attenuation values properties of each sound.
	sound->setMinDistance(30.f);
	sound->setAttenuation(0.1f);

	sound->setRelativeToListener(relativeToListener);
	sound->setPosition((float)soundPosition.x, 0.f, (float)soundPosition.y);

	_sounds.push_back(sound);
}
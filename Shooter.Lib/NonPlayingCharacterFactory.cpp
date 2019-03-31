#include "NonPlayingCharacterFactory.h"

#include "INonPlayingCharacterDatabase.h"
#include "NonPlayingCharacter.h"

using namespace Shooter::Npcs;

NonPlayingCharacterFactory::NonPlayingCharacterFactory(INonPlayingCharacterDatabase& npcDatabase) :
	_npcDatabase(npcDatabase) {
}

std::shared_ptr<INonPlayingCharacter> NonPlayingCharacterFactory::build(std::string npcId, Vector2& position, double orientation) {
	NonPlayingCharacterDescriptor& npcDescriptor = _npcDatabase.getNpc(npcId);
	return std::make_shared<NonPlayingCharacter>(npcId, orientation, position, 100, npcDescriptor.width, npcDescriptor.height);
}
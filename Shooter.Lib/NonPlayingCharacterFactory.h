#pragma once

#include <memory>
#include <string>

#include "INonPlayingCharacter.h"
#include "INonPlayingCharacterDatabase.h"
#include "Vector2.h"

using namespace Shooter::WorldDatabase::Npcs;
using namespace Shooter::Math;

namespace Shooter {
	namespace Npcs {
		class NonPlayingCharacterFactory
		{
		public:
			NonPlayingCharacterFactory(INonPlayingCharacterDatabase& npcDatabase);

		public:
			std::shared_ptr<INonPlayingCharacter> build(std::string npcId, Vector2& position, double orientation);

		private:
			INonPlayingCharacterDatabase& _npcDatabase;
		};
	}
}
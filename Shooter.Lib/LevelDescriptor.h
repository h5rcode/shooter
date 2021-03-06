#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Floor.h"
#include "FloorDescriptor.h"
#include "IItem.h"
#include "INonPlayingCharacter.h"
#include "IPropDatabase.h"
#include "ItemFactory.h"
#include "LevelItemDescriptor.h"
#include "LevelNpcDescriptor.h"
#include "NonPlayingCharacterFactory.h"
#include "PlayerInitialStateDescriptor.h"
#include "Prop.h"
#include "LevelPropDescriptor.h"
#include "Vector2.h"
#include "Wall.h"
#include "WallDescriptor.h"

using namespace Shooter::Items;
using namespace Shooter::Math;
using namespace Shooter::Npcs;
using namespace Shooter::WorldDatabase::Props;

namespace Shooter {
	namespace LevelDescriptors {
		class LevelDescriptor {
		public:
			LevelDescriptor(ItemFactory& itemFactory, NonPlayingCharacterFactory& npcFactory, IPropDatabase& propDatabase);
		public:
			std::string name;
			PlayerInitialStateDescriptor playerInitialStateDescriptor;
			std::vector<std::shared_ptr<FloorDescriptor>> floorDescriptors;
			std::vector<std::shared_ptr<LevelItemDescriptor>> itemDescriptors;
			std::vector<std::shared_ptr<LevelNpcDescriptor>> nonPlayingCharacters;
			std::vector<std::shared_ptr<LevelPropDescriptor>> propDescriptors;
			std::vector<std::shared_ptr<WallDescriptor>> wallDescriptors;

			void loadFromFile(std::string& fileName);

			std::vector<std::shared_ptr<Floor>> getFloors();
			std::vector<std::shared_ptr<IItem>> getItems();
			std::vector<std::shared_ptr<INonPlayingCharacter>> getNonPlayingCharacters();
			std::vector<std::shared_ptr<Prop>> getProps();
			std::vector<std::shared_ptr<Wall>> getWalls();

		private:
			ItemFactory& _itemFactory;
			IPropDatabase& _propDatabase;
			NonPlayingCharacterFactory& _npcFactory;
		};
	}
}
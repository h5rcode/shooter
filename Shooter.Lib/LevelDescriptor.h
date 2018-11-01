#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IItem.h"
#include "ItemFactory.h"
#include "LevelItemDescriptor.h"
#include "PlayerInitialStateDescriptor.h"
#include "Prop.h"
#include "PropDescriptor.h"
#include "Vector2.h"
#include "Wall.h"
#include "WallDescriptor.h"

using namespace Shooter::Items;
using namespace Shooter::Math;

namespace Shooter {
	namespace LevelDescriptors {
		class LevelDescriptor {
		public:
			LevelDescriptor(ItemFactory& itemFactory);
		public:
			std::string name;
			PlayerInitialStateDescriptor playerInitialStateDescriptor;
			std::vector<std::shared_ptr<LevelItemDescriptor>> itemDescriptors;
			std::vector<std::shared_ptr<PropDescriptor>> propDescriptors;
			std::vector<std::shared_ptr<WallDescriptor>> wallDescriptors;

			void loadFromFile(std::string& fileName);

			std::vector<std::shared_ptr<IItem>> getItems();
			std::vector<std::shared_ptr<Prop>> getProps();
			std::vector<std::shared_ptr<Wall>> getWalls();

		private:
			ItemFactory& _itemFactory;
		};
	}
}
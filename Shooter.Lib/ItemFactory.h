#pragma once

#include <memory>
#include <string>

#include "IItem.h"
#include "IItemDatabase.h"
#include "IResourceManager.h"
#include "Vector2.h"

using namespace Shooter::ItemDatabase;
using namespace Shooter::Math;
using namespace Shooter::Rendering;

namespace Shooter {
	namespace Items {
		class ItemFactory
		{
		public:
			ItemFactory(IItemDatabase& itemDatabase, IResourceManager& resourceManager);

		public:
			std::shared_ptr<IItem> buildItem(std::string itemId, Vector2& position, double orientation);

		private:
			IItemDatabase& _itemDatabase;
			IResourceManager& _resourceManager;
		};
	}
}
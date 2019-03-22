#pragma once

#include "IGameSet.h"

using namespace Shooter::Items;
using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class GameSet : public IGameSet
		{
		public:
			GameSet(
				std::vector<std::shared_ptr<Floor>> floors,
				std::vector<std::shared_ptr<IItem>> items,
				std::vector<std::shared_ptr<Wall>> walls,
				std::vector<std::shared_ptr<Prop>> props);
		public:
			void addProp(std::shared_ptr<Prop> prop);
			bool collidesWith(BoundingBox& boundingBox) const;
			std::shared_ptr<IItem> getItemAt(Vector2& position);
			std::vector<std::shared_ptr<IItem>>& getItems();
			std::vector<std::shared_ptr<Floor>>& getFloors();
			std::shared_ptr<Prop> getPropAt(Vector2& position);
			std::vector<std::shared_ptr<Prop>>& getProps();
			std::vector<std::shared_ptr<Wall>>& getWalls();
			void removeItem(std::shared_ptr<IItem> item);
			void removeProp(std::shared_ptr<Prop> prop);
		private:
			std::vector<std::shared_ptr<Floor>> _floors;
			std::vector<std::shared_ptr<IItem>> _items;
			std::vector<std::shared_ptr<Wall>> _walls;
			std::vector<std::shared_ptr<Prop>> _props;
		};
	}
}

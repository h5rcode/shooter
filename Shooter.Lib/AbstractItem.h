#pragma once

#include <memory>

#include "BoundingBox.h"
#include "IItem.h"
#include "Vector2.h"

using namespace Shooter::Math;
using namespace Shooter::World;

namespace Shooter {
	namespace Items {
		class AbstractItem : public IItem {
		protected:
			AbstractItem(
				std::string id,
				std::string name,
				int weight,
				Vector2 position,
				int width,
				int height,
				double orientation);

		public:
			BoundingBox & getBoundingBox() override;
			int getHeight() const override;
			std::string& getId() override;
			Vector2 & getPosition() override;
			std::string& getName() override;
			double getOrientation() const;
			int getWeight() const override;
			int getWidth() const override;
			virtual void setSelected(bool selected) override;

		private:
			std::string _id;
			int _width;
			int _height;
			std::string _name;
			int _weight;
			BoundingBox _boundingBox;
			double _orientation;
			Vector2 _position;
			bool _selected;
		};
	}
}
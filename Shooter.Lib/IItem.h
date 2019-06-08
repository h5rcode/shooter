#pragma once

#include <string>

#include "BoundingBox.h"

using namespace Shooter::Math;
using namespace Shooter::World;

namespace Shooter {
	namespace Items {
		class IItem
		{
		public:
			virtual BoundingBox& getBoundingBox() = 0;
			virtual int getHeight() const = 0;
			virtual std::string& getId() = 0;
			virtual std::string& getName() = 0;
			virtual double getOrientation() const = 0;
			virtual Vector2& getPosition() = 0;
			virtual int getWeight() const = 0;
			virtual int getWidth() const = 0;
			virtual void setSelected(bool selected) = 0;
		};
	}
}
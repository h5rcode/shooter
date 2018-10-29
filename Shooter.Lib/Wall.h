#pragma once

#include <string>

#include "BoundingBox.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Wall {
		public:
			Wall(Vector2 position, int width, int length, double orientation, std::string texture);
		public:
			BoundingBox& getBoundingBox();
			Vector2& getPosition();
			int getWidth() const;
			int getLength() const;
			double getOrientation() const;
			std::string& getTexture();
		private:
			BoundingBox _boundingBox;
			Vector2 _position;
			int _width;
			int _length;
			double _orientation;
			std::string _texture;
		};
	}
}
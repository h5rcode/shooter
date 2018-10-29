#pragma once

#include <string>

#include "BoundingBox.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Prop {
		public:
			Prop(Vector2 position, int width, int height, double orientation, std::string texture);
		public:
			BoundingBox & getBoundingBox();
			int getHeight() const;
			double getOrientation() const;
			Vector2& getPosition();
			std::string& getTexture();
			int getWidth() const;
			bool isSelected() const;
			void setOrientation(double orientation);
			void setPosition(Vector2& position);
			void setSelected(bool selected);
		private:
			void resetBoundingBox();
		private:
			int _width;
			int _height;
			BoundingBox _boundingBox;
			double _orientation;
			Vector2 _position;
			bool _selected;
			std::string _texture;
		};
	}
}
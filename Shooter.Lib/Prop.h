#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "BoundingBox.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Prop {
		public:
			Prop(Vector2 position, int width, int height, double orientation, sf::Texture& texture);
		public:
			BoundingBox & getBoundingBox();
			Vector2& getPosition();
			void setOrientation(double orientation);
			void setPosition(Vector2& position);
			void setSelected(bool selected);
			void render(sf::RenderWindow& renderWindow);
		private:
			void resetBoundingBox();
		private:
			int _width;
			int _height;
			BoundingBox _boundingBox;
			double _orientation;
			Vector2 _position;
			bool _selected;
			sf::Sprite _sprite;
		};
	}
}
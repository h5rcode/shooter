#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Projection.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class BoundingBox {
		public:
			BoundingBox(Vector2& position, int width, int height, double orientation);

		public:
			int getHeight() const;
			std::vector<std::shared_ptr<Vector2>>& getNormals();
			int getWidth() const;
			bool intersects(BoundingBox& boundingBox) const;
			Projection project(Vector2& axis) const;
			void render(sf::RenderWindow& window);

		private:
			int _height;
			int _width;
			std::vector<std::shared_ptr<Vector2>> _vertices;
			std::vector<std::shared_ptr<Vector2>> _normals;
		};
	}
}
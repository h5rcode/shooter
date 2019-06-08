#pragma once

#include <SFML/Graphics.hpp>

#include "IBoundingBoxRenderer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class BoundingBoxRenderer : public IBoundingBoxRenderer {
			public:
				BoundingBoxRenderer(sf::RenderWindow& renderWindow);
			public:
				void render(BoundingBox& boundingBox);

			private:
				sf::RenderWindow& _renderWindow;
				sf::VertexArray _vertexArray;
			};
		}
	}
}
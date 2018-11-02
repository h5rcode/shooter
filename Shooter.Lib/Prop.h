#pragma once

#include <string>

#include "BoundingBox.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Prop {
		public:
			Prop(std::string id, std::string name, Vector2 position, int width, int height, double orientation);
		public:
			BoundingBox & getBoundingBox();
			int getHeight() const;
			std::string& getId();
			std::string& getName();
			double getOrientation() const;
			Vector2& getPosition();
			int getWidth() const;
			bool isSelected() const;
			void setOrientation(double orientation);
			void setPosition(Vector2& position);
			void setSelected(bool selected);

		private:
			void resetBoundingBox();

		private:
			std::string _id;
			int _width;
			int _height;
			BoundingBox _boundingBox;
			std::string _name;
			double _orientation;
			Vector2 _position;
			bool _selected;
		};
	}
}
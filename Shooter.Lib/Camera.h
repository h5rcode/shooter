#pragma once

#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Camera {
		public:
			Camera(int viewWidth, int viewHeight);
			Vector2 getPosition() const;
			void setPosition(Vector2 position);
			int getViewWidth() const;
			int getViewHeight() const;
		private:
			Vector2 _position;
			int _viewWidth;
			int _viewHeight;
		};
	}
}
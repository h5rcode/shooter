#pragma once

#include "Event.h"

namespace Shooter {
	namespace Input {
		typedef enum Key {
			DOWN,
			LEFT,
			RIGHT,
			UP
		} Key;

		class IInputManager
		{
		public:
			virtual void getMouseState(double& mouseX, double& mouseY) = 0;
			virtual bool isKeyDown(Key key) = 0;
			virtual bool pollEvent(Event& event) = 0;
		};
	}
}
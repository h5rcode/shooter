#pragma once

#include <SFML/Window.hpp>

namespace Shooter {
	namespace Input {
		class IInputManager
		{
		public:
			virtual void getMouseState(double& mouseX, double& mouseY) = 0;
			virtual bool pollEvent(sf::Event& event) = 0;
		};
	}
}
#pragma once

#include <SFML/Graphics.hpp>

#include "IInputManager.h"

namespace Shooter {
	namespace Input {
		class SfmlInputManager : public IInputManager
		{
		public:
			SfmlInputManager(sf::RenderWindow &window);

			void getMouseState(double& mouseX, double& mouseY);
			bool pollEvent(sf::Event& event);

		private:
			sf::RenderWindow& _window;
		};
	}
}
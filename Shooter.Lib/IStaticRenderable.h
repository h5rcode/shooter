#pragma once

#include <SFML/Graphics.hpp>

class IStaticRenderable {
public:
	virtual void render(sf::RenderWindow& renderWindow) = 0;
};
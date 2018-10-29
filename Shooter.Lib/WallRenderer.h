#pragma once

#include <SFML/Graphics.hpp>

#include "IResourceManager.h"
#include "IWallRenderer.h"

using namespace Shooter::World;
using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;

class WallRenderer : public IWallRenderer {
public:
	WallRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager);

public:
	void render(Wall& wall);

private:
	sf::RenderWindow& _renderWindow;
	IResourceManager& _resourceManager;
};
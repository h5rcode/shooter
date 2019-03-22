#pragma once

#include <SFML/Graphics.hpp>

#include "IResourceManager.h"
#include "IFloorRenderer.h"

using namespace Shooter::World;
using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;

class FloorRenderer : public IFloorRenderer {
public:
	FloorRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager);

public:
	void render(Floor& floor);

private:
	sf::RenderWindow& _renderWindow;
	IResourceManager& _resourceManager;
};
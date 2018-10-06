#pragma once

#include "IResourceManager.h"
#include "IStaticRenderable.h"
#include "Vector2.h"

class StaticRenderable : public IStaticRenderable {
public:
	StaticRenderable(
		Vector2 position,
		int width,
		int height,
		double orientation,
		IResourceManager& resourceManager,
		std::string& filename);

public:
	void render(sf::RenderWindow& renderWindow) override;

private:
	int _width;
	int _height;
	Vector2 _position;
	double _orientation;
	IResourceManager& _resourceManager;
	sf::Sprite _sprite;
};
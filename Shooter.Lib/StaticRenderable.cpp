#include "StaticRenderable.h"

StaticRenderable::StaticRenderable(
	Vector2 position,
	int width,
	int height,
	double orientation,
	IResourceManager& resourceManager,
	std::string& filename) :
	_width(width),
	_height(height),
	_position(position),
	_orientation(orientation),
	_resourceManager(resourceManager)
{
	sf::Texture* texture = resourceManager.getTexture(filename);

	sf::Vector2u textureSize = texture->getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)_width / textureWidth, (float)_height / textureHeight);

	_sprite.setPosition((float)_position.x, (float)_position.y);
	_sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	_sprite.setRotation((float)_orientation);
	_sprite.setScale(spriteScale);
	_sprite.setTexture(*texture);
}

void StaticRenderable::render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_sprite);
}
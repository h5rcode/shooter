#include "PropRenderer.h"

using namespace Shooter::Rendering::Renderers;

PropRenderer::PropRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager) :
	_renderWindow(renderWindow),
	_resourceManager(resourceManager)
{
}

void PropRenderer::render(Prop& prop) {

	sf::Texture* texture = _resourceManager.getTexture(prop.getTexture());
	int width = prop.getWidth();
	int height = prop.getHeight();

	sf::Vector2u textureSize = texture->getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)width / textureWidth, (float)height / textureHeight);

	Vector2& position = prop.getPosition();
	double orientation = prop.getOrientation();

	sf::Sprite sprite;
	sprite.setPosition((float)position.x, (float)position.y);
	sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	sprite.setRotation((float)orientation);
	sprite.setScale(spriteScale);
	sprite.setTexture(*texture);

	_renderWindow.draw(sprite);
}
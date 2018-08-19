#include "AbstractItem.h"

AbstractItem::AbstractItem(int weight, Vector2 position, int width, int height, double orientation, std::string& texture) :
	_weight(weight),
	_orientation(orientation),
	_position(position),
	_width(width),
	_height(height),
	_selected(false),
	_sprite(),
	_texture(),
	_boundingBox(position, width, height, orientation)
{
	_texture.loadFromFile(texture);

	sf::Vector2u textureSize = _texture.getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)_width / textureWidth, (float)_height / textureHeight);

	_sprite.setPosition((float)_position.x, (float)_position.y);
	_sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	_sprite.setRotation((float)_orientation);
	_sprite.setScale(spriteScale);
	_sprite.setTexture(_texture);
}

BoundingBox & AbstractItem::getBoundingBox()
{
	return _boundingBox;
}

int AbstractItem::getWeight() const
{
	return _weight;
}

void AbstractItem::render(sf::RenderWindow& renderWindow) {
	renderWindow.draw(_sprite);

	if (_selected) {
		_boundingBox.render(renderWindow);
	}
}

void AbstractItem::setSelected(bool selected)
{
	_selected = selected;
}

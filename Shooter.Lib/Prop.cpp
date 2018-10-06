#include "Prop.h"

Prop::Prop(Vector2 position, int width, int height, double orientation, sf::Texture& texture) :
	_orientation(orientation),
	_position(position),
	_width(width),
	_height(height),
	_selected(false),
	_sprite(),
	_boundingBox(position, width, height, orientation)
{
	sf::Vector2u textureSize = texture.getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)_width / textureWidth, (float)_height / textureHeight);

	_sprite.setPosition((float)_position.x, (float)_position.y);
	_sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	_sprite.setRotation((float)_orientation);
	_sprite.setScale(spriteScale);
	_sprite.setTexture(texture);
}

BoundingBox& Prop::getBoundingBox()
{
	return _boundingBox;
}

Vector2 & Prop::getPosition()
{
	return _position;
}

void Prop::render(sf::RenderWindow& renderWindow) {
	renderWindow.draw(_sprite);

	if (_selected) {
		_boundingBox.render(renderWindow);
	}
}

void Prop::resetBoundingBox()
{
	_boundingBox = BoundingBox(_position, _width, _height, _orientation);
}

void Prop::setOrientation(double orientation) {
	_orientation = orientation;
	_sprite.setRotation((float)_orientation);
	resetBoundingBox();
}

void Prop::setPosition(Vector2& position) {
	_position = position;
	_sprite.setPosition((float)_position.x, (float)_position.y);
	resetBoundingBox();
}

void Prop::setSelected(bool selected) {
	_selected = selected;
}
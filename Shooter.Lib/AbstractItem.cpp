#include "AbstractItem.h"

using namespace Shooter::Items;
using namespace Shooter::Math;
using namespace Shooter::World;

AbstractItem::AbstractItem(
	std::string id,
	std::string name,
	int weight,
	Vector2 position,
	int width,
	int height,
	double orientation) :
	_id(id),
	_name(name),
	_weight(weight),
	_orientation(orientation),
	_position(position),
	_width(width),
	_height(height),
	_selected(false),
	_boundingBox(position, width, height, orientation)
{
}

BoundingBox & AbstractItem::getBoundingBox()
{
	return _boundingBox;
}

int AbstractItem::getHeight() const {
	return _height;
}

std::string& AbstractItem::getId() {
	return _id;
}

std::string& AbstractItem::getName() {
	return _name;
}

double AbstractItem::getOrientation() const {
	return _orientation;
}

Vector2 & AbstractItem::getPosition() {
	return _position;
}

int AbstractItem::getWeight() const
{
	return _weight;
}

int AbstractItem::getWidth() const {
	return _width;
}

void AbstractItem::setSelected(bool selected)
{
	_selected = selected;
}

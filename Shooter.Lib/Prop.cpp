#include "Prop.h"

using namespace Shooter::Math;
using namespace Shooter::World;

Prop::Prop(std::string id, std::string name, Vector2 position, int width, int height, double orientation) :
	_id(id),
	_name(name),
	_orientation(orientation),
	_position(position),
	_width(width),
	_height(height),
	_selected(false),
	_boundingBox(position, width, height, orientation)
{
}

BoundingBox& Prop::getBoundingBox()
{
	return _boundingBox;
}

int Prop::getHeight() const {
	return _height;
}

std::string& Prop::getId() {
	return _id;
}

std::string& Prop::getName() {
	return _name;
}

double Prop::getOrientation() const {
	return _orientation;
}

Vector2 & Prop::getPosition()
{
	return _position;
}

int Prop::getWidth() const {
	return _width;
}

bool Prop::isSelected() const {
	return _selected;
}

void Prop::resetBoundingBox()
{
	_boundingBox = BoundingBox(_position, _width, _height, _orientation);
}

void Prop::setOrientation(double orientation) {
	_orientation = orientation;
	resetBoundingBox();
}

void Prop::setPosition(Vector2& position) {
	_position = position;
	resetBoundingBox();
}

void Prop::setSelected(bool selected) {
	_selected = selected;
}
#include "AbstractItem.h"

using namespace Shooter::Items;
using namespace Shooter::Math;
using namespace Shooter::Rendering::Renderables;
using namespace Shooter::World;

AbstractItem::AbstractItem(
	std::string name,
	int weight,
	Vector2 position,
	int width,
	int height,
	double orientation,
	std::shared_ptr<IStaticRenderable> staticRenderable) :
	_name(name),
	_weight(weight),
	_orientation(orientation),
	_position(position),
	_width(width),
	_height(height),
	_selected(false),
	_staticRenderable(staticRenderable),
	_boundingBox(position, width, height, orientation)
{
}

BoundingBox & AbstractItem::getBoundingBox()
{
	return _boundingBox;
}

std::string& AbstractItem::getName() {
	return _name;
}

Vector2 & AbstractItem::getPosition() {
	return _position;
}

int AbstractItem::getWeight() const
{
	return _weight;
}

void AbstractItem::render(sf::RenderWindow& renderWindow)
{
	_staticRenderable->render(renderWindow);

	if (_selected) {
		_boundingBox.render(renderWindow);
	}
}

void AbstractItem::setSelected(bool selected)
{
	_selected = selected;
}

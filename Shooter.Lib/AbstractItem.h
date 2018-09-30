#pragma once

#include <memory>

#include "BoundingBox.h"
#include "IItem.h"
#include "IStaticRenderable.h"
#include "Vector2.h"

class AbstractItem : public IItem {
protected:
	AbstractItem(int weight, Vector2 position, int width, int height, double orientation, std::shared_ptr<IStaticRenderable> staticRenderable);

public:
	BoundingBox & getBoundingBox() override;
	Vector2 & getPosition() override;
	int getWeight() const override;
	void render(sf::RenderWindow& renderWindow) override;
	virtual void setSelected(bool selected) override;

private:
	int _width;
	int _height;
	int _weight;
	BoundingBox _boundingBox;
	double _orientation;
	Vector2 _position;
	bool _selected;
	std::shared_ptr<IStaticRenderable> _staticRenderable;
};
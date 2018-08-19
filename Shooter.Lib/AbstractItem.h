#pragma once

#include "BoundingBox.h"
#include "IItem.h"
#include "Vector2.h"

class AbstractItem : public IItem {
protected:
	AbstractItem(int weight, Vector2 position, int width, int height, double orientation, std::string& texture);

public:
	BoundingBox & getBoundingBox() override;
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
	sf::Sprite _sprite;
	sf::Texture _texture;
};
#pragma once

#include "Vector2.h"

class Camera {
public:
	Camera();
	Vector2 getPosition() const;
	void setPosition(Vector2 position);
	int getViewWidth() const;
	int getViewHeight() const;
private:
	Vector2 _position;
	int _viewWidth;
	int _viewHeight;
};
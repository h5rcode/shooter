#include "Camera.h"

Camera::Camera() :
	_viewWidth(800),
	_viewHeight(600)
{
}

Vector2 Camera::getPosition() const
{
	return _position;
}

int Camera::getViewWidth() const
{
	return _viewWidth;
}

int Camera::getViewHeight() const
{
	return _viewHeight;
}

void Camera::setPosition(Vector2 position)
{
	_position.x = position.x;
	_position.y = position.y;
}
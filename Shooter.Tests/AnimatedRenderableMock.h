#pragma once

#include "gmock/gmock.h"

#include "AnimatedRenderable.h"

class AnimatedRenderableMock : public AnimatedRenderable {
public:
	AnimatedRenderableMock();
public:
	MOCK_METHOD0(play, void());
	MOCK_METHOD0(pause, void());
	MOCK_METHOD1(render, void(sf::RenderWindow& renderWindow));
	MOCK_METHOD1(setRotation, void(double rotation));
	MOCK_METHOD2(setPosition, void(double x, double y));
	MOCK_METHOD1(update, void(sf::Time elapsedTime));
};

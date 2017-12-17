#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "BoundingBox.h"
#include "IWeapon.h"
#include "Vector2.h"

typedef enum CharacterState {
	IDLE,
	ATTACKING
} CharacterState;

class Player
{
public:
	Player(Vector2 position);

	bool canAttack() const;
	BoundingBox getBoundingBox(sf::Time elapsedTime);
	std::shared_ptr<IWeapon> getEquipedWeapon() const;
	double getOrientation();
	Vector2 computePosition(sf::Time elapsedTime);
	Vector2& getPosition();
	const Vector2& getSpeed();
	void immobilize();
	void move(sf::Time elapsedTime);
	void pointAt(Vector2& position);
	void render(sf::RenderWindow& renderWindow);
	void setAcceleration(Vector2& acceleration);
	void setEquipedWeapon(std::shared_ptr<IWeapon> weapon);
	void setMaxSpeed(double maxSpeed);

private:
	Vector2 computeSpeed(sf::Time elapsedTime);

private:
	double _friction;
	double _maxSpeed;
	Vector2 _acceleration;
	Vector2 _speed;
	Vector2 _position;
	double _orientation;

	sf::Texture _texture;
	Animation _animation;
	AnimatedSprite _animatedSprite;

	std::shared_ptr<IWeapon> _equipedWeapon;

	CharacterState _state;
};


#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "IWeapon.h"
#include "Vector2.h"

typedef enum CharacterState {
	IDLE,
	ATTACKING
} CharacterState;

class Player
{
public:
	Player();

	bool canAttack() const;
	IWeapon* getEquipedWeapon() const;
	double getOrientation();
	Vector2 computePosition(sf::Time elapsedTime);
	Vector2& getPosition();
	void move(sf::Time elapsedTime);
	void pointAt(Vector2& position);
	void render(sf::RenderWindow& renderWindow);
	void setAcceleration(Vector2& acceleration);
	void setEquipedWeapon(IWeapon* weapon);
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

	IWeapon* _equipedWeapon;

	CharacterState _state;
};


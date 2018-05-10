#pragma once

#include <memory>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "BoundingBox.h"
#include "Inventory.h"
#include "IWeapon.h"
#include "Prop.h"
#include "Vector2.h"

typedef enum CharacterState {
	IDLE,
	ATTACKING
} CharacterState;

class Player
{
public:
	Player(Vector2 position);

public:
	std::vector<std::shared_ptr<Projectile>> attackToward(Vector2& position);
	bool canAttack() const;
	Vector2 computePosition(sf::Time elapsedTime);
	std::shared_ptr<Prop> dropProp();
	void equipWeapon(std::shared_ptr<IWeapon> weapon);
	BoundingBox getBoundingBox(sf::Time elapsedTime);
	std::shared_ptr<IWeapon> getEquipedWeapon() const;
	double getOrientation();
	Vector2& getPosition();
	std::shared_ptr<Prop> getProp();
	const Vector2& getSpeed();
	void immobilize();
	void move(sf::Time elapsedTime);
	bool pickUpProp(std::shared_ptr<Prop> prop);
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
	double _reach;
	Vector2 _acceleration;
	Vector2 _speed;
	Vector2 _position;
	double _orientation;

	sf::Sound _sound;
	sf::SoundBuffer _soundBuffer;

	sf::Texture _texture;
	Animation _animation;
	AnimatedSprite _animatedSprite;

	std::shared_ptr<IWeapon> _equipedWeapon;
	std::shared_ptr<Prop> _prop;

	Inventory _inventory;

	CharacterState _state;
};


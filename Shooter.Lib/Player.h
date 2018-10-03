#pragma once

#include <memory>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "BoundingBox.h"
#include "IAnimatedRenderable.h"
#include "IInventory.h"
#include "IItem.h"
#include "IPlayer.h"
#include "IWeapon.h"
#include "Prop.h"
#include "Vector2.h"

typedef enum CharacterState {
	IDLE,
	ATTACKING
} CharacterState;

class Player : public IPlayer
{
public:
	Player(Vector2 position, int hitpoints, IAnimatedRenderable& animatedRenderable, IInventory& inventory);

public:
	std::vector<std::shared_ptr<Projectile>> attackToward(Vector2& position);
	bool canAttack() const;
	Vector2 computePosition(sf::Time elapsedTime);
	std::shared_ptr<Prop> dropProp();
	void equipWeapon(std::shared_ptr<IWeapon> weapon);
	BoundingBox getBoundingBox(sf::Time elapsedTime);
	std::shared_ptr<IWeapon> getEquipedWeapon() const;
	int getHitpoints() const;
	double getOrientation();
	Vector2& getPosition();
	std::shared_ptr<Prop> getProp();
	const Vector2& getSpeed();
	void hurt(int damage);
	void immobilize();
	void move(sf::Time elapsedTime);
	bool pickUpItem(std::shared_ptr<IItem> item);
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
	int _hitpoints;
	double _maxSpeed;
	double _reach;
	Vector2 _acceleration;
	Vector2 _speed;
	Vector2 _position;
	double _orientation;

	sf::Sound _sound;
	sf::SoundBuffer _soundBuffer;

	IAnimatedRenderable& _animatedRenderable;

	std::shared_ptr<IWeapon> _equipedWeapon;
	std::shared_ptr<Prop> _prop;

	IInventory& _inventory;

	CharacterState _state;
};


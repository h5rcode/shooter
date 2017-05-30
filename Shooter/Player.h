#pragma once

#include <string>

#include "IWeapon.h"
#include "Vector2.h"

typedef enum CharacterState {
	IDLE,
	ATTACKING
} CharacterState;

class Player
{
public:
	Player(std::string& texture);

	bool canAttack() const;
	IWeapon* getEquipedWeapon() const;
	double getOrientation();
	Vector2& getPosition();
	std::string& getTexture();
	void move(int elapsedMs);
	void pointAt(Vector2& position);
	void setAcceleration(Vector2& acceleration);
	void setEquipedWeapon(IWeapon* weapon);
	void setMaxSpeed(double maxSpeed);

private:
	double _friction;
	double _maxSpeed;
	Vector2 _acceleration;
	Vector2 _speed;
	Vector2 _position;
	double _orientation;

	std::string& _texture;

	IWeapon* _equipedWeapon;

	CharacterState _state;
};


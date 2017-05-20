#pragma once

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
	void move(int elapsedMs);
	void setAcceleration(Vector2& acceleration);
	void setEquipedWeapon(IWeapon* weapon);
	void setMaxSpeed(double maxSpeed);

private:
	double _friction;
	double _maxSpeed;
	Vector2 _acceleration;
	Vector2 _speed;
	Vector2 _position;

	IWeapon* _equipedWeapon;

	CharacterState _state;
};


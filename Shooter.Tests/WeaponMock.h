#pragma once

#include "gmock/gmock.h"

#include "IWeapon.h"

using namespace Shooter::Math;

class WeaponMock : public IWeapon {
public:
	MOCK_CONST_METHOD0(canAttack, bool());
	MOCK_METHOD2(fire, std::vector<std::shared_ptr<Projectile>>(Vector2& initialPosition, Vector2& targetPosition));
	MOCK_METHOD0(getDescription, std::string());
};
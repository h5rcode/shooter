#pragma once

#include "FirearmDescriptor.h"
#include "WeaponType.h"

struct WeaponDescriptor {
	WeaponType weaponType;

	union {
		FirearmDescriptor firearm;
	};
};

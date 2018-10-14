#include "PlayerInitialStateDescriptor.h"

using namespace Shooter::LevelDescriptors;
using namespace Shooter::Math;

Vector2 PlayerInitialStateDescriptor::getPosition() {
	return Vector2(this->x, this->y);
}
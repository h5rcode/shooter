#pragma once

#include "Projectile.h"

using namespace Shooter::Items::Weapons;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IProjectileRenderer {
			public:
				virtual void render(Projectile& projectile) = 0;
			};
		}
	}
}
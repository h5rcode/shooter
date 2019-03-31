#pragma once

#include "INonPlayingCharacter.h"

using namespace Shooter::Npcs;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class INonPlayingCharacterRenderer {
			public:
				virtual void render(INonPlayingCharacter& npc) = 0;
			};
		}
	}
}
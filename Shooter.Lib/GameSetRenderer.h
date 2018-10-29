#pragma once

#include "IGameSetRenderer.h"
#include "IItemRenderer.h"
#include "IPropRenderer.h"
#include "IWallRenderer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class GameSetRenderer : public IGameSetRenderer {
			public:
				GameSetRenderer(IItemRenderer& itemRenderer, IPropRenderer& propRenderer, IWallRenderer& wallRenderer);
			public:
				void render(IGameSet& gameSet) const;
			private:
				IItemRenderer& _itemRenderer;
				IPropRenderer& _propRenderer;
				IWallRenderer& _wallRenderer;
			};
		}
	}
}
#pragma once

#include "IFloorRenderer.h"
#include "IGameSetRenderer.h"
#include "IItemRenderer.h"
#include "IPropRenderer.h"
#include "IWallRenderer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class GameSetRenderer : public IGameSetRenderer {
			public:
				GameSetRenderer(
					IFloorRenderer& floorRenderer,
					IItemRenderer& itemRenderer,
					IPropRenderer& propRenderer,
					IWallRenderer& wallRenderer);
			public:
				void render(IGameSet& gameSet) const;
			private:
				IFloorRenderer& _floorRenderer;
				IItemRenderer& _itemRenderer;
				IPropRenderer& _propRenderer;
				IWallRenderer& _wallRenderer;
			};
		}
	}
}
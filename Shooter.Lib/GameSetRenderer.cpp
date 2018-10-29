#include "GameSetRenderer.h"

using namespace Shooter::Rendering::Renderers;

GameSetRenderer::GameSetRenderer(IItemRenderer& itemRenderer, IPropRenderer& propRenderer, IWallRenderer& wallRenderer) :
	_itemRenderer(itemRenderer),
	_propRenderer(propRenderer),
	_wallRenderer(wallRenderer) {
}

void GameSetRenderer::render(IGameSet& gameSet) const {
	std::vector<std::shared_ptr<IItem>>& items = gameSet.getItems();
	for (std::vector<std::shared_ptr<IItem>>::iterator it = items.begin(); it != items.end(); ++it)
	{
		std::shared_ptr<IItem> item = *it;
		_itemRenderer.render(*item);
	}

	std::vector<std::shared_ptr<Wall>>& walls = gameSet.getWalls();
	for (std::vector<std::shared_ptr<Wall>>::iterator it = walls.begin(); it != walls.end(); ++it)
	{
		std::shared_ptr<Wall> wall = *it;
		_wallRenderer.render(*wall);
	}

	std::vector<std::shared_ptr<Prop>>& props = gameSet.getProps();
	for (std::vector<std::shared_ptr<Prop>>::iterator it = props.begin(); it != props.end(); ++it)
	{
		std::shared_ptr<Prop> prop = *it;
		_propRenderer.render(*prop);
	}
}

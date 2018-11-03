#include "ItemRenderer.h"

using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;

ItemRenderer::ItemRenderer(IItemDatabase& itemDatabase, sf::RenderWindow& renderWindow, IResourceManager& resourceManager) :
	_itemDatabase(itemDatabase),
	_renderWindow(renderWindow),
	_resourceManager(resourceManager)
{
}

void ItemRenderer::render(IItem& item) {
	std::shared_ptr<ItemDescriptor> itemDescriptor = _itemDatabase.getItem(item.getId());
	sf::Texture* texture = _resourceManager.getTexture(itemDescriptor->texture);

	sf::Vector2u textureSize = texture->getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)item.getWidth() / textureWidth, (float)item.getHeight() / textureHeight);

	Vector2& position = item.getPosition();

	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setPosition((float)position.x, (float)position.y);
	sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	sprite.setRotation((float)item.getOrientation());
	sprite.setScale(spriteScale);

	_renderWindow.draw(sprite);
}
#include "NonPlayingCharacterRenderer.h"

using namespace Shooter::Rendering::Renderers;

NonPlayingCharacterRenderer::NonPlayingCharacterRenderer(
	INonPlayingCharacterDatabase& npcDatabase,
	sf::RenderWindow& renderWindow,
	IResourceManager& resourceManager) :
	_npcDatabase(npcDatabase),
	_renderWindow(renderWindow),
	_resourceManager(resourceManager) {}

void NonPlayingCharacterRenderer::render(INonPlayingCharacter& npc) {

	NonPlayingCharacterDescriptor& npcDescriptor = _npcDatabase.getNpc(npc.getId());
	sf::Texture* texture = _resourceManager.getTexture(npcDescriptor.texture);
	Vector2& position = npc.getPosition();

	sf::Vector2u textureSize = texture->getSize();

	_sprite.setTexture(*texture);
	_sprite.setPosition((float)position.x, (float)position.y);
	_sprite.setRotation((float)npc.getOrientation());
	_sprite.setOrigin((float)(textureSize.x / 2), (float)(textureSize.y / 2));
	_renderWindow.draw(_sprite);
}
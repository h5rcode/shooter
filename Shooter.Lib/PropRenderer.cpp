#include "PropDescriptor.h"
#include "PropRenderer.h"

using namespace Shooter::Rendering::Renderers;

PropRenderer::PropRenderer(
	IBoundingBoxRenderer& boundingBoxRenderer,
	IPropDatabase& propDatabase,
	RenderingOptions& renderingOptions,
	sf::RenderWindow& renderWindow,
	IResourceManager& resourceManager) :
	_boundingBoxRenderer(boundingBoxRenderer),
	_propDatabase(propDatabase),
	_renderingOptions(renderingOptions),
	_renderWindow(renderWindow),
	_resourceManager(resourceManager)
{
}

void PropRenderer::render(Prop& prop)
{
	PropDescriptor& propDescriptor = _propDatabase.getProp(prop.getId());
	sf::Texture* texture = _resourceManager.getTexture(propDescriptor.texture);
	int width = prop.getWidth();
	int height = prop.getHeight();

	sf::Vector2u textureSize = texture->getSize();
	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;

	sf::Vector2f spriteScale = sf::Vector2f((float)width / textureWidth, (float)height / textureHeight);

	Vector2& position = prop.getPosition();
	double orientation = prop.getOrientation();

	sf::Sprite sprite;
	sprite.setPosition((float)position.x, (float)position.y);
	sprite.setOrigin(textureWidth / 2, textureHeight / 2);
	sprite.setRotation((float)orientation);
	sprite.setScale(spriteScale);
	sprite.setTexture(*texture);

	_renderWindow.draw(sprite);

	if (_renderingOptions.DrawBoundingBoxes) {
		BoundingBox& boundingBox = prop.getBoundingBox();
		_boundingBoxRenderer.render(boundingBox);
	}
}
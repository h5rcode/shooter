#include "ProjectileRenderer.h"

using namespace Shooter::Rendering::Renderers;

ProjectileRenderer::ProjectileRenderer(sf::RenderWindow& renderWindow, sf::Texture& texture) :
	_renderWindow(renderWindow) {
	_sprite.setTexture(texture);
}

void ProjectileRenderer::render(Projectile& projectile) {

	int width = projectile.getWidth();
	int height = projectile.getHeight();

	_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	_sprite.setOrigin(width / 2.f, height / 2.f);

	Vector2& position = projectile.getPosition();
	double orientation = projectile.getOrientation();

	_sprite.setPosition((float)position.x, (float)position.y);
	_sprite.setRotation((float)orientation);

	_renderWindow.draw(_sprite);
}
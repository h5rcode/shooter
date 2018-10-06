#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class IResourceManager {
public:
	virtual sf::Font* getFont(const std::string& filename) = 0;
	virtual sf::SoundBuffer* getSoundBuffer(const std::string& filename) = 0;
	virtual sf::Texture* getTexture(const std::string& filename) = 0;
};

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
	for (auto& it : _fonts)
	{
		delete it.second;
	}

	for (auto& it : _soundBuffers)
	{
		delete it.second;
	}

	for (auto& it : _textures)
	{
		delete it.second;
	}
}

sf::Font* ResourceManager::getFont(const std::string& filename) {
	const auto& it = _fonts.find(filename);

	if (it == _fonts.end()) {
		sf::Font* font = new sf::Font();
		font->loadFromFile(filename);

		_fonts[filename] = font;

		return font;
	}

	return it->second;
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(const std::string& filename) {
	const auto& it = _soundBuffers.find(filename);

	if (it == _soundBuffers.end()) {
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		soundBuffer->loadFromFile(filename);

		_soundBuffers[filename] = soundBuffer;

		return soundBuffer;
	}

	return it->second;
}

sf::Texture* ResourceManager::getTexture(const std::string& filename) {
	const auto& it = _textures.find(filename);

	if (it == _textures.end()) {
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(filename);

		_textures[filename] = texture;

		return texture;
	}

	return it->second;
}
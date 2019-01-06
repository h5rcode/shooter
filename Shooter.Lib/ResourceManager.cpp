
#include "ResourceManager.h"

const std::string TEXTURES_PATH = "Resources/textures/";
const std::string SOUND_PATH = "Resources/sounds/";

using namespace Shooter::Rendering;

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
	std::string filepath = SOUND_PATH + filename;
	const auto& it = _soundBuffers.find(filepath);

	if (it == _soundBuffers.end()) {
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		soundBuffer->loadFromFile(filepath);

		_soundBuffers[filepath] = soundBuffer;

		return soundBuffer;
	}

	return it->second;
}

sf::Texture* ResourceManager::getTexture(const std::string& filename) {
	std::string filepath = TEXTURES_PATH + filename;
	const auto& it = _textures.find(filepath);

	if (it == _textures.end()) {
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(filepath);
		texture->setSmooth(true);

		_textures[filepath] = texture;

		return texture;
	}

	return it->second;
}
void ResourceManager::loadFont(const std::string& filename) {
	const auto& it = _fonts.find(filename);

	if (it != _fonts.end()) {
		throw std::runtime_error("The font '" + filename + "' is already loaded.");
	}

	sf::Font* font = new sf::Font();
	font->loadFromFile(filename);

	_fonts[filename] = font;
}

void ResourceManager::loadSoundBuffer(const std::string& filename) {
	std::string filepath = SOUND_PATH + filename;
	const auto& it = _soundBuffers.find(filepath);

	if (it != _soundBuffers.end()) {
		throw std::runtime_error("The sound buffer '" + filename + "' is already loaded.");
	}

	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	soundBuffer->loadFromFile(filepath);

	_soundBuffers[filepath] = soundBuffer;
}

void ResourceManager::loadTexture(const std::string& filename) {
	std::string filepath = TEXTURES_PATH + filename;
	const auto& it = _textures.find(filepath);

	if (it != _textures.end()) {
		throw std::runtime_error("The texture '" + filename + "' is already loaded.");
	}

	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(filepath);
	texture->setSmooth(true);

	_textures[filepath] = texture;
}
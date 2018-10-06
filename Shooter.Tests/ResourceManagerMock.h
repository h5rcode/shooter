#pragma once

#include "gmock/gmock.h"

#include "IResourceManager.h"

class ResourceManagerMock : public IResourceManager {
public:
	MOCK_METHOD1(getFont, sf::Font*(const std::string& filename));
	MOCK_METHOD1(getSoundBuffer, sf::SoundBuffer*(const std::string& filename));
	MOCK_METHOD1(getTexture, sf::Texture*(const std::string& filename));
};
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace Shooter {
	namespace Rendering {
		class IResourceManager {
		public:
			virtual sf::Font* getFont(const std::string& filename) = 0;
			virtual sf::SoundBuffer* getSoundBuffer(const std::string& filename) = 0;
			virtual sf::Texture* getTexture(const std::string& filename) = 0;

			virtual void loadFont(const std::string& filename) = 0;
			virtual void loadSoundBuffer(const std::string& filename) = 0;
			virtual void loadTexture(const std::string& filename, bool repeated = false) = 0;
		};
	}
}
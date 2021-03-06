#pragma once

#include "IResourceManager.h"

namespace Shooter {
	namespace Rendering {
		class ResourceManager : public IResourceManager {
		public:
			ResourceManager();
			~ResourceManager();

		public:
			sf::Font* getFont(const std::string& filename);
			sf::SoundBuffer* getSoundBuffer(const std::string& filename);
			sf::Texture* getTexture(const std::string& filename);

			void loadFont(const std::string& filename);
			void loadSoundBuffer(const std::string& filename);
			void loadTexture(const std::string& filename, bool repeated = false);

		private:
			std::map<std::string, sf::Font*> _fonts;
			std::map<std::string, sf::SoundBuffer*> _soundBuffers;
			std::map<std::string, sf::Texture*> _textures;
		};
	}
}
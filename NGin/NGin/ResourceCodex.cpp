#include "ResourceCodex.h"

namespace NGin {

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> ResourceCodex::pTextures;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> ResourceCodex::pFonts;
	std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> ResourceCodex::pSoundBuffers;
	std::string ResourceCodex::location = "";

	void ResourceCodex::DestroyUnused()
	{
		DestroyUnusedFrom(pTextures);
		DestroyUnusedFrom(pFonts);
		DestroyUnusedFrom(pSoundBuffers);
	}

}
#include "ResourceCodex.h"

namespace NGin {

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> ResourceCodex::pTextures;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> ResourceCodex::pFonts;
	std::string ResourceCodex::location = "assets/";

	void ResourceCodex::DestroyUnused()
	{
		auto i = pTextures.begin();

		while (i != pTextures.end()) {
			if (i->second.use_count() == 0) { // if nothing points to texture
				i = pTextures.erase(i); // delete texture
			}
			else { i++; } // if i is valid increment
		}
	}

}
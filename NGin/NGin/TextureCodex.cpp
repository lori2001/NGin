#include "TextureCodex.h"

namespace NGin {

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureCodex::pTextures;
	std::string TextureCodex::location;

	std::shared_ptr<sf::Texture> TextureCodex::Acquire(const std::string& name)
	{

		const auto temp = pTextures.find(name); // search for texute with given name
		if (temp != pTextures.end()) { // if something is found
			return temp->second;
		}
		else {
			auto pTex = std::make_shared<sf::Texture>();
			pTex->loadFromFile("assets/" + name);

			pTextures.insert({ name, pTex });
			return pTex;
		}
	}
	void TextureCodex::DestroyUnused()
	{
		auto i = pTextures.begin();

		while (i != pTextures.end()) {
			if (i->second.unique()) { // if nothing points to texture except the codex
				i = pTextures.erase(i); // delete texture
			}
			else { i++; } // if i is valid increment
		}
	}

}
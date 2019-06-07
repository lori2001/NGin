#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace NGin
{
	class TextureCodex
	{
	public:
		// acquires texture either by loading from file or by linking to existing pointer
		static std::shared_ptr<sf::Texture> Acquire(const std::string &name);
		// destorys textures that only point to codex
		static void DestroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location = loc; }
	private:
		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
		static std::string location;
	};
}

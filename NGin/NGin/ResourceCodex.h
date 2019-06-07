#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <type_traits>

namespace NGin
{
	class ResourceCodex
	{
	public:
		// acquires resources either by loading from file or by linking to existing pointer
		template <class Resource>
		static std::shared_ptr<Resource> Acquire(const std::string &name);
		// destorys textures that only point to codex
		static void DestroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location = loc; }
	private:

		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
		static std::unordered_map<std::string, std::shared_ptr<sf::Font>> pFonts;
		static std::string location;
	};
	template<class Resource>
	inline std::shared_ptr<Resource> ResourceCodex::Acquire(const std::string& name)
	{
		std::unordered_map<std::string, std::shared_ptr<Resource>>* pResources;

		/*Implement supported types*/
		if constexpr (std::is_same<Resource, sf::Texture>::value) {
			pResources = &pTextures;
		}
		else if (std::is_same<Resource, sf::Font>::value) {
			pResources = &pFonts;
		}

		auto temp = pResources->find(name); // searches resources for a texture

		if (temp != pResources->end()) { // if something is found
			return temp->second; // return the requested resource
		}
		else {
			auto pTex = std::make_shared<Resource>(); // creates a new texture
			pTex->loadFromFile(location + name); // loads it

			pResources->insert({ name, pTex }); // inserts it inside the proper resource
			return pTex;
		}
	}
}

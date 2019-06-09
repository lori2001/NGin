#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
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

		// destorys all resources that only point nowhere
		static void DestroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location = loc; }
	private:
		// destroys resources form given map that point nowhere
		template <class UnorderedMap>
		static void DestroyUnusedFrom(UnorderedMap map);

	private:
		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
		static std::unordered_map<std::string, std::shared_ptr<sf::Font>> pFonts;
		static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> pSoundBuffers;
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
		else if constexpr (std::is_same<Resource, sf::Font>::value) {
			pResources = &pFonts;
		}
		else if constexpr(std::is_same<Resource, sf::SoundBuffer>::value) {
			pResources = &pSoundBuffers;
		}

		auto temp = pResources->find(name); // searches resources with the given name

		if (temp != pResources->end()) { // if something is found
			return temp->second; // returns the requested resource
		}
		else {
			auto pTex = std::make_shared<Resource>(); // creates a new resource
			pTex->loadFromFile(location + name); // loads it

			pResources->insert({ name, pTex }); // inserts it inside the proper resource map
			return pTex; // returns the requested resource
		}
	}
	template<class UnorderedMap>
	inline void ResourceCodex::DestroyUnusedFrom(UnorderedMap map)
	{
		auto i = map.begin();

		while (i != map.end()) {
			if (i->second.use_count() == 0) { // if nothing points to texture
				i = map.erase(i); // delete texture
			}
			else { i++; } // if i is valid increment
		}
	}
}

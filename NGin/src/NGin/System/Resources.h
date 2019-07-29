#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>

namespace ngin
{
	class Resources
	{
	public:
		// acquires resources either by loading from file or by linking to existing pointer
		static std::shared_ptr<sf::Texture> AcquireTexture(const std::string& name);
		static std::shared_ptr<sf::Font> AcquireFont(const std::string& name);
		static std::shared_ptr<sf::SoundBuffer> AcquireSoundBuffer(const std::string& name);

		// destorys all resources that only point nowhere
		static void DestroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location = loc; }
	private:
		// destroys resources form given map that point nowhere
		template <class UnorderedMap>
		static void DestroyUnusedFrom(UnorderedMap& map);

	private:
		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;
		static std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts_;
		static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers_;
		static std::string location;
	};
	template<class UnorderedMap>
	inline void Resources::DestroyUnusedFrom(UnorderedMap& map)
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

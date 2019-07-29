#include "Resources.h"

namespace ngin {

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resources::textures_;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Resources::fonts_;
	std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> Resources::soundBuffers_;
	std::string Resources::location = "";

	std::shared_ptr<sf::Texture> Resources::AcquireTexture(const std::string& name)
	{
		auto search = textures_.find(location + name); // search

		// if something is found
		if (search != textures_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(location + name);
			textures_.insert({ location + name, texture });
			return texture;
		}
	}

	std::shared_ptr<sf::Font> Resources::AcquireFont(const std::string& name)
	{
		auto search = fonts_.find(location + name); // search

		// if something is found
		if (search != fonts_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto font = std::make_shared<sf::Font>();
			font->loadFromFile(location + name);
			fonts_.insert({ location + name, font });
			return font;
		}
	}

	std::shared_ptr<sf::SoundBuffer> Resources::AcquireSoundBuffer(const std::string& name)
	{
		auto search = soundBuffers_.find(location + name); // search

		// if something is found
		if (search != soundBuffers_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto soundBuffer = std::make_shared<sf::SoundBuffer>();
			soundBuffer->loadFromFile(location + name);
			soundBuffers_.insert({ location + name, soundBuffer });
			return soundBuffer;
		}
	}

	void Resources::DestroyUnused()
	{
		DestroyUnusedFrom(textures_);
		DestroyUnusedFrom(fonts_);
		DestroyUnusedFrom(soundBuffers_);
	}

}
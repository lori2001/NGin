#pragma once
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

namespace NGin::UI {
	class Cursor : public sf::Drawable
	{
	public:
		static void draw(sf::RenderTarget& target);

		// texture of the mouse displayed
		static void setTexture(const sf::Texture& texture);

		// this function returns the position of an element relative to the window
		// the cursor is set to. (needs void followMouse)
		static sf::Vector2f getPosition() { return sprite.getPosition(); }

		// IMPORTANT !!! ALL UI ELEMENTS DEPEND ON THIS FUNCTION!!!
		// updtates cursor's position relative to window
		// based on where the mouse is at at a given frame
		static void followMouse(sf::RenderWindow& window);

		// sets the sound the cursor makes ex. when pressing a button 
		static void setBuffer(sf::SoundBuffer& soundBuffer);

		// plays the sound avoiding sound overlap with multiple clicks
		static void playSound();

	private:
		static sf::Sprite sprite;

		// the sound feedbacks played when mouse presses something
		static sf::Sound sound;
	};
}
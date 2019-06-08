#pragma once
#include "SFML\Graphics.hpp"

namespace NGin::UI
{
	class Cursor : public sf::Sprite
	{
	public:
		Cursor(const sf::Texture& texture)
		{
			// sets given texture to cursor
			Sprite::setTexture(texture);
		}
		Cursor() = default;

		// only works if the cursor is used (followMouse is called)
		static sf::Vector2f getPosition() { return mousePosition; }

		// disables default mouse texture and
		// updtates cursor's position relative to window
		// based on where the mouse is at at a given frame
		void followMouse(sf::RenderWindow& window);

	private:

		static sf::Vector2f mousePosition;
	};
}

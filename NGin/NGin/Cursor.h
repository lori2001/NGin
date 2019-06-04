#pragma once
#include "SFML\Graphics.hpp"

namespace NGin {
	namespace UI
	{
		class Cursor : public sf::Sprite
		{
		private:
			static sf::Vector2f mousePosition;
		
		public:
			Cursor(const sf::Texture & texture)
			{
				// sets given texture to cursor
				Sprite::setTexture(texture);

				//scales the cursor down a bit
				Transformable::setScale({ 0.85f, 0.85f });
			}
			Cursor() = default;

			static sf::Vector2f getPosition() { return mousePosition; }

			// updtates cursor's position relative to window
			// based on where the mouse is at at a given frame
			void followMouse(const sf::RenderWindow & window);
		};
	}
}

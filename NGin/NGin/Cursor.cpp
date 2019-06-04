#include "Cursor.h"

namespace NGin {
	namespace UI
	{
		sf::Vector2f Cursor::mousePosition;

		void Cursor::followMouse(const sf::RenderWindow& window)
		{
			// gets mouse position relative to window
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			// sets sprites coordinates to the updated positions
			Sprite::setPosition(mousePosition);
		}

	}
}

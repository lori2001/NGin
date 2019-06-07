#include "Cursor.h"

namespace NGin {
	namespace UI
	{
		sf::Vector2f Cursor::mousePosition;

		void Cursor::followMouse(sf::RenderWindow& window)
		{
			// gets mouse position relative to window
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			// disables default cursor on a given window
			window.setMouseCursorVisible(false);

			// sets sprites coordinates to the updated positions
			Sprite::setPosition(mousePosition);
		}

	}
}

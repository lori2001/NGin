#include "Center.h"
#include <iostream>
namespace NGin {
	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds) {
		if (text.getString() != "") {
			// Set text position in center
			text.setPosition({ bounds.left + (bounds.width / 2) - (text.getGlobalBounds().width / 2),
			bounds.top + (bounds.height / 2) - (text.getGlobalBounds().height / 2 + text.getLocalBounds().top)});
		}
	}
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape)
	{
		// corrects for outline missposition
		// does not apply to negative outlines
		if (shape.getOutlineThickness() > 0) {
			centerTextInBounds(text, {
			shape.getGlobalBounds().left,
			shape.getGlobalBounds().top,
			shape.getGlobalBounds().width - shape.getOutlineThickness() ,
			shape.getGlobalBounds().height - shape.getOutlineThickness() });
		}
		else centerTextInBounds(text, shape.getGlobalBounds());
	}
}

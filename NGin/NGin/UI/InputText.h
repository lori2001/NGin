#pragma once
#include "UIElement.h"
#include "../Utils.h"

namespace NGin::UI {
	class InputText : public UIElement {
	public:
		InputText(const sf::Vector2f& size) {
			cursor.setFillColor(sf::Color::Transparent);
			cursor.setString("|");

			setSelectThickness(3);
			setMaxCharacters(20);
			setCharacterSize(25);
			setSize(size);
		}
		InputText() : InputText({ 400, 50 }) {}
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//  Selects by mouse (BUT Needs handleEvents() to take action!)
		void select(const sf::Vector2f& mouse);
		// handles enter and mouseclick events and plays given sounds and animations whenever needed
		void handleEvents(const sf::Event& event);

		// sets the fill color of the underlying rectangle
		void setFillColor(const sf::Color& color);
		// sets the fill color of the overlaying text
		void setTextColor(const sf::Color& color);
		// sets the texture of the shape
		void setTexture(const sf::Texture& texture);
		// sets the position of the object
		void setPosition(const sf::Vector2f& position);
		// sets the font the text is going to have
		void setFont(sf::Font& font);
		// sets the maximum number of characters allowed
		void setMaxCharacters(const unsigned nrofMaxChars);
		// sets the string of the text element
		void setString(const sf::String& str);
		// sets the size of characters
		void setCharacterSize(const unsigned charSize);
		// sets the color of the outline when selected
		void setSelectColor(const sf::Color& color);
		// sets the thickness of the selection outline when active
		void setSelectThickness(const float thickness);
		// sets the size of the underlying shape
		void setSize(const sf::Vector2f& size);

		// returns the text inputed into the object
		sf::String getString() { return text.getString(); }
		bool getisActive() { return isActive; }

	private:
		sf::RectangleShape shape; // the block that the text gets displayed in
		float outlineThickness; // the thickness of shape's outline when selected
		unsigned maxChars; // holds the number of maximum characters allowed in one object

		sf::Text text; // the rewritable text inside the rectangle

		sf::Text cursor; // just a | to show off cursor position
		void adjustCursor();

		bool isActive = false; // true whenever writing may occur
		bool isSelected = false; // true whenever object is selected by means(ex.mouse)
		bool isInactive = false; // true whenever object canot be selected or changed
	};
}
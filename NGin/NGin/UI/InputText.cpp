#include "InputText.h"
#include "../Base/Logger.h"
#include "Cursor.h"

namespace NGin::UI {
	void InputText::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(text);
		target.draw(cursor);

		// if the font is not set
		if (text.getFont() == nullptr) {

			// print a warning message
			NGin::Logger::logOnce("Font undefinded for InputText nr."
				+ std::to_string(UIElement::Elemindex)
				+ " -> OBJECT MAY NOT FUNCTION PROPERLY", NGin::Logger::Severity::Warning);
		}
	}
	void InputText::select(const sf::Vector2f& mouse)
	{
		if (!isInactive) {
			isSelected = shape.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));
		}
	}
	void InputText::handleEvents(const sf::Event& event)
	{
		if (isSelected)
			shape.setOutlineThickness(outlineThickness);
		else
			shape.setOutlineThickness(0);

		// if mouse button pressed on object
		if (isSelected && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
		{ 
			NGin::UI::Cursor::playSound();

			// adjusts cursor's position
			adjustCursor();

			// color the cursor character (make visible)
			cursor.setFillColor(text.getFillColor());

			isActive = true; // makes active so writing may occur
		}
		// if mouse button pressed outside object or enter is pressed
		else if ((!isSelected && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			// make object non-active
			isActive = false;

			// hide cursor
			cursor.setFillColor(sf::Color::Transparent);
		}

		// if active and text was entered
		if (isActive && event.type == sf::Event::TextEntered)
		{
			char inputchar = event.text.unicode; // gets the character entered
			std::string container = text.getString(); // holds the string that's going to be modified

			// if backslash pressed and there are characters
			if (inputchar == '\b') {
				if (container.size() > 0) {
					container.erase(container.end() - 1); // erase the last character
				}
			}
			// if we have less than max characters and it does not go out of bounds
			else if (container.size() < maxChars && text.getLocalBounds().width < shape.getGlobalBounds().width - outlineThickness - 5)
			{
				// if shift is pressed or capslock active make the entered character caps
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					inputchar = toupper(inputchar);

				// add new character to string
				container += inputchar;
			}

			// add new string to output text
			text.setString(container);
			// center text
			centerTextInShape(text, shape);
			// adjusts cursor's position
			adjustCursor();
		}
	}
	void InputText::setFillColor(const sf::Color& color)
	{
		shape.setFillColor(color);
	}
	void InputText::setTextColor(const sf::Color& color)
	{
		text.setFillColor(color);
	}
	void InputText::setTexture(const sf::Texture& texture)
	{
		shape.setTexture(&texture);
	}
	void InputText::setPosition(const sf::Vector2f& position)
	{
		shape.setPosition(position);
		centerTextInShape(text, shape);
	}
	void InputText::setFont(sf::Font& font)
	{
		text.setFont(font);
		cursor.setFont(font);

		centerTextInShape(text, shape);
	}
	void InputText::setMaxCharacters(const unsigned nrofMaxChars)
	{
		maxChars = nrofMaxChars;
	}
	void InputText::setString(const sf::String& str)
	{
		text.setString(str);
		// centers the newly added string
		centerTextInShape(text, shape);
	}
	void InputText::setCharacterSize(const unsigned charSize) {
		text.setCharacterSize(charSize);
		centerTextInShape(text, shape);

		cursor.setCharacterSize(charSize);
	}
	void InputText::setSelectColor(const sf::Color& color) {
		shape.setOutlineColor(color);
	}
	void InputText::setSelectThickness(const float thickness) {
		outlineThickness = thickness;
	}
	void InputText::setSize(const sf::Vector2f& size) {
		shape.setSize(size);
	}
	void InputText::adjustCursor()
	{
		// if there is text set cursor after it
		if (text.getString() != "") {

			cursor.setPosition({ text.getGlobalBounds().left + text.getGlobalBounds().width + 1,
				shape.getGlobalBounds().top + (shape.getGlobalBounds().height + outlineThickness) / 2
				- (cursor.getGlobalBounds().height / 2 + cursor.getLocalBounds().top) });
		}
		else {
			// if there is no text put the cursor in center of shape
			centerTextInShape(cursor, shape);
		}

	}
}
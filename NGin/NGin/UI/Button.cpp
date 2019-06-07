#include <iostream>
#include "Button.h"

namespace NGin
{
	namespace UI
	{
		sf::Vector2f Button::calcTextPos()
		{
			// Center text's origin
			text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f,
				text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);

			// Set text position
			return (sf::Vector2f{ shape.getGlobalBounds().left + shape.getGlobalBounds().width / 2,
								  shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2 });
		}
		void Button::selectByKeyboard(const int numerotation, const int arrowCount)
		{
			// prioritize mouse over keyboard
			if (!useMouse)
			{
				if (arrowCount == numerotation) {
					isSelected = true;
				}
				else {
					isSelected = false;
				}

				useKeyboard = true;
			}
			else if (warningMessage) {
				std::cout << "WARNING! Buttons can't be contolled by both mouse and keyboard at once! -> Keyboard control DISABLED" << std::endl;
				warningMessage = false;
			}
		}
		void Button::selectByMouse(const sf::Vector2f & mouse)
		{
			// checks if the mouse and the button intersect
			isSelected = shape.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 })); // consider mouse to be 1x1 pixels

			useMouse = true;
		}
		void Button::handleEvents(const sf::Event & event)
		{
			// if the button is selected outline appears
			if (isSelected)
				shape.setOutlineThickness(outlineThickness);
			else // if not the outline disappears
				shape.setOutlineThickness(0);

			// if its selected and the right events are triggered
			if (isSelected && ((useMouse && event.mouseButton.button == sf::Mouse::Left) || (useKeyboard && event.key.code == sf::Keyboard::Enter)))
			{
				if ((useMouse && event.type == sf::Event::MouseButtonPressed) || (useKeyboard && event.type == sf::Event::KeyPressed))
				{
					if (sound.getStatus() != sf::Music::Status::Playing) // play button sound
						sound.play();

					//create the "pressed in" visual effect
					shape.setTextureRect(sf::IntRect((int)shape.getSize().x, 0, (int)shape.getSize().x, (int)shape.getSize().y));

					//the button has been pressed / take action when released
					isPressed = true;
				}
				else if (isPressed && ((useMouse && event.type == sf::Event::MouseButtonReleased) || (useKeyboard && event.type == sf::Event::KeyReleased)))
				{
					//take action
					isActive = true;
				}
			}

			// make the button inactive whenever needed
			if ((useMouse && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) || !isSelected)
			{
				shape.setTextureRect(sf::IntRect(0, 0, (int)shape.getSize().x, (int)shape.getSize().y));
				isPressed = false;
			}

			// if the button is pressed and selected the text moves down and right a bit to create the pressed-in feeling
			if (isPressed && isSelected)
				text.setPosition(sf::Vector2f(textPos.x + (3 * shape.getScale().x), textPos.y + (3 * shape.getScale().y))); // move 3px to shape's scale
			else // else the text gets back its position
				text.setPosition(textPos);
		}
		void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
		{
			target.draw(shape, states);
			target.draw(text, states);
		}
		void Button::setSoundFX(const sf::Sound & sound)
		{
			this->sound = sound;
		}
		void Button::setFont(const sf::Font & font)
		{
			// sets font
			text.setFont(font);

			// centers text with the new font in mind
			textPos = calcTextPos();
			text.setPosition(textPos);
		}
		void Button::setTextColor(const sf::Color & color)
		{
			text.setFillColor(color);
		}
		void Button::setTexture(const sf::Texture & texture)
		{
			// sets sprite texture
			shape.setTexture(&texture);

			// uses the first part of the buttontexture
			shape.setTextureRect(sf::IntRect(0, 0, int(shape.getSize().x), int(shape.getSize().y)));
		}
		void Button::setFillColor(const sf::Color & color)
		{
			shape.setFillColor(color);
		}
		void Button::setPosition(const sf::Vector2f & position)
		{
			//sets position of the sprite
			shape.setPosition(position);

			// update the position of the text based on shape's position
			textPos = calcTextPos();
			text.setPosition(textPos);
		}
		void Button::setSelectColor(const sf::Color & color)
		{
			//in case selected this color will be the outline
			shape.setOutlineColor(color);
		}
		void Button::setSelectThickness(const float thickness)
		{
			outlineThickness = thickness;
		}
		void Button::setScale(const sf::Vector2f & scale)
		{
			//changes sprite scale
			shape.setScale(scale);

			//changes text size
			text.setCharacterSize(int(38 * scale.y));

			//centers the newly sized text
			textPos = calcTextPos();
			text.setPosition(textPos);
		}
		void Button::setCharacterSize(const int size)
		{
			//sets the new string to the text
			this->text.setCharacterSize(size);

			//centers the string with its new height
			textPos = calcTextPos();
			text.setPosition(textPos);
		}
		bool Button::activated()
		{
			if (isActive) {
				isActive = false;
				return true;
			}
			else return false;
		}
		void Button::setString(const sf::String & txt)
		{
			//sets the new string to the text
			this->text.setString(txt);

			//centers the new string of text
			textPos = calcTextPos();
			text.setPosition(textPos);
		}
	}
}

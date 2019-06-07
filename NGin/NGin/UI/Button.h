#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace NGin
{
	namespace UI
	{
		class Button : public sf::Drawable
		{
		public:
			Button(const sf::Vector2f& size) {
				shape.setSize(size);
				shape.setFillColor(sf::Color(98, 144, 219));
				shape.setOutlineColor(sf::Color(211, 95, 82));
				outlineThickness = 3;
			}
			Button(const sf::Vector2f& size, const sf::Texture& texture) : Button(size) {
				this->setTexture(texture);
			}
			Button(const sf::Font& font, const sf::String& txt, const sf::Vector2f& size) : Button(size)
			{
				text.setFont(font);
				text.setString(txt);
				text.setCharacterSize(30);
				text.setFillColor(sf::Color(0, 0, 0));

				textPos = calcTextPos();
				text.setPosition(textPos);
			}
			Button() : Button(sf::Vector2f{ 400, 50 }) {} // default empty selectable rectangle

			/* IMPORTANT! You have to count and modify arrowCount in an outside variable in order for this to work
			   Also needs handleEvents() to take action*/
			void selectByKeyboard(const int numerotation, const int arrowCount);
			/* Needs handleEvents() to take action */
			void selectByMouse(const sf::Vector2f& mouse);

			// handles enter and mouseclick events and plays given sounds and animations whenever neede
			void handleEvents(const sf::Event& event);
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			// sound the button makes when pressed
			void setSoundFX(const sf::Sound& pressbutton);
			// font of the text on the button
			void setFont(const sf::Font& font);
			// sets the color of the text on the button
			void setTextColor(const sf::Color& color);
			// string the button uses
			void setString(const sf::String& txt);
			// texture of the button
			void setTexture(const sf::Texture& texture);
			// changes the default color of the button
			void setFillColor(const sf::Color& color);
			// position of the button
			void setPosition(const sf::Vector2f& position);
			// outline's color when selected
			void setSelectColor(const sf::Color& color);
			// sets the thickness of the outline when selected
			void setSelectThickness(const float thickness);
			// scale of the button
			void setScale(const sf::Vector2f& scale);
			// sets the character size of the text
			void setCharacterSize(const int size);
		
			// returns true whenever action needs to be taken. sets itself back to false automatically
			bool activated();

			sf::Vector2f getScale() const { return  shape.getScale(); }
			sf::Vector2f getPosition() const { return shape.getPosition(); }
			sf::Vector2f getSize() const { return shape.getSize(); }
			sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }

		private:
			sf::RectangleShape shape; // creates a shape for the button
			sf::Text text; // a text to be on the button
			sf::Sound sound; // sound to play when button activated

			float outlineThickness; // the thickness of the outline when selected
			sf::Vector2f textPos; // the position at which the text should stay
			sf::Vector2f calcTextPos(); // updates default text position so as to avoid writing so much and make things compact

			bool isPressed = false; // intermediarily active boolean in between isSelected and isActive
			bool isSelected = false; // if the button is selected by either mouse or keyboard this is true
			bool isActive = false; // this is true when the button is pressed upon

			bool useMouse = false; // true whenever mouse selection is used
			bool useKeyboard = false; // true whenever keyboard selection is used

			bool warningMessage = true; // used to display warning message only once in an endless loop
		};
	}
}

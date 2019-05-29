#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace NGin
{
	namespace UI
	{
		class Button : public sf::Drawable
		{
		private:
			sf::RectangleShape shape; // creates a shape for the button
			sf::Text text; // a text to be on the button
			sf::Sound sound; // sound to play when button activated

			sf::Vector2f textPos; // the position at which the text should stay
			sf::Vector2f calcTextPos(); // updates default text position so as to avoid writing so much and make things compact

			bool isPressed = false; // intermediarily active boolean in between isSelected and isActive
			bool isSelected = false; // if the button is selected by either mouse or keyboard this is true
			bool isActive = false; // this is true when the button is pressed upon

			bool useMouse = false; // true whenever mouse selection is used
			bool useKeyboard = false; // true whenever keyboard selection is used

			bool warningMessage = true; // used to display warning message only once in an endless loop
		public:
			Button(const sf::Vector2f& size) {
				shape.setSize(size);
				shape.setFillColor(sf::Color(57, 179, 0));
				shape.setOutlineColor(sf::Color(57, 65, 222));
			}
			Button(const sf::Font& font, const sf::String& txt, const sf::Vector2f& size) : Button(size)
			{
				text.setFont(font);
				text.setString(txt);
				text.setCharacterSize(30);
				text.setFillColor(sf::Color(200, 100, 100)); // (247, 148, 29)  (57,179,0)  (57, 65, 222)

				textPos = calcTextPos();
				text.setPosition(textPos);
			}
			Button() : Button(sf::Vector2f{ 400, 50 }) {} // default empty selectable rectangle

			/* IMPORTANT! You have to count and modify arrowCount in an outside variable in order for this to work
			   Also needs handleEvents() to take action*/
			void selectByKeyboard(const int& numerotation, const int& arrowCount);
			/* Needs handleEvents() to take action */
			void selectByMouse(const sf::Vector2f& mouse);

			void handleEvents(const sf::Event& event);
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			// setters
			void setSoundFX(const sf::Sound& pressbutton); // sound the button makes when pressed
			void setFont(const sf::Font& font); // font of the button
			void setTextColor(const sf::Color& color); // sets the color of the text on the button
			void setString(const sf::String& txt); // string the button uses
			void setTexture(const sf::Texture& texture); // texture of the button
			void setFillColor(const sf::Color& color); // changes the default color of the button
			void setPosition(const sf::Vector2f& position); // position of the button
			void setSelectColor(const sf::Color& color); // outline's color when selected
			void setScale(const sf::Vector2f& scale); // scale of the button
			void setCharacterSize(const int& size); // sets the character size of the text

			// getters

			// returns true whenever action needs to be taken. sets itself back to false automatically
			bool activated();

			sf::Vector2f getScale() const { return  shape.getScale(); }
			sf::Vector2f getPosition() const { return shape.getPosition(); }
			sf::Vector2f getSize() const { return shape.getSize(); }
			sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
		};
	}
}

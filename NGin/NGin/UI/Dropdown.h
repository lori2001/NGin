#pragma once
#include "UIElement.h"
#include "../Utils.h"

namespace NGin::UI
{
	class Dropdown : public UIElement
	{
	public:
		Dropdown(const sf::Vector2f& size) {
			/*declaration of MANDATORY first element*/
				isSelected.push_back(false);
				isActive.push_back(false);
				texts.push_back({ "", sf::Font{}, 22 });
				centerTextInShape(texts[0], shape);

			outlineThickness = 3; // the thickness of outline when selected

			highlight.setFillColor(sf::Color(255, 255, 255, 100)); // half-transparent white

			this->size = size;
			shape.setSize(size);
			highlight.setSize(size);
		}
		Dropdown() : Dropdown({ 300, 40 }) {}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// can be selected by mouse (only if the object is not inactive)
		void select(const sf::Vector2f& mouse);
		// reacts to user input (other than selecting)
		void handleEvents(const sf::Event& event);

		// creates a dropdown element filled with text
		void addDropString(const sf::String text);
		// deletes element with index i
		void deleteDropString(const int i);

		// BEWARE! SETS texture.isRepeated() to true
		// adds given texture to the object shape
		void setTexture(sf::Texture& texture);
		// sets the font for all texts
		void setFont(sf::Font& in_font);
		// gives a color to the shape
		void setFillColor(const sf::Color& color);
		// sets selection outline's color
		void setSelectColor(const sf::Color& color);
		// sets the size of the main item and its derivates
		void setSize(const sf::Vector2f& in_size);
		// sets the object's position
		void setPosition(const sf::Vector2f& position);
		// sets the size of the text inside the dropdown
		void setTextSize(const unsigned charSize);
		// sets the text with given index inside the droptext vector
		void setDropString(const int i, const sf::String& text);
		// makes dropdown unselectable and unactivateable
		void setInactivity(const bool in_isInactive);
		// if true does not swap out the main drop-text inside the object
		void setStaticism(const bool in_isStatic);

		// returns isActive for given element number and sets it to false
		bool activated(const int i);
		// gets the number of elements (including default one)
		int getNrofElem();
		// gets the string of the element of index i
		sf::String getDropString(const int i);

	private:
		sf::Vector2f size; // the size of the object in closed status
		float outlineThickness; // the size of the outline in pixels

		sf::RectangleShape shape; // the main shape of the object
		sf::Color shapeColor; // the color the shape has when not inactive
		sf::RectangleShape highlight; // the overlay that gets displayed upon currently selected element

		std::vector<sf::Text> texts; // texts inside each element

		std::vector<bool> isSelected; // bool for each element that = true if the element is selected
		std::vector<bool> isActive; // if true then react - this is done outside of object exept for element nr 0

		bool drawHighlight = false; // if true the highlight gets drawn
		bool isInactive = false; // if true the object is unselectable and unactivatable
		bool isStatic = false; // if true the values do not ever swap out inside the container
	};
}
#pragma once
#include "UIElement.h"
#include "../Utilities.h"

namespace ngin::ui
{
	class Dropdown : public UIElement
	{
	public:
		Dropdown(const sf::Vector2f& size) {
			setSize(size);

			/*declaration of MANDATORY first element*/
				isSelecteds_.push_back(false);
				isActives_.push_back(false);
				texts_.push_back(sf::Text{});

			selectThickness_ = 3; // the thickness of outline when selected
			setCharacterSize(22);
			highlight_.setFillColor(sf::Color(255, 255, 255, 100)); // half-transparent white
		}
		Dropdown() : Dropdown({ 300, 40 }) {}

		void draw(sf::RenderWindow& window);

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);

		// creates a dropdown element filled with text
		void addDropString(const sf::String& text);
		// deletes element with index i
		void deleteDropString(const int i);

		// BEWARE! SETS texture.isRepeated() to true
		void setTexture(sf::Texture& texture);
		void setFont(sf::Font& font);
		void setFillColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color) { shape_.setOutlineColor(color); }
		void setSelectThickness(const float thickness) { selectThickness_ = thickness; }
		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setCharacterSize(const unsigned characterSize);
		void setDropString(const int i, const sf::String& text);
		void setDisabled(const bool isDisabled);
		void setStatic(const bool isStatic) { isStatic_ = isStatic; }

		bool isActive(const int i) const { return isActives_[i]; }
		int getElementsNo() const { return int(isSelecteds_.size()); }
		sf::String getDropString(const int i) const { return texts_[i].getString(); }

	private:
		sf::Vector2f size_; // the size of the object in closed status
		float selectThickness_; // the size of the outline in pixels

		sf::RectangleShape shape_; // the main shape of the object
		sf::Color shapeColor_; // the color the shape has when not inactive
		sf::RectangleShape highlight_; // the overlay that gets displayed upon currently selected element
		sf::FloatRect closedGlobalBounds_;

		std::vector<sf::Text> texts_; // texts inside each element
		unsigned characterSize_;
		std::vector<bool> isSelecteds_; // bool for each element that = true if the element is selected
		std::vector<bool> isActives_; // if true then react - this is done outside of object exept for element nr 0

		bool drawHighlight_ = false; // if true the highlight gets drawn
		bool isDisabled_ = false; // if true the object is unselectable and unactivatable
		bool isStatic_ = false; // if true the values do not ever swap out inside the container
	};
}
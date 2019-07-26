#pragma once
#include "UIElement.h"
#include "Button.h"

namespace ngin::ui {
	class Slider : public UIElement {
	public:
		Slider(const sf::Vector2f& shapeSize,
			const sf::Vector2f& arrowSize,
			const sf::Vector2f& markSize,
			const sf::Vector2f& position = { 0,0 })
		{
			setSelectThickness(-3); // selection goes inside container
			setSizes(shapeSize, arrowSize, markSize);

			// button has to be centered in order to align properly
			mark_.setOrigin({ mark_.getGlobalBounds().width / 2, mark_.getGlobalBounds().height / 2 });

			// set up the mark's virtual box (has some additional offset calibrated for default textures)
			sliderBox_ = { mark_.getGlobalBounds().width / 2 + 5 , 0,
					   container_.getGlobalBounds().width - mark_.getGlobalBounds().width - 10,
					   container_.getGlobalBounds().height / 2 };

			setPosition({ 0, 0 });

		} Slider(const sf::Vector2f& position = { 0,0 }) : Slider({ 300, 40 }, { 40, 40 }, { 30, 30 }, position) {}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderWindow& window);

		void setTexture(const sf::Texture& texture);
		void setFillColor(const sf::Color& color);
		void setContainerColor(const sf::Color& color) { container_.setFillColor(color); }
		void setMarkColor(const sf::Color& color) { mark_.setFillColor(color); }
		void setArrowsColor(const sf::Color& color);
		void setSliderBox(const sf::FloatRect& sliderBox) { sliderBox_ = sliderBox; }
		void setPosition(const sf::Vector2f& position);
		void setLevel(const float level);
		void setSizes(const sf::Vector2f& shapeSize, const sf::Vector2f& arrowSize, const sf::Vector2f& markSize);
		void setSelectThickness(const float selectSize) { selectThickness_ = selectSize; }

		float getLevel() { return level_; }
		sf::Vector2f getSize() { return { leftButton_.getSize().x + container_.getSize().x + rightArrow.getSize().x, container_.getSize().y }; }
		bool getHasChanged() { return hasChanged_; }
	private:
		// adjust button position based on level
		void adjustMarkPos();
	private:
		sf::FloatRect sliderBox_; // a box for the mark to move in
		sf::RectangleShape container_;
		sf::RectangleShape mark_;
		Button leftButton_; // the button on the left of the window
		Button rightArrow; // the button on the right of the window

		float selectThickness_;
		float level_ = 0; // the output percentage (0 <= level <= 1)

		bool isSliding_ = false; // true if lmb is on hold (then slider is active)
		bool isDisabled_ = false; // if true the object can't be selected or modified
		bool isSelected_ = false; // used for the main section
		bool hasChanged_ = false; // signals to user wheter level has been changed compared to last time
	};
}
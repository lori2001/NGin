#pragma once
#include "UIElement.h"
#include "Button.h"

namespace NGin::UI {
	class Slider : public UIElement {
	public:
		Slider(const sf::Vector2f& shapeSize,
			const sf::Vector2f& arrowSize,
			const sf::Vector2f& markSize,
			const sf::Vector2f& position = { 0,0 })
		{
			outlineThickness = 3;

			// set shapes' sizes
			shape.setSize(shapeSize);
			leftArrow.setSize(arrowSize);
			rightArrow.setSize(arrowSize);
			mark.setSize(markSize);

			// button has to be centered in order to align properly
			mark.setOrigin({ mark.getGlobalBounds().width / 2, mark.getGlobalBounds().height / 2 });

			// set up virtual box (has some additional offset calibrated for default textures)
			sliderBox = { mark.getGlobalBounds().width / 2 + 5 , 0,
					   shape.getGlobalBounds().width - mark.getGlobalBounds().width - 10,
					   shape.getGlobalBounds().height / 2 };

			setPosition({ 0, 0 });

		} Slider(const sf::Vector2f& position = { 0,0 }) : Slider({ 300, 40 }, { 40, 40 }, { 30, 30 }, position) {}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//  Selects by mouse (BUT Needs handleEvents() to take action!)
		void select(const sf::Vector2f& mouse);

		// handles enter and mouseclick events and plays given sounds and animations whenever needed
		void handleEvents(const sf::Event& event);

		// sets textures which then get mapped according to sizes (shape->arrow->button)
		void setTexture(const sf::Texture& texture);
		// set fill color of every element
		void setFillColor(const sf::Color& color);
		// set the fill color of the mark's container only
		void setContainerColor(const sf::Color& color);
		// set the fill color of the mark only
		void setMarkColor(const sf::Color& color);
		// set the fill color of the arrows(left and right) only
		void setArrowsColor(const sf::Color& color);
		// sets the box the slider can move in
		void setSliderBox(const sf::FloatRect& newbox);
		// sets the position of the object (top-left pivot)
		void setPosition(const sf::Vector2f& position);

		// gets the current level of the slider in a value between 0 and 1
		float getLevel();
	private:
		// adjust button position based on level
		void adjustMarkPos();
	private:
		sf::FloatRect sliderBox; // a virtual box for the mark
		sf::RectangleShape shape; // the main shape of the slider
		sf::RectangleShape mark; // the round sprite signaling current level
		Button leftArrow; // the left arrow's button
		Button rightArrow; // the right arrow's button

		float outlineThickness; // the thickness of selection outline
		float mouseX = 0; // holds mouse's X position to help calculate level later on
		float level = 0; // the output percentage (0 <= level <= 1)

		bool isSliding = false; // true if lmb is on hold (then slider is active)
		bool isInactive = false; // if true the object can't be selected or modified
		bool isSelected = false; // used for the main section
		bool isActive = false; // used for the main section
	};
}
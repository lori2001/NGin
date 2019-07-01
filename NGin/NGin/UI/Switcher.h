#pragma once
#include "UIElement.h"
#include "Button.h"

namespace NGin::UI {
	class Switcher : public UIElement {
	public:
		Switcher() : Switcher(sf::Vector2f{ 60,60 }) {}
		Switcher(const sf::Vector2f& size) {
			setSize(size);
		}

		// handles enter and mouseclick events and plays given sounds and animations whenever needed
		void handleEvents(const sf::Event& event);

		void select(const sf::Vector2f& mouse);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// texture of the button + mark (overwrite)
		void setTexture(const sf::Texture& texture);
		// sets position of the switch (overwrite)
		void setPosition(const sf::Vector2f& position);
		// rescales the entire switcher by given decimal
		void setScale(const sf::Vector2f& scale);
		// sets the size of the switcher displayed to given numbers
		void setSize(const sf::Vector2f& size);
		// set the fill color of everything
		void setFillColor(const sf::Color& color);
		// set the color of only the mark
		void setMarkColor(const sf::Color& color);
		// set the color of only the button
		void setButtonColor(const sf::Color& color);
		// sets the color of the selection rectangle
		void setSelectColor(const sf::Color& color);

		// returns true whether switcher is  active
		bool getisActive();
	private:
		// this is the mark getting displayed over the button whenever switched on
		sf::RectangleShape mark;
		// the color the mark normally has (when not inactive)
		sf::Color markColor;

		// this is the base button that gtets transformed into switcher
		Button button;

		bool isActive = false;
	};
}
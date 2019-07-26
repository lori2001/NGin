#pragma once
#include "UIElement.h"
#include "Button.h"

namespace ngin::ui {
	class Switcher : public UIElement {
	public:
		Switcher() : Switcher(sf::Vector2f{ 60,60 }) {}
		Switcher(const sf::Vector2f& size) {
			setSize(size);
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderWindow& window);

		void setTexture(const sf::Texture& texture);
		void setPosition(const sf::Vector2f& position);
		void setScale(const sf::Vector2f& scale);
		void setSize(const sf::Vector2f& size);
		void setFillColor(const sf::Color& color);
		void setMarkColor(const sf::Color& color);
		void setButtonColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color);
		void setisActive(const bool active);
		void setDisabled(const bool isDisabled);

		bool isActive() { return isActive_; }
		bool hasChanged() { return hasChanged_; }
		sf::Vector2f getSize() const { return button_.getSize(); }
	private:
		sf::RectangleShape mark;

		Button button_;

		bool isActive_ = false;
		bool hasChanged_ = false;
	};
}
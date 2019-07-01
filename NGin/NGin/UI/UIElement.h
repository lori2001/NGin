#pragma once
#include "SFML/Graphics.hpp"

namespace NGin::UI {
	// helps count number of UIElements for debugging purposes
	static std::vector<bool> UIElements;

	// holds every class that all UIElements should have in common
	class UIElement : public sf::Drawable
	{
	public:
		UIElement() {
			Elemindex = UIElements.size();
			UIElements.push_back(true);
		}
		virtual ~UIElement()
		{
			UIElements.erase(UIElements.begin() + Elemindex);
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void select(const sf::Vector2f& mouse) = 0;
		virtual void handleEvents(const sf::Event& event) = 0;

	protected:
		unsigned Elemindex;
	};
}

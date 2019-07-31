#pragma once
#include "SFML/Graphics.hpp"

namespace ngin {
	class Level : public sf::Drawable
	{
	public:
		// gets called after creating the window
		virtual void setup() {}
		// gets called only if there is an ongoing event
		virtual void handleEvents(const sf::Event& event) {}
		// gets called every frame but is not constant
		virtual void update() {}
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

namespace ngin
{
	// holds every class that all UIElements should have in common
	class UIElement : public sf::Drawable
	{
	public:
		UIElement() {
			iElement_ = static_cast<int>(Elements_.size());
			Elements_.push_back(true);
		}
		virtual ~UIElement()
		{
			Elements_.erase(Elements_.begin() + iElement_);
		}

		virtual void handleEvents(const sf::Event& event, const sf::Vector2f& mouse) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		int getElementIndex() const { return iElement_; }
	private:
		// helps count number of UIElements for debugging purposes
		static std::vector<bool> Elements_;
		int iElement_;
	};
}

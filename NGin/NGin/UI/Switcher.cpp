#include "Switcher.h"

namespace NGin::UI {
	void Switcher::selectByMouse(const sf::Vector2f& mouse)
	{
		button.selectByMouse(mouse);
	}
	void Switcher::handleEvents(const sf::Event& event)
	{
		button.handleEvents(event);

		if (button.getIsPressed()) {
			mark.setTextureRect({ int(3 * mark.getSize().x), 0, int(mark.getSize().x), int(mark.getSize().y) });
		}
		else {
			mark.setTextureRect({ int(2 * mark.getSize().x), 0, int(mark.getSize().x), int(mark.getSize().y) });
		}

		if (button.activated()) {
			isActive = !isActive;
		}

	}
	void Switcher::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		button.draw(target, states);
		
		if(isActive)
			target.draw(mark);
	}
	void Switcher::setTexture(const sf::Texture& texture)
	{
		button.setTexture(texture);
		mark.setTexture(&texture);
	}
	void Switcher::setPosition(const sf::Vector2f& position)
	{
		button.setPosition(position);
		mark.setPosition(position);
	}
	void Switcher::setScale(const sf::Vector2f& scale)
	{
		button.setScale(scale);
		mark.setScale(scale);
	}
	void Switcher::setSize(const sf::Vector2f& size)
	{
		button.setSize(size);
		mark.setSize(size);
	}
	void Switcher::setFillColor(const sf::Color& color)
	{
		setButtonColor(color);
		setMarkColor(color);
	}
	void Switcher::setMarkColor(const sf::Color& color)
	{
		markColor = color;
		mark.setFillColor(markColor);
	}
	void Switcher::setButtonColor(const sf::Color& color)
	{
		button.setFillColor(color);
	}
	void Switcher::setSelectColor(const sf::Color& color)
	{
		button.setSelectColor(color);
	}
	bool Switcher::getisActive()
	{
		return isActive;
	}
}

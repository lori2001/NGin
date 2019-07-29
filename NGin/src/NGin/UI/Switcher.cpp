#include "Switcher.h"

namespace ngin::ui {
	void Switcher::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		hasChanged_ = false;

		button_.handleEvents(event, mouse);

		if (button_.isPressed()) {
			mark.setTextureRect({ int(3 * mark.getSize().x), 0, int(mark.getSize().x), int(mark.getSize().y) });
		}
		else {
			mark.setTextureRect({ int(2 * mark.getSize().x), 0, int(mark.getSize().x), int(mark.getSize().y) });
		}

		if (button_.isActive()) {
			isActive_ = !isActive_;
			hasChanged_ = true;
		}
		else hasChanged_ = false;

	}
	void Switcher::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(button_);

		if (isActive_)	
			target.draw(mark);
	}
	void Switcher::setTexture(const sf::Texture& texture)
	{
		button_.setTexture(texture);
		mark.setTexture(&texture);
	}
	void Switcher::setPosition(const sf::Vector2f& position)
	{
		button_.setPosition(position);
		mark.setPosition(position);
	}
	void Switcher::setScale(const sf::Vector2f& scale)
	{
		button_.setScale(scale);
		mark.setScale(scale);
	}
	void Switcher::setSize(const sf::Vector2f& size)
	{
		button_.setSize(size);
		mark.setSize(size);
	}
	void Switcher::setFillColor(const sf::Color& color)
	{
		setButtonColor(color);
		setMarkColor(color);
	}
	void Switcher::setMarkColor(const sf::Color& color)
	{
		mark.setFillColor(color);
	}
	void Switcher::setButtonColor(const sf::Color& color)
	{
		button_.setFillColor(color);
	}
	void Switcher::setSelectColor(const sf::Color& color)
	{
		button_.setSelectColor(color);
	}
	void Switcher::setisActive(const bool active)
	{
		isActive_ = active;
		mark.setTextureRect({ int(2 * mark.getSize().x), 0, int(mark.getSize().x), int(mark.getSize().y) });
	}
	void Switcher::setDisabled(const bool isDisabled)
	{
		button_.setDisabled(isDisabled);
	}
}

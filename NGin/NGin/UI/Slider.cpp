#include "Slider.h"
#include "../Base/Console.h"
#include "Cursor.h"

namespace ngin::ui {
	void Slider::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_) {

			isSelected_ = container_.getGlobalBounds().intersects({ mouse, { 1,1 } });

			if (isSelected_) {
				container_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed) {
					// isSliding is true if isSelected and while lmb is held 
					isSliding_ = true;

					// play slider sound
					ngin::ui::Cursor::playSound();
				}
			}
			else
				container_.setOutlineThickness(0);

			if (event.type == sf::Event::MouseButtonReleased && isSliding_) {

				// if lmb is released set to false
				isSliding_ = false;
			}
			else if (isSliding_) {
				// calculate the level based on the mouse's position (OUTPUT: a number between 0 and 1)
				level_ = (mouse.x - container_.getGlobalBounds().left) / container_.getGlobalBounds().width;

				// Safely restrict that number
				if (level_ > 1) level_ = 1;
				else if (level_ < 0) level_ = 0;

				hasChanged_ = true; // signal that the level has changed in this frame

				adjustMarkPos();
			}

			leftButton_.handleEvents(event, mouse);
			rightArrow.handleEvents(event, mouse);

			if (leftButton_.isActive()) {
				float temp = level_ - 0.05F; // step down level by 0.05

				// establish 0 as minimum limit
				if (temp < 0) level_ = 0;
				else level_ = temp;

				hasChanged_ = true; // signal that the level has changed in this frame
				adjustMarkPos();
			}
			else if (rightArrow.isActive()) {
				float temp = level_ + 0.05F; // step up level by 0.05

				// establish 1 as maximum limit
				if (temp > 1) level_ = 1;
				else level_ = temp;

				hasChanged_ = true; // signal that the level has changed in this frame
				adjustMarkPos();
			}
		}
	}
	void Slider::draw(sf::RenderWindow& window)
	{
		// DONT DO this at home, kids
		hasChanged_ = false; // the level has not yet changed in this frame

		window.draw(container_);
		leftButton_.draw(window);
		rightArrow.draw(window);
		window.draw(mark_);
	}
	void Slider::setTexture(const sf::Texture& texture)
	{
		container_.setTexture(&texture);
		leftButton_.setTexture(texture);
		rightArrow.setTexture(texture);
		mark_.setTexture(&texture);

		leftButton_.setTexturePos({ 0, 0 });

		container_.setTextureRect({ 2 * (int)leftButton_.getSize().x, 0, (int)container_.getSize().x, (int)container_.getSize().y });

		rightArrow.setTexturePos({ 2 * int(leftButton_.getSize().x) + int(container_.getSize().x), 0 });

		mark_.setTextureRect ({
			int(container_.getSize().x) + 2 * int(leftButton_.getSize().x) + 2 * int(rightArrow.getSize().x), 0,
			(int)mark_.getSize().x, (int)mark_.getSize().y
		});
	}
	void Slider::setFillColor(const sf::Color& color)
	{
		setContainerColor(color);
		setMarkColor(color);
		setArrowsColor(color);
	}
	void Slider::setArrowsColor(const sf::Color& color)
	{
		leftButton_.setFillColor(color);
		rightArrow.setFillColor(color);
	}
	void Slider::setPosition(const sf::Vector2f& position)
	{
		// positon structure (leftArrow->shape->rightArrow)
		leftButton_.setPosition(position);
		container_.setPosition({ leftButton_.getPosition().x + leftButton_.getGlobalBounds().width, position.y });
		rightArrow.setPosition({ container_.getPosition().x + container_.getGlobalBounds().width, position.y });

		// put the mark where it should be
		adjustMarkPos();
	}
	void Slider::setLevel(const float level)
	{
		// only if the level wasn't changed manually
		if (!hasChanged_) {

			// check if the set level is valid
			if (level > 1) {
				Console::logOnce(Console::Severity::Warning, "Element: ", getElementIndex(),
					" Slider level set to: ", level, " -> above 1(100%)!");
			}
			else if (level < 0) {
				Console::logOnce(Console::Severity::Warning, "Element: ", getElementIndex(),
					" Slider level set to: ", level, " -> below 0(0%)!");
			}

			// set level
			level_ = level;
			// adjust mark position to level
			adjustMarkPos();
		}

		hasChanged_ = false;
	}
	void Slider::setSizes(const sf::Vector2f& shapeSize, const sf::Vector2f& arrowSize, const sf::Vector2f& markSize)
	{
		container_.setSize(shapeSize);
		leftButton_.setSize(arrowSize);
		rightArrow.setSize(arrowSize);
		mark_.setSize(markSize);
	}
	void Slider::adjustMarkPos()
	{
		mark_.setPosition({
			container_.getPosition().x + sliderBox_.left + (sliderBox_.width * level_),
			container_.getPosition().y + sliderBox_.height });
	}
}
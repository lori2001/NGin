#include "Slider.h"
#include "Cursor.h"

namespace NGin::UI {
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(leftArrow);
		target.draw(rightArrow);
		target.draw(mark);
	}
	void Slider::select(const sf::Vector2f& mouse)
	{
		if (!isInactive) {

			leftArrow.select(mouse);
			rightArrow.select(mouse);

			sf::FloatRect mouseRect = { mouse, { 1,1 } };

			isSelected = shape.getGlobalBounds().intersects(mouseRect);

			// store mouse.x in slider level to avoid declaring another float
			mouseX = mouse.x;
		}
	}
	void Slider::handleEvents(const sf::Event& event)
	{
		if (!isInactive) {

			if (isSelected) {
				shape.setOutlineThickness(-outlineThickness);

				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed) {
					// isSliding is true if isSelected and while lmb is held 
					isSliding = true;

					// play slider sound
					NGin::UI::Cursor::playSound();
				}
			}
			else 
				shape.setOutlineThickness(0);
			
			if (event.type == sf::Event::MouseButtonReleased && isSliding) {

				// if lmb is released set to false
				isSliding = false;
			}
			else if (isSliding) {
				// calculate the level based on the mouse's position (OUTPUT: a number between 0 and 1)
				level = (mouseX - shape.getGlobalBounds().left) / shape.getGlobalBounds().width;

				// Safely restrict that number
				if (level > 1) level = 1;
				else if (level < 0) level = 0;

				adjustMarkPos();
			}

			leftArrow.handleEvents(event);
			rightArrow.handleEvents(event);

			if (leftArrow.activated()) {
				float temp = level - 0.05f; // step down level by 0.05

				// establish 0 as minimum limit
				if (temp < 0) level = 0;
				else level = temp;

				adjustMarkPos();
			}
			else if (rightArrow.activated()) {
				float temp = level + 0.05f; // step up level by 0.05

				// establish 1 as maximum limit
				if (temp > 1) level = 1;
				else level = temp;

				adjustMarkPos();
			}
		}
	}
	void Slider::setTexture(const sf::Texture& texture)
	{
		shape.setTexture(&texture);
		leftArrow.setTexture(texture);
		rightArrow.setTexture(texture);
		mark.setTexture(&texture);

		leftArrow.setTexturePos({ 0, 0 });

		shape.setTextureRect({ 2 * (int)leftArrow.getSize().x, 0, (int)shape.getSize().x, (int)shape.getSize().y });

		rightArrow.setTexturePos({ int(2 * leftArrow.getSize().x + shape.getSize().x), 0 });

		mark.setTextureRect ({
			int(shape.getSize().x + 2 * leftArrow.getSize().x + 2 * rightArrow.getSize().x), 0,
			(int)mark.getSize().x, (int)mark.getSize().y
		});
	}
	void Slider::setFillColor(const sf::Color& color)
	{
		setContainerColor(color);
		setMarkColor(color);
		setArrowsColor(color);
	}
	void Slider::setContainerColor(const sf::Color& color)
	{
		shape.setFillColor(color);
	}
	void Slider::setMarkColor(const sf::Color& color)
	{
		mark.setFillColor(color);
	}
	void Slider::setArrowsColor(const sf::Color& color)
	{
		leftArrow.setFillColor(color);
		rightArrow.setFillColor(color);
	}
	void Slider::setSliderBox(const sf::FloatRect& newbox)
	{
		sliderBox = newbox;
	}
	void Slider::setPosition(const sf::Vector2f& position)
	{
		// positon structure (leftArrow->shape->rightArrow)
		leftArrow.setPosition(position);
		shape.setPosition({ leftArrow.getPosition().x + leftArrow.getGlobalBounds().width, position.y });
		rightArrow.setPosition({ shape.getPosition().x + shape.getGlobalBounds().width, position.y });

		// put the mark where it should be
		adjustMarkPos();
	}
	float Slider::getLevel()
	{
		return level;
	}
	void Slider::adjustMarkPos()
	{
		mark.setPosition({
			shape.getPosition().x + sliderBox.left + (sliderBox.width * level),
			shape.getPosition().y + sliderBox.height });
	}
}
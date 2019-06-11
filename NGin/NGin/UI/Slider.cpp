#include "Slider.h"

namespace NGin::UI {
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(leftArrow);
		target.draw(rightArrow);
		target.draw(mark);
	}
	void Slider::selectByMouse(const sf::Vector2f& mouse)
	{
		if (!isInactive) {

			leftArrow.selectByMouse(mouse);
			rightArrow.selectByMouse(mouse);

			sf::FloatRect mouseRect = { mouse, { 1,1 } };

			isSelected = shape.getGlobalBounds().intersects(mouseRect);

			// store mouse.x in slider level to avoid declaring another float
			mouseX = mouse.x;
		}
	}
	void Slider::handleEvents(const sf::Event& event)
	{
		if (!isInactive) {

			if (isSelected)
				shape.setOutlineThickness(-outlineThickness);
			else 
				shape.setOutlineThickness(0);

			if (event.mouseButton.button == sf::Mouse::Left && isSelected)
			{
				// isSliding is true if isSelected and while lmb is held 
				isSliding = true;
			}
			
			if (event.type == sf::Event::MouseButtonReleased && isSliding) {

				// play slider sound
				if (sound.getStatus() != sf::Music::Status::Playing)
					sound.play();

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
	void Slider::setSoundFX(const sf::SoundBuffer& buffer)
	{
		sound.setBuffer(buffer);
		leftArrow.setSoundFX(buffer);
		rightArrow.setSoundFX(buffer);
	}
	void Slider::setFillColor(const sf::Color& color)
	{
		shape.setFillColor(color);
		leftArrow.setFillColor(color);
		rightArrow.setFillColor(color);
		mark.setFillColor(color);
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
#include "Dropdown.h"
#include <iostream>

namespace NGin::UI
{
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);

		if (drawHighlight) {
			target.draw(highlight);
		}

		target.draw(droptext[0]);

		if (isActive[0]) {
			for (int i = 1; i < int(droptext.size()); i++) {
				target.draw(droptext[i]);
			}
		}

		target.draw(textAbove);
	}
	void Dropdown::selectByMouse(const sf::Vector2f& mouse)
	{
		if (!isInactive)
		{
			// first element is the closed-up shape
			sf::FloatRect mainrect(shape.getGlobalBounds().left, shape.getGlobalBounds().top, size.x * shape.getScale().x, size.y * shape.getScale().y);
			
			// a false rectangle that represents mouse for easy intersection checking
			sf::FloatRect mouseRect = { mouse, { 1,1 } };
			
			// check if it collides with mouse
			isSelected[0] = mainrect.intersects(mouseRect);

			// if the main element has been pressed
			if (isActive[0])
			{
				// iterate through each element of the dropdown
				for (int i = 1; i < int(isSelected.size()); i++)
				{
					// creates a FloatRect class for the current elements' position
					// keep in mind that shape is in extended mode right now
					sf::FloatRect thisrect(
						shape.getGlobalBounds().left,
						shape.getGlobalBounds().top + (size.y * shape.getScale().y * i), // moves down by the amount of i
						size.x * shape.getScale().x,
						size.y * shape.getScale().y
					);

					// checks intersection with mouse for each element
					isSelected[i] = thisrect.intersects(mouseRect);
				}
			}
		}
	}
	void Dropdown::handleEvents(const sf::Event& event)
	{
		// if the leftmousebutton is enabled and this object is not inactive
		if (event.mouseButton.button == sf::Mouse::Left && !isInactive)
		{
			// if mouse is pressed and the main element is selected
			if (event.type == sf::Event::MouseButtonPressed && isSelected[0])
			{
				// play button sound
				if (sound.getStatus() != sf::Music::Status::Playing && isActive[0] == false)
					sound.play();

				// drop down
				shape.setTextureRect(sf::IntRect((int)size.x, 0, (int)size.x, int(size.y * isSelected.size())));
				shape.setSize(sf::Vector2f(size.x, size.y * isSelected.size()));

				// set main bool to true (makes all items viewable & selectable)
				isActive[0] = true;
			}
			// if dropped down & left mouse button released & the mouse isn't on the main element
			else if (isActive[0] && event.type == sf::Event::MouseButtonReleased && !isSelected[0])
			{
				// iterate through each element
				for (int i = 0; i < int(isSelected.size()); i++)
				{
					if (isSelected[i]) //check if selected
					{
						// play button sound
						if (sound.getStatus() != sf::Music::Status::Playing)
							sound.play();

						// make button active
						isActive[i] = true;

						// if the dropdown's displayed information should change
						if (!isStatic)
						{
							//change text
							droptext[0].setString(droptext[i].getString());

							centerTextInBounds(droptext[0], { shape.getGlobalBounds().left,
															  shape.getGlobalBounds().top,
															  size.x * shape.getScale().x,
															  size.y * shape.getScale().y });

							/*if (dropcolor[i].getFillColor() != sf::Color::Transparent) // if color is used
								setDropColor(0, dropcolor[i].getFillColor()); //change color
							*/
						}

						break;
					}
					else //if not selected make sure its inactive
						isActive[i] = false;
				}

				// (if lmb is pressed) minimalize the dropdown back (no matter what) 
				shape.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
				shape.setSize(size);
			}
		}

		// if dropped down or first element is selected
		if ((isActive[0] || isSelected[0]) && !isInactive)
			shape.setOutlineThickness(outlineThickness);
		else
			shape.setOutlineThickness(0);

		drawHighlight = false; // do not draw highlight by default

		if (isActive[0]) // if dropped down
		{
			for (int i = 1; i < int(isSelected.size()); i++) // for every element
			{
				if (isSelected[i]) // if the element is selected
				{
					// set the position of the selection rectangle properly
					highlight.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + size.y * i * shape.getScale().y));
					drawHighlight = true;

					// break because only one can be selected at once
					break;
				}
			}
		}
	}
	void Dropdown::addTextElement(const sf::String text)
	{
		isSelected.push_back(false);
		isActive.push_back(false);
		droptext.push_back({ text, *textAbove.getFont(), dropTextSize });

		// puts added element's text inside its container
		int i = droptext.size() - 1;
		centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
								  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
								  shape.getGlobalBounds().width,
								  shape.getGlobalBounds().height });
	}
	void Dropdown::deleteTextElement(const int index)
	{
		if (index < int(isSelected.size()) ) {
			isSelected.erase(isSelected.begin() + index);
			isActive.erase(isActive.begin() + index);
			droptext.erase(droptext.begin() + index);

			// repositions elements properly after the deleted element
			for (int i = index; i < int(isSelected.size()); i++) {
				centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
						  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
						  shape.getGlobalBounds().width,
						  shape.getGlobalBounds().height });
			}
		}
		else {
			std::cout << "WARNING! Dropdown -- delete nr." << index;
			std::cout << " out of vector size - COMMAND IGNORED" << std::endl;
		}
	}
	void Dropdown::setTexture(const sf::Texture& texture)
	{
		shape.setTexture(&texture);
		if(!isInactive) shape.setTextureRect({ 0, 0, int(size.x), int(size.y) });
	}
	void Dropdown::setFont(const sf::Font& param)
	{
		textAbove.setFont(param);
		centerTextInBounds(textAbove, { shape.getGlobalBounds().left,
								shape.getGlobalBounds().top - shape.getGlobalBounds().height,
								shape.getGlobalBounds().width,
								shape.getGlobalBounds().height });

		for (int i = 0; i < int(droptext.size()); i++)
		{
			droptext[i].setFont(param);
			centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
											  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
											  shape.getGlobalBounds().width,
											  shape.getGlobalBounds().height });
		}
	}
	void Dropdown::setFillColor(const sf::Color& color)
	{
		shape.setFillColor(color);
		shapeColor = color;
	}
	void Dropdown::setSelectColor(const sf::Color& color)
	{
		shape.setOutlineColor(color);
	}
	void Dropdown::setSize(const sf::Vector2f& in_size)
	{
		size = in_size;
		shape.setSize(in_size);
	}
	void Dropdown::setPosition(const sf::Vector2f& position)
	{
		shape.setPosition(position);
		centerTextInBounds(textAbove, { shape.getGlobalBounds().left,
										shape.getGlobalBounds().top - shape.getGlobalBounds().height,
										shape.getGlobalBounds().width,
										shape.getGlobalBounds().height });

		for (int i = 0; i < int(droptext.size()); i++)
		{
			centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
											  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
											  shape.getGlobalBounds().width,
											  shape.getGlobalBounds().height });
		}
	}
	void Dropdown::setAboveString(const sf::String& string)
	{
		textAbove.setString(string);
		centerTextInBounds(textAbove, { shape.getGlobalBounds().left,
								shape.getGlobalBounds().top - shape.getGlobalBounds().height,
								shape.getGlobalBounds().width,
								shape.getGlobalBounds().height });

	}
	void Dropdown::setAboveSize(const unsigned charSize)
	{
		textAbove.setCharacterSize(charSize);
		centerTextInBounds(textAbove, { shape.getGlobalBounds().left,
								shape.getGlobalBounds().top - shape.getGlobalBounds().height,
								shape.getGlobalBounds().width,
								shape.getGlobalBounds().height });

	}
	void Dropdown::setDropTextSize(const unsigned charSize)
	{
		dropTextSize = charSize;

		for (int i = 0; i < int(droptext.size()); i++) {
			droptext[i].setCharacterSize(dropTextSize);

			centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
								  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
								  shape.getGlobalBounds().width,
								  shape.getGlobalBounds().height });
		}
	}
	void Dropdown::setDropString(const int i, const sf::String& text)
	{
		droptext[i].setString(text);

		centerTextInBounds(droptext[i], { shape.getGlobalBounds().left,
					  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
					  shape.getGlobalBounds().width,
					  shape.getGlobalBounds().height });
	}
	void Dropdown::setInactivity(const bool in_isInactive)
	{
		if (isInactive && !in_isInactive) {
			// set original shape color back
			shape.setFillColor(shapeColor);
		}
		else if (!isInactive && in_isInactive) {
			// gets rid of selected outline if there is any
			isActive[0] = false;
			isSelected[0] = false;
			shape.setOutlineThickness(0);

			// set greyish color to shape
			shape.setFillColor({ 150, 150, 150 });
		}

		isInactive = in_isInactive;
	}
	void Dropdown::setStaticism(const bool in_isStatic)
	{
		isStatic = in_isStatic;
	}
	void Dropdown::setSoundFX(const sf::SoundBuffer& buffer)
	{
		this->sound.setBuffer(buffer);
	}
	bool Dropdown::activated(const int i)
	{
		if (isActive[i]) {
			isActive[i] = false;
			return true;
		}
		else return false;
	}
	int Dropdown::getNrofElem()
	{
		return int(isSelected.size());
	}
	sf::String Dropdown::getDropString(const int i)
	{
		return droptext[i].getString();
	}
}
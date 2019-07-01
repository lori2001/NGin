#include "Dropdown.h"

#include "../Base/Logger.h"
#include "Cursor.h"

namespace NGin::UI
{
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);

		if (drawHighlight) {
			target.draw(highlight);
		}

		for (int i = 0; i < int(texts.size()); i++) {

			// checks if the fonts are properly defined and prints a warning if not
			if ((texts[i].getString() != "") && texts[i].getFont() == nullptr) {
				Logger::logOnce("Dropdown nr." + std::to_string(Elemindex) + " -> Text nr." + std::to_string(i)
				+ " set but font NOT initialized! -> TEXT MAY NOT BE DISPLAYED!", Logger::Severity::Warning);
			}

			if (i == 0 || isActive[0]) {
				target.draw(texts[i]);
			}
		}
	}
	void Dropdown::select(const sf::Vector2f& mouse)
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
		if (!isInactive) {
			// if the leftmousebutton is enabled
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// if mouse is pressed and the main element is selected
				if (event.type == sf::Event::MouseButtonPressed && isSelected[0])
				{
					// play feedback sound
					Cursor::playSound();

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
							// play feedback sound
							Cursor::playSound();

							// make button active
							isActive[i] = true;

							// if the dropdown's displayed information should change
							if (!isStatic)
							{
								//change text
								texts[0].setString(texts[i].getString());

								// center the new text properly
								centerTextInBounds(texts[0], { shape.getGlobalBounds().left + outlineThickness,
																  shape.getGlobalBounds().top + outlineThickness,
																  size.x * shape.getScale().x,
																  size.y * shape.getScale().y });
							}

							break;
						}
						else // if not selected make sure its not active
							isActive[i] = false;
					}

					// (if lmb is released) minimalize the dropdown back (no matter what) 
					shape.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
					shape.setSize(size);
				}
			}

			// if dropped down or first element is selected
			if ((isActive[0] || isSelected[0]))
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
	}
	void Dropdown::addDropString(const sf::String text)
	{
		isSelected.push_back(false);
		isActive.push_back(false);
		texts.push_back({ text, *texts[0].getFont(), texts[0].getCharacterSize() });

		// puts added element's text inside its container
		int i = texts.size() - 1;
		centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
								  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
								  shape.getGlobalBounds().width,
								  shape.getGlobalBounds().height });
	}
	void Dropdown::deleteDropString(const int index)
	{
		if (index < int(isSelected.size()) ) {
			isSelected.erase(isSelected.begin() + index);
			isActive.erase(isActive.begin() + index);
			texts.erase(texts.begin() + index);

			// repositions elements properly after the deleted element
			for (int i = index; i < int(isSelected.size()); i++) {
				centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
						  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
						  shape.getGlobalBounds().width,
						  shape.getGlobalBounds().height });
			}
		}
		else {
			Logger::logOnce("Dropdown nr." + std::to_string(Elemindex) + "-> cannot delete text nr." + std::to_string(index)
			+ " (vector size is " + std::to_string(isSelected.size()) + ") -> COMMAND IGNORED", Logger::Severity::Warning);
		}
	}
	void Dropdown::setTexture(sf::Texture& texture)
	{
		texture.setRepeated(true);

		shape.setTexture(&texture);
		if(!isInactive) shape.setTextureRect({ 0, 0, int(size.x), int(size.y) });
	}
	void Dropdown::setFont(sf::Font& in_font)
	{
		for (int i = 0; i < int(texts.size()); i++)
		{
			texts[i].setFont(in_font);

			centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
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

		for (int i = 0; i < int(texts.size()); i++)
		{
			centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
											  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
											  shape.getGlobalBounds().width,
											  shape.getGlobalBounds().height });
		}
	}
	void Dropdown::setTextSize(const unsigned charSize)
	{
		for (int i = 0; i < int(texts.size()); i++) {
			texts[i].setCharacterSize(charSize);

			centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
								  shape.getGlobalBounds().top + shape.getGlobalBounds().height * i,
								  shape.getGlobalBounds().width,
								  shape.getGlobalBounds().height });
		}
	}
	void Dropdown::setDropString(const int i, const sf::String& text)
	{
		texts[i].setString(text);

		centerTextInBounds(texts[i], { shape.getGlobalBounds().left,
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
		return texts[i].getString();
	}
}
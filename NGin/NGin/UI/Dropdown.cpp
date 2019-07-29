#include "Dropdown.h"

#include "../Base/Console.h"
#include "Cursor.h"

namespace ngin::ui
{
	void Dropdown::draw(sf::RenderWindow& window)
	{
		window.draw(shape_);

		if (drawHighlight_) {
			window.draw(highlight_);
		}

		if (texts_[0].getFont() != 0) {
			for (int i = 0; i < int(texts_.size()); i++) {
				if ((i == 0 || isActives_[0]) && texts_[i].getString() != "")
					window.draw(texts_[i]);
			}
		}
	}
	void Dropdown::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_)
		{
			sf::FloatRect mainrect(shape_.getGlobalBounds().left,
								   shape_.getGlobalBounds().top,
								   size_.x * shape_.getScale().x,
								   size_.y * shape_.getScale().y);

			sf::FloatRect mouseRect = { mouse, { 1,1 } };

			isSelecteds_[0] = mainrect.intersects(mouseRect);

			// if the main element has been pressed
			if (isActives_[0])
			{
				for (int i = 1; i < int(isSelecteds_.size()); i++)
				{
					// keep in mind that shape is in extended mode right now
					sf::FloatRect thisrect(
						shape_.getGlobalBounds().left,
						shape_.getGlobalBounds().top + (size_.y * shape_.getScale().y * i),
						size_.x * shape_.getScale().x,
						size_.y * shape_.getScale().y
					);

					// checks intersection with mouse for each element
					isSelecteds_[i] = thisrect.intersects(mouseRect);
				}
			}

			for (int i = 1; i < static_cast<int>(isActives_.size()); i++)
				isActives_[i] = false;

			// if the leftmousebutton is enabled
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// if mouse is pressed and the main element is selected
				if (event.type == sf::Event::MouseButtonPressed && isSelecteds_[0])
				{
					// play feedback sound
					Cursor::playSound();

					// drop down
					shape_.setTextureRect(sf::IntRect((int)size_.x, 0, (int)size_.x, int(size_.y * isSelecteds_.size())));
					shape_.setSize(sf::Vector2f(size_.x, size_.y * isSelecteds_.size()));

					// set main bool to true (makes all items viewable & selectable)
					isActives_[0] = true;
				}
				// if dropped down & left mouse button released & the mouse isn't on the main element
				else if (isActives_[0] && event.type == sf::Event::MouseButtonReleased && !isSelecteds_[0])
				{
					// iterate through each element
					for (int i = 0; i < int(isSelecteds_.size()); i++)
					{
						if (isSelecteds_[i]) //check if selected
						{
							// play feedback sound
							Cursor::playSound();

							// make button active
							isActives_[i] = true;

							// if the dropdown's displayed information should change
							if (!isStatic_)
							{
								//change text
								texts_[0].setString(texts_[i].getString());

								// center the new text properly
								align::centerTextInBounds(texts_[0], closedGlobalBounds_);
							}

							break;
						}
						else // if not selected make sure its not active
							isActives_[i] = false;
					}

					// (if lmb is released) minimalize the dropdown back (no matter what) 
					shape_.setTextureRect(sf::IntRect(0, 0, int(size_.x), int(size_.y)));
					shape_.setSize(size_);
				}
			}

			// if dropped down or first element is selected
			if (isActives_[0] || isSelecteds_[0])
				shape_.setOutlineThickness(selectThickness_);
			else
				shape_.setOutlineThickness(0);

			drawHighlight_ = false; // do not draw highlight by default

			if (isActives_[0]) // if dropped down
			{
				for (int i = 1; i < int(isSelecteds_.size()); i++) // for every element
				{
					if (isSelecteds_[i]) // if the element is selected
					{
						// set the position of the selection rectangle properly
						highlight_.setPosition(sf::Vector2f(shape_.getPosition().x, shape_.getPosition().y + size_.y * i * shape_.getScale().y));
						drawHighlight_ = true;

						// break because only one can be selected at once
						break;
					}
				}
			}
		}
	}
	void Dropdown::addDropString(const sf::String& text)
	{
			isSelecteds_.push_back(false);
			isActives_.push_back(false);
			int i = texts_.size();

			if (texts_[0].getFont() != 0) {
				texts_.push_back({ text, *texts_[0].getFont(), characterSize_ });
			}
			else {
				sf::Text tmp;
				tmp.setString(text);
				tmp.setCharacterSize(characterSize_);
				texts_.push_back(tmp);

				NG_LOG_WARN("Dropdown nr.", getElementIndex(), " -> Text nr.", i,
					" set but font NOT initialized! -> TEXT MAY NOT BE DISPLAYED!");
			}

			// puts added element's text inside its container
			align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::deleteDropString(const int index)
	{
		if (index < int(isSelecteds_.size()) ) {
			isSelecteds_.erase(isSelecteds_.begin() + index);
			isActives_.erase(isActives_.begin() + index);
			texts_.erase(texts_.begin() + index);

			// repositions elements properly after the deleted element
			for (int i = index; i < int(isSelecteds_.size()); i++) {
				align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
			}
		}
		else {
			NG_LOG_WARN("Dropdown nr.", getElementIndex(), " -> cannot delete text nr.",
				index, " (vector size is ", isSelecteds_.size(), ") -> COMMAND IGNORED");
		}
	}
	void Dropdown::setTexture(sf::Texture& texture)
	{
		texture.setRepeated(true);

		shape_.setTexture(&texture);
		if(!isDisabled_) shape_.setTextureRect({ 0, 0, int(size_.x), int(size_.y) });
	}
	void Dropdown::setFont(sf::Font& font)
	{
		for (int i = 0; i < int(texts_.size()); i++)
		{
			texts_[i].setFont(font);

			align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
		}
	}
	void Dropdown::setFillColor(const sf::Color& color)
	{
		shape_.setFillColor(color);
		shapeColor_ = color;
	}
	void Dropdown::setSize(const sf::Vector2f& size)
	{
		size_ = size;
		shape_.setSize(size);
		highlight_.setSize(size);

		closedGlobalBounds_.width = shape_.getGlobalBounds().width;
		closedGlobalBounds_.height = shape_.getGlobalBounds().height;

		for (int i = 0; i < int(texts_.size()); i++)
			align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::setPosition(const sf::Vector2f& position)
	{
		shape_.setPosition(position);

		closedGlobalBounds_.left = shape_.getGlobalBounds().left;
		closedGlobalBounds_.top = shape_.getGlobalBounds().top;

		for (int i = 0; i < int(texts_.size()); i++)
			align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::setCharacterSize(const unsigned characterSize)
	{
		characterSize_ = characterSize;

		for (int i = 0; i < int(texts_.size()); i++) {
			texts_[i].setCharacterSize(characterSize_);

			align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
		}
	}
	void Dropdown::setDropString(const int i, const sf::String& text)
	{
		if (i == 0 && texts_[0].getFont() == 0)
			NG_LOG_WARN("Dropdown nr.", getElementIndex(), " -> Text nr.", i,
				" set but font NOT initialized! -> TEXT MAY NOT BE DISPLAYED!");

		texts_[i].setString(text);

		align::centerTextInBounds(texts_[i], closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::setDisabled(const bool isDisabled)
	{
		if (isDisabled_ && !isDisabled) {
			// set original shape color back
			shape_.setFillColor(shapeColor_);
		}
		else if (!isDisabled_ && isDisabled) {
			// gets rid of selected outline if there is any
			isActives_[0] = false;
			isSelecteds_[0] = false;
			shape_.setOutlineThickness(0);

			// set greyish color to shape
			shape_.setFillColor({ 150, 150, 150 });
		}

		isDisabled_ = isDisabled;
	}
}
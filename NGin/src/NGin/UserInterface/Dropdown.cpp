#include "Dropdown.h"

#include "../System/Console.h"
#include "Cursor.h"

namespace ng
{
	void Dropdown::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_)
		{
			wasActive_ = isActive_;
			isSelecteds_[0] = closedGlobalBounds_.contains(mouse);

			// if the main element has been pressed
			if (isActive_)
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
					isSelecteds_[i] = thisrect.contains(mouse);
				}
			}

			// if the leftmousebutton is enabled and there's no element blocking
			if (event.mouseButton.button == sf::Mouse::Left &&
				(blockingException_== getUIElementIndex() || blockingException_ == -1))
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
					isActive_ = true;
					blockingException_ = getUIElementIndex();
				}
				// if dropped down & left mouse button released & the mouse isn't on the main element
				else if (isActive_ && event.type == sf::Event::MouseButtonReleased && !isSelecteds_[0])
				{
					// iterate through each element
					for (int i = 0; i < int(isSelecteds_.size()); i++)
					{
						if (isSelecteds_[i]) //check if selected
						{
							// play feedback sound
							Cursor::playSound();

							// make button active
							activeDrop_ = i;

							// if the dropdown's displayed information should change
							if (!isStatic_)
							{
								//change text
								drops_[0].text.setString(drops_[i].text.getString());
								drops_[0].text.setFillColor(drops_[i].text.getFillColor());
								drops_[0].shape.setFillColor(drops_[i].shape.getFillColor());

								// center the new text properly
								centerTextInBounds(drops_[0].text, closedGlobalBounds_);
							}

							break;
						}
					}

					// (if lmb is released) minimalize the dropdown back (no matter what) 
					shape_.setTextureRect(sf::IntRect(0, 0, int(size_.x), int(size_.y)));
					shape_.setSize(size_);
					isActive_ = false;
					blockingException_ = -1;
				}
			}

			drawHighlight_ = false; // do not draw highlight by default

			if (isActive_) // if dropped down
			{
				shape_.setOutlineThickness(selectThickness_);
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
			else if(isSelecteds_[0])
				shape_.setOutlineThickness(selectThickness_);
			else
				shape_.setOutlineThickness(0);
		}
	}
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape_);

		for (int i = 0; i < int(drops_.size()); i++) {
			if (i == 0 || isActive_) {
				target.draw(drops_[i].shape);
			}
		}

		if (drops_[0].text.getFont() != 0) {
			for (int i = 0; i < int(drops_.size()); i++) {
				if ((i == 0 || isActive_) && drops_[i].text.getString() != "") {
					target.draw(drops_[i].text);
				}
			}
		}
		else {
			for (int i = 0; i < int(drops_.size()); i++) {
				if (drops_[i].text.getString() != "") {
					NG_LOG_ONCE_WARN("Dropdown nr.", getUIElementIndex(), " -> Text nr.", i,
						" set but font NOT initialized! -> TEXT MAY NOT BE DISPLAYED!");
				}
			}
		}

		if (drawHighlight_) {
			target.draw(highlight_);
		}
	}
	void Dropdown::addDropString(const std::string& string)
	{
			isSelecteds_.push_back(false);
			int i = drops_.size();

			if (drops_[0].text.getFont() != 0) {
				drops_.push_back(sf::Text{ string, *drops_[0].text.getFont(), characterSize_ });
				drops_[i].text.setFillColor(drops_[0].text.getFillColor());
			}
			else {
				sf::Text tmp;
				tmp.setString(string);
				tmp.setCharacterSize(characterSize_);
				tmp.setFillColor(drops_[0].text.getFillColor());
				drops_.push_back(tmp);
			}

			// puts added element's text inside its container
			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::addDropText(const sf::Text& text)
	{
		isSelecteds_.push_back(false);
		int i = drops_.size();

		drops_.push_back(text);

		// puts added element's text inside its container
		centerTextInBounds(drops_.back().text, closedGlobalBounds_, closedGlobalBounds_.height * i);
	}
	void Dropdown::setDropTextVec(const std::vector<sf::Text>& textVector)
	{
		drops_.clear();
		isSelecteds_.clear();

		for (auto &it: textVector) {
			drops_.push_back(it);
		}
	}
	void Dropdown::addDropColor(const sf::Color& color)
	{
		isSelecteds_.push_back(false);
		int i = drops_.size();

		sf::RectangleShape temp;
		temp.setSize({ size_.x - 6, size_.y - 6 });
		temp.setPosition(getPosition().x + 3, closedGlobalBounds_.top + closedGlobalBounds_.height * i + 3);
		temp.setScale(shape_.getScale());
		temp.setFillColor(color);

		drops_.push_back(temp);
	}
	void Dropdown::deleteDrop(const int index)
	{
		if (index < int(isSelecteds_.size()) ) {
			isSelecteds_.erase(isSelecteds_.begin() + index);
			drops_.erase(drops_.begin() + index);

			// repositions elements properly after the deleted element
			for (int i = index; i < int(isSelecteds_.size()); i++) {
				centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
				drops_[i].shape.setPosition(getPosition().x + 3, closedGlobalBounds_.top + closedGlobalBounds_.height * i + 3);
			}
		}
		else {
			NG_LOG_WARN("Dropdown nr.", getUIElementIndex(), " -> cannot delete text nr.",
				index, " (vector size is ", isSelecteds_.size(), ") -> COMMAND IGNORED");
		}
	}
	void Dropdown::deleteDrops()
	{
		isSelecteds_.clear();
		drops_.clear();
	}
	void Dropdown::setTexture(const ng::TexturePtr texture)
	{
		texture_ = texture;
		texture_->setRepeated(true);

		shape_.setTexture(&*texture_);
		if(!isDisabled_) shape_.setTextureRect({ 0, 0, int(size_.x), int(size_.y) });
	}
	void Dropdown::setFont(const ng::FontPtr font)
	{
		font_ = font;

		for (int i = 0; i < int(drops_.size()); i++)
		{
			drops_[i].text.setFont(*font_);

			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
		}
	}
	void Dropdown::setBaseColor(const sf::Color& color)
	{
		shape_.setFillColor(color);
		shapeColor_ = color;
	}
	void Dropdown::setDropTextColor(const int i, const sf::Color& color)
	{
		if (i < int(drops_.size())) {
			drops_[i].text.setFillColor(color);
		}
		else {
			NG_LOG_WARN("Text color (", color.r, color.g, color.b, ") could not be set "
				"to element nr.", getUIElementIndex(), " dropdown nr.", i);
		}
	}
	void Dropdown::setDropColor(const int i, const sf::Color& color)
	{
		if (i < int(drops_.size())) {
			drops_[i].shape.setFillColor(color);
		}
		else {
			NG_LOG_WARN("Shape color (", color.r, color.g, color.b, ") could not be set "
				"to element nr.", getUIElementIndex(), " dropdown nr.", i);
		}
	}
	void Dropdown::setTextColor(const sf::Color& color)
	{
		for (int i = 0; i < int(drops_.size()); i++)
		{
			drops_[i].text.setFillColor(color);
		}
	}
	void Dropdown::setSize(const sf::Vector2f& size)
	{
		size_ = size;
		shape_.setSize(size);
		highlight_.setSize(size);

		closedGlobalBounds_.width = size_.x * shape_.getScale().x;
		closedGlobalBounds_.height = size_.y * shape_.getScale().y;

		for (int i = 0; i < int(drops_.size()); i++) {
			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
			
			if(i == 0) drops_[0].shape.setSize({ size_.x * 0.85F - 6, size_.y - 6 });
			else       drops_[i].shape.setSize({ size_.x - 6, size_.y - 6 });
			drops_[i].shape.setPosition(getPosition().x + 3, closedGlobalBounds_.top + closedGlobalBounds_.height * i + 3);
		}
	}
	void Dropdown::setScale(const sf::Vector2f& scale)
	{
		shape_.setScale(scale);
		highlight_.setScale(scale);

		closedGlobalBounds_.width = size_.x * shape_.getScale().x;
		closedGlobalBounds_.height = size_.y * shape_.getScale().y;

		for (int i = 0; i < int(drops_.size()); i++) {
			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);

			drops_[i].shape.setScale(scale);
			drops_[i].shape.setPosition(getPosition().x + 3, closedGlobalBounds_.top + closedGlobalBounds_.height * i + 3);
		}
	}
	void Dropdown::setPosition(const sf::Vector2f& position)
	{
		shape_.setPosition(position);

		closedGlobalBounds_.left = shape_.getGlobalBounds().left;
		closedGlobalBounds_.top = shape_.getGlobalBounds().top;

		for (int i = 0; i < int(drops_.size()); i++) {
			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
			drops_[i].shape.setPosition(getPosition().x + 3, closedGlobalBounds_.top + closedGlobalBounds_.height * i + 3);
		}
	}
	void Dropdown::setCharacterSize(const unsigned characterSize)
	{
		characterSize_ = characterSize;

		for (int i = 0; i < int(drops_.size()); i++) {
			drops_[i].text.setCharacterSize(characterSize_);

			centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);
		}
	}
	void Dropdown::setDropString(const int i, const std::string& text)
	{
		drops_[i].text.setString(text);
		centerTextInBounds(drops_[i].text, closedGlobalBounds_, closedGlobalBounds_.height * i);

		// if the main drop is getting set make sure activeDrop doesn't return anything weird
		if (i == 0) activeDrop_ = 0;
	}
	void Dropdown::setDisabled(const bool isDisabled)
	{
		if (isDisabled_ && !isDisabled) {
			// set original shape color back
			shape_.setFillColor(shapeColor_);
		}
		else if (!isDisabled_ && isDisabled) {
			// gets rid of selected outline if there is any
			isActive_ = false;
			isSelecteds_[0] = false;
			shape_.setOutlineThickness(0);

			// set greyish color to shape
			shape_.setFillColor({ 120, 120, 120 });
		}

		isDisabled_ = isDisabled;
	}
	void Dropdown::setActiveDrop(const int i)
	{
		activeDrop_ = i;

		// if the dropdown's displayed information should change
		if (!isStatic_)
		{
			//change text
			drops_[0].text.setString(drops_[i].text.getString());
			drops_[0].text.setFillColor(drops_[i].text.getFillColor());
			drops_[0].shape.setFillColor(drops_[i].shape.getFillColor());

			// center the new text properly
			centerTextInBounds(drops_[0].text, closedGlobalBounds_);
		}
	}
}
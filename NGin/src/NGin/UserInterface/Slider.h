#pragma once
#include "UIElement.h"
#include "UISettings.h"

#include "Button.h"

namespace ng {
	class Slider : public UIElement {
	public:
		Slider() : UIElement() {
			setSelectThickness(-UISettings::DEFAULT::SELECT_THICKNESS); // selection goes inside container
			// button has to be centered in order to align properly
			mark_.setOrigin({ mark_.getGlobalBounds().width / 2, mark_.getGlobalBounds().height / 2 });
			setPosition({0, 0});
			adjustSliderBox();
			adjustMarkPos();
		}
		Slider(const ng::TexturePtr texture,
			const sf::Vector2f& shapeSize,
			const sf::Vector2f& arrowSize,
			const sf::Vector2f& markSize,
			const sf::Color& selectColor,
			const sf::Color& baseColor,
			const float selectThickness,
			const sf::Vector2f& scale = { 1.0F, 1.0F },
			const sf::Vector2f& position = { 0, 0 }) : UIElement()
		{
			setBaseColor(baseColor);
			setSelectColor(selectColor);
			setSelectThickness(-UISettings::DEFAULT::SELECT_THICKNESS); // selection goes inside container
			setSizes(shapeSize, arrowSize, markSize);
			setTexture(texture);

			// button has to be centered in order to align properly
			mark_.setOrigin({ mark_.getGlobalBounds().width / 2, mark_.getGlobalBounds().height / 2 });

			setPosition(position);
			setScale(scale);
			
			adjustSliderBox();
			adjustMarkPos();
		}
		Slider(const UISettings& uiSettings) :
			Slider(NG_TEXTURE_SPTR(uiSettings.sliderLoc),
				uiSettings.sliderShapeSize,
				uiSettings.sliderArrowSize,
				uiSettings.sliderMarkSize,
				uiSettings.selectColor,
				uiSettings.baseColor,
				uiSettings.selectThickness)
		{}
		// inherits: texture, sizes, selectColor, selectThickness, scale
		Slider(const ng::Slider& styler, const sf::Vector2f& position = {0, 0}) :
			Slider(styler.getTexture(),
				styler.getShapeSize(),
				styler.getArrowSize(),
				styler.getMarkSize(),
				styler.getSelectColor(),
				styler.getBaseColor(),
				styler.getSelectThickness(),
				styler.getScale(),
				position)
		{}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(const ng::TexturePtr texture);
		void setBaseColor(const sf::Color& color);
		void setContainerColor(const sf::Color& color) { container_.setFillColor(color); }
		void setMarkColor(const sf::Color& color) { mark_.setFillColor(color); }
		void setArrowsColor(const sf::Color& color);
		void setSliderBox(const sf::FloatRect& sliderBox) { sliderBox_ = sliderBox; }
		void setPosition(const sf::Vector2f& position);
		void setLevel(const float level);
		void setSizes(const sf::Vector2f& shapeSize, const sf::Vector2f& arrowSize, const sf::Vector2f& markSize);
		void setScale(const sf::Vector2f& scale);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float selectSize);
		void setDisabled(const bool isDisabled) { isDisabled_ = isDisabled; }

		const ng::TexturePtr getTexture() const { return texture_; }
		sf::Vector2f getShapeSize() const { return container_.getSize(); }
		sf::Vector2f getArrowSize() const { return leftButton_.getSize(); }
		sf::Vector2f getMarkSize() const { return mark_.getSize(); }
		sf::Color getSelectColor() const { return container_.getOutlineColor(); }
		sf::Color getBaseColor() const { return container_.getFillColor(); }
		float getSelectThickness() const { return selectThickness_; }
		float getLevel() const { return level_; }
		sf::Vector2f getSize() const { return { leftButton_.getSize().x + container_.getSize().x + rightButton_.getSize().x, container_.getSize().y }; }
		sf::Vector2f getScale() const { return container_.getScale(); }
		sf::Vector2f getPosition() const { return leftButton_.getPosition(); }
		bool hasChanged() const { return hasChanged_; }
		sf::FloatRect getGlobalBounds() const;
	private:
		// adjust button position based on level
		void adjustMarkPos();
		// set up the mark's virtual box (has some additional offset calibrated for default textures)
		void adjustSliderBox();
	private:

		ng::TexturePtr texture_;

		sf::FloatRect sliderBox_; // a box for the mark to move in
		sf::RectangleShape container_;
		sf::RectangleShape mark_;
		Button leftButton_; // the button on the left of the window
		Button rightButton_; // the button on the right of the window

		float selectThickness_;
		float level_ = 0; // the output percentage (0 <= level <= 1)

		bool isSliding_ = false; // true if lmb is on hold (then slider is active)
		bool isDisabled_ = false; // if true the object can't be selected or modified
		bool isSelected_ = false; // used for the main section
		bool hasChanged_ = false; // signals to user wheter level has been changed compared to last time
	};
}
#pragma once
#include "UIElement.h"
#include "UISettings.h"

#include "../System/Resources.h"
#include "Button.h"

namespace ng {
	class Switcher : public UIElement {
	public:
		Switcher() : UIElement() {}
		Switcher(
			const ng::TexturePtr texture,
			const sf::Vector2f& buttonSize,
			const sf::Vector2f& markSize,
			const sf::Color& selectColor,
			const sf::Color& baseColor,
			const float selectThickness,
			const sf::Vector2f& scale = { 1.0F, 1.0F },
			const sf::Vector2f& position = { 0, 0 }) : UIElement()
		{
			setButtonSize(buttonSize);
			setMarkSize(markSize);
			setPosition(position);
			setScale(scale);
			setSelectColor(selectColor);
			setBaseColor(baseColor);
			setSelectThickness(selectThickness);
			setTexture(texture);
		}
		Switcher(const UISettings& uiSettings) :
			Switcher(
				NG_TEXTURE_SPTR(uiSettings.switcherTextureLoc),
				uiSettings.switcherButtonSize,
				uiSettings.switcherMarkSize,
				uiSettings.selectColor,
				uiSettings.baseColor,
				uiSettings.selectThickness)
		{}
		// inherits other switcher's properties:
		// button size, mark size, texture, select color, select thickness, scale
		Switcher(const Switcher& styler, const sf::Vector2f& position = {0, 0}) :
			Switcher(
				styler.getTexture(),
				styler.getButtonSize(),
				styler.getMarkSize(),
				styler.getSelectColor(),
				styler.getButtonColor(),
				styler.getSelectThickness(),
				styler.getScale(),
				position)
		{}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(const ng::TexturePtr texture);
		void setPosition(const sf::Vector2f& position);
		void setScale(const sf::Vector2f& scale);
		void setButtonSize(const sf::Vector2f& size);
		void setMarkSize(const sf::Vector2f& size);
		void setSize(const sf::Vector2f& size);
		void setBaseColor(const sf::Color& color);
		void setMarkColor(const sf::Color& color);
		void setButtonColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float thickness);
		void setIsActive(const bool active);
		void setDisabled(const bool isDisabled);

		bool isActive() const { return isActive_; }
		bool hasChanged() const { return hasChanged_; }
		sf::Vector2f getButtonSize() const { return button_.getSize(); }
		sf::Vector2f getMarkSize() const { return mark_.getSize(); }
		sf::Vector2f getSize() const { return button_.getSize(); }
		sf::Vector2f getPosition() const { return button_.getPosition(); }
		sf::Vector2f getScale() const { return button_.getScale(); }
		sf::Color getSelectColor() const { return button_.getSelectColor(); }
		sf::Color getButtonColor() const { return button_.getBaseColor(); }
		float getSelectThickness() const { return button_.getSelectThickness(); }
		ng::TexturePtr getTexture() const { return texture_; }
		sf::FloatRect getGlobalBounds() const { return button_.getGlobalBounds(); }
	private:
		ng::TexturePtr texture_;

		Button button_;
		sf::RectangleShape mark_;

		bool isActive_ = false;
		bool hasChanged_ = false;
	};
}
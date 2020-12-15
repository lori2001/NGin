#pragma once
#include "UIElement.h"
#include "UISettings.h"
#include "../Utilities/Align.h"

namespace ng
{
	class Button : public UIElement
	{
	public:
		Button() : UIElement() {
			setCharacterSize(UISettings::DEFAULT::CHARACTER_SIZE);
			setSelectThickness(UISettings::DEFAULT::SELECT_THICKNESS);
		}
		Button(
			const ng::TexturePtr buttonTexture,
			const ng::FontPtr font,
			const sf::String& string,
			const sf::Vector2f& buttonSize,
			const unsigned characterSize,
			const sf::Color& fontColor,
			const sf::Color& selectColor,
			const sf::Color& baseColor,
			const float selectThickness,
			const sf::Vector2f& scale = { 1.0F, 1.0F },
			const sf::Vector2f& position = {0, 0}) : Button()
		{
			setBaseColor(baseColor);
			setFont(font);
			setCharacterSize(characterSize);
			setTextColor(fontColor);
			setSize(buttonSize);
			setTexture(buttonTexture);
			setSelectColor(selectColor);
			setSelectThickness(selectThickness);
			setString(string);
			setScale(scale);
			setPosition(position);
		}
		// texture, font, size, characterSize, fontColor, selectColor, selectThickness, scale
		Button(const ng::Button& styler,
			const sf::String string,
			const sf::Vector2f position = { 0, 0 })
			: Button(
				styler.getTexture(),
				styler.getFont(),
				string,
				styler.getSize(),
				styler.getCharacterSize(),
				styler.getFontColor(),
				styler.getSelectColor(),
				styler.getBaseColor(),
				styler.getSelectThickness(),
				styler.getScale(),
				position
			)
		{}
		Button(const UISettings& uiSettings, const sf::String string = "") :
			Button(
				NG_TEXTURE_SPTR(uiSettings.buttonLoc),
				NG_FONT_SPTR(uiSettings.fontLoc),
				string,
				uiSettings.buttonSize,
				uiSettings.fontSize,
				uiSettings.fontColor,
				uiSettings.selectColor,
				uiSettings.baseColor,
				uiSettings.selectThickness)
		{}
		Button(const sf::Vector2f& size, const ng::TexturePtr texture) : Button() {
			setSize(size);
			setTexture(texture);
		}
		Button(const sf::String& string) :
			Button(string, NG_FONT_SPTR(UISettings::DEFAULT::FONT_LOC)) {}
		Button(const sf::String& string, const ng::FontPtr font) : Button()
		{
			setFont(font);
			setString(string);
		}
		Button(const sf::String& string, const ng::FontPtr font,
			const sf::Vector2f& buttonSize, const ng::TexturePtr texture) : Button()
		{
			setSize(buttonSize);
			setString(string);
			setTexture(texture);
		}

		// Handles input events and plays given sounds and animations whenever needed.
		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setFont(const ng::FontPtr font);
		void setTextColor(const sf::Color& color);
		void setString(const sf::String& text);
		void setTexture(const ng::TexturePtr texture);
		void setTexturePos(const sf::Vector2i position);
		void setBaseColor(const sf::Color& color);
		void setPosition(const sf::Vector2f& position);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float thickness);
		void setOrigin(const sf::Vector2f& origin);
		void setScale(const sf::Vector2f& scale);
		void setCharacterSize(const unsigned size);
		void setSize(const sf::Vector2f size);
		void setDisabled(const bool isDisabled);

		const ng::TexturePtr getTexture() const { return texture_;; }
		sf::Vector2f getScale() const { return shape_.getScale(); }
		const ng::FontPtr getFont() const { return font_; }
		unsigned getCharacterSize() const { return text_.getCharacterSize(); }
		sf::Color getFontColor() const { return text_.getFillColor(); }
		sf::Color getSelectColor() const { return shape_.getOutlineColor(); }
		sf::Color getBaseColor() const { return shape_.getFillColor(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		float getSelectThickness() const { return selectThickness_; }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
		sf::String getString() const { return text_.getString(); }

		bool isPressed() const { return state_ == STATES::PRESSED; }
		bool isActive() const { return state_ == STATES::ACTIVE; }
	private:
		ng::TexturePtr texture_;
		ng::FontPtr font_;

		sf::RectangleShape shape_;

		sf::Text text_;

		float selectThickness_;
		sf::Vector2f textPos_;
		sf::Vector2i texturePos_ = { 0, 0 }; // the position at which textures should be loaded from

		sf::Color shapeColor_;

		enum class STATES {
			NONE = 0,
			DISABLED,
			SELECTED,
			PRESSED,
			ACTIVE,
			UNSELECTED,
		} state_;
	};
}

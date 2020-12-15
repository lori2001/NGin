#pragma once
#include "Button.h"
#include "UIElement.h"

namespace ng {
	class ConfirmDialog : public ng::UIElement
	{
	public:
		enum class DIALOG_TYPE {
			DIALOG_CLOSE_ONLY,
			DIALOG_YES_OR_CLOSE
		};

		ConfirmDialog(DIALOG_TYPE type) : UIElement()
		{
			type_ = type;
			textYOffset_ = -20;
			buttonOffset_ = { 30, 20 };
			isActive_ = false;
			setCharacterSize(30);

			closeButton_.setString("close");

			if (type == DIALOG_TYPE::DIALOG_YES_OR_CLOSE)
			{
				okButton_.setString("ok");
				setButtonScale({ 0.5F, 0.8F });
			}
		}
		ConfirmDialog(DIALOG_TYPE type,
			ng::TexturePtr shapeTexture,
			ng::TexturePtr buttonTexture,
			ng::FontPtr font,
			const std::string& text,
			const sf::Vector2f& size,
			const sf::Vector2f& buttonSize,
			const sf::Color& textColor = sf::Color::White,
			const sf::Color& selectColor = sf::Color::White,
			const sf::Color& baseColor = sf::Color::White,
			const sf::Vector2f & position = { 0, 0 }
			) : ConfirmDialog(type)
		{
			setTextures(buttonTexture, shapeTexture);
			setFont(font);
			setButtonSize(buttonSize);
			setString(text);
			setSize(size);
			setPosition(position);
			setTextColor(textColor);
			setSelectColor(selectColor);
			setBaseColor(baseColor);
		}
		ConfirmDialog(
			const UISettings& uiSettings,
			DIALOG_TYPE type,
			const sf::Vector2f& size,
			const std::string& text = "")
			: ConfirmDialog (
				type,
				NG_TEXTURE_SPTR(uiSettings.confirmDialogLoc),
				NG_TEXTURE_SPTR(uiSettings.buttonLoc),
				NG_FONT_SPTR(uiSettings.fontLoc),
				text,
				size,
				uiSettings.buttonSize,
				uiSettings.fontColor,
				uiSettings.selectColor,
				uiSettings.baseColor)
		{}
		ConfirmDialog(
			const UISettings& uiSettings, DIALOG_TYPE type, const std::string& text = "")
			: ConfirmDialog(uiSettings, type, uiSettings.confirmDialogSize, text)
		{}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// WARNING! Stops other window processes until closed!!!
		// converts the shape's size to window size
		void drawInWindow(const std::string& windowName);

		void setPosition(const sf::Vector2f& position);
		void setButtonSize(const sf::Vector2f& size);
		void setSize(const sf::Vector2f& size);
		void setButtonTexture(const ng::TexturePtr texture);
		void setBaseColor(const sf::Color& color);
		void setShapeTexture(const ng::TexturePtr texture);
		void setTextures(const ng::TexturePtr buttonTexture,
			const ng::TexturePtr shapeTexture);
		void setFont(const ng::FontPtr font);
		void setButtonTextColor(const sf::Color color);
		void setMessageColor(const sf::Color color) { text_.setFillColor(color); }
		void setAllTextColor(const sf::Color color) { setButtonTextColor(color); setMessageColor(color);}
		void setCharacterSize(const unsigned characterSize);
		void setShapeScale(const sf::Vector2f& scale);
		void setButtonScale(const sf::Vector2f& buttonScale);
		void setTextColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color);
		// sets buttons offset relative to the edge of window
		// in case of 1 button only Y offset is available
		// unsigned values expected
		void setButtonOffset(const sf::Vector2f& offset);
		void setString(const std::string& string);
		void setTextYOffset(const float textYOffset);

		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
		sf::Color getShapeColor() const { return shape_.getFillColor(); }

		// in case of one button close is called
		enum class RESPONSE {
			RESPONSE_NONE = 0,
			RESPONSE_OK,
			RESPONSE_CLOSE
		};

		RESPONSE getResponse() { return response_; }

		bool isActive() { return isActive_; }
		void setIsActive(const bool isActive) { isActive_ = isActive; }

	private:
		ng::FontPtr font_;
		ng::TexturePtr shapeTexture_;
		ng::TexturePtr buttonTexture_;

		bool isActive_;
		DIALOG_TYPE type_ = DIALOG_TYPE::DIALOG_YES_OR_CLOSE;
		RESPONSE response_ = RESPONSE::RESPONSE_NONE;

		sf::RectangleShape shape_;
		sf::Text text_;
		float textYOffset_ = 0; // y ofsset of text from center

		sf::Vector2f buttonOffset_;
		Button okButton_;
		Button closeButton_;
	};
}
#pragma once
#include "SFML/Graphics/Color.hpp"
#include "../System/Resources.h"

namespace ng {
	struct UISettings {
		class DEFAULT {
		public:
			static constexpr const char* FONT_LOC = "font.ttf";
			static constexpr unsigned char FONT_COLOR_R = 0;
			static constexpr unsigned char FONT_COLOR_G = 0;
			static constexpr unsigned char FONT_COLOR_B = 0;
			static constexpr unsigned CHARACTER_SIZE = 30;
			static constexpr unsigned char SELECT_COLOR_R = 255;
			static constexpr unsigned char SELECT_COLOR_G = 255;
			static constexpr unsigned char SELECT_COLOR_B = 255;
			static constexpr float SELECT_THICKNESS = 2.5F;
			static constexpr int HIGHLIGHT_COLOR_R = 255;
			static constexpr int HIGHLIGHT_COLOR_G = 0;
			static constexpr int HIGHLIGHT_COLOR_B = 0;
			static constexpr int HIGHLIGHT_COLOR_A = 100;
			static constexpr int BASE_COLOR_R = 255;
			static constexpr int BASE_COLOR_G = 255;
			static constexpr int BASE_COLOR_B = 255;

			static constexpr const char* SWITCHER_LOC = "switcher.png";
			static constexpr float SWITCHER_W = 60.0F;
			static constexpr float SWITCHER_H = 60.0F;

			static constexpr const char* SLIDER_LOC = "slider.png";
			static constexpr float SLIDER_S_W = 300.0F; // shape
			static constexpr float SLIDER_S_H = 40.0F;
			static constexpr float SLIDER_A_W = 40.0F; // arrow
			static constexpr float SLIDER_A_H = 40.0F;
			static constexpr float SLIDER_M_W = 30.0F; // mark
			static constexpr float SLIDER_M_H = 30.0F;

			static constexpr const char* SCROLLBOX_LOC = "scrollbox.png";
			static constexpr const float SCROLLBOX_OUTSIDE_W = 500.0F;
			static constexpr const float SCROLLBOX_OUTSIDE_H = 500.0F;
			static constexpr const float SCROLLBOX_SCROLLER_SSIZE = 30.0F; // small size
			static constexpr const float SCROLLBOX_SCROLLER_LSIZE = 150.0F; // large size

			static constexpr auto INTXT_TEXTURE_LOC = "inputtext.png";
			static constexpr const float INTXT_SHAPE_W = 400.0F;
			static constexpr const float INTXT_SHAPE_H = 50.0F;

			static constexpr const char* DROPDOWN_LOC = "dropdown.png";
			static constexpr const float DROPDOWN_W = 300.0F;
			static constexpr const float DROPDOWN_H = 40.0F;

			static constexpr const char* BUTTON_LOC = "button.png";
			static constexpr const float BUTTON_W = 400.0F;
			static constexpr const float BUTTON_H = 50.0F;

			static constexpr const char* CONFIRM_DIALOG_LOC = "confirmdialog.png";
			static constexpr const float CONFIRM_DIALOG_W = 600.0F;
			static constexpr const float CONFIRM_DIALOG_H = 200.0F;
		};

		std::string fontLoc = DEFAULT::FONT_LOC;
		sf::Color fontColor =
		{ DEFAULT::FONT_COLOR_R, DEFAULT::FONT_COLOR_G, DEFAULT::FONT_COLOR_B };
		unsigned fontSize = DEFAULT::CHARACTER_SIZE;
		float selectThickness = DEFAULT::SELECT_THICKNESS;
		sf::Color selectColor =
		{ DEFAULT::SELECT_COLOR_R, DEFAULT::SELECT_COLOR_G, DEFAULT::SELECT_COLOR_B };
		sf::Color highlightColor =
		{ DEFAULT::HIGHLIGHT_COLOR_R, DEFAULT::HIGHLIGHT_COLOR_G,
		  DEFAULT::HIGHLIGHT_COLOR_B, DEFAULT::HIGHLIGHT_COLOR_A};
		sf::Color baseColor =
		{ DEFAULT::BASE_COLOR_R, DEFAULT::BASE_COLOR_G, DEFAULT::BASE_COLOR_B};

		std::string switcherTextureLoc = DEFAULT::SWITCHER_LOC;
		sf::Vector2f switcherButtonSize = { DEFAULT::SWITCHER_W, DEFAULT::SWITCHER_H };
		sf::Vector2f switcherMarkSize = { DEFAULT::SWITCHER_W, DEFAULT::SWITCHER_H };

		std::string sliderLoc = DEFAULT::SLIDER_LOC;
		sf::Vector2f sliderShapeSize = { DEFAULT::SLIDER_S_W, DEFAULT::SLIDER_S_H };
		sf::Vector2f sliderArrowSize = { DEFAULT::SLIDER_A_W, DEFAULT::SLIDER_A_H };
		sf::Vector2f sliderMarkSize = { DEFAULT::SLIDER_M_W, DEFAULT::SLIDER_M_H };

		std::string scrollboxLoc = DEFAULT::SCROLLBOX_LOC;
		sf::Vector2f scrollboxInsideSize = { DEFAULT::SCROLLBOX_OUTSIDE_W * 2, DEFAULT::SCROLLBOX_OUTSIDE_H * 2 };
		sf::Vector2f scrollboxOutsideSize = { DEFAULT::SCROLLBOX_OUTSIDE_W, DEFAULT::SCROLLBOX_OUTSIDE_H };
		sf::Vector2f scrollboxXscrollerSize =
		{ DEFAULT::SCROLLBOX_SCROLLER_LSIZE, DEFAULT::SCROLLBOX_SCROLLER_SSIZE };
		sf::Vector2f scrollboxYscrollerSize =
		{ DEFAULT::SCROLLBOX_SCROLLER_SSIZE, DEFAULT::SCROLLBOX_SCROLLER_LSIZE };

		std::string inputTextLoc = DEFAULT::INTXT_TEXTURE_LOC;
		sf::Vector2f inputTextSize = { DEFAULT::INTXT_SHAPE_W, DEFAULT::INTXT_SHAPE_H };

		std::string dropdownLoc = { DEFAULT::DROPDOWN_LOC };
		sf::Vector2f dropdownSize = { DEFAULT::DROPDOWN_W, DEFAULT::DROPDOWN_H };

		std::string buttonLoc = { DEFAULT::BUTTON_LOC };
		sf::Vector2f buttonSize = { DEFAULT::BUTTON_W, DEFAULT::BUTTON_H };

		std::string confirmDialogLoc = { DEFAULT::CONFIRM_DIALOG_LOC };
		sf::Vector2f confirmDialogSize = { DEFAULT::CONFIRM_DIALOG_W, DEFAULT::CONFIRM_DIALOG_H };
	};
}
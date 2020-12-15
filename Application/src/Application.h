#pragma once
#define MAIN_LEVEL

#include "NGin.h"

struct AppUISettings : public ng::UISettings {
	AppUISettings() {
		ng::UISettings::fontColor = { 0, 0 ,255 };
		ng::UISettings::baseColor = sf::Color::Red;
	}
};

class Application : public ng::Main
{
public:
	Application();

	/* abstract overrides */
	virtual void handleEvents();
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	AppUISettings uiSettings;

	ng::Button button_{ uiSettings };

	ng::Dropdown dropdown_{ uiSettings };

	ng::InputText inputText_{ uiSettings };

	sf::RectangleShape scrollBoxRect_;
	ng::ScrollBox scrollBox_{ uiSettings };

	ng::Slider slider_{ uiSettings };

	ng::Switcher switcher_{ uiSettings };

	ng::Button confirmDialogButton_{ uiSettings, "Enable confirm dialog!"};
	ng::ConfirmDialog confirmDialog_{
		uiSettings, ng::ConfirmDialog::DIALOG_TYPE::DIALOG_CLOSE_ONLY
	};
};

ng::Main* setMainLevel() {
	return new Application;
}
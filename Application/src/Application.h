#pragma once
#define MAIN_LEVEL

#include "NGin.h"

class Application : public ng::Main
{
public:
	Application();

	/* abstract overrides */
	virtual void handleEvents();
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	ng::Button button_;

	ng::Dropdown dropdown_;

	ng::InputText inputText_;

	sf::RectangleShape scrollBoxRect_;
	ng::ScrollBox scrollBox_;

	ng::Slider slider_;

	ng::Switcher switcher_;

	ng::Button confirmDialogButton_{"Enable confirm dialog!"};
	ng::ConfirmDialog confirmDialog_{ ng::ConfirmDialog::DIALOG_TYPE::DIALOG_CLOSE_ONLY };
};

ng::Main* setMainLevel() {
	return new Application;
}
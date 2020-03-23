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

	sf::RectangleShape testRect;
	ng::ScrollBox scrollBox_;

	ng::Button button_;
};

ng::Main* setMainLevel() {
	return new Application;
}
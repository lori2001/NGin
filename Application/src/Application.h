#pragma once
#define MAIN_LEVEL

#include "NGin.h"

class Application : public ngin::MainLevel
{
public:
	Application();

	/* abstract overrides */
	virtual void setup();
	virtual void handleEvents();
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	ngin::Button button;
};

ngin::MainLevel* setMainLevel() {
	return new Application;
}
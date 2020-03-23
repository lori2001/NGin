#include "Application.h"

Application::Application()
{
	windowVideoMode = { 1366,768 };
	windowName = "Client App";

	ng::Resources::setLocation("assets/");

	testRect.setFillColor(sf::Color::Red);
	testRect.setSize({ 60, 60 });

	scrollBox_.setTexture(NG_TEXTURE("scrollbox.png"));
	scrollBox_.setPosition({ 200, 200 });

	scrollBox_.addElement(testRect, { 500, 500 });

	button_.setTexture(NG_TEXTURE("button.png"));
}

void Application::handleEvents()
{
	scrollBox_.handleEvents(event_, ng::Cursor::getPosition());
	button_.handleEvents(event_, ng::Cursor::getPosition());

	if (button_.isActive()) {
		NG_LOG_ERROR("Button is active");
	}
}

void Application::update()
{
	/*Empty bc im shit*/
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scrollBox_);
	target.draw(button_);
}

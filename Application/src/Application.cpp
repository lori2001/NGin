#include "Application.h"

Application::Application()
{
	windowVideoMode_ = { 1366,768 };
	windowName_ = "Client App";
}

void Application::setup()
{
	ngin::Resources::setLocation("assets/");

	button.setTexture(*ngin::Resources::AcquireTexture("button.png"));
	button.setPosition({100, 200});
}

void Application::handleEvents()
{
	button.handleEvents(event_, ngin::Cursor::getPosition());

	if (button.isActive()) {
		NG_LOG_INFO("Button Pressed");
	}
}

void Application::update()
{
	/*Empty bc im shit*/
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button);
}

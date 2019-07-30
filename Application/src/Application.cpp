#include "Application.h"

Application::Application()
{
	windowSize_ = { 1366,768 };
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
	button.handleEvents(event_, ngin::ui::Cursor::getPosition());

	if (button.isActive()) {
		NG_LOG_INFO("Button Pressed");
	}
}

void Application::update()
{
}

void Application::draw(sf::RenderWindow& window) const
{
	window.draw(button);
}

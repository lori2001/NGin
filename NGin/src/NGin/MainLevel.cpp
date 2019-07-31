#include "MainLevel.h"

void ngin::MainLevel::run()
{
	window_.create(sf::VideoMode(windowSize_.x, windowSize_.y), windowName_);

	ngin::Timer::measureSysTime();

	setup();

	while (window_.isOpen())
	{
		while (window_.pollEvent(event_))
		{
			if (event_.type == sf::Event::Closed)
				window_.close();

			handleEvents();

			ngin::Cursor::followMouse(window_);
		}

		window_.clear();

		update();
		window_.draw(*this);

		window_.display();
	}
}

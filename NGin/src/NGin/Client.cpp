#include "Client.h"

void ngin::Client::run()
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

			ngin::ui::Cursor::followMouse(window_);
		}

		window_.clear();

		update();
		draw(window_);

		window_.display();
	}
}

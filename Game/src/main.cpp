#include "SFML/Graphics.hpp"
#include "NGin/Button.h"

#include <iostream>

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Super Mario HD");

	NGin::UI::Button button1;
	sf::Vector2f mouse;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

			button1.handleEvents(event);
			button1.selectByMouse(mouse);
		}

		window.clear();

		window.draw(button1);
		if (button1.activated()) {
			std::cout << "button pressed" << std::endl;
		}

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
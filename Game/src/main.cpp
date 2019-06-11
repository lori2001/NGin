#include "SFML/Graphics.hpp"
#include "NGin/UserInterface.h"
#include "NGin/Base.h"

#include <iostream>

using namespace NGin;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "Super Mario HD");

	ResourceCodex::setLocation("assets/");
	UI::Cursor cursor{ *ResourceCodex::Acquire<sf::Texture>("cursor.png") };

	UI::Slider slider{ {100,100} };
	slider.setTexture(*ResourceCodex::Acquire<sf::Texture>("slider.png"));
	slider.setFillColor(sf::Color(155,23,255));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			cursor.followMouse(window);

			slider.selectByMouse(UI::Cursor::getPosition());
			slider.handleEvents(event);
		}

		window.clear();

		window.draw(slider);
		window.draw(cursor);

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
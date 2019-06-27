#include "SFML/Graphics.hpp"
#include "NGin/UserInterface.h"
#include "NGin/Base.h"

#include <iostream>

using namespace NGin;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "My Application");

	ResourceCodex::setLocation("assets/");
	UI::Cursor cursor{ *ResourceCodex::Acquire<sf::Texture>("cursor.png") };

	UI::InputText inputtext;

	Logger::setConsoleFont({ 18, 18 }, true);
	Logger::setConsoleSize({ 1280, 600 });

	Logger::log("Application Initialized");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			cursor.followMouse(window);
		}
		
		window.clear();

		window.draw(inputtext);
		window.draw(cursor);
		
		window.display();
	}

	return 0;
}
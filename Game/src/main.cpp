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

	UI::Button button;
	button.setTexture(*ResourceCodex::Acquire<sf::Texture>("button.png"));
	button.setPosition({800, 200});
	button.setFillColor(sf::Color(100,255,50));

	UI::Switcher switcher;
	//switcher.setTexture(*ResourceCodex::Acquire<sf::Texture>("switcher.png"));
	switcher.setButtonColor(sf::Color::Red);
	switcher.setMarkColor(sf::Color::Blue);
	switcher.setPosition({200,200});

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			cursor.followMouse(window);

			switcher.selectByMouse(UI::Cursor::getPosition());
			switcher.handleEvents(event);

			button.selectByMouse(UI::Cursor::getPosition());
			button.handleEvents(event);
		}
		
		window.clear();

		window.draw(switcher);
		window.draw(button);
		window.draw(cursor);
		
		window.display();
	}

	return 0;
}
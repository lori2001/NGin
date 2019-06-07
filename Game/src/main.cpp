#include "SFML/Graphics.hpp"
#include "NGin/UserInterface.h"
#include "NGin/ResourceCodex.h"

#include <iostream>

using namespace NGin;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "Super Mario HD");

	UI::Cursor cursor{ *ResourceCodex::Acquire<sf::Texture>("cursor.png") };
	UI::Button button{ {400, 50}, *ResourceCodex::Acquire<sf::Texture>("button.png") };
	UI::Button button2{ {400, 50}, *ResourceCodex::Acquire<sf::Texture>("button.png") };
	button.setFont(*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	button.setString("StartGame");

	button2.setPosition(sf::Vector2f{ 200, 200 });
	button2.setFont(*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	button2.setString("Options");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			button.handleEvents(event);
			button.selectByMouse(UI::Cursor::getPosition());

			button2.handleEvents(event);
			button2.selectByMouse(UI::Cursor::getPosition());

			cursor.followMouse(window);
		}

		window.clear();

		window.draw(button);
		window.draw(button2);
		window.draw(cursor);

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
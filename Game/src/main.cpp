#include "SFML/Graphics.hpp"
#include "NGin/UserInterface.h"
#include "NGin/TextureCodex.h"

#include <iostream>

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "Super Mario HD");

	NGin::UI::Button button1{ {400,50}, *NGin::TextureCodex::Acquire("button.png") };
	button1.setPosition(sf::Vector2f{ 200,200 });
	
	NGin::UI::Cursor cursor{*NGin::TextureCodex::Acquire("cursor.png") };

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			button1.handleEvents(event);
			button1.selectByMouse(NGin::UI::Cursor::getPosition());
			cursor.followMouse(window);
		}

		window.clear();

		window.draw(button1);
		window.draw(cursor);
		if (button1.activated()) {
			std::cout << "button pressed" << std::endl;
		}

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
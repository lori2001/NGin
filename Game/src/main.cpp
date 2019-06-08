#include "SFML/Graphics.hpp"
#include "NGin/UserInterface.h"
#include "NGin/ResourceCodex.h"

#include <iostream>

using namespace NGin;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "Super Mario HD");

	ResourceCodex::setLocation("assets/");
	UI::Cursor cursor{ *ResourceCodex::Acquire<sf::Texture>("cursor.png") };
	
	UI::Button button{ {400, 50}, *ResourceCodex::Acquire<sf::Texture>("button.png") };
	button.setFont(*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	button.setString("Start Game");
	button.setSoundFX(*ResourceCodex::Acquire<sf::SoundBuffer>("button_click.wav"));
	button.setPosition({200,200});

	//UI::Dropdown dropdown{ 5 };
	(*ResourceCodex::Acquire<sf::Texture>("dropdown.png")).setRepeated(true);

	//dropdown.setPosition({1000, 300});
	//dropdown.setTexture(*ResourceCodex::Acquire<sf::Texture>("dropdown.png"),
	//					*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	//dropdown.setAbovetext("Blah-Blah");

	sf::Sound dummy;

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
			
			// dropdown.checkSelected(UI::Cursor::getPosition());
			// dropdown.handleInput(event, dummy);

			cursor.followMouse(window);
		}

		window.clear();

		if (button.activated()) {
			std::cout << "I am being pressed!" << std::endl;
		}

		window.draw(button);
		// window.draw(dropdown);
		window.draw(cursor);

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
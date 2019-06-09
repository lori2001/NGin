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
	
	UI::Button button{ {400, 50}, *ResourceCodex::Acquire<sf::Texture>("button.png") };
	button.setFont(*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	button.setString("Start Game");
	button.setSoundFX(*ResourceCodex::Acquire<sf::SoundBuffer>("button_click.wav"));
	button.setPosition({200,200});

	UI::Dropdown dropdown;

	ResourceCodex::Acquire<sf::Texture>("dropdown.png")->setRepeated(true);
	dropdown.setTexture(*ResourceCodex::Acquire<sf::Texture>("dropdown.png"));

	dropdown.setPosition({ 800,200 });
	dropdown.setShapeColor(sf::Color::Red);
	dropdown.setSelectColor(sf::Color::Blue);
	dropdown.setFont(*ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	dropdown.setAboveString("Resolution");
	dropdown.setDropString(0, "1366x600");
	dropdown.addTextElement("1000x600");
	dropdown.addTextElement("800x600");
	dropdown.addTextElement("400x400");
	dropdown.deleteTextElement(2);

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
			
			dropdown.handleEvents(event);
			dropdown.selectByMouse(UI::Cursor::getPosition());

			cursor.followMouse(window);
		}

		window.clear();

		if (button.activated()) {
			std::cout << "I am being pressed!" << std::endl;
		}

		for (int i = 1; i < dropdown.getNrofElem(); i++) {
			if (dropdown.activated(i)) {
				std::cout << "ACTIVATED: " << i << std::endl;
			}
		}

		window.draw(button);
		window.draw(dropdown);
		window.draw(cursor);

		//insert drawing commands in here

		window.display();
	}

	return 0;
}
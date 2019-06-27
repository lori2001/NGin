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

	UI::Dropdown dropdown;
	ResourceCodex::Acquire<sf::Texture>("dropdown.png")->setRepeated(true);
	dropdown.setTexture( *ResourceCodex::Acquire<sf::Texture>("dropdown.png"));
	dropdown.setFillColor(sf::Color::Red);
	dropdown.setFont( *ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	dropdown.addTextElement("Proba1");
	dropdown.addTextElement("Proba2");
	dropdown.addTextElement("Proba3");
	dropdown.addTextElement("Proba4");
	dropdown.addTextElement("Proba5");
	dropdown.addTextElement("Proba6");
	dropdown.setPosition({200,200});

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

			dropdown.selectByMouse(UI::Cursor::getPosition());
			dropdown.handleEvents(event);
		}
		
		if (dropdown.activated(1)) {
			dropdown.deleteTextElement(5);
		}


		window.clear();

		window.draw(inputtext);
		window.draw(dropdown);
		window.draw(cursor);
		
		window.display();
	}

	return 0;
}
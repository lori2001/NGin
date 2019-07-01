#include "SFML/Graphics.hpp"
#include "NGin/Base.h"
#include "NGin/UserInterface.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1366, 768), "My Application");

	NGin::Logger::setConsoleFont({ 18, 18 }, true);
	NGin::Logger::setConsoleSize({ 1280, 600 });

	NGin::ResourceCodex::setLocation("assets/");
	NGin::UI::Cursor::setBuffer(*NGin::ResourceCodex::Acquire<sf::SoundBuffer>("click.wav"));

	NGin::UI::InputText inputText;
	inputText.setFont(*NGin::ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	inputText.setTexture(*NGin::ResourceCodex::Acquire<sf::Texture>("inputtext.png"));
	inputText.setPosition({200,300});
	inputText.setFillColor(sf::Color(200,40,140));
	inputText.setTextColor(sf::Color(160,160,20));
	inputText.setSelectColor(sf::Color::Yellow);

	NGin::UI::Dropdown dropdown;
	dropdown.setTexture(*NGin::ResourceCodex::Acquire<sf::Texture>("dropdown.png"));
	dropdown.setPosition({200, 400});
	dropdown.setFont(*NGin::ResourceCodex::Acquire<sf::Font>("arial.ttf"));
	dropdown.setDropString(0, "ADW");
	dropdown.addDropString("SSSWW");
	dropdown.addDropString("SSSsdqwWW");
	dropdown.addDropString("SSSW");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();
	
			NGin::UI::Cursor::followMouse(window);

			inputText.select(NGin::UI::Cursor::getPosition());
			inputText.handleEvents(event);

			dropdown.select(NGin::UI::Cursor::getPosition());
			dropdown.handleEvents(event);
		}
		
		window.clear();

		
			if (inputText.getString() == "Douche" && !inputText.getisActive())
			{
				inputText.setString("Bag");
			}


		window.draw(dropdown);
		window.draw(inputText);

		window.display();
	}

	return 0;
}
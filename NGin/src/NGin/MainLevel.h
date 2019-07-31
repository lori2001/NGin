#pragma once
#include "SFML/Graphics.hpp"
#include "System/Timer.h"
#include "UI/Cursor.h"

namespace ngin {
	class MainLevel
	{
	public:
		void run();

	protected:
		// gets called after creating the window
		virtual void setup() {}
		// gets called only if there is an ongoing event
		virtual void handleEvents() {}
		// gets called every frame but is not constant
		virtual void update() {}
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderWindow& window) const {}

		sf::Vector2i windowSize_{ 1000,600 };
		sf::String windowName_ = "My Application";
		sf::RenderWindow window_;
		sf::Event event_;
	};

	// To be defined in client
	ngin::MainLevel* setMainLevel();
}

#pragma once
#include "SFML/Graphics.hpp"
#include "../System/Timer.h"
#include "../Audio/Audio.h"
#include "../UserInterface/Cursor.h"
#include"../System/Console.h"

namespace ng {
	enum class WINDOW_TYPE {
		WINDOW_RESIZEABLE = 0, // resizeable windowed
		WINDOW_UNRESIZEABLE, // unresizeable windowed
		WINDOW_BORDERLESS,
		WINDOW_FULLSCREEN
	};

	class Main : public sf::Drawable
	{
	public:
		Main();
		virtual ~Main() = default;
		void run();

		static sf::View view; // default view is full HD
		static sf::VideoMode windowVideoMode;
		static sf::String windowName;
		static sf::Color windowClearColor;
		static WINDOW_TYPE windowType;

		static unsigned long long getLoopCicleCount();
		// quickly ad view_ to window_
		static void applyViewToWindow();
		// returns true if window is in focus
		static bool windowHasFocus() { return hasFocus; }
	protected:
		// gets called only if there is an ongoing event
		virtual void handleEvents() = 0;
		// gets called every frame but is not constant
		virtual void update() = 0;
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		// use this to set window icon instead of accesing window_ directly
		void setWindowIcon(const std::string& location);

		static sf::RenderWindow window;
		sf::Event event_;

	private:
		sf::VideoMode saveVideoMode_ = windowVideoMode;
		sf::String saveName_ = windowName;
		WINDOW_TYPE saveType_ = windowType;

		sf::Image icon_;
		bool hasIcon_ = false;

		static bool hasFocus;

		static unsigned long long loopCicles; // counts how many loops have passed

		// recreates window with current settings
		void applySettingsToWindow();
		// called by updateWindow to set style
		void setWindowStyle(sf::Window& window, sf::Uint32 style) const;
	};

	// To be defined in client
	ng::Main* setMainLevel();
}

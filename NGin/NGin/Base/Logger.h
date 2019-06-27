#pragma once
#include "SFML/System.hpp"
#include <iostream>
#include <vector>
#include <windows.h> // <- only windows capable

namespace NGin
{
	class Logger {
	public:
		enum Severity {
			Info = 0,
			Warning,
			Error
		};

		// prints out the given message with different colors and extentions based on severity
		static void log(const std::string& output, const Severity& severity = Severity::Info);

		// prints out the same text only once
		// can be used in while loops to avoid spamming messages
		static void logOnce(const std::string& output, const Severity& severity = Severity::Info);

		// Hides console for Release mode
		static void hideReleaseConsole();

		static void setConsoleSize(const sf::Vector2i &size);
		// changes even fonts already displayed
		static void setConsoleFont(const sf::Vector2i& size, const bool isBold = false);
	private:
		// handle of the console window
		static HANDLE consoleHandle;
		// holds default background and foreground colors(black/white)
		static int defaultColors;

		// struct used to generate string hashes
		static std::hash<std::string> strHash;

		// holds string hashes which will be searched
		// when displaying a log once in a loop
		static std::vector<size_t> strHashes;
		
		// gets the current colors of the console
		static WORD GetConsoleTextAttribute(HANDLE hCon);
	};
}

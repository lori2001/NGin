#include "Logger.h"

namespace NGin {
	HANDLE Logger::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int Logger::defaultColors = GetConsoleTextAttribute(consoleHandle);
	std::hash<std::string> Logger::strHash;
	std::vector<size_t> Logger::strHashes;

	void Logger::log(const std::string& output, const Severity& severity)
	{
		// Change font color based on severity
		if (severity == Severity::Info) {
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			std::cout << "INFO: ";
		} else if (severity == Severity::Error) {
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "ERROR! ";
		} else if (severity == Severity::Warning) {
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << "WARNING: ";
		}

		std::cout << output << std::endl;

		// change colors back in case some1 wants to log using std::cout
		SetConsoleTextAttribute(consoleHandle, defaultColors);
	}
	void Logger::logOnce(const std::string& output, const Severity& severity)
	{
		// get the hash for the output string
		size_t outputHash = strHash(output);
		// search for hash in the container vector
		auto it = find(strHashes.begin(), strHashes.end(), outputHash);

		// if no hash was found
		if (it == strHashes.end()) {
			log(output, severity); // log
			strHashes.push_back(outputHash); // add the new hash to vector
		}
		else return;
	}
	void Logger::hideReleaseConsole()
	{
		#ifndef _DEBUG
			HWND console = GetConsoleWindow();
			ShowWindow(console, SW_HIDE);
		#endif
	}
	void Logger::setConsoleSize(const sf::Vector2i& size)
	{
		RECT rect;
		HWND console = GetConsoleWindow();
		GetWindowRect(console, &rect); // stores the console's current dimensions

		MoveWindow(console, rect.left, rect.top, size.x, size.y, TRUE);
	}
	void Logger::setConsoleFont(const sf::Vector2i& size, const bool isBold)
	{
		CONSOLE_FONT_INFOEX font;
		font.cbSize = sizeof(font);

		font.dwFontSize.X = size.x;
		font.dwFontSize.Y = size.y;

		if(isBold)
			font.FontWeight = FW_BOLD;
		else 
			font.FontWeight = FW_NORMAL;

		SetCurrentConsoleFontEx(consoleHandle, false, &font);
	}
	WORD Logger::GetConsoleTextAttribute(HANDLE hCon)
	{
		CONSOLE_SCREEN_BUFFER_INFO con_info;
		GetConsoleScreenBufferInfo(hCon, &con_info);
		return con_info.wAttributes;
	}
}
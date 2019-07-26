#pragma once
#include "SFML/System.hpp"
#include "Timer.h"
#include <vector>
#include <windows.h> // <- only windows capable
#include <sstream>

namespace ngin
{
	class Console {
	public:
		enum Severity {
			Note = 0,
			Info,
			Warning,
			Error
		};

		// prints out the given message with given severity
		static void log(const std::string& output, const Severity& severity = Severity::Note);

		template <typename T>
		static void log(const Severity& severity, T t);
		template<typename T, typename... Args>
		static void log(const Severity& severity, T t, Args... args);

		// prints out the same text only once
		static void logOnce(const std::string& output, const Severity& severity = Severity::Note);

		template <typename T>
		static void logOnce(const Severity& severity, T t);
		template<typename T, typename... Args>
		static void logOnce(const Severity& severity, T t, Args... args);

		static void hideOnRelease();
		static void setSize(const sf::Vector2u &size);
		// !!! Changes all fonts (even those alredy printed)
		static void setFontStyle(const sf::Vector2i& size, const bool isBold = false);
		static void setName(const LPCSTR name);

	private:
		static HANDLE HConsole_;
		static int defaultColors_; // default background and foreground colors(black/white)

		static std::hash<std::string> strHash_; // generate hashes
		static std::vector<size_t> strHashes_; // store hashes

		// string stream that temporarly stores input for write
		static std::ostringstream outStringStream_;
		
		// gets the current colors of the console
		static WORD GetConsoleTextAttribute(HANDLE hCon) {
			CONSOLE_SCREEN_BUFFER_INFO con_info;
			GetConsoleScreenBufferInfo(hCon, &con_info);
			return con_info.wAttributes;
		}
	};

	template<typename T>
	inline void Console::log(const Severity& severity, T t)
	{
		outStringStream_ << t;
		log(outStringStream_.str(), severity);
		outStringStream_.str(""); // clear stream
	}
	template<typename T, typename ...Args>
	inline void Console::log(const Severity& severity, T t, Args ...args)
	{
		const std::size_t n = sizeof...(Args);

		if (n > 0) // grow stream until last value
			outStringStream_ << t;

		log(severity, args...);
	}
	template<typename T>
	inline void Console::logOnce(const Severity& severity, T t)
	{
		outStringStream_ << t;
		logOnce(outStringStream_.str(), severity);
		outStringStream_.str(""); // clear stream
	}
	template<typename T, typename ...Args>
	inline void Console::logOnce(const Severity& severity, T t, Args ...args)
	{
		const std::size_t n = sizeof...(Args);

		if (n > 0) // grow stream until last value
			outStringStream_ << t;

		logOnce(severity, args...);
	}
}

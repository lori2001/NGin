#include "Application.h"

Application::Application()
{
	windowVideoMode = { 1000 ,600 };
	windowName = "Client App";
	
	// --- Button --------------------------
	button_.setString("Test Button");
	button_.setPosition({ 30.0F, 50.0F });

	// --- Confirm Dialog -------------------
	confirmDialog_.setPosition({ 600.0F, 480.0F });
	confirmDialog_.setString("This is a test string to see if\n"
							 "everything works fine");

	confirmDialogButton_.setPosition({ 600.0F, 400.0F });

	// --- Dropdown -------------------------
	dropdown_.setDropString(0, "Test Dropdown");
	dropdown_.addDropString("test");
	dropdown_.addDropColor(sf::Color::Cyan);
	dropdown_.addDropString("test2");
	dropdown_.setPosition({ 30.0F, 160.0F });

	// --- Input Text ----------------------
	inputText_.setString("Try writing here");
	inputText_.setPosition({ 30.0F, 350.0F });

	// --- ScrollBox --------------------------
	scrollBoxRect_.setSize({ 120, 120 });
	scrollBox_.setPosition({ 30.0F, 450.0F });
	scrollBox_.addElement(scrollBoxRect_, { 200.0F, 200.0F });

	// --- Slider -----------------------------
	slider_.setLevel(0.3F);
	slider_.setPosition({ 600.0F, 50.0F });

	// --- Switcher -----------------------
	switcher_.setPosition({ 600.0F, 200.0F });
}

void Application::handleEvents()
{
	button_.handleEvents(event_, ng::Cursor::getPosition());
	dropdown_.handleEvents(event_, ng::Cursor::getPosition());
	inputText_.handleEvents(event_, ng::Cursor::getPosition());
	scrollBox_.handleEvents(event_, ng::Cursor::getPosition());
	slider_.handleEvents(event_, ng::Cursor::getPosition());
	switcher_.handleEvents(event_, ng::Cursor::getPosition());
	confirmDialogButton_.handleEvents(event_, ng::Cursor::getPosition());
	confirmDialog_.handleEvents(event_, ng::Cursor::getPosition());

	if (confirmDialogButton_.isActive()) {
		confirmDialog_.setIsActive(true);
		confirmDialog_.drawInWindow("ConfirmDialog");
	}
}

void Application::update()
{
	// Empty bc im shit
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button_);
	target.draw(dropdown_);
	target.draw(inputText_);
	target.draw(scrollBox_);
	target.draw(slider_);
	target.draw(switcher_);
	target.draw(confirmDialogButton_);
	target.draw(confirmDialog_);
}

#include "Application.h"

Application::Application()
{
	windowVideoMode = { 1000 ,600 };
	windowName = "Client App";

	// ng::Resources::setLocation("assets/"); // default anyways

	// --- Button --------------------------
	button_.setTexture(NG_TEXTURE("button.png"));
	button_.setFont(NG_FONT("arial.ttf"));
	button_.setString("Test Button");
	button_.setPosition({ 30.0F, 50.0F });

	// --- Confirm Dialog -------------------
	confirmDialog_.setSize({ 600, 200 });
	confirmDialog_.setPosition({ 600.0F, 480.0F });
	confirmDialog_.setShapeColor(sf::Color::Cyan);
	confirmDialog_.setButtonTexture(NG_TEXTURE("button.png"));
	confirmDialog_.setString("This is a test string to see if\n"
							 "everything works fine");
	confirmDialog_.setFont(NG_FONT("arial.ttf"));
	confirmDialog_.setTextColor(sf::Color::Magenta);
	confirmDialog_.setButtonTextColor(sf::Color::Red);

	confirmDialogButton_.setTexture(NG_TEXTURE("button.png"));
	confirmDialogButton_.setFont(NG_FONT("arial.ttf"));
	confirmDialogButton_.setPosition({ 600.0F, 400.0F });
	confirmDialogButton_.setTextColor( sf::Color::Red );
	confirmDialogButton_.setFillColor({123, 231, 231});

	// --- Dropdown -------------------------
	dropdown_.setTexture(NG_TEXTURE("dropdown.png"));
	dropdown_.setFont(NG_FONT("arial.ttf"));
	dropdown_.setDropString(0, "Test Dropdown");
	dropdown_.addDropString("test");
	dropdown_.addDropColor(sf::Color::Cyan);
	dropdown_.addDropString("test2");
	dropdown_.setTextColor(sf::Color::Blue);
	dropdown_.setHighlightColor({ 255, 0, 0, 50 });
	dropdown_.setPosition({ 30.0F, 160.0F });

	// --- Input Text ----------------------
	inputText_.setTexture(NG_TEXTURE("inputtext.png"));
	inputText_.setFont(NG_FONT("arial.ttf"));
	inputText_.setString("Try writing here");
	inputText_.setTextColor(sf::Color::Red);
	inputText_.setPosition({ 30.0F, 350.0F });

	// --- ScrollBox --------------------------
	scrollBoxRect_.setFillColor(sf::Color::Red);
	scrollBoxRect_.setSize({ 120, 120 });
	scrollBox_.setTexture(NG_TEXTURE("scrollbox.png"));
	scrollBox_.setPosition({ 30.0F, 450.0F });
	scrollBox_.addElement(scrollBoxRect_, { 200.0F, 200.0F });

	// --- Slider -----------------------------
	slider_.setTexture(NG_TEXTURE("slider.png"));
	slider_.setLevel(0.3F);
	slider_.setMarkColor(sf::Color::Green);
	slider_.setArrowsColor(sf::Color::Red);
	slider_.setPosition({ 600.0F, 50.0F });

	// --- Switcher -----------------------
	switcher_.setTexture(NG_TEXTURE("switcher.png"));
	switcher_.setMarkColor(sf::Color::Black);
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

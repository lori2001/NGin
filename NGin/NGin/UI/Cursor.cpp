#include "Cursor.h"

namespace NGin::UI {

	sf::Sprite Cursor::sprite;
	sf::Sound Cursor::sound;

	void Cursor::draw(sf::RenderTarget& target)
	{
		target.draw(sprite);
	}

	void Cursor::setTexture(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}

	void Cursor::followMouse(sf::RenderWindow& window)
	{
		// sets sprite's coordinates to the mouse's position
		sprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		if (sprite.getTexture() != NULL) {
			// disables default Cursor on a given window
			window.setMouseCursorVisible(false);
		}
	}

	void Cursor::setBuffer(sf::SoundBuffer& soundBuffer)
	{
		sound.setBuffer(soundBuffer);
	}

	void Cursor::playSound()
	{
		// avoid overlapping press sounds
		if (sound.getStatus() != sf::Music::Status::Playing)
			sound.play();
	}
}

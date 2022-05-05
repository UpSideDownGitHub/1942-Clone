#include "Input.h"

/*
THIS FUNCTION WILL HANDLE THE INPUT FOR THE ENTIRE GAME
*/
void Input::pollEvents(sf::RenderWindow *window)
{
	buttonPresses[0] = false;
	buttonPresses[1] = false;
	buttonPresses[2] = false;
	buttonPresses[3] = false;
	buttonPresses[4] = false;
	buttonPresses[5] = false;
	spacePressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		buttonPresses[0] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		buttonPresses[1] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		buttonPresses[2] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		buttonPresses[3] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		buttonPresses[4] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		buttonPresses[5] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		spacePressed = true;
}

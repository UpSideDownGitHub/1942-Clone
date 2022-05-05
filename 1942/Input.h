#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Input
{
public:
	// VARIABLES
	bool buttonPresses[6] = {false, false, false, false, false, false};
	bool spacePressed = false;

	// METHODS
	void pollEvents(sf::RenderWindow *window);
private:
};


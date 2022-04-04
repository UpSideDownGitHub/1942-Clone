#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Input
{
public:
	// VARIABLES
	bool buttonPresses[6];
	bool spacePressed = false;

	// METHODS
	void pollEvents(sf::RenderWindow *window);
private:
	// VARIABLES
	sf::Event sfmlEvent;
};


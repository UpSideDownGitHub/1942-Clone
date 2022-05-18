/*
Program: 1942
Filename: Input.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: Input.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Input.h"

/*
THIS FUNCTION WILL HANDLE THE INPUT FOR THE ENTIRE GAME
*/
void Input::pollEvents(sf::RenderWindow *window)
{
	// RESET ALL INPUT
	buttonPresses[0] = false;
	buttonPresses[1] = false;
	buttonPresses[2] = false;
	buttonPresses[3] = false;
	buttonPresses[4] = false;
	buttonPresses[5] = false;
	spacePressed = false;

	// LEFT KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		buttonPresses[0] = true;
	}
	// DOWN KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		buttonPresses[1] = true;
	}
	// UP KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		buttonPresses[2] = true;
	}
	// RIGHT KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		buttonPresses[3] = true;
	}
	// Z KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		buttonPresses[4] = true;
	}
	// X KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		buttonPresses[5] = true;
	}
	// SPACE KEY PRESSED
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		spacePressed = true;
	}
}

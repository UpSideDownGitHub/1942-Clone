/**
Program: 1842
Filename: Input.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: Input.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <iostream>

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


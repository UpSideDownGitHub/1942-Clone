/**
Program: 1942
Filename: 2_Test.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: 2_Test.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Game.h"

// MAIN METHOD
int main()
{
	// INITILISE A RANDOM SEED
	srand(static_cast<unsigned>(time(0)));

	// INSTANCE OF GAME CLASS 
	//		MAIN CLASS THAT WILL HANDLE THE GAME
	Game game;

	// WHILST THE GAME IS OPEN CALL THE UPDATE AND RENDER METHODS OF GAME
	while (game.running())
	{
		// FOR THE GAMEPLAY
		game.update();
		// RENDERING THE UI
		game.render();
	}

	// END OF APPLICATION
	return 0;
}


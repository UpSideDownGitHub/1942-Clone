/**
Program: 1842
Filename: HighScoreScreen.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: HighScoreScreen.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Input.h"
#include "SaveData.h"

class HighScoreScreen
{
public:
	// CONSTRUCTORS
	HighScoreScreen();

	// METHODS
	void initilise(int score, int lives);
	void update(sf::RenderWindow* win);
	void render(sf::RenderTarget* target);

	//				GAME MODES
	// ENDLESS
	bool endless = false;
	
	// NO POWER UPS
	bool noPowerUps = false;

	// INSANE
	bool insane = false;

	// RANDOM
	bool random = false;

	//		VARIABLES
	Input input;
	SaveData saveData;
	bool close = false;

	// MOVING AROUND MENU
	// Wait Between Presses
	time_t startTime, startTime2;
	float timeToWait = 60, timeToWait2 = 75;

	int currentSelectScoreToChange = 999;

	int currentlySelected = 9;
	std::string currentLetter = "";
	int currentCharacters = 0;
	int maxCharacters = 8;

	// Main Window
	sf::Font arial;
	std::string letters[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
								"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
										  "U", "V", "W", "X", "Y", "Z"};
	std::vector<sf::RectangleShape> letterButtons;
	std::vector<sf::Text> letterText;

	sf::Text topFiveMessage;
	// TOP
	sf::Text top;
	sf::Text topScore;
	std::ostringstream ssTopScore;
	sf::Text topName;
	std::ostringstream ssTopName;
	sf::Text topLives;
	std::ostringstream ssTopLives;
	
	// 2ND
	sf::Text second;
	sf::Text secondScore;
	std::ostringstream ssSecondScore;
	sf::Text secondName;
	std::ostringstream ssSecondName;
	sf::Text secondLives;
	std::ostringstream ssSecondLives;

	// 3RD
	sf::Text third;
	sf::Text thirdScore;
	std::ostringstream ssThirdScore;
	sf::Text thirdName;
	std::ostringstream ssThirdName;
	sf::Text thirdLives;
	std::ostringstream ssThirdLives;
	
	// 4TH
	sf::Text forth;
	sf::Text forthScore;
	std::ostringstream ssForthScore;
	sf::Text forthName;
	std::ostringstream ssForthName;
	sf::Text forthLives;
	std::ostringstream ssForthLives;

	// 5TH
	sf::Text fith;
	sf::Text fithScore;
	std::ostringstream ssFithScore;
	sf::Text fithName;
	std::ostringstream ssFithName;
	sf::Text fithLives;
	std::ostringstream ssFithLives;
private:
	// METHODS
	void initGUI();
};


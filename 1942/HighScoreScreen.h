#pragma once
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
	//		VARIABLES
	Input input;
	SaveData saveData;
	bool menu1 = true, menu2 = false;

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


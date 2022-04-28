#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Input.h"
#include "SaveData.h"


class StartScreens
{
public:
	// CONSTRUCTORS
	StartScreens();

	// METHODS
	bool checkButtonPress(sf::RenderWindow* win);
	void render(sf::RenderTarget* target);

	//		VARIABLES
	Input input;
	SaveData saveData;

	time_t startTime;
	float timeToWait = 150;
	bool doOnce = true;

	// MAIN WINDOW
	sf::Font arial;
	sf::Text highScoreLabel;
	sf::Text highScoreText;
	std::ostringstream ssHighscore;
	sf::Text gameNameText;
	sf::Text insertCoinText;
	sf::Text copyrightText;


private:
	// METHODS
	void initGUI();
};


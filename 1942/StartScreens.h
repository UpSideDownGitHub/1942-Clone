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
	void checkButtonPress(sf::RenderWindow* win);
	void render(sf::RenderTarget* target);
	void selectMode(sf::RenderWindow* win);
	void loadLeaderboard();

	//		VARIABLES
	Input input;
	SaveData saveData;

	time_t startTime, startTime2;
	float timeToWait = 150, timeToWait2 = 65;
	bool doOnce = true;

	// MAIN WINDOW
	sf::Font arial;
	sf::Text highScoreLabel;
	sf::Text highScoreText;
	std::ostringstream ssHighscore;
	sf::Text gameNameText;
	sf::Text insertCoinText;
	sf::Text copyrightText;

	// Extra Game Modes
	std::string gameModes[7] = { "Normal", "Endless", "No Power Ups", "Insane", "Random", "Leaderboard", "Exit"};
	std::vector<sf::Text> options;
	int selected = 0;
	bool play = false;
	bool normal = false, endless = false, noPowerUp = false, insane = false, random = false, leaderboard = false;

	//			 LEADERBOARD
	// LEADERBOARD SELECTION
	std::vector<sf::Text> gamemodeNameOptions;
	int selected2 = 0;
	sf::Text gameModeName;

	sf::Text topFiveMessage;
	sf::RectangleShape box;
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


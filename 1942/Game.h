/**
Program: 1842
Filename: Game.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: Game.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include <SFML/Graphics.hpp>
#include <list>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <chrono>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "StartScreens.h"
#include "CheckCollisions.h"
#include "PopUp.h"
#include "SaveData.h"
#include "Audio.h"
#include "HighScoreScreen.h"
#include "Input.h"

#pragma once
class Game
{
public:
	//			VARIABLES
	sf::RenderWindow* window;

	// CLASSES
	Player player;
	EnemySpawner spawner;
	StartScreens startScreens;
	CheckCollisions checkCollisions;
	SaveData saveData;
	Audio audio;
	HighScoreScreen highScoreScreen;
	Input input;

	// HIGH SCORE SCEEN
	bool inHighScoreScreen = false;

	// MAIN MENU
	bool inMainMenus = true;
	int livesUsed = 0;

	//			GUI ELEMENTS
	// LIVES
	sf::Text lives;
	std::ostringstream livesnum;

	// DODGES
	sf::Text dodges;
	std::ostringstream dodgesNum;
	bool updateDodgesText = true;

	//	SCORE SYSTEM
	sf::Text scoreP1;
	sf::Text scoreP1Num;
	std::ostringstream ssScoreP1;
	sf::Text highScoreLabel;
	sf::Text highScoreText;
	std::ostringstream ssHighscore;
	sf::Text scoreP2;
	sf::Text scoreP2Num;
	std::ostringstream ssP2Num;

	int P1score = 0;
	int highScore = 0;

	// POWER UPS
	time_t startTimeOrangePowerUp;
	float timeToWaitOrangePowerUp = 5000;

	//		LEVEL SYSTEM
	int level = 0;

	bool calculateInfomationOnce = true;
	// LEVEL START SCREEN
	sf::Font arial;
	sf::Text levelName;
	sf::Text levelNumber;
	std::ostringstream ssLevel;
	sf::Text readyText;
	sf::Text player1Text;
	time_t startTime;
	int secondsToShow = 2;
	bool showingLevelInfo = true;

	// LEVEL END SCREEN (NOT DEATH)
	sf::Text downPercentage;
	std::ostringstream ssPercent;
	sf::Text bonusText;
	sf::Text bonusPointsText;
	std::ostringstream ssBonusPoints;
	sf::Text rollBonusText;
	std::ostringstream ssRollBonusPoints;
	time_t startTime2;
	int secondsToShow2 = 3;
	bool showingLevelEndInfo = false;
	// LEVEL END SCREEN (PLAYER DEATH)
	sf::Text shootDownPercentage;
	std::ostringstream ssDownPercent;
	sf::Text percentageComplete;
	std::ostringstream ssPercentComplete;
	sf::Text todaysTopPercentage;
	std::ostringstream ssTopPercentage;
	sf::Text gameOver;
	time_t startTime3;
	int secondsToShow3 = 5;
	bool showingLevelEndInfo2 = false;

	// BEATEN FINAL BOSS SCREEN
	sf::Text congratulationsText;
	sf::Text bestPlayerText1;
	sf::Text bestPlayerText2;
	sf::Text finalMessageText;
	time_t startTime4;
	int secondsToShow4 = 3;
	bool showingBeatFinalBossMessage = false;

	// GIVE UP SCREEN
	sf::Text wegiveupText;
	sf::Text specialBonusText;
	sf::Text bonusNumText;
	sf::Text gameOverText;
	sf::Text presentedText;
	time_t startTime5;
	int secondsToShow5 = 5;
	bool showingWeGiveUpScreen = false;
	bool gameBeaten = false;
	bool addedScore = false;

	bool runStart = true;

	//			GAME MODES
	// ENDLESS
	sf::Text endlessMode;

	// PAUSE MENU
	bool muted = false;
	bool paused = false;
	sf::RectangleShape box;
	bool doOnce2 = true;
	time_t startTime6, startTime7;
	int timeToWait1 = 65, timeToWait2 = 100;

	std::string pauseOptionTexts[4] = { "Resume", "Main Menu", "Sound On/Off", "Exit"};
	std::vector<sf::Text> options;
	int selected = 0;

	// CONSTRUCTORS
	Game();

	// METHODS
	void start();
	void update();
	void render();

	void renderPauseMenu();
	void renderLevelInfoScreen();
	void renderLevelEndScreenND();
	void renderLevelEndScreenD();
	void renderScoreInfomation();
	void renderFinalBossMessage();
	void renderWeGiveUpScreen();

	void checkPowerUps(int num, int num2);

	// ACCESSORS
	const bool running() const;

private:
	// VARIABLES
	sf::Event sfmlEvent;

	// METHODS
	void initWindow();
	void initGUI();
	void initAudio();
};


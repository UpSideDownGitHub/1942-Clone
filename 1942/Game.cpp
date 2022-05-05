/*
Program: 1942
Filename: Game.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: Game.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILE
#include "Game.h"

//#define TESTING
//#define TESTING2

/*
	CONSTRUCTOR FOR THE GAME CLASS
*/
Game::Game()
{
	startTimeOrangePowerUp = clock();
	startTime = clock();
	startTime2 = clock();
	startTime3 = clock();
	startTime4 = clock();
	startTime5 = clock();
	startTime6 = clock();
	startTime7 = clock();

	// CREATE THE GAME WINDOW
	float width = 560.f;
	float height = 640.f;
	this->window = new sf::RenderWindow(sf::VideoMode((int)width, (int)height), "1942", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);

	// MOVE THE WINDOW TO THE MIDDLE OF THE SCREEN
	sf::Vector2i centerWindow((int)((sf::VideoMode::getDesktopMode().width / 2) - width / 2.f), (int)((sf::VideoMode::getDesktopMode().height / 2) - height / 1.75f));
	this->window->setPosition(centerWindow);
	this->window->setKeyRepeatEnabled(true);

	initGUI();
	initAudio();
}

/*
	CALLED ON THE FIRST "Update()" OF A NEW GAME
*/
void Game::start()
{
	spawner.endlessMode = false;
	spawner.noPowerUpsMode = false;
	spawner.insaneMode = false;
	spawner.randomMode = false;
	

	runStart = false;
	showingLevelEndInfo = false;
	showingLevelEndInfo2 = false;
	gameBeaten = false;
	showingBeatFinalBossMessage = false;
	showingWeGiveUpScreen = false;
	addedScore = false;
	showingLevelInfo = true;
	livesUsed = 0;
	player = Player();
	if (startScreens.endless)
	{
		player.lives = 0;
		livesnum.str("");
		for (int k = 0; k < player.lives; k++)
		{
			livesnum << "O ";
		}
		lives.setString(livesnum.str());
	}

	spawner = EnemySpawner();
	startTime = time(0);
	level = 0; // 0
	P1score = 0;
	ssScoreP1.str("");
	ssScoreP1 << P1score;
	scoreP1Num.setString(ssScoreP1.str());
	scoreP1Num.setOrigin(round(scoreP1Num.getLocalBounds().width / 2), round(scoreP1Num.getLocalBounds().height / 2));
	ssLevel.str("");
	ssLevel << 32 - level << " Stage";
	levelNumber.setString(ssLevel.str());
	levelNumber.setOrigin(levelNumber.getLocalBounds().width / 2, levelNumber.getLocalBounds().height / 2);
	levelName.setString("Midway");
	levelName.setOrigin(levelName.getLocalBounds().width / 2, levelName.getLocalBounds().height / 2);
}

/*
	RENDERING (THIS FUNCTION HANDLES RENDERING FOR THE ENTIRE GAME AND WILL CALL EACH OF THE COMPONENTS RENDER FUNCTION
	SO THAT THEY CAN BE RENDERED/DRANW ONTO THE SCREEN)
*/
void Game::render()
{
	// CLEAR WHAT HAS BEEN PREVIOSLY DRAWN TO THE WINDOW
	window->clear();

	if (inHighScoreScreen)
	{
		highScoreScreen.render(window);
		renderScoreInfomation();
	}
	else if (inMainMenus)
	{
		startScreens.render(window);
	}
	else
	{
		// PLAYER
		player.render(this->window);	// USES LOTS OF CPU POWER

		// ENEMYS
		spawner.render(this->window);

		renderScoreInfomation();		// USES LOTS OF CPU POWER 

		if (showingWeGiveUpScreen)
			renderWeGiveUpScreen();

		if (showingBeatFinalBossMessage)
			renderFinalBossMessage();

		if (showingLevelEndInfo2)
			renderLevelEndScreenD();

		if (showingLevelEndInfo)
			renderLevelEndScreenND();
		
		if (showingLevelInfo)
			renderLevelInfoScreen();
		window->draw(lives);
		window->draw(dodges);

		if (paused)
			renderPauseMenu();
	}
	// DISPLAY WHAT HAS BEEN DRAWN TO THE WINDOW
	window->display();					// USES LOTS OF CPU POWER BUT CAN DO NOTHING ABOUT THAT
}

void Game::renderPauseMenu()
{
	window->draw(box);
	for (sf::Text text : options)
	{
		window->draw(text);
	}
}
void Game::renderScoreInfomation()
{
	if (spawner.scoreChanged)
	{
		spawner.scoreChanged = false;
		P1score = spawner.currentPoints;
		ssScoreP1.str("");
		ssScoreP1 << P1score;
		scoreP1Num.setString(ssScoreP1.str());
		scoreP1Num.setOrigin(round(scoreP1Num.getLocalBounds().width / 2), round(scoreP1Num.getLocalBounds().height / 2));
		if (P1score > highScore)
		{
			ssHighscore.str("");
			ssHighscore << P1score;
			highScoreText.setString(ssHighscore.str());
			highScoreText.setOrigin(round(scoreP1Num.getLocalBounds().width / 2), round(scoreP1Num.getLocalBounds().height / 2));
		}
	}

	window->draw(scoreP1);
	window->draw(scoreP1Num);
	window->draw(highScoreLabel);
	window->draw(highScoreText);
	window->draw(scoreP2); 
	window->draw(scoreP2Num);
}
void Game::renderLevelInfoScreen()
{
	if (startScreens.endless)
	{
		window->draw(endlessMode);
	}
	else
	{
		window->draw(levelName);
		window->draw(levelNumber);
	}
	window->draw(readyText);
	window->draw(player1Text);
}
void Game::renderLevelEndScreenND()
{
	window->draw(downPercentage);
	window->draw(bonusText);
	window->draw(bonusPointsText);
	window->draw(rollBonusText);
}

void Game::renderLevelEndScreenD()
{
	if (!startScreens.endless)
	{
		window->draw(percentageComplete);
		window->draw(todaysTopPercentage);
	}
	window->draw(shootDownPercentage);
	window->draw(gameOver);
}

void Game::renderFinalBossMessage()
{
	window->draw(congratulationsText);
	window->draw(bestPlayerText1);
	window->draw(bestPlayerText2);
	window->draw(finalMessageText);
}

void Game::renderWeGiveUpScreen() 
{
	window->draw(wegiveupText);
	window->draw(specialBonusText);
	window->draw(bonusNumText);
	window->draw(gameOverText);
	window->draw(presentedText);
}

/*
	THIS IS THE MAIN UPDATE FUNCTION FOR THE GAME AND WILL HANDLE CALLING ALL THE OTHER UPDATE FUNCTIONS OF ALL
	OTHER OBJECTS IN THE SCENE
*/
void Game::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// THIS IS TO MAKE THE WINDOW RESPOND
	}
	if (inHighScoreScreen)
	{
		highScoreScreen.update(window);
		if (highScoreScreen.close)
		{
			inMainMenus = true;
			inHighScoreScreen = false;
			highScoreScreen.close = false;
		}
	}
	else if (inMainMenus)
	{
		startScreens.checkButtonPress(window);
		inMainMenus = !startScreens.play;
		if (!inMainMenus)
		{
			audio.audio[1]->play();
			runStart = true;
		}
	}
	else if (paused)
	{
		if (doOnce2)
		{
			doOnce2 = false;
			startTime6 = clock();
			startTime7 = clock();
		}
		input.pollEvents(window);
		if (float(clock() - startTime7) / CLOCKS_PER_SEC * 1000 >= timeToWait2)
		{
			if (input.buttonPresses[1]) // DOWN
			{
				if (float(clock() - startTime6) / CLOCKS_PER_SEC * 1000 >= timeToWait1)
				{
					startTime6 = clock();
					if (selected < 3)
					{
						options[selected].setFillColor(sf::Color::White);
						selected++;
						options[selected].setFillColor(sf::Color::Yellow);
					}
				}
			}
			else if (input.buttonPresses[2]) // UP
			{
				if (float(clock() - startTime6) / CLOCKS_PER_SEC * 1000 >= timeToWait1)
				{
					startTime6 = clock();
					if (selected > 0)
					{
						options[selected].setFillColor(sf::Color::White);
						selected--;
						options[selected].setFillColor(sf::Color::Yellow);
					}
				}
			}
			if (input.spacePressed)
			{
				doOnce2 = true;
				if (selected == 0)
				{
					paused = false;
				}
				else if (selected == 1)
				{
					paused = false;
					inMainMenus = true;
				}
				else if (selected == 2)
				{
					if (muted)
					{
						for (int i = 0; i < 9; i++)
						{
							audio.audio[i]->setVolume(0);
						}
					}
					else
					{
						for (int i = 0; i < 9; i++)
						{
							audio.audio[i]->setVolume(100);
						}
					}
					muted = !muted;
					paused = false;
				}
				else if (selected == 3)
				{
					window->close();
				}
				startTime7 = clock();
			}
		}
	}
	else
	{
		if (runStart)
			start();
		// SHOW LEVEL
		if (showingLevelInfo)
		{
			if (time(0) - startTime > secondsToShow)
			{
				// START THE LEVEL
				showingLevelInfo = false;
				if (startScreens.endless)
					spawner.startEndlessMode();
				else if (startScreens.noPowerUp)
					spawner.startNoPowerUpMode(level);
				else if (startScreens.insane)
					spawner.startInsaneMode(level);
				else if (startScreens.random)
					spawner.startRandomMode(level);
				else
					spawner.startLevel(level);
			}
		}
		// NEXT LEVEL
		else if (showingLevelEndInfo)
		{
			if (time(0) - startTime2 > secondsToShow2)
			{
				calculateInfomationOnce = true;
				showingLevelEndInfo = false;
				if (gameBeaten)
				{
					showingLevelEndInfo2 = true;
					startTime3 = time(0);
				}
				else
				{
					level++;
					if (player.dodges > 3)
						player.dodges = 3;
					ssLevel.str("");
					ssLevel << 32 - level << " Stage";
					levelNumber.setString(ssLevel.str());
					levelNumber.setOrigin(levelNumber.getLocalBounds().width / 2, levelNumber.getLocalBounds().height / 2);


					std::string nameOfLevel;
					int curLevel = 32 - level;
					if (curLevel <= 32 && curLevel >= 29)
						nameOfLevel = "Midway";
					else if (curLevel <= 28 && curLevel >= 25)
						nameOfLevel = "Marshall";
					else if (curLevel <= 24 && curLevel >= 21)
						nameOfLevel = "Attu";
					else if (curLevel <= 20 && curLevel >= 17)
						nameOfLevel = "Rabaul";
					else if (curLevel <= 16 && curLevel >= 13)
						nameOfLevel = "Leyte";
					else if (curLevel <= 12 && curLevel >= 9)
						nameOfLevel = "Saipan";
					else if (curLevel <= 8 && curLevel >= 5)
						nameOfLevel = "Iwojima";
					else if (curLevel <= 4 && curLevel >= 1)
						nameOfLevel = "Okinawa";

					levelName.setString(nameOfLevel);
					levelName.setOrigin(levelName.getLocalBounds().width / 2, levelName.getLocalBounds().height / 2);

					showingLevelInfo = true;
					startTime = time(0);
				}
			}
			else if (calculateInfomationOnce)
			{
				spawner.scoreChanged = true;
				audio.audio[2]->play();
				calculateInfomationOnce = false;
				// SHOT DOWN %
				float percent = ((float)spawner.currentEnemyDestroyed / (float)spawner.currentEnemySpawned) * 100.00f;
				ssPercent.str("");
				ssPercent << "Shooting Down " << percent << "%";
				downPercentage.setString(ssPercent.str());
				// BONUS
				int bonus = 0;
				if (percent == 100)
					bonus = 50000;
				else if (percent >= 95 && percent < 100)
					bonus = 20000;
				else if (percent >= 90 && percent < 95)
					bonus = 10000;
				else if (percent >= 85 && percent < 90)
					bonus = 5000;
				else if (percent >= 80 && percent < 85)
					bonus = 4000;
				else if (percent >= 70 && percent < 80)
					bonus = 3000;
				else if (percent >= 60 && percent < 70)
					bonus = 2000;
				else if (percent >= 50 && percent < 60)
					bonus = 1000;
				else if (percent < 50)
					bonus = 0;
				spawner.currentPoints += bonus;
				ssBonusPoints.str("");
				ssBonusPoints << bonus << " pts";
				bonusPointsText.setString(ssBonusPoints.str());
				// ROLL BONUS 
				int rollBonus = 1000 * player.dodges;
				spawner.currentPoints += rollBonus;
				ssRollBonusPoints.str("");
				ssRollBonusPoints << "Rx1000 = " << rollBonus << " pts";
				rollBonusText.setString(ssRollBonusPoints.str());
			}
		}
		// END GAME
		else if (showingLevelEndInfo2)
		{
			if (time(0) - startTime3 > secondsToShow3)
			{
				calculateInfomationOnce = true;
				showingLevelEndInfo2 = false;
				if (gameBeaten)
				{
					showingWeGiveUpScreen = true;
					startTime5 = time(0);
				}
				else
				{
					level = 0;
					runStart = true;

					// MAKE THIS SHOW THE NEW HIGHSCORE SCREEN IF THE PLAYER ACHIVED A NEW HIGHSCORE
					saveData.loadFile();
					SaveData::PlayerInfo* leaderboard = saveData.getLeaderboard();
					for (int i = 0; i < 5; i++)
					{
						if (spawner.currentPoints > leaderboard[i].Score)
						{
							highScoreScreen.endless = false;
							highScoreScreen.noPowerUps = false;
							highScoreScreen.insane = false;
							highScoreScreen.random = false;

							if (startScreens.endless)
								highScoreScreen.endless = true;
							else if (startScreens.noPowerUp)
								highScoreScreen.noPowerUps = true;
							else if (startScreens.insane)
								highScoreScreen.insane = true;
							else if (startScreens.random)
								highScoreScreen.random = true;
							highScoreScreen.initilise(spawner.currentPoints, livesUsed);
							inHighScoreScreen = true;
							break;
						}
					}
					if (!inHighScoreScreen)
						inMainMenus = true;
				}
			}
			else if (calculateInfomationOnce)
			{
				std::cout << "HELLO" << "\n";
				spawner.scoreChanged = true;
				audio.audio[2]->play();
				calculateInfomationOnce = false;
				// SHOOT DOWN PERCENTAGE
				ssDownPercent.str("");
				ssDownPercent << "Shot Down " << spawner.totalEnemyDestroyed;
				shootDownPercentage.setString(ssDownPercent.str());
				// PERCENTAGE COMPLETE
				ssPercentComplete.str("");
				float percentage = ((float)spawner.currentLevel / (float)32)*100.00f;
				ssPercentComplete << "Percentage " << percentage << "%";
				percentageComplete.setString(ssPercentComplete.str());

				saveData.loadFile();
				// TODAYS HIGHEST PERCENT
				ssTopPercentage.str("");
				ssTopPercentage << "Todays Top " << saveData.getDailyHighestPercent() << "%"; // WILL HAVE TO TAKE THIS FROM THE SAVE DATA WHEN THAT IS ADDED
				todaysTopPercentage.setString(ssTopPercentage.str());

				if (saveData.getDailyHighestPercent() < percentage)
				{
					saveData.setDailyHighestPercent((int)percentage);
					saveData.saveFile();
				}
				if (saveData.getHighScore() < spawner.currentPoints)
				{
					saveData.setHighScore(spawner.currentPoints);
					saveData.saveFile();
				}
			}
		}
		else if (showingBeatFinalBossMessage)
		{
			if (time(0) - startTime4 > secondsToShow4)
			{
				showingBeatFinalBossMessage = false;
				// NEXT LEVEL
				showingLevelEndInfo = true;
				startTime2 = time(0);
			}
		}
		else if (showingWeGiveUpScreen)
		{
			if (!addedScore)
			{
				spawner.scoreChanged = true;
				spawner.currentPoints += 10000000;
				addedScore = true;
			}
			if (time(0) - startTime5 > secondsToShow5)
			{
				showingWeGiveUpScreen = false;
				gameBeaten = false;
				addedScore = false;
				// WILL NEED TO MAKE THIS TAKE THE PLAYER TO THE ENTER USERNAME SCREEN THAT WILL LET THEM SAVE THERE HIGHSCORE
				saveData.loadFile();
				SaveData::PlayerInfo* leaderboard = saveData.getLeaderboard();
				for (int i = 0; i < 5; i++)
				{
					if (spawner.currentPoints > leaderboard[i].Score)
					{
						highScoreScreen.endless = false;
						highScoreScreen.noPowerUps = false;
						highScoreScreen.insane = false;
						highScoreScreen.random = false;

						if (startScreens.endless)
							highScoreScreen.endless = true;
						else if (startScreens.noPowerUp)
							highScoreScreen.noPowerUps = true;
						else if (startScreens.insane)
							highScoreScreen.insane = true;
						else if (startScreens.random)
							highScoreScreen.random = true;
						highScoreScreen.initilise(spawner.currentPoints, livesUsed);
						inHighScoreScreen = true;
						break;
					}
				}
				if (!inHighScoreScreen)
					inMainMenus = true;
				level = 0;
				runStart = true;
			}
		}
		// PLAY LEVEL
		else
		{
			// add the diffrent game modes here
			if (spawner.playLevel)
			{
				input.pollEvents(window);
				if (input.spacePressed && float(clock() - startTime7) / CLOCKS_PER_SEC * 1000 >= 200)
				{
					paused = true;
				}

				// DISABLE ENEMY SHOOTING FOR THE ORANGE POWER UP
				if (float(clock() - startTimeOrangePowerUp) / CLOCKS_PER_SEC * 1000 >= timeToWaitOrangePowerUp)
				{
					for (Enemy *enemys : spawner.enemys)
					{
						enemys->canShoot = true;
					}
				}

				// PLAYER MOVEMENT AND SHOOTING
				player.update(this->window, &audio);

#if defined(TESTING)
				spawner.test_update(&player);
#else
				// SPANWER SPAWNING AND ENEMY DEATH COLLECTION
				spawner.update(&player, &audio);
#endif
				//		COLLISION DETECTION	
				// PLAYER BULLETS HITTING ENEMYS
				checkCollisions.checkPlayerBulletCollisions(player.bullets, spawner.enemys);
				// IF ANY ENEMYS WHERE HIT
				if (checkCollisions.copyBullets)
				{
					for (Bullet *bullet : player.bullets)
					{
						// MAKE EXPLOSION EFFECTS
						if (bullet->makeExplosion)
						{
#if defined(TESTING)

#else
							spawner.popUps.push_back(new PopUp(bullet->getPosition(), clock(), 200, true));
							audio.audio[5]->play();
#endif
						}
					}
					player.bullets = checkCollisions.bulletsToCopy;
					checkCollisions.bulletsToCopy.clear();
					checkCollisions.copyBullets = false;
				}

				// ENEMYS HITTING PLAYER
				if (player.takeDamage)
				{
					updateDodgesText = true;
#if defined(TESTING2)

#else
					checkCollisions.checkEnemyHitPlayer(&player, spawner.enemys);					
					checkCollisions.checkEnemyBulletCollisions(player.enemyBullets, &player);
#endif
				}
				// PLAYER USED A DODGE
				else if (updateDodgesText)
				{
					updateDodgesText = false;
					dodgesNum.str("");
					for (int k = 0; k < player.dodges; k++)
					{
						dodgesNum << "X ";
					}
					dodges.setString(dodgesNum.str());
					dodges.setOrigin(dodges.getLocalBounds().width, dodges.getLocalBounds().height);
				}

				// PLAYER LOST A LIFE 
				if (checkCollisions.changedLives)
				{
					if (player.shootingMethod == 4)
					{
						livesUsed++;
						player.shootingMethod--;
						player.lives++;
						checkCollisions.changedLives = false;
						player.enemyBullets.clear();
					}
					else if (player.shootingMethod == 3)
					{
						livesUsed++;
						player.shootingMethod--;
						player.leftFighter = true;
						player.lives++;
						checkCollisions.changedLives = false;
						player.enemyBullets.clear();
					}
					else if (player.shootingMethod <= 2)
					{
						livesUsed++;
						player.shootingMethod = 1;
						spawner.hasQuadShot = false;

						if (player.lives >= 0)
						{
							audio.audio[3]->play();
							checkCollisions.changedLives = false;
							showingLevelInfo = true;
							spawner.enemys.clear();
							player.enemyBullets.clear();
							livesnum.str("");
							for (int k = 0; k < player.lives; k++)
							{
								livesnum << "O ";
							}
							lives.setString(livesnum.str());
							startTime = time(0);
						}
						else if (player.lives < 0)
						{
							audio.audio[4]->play();
							showingLevelEndInfo2 = true;
							startTime3 = time(0);
							spawner.enemys.clear();
						}
					}
				}

				// PLAYER HITTING POWERUPS
				std::vector<int> powerUpNum = checkCollisions.checkPlayerPowerUpCollisions(spawner.powerups, &player);
				if (powerUpNum.size() > 0)
				{
					checkPowerUps(powerUpNum[0], powerUpNum[1]);
					if (checkCollisions.copyPowerUps)
					{
						spawner.powerups = checkCollisions.powerUpsCopy;
						checkCollisions.powerUpsCopy.clear();
						checkCollisions.copyPowerUps = false;
					}
					
				}

			}
			// LEVEL BEATEN
			else
			{
				// PLAY LEVEL WON SOUND
				audio.audio[2]->play();
				if (spawner.currentLevel == 31)
				{
					// PLAYER BEAT THE FINAL BOSS
					startTime4 = time(0);
					showingBeatFinalBossMessage = true;
				}
				else if (spawner.currentLevel == 32)
				{
					// PLAYER BEAT THE FINAL LEVEL
					gameBeaten = true;
					showingLevelEndInfo = true;
					startTime2 = time(0);
				}
				else
				{
					// NEXT LEVEL
					showingLevelEndInfo = true;
					startTime2 = time(0);
				}
			}
		}
	}
}

void Game::checkPowerUps(int num, int num2)
{
	audio.audio[6]->play();
	spawner.scoreChanged = true;
	if (num == 0)
	{
		spawner.currentPoints += 1000;
		// ENABLE QUAD SHOOTING
		player.shootingMethod = 2;
	}
	else if (num == 1)
	{
		spawner.currentPoints += 1000;
		// DESTROY ALL ENEMYS
		for (Enemy *enemys : spawner.enemys)
		{
			enemys->die = true;
		}
	}
	else if (num == 2)
	{
		spawner.currentPoints += 1000;
		// ENABLE SEXT SHOOTING
		player.shootingMethod = 4;
	}
	else if (num == 3)
	{
		spawner.currentPoints += 1000;
		// NO ENEMY SHOOTING
		for (Enemy *enemys : spawner.enemys)
		{
			enemys->canShoot = false;
		}
		startTimeOrangePowerUp = clock();
	}
	else if (num == 4)
	{
		spawner.currentPoints += 1000;
		player.dodges++;
		dodgesNum.str("");
		for (int k = 0; k < player.dodges; k++)
		{
			dodgesNum << "X ";
		}
		dodges.setString(dodgesNum.str());
		dodges.setOrigin(dodges.getLocalBounds().width, dodges.getLocalBounds().height);
	}
	else if (num == 5)
	{
		spawner.currentPoints += 1000;
		// +1 LIFE (FOREVER)
		player.lives++;
		livesnum.str("");
		for (int k = 0; k < player.lives; k++)
		{
			livesnum << "O ";
		}
		lives.setString(livesnum.str());
	}
	else if (num == 6)
	{
		spawner.currentPoints += 1000;
	}
	else if (num == 7)
	{
		spawner.currentPoints += 5000;
	}

	if (num == 7)
	{
		spawner.popUps.push_back(new PopUp("5000", spawner.powerups[num2]->getPosition(), clock(), 1000));
	}
	else
	{
		spawner.popUps.push_back(new PopUp("1000", spawner.powerups[num2]->getPosition(), clock(), 1000));
	}

}


/*
	INILISES THE GUI OF THE GAME
*/
void Game::initGUI()
{
	// LOAD THE FONT
	arial.loadFromFile("Assets/arial.ttf");

	// LIVES
	livesnum.str("");
	for (int k = 0; k < player.lives; k++)
	{
		livesnum << "O ";
	}
	lives.setCharacterSize(30);
	lives.setPosition({ 5, 600 });
	lives.setFont(arial);
	lives.setString(livesnum.str());

	// DODGES
	dodgesNum.str("");
	for (int k = 0; k < player.dodges; k++)
	{
		dodgesNum << "X ";
	}
	dodges.setCharacterSize(30);
	dodges.setPosition({ 560, 620 });
	dodges.setFont(arial);
	dodges.setString(dodgesNum.str());
	dodges.setOrigin(dodges.getLocalBounds().width, dodges.getLocalBounds().height);

	//		SCORE
	// PLAYER 1 SCORE
	
	scoreP1.setCharacterSize(20);
	scoreP1.setPosition({ 100, 5 });
	scoreP1.setFont(arial);
	scoreP1.setString("1UP");
	
	ssScoreP1.str("");
	ssScoreP1 << P1score;
	scoreP1Num.setCharacterSize(15);
	scoreP1Num.setPosition({ 120, 30 });
	scoreP1Num.setFont(arial);
	scoreP1Num.setString(ssScoreP1.str());
	scoreP1Num.setOrigin(round(scoreP1Num.getLocalBounds().width / 2), round(scoreP1Num.getLocalBounds().height / 2));

	// PLAYER 2 SCORE
	scoreP2.setCharacterSize(20);
	scoreP2.setPosition({ 430, 5 });
	scoreP2.setFont(arial);
	scoreP2.setString("2UP");
	
	ssP2Num.str("");
	ssP2Num << P1score;
	scoreP2Num.setCharacterSize(15);
	scoreP2Num.setPosition({ 450, 30});
	scoreP2Num.setFont(arial);
	scoreP2Num.setString(ssP2Num.str());
	scoreP2Num.setOrigin(round(scoreP2Num.getLocalBounds().width / 2), round(scoreP2Num.getLocalBounds().height / 2));

	// HIGHSCORE
	highScoreLabel.setCharacterSize(20);
	highScoreLabel.setPosition({ 230, 5 });
	highScoreLabel.setFont(arial);
	highScoreLabel.setString("High-Score");

	saveData.loadFile();
	highScore = saveData.getHighScore();

	ssHighscore.str("");
	ssHighscore << highScore;
	highScoreText.setCharacterSize(15);
	highScoreText.setPosition({ 280, 30});
	highScoreText.setFont(arial);
	highScoreText.setString(ssHighscore.str());
	highScoreText.setOrigin(round(highScoreText.getLocalBounds().width / 2), round(highScoreText.getLocalBounds().height / 2));

	//			LEVEL INFO SCREEN
	// LEVEL NAME
	levelName.setCharacterSize(50);
	levelName.setPosition({ 290, 200 });
	levelName.setFont(arial);
	levelName.setFillColor(sf::Color::Red);
	levelName.setString("Level Name");
	levelName.setOrigin(levelName.getLocalBounds().width / 2, levelName.getLocalBounds().height / 2);
	// LEVEL
	ssLevel.str("");
	ssLevel << 32 - level << " Stage";
	// LEVEL NUMBER
	levelNumber.setCharacterSize(45);
	levelNumber.setPosition({ 280, 260 });
	levelNumber.setFont(arial);
	levelNumber.setFillColor(sf::Color::Yellow);
	levelNumber.setString(ssLevel.str());
	levelNumber.setOrigin(levelNumber.getLocalBounds().width / 2, levelNumber.getLocalBounds().height / 2);
	// READY TEXT
	readyText.setCharacterSize(30);
	readyText.setPosition({ 240, 360 });
	readyText.setFont(arial);
	readyText.setString("Ready");
	// PLAYER 1 TEXT
	player1Text.setCharacterSize(30);
	player1Text.setPosition({ 230, 400 });
	player1Text.setFont(arial);
	player1Text.setString("Player 1");

	// ENDLESS MODE UI
	endlessMode.setCharacterSize(50);
	endlessMode.setPosition({ 290, 200 });
	endlessMode.setFont(arial);
	endlessMode.setFillColor(sf::Color::Red);
	endlessMode.setString("Endless Mode");
	endlessMode.setOrigin(levelName.getLocalBounds().width / 2, levelName.getLocalBounds().height / 2);

	// LEVEL END SCREEN (NTO DEATH)
	// SHOT DOWN %
	ssPercent.str("");
	ssPercent << "Shooting Down " << 100 << "%";
	downPercentage.setCharacterSize(30);
	downPercentage.setPosition({ 140, 200 });
	downPercentage.setFont(arial);
	downPercentage.setFillColor(sf::Color::Yellow);
	downPercentage.setString(ssPercent.str());
	// BONUS TEXT
	bonusText.setCharacterSize(30);
	bonusText.setPosition({ 240, 300 });
	bonusText.setFont(arial);
	bonusText.setFillColor(sf::Color::Red);
	bonusText.setString("Bonus");
	// BONUS
	ssBonusPoints.str("");
	ssBonusPoints << 100000 << " pts";
	bonusPointsText.setCharacterSize(30);
	bonusPointsText.setPosition({ 210, 350 });
	bonusPointsText.setFont(arial);
	bonusPointsText.setFillColor(sf::Color::Yellow);
	bonusPointsText.setString(ssBonusPoints.str());
	// ROLL BONUS 
	ssRollBonusPoints.str("");
	ssRollBonusPoints << "Rx1000 = " << 3000 << " pts";
	rollBonusText.setCharacterSize(30);
	rollBonusText.setPosition({ 160, 400 });
	rollBonusText.setFont(arial);
	rollBonusText.setFillColor(sf::Color::Yellow);
	rollBonusText.setString(ssRollBonusPoints.str());

	// LEVEL END SCREEN (PLAYER DEATH)
	// SHOOT DOWN PERCENTAGE
	ssDownPercent.str("");
	ssDownPercent << "Shooting Down " << 100 << "%";
	shootDownPercentage.setCharacterSize(30);
	shootDownPercentage.setPosition({ 140, 150 });
	shootDownPercentage.setFont(arial);
	shootDownPercentage.setFillColor(sf::Color::Yellow);
	shootDownPercentage.setString(ssPercent.str());
	// PERCENTAGE COMPLETE
	ssPercentComplete.str("");
	ssPercentComplete << "Percentage " << 100 << "%";
	percentageComplete.setCharacterSize(30);
	percentageComplete.setPosition({ 160, 250 });
	percentageComplete.setFont(arial);
	percentageComplete.setFillColor(sf::Color::Yellow);
	percentageComplete.setString(ssPercentComplete.str());
	// TODAYS HIGHEST PERCENT
	ssTopPercentage.str("");
	ssTopPercentage << "Todays Top " << 100 << "%";
	todaysTopPercentage.setCharacterSize(30);
	todaysTopPercentage.setPosition({ 160, 350 });
	todaysTopPercentage.setFont(arial);
	todaysTopPercentage.setFillColor(sf::Color::Yellow);
	todaysTopPercentage.setString(ssTopPercentage.str());
	// GAME OVER MESSAGE
	gameOver.setCharacterSize(30);
	gameOver.setPosition({ 200, 500 });
	gameOver.setFont(arial);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setString("Game Over");

	// END MESSAGE SCREEN (AFTER BEATING THE FINAL BOSS ENEMY)
	// CONGRATS MESSAGE
	congratulationsText.setCharacterSize(50);
	congratulationsText.setPosition({ 130, 150 });
	congratulationsText.setFont(arial);
	congratulationsText.setFillColor(sf::Color::White);
	congratulationsText.setString("Congratuation");
	// BEST PLAYER MESSAGE 1
	bestPlayerText1.setCharacterSize(30);
	bestPlayerText1.setPosition({ 230, 250 });
	bestPlayerText1.setFont(arial);
	bestPlayerText1.setFillColor(sf::Color::White);
	bestPlayerText1.setString("You Are");
	// BEST PLAYER MESSAGE 2
	bestPlayerText2.setCharacterSize(30);
	bestPlayerText2.setPosition({ 150, 300 });
	bestPlayerText2.setFont(arial);
	bestPlayerText2.setFillColor(sf::Color::White);
	bestPlayerText2.setString("The Best Of Player !");
	// FIGHT ONE MORE MESSAGE
	finalMessageText.setCharacterSize(30);
	finalMessageText.setPosition({ 150, 400 });
	finalMessageText.setFont(arial);
	finalMessageText.setFillColor(sf::Color::White);
	finalMessageText.setString("Fight One Last Stage");

	// WE GIVE UP SCREEN
	// GIVE UP MESSAGE
	wegiveupText.setCharacterSize(50);
	wegiveupText.setPosition({ 150, 100 });
	wegiveupText.setFont(arial);
	wegiveupText.setFillColor(sf::Color::White);
	wegiveupText.setString("We Give Up");
	// BONUS TEXT
	specialBonusText.setCharacterSize(30);
	specialBonusText.setPosition({ 190, 200 });
	specialBonusText.setFont(arial);
	specialBonusText.setFillColor(sf::Color::White);
	specialBonusText.setString("Special Bonus");
	//BONUS AMMOUTN
	bonusNumText.setCharacterSize(30);
	bonusNumText.setPosition({ 185, 250 });
	bonusNumText.setFont(arial);
	bonusNumText.setFillColor(sf::Color::White);
	bonusNumText.setString("10,000,000 pts");
	// GAME OVER MESSAGE
	gameOverText.setCharacterSize(30);
	gameOverText.setPosition({ 200, 350 });
	gameOverText.setFont(arial);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("Game Over");
	// PRESENTED BY MESSAGE
	presentedText.setCharacterSize(30);
	presentedText.setPosition({ 140, 450 });
	presentedText.setFont(arial);
	presentedText.setFillColor(sf::Color::White);
	presentedText.setString("Presented By Reuben");

	// PAUSE MENU
	int xOffset = 280;
	int yOffset = 200;
	int yMulti = 60;
	for (int i = 0; i < 4; i++)
	{
		sf::Text temp;
		temp.setCharacterSize(30);
		temp.setPosition((float)xOffset, (float)yOffset + i * yMulti);
		temp.setFont(arial);
		temp.setString(pauseOptionTexts[i]);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);
		options.push_back(temp);
	}

	box.setFillColor(sf::Color::Blue);
	box.setPosition(100, 150);
	box.setSize({ 350, 300});

	options[selected].setFillColor(sf::Color::Yellow);
}

/*
	LOAD ALL THE AUDIO FILES
*/
void Game::initAudio()
{
	// CLEAR ANY OTHER AUDIO FILES (JUST IN CASE)
	audio.audio.clear();

	// SOUND
	audio.loadAudio("Assets/AUDIO/BossAppears.wav", false);				// 0 = Boss Appear
	audio.loadAudio("Assets/AUDIO/ButtonPress.wav", false);				// 1 = Button Press
	audio.loadAudio("Assets/AUDIO/EndOfRound.wav", false);				// 2 = End Of Round
	audio.loadAudio("Assets/AUDIO/Explosion.wav", false);				// 3 = Explosion (Player and Enemy)
	audio.loadAudio("Assets/AUDIO/FinalBossExplode.wav", false);		// 4 = Final Boss Explode (Also when player dies)
	audio.loadAudio("Assets/AUDIO/Hit.wav", false);						// 5 = Hit
	audio.loadAudio("Assets/AUDIO/PowerUp.wav", false);					// 6 = Power Up
	audio.loadAudio("Assets/AUDIO/Shoot.wav", false);					// 7 = Shoot
	audio.loadAudio("Assets/AUDIO/StartOfRound.wav", false);			// 8 = Start Of Round

	// MUSIC
	//audio.loadAudio("Assets/AUDIO/BackgroundMusic.wav", true);		// 9 = BACKGROUND MUSIC
}

/*
	USED BY "int main()" TO CHECK IF THE GAME IS STILL RUNNING
*/
const bool Game::running() const
{
	// CHECK IF THE GAME IS RUNNING BY CHECKING IF THE GAME WINDOW IS OPEN
	return this->window->isOpen();
}
/**
Program: 1942
Filename: EnemySpawner.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: EnemySpawner.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "EnemySpawner.h"

/*
	USED TO TEST SINGULAR ENEMIES
		- THIS WILL BE A SIMPLIFIED VERSION OF THE UPDATE METHOD 
*/
void EnemySpawner::test_update(Player *player)
{
	// IF ENOUGH TIME HAS PASSED AND CAN PLAY THE LEVEL
	if (time(0) - startLevelTime > levelLength && playLevel)
	{
		// STOP SPAWNING ENEMIES
		canSpawn = false;
		// IF ALL ENEMIES HAVE DIED SET playLevel TO FALSE
		if (currentTestSpawns <= 0)
		{
			playLevel = false;
		}
	}
	// IF CAN PLAY THE LEVEL
	if (playLevel)
	{
		// CALL THE MOVE ENEMY FUNCTION
		test_moveEnemy(player);
		// IF CAN SPAWN ENEMIES
		if (canSpawn)
		{
			// SPAWN ENEMIES
			test_spawnEnemy();
		}
	}
}

/*
	USED TO TEST SINGULAR ENEMIES
		- THIS WILL BE A SIMPLIFIED VERSION OF THE MOVE ENEMY METHOD
*/
void EnemySpawner::test_moveEnemy(Player *player)
{
	// LOOP THROUGH ALL CURRENT ENEMIES
	for (int i = 0; i < enemys.size(); i++)
	{
		// CALL THE UPDATE FUNCTION OF THE ENEMY (WILL MOVE THE ENEMEY)
		enemys[i]->update(player);
		// IF THE ENEMY HAS GONE OF THE EDGE OF THE SCREEN
		if (enemys[i]->getPosition().y <= -200 || enemys[i]->getPosition().y >= 750 || enemys[i]->getPosition().x <= -200 || enemys[i]->getPosition().x >= 750 || enemys[i]->die)
		{
			// DESTROY THE ENEMY AND DECREAS THE CURRENT AMMOUNT OF ENEMYS BY 1
			currentTestSpawns--;
			enemys.erase(enemys.begin() + i);
		}
	}
}

/*
	USED TO TEST SINGULAR ENEMIES
		- THIS WILL BE A SIMPLIFIED VERSION OF THE SPAWN ENEMY METHOD
*/
void EnemySpawner::test_spawnEnemy()
{
	// SET THE MIN AND MAX OF THE ENEMY TO SPAWN
	minAmmountTest = 1;
	maxAmmountTest = 1;
	// IF THERE IS ONLY 1 TEST ENEMY LEFT ON THE BOARD
	if (currentTestSpawns < 1)
	{
		// IF ENOUGH TIME HAS PASSED TO SPAWN ANOTHER WAVE OF ENEMIES
		if (float(clock() - startTime5) / CLOCKS_PER_SEC * 1000 >= timeToWaitTestEnemy)
		{
			// FOR THE AMMOUNT OF ENEMIES THAT CAN BE SAPWNED IN A WAVE
			for (int i = 0; i < maxAmmountTest; i++)
			{
				// SPAWN ENEMY AND INCREASE THE CURRENT AMMOUNT OF ENEMIES BY 1
				enemys.push_back(new Ayako());
				currentTestSpawns += 1;
			}
		}
	}
}

/*
	CONSTRUCTOR FOR THE ENEMY SPAWNER (USED TO INITALISE ALL OF THE VARIABLES)
*/
EnemySpawner::EnemySpawner()
{
	// SET THE INITIAL TIME
	startTime = clock();
	startTime2 = clock();
	startTime3 = clock();
	startTime4 = clock();
	startTime5 = clock();
	startLevelTime = time(0);
}

/*
	CALLED AT THE START OF A LEVEL TO
*/
void EnemySpawner::startLevel(int level)
{
	// SET THE INITIAL TIME
	startTime = clock();
	startTime2 = clock();
	startTime3 = clock();
	startTime4 = clock();
	startLevelTime = time(0);
	
	// SET ALL INITIAL VARIABLES
	currentLevel = level;
	playLevel = true;
	canSpawn = true;
	curreentAmmountOfSmallEnemy = 0;
	currentAmmountOfMediumEnemy = 0;
	currentAmmountOfSpecialEnemy = 0;
	smallMinToSpawnMore = 2;
	mediumMinToSpawnMore = 1;
	bossSpawned = false;
	bossKilled = false;
	miniBossSpawned = false;
	currentEnemyDestroyed = 0;
	currentEnemySpawned = 0;
	daihiryuPointsMultiplier = 0;

	//		GAME MODES
	// IF NOT PLAYING INSANE MODE
	if (!insaneMode)
	{
		// FOR EACH OF THE CURRENT LEVELS PLAYED
		for (int i = 0; i < currentLevel; i += 10)
		{
			// INCREASE THE AMMOUNT OF ENEMIES TO SPAWN
			smallMinToSpawnMore += 2;
			mediumMinToSpawnMore++;
		}
	}
	// INSAME MODE
	else
	{
		// FOR EACH OF THE CURRENT LEVELS + 32 (START AT MAX DIFFICULTY)
		for (int i = 0; i < 32 + currentLevel; i += 10)
		{
			// INCREASE THE AMMOUNT OF ENEMIES TO SPAWN
			smallMinToSpawnMore += 2;
			mediumMinToSpawnMore++;
		}
	}
}

/*
	STARTS ENDLESS MODE
*/
void EnemySpawner::startEndlessMode()
{
	endlessMode = true;
	startLevel(32);
}

/*
	STARTS NO POWER UPS MODE
*/
void EnemySpawner::startNoPowerUpMode(int level)
{
	noPowerUpsMode = true;
	startLevel(level);
}

/*
	STARTS INSANE MODE
*/
void EnemySpawner::startInsaneMode(int level)
{
	insaneMode = true;
	startLevel(level);
}

/*
	STARTS RANDOM MODE
*/
void EnemySpawner::startRandomMode(int level)
{
	randomMode = true;
	startLevel(level);
}

/*
	UPDATE FUNCTION HANDLES ALL OF THE ENEMIES AND WILL CALL ALL OTHER FUNCTIONS (MOVEMENT & SPAWNING)
*/
void EnemySpawner::update(Player *player, Audio *audio)
{
	// FOR EACH OF THE POWERUPS CURRENTLY ON SCREEN
	for (PowerUp *powerUp : powerups)
	{
		// CALL THE UPDATE FUNCTION FOR EACH OF THE POWERUPS
		powerUp->update();
	}
	// FOR THE AMMOUT OF POPUPS ON SCREEN
	for (int i = 0; i < popUps.size(); i++)
	{
		// IF THERE TIME HAS RUN OUT
		if (float(clock() - popUps[i]->spawnTime) / CLOCKS_PER_SEC * 1000 >= popUps[i]->timeToSurvive)
		{
			// DESTROY THE POPUP
			popUps.erase(popUps.begin() + i);
		}
	}

	// ENEDLESS MODE
	if (endlessMode)
	{
		// CALL THE MOVE ENEMY FUNCTION AND CALL THE SPAWN ENEMY FUNCTION
		moveEnemy(player, audio);
		spawnEnemy();
	}
	// ALL OTHER GAME MODES
	else
	{
		// IF THE LEVEL IS CURRENTLY BEING PLAYED
		if (time(0) - startLevelTime > levelLength && playLevel)
		{
			canSpawn = false;
			// IF THE CURRENT LEVEL IS A BOSS LEVEL
			if ((currentLevel == 32 - 25 || currentLevel == 32 - 15 || currentLevel == 32 - 10 || currentLevel == 32 - 5 || currentLevel == 32 - 1) && !bossSpawned && !bossKilled)
			{
				// SPAWN BOSS ENEMY
				audio->audio[0]->play();
				enemys.push_back(new Ayako());
				bossSpawned = true;
			}
			// IF ALL ENEMIES HAVE BEEN KILLED THEN END THE LEVEL
			if (curreentAmmountOfSmallEnemy <= 0 && currentAmmountOfMediumEnemy <= 0 && currentAmmountOfSpecialEnemy <= 0 && !bossSpawned && !miniBossSpawned)
			{
				playLevel = false;
			}
		}
		// IF PLAYING THE LEVEL
		if (playLevel)
		{
			// CALL THE MOVEENEMY METHOD TO MOVE ALL OF THE ENEMIES
			moveEnemy(player, audio);
			// IF ENEMIES CAN SPAWN
			if (canSpawn)
			{
				// RANDOM MODE
				if (randomMode)
				{
					// SPAWN A RANDOM ENEMY
					randomSpawnEnemy();
				}
				// ALL OTHER MODES
				else
				{
					// SPAWN AN ENEMY
					spawnEnemy();
				}
			}
		}
	}
}

/*
	HANDLES MOVING THE ENEMIS AND ALSO CHECKING IF THEY SHOULD DIE
*/
void EnemySpawner::moveEnemy(Player *player, Audio *audio)
{
	// FOR EACH OF THE ENIMES ON THE SCREEN CURRENTLY
	for (int i = 0; i < enemys.size(); i++)
	{
		// CALL THE UPDATE FUNCTION TO MOVE THE ENEMY
		enemys[i]->update(player);
		
		// IF THE ENEMY IS OUTSIDE OF THE GAMES BOUNDS
		if (enemys[i]->getPosition().y <= -200 || enemys[i]->getPosition().y >= 750 || enemys[i]->getPosition().x <= -200 || enemys[i]->getPosition().x >= 750 || enemys[i]->die)
		{
			// INCREASE THE TOTAL & CURRENT ENEMIES SPAWNED BY 1
			totalEnemySpawned++;
			currentEnemySpawned++;

			// IF THE ENEMY HAS DIED
			if (enemys[i]->die)
			{
				// INCREASE THE SCORE
				scoreChanged = true;

				// INCREASE THE TOTAL & CURRENT ENEMIES DESTROYED BY 1
				totalEnemyDestroyed++;
				currentEnemyDestroyed++;
				
				// IF THE ENEMY WAS A BOSS
				if (enemys[i]->type() == 12)
				{
					// PLAY BOSS DEATH EFFECT
					audio->audio[4]->play();
				}
				else
				{
					// PLAY REGUALR ENEMY DEATH EFFECT
					audio->audio[3]->play();
				}
			}

			// ZERO
			if (enemys[i]->type() == 0)
			{
				curreentAmmountOfSmallEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200,false));
				}
			}
			// BVD
			else if (enemys[i]->type() == 1)
			{
				currentAmmountOfMediumEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT & POINTS POPUP
					currentPoints += 1000;
					popUps.push_back(new PopUp("1000", enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// DAIHIRYU
			else if (enemys[i]->type() == 2)
			{
				miniBossSpawned = false;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT & POINTS POPUP
					currentPoints += 2000 + (500 * daihiryuPointsMultiplier);
					popUps.push_back(new PopUp(std::to_string(2000 + (500 * daihiryuPointsMultiplier)), enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			//AKAMIZU
			else if (enemys[i]->type() == 3)
			{
				curreentAmmountOfSmallEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 30;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// RAIZAN
			else if (enemys[i]->type() == 4)
			{
				curreentAmmountOfSmallEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// RED 1
			else if (enemys[i]->type() == 5)
			{
				currentAmmountOfSpecialEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
					// DEFEATED ALL 5 REDS
					if (currentReds == 0)
					{
						//DESTROYED THEM ALL SO SPAWN A POWERUP IN THAT GIVEN POSITION
						currentPoints += 500;
						popUps.push_back(new PopUp("500", enemys[i]->getPosition(), clock(), 1000));
						spawnPowerUp(enemys[i]->getPosition());
					}
				}
			}
			// SHORYU
			else if (enemys[i]->type() == 6)
			{
				currentAmmountOfMediumEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT & POINTS POPUP
					popUps.push_back(new PopUp("1000", enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					currentPoints += 1000;
				}
			}
			// BONUS FIGHTER
			else if (enemys[i]->type() == 7)
			{
				currentAmmountOfSpecialEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					powerups.push_back(new Yashichi(enemys[i]->getPosition()));
					currentPoints += 50;
				}
			}
			// QING
			else if (enemys[i]->type() == 8)
			{
				currentAmmountOfMediumEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT & POINTS POPUP
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					popUps.push_back(new PopUp("1500", enemys[i]->getPosition(), clock(), 1000));
					currentPoints += 1500;
				}
			}
			// FUKUSUKE
			else if (enemys[i]->type() == 9)
			{
				curreentAmmountOfSmallEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// RED 2
			else if (enemys[i]->type() == 10)
			{
				currentAmmountOfSpecialEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
					// DEFEATED ALL 5 REDS
					if (currentReds == 0)
					{
						//DESTROYED THEM ALL SO SPAWN A POWERUP IN THAT GIVEN POSITION
						currentPoints += 500;
						popUps.push_back(new PopUp("500", enemys[i]->getPosition(), clock(), 1000));
						spawnPowerUp(enemys[i]->getPosition());
					}
				}
			}
			// RED 3
			else if (enemys[i]->type() == 11)
			{
				currentAmmountOfSpecialEnemy--;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
					// DEFEATED ALL 5 REDS
					if (currentReds == 0)
					{
						//DESTROYED THEM ALL SO SPAWN A POWERUP IN THAT GIVEN POSITION
						currentPoints += 500;
						popUps.push_back(new PopUp("500", enemys[i]->getPosition(), clock(), 1000));
						spawnPowerUp(enemys[i]->getPosition());
					}
				}
			}
			// AYAKO
			else if (enemys[i]->type() == 12)
			{
				// BOSS DEFEATED
				bossSpawned = false;
				bossKilled = true;
				// ENEMY DIED
				if (enemys[i]->die)
				{
					// INCREASE POINTS AND CREATE EXPLOSTION EFFECT & POINTS POPUP
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					popUps.push_back(new PopUp("20000", enemys[i]->getPosition(), clock(), 1000));
					currentPoints += 20000;
				}
			}
			// REMOVE THE ENEMY FROM THE LIST OF ENEMIES
			enemys.erase(enemys.begin() + i);
		}
	}
}

/*
	WILL SPAWN A RANDOM POWER UP IN THE GIVEN POSITION, DEPENDING ON THE CURRENT LEVEL OF THE SHIP (SPECIFICALLY FOR THE GREEN POWERUP
	WHICH IT WILL ALWAYS SPAWN FIRST IF THE PLAYER DOES NOT ALLREADY HAVE IT)
*/
void EnemySpawner::spawnPowerUp(sf::Vector2f pos) 
{
	// GREEN - 4 SHOTS
	if (!hasQuadShot) 
	{
		// ADD A GREEN POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new GreenPowerUp(pos));
		hasQuadShot = true;
		return;
	}

	//GENERATE A RANDOM NUMBER BETWEEN 1-6
	int ran = rand() % (6 + 1 - 1) + 1;
	
	// WHITE - DESTROY ALL ENEMIES
	if (ran == 1)
	{
		// ADD A WHITE POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new WhitePowerUp(pos));
	}
	// GRAY - 6 SHOTS
	else if (ran == 2) 
	{
		// ADD A GRAY POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new GrayPowerUp(pos));
		hasSextShot = true;
	}
	// ORANGE - NO ENEMY SHOOTING
	else if (ran == 3) 
	{
		// ADD A ORANGE POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new OrangePowerUp(pos));
	}
	// YELLOW - +1 LOOP
	else if (ran == 4) 
	{
		// ADD A YELLOW POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new YellowPowerUp(pos));
	}
	// BLACK - +1 LIFE
	else if (ran == 5) 
	{
		// ADD A BLACK POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new BlackPowerUp(pos));
	}
	// RED - +1000 POINTS
	else if (ran == 6) 
	{
		// ADD A RED POWER UP TO THE VECTOR OF POWER UPS
		powerups.push_back(new RedPowerUp(pos));
	}
}

/*
	SPAWNS A RADNOM ENEMY EVERY PERIOD OF TIME FOR EACH TYPE OF ENEMY
*/
void EnemySpawner::randomSpawnEnemy()
{
	// IF ENOUGH TIME HAS PASSED SINCE THE LAST MINI BOSS ENEMY HAS SPAWNED
	if (float(clock() - startTime4) / CLOCKS_PER_SEC * 1000 >= timeToWaitMiniBoss)
	{
		// SPANW A RANDOM ENEMY
		Spawn();
	}
	// IF ENOUGH TIME HAS PASSED SINCE THE LAST SPECIAL ENEMY HAS SPAWNED
	if (float(clock() - startTime3) / CLOCKS_PER_SEC * 1000 >= timeToWaitSpecialEnemy)
	{
		// SPANW A RANDOM ENEMY
		Spawn();
	}
	// IF ENOUGH TIME HAS PASSED TO SPAWN ANOTHER MEDIUM ENEMY
	if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWaitMediumEnemy)
	{
		// SPANW A RANDOM ENEMY
		Spawn();
	}
	// IF ENOUGH TIME HAS PASSED SINCE THE LAST SMALL ENEMY HAS SPAWNED
	if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWaitSmallEnemy)
	{
		// SPANW A RANDOM ENEMY
		Spawn();
	}
}

/*
	SPAWNS A RANDOM ENEMY FROM ALL OF THE ENEMIES
*/
void EnemySpawner::Spawn()
{
	// GENERATE A RANDOM NUMBER BETWEEN 0-12
	int enemyToSpawn = rand() % (12 + 1 - 0) + 0;

	// DAIHIRYU
	if (enemyToSpawn == 0)
	{
		startTime4 = clock();
		// IF CAN SPAWN THIS ENEMY
		if (!miniBossSpawned && rand() % 10 == 0)
		{
			// CALCULATE SPAWN POSITION
			int temp1 = rand() % (daihiryuMaxX + 1 - daihiryuMinX) + daihiryuMinX;
			int temp2 = rand() % (daihiryuMaxY + 1 - daihiryuMinY) + daihiryuMinY;
			// SPAWN ENEMY
			enemys.push_back(new Daihiryu(temp1, temp2));
			miniBossSpawned = true;
			return;
		}
	}
	// RED
	else if (enemyToSpawn == 1)
	{
		startTime3 = clock();
		// IF THERE IS ONLY 1 SPECIAL ENEMY LEFT ON THE BOARD
		if (currentAmmountOfSpecialEnemy < 1)
		{
			// CALCULATE SPAWN POSITION
			int temp2 = rand() % (red1MaxY + 1 - red1MinY) + red1MinY;
			// SPAWN ENEMY
			enemys.push_back(new Red(1, temp2));
			enemys.push_back(new Red(2, temp2));
			enemys.push_back(new Red(3, temp2));
			enemys.push_back(new Red(4, temp2));
			enemys.push_back(new Red(5, temp2));
			currentAmmountOfSpecialEnemy += 5;
			currentReds = 5;
			return;
		}
	}
	// RED2
	else if (enemyToSpawn == 2)
	{
		startTime3 = clock();
		// IF THERE IS ONLY 1 SPECIAL ENEMY LEFT ON THE BOARD
		if (currentAmmountOfSpecialEnemy < 1)
		{
			// SPAWN ENEMY
			enemys.push_back(new Red2(1));
			enemys.push_back(new Red2(2));
			enemys.push_back(new Red2(3));
			enemys.push_back(new Red2(4));
			enemys.push_back(new Red2(5));
			currentAmmountOfSpecialEnemy += 5;

			currentReds = 5;
			return;
		}
	}
	// RED3
	else if (enemyToSpawn == 3)
	{
		startTime3 = clock();
		// IF THERE IS ONLY 1 SPECIAL ENEMY LEFT ON THE BOARD
		if (currentAmmountOfSpecialEnemy < 1)
		{
			// SPAWN ENEMY
			enemys.push_back(new Red3(1));
			enemys.push_back(new Red3(2));
			enemys.push_back(new Red3(3));
			enemys.push_back(new Red3(4));
			enemys.push_back(new Red3(5));
			currentAmmountOfSpecialEnemy += 5;
			currentReds = 5;
			return;
		}
	}
	// BONUS FIGHTER
	else if (enemyToSpawn == 4)
	{
		startTime3 = clock();
		// IF THERE IS ONLY 1 SPECIAL ENEMY LEFT ON THE BOARD
		if (currentAmmountOfSpecialEnemy < 1)
		{
			// CALCULATE SPAWN POSITION
			int temp1 = rand() % (bonusMaxX + 1 - bonusMinX) + bonusMinX;
			int temp2 = rand() % (bonusMaxY + 1 - bonusMinY) + bonusMinY;
			// SPAWN ENEMY
			enemys.push_back(new BounsFighter(rand() % 2 == 0, temp1, temp2));
			currentAmmountOfSpecialEnemy++;
			return;
		}
	}
	// BVD
	else if (enemyToSpawn == 5)
	{
		startTime2 = clock();
		// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
		if (currentAmmountOfMediumEnemy < mediumMinToSpawnMore)
		{
			// CALCULATE SPAWN POSITION
			int temp1 = rand() % (bvdMaxX + 1 - bvdMinX) + bvdMinX;
			int temp2 = rand() % (bvdMaxY + 1 - bvdMinY) + bvdMinY;
			// SPAWN ENEMY
			enemys.push_back(new BVD(rand() % 2 == 0, temp1, temp2));
			currentAmmountOfMediumEnemy++;
			return;
		}
	}
	// SHORYU
	else if (enemyToSpawn == 6)
	{
		startTime2 = clock();
		// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
		if (currentAmmountOfMediumEnemy < mediumMinToSpawnMore)
		{
			// CALCULATE SPAWN POSITION
			int temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
			int temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
			// SPAWN ENEMY
			enemys.push_back(new Shoryu(true, temp1, temp2));
			currentAmmountOfMediumEnemy++;

			// CALCULATE SPAWN POSITION
			temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
			temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
			// SPAWN ENEMY
			enemys.push_back(new Shoryu(false, temp1, temp2));
			currentAmmountOfMediumEnemy++;
			return;
		}
	}
	// QING
	else if (enemyToSpawn == 7)
	{
		startTime2 = clock();
		// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
		if (currentAmmountOfMediumEnemy < mediumMinToSpawnMore)
		{
			// FOR THE MAX CLUSTER SIZE
			for (int i = 0; i < qingMaxAmmount; i++)
			{
				// IF LESS THAN MIN AMMOUNT
				if (i < qingMinAmmount)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
					int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
					// SPAWN ENEMY
					enemys.push_back(new Qing(temp1, temp2));
					currentAmmountOfMediumEnemy++;
				}
				// MORE THAN MIN AMMOUNT
				else
				{
					// RANDOM CHANCE TO SPAWN ENEMY
					int ran2 = rand() % (100 + 1 - 0) + 0;
					if (ran2 < qingSpawnChance * 100)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
						int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
						// SPAWN ENEMY
						enemys.push_back(new Qing(temp1, temp2));
						currentAmmountOfMediumEnemy++;
					}
				}
			}
			return;
		}
	}
	// ZERO
	else if (enemyToSpawn == 8)
	{
		startTime = clock();
		// IF THERE ARE LESS THAN 2 SMALL ENEMYS LEFT ON THE BOARD
		if (curreentAmmountOfSmallEnemy <= smallMinToSpawnMore)
		{
			// FOR THE MAX CLUSTER SIZE
			for (int i = 0; i < zeroMaxAmmount; i++)
			{
				// IF LESS THAN MIN AMMOUNT
				if (i < zeroMinAmmount)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
					int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
					// SPAWN ENEMY
					enemys.push_back(new Zero((float)temp1, (float)temp2));
					curreentAmmountOfSmallEnemy++;
				}
				// MORE THAN MIN AMMOUNT
				else
				{
					// RANDOM CHANCE TO SPAWN ENEMY
					int ran2 = rand() % (100 + 1 - 0) + 0;
					if (ran2 < zeroSpawnChance * 100)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
						int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
						// SPAWN ENEMY
						enemys.push_back(new Zero((float)temp1, (float)temp2));
						curreentAmmountOfSmallEnemy++;
					}
				}
			}
			return;
		}
	}
	// AKAMIZU
	else if (enemyToSpawn == 9)
	{
		startTime = clock();
		// IF THERE ARE LESS THAN 2 SMALL ENEMYS LEFT ON THE BOARD
		if (curreentAmmountOfSmallEnemy <= smallMinToSpawnMore)
		{
			// FOR THE MAX CLUSTER SIZE
			for (int i = 0; i < akamizuMaxAmmount; i++)
			{
				// IF LESS THAN MIN AMMOUNT
				if (i < akamizuMinAmmount)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
					int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
					// SPAWN ENEMY
					enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
					curreentAmmountOfSmallEnemy++;
				}
				// MORE THAN MIN AMMOUNT
				else
				{
					// RANDOM CHANCE TO SPAWN ENEMY
					int ran2 = rand() % (100 + 1 - 0) + 0;
					if (ran2 < akamizuSpawnChance * 100)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
						int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
						// SPAWN ENEMY
						enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
				}
			}
			return;
		}
	}
	// RAIZAN
	else if (enemyToSpawn == 10)
	{
		startTime = clock();
		// IF THERE ARE LESS THAN 2 SMALL ENEMYS LEFT ON THE BOARD
		if (curreentAmmountOfSmallEnemy <= smallMinToSpawnMore)
		{
			// FOR THE MAX CLUSTER SIZE
			for (int i = 0; i < raizanMaxAmmount; i++)
			{
				// IF LESS THAN MIN AMMOUNT
				if (i < raizanMinAmmount)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
					int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
					// SPAWN ENEMY
					enemys.push_back(new Raizan(temp1, temp2));
					curreentAmmountOfSmallEnemy++;
				}
				// MORE THAN MIN AMMOUNT
				else
				{
					// RANDOM CHANCE TO SPAWN ENEMY
					int ran2 = rand() % (100 + 1 - 0) + 0;
					if (ran2 < raizanSpawnChance * 100)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
						int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
						// SPAWN ENEMY
						enemys.push_back(new Raizan(temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
				}
			}
			return;
		}
	}
	// FUKUSUKE
	else if (enemyToSpawn == 11)
	{
		startTime = clock();
		// IF THERE ARE LESS THAN 2 SMALL ENEMYS LEFT ON THE BOARD
		if (curreentAmmountOfSmallEnemy <= smallMinToSpawnMore)
		{
			// FOR THE MAX CLUSTER SIZE
			for (int i = 0; i < fukusukeMaxAmmount; i++)
			{
				// IF LESS THAN MIN AMMOUNT
				if (i < fukusukeMinAmmount)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
					int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
					// SPAWN ENEMY
					enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
					curreentAmmountOfSmallEnemy++;
				}
				// MORE THAN MIN AMMOUNT
				else
				{
					// RANDOM CHANCE TO SPAWN ENEMY
					int ran2 = rand() % (100 + 1 - 0) + 0;
					if (ran2 < fukusukeSpawnChance * 100)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
						int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
						// SPAWN ENEMY
						enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
				}
			}
			return;
		}
	}
	// AYAKO
	else if (enemyToSpawn == 12)
	{
		// IF CAN SPAWN THIS ENEMY
		if (rand() % 25 == 0 && !bossSpawned)
		{
			// SPAWN ENEMY
			enemys.push_back(new Ayako());
			bossSpawned = true;
		}
	}
}

/*
	REGULAR SPAWNER FOR THE NON RANDOM & NOT TESTING MODES THAT WILL SPAWN ENEMIES IN WAVES 
	WITH THE DIFFICULTY AND AMMOUNT OF EACH EMENY COMPLETLY CUSTOMIZABLE
*/
void EnemySpawner::spawnEnemy()
{
	// FOR INCREASEING THE DEFAULT LEVEL TO 32 WHEN PLAIYING INSANE MODE
	int j = currentLevel;
	if (insaneMode)
		currentLevel += 32;

	// IF THERE IS A MINI BOSS
	if (miniBossSpawned)
	{
		// IF ENOUGH TIME HAS PASSED SINCE LAST MINI BOSS SPAWNED
		if (float(clock() - startTime4) / CLOCKS_PER_SEC * 1000 >= timeToWaitMiniBoss)
		{
			// 1 IN 3 CHANCE TO SPAWN
			if (rand() % 3 == 0)
			{
				// RESET CLOCK
				startTime4 = clock();
				// IF PAST LEVEL 5
				if (currentLevel >= 5)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (daihiryuMaxX + 1 - daihiryuMinX) + daihiryuMinX;
					int temp2 = rand() % (daihiryuMaxY + 1 - daihiryuMinY) + daihiryuMinY;
					// SPAWN ENEMY
					enemys.push_back(new Daihiryu(temp1, temp2));
					miniBossSpawned = true;
				}
			}
			// CANT SPAWN
			else
			{
				// RESET CLOCK
				startTime4 = clock();
			}
		}
	}
	// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
	if (currentAmmountOfSpecialEnemy < 1 && !noPowerUpsMode)
	{
		// IF ENOUGH TIME HAS PASSED SINCE LAST SPECIAL ENEMY SPAWNED
		if (float(clock() - startTime3) / CLOCKS_PER_SEC * 1000 >= timeToWaitSpecialEnemy)
		{
			// 1 IN 3 CHANCE TO SPAWN
			if (rand() % 3 == 0)
			{
				// RESET CLOCK
				startTime3 = clock();

				// CHANCE TO SWAP ENEMY TO SPAWN
				int ran = rand() % (100 + 1 - 0) + 0;
				
				// CALCULATE WHICH ENEMIES CAN BE SPAWNED BASED ON THE LEVEL
				int specialsAvailable = 0;
				if (currentLevel >= 15)
					specialsAvailable = 3;
				else if (currentLevel >= 7)
					specialsAvailable = 2;
				else if (currentLevel >= 1)
					specialsAvailable = 1;
				
				// IF CAN SWAP
				if (ran <= swapSpecialChance * 100)
				{
					// SWAP TO ANOTHER ENEMY TO SPAWN
					currentSpecialEnemy = rand() % (specialsAvailable + 1 - 0) + 0;
				}

				// RED1
				if (currentSpecialEnemy == 1) 
				{
					// CALCULATE SPAWN POSITION
					int temp2 = rand() % (red1MaxY + 1 - red1MinY) + red1MinY;
					// SPAWN ENEMY
					enemys.push_back(new Red(1, temp2));
					enemys.push_back(new Red(2, temp2));
					enemys.push_back(new Red(3, temp2));
					enemys.push_back(new Red(4, temp2));
					enemys.push_back(new Red(5, temp2));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				// RED2
				else if (currentSpecialEnemy == 2)
				{
					// SPAWN ENEMY
					enemys.push_back(new Red2(1));
					enemys.push_back(new Red2(2));
					enemys.push_back(new Red2(3));
					enemys.push_back(new Red2(4));
					enemys.push_back(new Red2(5));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				// RED3
				else if (currentSpecialEnemy == 3) 
				{
					// SPAWN ENEMY
					enemys.push_back(new Red3(1));
					enemys.push_back(new Red3(2));
					enemys.push_back(new Red3(3));
					enemys.push_back(new Red3(4));
					enemys.push_back(new Red3(5));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				// BONUS FIGHTER
				else if (currentSpecialEnemy == 0) 
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (bonusMaxX + 1 - bonusMinX) + bonusMinX;
					int temp2 = rand() % (bonusMaxY + 1 - bonusMinY) + bonusMinY;
					// SPAWN ENEMY
					enemys.push_back(new BounsFighter(rand() % 2 == 0, temp1, temp2));
					currentAmmountOfSpecialEnemy++;
				}
			}
			// CANT SPAWN
			else
			{
				// RESET CLOCK
				startTime3 = clock();
			}
		}
	}

	// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
	if (currentAmmountOfMediumEnemy < mediumMinToSpawnMore)
	{
		// IF ENOUGH TIME HAS PASSED TO SPAWN ANOTHER MEDIUM ENEMY
		if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWaitMediumEnemy)
		{
			// THERE IS A 1/3 CHANCE TO SPAWN A MEDIUM ENEMY
			if (rand() % 3 == 0)
			{
				// RESET CLOCK
				startTime2 = clock();

				// CHANCE TO SWAP ENEMY TO SPAWN
				int ran = rand() % (100 + 1 - 0) + 0;

				// CALCULATE WHICH ENEMIES CAN BE SPAWNED BASED ON THE LEVEL
				int mediumsAvailable = 0;
				if (currentLevel >= 20)
					mediumsAvailable = 2;
				else if (currentLevel >= 15)
					mediumsAvailable = 1;
				else if (currentLevel >= 0)
					mediumsAvailable = 0;

				// IF CAN SWAP
				if (ran <= swapMediumChance * 100)
				{
					// SWAP TO ANOTHER ENEMY TO SPAWN
					currentMediumeEnemy = rand() % (mediumsAvailable + 1 - 0) + 0;
				}

				// BVD
				if (currentMediumeEnemy == 0) 
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (bvdMaxX + 1 - bvdMinX) + bvdMinX;
					int temp2 = rand() % (bvdMaxY + 1 - bvdMinY) + bvdMinY;
					// SPAWN ENEMY
					enemys.push_back(new BVD(rand() % 2 == 0, temp1, temp2));
					currentAmmountOfMediumEnemy++;
				}
				// SHORYU
				else if (currentMediumeEnemy == 1)
				{
					// CALCULATE SPAWN POSITION
					int temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
					int temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
					// SPAWN ENEMY
					enemys.push_back(new Shoryu(true, temp1, temp2));
					currentAmmountOfMediumEnemy++;

					// CALCULATE SPAWN POSITION
					temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
					temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
					// SPAWN ENEMY
					enemys.push_back(new Shoryu(false, temp1, temp2));
					currentAmmountOfMediumEnemy++;
				}
				// QING
				else if (currentMediumeEnemy == 2) 
				{
					// FOR THE MAX CLUSTER SIZE
					for (int i = 0; i < qingMaxAmmount; i++)
					{
						// IF LESS THAN MIN AMMOUNT
						if (i < qingMinAmmount)
						{
							// CALCULATE SPAWN POSITION
							int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
							int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
							// SPAWN ENEMY
							enemys.push_back(new Qing(temp1, temp2));
							currentAmmountOfMediumEnemy++;
						}
						// MORE THAN MIN AMMOUNT
						else
						{
							// CHANCE TO SPAWN ENEMY
							int ran2 = rand() % (100 + 1 - 0) + 0;
							if (ran2 < qingSpawnChance * 100)
							{
								// CALCULATE SPAWN POSITION
								int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
								int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
								// SPAWN ENEMY
								enemys.push_back(new Qing(temp1, temp2));
								currentAmmountOfMediumEnemy++;
							}
						}
					}
				}
			}
			// CANT SPAWN
			else
			{
				// RESET CLOCK
				startTime2 = clock();
			}
		}
	}
	// IF THERE ARE LESS THAN 2 SMALL ENEMYS LEFT ON THE BOARD
	if (curreentAmmountOfSmallEnemy <= smallMinToSpawnMore)
	{
		// IF ENOUGH TIME HAS PASSED SINCE THE LAST SMALL ENEMY HAS SPAWNED
		if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWaitSmallEnemy)
		{
			// RESET CLOCK
			startTime = clock();

			// CHANCE TO SWAP ENEMY TO SPAWN
			int ran = rand() % (100 + 1 - 0) + 0;

			// CALCULATE WHICH ENEMIES CAN BE SPAWNED BASED ON THE LEVEL
			int smallsAvailable = 0;
			if (currentLevel >= 25)
				smallsAvailable = 3;
			else if (currentLevel >= 10)
				smallsAvailable = 2;
			else if (currentLevel >= 5)
				smallsAvailable = 1;
			else if (currentLevel >= 0)
				smallsAvailable = 0;

			// IF CAN SWAP
			if (ran <= swapSmallChance * 100)
			{
				// SWAP TO ANOTHER ENEMY TO SPAWN
				currentSmallEnemy = rand() % (smallsAvailable + 1 - 0) + 0;
			}

			// ZERO
			if (currentSmallEnemy == 0)
			{
				// FOR THE MAX CLUSTER SIZE
				for (int i = 0; i < zeroMaxAmmount; i++)
				{
					// IF LESS THAN MIN AMMOUNT
					if (i < zeroMinAmmount)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
						int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
						// SPAWN ENEMY
						enemys.push_back(new Zero((float)temp1, (float)temp2));
						curreentAmmountOfSmallEnemy++;
					}
					// MORE THAN MIN AMMOUNT
					else
					{
						// CHANCE TO SPAWN ENEMY
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < zeroSpawnChance * 100)
						{
							// CALCULATE SPAWN POSITION
							int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
							int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
							// SPAWN ENEMY
							enemys.push_back(new Zero((float)temp1, (float)temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			// AKAMIZU
			else if (currentSmallEnemy == 1)
			{
				// FOR THE MAX CLUSTER SIZE
				for (int i = 0; i < akamizuMaxAmmount; i++)
				{
					// IF LESS THAN MIN AMMOUNT
					if (i < akamizuMinAmmount)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
						int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
						// SPAWN ENEMY
						enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					// MORE THAN MIN AMMOUNT
					else
					{
						// CHANCE TO SPAWN ENEMY
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < akamizuSpawnChance * 100)
						{
							// CALCULATE SPAWN POSITION
							int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
							int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
							// SPAWN ENEMY
							enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			// RAIZAN
			else if (currentSmallEnemy == 2)
			{
				// FOR THE MAX CLUSTER SIZE
				for (int i = 0; i < raizanMaxAmmount; i++)
				{
					// IF LESS THAN MIN AMMOUNT
					if (i < raizanMinAmmount)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
						int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
						// SPAWN ENEMY
						enemys.push_back(new Raizan(temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					// MORE THAN MIN AMMOUNT
					else
					{
						// CHANCE TO SPAWN ENEMY
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < raizanSpawnChance * 100)
						{
							// CALCULATE SPAWN POSITION
							int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
							int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
							// SPAWN ENEMY
							enemys.push_back(new Raizan(temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			// FUKUSUKE
			else if (currentSmallEnemy == 3)
			{
				// FOR THE MAX CLUSTER SIZE
				for (int i = 0; i < fukusukeMaxAmmount; i++)
				{
					// IF LESS THAN MIN AMMOUNT
					if (i < fukusukeMinAmmount)
					{
						// CALCULATE SPAWN POSITION
						int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
						int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
						// SPAWN ENEMY
						enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					// MORE THAN MIN AMMOUNT
					else
					{
						// CHANCE TO SPAWN ENEMY
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < fukusukeSpawnChance * 100)
						{
							// CALCULATE SPAWN POSITION
							int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
							int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
							// SPAWN ENEMY
							enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
		}
	}
	// SET THE CURRENT LEVEL BACK TO THE ACUTAL LEVEL (THIS IS INCASE OF PLAYING
	// INSANE MODE)
	currentLevel = j;
}

/*
	REDER ALL OF THE ENEMIES, POWERUPS, POPUPS TO THE WINDOW
*/
void EnemySpawner::render(sf::RenderTarget *target)
{
	// CALL THE RENDER FUNCTION ATTACHED TO ALL OF THE ENEMY OBJECTS
	for (Enemy *enemy: enemys)
	{
		enemy->render(target);
	}
	// CALL THE RENDER FUNCTION ATTACHED TO ALL OF THE POWERUP OBJECTS
	for (PowerUp *powerUp : powerups)
	{
		powerUp->render(target);
	}
	// CALL THE RENDER FUNCTION ATTACHED TO ALL OF THE POPUP OBJECTS
	for (PopUp *popUp : popUps)
	{
		popUp->render(target);
	}
}
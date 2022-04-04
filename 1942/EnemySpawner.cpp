#include "EnemySpawner.h"

void EnemySpawner::test_update(Player *player)
{
	if (time(0) - startLevelTime > levelLength && playLevel) // WILL NEED TO ADD AN EXCEPTION WHEN THERE IS A BOSS TO FIGHT
	{
		canSpawn = false;
		if (currentTestSpawns <= 0)
			playLevel = false;
	}
	if (playLevel)
	{
		test_moveEnemy(player);
		if (canSpawn)
			test_spawnEnemy();
	}
}
void EnemySpawner::test_moveEnemy(Player *player)
{
	// call update functions
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->update(player);
		if (enemys[i]->getPosition().y <= -200 || enemys[i]->getPosition().y >= 750 || enemys[i]->getPosition().x <= -200 || enemys[i]->getPosition().x >= 750 || enemys[i]->die)
		{
			currentTestSpawns--;
			enemys.erase(enemys.begin() + i);
		}
	}
}
void EnemySpawner::test_spawnEnemy()
{
	// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
	if (currentTestSpawns < 1)
	{
		if (float(clock() - startTime5) / CLOCKS_PER_SEC * 1000 >= timeToWaitTestEnemy)
		{
			for (int i = 0; i < maxAmmountTest; i++)
			{
				if (i < minAmmountTest)
				{
					int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
					int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
					enemys.push_back(new Ayako());
					currentTestSpawns++;
				}
				else
				{
				int ran2 = rand() % (100 + 1 - 0) + 0;
				if (ran2 < 1 * 100)
				{
					int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
					int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
					enemys.push_back(new Ayako());
					currentTestSpawns++;
				}
				}
			}
		}
	}
}





EnemySpawner::EnemySpawner()
{
	startTime = clock();
	startTime2 = clock();
	startTime3 = clock();
	startTime4 = clock();
	startLevelTime = clock();
}

void EnemySpawner::startLevel(int level)
{
	startTime = clock();
	startTime2 = clock();
	startTime3 = clock();
	startTime4 = clock();
	startLevelTime = time(0);
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

	for (int i = 0; i < currentLevel; i += 10)
	{
		smallMinToSpawnMore += 2;
		mediumMinToSpawnMore++;
	}
}



void EnemySpawner::update(Player *player)
{
	for (PowerUp *powerUp : powerups)
	{
		powerUp->update();
	}
	for (int i = 0; i < popUps.size(); i++)
	{
		if (float(clock() - popUps[i]->spawnTime) / CLOCKS_PER_SEC * 1000 >= popUps[i]->timeToSurvive)
		{
			popUps.erase(popUps.begin() + i);
		}
	}


	if (time(0) - startLevelTime > levelLength && playLevel) // WILL NEED TO ADD AN EXCEPTION WHEN THERE IS A BOSS TO FIGHT
	{
		canSpawn = false;
		if ((currentLevel == 32 - 25 || currentLevel == 32 - 15 || currentLevel == 32 - 10 || currentLevel == 32 - 5 || currentLevel == 32 - 1) && !bossSpawned && !bossKilled)
		{
			// spawn boss enemy
			enemys.push_back(new Ayako());
			bossSpawned = true;
		}
		if (curreentAmmountOfSmallEnemy <= 0 && currentAmmountOfMediumEnemy <= 0 && currentAmmountOfSpecialEnemy <= 0 && !bossSpawned && !miniBossSpawned)
			playLevel = false;
	}
	if (playLevel)
	{
		moveEnemy(player);
		if (canSpawn)
			spawnEnemy();
	}
}
void EnemySpawner::moveEnemy(Player *player)
{
	// call update functions
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->update(player);
		if (enemys[i]->getPosition().y <= -200 || enemys[i]->getPosition().y >= 750 || enemys[i]->getPosition().x <= -200 || enemys[i]->getPosition().x >= 750 || enemys[i]->die)
		{
			totalEnemySpawned++;
			currentEnemySpawned++;
			if (enemys[i]->die)
			{
				totalEnemyDestroyed++;
				currentEnemyDestroyed++;
			}

			if (enemys[i]->type() == 0)
			{
				curreentAmmountOfSmallEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200,false));
				}
			}
			else if (enemys[i]->type() == 1)
			{
				currentAmmountOfMediumEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 1000;
					popUps.push_back(new PopUp("1000", enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			else if (enemys[i]->type() == 2)
			{
				miniBossSpawned = false;
				if (enemys[i]->die)
				{
					currentPoints += 2000 + (500 * daihiryuPointsMultiplier);
					popUps.push_back(new PopUp(std::to_string(2000 + (500 * daihiryuPointsMultiplier)), enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			else if (enemys[i]->type() == 3)
			{
				curreentAmmountOfSmallEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 30;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			else if (enemys[i]->type() == 4)
			{
				curreentAmmountOfSmallEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// RED 1
			else if (enemys[i]->type() == 5)
			{
				currentAmmountOfSpecialEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
					if (currentReds == 0)
					{
						//DESTROYED THEM ALL SO SPAWN A POWERUP IN THAT GIVEN POSITION
						currentPoints += 500;
						popUps.push_back(new PopUp("500", enemys[i]->getPosition(), clock(), 1000));
						spawnPowerUp(enemys[i]->getPosition());
					}
				}
			}
			else if (enemys[i]->type() == 6)
			{
				currentAmmountOfMediumEnemy--;
				if (enemys[i]->die)
				{
					popUps.push_back(new PopUp("1000", enemys[i]->getPosition(), clock(), 1000));
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					currentPoints += 1000;
				}
			}
			// BONUS FIGHTER
			else if (enemys[i]->type() == 7)
			{
				currentAmmountOfSpecialEnemy--;
				if (enemys[i]->die)
				{
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					powerups.push_back(new Yashichi(enemys[i]->getPosition()));
					currentPoints += 50;
				}
			}
			else if (enemys[i]->type() == 8)
			{
				currentAmmountOfMediumEnemy--;
				if (enemys[i]->die)
				{
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					popUps.push_back(new PopUp("1500", enemys[i]->getPosition(), clock(), 1000));
					currentPoints += 1500;
				}
			}
			else if (enemys[i]->type() == 9)
			{
				curreentAmmountOfSmallEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 50;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
				}
			}
			// RED 2
			else if (enemys[i]->type() == 10)
			{
				currentAmmountOfSpecialEnemy--;
				if (enemys[i]->die)
				{
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
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
				if (enemys[i]->die)
				{
					currentPoints += 100;
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));

					currentReds--;
					if (currentReds == 0)
					{
						//DESTROYED THEM ALL SO SPAWN A POWERUP IN THAT GIVEN POSITION
						currentPoints += 500;
						popUps.push_back(new PopUp("500", enemys[i]->getPosition(), clock(), 1000));
						spawnPowerUp(enemys[i]->getPosition());
					}
				}
			}
			else if (enemys[i]->type() == 12)
			{
				bossSpawned = false;
				bossKilled = true;
				if (enemys[i]->die)
				{
					popUps.push_back(new PopUp(enemys[i]->getPosition(), clock(), 200, false));
					popUps.push_back(new PopUp("20000", enemys[i]->getPosition(), clock(), 1000));
					currentPoints += 20000;
				}
			}
			enemys.erase(enemys.begin() + i);
		}
	}
}

void EnemySpawner::spawnPowerUp(sf::Vector2f pos) 
{
	if (!hasQuadShot) // GREEN
	{
		powerups.push_back(new GreenPowerUp(pos));

		// REMOVE THIS LINE AN PUT IT WHEN THE POWER UP IS COLLIED WITH
		hasQuadShot = true;
		return;
	}

	int ran;
	if (hasSextShot)
	{
		do
		{
			ran = rand() % (6 + 1 - 1) + 1;
		} while (ran == 2);
	}
	else
	{
		ran = rand() % (6 + 1 - 1) + 1;
	}
	
	if (ran == 1) // WHITE
	{
		powerups.push_back(new WhitePowerUp(pos));
	}
	else if (ran == 2) // GRAY
	{
		powerups.push_back(new GrayPowerUp(pos));
		// REMOVE THIS LINE AN PUT IT WHEN THE POWER UP IS COLLIED WITH
		hasSextShot = true;
	}
	else if (ran == 3) // ORANGE
	{
		powerups.push_back(new OrangePowerUp(pos));
	}
	else if (ran == 4) // YELLOW
	{
		powerups.push_back(new YellowPowerUp(pos));
	}
	else if (ran == 5) // BLACK
	{
		powerups.push_back(new BlackPowerUp(pos));
	}
	else if (ran == 6) // RED
	{
		powerups.push_back(new RedPowerUp(pos));
	}
}
void EnemySpawner::spawnEnemy()
{
	if (miniBossSpawned)
	{
		//std::cout << clock() - startTime4 << " " << timeToWaitMiniBoss << "\n";
		if (float(clock() - startTime4) / CLOCKS_PER_SEC * 1000 >= timeToWaitMiniBoss)
		{
			std::cout << currentLevel << "\n";
			if (rand() % 3 == 0)
			{
				startTime4 = clock();

				
				if (currentLevel >= 5)
				{
					int temp1 = rand() % (daihiryuMaxX + 1 - daihiryuMinX) + daihiryuMinX;
					int temp2 = rand() % (daihiryuMaxY + 1 - daihiryuMinY) + daihiryuMinY;
					enemys.push_back(new Daihiryu(temp1, temp2));
					miniBossSpawned = true;
				}
			}
			else
			{
				startTime4 = clock();
			}
		}
	}
	// IF THERE IS ONLY 1 MEDIUM ENEMY LEFT ON THE BOARD
	if (currentAmmountOfSpecialEnemy < 1)
	{
		if (float(clock() - startTime3) / CLOCKS_PER_SEC * 1000 >= timeToWaitSpecialEnemy)
		{
			if (rand() % 3 == 0)
			{
				startTime3 = clock();

				// limit the things spawning to the level here
				int ran = rand() % (100 + 1 - 0) + 0;
				
				int specialsAvailable = 0;
				if (currentLevel >= 15)
					specialsAvailable = 3;
				else if (currentLevel >= 7)
					specialsAvailable = 2;
				else if (currentLevel >= 1)
					specialsAvailable = 1;
				
				if (ran <= swapSpecialChance * 100)
				{
					currentSpecialEnemy = rand() % (specialsAvailable + 1 - 0) + 0;
				}


				if (currentSpecialEnemy == 1) // red 1
				{
					int temp2 = rand() % (red1MaxY + 1 - red1MinY) + red1MinY;
					enemys.push_back(new Red(1, temp2));
					enemys.push_back(new Red(2, temp2));
					enemys.push_back(new Red(3, temp2));
					enemys.push_back(new Red(4, temp2));
					enemys.push_back(new Red(5, temp2));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				else if (currentSpecialEnemy == 2) // red 2
				{
					enemys.push_back(new Red2(1));
					enemys.push_back(new Red2(2));
					enemys.push_back(new Red2(3));
					enemys.push_back(new Red2(4));
					enemys.push_back(new Red2(5));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				else if (currentSpecialEnemy == 3) // red 2
				{
					enemys.push_back(new Red3(1));
					enemys.push_back(new Red3(2));
					enemys.push_back(new Red3(3));
					enemys.push_back(new Red3(4));
					enemys.push_back(new Red3(5));
					currentAmmountOfSpecialEnemy += 5;

					currentReds = 5;
				}
				else if (currentSpecialEnemy == 0) // bonus plane
				{
					int temp1 = rand() % (bonusMaxX + 1 - bonusMinX) + bonusMinX;
					int temp2 = rand() % (bonusMaxY + 1 - bonusMinY) + bonusMinY;
					enemys.push_back(new BounsFighter(rand() % 2 == 0, temp1, temp2));
					currentAmmountOfSpecialEnemy++;
				}
			}
			else
			{
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
				startTime2 = clock();

				// CHANGE WHICH MEDIUM ENEMY IS BEING SPAWNED
				int ran = rand() % (100 + 1 - 0) + 0;

				// LIMIT SPAWNS THE THE CURRENT LEVELS SPAWNS
				int mediumsAvailable = 0;
				if (currentLevel >= 20)
					mediumsAvailable = 2;
				else if (currentLevel >= 15)
					mediumsAvailable = 1;
				else if (currentLevel >= 0)
					mediumsAvailable = 0;

				if (ran <= swapMediumChance * 100)
				{
					currentMediumeEnemy = rand() % (mediumsAvailable + 1 - 0) + 0;
				}

				if (currentMediumeEnemy == 0) // bvd
				{
					int temp1 = rand() % (bvdMaxX + 1 - bvdMinX) + bvdMinX;
					int temp2 = rand() % (bvdMaxY + 1 - bvdMinY) + bvdMinY;
					enemys.push_back(new BVD(rand() % 2 == 0, temp1, temp2));
					currentAmmountOfMediumEnemy++;
				}
				else if (currentMediumeEnemy == 1) // shoryu
				{
					int temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
					int temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
					enemys.push_back(new Shoryu(true, temp1, temp2));
					currentAmmountOfMediumEnemy++;
					temp1 = rand() % (shoryuMaxX + 1 - shoryuMinX) + shoryuMinX;
					temp2 = rand() % (shoryuMaxY + 1 - shoryuMinY) + shoryuMinY;
					enemys.push_back(new Shoryu(false, temp1, temp2));
					currentAmmountOfMediumEnemy++;
				}
				else if (currentMediumeEnemy == 2) // qing
				{
					for (int i = 0; i < qingMaxAmmount; i++)
					{
						if (i < qingMinAmmount)
						{
							int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
							int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
							enemys.push_back(new Qing(temp1, temp2));
							currentAmmountOfMediumEnemy++;
						}
						else
						{
							int ran2 = rand() % (100 + 1 - 0) + 0;
							if (ran2 < qingSpawnChance * 100)
							{
								int temp1 = rand() % (qingMaxX + 1 - qingMinX) + qingMinX;
								int temp2 = rand() % (qingMaxY + 1 - qingMinY) + qingMinY;
								enemys.push_back(new Qing(temp1, temp2));
								currentAmmountOfMediumEnemy++;
							}
						}
					}
				}
			}
			else
			{
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
			startTime = clock();

			// CHANGE THE SMALL ENEMY BEING SPAWNED
			int ran = rand() % (100 + 1 - 0) + 0;

			// LIMIT SPAWNS THE THE CURRENT LEVELS SPAWNS
			int smallsAvailable = 0;
			if (currentLevel >= 25)
				smallsAvailable = 3;
			else if (currentLevel >= 10)
				smallsAvailable = 2;
			else if (currentLevel >= 5)
				smallsAvailable = 1;
			else if (currentLevel >= 0)
				smallsAvailable = 0;

			if (ran <= swapSmallChance * 100)
			{
				currentSmallEnemy = rand() % (smallsAvailable + 1 - 0) + 0;
			}

			if (currentSmallEnemy == 0) // zero
			{
				for (int i = 0; i < zeroMaxAmmount; i++)
				{
					if (i < zeroMinAmmount)
					{
						int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
						int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
						enemys.push_back(new Zero(temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					else
					{
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < zeroSpawnChance * 100)
						{
							int temp1 = rand() % (zeroMaxX + 1 - zeroMinX) + zeroMinX;
							int temp2 = rand() % (zeroMaxY + 1 - zeroMinY) + zeroMinY;
							enemys.push_back(new Zero(temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			else if (currentSmallEnemy == 1) // akamizu
			{
				for (int i = 0; i < akamizuMaxAmmount; i++)
				{
					if (i < akamizuMinAmmount)
					{
						int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
						int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
						enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					else
					{
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < akamizuSpawnChance * 100)
						{
							int temp1 = rand() % (akamizuMaxX + 1 - akamizuMinX) + akamizuMinX;
							int temp2 = rand() % (akamizuMaxY + 1 - akamizuMinY) + akamizuMinY;
							enemys.push_back(new Akamizu(rand() % 2 == 0, temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			else if (currentSmallEnemy == 2) // raizan
			{
				for (int i = 0; i < raizanMaxAmmount; i++)
				{
					if (i < raizanMinAmmount)
					{
						int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
						int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
						enemys.push_back(new Raizan(temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					else
					{
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < raizanSpawnChance * 100)
						{
							int temp1 = rand() % (raizanMaxX + 1 - raizanMinX) + raizanMinX;
							int temp2 = rand() % (raizanMaxY + 1 - raizanMinY) + raizanMinY;
							enemys.push_back(new Raizan(temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
			else if (currentSmallEnemy == 3) // fukusuke
			{
				for (int i = 0; i < fukusukeMaxAmmount; i++)
				{
					if (i < fukusukeMinAmmount)
					{
						int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
						int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
						enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
						curreentAmmountOfSmallEnemy++;
					}
					else
					{
						int ran2 = rand() % (100 + 1 - 0) + 0;
						if (ran2 < fukusukeSpawnChance * 100)
						{
							int temp1 = rand() % (fukusukeMaxX + 1 - fukusukeMinX) + fukusukeMinX;
							int temp2 = rand() % (fukusukeMaxY + 1 - fukusukeMinY) + fukusukeMinY;
							enemys.push_back(new Fukusuke(rand() % 2 == 0, temp1, temp2));
							curreentAmmountOfSmallEnemy++;
						}
					}
				}
			}
		}
	}
}
void EnemySpawner::render(sf::RenderTarget *target)
{
	for (Enemy *enemy: enemys)
	{
		enemy->render(target);
	}
	for (PowerUp *powerUp : powerups)
	{
		powerUp->render(target);
	}
	for (PopUp *popUp : popUps)
	{
		popUp->render(target);
	}
}
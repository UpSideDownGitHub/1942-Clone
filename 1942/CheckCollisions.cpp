/**
Program: 1942
Filename: CheckCollisions.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File: CheckCollisions.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "CheckCollisions.h"

/*
	CHECK IF THE ANY OF THE PLAYER BULLETS HAVE COLLIDED WITH ANY OF THE ENEMIES OR
	IF ANY OF THE PLAYER BULLETS HAVE WHENT OFF THE EDGE OF THE SCREEN AND SO CAN
	BE DESTROYED
*/
void CheckCollisions::checkPlayerBulletCollisions(std::vector<Bullet *> playerBullets, std::vector<Enemy*> enemys)
{
	// FOR THE AMMOUNT OF PLAYER BULLETS
	for (int i = 0; i < playerBullets.size(); i++)
	{
		// IF THE CURERNT BULLET IS HAS GONE OF THE TOP OF THE SCREEN
		if (playerBullets[i]->getPosition().y < -10)
		{
			// REMOVE THE BULLET FROM THE LIST
			copyOverBullets(playerBullets, i);
			// MOVE TO THE NEXT BULLET
			continue;
		}
		// FOR ALL OF THE ENEMYS ON SCREEN
		for (int j = 0; j < enemys.size(); j++)
		{
			// IF THE CURRENT PLAYER BULLET IS COLLIDING WITH THE CURRENT ENEMY
			if (playerBullets[i]->getBounds().intersects(enemys[j]->getGlobalBounds()))
			{
				// TAKE OFF HEALTH FROM THAT ENEMY
				enemys[j]->removeHealth();
				// IF THAT ENEMY HAS NO MORE HEALTH LEFT SET IT TO EXPLODE
				if (enemys[j]->health > 0)
				{
					playerBullets[i]->makeExplosion = true;
				}
				// REMOVE THE CURRENT BULLET FROM THE LIST
				copyOverBullets(playerBullets, i);
				// STOP CHECKING FOR THIS BULLET AS HAS BEEN REMOVED
				break;
			}
		}
	}
}

/*
	HANDLES REMOVING PLAYER BULLETS FROM THE LIST TO THEN BE COPIED BY THE Game
	CLASS AND USED TO RENDER ALL OF THE DIFFRENT BULLETS
*/
void CheckCollisions::copyOverBullets(std::vector<Bullet *> playerBullets, int i)
{
	// SET COPY BULLETS TO TRUE SO THE Game CLASS WILL COPY OVER THE BULLETS
	// WITH THE BULLETS REMOVED
	copyBullets = true;
	// ERASE THE GIVEN BULLET FROM THE LIST OF BULLETS
	playerBullets.erase(playerBullets.begin() + i);
	// SET THE VECTOR OF BULLETS TO BE THE COPIED BY THE Game CLASS
	bulletsToCopy = playerBullets;
}

/*
	CHECKS IF ANY OF THE ENEMIES HAVE HIT THE PLAYER CHARACTER AND IF THEY HAVE WILL TAKE A 
	LIFE OF THE PLAYER (KILL THE PLAYER)
*/
void CheckCollisions::checkEnemyHitPlayer(Player *player, std::vector<Enemy*> enemys)
{
	// FOR EACH OF THE ENEIMES CURRRENTLY SPAWNED
	for (int i = 0; i < enemys.size(); i++)
	{
		// IF THEY ARE COLLIDING WITH THE PLAYER
		if (player->getGlobalBounds().intersects(enemys[i]->getGlobalBounds()))
		{
			// TAKE A LIGE OF THE PLAYER
			player->lives--;
			// SET TO TRUE TO UPDATE THE PLAYER RELATED UI
			changedLives = true;
			return;
		}
	}
}

/*
	CHECK THAT ANY OF THE ENEMY BULLETS HAVE COLLIDED WITH THE PLAYER
*/
void CheckCollisions::checkEnemyBulletCollisions(std::vector<Bullet *> enemyBullets, Player *player)
{
	// FOR EACH OF THE ENEMY BULLETS CURRENTLY SPAWNED
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		// IF THE CURRENT ENEMY BULLET IS COLLIDING WITH THE PLAYER
		if (player->getGlobalBounds().intersects(enemyBullets[i]->getBounds()))
		{
			// TAKE A LIFE OF THE PLAYER
			player->lives--;
			
			// SET TO TRUE TO UPDATE PLAYER HEALTH UI
			changedLives = true;
			
			// IF THE ENEMY BULLET IS ON THE LEFT OF THE PLAYER
			if (enemyBullets[i]->getPosition().x < player->getPosition().x)
			{
				// SET TO REMOVE THE LEFT FIGHTER (THIS WILL ONLY BE REMOVED IF THE PLAYER
				// HAS THE ENEMY FIGHTERS EQUIPPED)
				player->leftFighter = false;
				continue;
			}
			return;
		}
	}
}

/*
	CHECK IF THE PLAYER HAS COLLIDED WITH ANY POWERUP OBJECTS THAT ARE ON THE SCREEN
	AND THEN RETURN THE POWERUPS THAT THE PLAYER IS CURRENTLY COLLIDING WITH
*/
std::vector<int> CheckCollisions::checkPlayerPowerUpCollisions(std::vector<PowerUp *> powerUps, Player *player)
{
	std::vector<int> temp;
	// FOR THE AMMOUNT OF POWER UPS CURRENTLY IN THE GAME
	for (int i = 0; i < powerUps.size(); i++)
	{
		// IF THE PLAYER IS COLLIDING WITH ANY OF THE POWERUPS
		if (player->getGlobalBounds().intersects(powerUps[i]->getGlobalBounds()))
		{
			// REMOVE THE POWERUP FROM THE MAIN LIST
			copyOverPowerUps(powerUps, i);
			// ADD THE POWERUP TYPE TO THE LIST OF POWERUPS COLLIDED WITH TO RETURN
			temp.push_back(powerUps[i]->type());
			temp.push_back(i);

			// RETURN THE VECTOR HOLDING THE POWER UP TYPE AND I
			return temp;
		}
	}
	// RETURN THE EMPTY VECTOR
	return temp;
}

/*
	HANDLES REMOVING POWER UPS FROM THE LIST TO THEN BE COPIED BY THE Game
	CLASS AND USED TO RENDER ALL OF THE DIFFRENT POWER UPS
*/
void CheckCollisions::copyOverPowerUps(std::vector<PowerUp *> powerUps, int i)
{
	// SET COPY POWER UPS TO TRUE SO THE Game CLASS WILL COPY OVER THE POWER UPS
	// WITH THE POWER UPS REMOVED
	copyPowerUps = true;
	// ERASE THE GIVEN POWERUP FROM THE LIST OF POWERUPS
	powerUps.erase(powerUps.begin() + i);
	// SET THE VECTOR OF POWER UPS TO BE COPIED BY THE Game	CLASS
	powerUpsCopy = powerUps;
}
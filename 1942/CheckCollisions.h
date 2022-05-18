/**
Program: 1942
Filename: CheckCollisions.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File CheckCollisions.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <list>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <chrono>

#include "Player.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "Bullet.h"
#include "PowerUp.h"

class CheckCollisions
{
public:
	//			METHODS
	// BULLET & ENEMY
	void checkPlayerBulletCollisions(std::vector<Bullet *> playerBullets, std::vector<Enemy*> enemys);
	void copyOverBullets(std::vector<Bullet *> playerBullets, int i);

	// ENEMY & PLAYER
	void checkEnemyHitPlayer(Player *player, std::vector<Enemy*> enemys);
	void checkEnemyBulletCollisions(std::vector<Bullet *> enemyBullets, Player *player);

	// POWERUPS
	void copyOverPowerUps(std::vector<PowerUp *> powerUps, int i);
	std::vector<int> checkPlayerPowerUpCollisions(std::vector<PowerUp *> powerUps, Player *player);

	// VARIABLES
	bool copyBullets = false;
	std::vector<Bullet *> bulletsToCopy;

	bool changedLives = false;

	bool copyPowerUps = false;
	std::vector<PowerUp *> powerUpsCopy;

private:

};


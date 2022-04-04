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

#pragma once
class CheckCollisions
{
public:
	void checkPlayerBulletCollisions(std::vector<Bullet *> playerBullets, std::vector<Enemy*> enemys);
	void copyOverBullets(std::vector<Bullet *> playerBullets, int i);

	void checkEnemyHitPlayer(Player *player, std::vector<Enemy*> enemys);

	void checkEnemyBulletCollisions(std::vector<Bullet *> enemyBullets, Player *player);

	std::vector<int> checkPlayerPowerUpCollisions(std::vector<PowerUp *> powerUps, Player *player);
	void copyOverPowerUps(std::vector<PowerUp *> powerUps, int i);


	bool copyBullets = false;
	std::vector<Bullet *> bulletsToCopy;

	bool changedLives = false;

	bool copyPowerUps = false;
	std::vector<PowerUp *> powerUpsCopy;

private:

};


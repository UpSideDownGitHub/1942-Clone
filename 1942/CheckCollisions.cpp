#include "CheckCollisions.h"


void CheckCollisions::checkPlayerBulletCollisions(std::vector<Bullet *> playerBullets, std::vector<Enemy*> enemys)
{
	for (int i = 0; i < playerBullets.size(); i++)
	{
		if (playerBullets[i]->getPosition().y < -10)
		{
			copyOverBullets(playerBullets, i);
			continue;
		}
		for (int j = 0; j < enemys.size(); j++)
		{
			if (playerBullets[i]->getBounds().intersects(enemys[j]->getGlobalBounds()))
			{
				enemys[j]->removeHealth();
				if (enemys[j]->health > 0)
				{
					playerBullets[i]->makeExplosion = true;
				}
				copyOverBullets(playerBullets, i);
			}
		}
	}
}

void CheckCollisions::copyOverBullets(std::vector<Bullet *> playerBullets, int i)
{
	copyBullets = true;
	playerBullets.erase(playerBullets.begin() + i);
	bulletsToCopy = playerBullets;
}

void CheckCollisions::checkEnemyHitPlayer(Player *player, std::vector<Enemy*> enemys)
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (player->getGlobalBounds().intersects(enemys[i]->getGlobalBounds()))
		{
			player->lives--;
			changedLives = true;
		}
	}
}

void CheckCollisions::checkEnemyBulletCollisions(std::vector<Bullet *> enemyBullets, Player *player)
{
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (player->getGlobalBounds().intersects(enemyBullets[i]->getBounds()))
		{
			player->lives--;
			changedLives = true;
		}
	}
}

std::vector<int> CheckCollisions::checkPlayerPowerUpCollisions(std::vector<PowerUp *> powerUps, Player *player)
{
	std::vector<int> temp;
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (player->getGlobalBounds().intersects(powerUps[i]->getGlobalBounds()))
		{
			copyOverPowerUps(powerUps, i);
			temp.push_back(powerUps[i]->type());
			temp.push_back(i);
			return temp;
		}
	}
	return temp;
}
void CheckCollisions::copyOverPowerUps(std::vector<PowerUp *> powerUps, int i)
{
	copyPowerUps = true;
	powerUps.erase(powerUps.begin() + i);
	powerUpsCopy = powerUps;
}
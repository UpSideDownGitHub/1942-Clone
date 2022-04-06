#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "Enemy.h"
#include "PowerUp.h"
#include "PopUp.h"
#include "Audio.h"

#pragma once
class EnemySpawner
{
public:
	// TESTING
	void test_update(Player *player);
	void test_spawnEnemy();
	void test_moveEnemy(Player *player);
	int maxTestSpawns = 1;
	int currentTestSpawns = 0;
	time_t startTime5;
	float timeToWaitTestEnemy = 100;
	int minAmmountTest = 1;
	int maxAmmountTest = 1;

	//									VARIABLES
	// ENEMY TYPES
	std::vector<Enemy*> enemys;
	
	// POWER UP 
	std::vector<PowerUp*> powerups;
	bool hasQuadShot = false;
	bool hasSextShot = false;

	// POPUPS
	std::vector<PopUp *> popUps;

	// END SCREEN INFOMATION
	int totalEnemySpawned = 0;
	int totalEnemyDestroyed = 0;
	int currentEnemySpawned = 0;
	int currentEnemyDestroyed = 0;

	//	POINTS
	int currentPoints = 0;
	int daihiryuPointsMultiplier = 0;
	bool scoreChanged = false;

	//					SPAWN CHANCE
	// TIMING
	time_t startTime, startTime2, startTime3, startTime4;									//10000
	float timeToWaitSmallEnemy = 1000, timeToWaitMediumEnemy = 5000, timeToWaitSpecialEnemy = 10000, timeToWaitMiniBoss = 20000; // Milliseconds
	// GENERAL
	int curreentAmmountOfSmallEnemy = 0;
	int currentAmmountOfMediumEnemy = 0;
	int currentAmmountOfSpecialEnemy = 0;
	bool miniBossSpawned = false;
	bool bossSpawned = false;


	int smallMinToSpawnMore = 2;
	int mediumMinToSpawnMore = 1;

	//		SPECIAL ENEMY TYPES
	int swapSpecialChance = 1;
	int currentSpecialEnemy = 0;

	int currentReds = -1;

	// RED 1
	int red1MinY = 50;
	int red1MaxY = 300;

	// RED 2
	// just need to spawn

	// RED 3
	// just need to spawn

	// BONUS ENEMY
	int bonusMinX = 0;
	int bonusMaxX = 20;
	int bonusMinY = -100;
	int bonusMaxY = 0;

	//		BOSS ENEMY TYPES
	// DAIHIRYU
	int daihiryuMinX = 150;
	int daihiryuMaxX = 500;
	int daihiryuMinY = -100;
	int daihiryuMaxY = 0;
	// AYAKO
	bool bossKilled = false;

	//		SMALL ENEMY TYPES
	int currentSmallEnemy = 0;
	float swapSmallChance = 0.1;

	// ZERO
	float zeroSpawnChance= 0.5;
	int zeroMinAmmount = 3;
	int zeroMaxAmmount = 5;
	int zeroMinX = 10;
	int zeroMaxX = 300;
	int zeroMinY = -100;
	int zeroMaxY = 0;
	
	// AKAMIZU
	float akamizuSpawnChance = 0.5;
	int akamizuMinAmmount = 3;
	int akamizuMaxAmmount = 5;
	int akamizuMinX = -100;
	int akamizuMaxX = 0;
	int akamizuMinY = 0;
	int akamizuMaxY = 300;

	// RAIZAN
	float raizanSpawnChance = 0.5;
	int raizanMinAmmount = 3;
	int raizanMaxAmmount = 5;
	int raizanMinX = 10;
	int raizanMaxX = 500;
	int raizanMinY = -100;
	int raizanMaxY = 0;

	// FUKUSUKE
	float fukusukeSpawnChance = 0.5;
	int fukusukeMinAmmount = 2;
	int fukusukeMaxAmmount = 5;
	int fukusukeMinX = -100;
	int fukusukeMaxX = 0;
	int fukusukeMinY = 0;
	int fukusukeMaxY = 300;

	//		MEDIUM ENEMY TYPES
	int currentMediumeEnemy = 0;
	float swapMediumChance = 0.5;

	// BVD
	float bvdSpawnChance = 0.5;
	int bvdMinAmmount = 1;
	int bvdMaxAmmount = 1;
	int bvdMinX = 10;
	int bvdMaxX = 300;
	int bvdMinY = 0;
	int bvdMaxY = 0;

	// SHORyU
	float shoryuSpawnChance = 0.5;
	int shoryuMinAmmount = 1;
	int shoryuMaxAmmount = 1;
	int shoryuMinX = 10;
	int shoryuMaxX = 300;
	int shoryuMinY = 0;
	int shoryuMaxY = 0;

	// QING
	float qingSpawnChance = 0.5;
	int qingMinAmmount = 1;
	int qingMaxAmmount = 5;
	int qingMinX = 10;
	int qingMaxX = 550;
	int qingMinY = 640;
	int qingMaxY = 740;

	bool playLevel = false;
	int currentLevel = 0;
	bool canSpawn = true;

	time_t startLevelTime;
	int levelLength = 10; // 120

	// CONSTRUCTOR
	EnemySpawner();

	// METHODS
	void update(Player *player, Audio *audio);
	void moveEnemy(Player *player, Audio *audio);
	void spawnEnemy();
	void render(sf::RenderTarget *target);
	void spawnPowerUp(sf::Vector2f pos);

	void startLevel(int level);

private:
};


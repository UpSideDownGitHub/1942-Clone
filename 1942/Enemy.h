#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Player.h"


#pragma once
class Enemy
{
public:
	// CONSTRUCTOR
	Enemy();

	// VARIABLES
	int health;	
	bool die = false;
	bool canShoot = true;

	// METHODS
	void removeHealth();
	virtual void update(Player *player);
	void render(sf::RenderTarget *target);
	virtual int type();
	virtual void shoot(Player *player, float randomDeviation);

	// ACCESSORS
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	
protected:
	// VARIABLES
	sf::ConvexShape shape;
	sf::RectangleShape center;

	// METHODS


};

class Zero : public Enemy
{
public:
	// VARIABLES
	float verMoveSpeed;
	float maxVertSpeed;
	float rateOfChange;
	bool startChange;
	bool stopChange;
	float distanceToPlayer;
	float horMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	//METHODS
	Zero(float xOffset, float yOffset);
	virtual void update(Player *player);
	virtual int type();
protected:
};

class BVD : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;
	float distaneFromEdge;

	bool once = true;
	float randomDeviation = 50;

	bool down = true, left = false, right = false, up = false;
	bool leftSide = true;
	bool doneturn = false, end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	// METHODS
	BVD(bool onLeft, int xOffset, int yOffset);
	virtual void update(Player *player);
	void nextMove(Player *player);
	virtual int type();

private:
};

class Daihiryu : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;
	float distaneFromEdge;

	int currentLoop = 0;
	int maxLoops = 2;

	bool once = true;
	float randomDeviation = 10;

	bool down = false, left = false, right = false, up = true;
	bool end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;


	// METHODS
	Daihiryu(int xOffset, int yOffset);
	virtual void update(Player *player);
	virtual void shoot(Player *player, float randomDeviation);
	void nextMove(Player *player);
	virtual int type();
private:

};

class Akamizu : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;
	float distaneFromEdge;

	bool once = true;
	float randomDeviation = 100;

	bool down = false, left = false, right = false, up = false;
	bool end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	bool movingLeft;

	// METHODS
	Akamizu(bool shipMovingLeft, int xOffset, int yOffset);
	virtual void update(Player *player);
	void nextMove(Player *player);
	virtual int type();
private:
};

class Raizan : public Enemy
{
public:
	// VARIABLES
	float verMoveSpeed;
	float maxHorSpeed;
	float rateOfChange;
	bool startChange;
	bool stopChange;
	float distanceToPlayer;
	float horMoveSpeed;
	bool left;

	bool once = true;
	float randomDeviation = 50;
	float shootDistance = 350;

	//METHODS
	Raizan(int xOffset, int yOffset);
	virtual void update(Player *player);
	virtual int type();
private:
};

class Red : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;

	float turnPos1;
	float turnPos2;
	float turnPos3;
	float turnPos4;

	bool once = true;
	float randomDeviation = 50;

	bool down = false, left = false, right = true, up = false;
	bool end = false, nextLoop = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	int currentLoop = 0;

	// METHODS
	Red(int num, int yOffset);
	virtual void update(Player *player);
	void nextMove();
	virtual int type();
private:
};

class Shoryu : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;
	float distaneFromEdge;

	bool once = true;
	float randomDeviation = 50;

	bool down = true, left = false, right = false, up = false;
	bool leftSide = true;
	bool doneturn = false, end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	// METHODS
	Shoryu(bool onLeft, int xOffset, int yOffset);
	virtual void update(Player *player);
	void nextMove(Player *player);
	virtual int type();

private:
};
	
class BounsFighter : public Enemy
{
public:
	// VARIABLES
	float verMoveSpeed;
	float horMoveSpeed;
	float rateOfChange;
	float increaseInSpeed;
	bool moveLeft;

	bool once = true;
	float randomDeviation = 50;

	//METHODS
	BounsFighter(bool left, int xOffset, int yOffset);
	void update(Player *player);
	virtual int type();

private:
};

class Qing : public Enemy
{
public:
	float verMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	Qing(int xOffset, int yOffset);
	virtual void update(Player *player);
	virtual int type();

private:
};


class Fukusuke : public Enemy
{
public:
	// VARIABLES
	float maxHorMoveSpeed, maxVerMoveSpeed;
	float horMoveSpeed;
	float verMoveSpeed;
	float rateOfChange;

	float moveDownDistance;
	float moveUpDistance;
	float turnPos1;
	float turnPos2;

	bool once = true;
	float randomDeviation = 100;

	bool down = false, left = false, right = false, up = false;
	bool end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	bool movingLeft;

	// METHODS
	Fukusuke(bool shipMovingLeft, int xOffset, int yOffset);
	virtual void update(Player *player);
	void nextMove(Player *player);
	virtual int type();

private:
};

class Red2 : public Enemy
{
public:
	// VARIABLES
	float horMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	// METHODS
	Red2(int num);
	void update(Player *player);
	virtual int type();
private:
};

class Red3 : public Enemy
{
public:
	// VARIABLES
	float horMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	// METHODS
	Red3(int num);
	virtual void update(Player *player);
	virtual int type();
private:
};

class Ayako : public Enemy
{
public:
	// VARIABLES
	float verMoveSpeed;
	float turnPos1;
	float turnPos2;

	bool up = true, down = false;

	time_t startTime1, startTime2, startTime3, startTime4;
	float timeToWait = 2500;


	float randomDeviation = 200;

	// METHODS
	Ayako();
	virtual void update(Player *player);
	void nextMove();
	virtual int type();
	virtual void shoot(Player *player, float randomDeviation, sf::Vector2f spawnPos);
private:
};
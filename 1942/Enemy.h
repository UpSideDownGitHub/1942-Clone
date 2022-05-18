/**
Program: 1942
Filename: Enemy.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File Enemy.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Player.h"

class Enemy
{
public:
	// CONSTRUCTOR
	Enemy();

	// VARIABLES
	int health;	
	bool die = false;
	bool canShoot = true;

	//			METHODS
	void removeHealth();
	void render(sf::RenderTarget *target);
	// VIRTUAL 
	virtual void update(Player *player);
	virtual int type();
	virtual void shoot(Player *player, float randomDeviation);

	// ACCESSORS
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	
protected:
	// VARIABLES
	sf::ConvexShape shape;
	sf::RectangleShape center;
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

	// CONSTRUCTOR
	Zero(float xOffset, float yOffset);
	
	//METHODS
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

	// CONSTRUCTOR
	BVD(bool onLeft, int xOffset, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	void nextMove(Player *player);
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

	// CONSTRUCTOR
	Daihiryu(int xOffset, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual void shoot(Player *player, float randomDeviation);
	virtual int type();
	void nextMove(Player *player);
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

	// CONSTRUCTOR
	Akamizu(bool shipMovingLeft, int xOffset, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	void nextMove(Player *player);
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

	// CONSTRUCTOR
	Red(int num, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	void nextMove();
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

	// CONSTRUCTOR
	Shoryu(bool onLeft, int xOffset, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	void nextMove(Player *player);

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

	// CONSTRUCTOR
	BounsFighter(bool left, int xOffset, int yOffset);

	//METHODS
	virtual int type();
	void update(Player *player);

private:
};

class Qing : public Enemy
{
public:
	// VARIABLES
	float verMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	// CONSTRUCTOR
	Qing(int xOffset, int yOffset);
	
	// METHODS
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

	float moveUpDistance;
	float turnPos1;
	float turnPos2;

	bool once = true;
	float randomDeviation = 100;

	bool down = false, left = false, right = false, up = false;
	bool end = false;
	bool decDown = false, decUp = false, decLeft = false, decRight = false;

	bool movingLeft;

	// CONSTRUCTOR
	Fukusuke(bool shipMovingLeft, int xOffset, int yOffset);

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	void nextMove(Player *player);

private:
};

class Red2 : public Enemy
{
public:
	// VARIABLES
	float horMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	// CONSTRUCTOR
	Red2(int num);

	// METHODS
	virtual int type();
	void update(Player *player);
private:
};

class Red3 : public Enemy
{
public:
	// VARIABLES
	float horMoveSpeed;

	bool once = true;
	float randomDeviation = 50;

	// CONSTRUCTOR
	Red3(int num);

	// METHODS
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

	// CONSTRUCTOR
	Ayako();

	// METHODS
	virtual void update(Player *player);
	virtual int type();
	virtual void shoot(Player *player, float randomDeviation, sf::Vector2f spawnPos);
	void nextMove();
private:
};
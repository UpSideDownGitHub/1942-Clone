/**
Program: 1842
Filename: PopUp.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: PopUp.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class PowerUp
{
public:
	// METHODS
	virtual void update();
	virtual int type();
	void render(sf::RenderTarget *target);
	
	// VARIABLES
	float moveSpeed = 1;

	// ACCESSORS
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
protected:
	// VARIABLES
	sf::CircleShape shape;
};

/*
	UNLOCK 4 SHOT ABILITY IN PLANE
*/
class GreenPowerUp: public PowerUp
{
public:
	GreenPowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	DESTROY ALL ENEMY SHIPS
*/
class WhitePowerUp : public PowerUp
{
public:
	WhitePowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	UNLOCK THE 2 EXTRA FIGHTERS (6 SHOTS)
*/
class GrayPowerUp : public PowerUp
{
public:
	GrayPowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	NO ENEMY SHOOTING FOR LIMATED TIME
*/
class OrangePowerUp : public PowerUp
{
public:
	OrangePowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	+1 LOOP FOR THE CURRENT LEVEL
*/
class YellowPowerUp : public PowerUp
{
public:
	YellowPowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	+1 LIFE 
*/
class BlackPowerUp : public PowerUp
{
public:
	BlackPowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	+1000 POINTS
*/
class RedPowerUp : public PowerUp
{
public:
	RedPowerUp(sf::Vector2f spawnPosition);
	virtual int type();
};

/*
	+5000 POINTS (DROPPED BY THE BonusFighters)
*/
class Yashichi : public PowerUp
{
public:
	Yashichi(sf::Vector2f spawnPosition);
	virtual int type();
};

/**
Program: 1842
Filename: Player.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 28/01/22
*/
/*
File: Player.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Input.h"
#include "Bullet.h"
#include "Audio.h"

class Player
{
public:
	//			VARIABLES
	Input input;

	// BULLET SHOT
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> enemyBullets;

	float movementSpeed = 3;
	int secondsToNextShot = 1;

	int shootingMethod = 1;
	bool leftFighter = true;

	int lives = 3;


	// DODGING
	time_t startTimeForDodge;
	float dogeIFrames = 2000;
	int dodges = 3;
	bool takeDamage = true;
	
	// CONSTRUCTOR
	Player();

	// METHODS
	void update(sf::RenderWindow *window, Audio *audio);
	void render(sf::RenderTarget *target);
	void shoot();

	// ACCESSORS
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

private:
	// VARIABLES
	sf::RectangleShape shape;
	sf::Vector2f movement;
	int Xmax, Xmin, Ymax, Ymin;

	bool canShoot = false;
	time_t start, end;
};


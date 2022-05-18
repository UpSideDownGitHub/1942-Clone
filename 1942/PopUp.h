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
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <iostream>

class PopUp
{
public:
	// CONSTRUCTORS
	PopUp(std::string text, sf::Vector2f spawnPostion, time_t spawnTime, float timeToSurvive);
	PopUp(sf::Vector2f spawnPosition, time_t spawnTime, float timeToSurvive, bool smallExplosion);

	// METHODS
	void render(sf::RenderTarget *target);

	//		Variables
	// EXPLOSION
	bool explosionEffect = false;
	sf::CircleShape shape;

	// SCORE TEXT
	sf::Text text;
	sf::Font arial;

	time_t spawnTime;
	float timeToSurvive;


private:
	
};


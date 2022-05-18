/*
Program: 1942
Filename: PopUp.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: PopUp.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "PopUp.h"

/*
	CONSTRUCTOR FOR THE POPUP CLASS FOR WORD BASED POPUPS (LIKE POINTS POPUPS)
*/
PopUp::PopUp(std::string text, sf::Vector2f spawnPostion, time_t spawnTime, float timeToSurvive)
{
	// LOAD FONT
	arial.loadFromFile("Assets/arial.ttf");

	// CREATE POPUP WITH THE GIVEN TEXT
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	this->text.setString(text);
	this->text.setFont(arial);
	this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 2);
	this->text.setPosition(spawnPostion);
	
	// SET SPAWN TIME AND TIME TO SURVIVE TO THE GIVEN VALUES
	this->spawnTime = spawnTime;
	this->timeToSurvive = timeToSurvive;
}

/*
	CONSTRUCTOR FOR THE POPUP CLASS FOR EXPLOSIONS (BIG & SMALL)
*/
PopUp::PopUp(sf::Vector2f spawnPosition, time_t spawnTime, float timeToSurvive, bool smallExplosion)
{
	// SET IT TO BE AN EPXLOSION EFFECT
	explosionEffect = true;
	// CREATE AN EXPLOSTION EFFECT
	if (smallExplosion)
	{
		// CREATE THE SHAPE OF THE EXPLOSION EFFECT
		shape.setRadius(10);
		shape.setPosition(spawnPosition);
		shape.setOrigin({ 10,10 });
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(4);
		shape.setPointCount(5);
	}
	// REGULAR EXPLOSION EFFECT
	else
	{
		// CREATE THE SHAPE OF THE EXPLOSION EFFECT
		shape.setRadius(15);
		shape.setPosition(spawnPosition);
		shape.setOrigin({ 20,20 });
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(5);
		shape.setPointCount(5);
	}

	// SET SPAWN TIME AND TIME TO SURVIVE TO THE GIVEN VALUES
	this->spawnTime = spawnTime;
	this->timeToSurvive = timeToSurvive;
}

/*
	RENDER METHOD WILL DRAW ALL OF THE POPUPS TO THE SCREEN
*/
void PopUp::render(sf::RenderTarget *target)
{
	// EXPLOSION EFFECT
	if (explosionEffect)
	{
		// DRAW EXPLOSION
		target->draw(shape);
	}
	// TEXT
	else
	{
		// DRAW TEXT
		target->draw(text);
	}
}
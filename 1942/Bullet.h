/**
Program: 1942
Filename: bullet.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File bullet.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	// CONSTRUCTORS
	Bullet(float pos_x, float pos_y, float movement_speed, bool player, sf::Vector2f size);
	Bullet(float pos_x, float pos_y, sf::Vector2f angleShot, float movement_speed);
	
	// VARIABLES
	bool player;
	bool makeExplosion = false;

	// ACCESSORS
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;

	// METHODS
	void update();
	void render(sf::RenderTarget* target);
private:
	// VARIABLES
	sf::RectangleShape shape;
	float movementSpeed;
	sf::Vector2f angle;
};


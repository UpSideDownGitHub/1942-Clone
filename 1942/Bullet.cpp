/**
Program: 1942
Filename: Bullet.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File: Bullet.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Bullet.h"

/*
	CONSTRUCTOR (TO SET ALL THE INITIAL VARIABLES) (FOR PLAYER SHOT BALLS)
*/
Bullet::Bullet(float pos_x, float pos_y, float movement_speed, bool player, sf::Vector2f size)
{
	// SET THE SIZE / SHAPE / POSITION OF THE BALL 
	this->shape.setSize(size);
	this->shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height);
	this->shape.setPosition(pos_x, pos_y);

	// SET THE SPEED OF THE BALL AS WELL AS WEATHER OR NOT THE BALL WAS FROM THE PLAYER
	this->movementSpeed = movement_speed;
	this->player = player;
}

/*
	CONSTRUCTOR (TO SET ALL THE INITIAL VARIABLES) (FOR ENEMY SHOT BALLS)
*/
Bullet::Bullet(float pos_x, float pos_y, sf::Vector2f angleShot, float movement_speed)
{
	// SET PLAYER TO FALSE AS NOT SHOT BY PLAYER
	player = false;

	// SET THE SIZE / SHAPE / POSITION OF THE BALL 
	this->shape.setSize({ 5, 5 });
	this->shape.setOrigin({ 5 / 2, 5 / 2 });
	this->shape.setPosition(pos_x, pos_y);

	// SET THE ANGLE / MOVEMENT SPEED OF THE BALL
	this->movementSpeed = movement_speed;
	angle = angleShot;
}

/*
	UPDATE FUNCTION OF THE BULLET (CALLED ONCE PER FRAME)
*/
void Bullet::update()
{
	// IF THIS IS A PLAYER BULLET
	if (player)
	{
		// MOVE THE BALL UPWARDS WITH THE MOVEMENT SPEED
		this->shape.move(sf::Vector2f{ 0,-1 } *this->movementSpeed);
		return;
	}
	// MOVE THE BALL AT THE CORRECT ANGLE WITH THE MOVEMENT SPEED
	this->shape.move(angle * movementSpeed);
}

/*
	DRAW THE BULLET TO THE SCREEN
*/
void Bullet::render(sf::RenderTarget* target)
{
	// DRAW THE BULLET TO THE RENDER TARGET
	target->draw(this->shape);
}

/*
	REUTRN THE BOUNDS OF THE BALL
*/
const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}
/*
	RETURN THE POSITION OF THE BALL
*/
const sf::Vector2f Bullet::getPosition() const
{
	return shape.getPosition();
}
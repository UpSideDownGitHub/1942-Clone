/*
Program: 1942
Filename: Player.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: Player.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Player.h"

/*
	CONSTRUCTOR FOR THE PLAYER CLASS
*/
Player::Player()
{
	// RESET CLOCKS
	startTimeForDodge = clock();
	start = time(0);

	// SET SHAPE OF THE PLAYER CHARACTER
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize({ 70,50 });
	this->shape.setOrigin({ 70/2 , 50/2 });
	this->shape.setPosition(280, 320);

	// SET BOUNDARIES OM THE SCREEN
	Xmax = 520;
	Xmin = 40;
	Ymax = 610;
	Ymin = 210;
	
	// OTHER
	canShoot = true;
	end = false;
}

/*
	UPDATE ALL ELEMENTS OF THE PLAYER'S SHIP
*/
void Player::update(sf::RenderWindow *window, Audio *audio)
{
	// CHECK FOR INPUT USING THE INPUT CLASS
	input.pollEvents(window);
	// LEFT
	if (input.buttonPresses[0])
	{
		movement.x -= movementSpeed;
	}
	// UP
	if (input.buttonPresses[1])
	{
		movement.y += movementSpeed;
	}
	// DOWN
	if (input.buttonPresses[2])
	{
		movement.y -= movementSpeed;
	}
	// RIGHT
	if (input.buttonPresses[3])
	{
		movement.x += movementSpeed;
	}

	// IF ENOUGH TIME HAS PASSED TO STOP DODGING
	if (float(clock() - startTimeForDodge) / CLOCKS_PER_SEC * 1000 >= dogeIFrames && !takeDamage)
	{
		// TURN OFF THE DODGE
		takeDamage = true;
		shape.setFillColor(sf::Color::Green);
		audio->audio[1]->play();
	}
	// IF CAN DODGE
	if (input.buttonPresses[5] && dodges-1 >= 0 && takeDamage)
	{
		// START A DODGE
		audio->audio[1]->play();
		dodges--;
		takeDamage = false;
		startTimeForDodge = clock();
		shape.setFillColor(sf::Color::Cyan);
	}
		
	// IF THE SHIP IS WITHIN THE X BOUNDARY
	if (getPosition().x + movement.x < Xmax && getPosition().x + movement.x > Xmin)
	{
		// STOP MOVING IN THAT DIRECTION
		shape.move(movement.x, 0);
	}
	// IF THE SHIP IS WITHIN THE Y BOUNDARY
	if (getPosition().y + movement.y < Ymax && getPosition().y + movement.y > Ymin)
	{
		// STOP MOVING THE SHIP IN THAT DIRECTION
		shape.move(0, movement.y);
	}
	// RESET MOVEMENT
	movement = { 0,0 };
	
	// Z 
	if (input.buttonPresses[4])
	{
		// CAN FIRE
		if (canShoot)
		{
			// FIRE A BULLET
			canShoot = false;
			start = time(0);
			audio->audio[7]->play();
			shoot();
		}
		// ENOUGH TIME HAS PASSED TO SHOOT AGAIN
		else if (time(0) - start > secondsToNextShot)
		{
			// FIRE A BULLET
			start = start + secondsToNextShot;
			audio->audio[7]->play();
			shoot();
		}
	}
	// LET GO OF Z
	else if (!input.buttonPresses[4])
	{
		// CAN SHOOT AGAIN
		canShoot = true;
	}

	// CALL "Update()" METHOD ATTACHED TO THE PLAYER BULLETS
	for (Bullet *bullet : bullets)
	{
		bullet->update();
	}
	// CALL "Update()" METHOD ATTACHED TO THE ENEMY BULLETS
	for (Bullet *bullet : enemyBullets)
	{
		bullet->update();
	}

}

/*
	DRAW THE PLAYER & BULLETS TO THE SCREEN
*/
void Player::render(sf::RenderTarget *target)
{
	// PLAYER
	target->draw(this->shape);
	
	//			BULLETS
	// PLAYER
	for (Bullet *bullet : bullets)
	{
		bullet->render(target);
	}
	// ENEMY
	for (Bullet *bullet : enemyBullets)
	{
		bullet->render(target);
	}
	
}

/*
	SHOOT BULLETS DEPENDING OF THE UPGRADES THE PLAYER CURRENTLY HAS SELECTED
*/
void Player::shoot()
{
	// REGULAR
	if (shootingMethod == 1)
	{
		// REGULAR BULLET
		bullets.push_back(new Bullet(
			getPosition().x,		// X POSITION
			getPosition().y,		// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{ 30,15 }));				// SIZE
	}
	// QUAD
	else if (shootingMethod == 2)
	{
		// MEDIUM BULLET
		bullets.push_back(new Bullet(
			getPosition().x,	// X POSITION
			getPosition().y,	// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{ 80,15 }));				// SIZE
	}
	// FIVE BULLETS
	else if (shootingMethod == 3)
	{
		// LEFT BULLET ON FIVE
		if (leftFighter)
		{
			// ONE FIGHTER BULLET
			bullets.push_back(new Bullet(
				getPosition().x-10,	// X POSITION
				getPosition().y,	// Y POSITION
				6,						// SPEED
				true,					// PLAYER BULLET
				{ 100,15 }));				// SIZE
		}
		// RIGHT BULLET ON FIVE
		else
		{
			// ONE FIGHTER BULLET
			bullets.push_back(new Bullet(
				getPosition().x+10,	// X POSITION
				getPosition().y,	// Y POSITION
				6,						// SPEED
				true,					// PLAYER BULLET
				{ 100,15 }));				// SIZE
		}
	}
	// SIX BULLETS
	else if (shootingMethod == 4)
	{
		// LARGE BULLET
		bullets.push_back(new Bullet(
			getPosition().x,	// X POSITION
			getPosition().y,	// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{ 120,15 }));				// SIZE
	}

}

/*
	USED TO GET THE POSITION OF THE CANNON
*/
const sf::Vector2f Player::getPosition() const
{
	return this->shape.getPosition();
}

/*
	USED TO GET THE BOUNDS OF THE CANNON
*/
const sf::FloatRect Player::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}


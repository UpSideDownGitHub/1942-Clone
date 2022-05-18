/*
Program: 1942
Filename: PowerUp.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: PowerUp.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "PowerUp.h"

/*
	UPDATE FUNCTION WILL MOVE THE POWER UP DOWN THE SCREEN AT A CONSTANT PACE
*/
void PowerUp::update()
{
	// MOVE THE POWER UP DOWN THE SCREEN
	shape.move(0, moveSpeed);
}

/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int PowerUp::type()
{
	return 0;
}

/*
	WILL DRAW THE CURRENT POPUP TO THE SCREEN
*/
void PowerUp::render(sf::RenderTarget *target)
{
	target->draw(shape);
}
/*
	USED TO GET THE POSITION OF THE CANNON
*/
const sf::Vector2f PowerUp::getPosition() const
{
	return this->shape.getPosition();
}

/*
	USED TO GET THE BOUNDS OF THE CANNON
*/
const sf::FloatRect PowerUp::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}


/*
	CONSTRUCTOR FOR THE GREEN POWER UP
*/
GreenPowerUp::GreenPowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Green);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int GreenPowerUp::type()
{
	return 0;
}

/*
	CONSTRUCTOR FOR THE WHITE POWER UP
*/
WhitePowerUp::WhitePowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::White);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int WhitePowerUp::type()
{
	return 1;
}

/*
	CONSTRUCTOR FOR THE GRAY POWER UP
*/
GrayPowerUp::GrayPowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(25);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color(0x5F5F5AFF)); // GRAY
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int GrayPowerUp::type()
{
	return 2;
}

/*
	CONSTRUCTOR FOR THE ORANGE POWER UP
*/
OrangePowerUp::OrangePowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color(0xFF9200FF)); // ORANGE
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int OrangePowerUp::type()
{
	return 3;
}

/*
	CONSTRUCTOR FOR THE YELLOW POWER UP
*/
YellowPowerUp::YellowPowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Yellow);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int YellowPowerUp::type()
{
	return 4;
}

/*
	CONSTRUCTOR FOR THE BLACK POWER UP
*/
BlackPowerUp::BlackPowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(0.5);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int BlackPowerUp::type()
{
	return 5;
}

/*
	CONSTRUCTOR FOR THE RED POWER UP
*/
RedPowerUp::RedPowerUp(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Red);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int RedPowerUp::type()
{
	return 6;
}

/*
	CONSTRUCTOR FOR THE YASHICHI
*/
Yashichi::Yashichi(sf::Vector2f spawnPos)
{
	// INTILISE THE SHAPE OF THE POWER UP AND THE COLOUR
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Blue);
}
/*
	WILL RETURN THE TYPE THAT THE CURRENT POPUP IS
*/
int Yashichi::type()
{
	return 7;
}
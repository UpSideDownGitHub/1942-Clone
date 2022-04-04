#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Input.h"
#include "Bullet.h"


#pragma once
class Player
{
public:
	// VARIABLES
	Input input;

	// BULLET SHOT
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> enemyBullets;

	float movementSpeed = 3;
	int secondsToNextShot = 1;

	bool shootingOne = true;
	bool shootingTwo = false;
	bool shootingThree = false;

	int lives = 3;

	// DODGING
	time_t startTimeForDodge;
	float dogeIFrames = 2000;
	int dodges = 3;
	bool takeDamage = true;
	
	// CONSTRUCTOR
	Player();

	//		METHODS
	void update(sf::RenderWindow *window);
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


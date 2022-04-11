#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Input.h"
#include "Bullet.h"
#include "Audio.h"


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

	//		METHODS
	void update(sf::RenderWindow *window, Audio *audio);
	void render(sf::RenderTarget *target);
	void shoot();

	void drawBullet(int num);
	void drawBullet2(int num);
	sf::RenderTarget *target;


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


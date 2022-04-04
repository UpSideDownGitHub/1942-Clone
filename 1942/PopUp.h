#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <iostream>

#pragma once
class PopUp
{
public:
	//CONSTRUCTORS
	PopUp(std::string text, sf::Vector2f spawnPostion, time_t spawnTime, float timeToSurvive);
	PopUp(sf::Vector2f spawnPosition, time_t spawnTime, float timeToSurvive, bool smallExplosion);

	//METHODS
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


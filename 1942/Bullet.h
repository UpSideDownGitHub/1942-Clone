#include <SFML/Graphics.hpp>

#pragma once
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


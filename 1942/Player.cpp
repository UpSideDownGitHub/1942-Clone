#include "Player.h"

/*
	CONSTRUCTOR FOR THE PLAYER CLASS
*/
Player::Player()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize({ 70,50 });
	this->shape.setOrigin({ 70/2 , 50/2 });
	this->shape.setPosition(280, 320);
	Xmax = 520;
	Xmin = 40;
	Ymax = 610;
	Ymin = 210;
	start = time(0);
	canShoot = true;
}

/*
	UPDATE ALL ELEMENTS OF THE PLAYER'S SHIP
*/
void Player::update(sf::RenderWindow *window)
{
	input.pollEvents(window);
	if (input.buttonPresses[0])
		movement.x -= movementSpeed;
	if (input.buttonPresses[1])
		movement.y += movementSpeed;
	if (input.buttonPresses[2])
		movement.y -= movementSpeed;
	if (input.buttonPresses[3])
		movement.x += movementSpeed;

	if (float(clock() - startTimeForDodge) / CLOCKS_PER_SEC * 1000 >= dogeIFrames)
	{
		takeDamage = true;
		shape.setFillColor(sf::Color::Green);
	}
	if (input.buttonPresses[5] && dodges-1 >= 0 && takeDamage)
	{
		// MAKE THE SHIP INVISABLE
		dodges--;
		takeDamage = false;
		startTimeForDodge = clock();
		shape.setFillColor(sf::Color::Cyan);
	}
		

	if (getPosition().x + movement.x < Xmax && getPosition().x + movement.x > Xmin)
	{
		shape.move(movement.x, 0);
	}
	if (getPosition().y + movement.y < Ymax && getPosition().y + movement.y > Ymin)
	{
		shape.move(0, movement.y);
	}
	movement = { 0,0 };

	if (input.buttonPresses[4])
	{
		if (canShoot)
		{
			canShoot = false;
			start = time(0);
			shoot();
		}
		else if (time(0) - start > secondsToNextShot)
		{
			start = start + secondsToNextShot;
			shoot();
		}
	}
	else if (!input.buttonPresses[4])
	{
		canShoot = true;
	}

	for (Bullet *bullet : bullets)
	{
		bullet->update();
	}
	for (Bullet *bullet : enemyBullets)
	{
		bullet->update();
	}

}

/*
	DRAW THE PLAYER TO THE SCREEN
*/
void Player::render(sf::RenderTarget *target)
{
	// PLAYER
	target->draw(this->shape);
	// BULLETS
	for (Bullet *bullet : bullets)
	{
		bullet->render(target);
	}
	for (Bullet *bullet : enemyBullets)
	{
		bullet->render(target);
	}
}

void Player::shoot()
{
	if (shootingThree)
	{
		// LARGE BULLET
		bullets.push_back(new Bullet(
			getPosition().x,	// X POSITION
			getPosition().y,	// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{120,15}));				// SIZE
	}
	else if (shootingTwo)
	{
		// MEDIUM BULLET
		bullets.push_back(new Bullet(
			getPosition().x,	// X POSITION
			getPosition().y,	// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{80,15}));				// SIZE
	}
	else if (shootingOne)
	{
		// REGULAR BULLET
		bullets.push_back( new Bullet (
			getPosition().x,		// X POSITION
			getPosition().y,		// Y POSITION
			6,						// SPEED
			true,					// PLAYER BULLET
			{30,15}));				// SIZE
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


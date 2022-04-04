#include "Bullet.h"

Bullet::Bullet(float pos_x, float pos_y, float movement_speed, bool player, sf::Vector2f size)
{
	this->shape.setSize(size);
	this->shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height);
	this->shape.setPosition(pos_x, pos_y);
	this->movementSpeed = movement_speed;
	this->player = player;
}

Bullet::Bullet(float pos_x, float pos_y, sf::Vector2f angleShot, float movement_speed)
{
	player = false;
	this->shape.setSize({ 5, 5 });
	this->shape.setOrigin({ 5 / 2, 5 / 2 });
	this->shape.setPosition(pos_x, pos_y);
	this->movementSpeed = movement_speed;
	angle = angleShot;
}

/*
	UPDATE FUNCTION OF THE BULLET (CALLED ONCE PER FRAME)
*/
void Bullet::update()
{
	if (player)
		this->shape.move(sf::Vector2f{ 0,-1 } *this->movementSpeed);
	else
		this->shape.move(angle * movementSpeed);
}

/*
	DRAW THE BULLET TO THE SCREEN
*/
void Bullet::render(sf::RenderTarget* target)
{
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
#include "PowerUp.h"
void PowerUp::update()
{
	// MOVE THE POWER UP DOWN THE SCREEN
	shape.move(0, moveSpeed);
}

int PowerUp::type()
{
	return 0;
}

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

GreenPowerUp::GreenPowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Green);
}

int GreenPowerUp::type()
{
	return 0;
}


WhitePowerUp::WhitePowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::White);
}
int WhitePowerUp::type()
{
	return 1;
}


GrayPowerUp::GrayPowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(25);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color(0x5F5F5AFF)); // GRAY
}
int GrayPowerUp::type()
{
	return 2;
}


OrangePowerUp::OrangePowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color(0xFF9200FF)); // ORANGE
}
int OrangePowerUp::type()
{
	return 3;
}


YellowPowerUp::YellowPowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Yellow);
}
int YellowPowerUp::type()
{
	return 4;
}

BlackPowerUp::BlackPowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(0.5);
}
int BlackPowerUp::type()
{
	return 5;
}

RedPowerUp::RedPowerUp(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Red);
}
int RedPowerUp::type()
{
	return 6;
}

Yashichi::Yashichi(sf::Vector2f spawnPos)
{
	shape.setRadius(20);
	shape.setOrigin({ 25 / 2, 25 / 2 });
	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Blue);
}
int Yashichi::type()
{
	return 7;
}
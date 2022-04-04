#include "PopUp.h"

PopUp::PopUp(std::string text, sf::Vector2f spawnPostion, time_t spawnTime, float timeToSurvive)
{
	arial.loadFromFile("Assets/arial.ttf");

	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	this->text.setString(text);
	this->text.setFont(arial);
	this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 2);
	this->text.setPosition(spawnPostion);


	this->spawnTime = spawnTime;
	this->timeToSurvive = timeToSurvive;
}

PopUp::PopUp(sf::Vector2f spawnPosition, time_t spawnTime, float timeToSurvive, bool smallExplosion)
{
	explosionEffect = true;
	// CREATE AN EXPLOSTION EFFECT
	if (smallExplosion)
	{
		shape.setRadius(10);
		shape.setPosition(spawnPosition);
		shape.setOrigin({ 10,10 });
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(4);
		shape.setPointCount(5);
	}
	else
	{
		shape.setRadius(15);
		shape.setPosition(spawnPosition);
		shape.setOrigin({ 20,20 });
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(5);
		shape.setPointCount(5);
	}


	this->spawnTime = spawnTime;
	this->timeToSurvive = timeToSurvive;
}


void PopUp::render(sf::RenderTarget *target)
{
	if (explosionEffect)
		target->draw(shape);
	else
		target->draw(text);
}
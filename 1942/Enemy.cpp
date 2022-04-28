#include "Enemy.h"
//#define TESTING
/*
	ENEMY CLASS METHODS
*/
Enemy::Enemy()
{
	shape.setPointCount(4);
	shape.setPoint(0, { 0,0 });
	shape.setPoint(1, { 10,0 });
	shape.setPoint(2, { 10,10 });
	shape.setPoint(3, { 0,10 });
	shape.setOrigin({ 20 / 2, 20 / 2 });
	shape.setPosition(10,10);
}
void Enemy::removeHealth()
{
	health -= 1;
	if (health <= 0)
	{
		die = true;
	}
}
void Enemy::update(Player *player)
{

}
void Enemy::render(sf::RenderTarget *target)
{
	target->draw(shape);
	target->draw(center);
}

int Enemy::type()
{
	return 0;
}

void Enemy::shoot(Player *player, float randomDeviation)
{
	sf::Vector2f curPos = shape.getPosition();
	sf::Vector2f position = player->getPosition();
	sf::Vector2f aimDir = position - curPos;
	aimDir.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	aimDir.y += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm,
		3));
}

/*
	USED TO GET THE POSITION OF THE CANNON
*/
const sf::Vector2f Enemy::getPosition() const
{
	return this->shape.getPosition();
}

/*
	USED TO GET THE BOUNDS OF THE CANNON
*/
const sf::FloatRect Enemy::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}



/*
	ZERO CLASS METHODS
*/
Zero::Zero(float xOffset, float yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, {  0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, {  8,10 });
	shape.setPoint(3, {  8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, {  7,32 });
	shape.setPoint(8, {  3,32 });
	shape.setPoint(9, {  0,28 });
	shape.setPoint(10, {-10,25 });
	shape.setPoint(11, {-10,20 });
	shape.setPoint(12, {  2,15 });
	shape.setPoint(13, {  2,10 });

	shape.setOrigin(5, 20);
	shape.setPosition(xOffset, yOffset);
	shape.setFillColor(sf::Color(23,115,60,255));

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getOrigin().x, shape.getOrigin().y);
	center.setFillColor(sf::Color::Red);
#endif
	maxVertSpeed = 2;
	verMoveSpeed = maxVertSpeed;
	horMoveSpeed = 0.6;
	rateOfChange = -0.05;
	distanceToPlayer = 150;
	startChange = false;
	stopChange = false;

	health = 1;
}
void Zero::update(Player *player)
{
	shape.move({ horMoveSpeed, verMoveSpeed });
#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif

	const float PI = 3.14159265;
	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);
	if (!stopChange)
	{
		if (!startChange && shape.getPosition().y > player->getPosition().y - distanceToPlayer)
			startChange = true;
		if (startChange)
		{
			if (verMoveSpeed < 0.6 && once && canShoot)
			{
				once = false;
				if (rand() % 3 == 0)
				{
					shoot(player, randomDeviation);
				}
			}
			verMoveSpeed += rateOfChange;
			if (verMoveSpeed <= -maxVertSpeed)
			{
				stopChange = true;
			}
		}
	}
}
int Zero::type()
{
	return 0;
}


/*
	BVD CLASS METHODS
*/
int BVD::type()
{
	return 1;
}
BVD::BVD(bool onLeft, int xOffset, int yOffset)
{
	int x = 3;
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f( 0*x,5*x ));
	shape.setPoint(1, sf::Vector2f(10 * x,5 * x ));
	shape.setPoint(2, sf::Vector2f(8 * x,10 * x ));
	shape.setPoint(3, sf::Vector2f(8 * x,15 * x ));
	shape.setPoint(4, sf::Vector2f(20 * x,20 * x ));
	shape.setPoint(5, sf::Vector2f(20 * x,25 * x ));
	shape.setPoint(6, sf::Vector2f(10 * x,28 * x ));
	shape.setPoint(7, sf::Vector2f(7 * x,32 * x ));
	shape.setPoint(8, sf::Vector2f(3 * x,32 * x ));
	shape.setPoint(9, sf::Vector2f(0 * x,28 * x ));
	shape.setPoint(10, sf::Vector2f(-10 * x,25 * x ));
	shape.setPoint(11, sf::Vector2f(-10 * x,20 * x ));
	shape.setPoint(12, sf::Vector2f(2 * x,15 * x ));
	shape.setPoint(13, sf::Vector2f(2 * x,10 * x ));

	shape.setOrigin(5*x, 20*x);
	shape.setPosition(560 - xOffset , yOffset);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	
	leftSide = onLeft;
	if (leftSide)
		shape.setPosition(xOffset, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1;

	moveDownDistance = 200;
	moveUpDistance = 125;
	distaneFromEdge = 150;

	health = 6;
}

void BVD::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}


	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
#ifdef TESTING
	center.move({ dx, dy });
#endif
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

	nextMove(player);

}

void BVD::nextMove(Player *player)
{
	if (down && end)
	{
		return;
	}
	if (up && shape.getPosition().y <= moveUpDistance)
	{
		decUp = true;

		end = true;
		if (leftSide)
			left = true;
		else
			right = true;
		return;
	}
	if (right && shape.getPosition().x >= 560 - distaneFromEdge)
	{
		decRight = true;

		if (end)
			down = true;
		else
			up = true;
		return;
	}
	if (left && shape.getPosition().x <= distaneFromEdge)
	{
		decLeft = true;

		if (end)
			down = true;
		else
			up = true;
		return;
	}
	if (shape.getPosition().y >= moveDownDistance && !doneturn)
	{
		decDown = true;

		//SHOOT BULLET TOWARDS THE PLAYER
		if (canShoot)
			shoot(player, randomDeviation);

		doneturn = true;
		if (leftSide)
			right = true;
		else
			left = true;
		return;
	}
}


/*
	DEIHIRYU CLASS METHODS
*/
int Daihiryu::type()
{
	return 2;
}
Daihiryu::Daihiryu(int xOffset, int yOffset)
{
	int x = 4;
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f(0 * x, 5 * x));
	shape.setPoint(1, sf::Vector2f(10 * x, 5 * x));
	shape.setPoint(2, sf::Vector2f(8 * x, 10 * x));
	shape.setPoint(3, sf::Vector2f(8 * x, 15 * x));
	shape.setPoint(4, sf::Vector2f(20 * x, 20 * x));
	shape.setPoint(5, sf::Vector2f(20 * x, 25 * x));
	shape.setPoint(6, sf::Vector2f(10 * x, 28 * x));
	shape.setPoint(7, sf::Vector2f(7 * x, 32 * x));
	shape.setPoint(8, sf::Vector2f(3 * x, 32 * x));
	shape.setPoint(9, sf::Vector2f(0 * x, 28 * x));
	shape.setPoint(10, sf::Vector2f(-10 * x, 25 * x));
	shape.setPoint(11, sf::Vector2f(-10 * x, 20 * x));
	shape.setPoint(12, sf::Vector2f(2 * x, 15 * x));
	shape.setPoint(13, sf::Vector2f(2 * x, 10 * x));

	shape.setFillColor(sf::Color(13, 74, 6, 255));
	shape.setOrigin(5 * x, 20 * x);
	shape.setPosition(xOffset, 640 + yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1;

	moveDownDistance = 200;
	moveUpDistance = 150;
	distaneFromEdge = 150;

	health = 15;
}
void Daihiryu::shoot(Player *player, float randomDeviation)
{
	sf::Vector2f curPos = this->shape.getPosition();
	sf::Vector2f position1 = curPos;
	sf::Vector2f position2;
	sf::Vector2f position3;

	// DOWN
	position1.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	position1.y += 10;

	if (player->getPosition().x > curPos.x)
	{
		// RIGHT
		position2 = curPos;
		position2.x += 10;
		position2.y += (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
		// DOWN AND RIGHT
		position3 = curPos;
		position3.x += 10 - randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
		position3.y += 10 - randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	}
	else
	{
		//LEFT
		position2 = curPos;
		position2.x -= 10;
		position2.y += (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
		// DOWN AND LEFT
		position3 = curPos;
		position3.x -= 10 - randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
		position3.y += 10 - randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	}
	sf::Vector2f aimDir1 = position1 - curPos;
	sf::Vector2f aimDir2 = position2 - curPos;
	sf::Vector2f aimDir3 = position3 - curPos;

	sf::Vector2f aimDirNorm1 = aimDir1 / sqrt(pow(aimDir1.x, 2) + pow(aimDir1.y, 2));
	sf::Vector2f aimDirNorm2 = aimDir2 / sqrt(pow(aimDir2.x, 2) + pow(aimDir2.y, 2));
	sf::Vector2f aimDirNorm3 = aimDir3 / sqrt(pow(aimDir3.x, 2) + pow(aimDir3.y, 2));

	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm1,
		3));
	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm2,
		3));
	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm3,
		3));
}
void Daihiryu::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			// SHOOT AT PLAYER
			if (canShoot)
				shoot(player, randomDeviation);

			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			// SHOOT AT PLAYER
			if (canShoot)
				shoot(player, randomDeviation);

			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			// SHOOT AT PLAYER
			if (canShoot)
				shoot(player, randomDeviation);

			decLeft = false;
			left = false;
		}
		else if (decRight)
		{
			// SHOOT AT PLAYER
			if (canShoot)
				shoot(player, randomDeviation);

			currentLoop++;
			decRight = false;
			right = false;
		}
	}
	
	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
#ifdef TESTING
	center.move({ dx, dy });
#endif
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

	nextMove(player);
}
void Daihiryu::nextMove(Player *player)
{
	if (shape.getPosition().y <= moveUpDistance && up && !end)
	{
		decUp = true;
		left = true;
		return;
	}
	if (shape.getPosition().x <= distaneFromEdge && left)
	{
		decLeft = true;
		down = true;
		return;
	}
	if (shape.getPosition().y >= moveDownDistance && down)
	{
		decDown = true;
		right = true;
		return;
	}
	// check if the final and stop ealier if it is
	if (currentLoop >= maxLoops)
	{
		if (shape.getPosition().x >= 250 && right)
		{

			decRight = true;
			up = true;
			end = true;
			return;
		}
	}
	else
	{
		if (shape.getPosition().x >= 560 - distaneFromEdge && right)
		{
			decRight = true;
			up = true;
			return;
		}
	}
}


/*
	AKAMIZU CLASS METHODS
*/
int Akamizu::type()
{
	return 3;
}
Akamizu::Akamizu(bool shipMovingLeft, int xOffset, int yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));

	if (!shipMovingLeft)
		shape.setPosition(560 - xOffset, yOffset);
	else
		shape.setPosition(xOffset, yOffset);


#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.03;
	movingLeft = shipMovingLeft;
	if (!movingLeft)
		left = true;
	else
		right = true;

	moveDownDistance = 250;
	moveUpDistance = 300;
	distaneFromEdge = 250;

	health = 1;
}

void Akamizu::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);
#ifdef TESTING
	center.move({ dx, dy });
#endif
	nextMove(player);
}

void Akamizu::nextMove(Player *player)
{
	/*
	RIGHT/LEFT
	LOOP
		DOWN,LEFT,UP,RIGHT / DOWN,RIGHT,UP,LEFT 
	*/
	if (movingLeft)
	{
		if (shape.getPosition().x >= 560 - distaneFromEdge && right && !end)
		{
			if (once&& rand() % 3 == 0 && canShoot)
			{
				shoot(player, randomDeviation);
			}
			once = false;
			decRight = true;
			down = true;
			return;
		}
		if (shape.getPosition().y >= moveDownDistance && down)
		{
			decDown = true;
			left = true;
			return;
		}
		if (shape.getPosition().x <= distaneFromEdge && left)
		{
			decLeft = true;
			up = true;
			return;
		}
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			decUp = true;
			right = true;
			end = true;
			return;
		}
	}
	else
	{
		if (shape.getPosition().x <= distaneFromEdge && left && !end)
		{
			if (once && rand() % 3 == 0 && canShoot)
			{
				shoot(player, randomDeviation);
			}
			once = false;
			decLeft = true;
			down = true;
			return;
		}
		if (shape.getPosition().y >= moveDownDistance && down)
		{
			decDown = true;
			right = true;
			return;
		}
		if (shape.getPosition().x >= 560 - distaneFromEdge && right)
		{
			decRight = true;
			up = true;
			return;
		}
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			decUp = true;
			left = true;
			end = true;
			return;
		}
	}
}


/*
	Raizan CLASS METHODS
*/
int Raizan::type()
{
	return 4;
}
Raizan::Raizan(int xOffset, int yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition(xOffset, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	maxHorSpeed = 2;
	verMoveSpeed = 2;
	horMoveSpeed = 0;
	rateOfChange = 0.05;
	distanceToPlayer = 250;
	startChange = false;
	stopChange = false;

	health = 1;
}

void Raizan::update(Player *player)
{
	shape.move({ horMoveSpeed, verMoveSpeed });
#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif

	const float PI = 3.14159265;
	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

	if (shape.getPosition().y > player->getPosition().y - shootDistance && once)
	{
		if (once && rand() % 2 == 0 && canShoot)
		{
			shoot(player, randomDeviation);
		}
		once = false;
	}

	if (!stopChange)
	{
		if (!startChange && shape.getPosition().y > player->getPosition().y - distanceToPlayer)
		{
			if (shape.getPosition().x <= player->getPosition().x)
				left = false;
			startChange = true;
			verMoveSpeed = 3;
		}
		if (startChange)
		{
			if (left)
				horMoveSpeed -= rateOfChange;
			else
				horMoveSpeed += rateOfChange;

			if (horMoveSpeed >= maxHorSpeed || horMoveSpeed <= -maxHorSpeed)
			{
				stopChange = true;
			}
		}
	}
}


/*
	RED CLASS METHODS
*/
int Red::type()
{
	return 5;
}
Red::Red(int num, int yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	if (num == 1)
		shape.setPosition(0, yOffset);
	if (num == 2)
		shape.setPosition(-50, yOffset);
	if (num == 3)
		shape.setPosition(-100, yOffset);
	if (num == 4)
		shape.setPosition(-150, yOffset);
	if (num == 5)
		shape.setPosition(-200, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.05;

	moveDownDistance = 150;
	moveUpDistance = 200;
	turnPos1 = 150;
	turnPos2 = 400;
	turnPos3 = 150;
	turnPos4 = 400;

	health = 1;
}

void Red::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			currentLoop++;
			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);
	
#ifdef TESTING
	center.move({ dx, dy });
#endif
	nextMove();
}

void Red::nextMove()
{
	if (!nextLoop)
	{
		if (shape.getPosition().x >= turnPos1 && right && !end)
		{
			decRight = true;
			down = true;
			return;
		}
	}
	else
	{
		if (shape.getPosition().x >= turnPos2 && right && !end)
		{
			decRight = true;
			down = true;
			return;
		}
	}
	if (shape.getPosition().y >= moveDownDistance && down)
	{
		decDown = true;
		left = true;
		return;
	}
	if (!nextLoop)
	{
		if (shape.getPosition().x <= turnPos3 && left)
		{
			decLeft = true;
			up = true;
			return;
		}
	}
	else
	{
		if (shape.getPosition().x <= turnPos4 && left)
		{
			decLeft = true;
			up = true;
			return;
		}
	}
	if (shape.getPosition().y <= moveUpDistance && up)
	{
		decUp = true;
		right = true;
		nextLoop = true;
		if (currentLoop == 1)
			end = true;
		return;
	}
}


/*
	SHORYU CLASS METHODS
*/
int Shoryu::type()
{
	return 6;
}
Shoryu::Shoryu(bool onLeft, int xOffset, int yOffset)
{
	int x = 3;
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f(0 * x, 5 * x));
	shape.setPoint(1, sf::Vector2f(10 * x, 5 * x));
	shape.setPoint(2, sf::Vector2f(8 * x, 10 * x));
	shape.setPoint(3, sf::Vector2f(8 * x, 15 * x));
	shape.setPoint(4, sf::Vector2f(20 * x, 20 * x));
	shape.setPoint(5, sf::Vector2f(20 * x, 25 * x));
	shape.setPoint(6, sf::Vector2f(10 * x, 28 * x));
	shape.setPoint(7, sf::Vector2f(7 * x, 32 * x));
	shape.setPoint(8, sf::Vector2f(3 * x, 32 * x));
	shape.setPoint(9, sf::Vector2f(0 * x, 28 * x));
	shape.setPoint(10, sf::Vector2f(-10 * x, 25 * x));
	shape.setPoint(11, sf::Vector2f(-10 * x, 20 * x));
	shape.setPoint(12, sf::Vector2f(2 * x, 15 * x));
	shape.setPoint(13, sf::Vector2f(2 * x, 10 * x));

	shape.setOrigin(5 * x, 20 * x);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition(560 - xOffset, yOffset);

	leftSide = onLeft;
	if (leftSide)
		shape.setPosition(xOffset, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1;

	moveDownDistance = 200;
	moveUpDistance = 125;
	distaneFromEdge = 150;

	health = 6;
}

void Shoryu::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

#ifdef TESTING
	center.move({ dx, dy });
#endif

	nextMove(player);

}

void Shoryu::nextMove(Player *player)
{
	if (down && end)
	{
		return;
	}
	if (up && shape.getPosition().y <= moveUpDistance)
	{
		decUp = true;

		end = true;
		if (leftSide)
			left = true;
		else
			right = true;
		return;
	}
	if (right && shape.getPosition().x >= 560 - distaneFromEdge)
	{
		decRight = true;

		if (end)
			down = true;
		else
			up = true;
		return;
	}
	if (left && shape.getPosition().x <= distaneFromEdge)
	{
		decLeft = true;

		if (end)
			down = true;
		else
			up = true;
		return;
	}
	if (shape.getPosition().y >= moveDownDistance && !doneturn)
	{
		decDown = true;
		//SHOOT BULLET TOWARDS THE PLAYER
		if (canShoot)
			shoot(player, randomDeviation);

		doneturn = true;
		if (leftSide)
			right = true;
		else
			left = true;
		return;
	}
}


/*
	BOUNSFIGHTER CLASS METHODS
*/
int BounsFighter::type()
{
	return 7;
}
BounsFighter::BounsFighter(bool left, int xOffset, int yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(217, 165, 46, 255));
	if (left)
	{
		moveLeft = true;
		shape.setPosition(560 + xOffset, 640 + yOffset);
		horMoveSpeed = -1;
	}
	else
	{
		moveLeft = false;
		shape.setPosition(-xOffset, 640 + yOffset);
		horMoveSpeed = 1;
	}

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif
	verMoveSpeed = -2;
	rateOfChange = 0.007;
	increaseInSpeed = -0.01;

	health = 1;
}

void BounsFighter::update(Player *player)
{
	shape.move({ horMoveSpeed, verMoveSpeed });

#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif

	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);
	verMoveSpeed += increaseInSpeed;
	if (moveLeft)
	{
		if (horMoveSpeed <= 0)
			horMoveSpeed += rateOfChange;
	}
	else
	{
		if (horMoveSpeed >= 0)
			horMoveSpeed -= rateOfChange;
	}
}

/*
	QING CLASS METHODS
*/
int Qing::type()
{
	return 8;
}
Qing::Qing(int xOffset, int yOffset)
{
	int x = 3;
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f(0 * x, 5 * x));
	shape.setPoint(1, sf::Vector2f(10 * x, 5 * x));
	shape.setPoint(2, sf::Vector2f(8 * x, 10 * x));
	shape.setPoint(3, sf::Vector2f(8 * x, 15 * x));
	shape.setPoint(4, sf::Vector2f(20 * x, 20 * x));
	shape.setPoint(5, sf::Vector2f(20 * x, 25 * x));
	shape.setPoint(6, sf::Vector2f(10 * x, 28 * x));
	shape.setPoint(7, sf::Vector2f(7 * x, 32 * x));
	shape.setPoint(8, sf::Vector2f(3 * x, 32 * x));
	shape.setPoint(9, sf::Vector2f(0 * x, 28 * x));
	shape.setPoint(10, sf::Vector2f(-10 * x, 25 * x));
	shape.setPoint(11, sf::Vector2f(-10 * x, 20 * x));
	shape.setPoint(12, sf::Vector2f(2 * x, 15 * x));
	shape.setPoint(13, sf::Vector2f(2 * x, 10 * x));

	shape.setOrigin(5 * x, 20 * x);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition(xOffset, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	verMoveSpeed = 1.5;

	health = 4;
}

void Qing::update(Player *player)
{
	shape.move({ 0, -verMoveSpeed });
#ifdef TESTING
	center.move({ 0, -verMoveSpeed });
#endif

	float dx = 0;
	float dy = -verMoveSpeed;
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);
}


/*
	FUKUSUKE CLASS METHODS
*/
int Fukusuke::type()
{
	return 9;
}
Fukusuke::Fukusuke(bool shipMovingLeft, int xOffset, int yOffset)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));

	if (!shipMovingLeft)
		shape.setPosition(560 - xOffset, yOffset);
	else
		shape.setPosition(xOffset, yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.07;
	movingLeft = shipMovingLeft;
	if (!movingLeft)
		left = true;
	else
		right = true;
	moveUpDistance = 300;
	turnPos1 = 150;
	turnPos2 = 150;

	health = 1;
}

void Fukusuke::update(Player *player)
{
	if (decDown || decUp)
	{
		if (verMoveSpeed >= 0)
		{
			verMoveSpeed -= rateOfChange;
		}
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	if (decLeft || decRight)
	{
		if (horMoveSpeed >= 0)
		{
			horMoveSpeed -= rateOfChange;
		}
		else if (decLeft)
		{
			decLeft = false;
			left = false;
			verMoveSpeed = 4;
			right = true;
			horMoveSpeed = 0.2;
		}
		else if (decRight)
		{
			decRight = false;
			right = false;
			verMoveSpeed = 4;
			left = true;
			horMoveSpeed = 0.2;
		}
	}

	float dx = 0;
	float dy = 0;
	if (down)
	{
		if (verMoveSpeed <= maxVerMoveSpeed && !decDown)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, verMoveSpeed });
		dy = verMoveSpeed;
	}
	if (left)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ -horMoveSpeed, 0 });
		dx = -horMoveSpeed;
	}
	if (right)
	{
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			horMoveSpeed += rateOfChange;
		}
		shape.move({ horMoveSpeed, 0 });
		dx = horMoveSpeed;
	}
	if (up)
	{
		if (verMoveSpeed <= maxVerMoveSpeed && !decUp)
		{
			verMoveSpeed += rateOfChange;
		}
		shape.move({ 0, -verMoveSpeed });
		dy = -verMoveSpeed;
	}
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

#ifdef TESTING
	center.move({ dx, dy });
#endif
	nextMove(player);
}

void Fukusuke::nextMove(Player *player)
{
	/*
	RIGHT/LEFT
	LOOP
		UP,LEFT,DOWN & RIGHT / UP,RIGHT,DOWN & LEFT
	*/
	if (movingLeft)
	{
		if (shape.getPosition().x >= turnPos1 && right && !end)
		{
			decRight = true;
			up = true;
			return;
		}
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			decUp = true;
			left = true;
			return;
		}
		if (shape.getPosition().x <= turnPos2 && left)
		{
			decLeft = true;
			down = true;
			end = true;
			if (once && canShoot)
				shoot(player, randomDeviation);
			once = false;
			return;
		}
	}
	else
	{
		if (shape.getPosition().x <= 560 - turnPos1 && left && !end)
		{
			decLeft = true;
			up = true;
			return;
		}
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			decUp = true;
			right = true;
			return;
		}
		if (shape.getPosition().x >= 560 - turnPos2 && right)
		{
			decRight = true;
			down = true;
			end = true;
			if (once && canShoot)
				shoot(player, randomDeviation);
			once = false;
			return;
		}
	}
}


/*
	RED2 CLASS METHODS
*/
int Red2::type()
{
	return 10;
}
Red2::Red2(int num)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	if (num == 1)
		shape.setPosition(-200, 100);
	if (num == 2)
		shape.setPosition(-100, 150);
	if (num == 3)
		shape.setPosition(0, 200);
	if (num == 4)
		shape.setPosition(-100, 250);
	if (num == 5)
		shape.setPosition(-200, 300);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	horMoveSpeed = 3;

	health = 1;
}

void Red2::update(Player *player)
{
	shape.move({ horMoveSpeed, 0 });
	float dx = horMoveSpeed;
	float dy = 0;
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

#ifdef TESTING
	center.move({ dx, dy });
#endif
}

/*
	RED3 CLASS METHODS
*/
int Red3::type()
{
	return 11;
}
Red3::Red3(int num)
{
	shape.setPointCount(14);
	shape.setPoint(0, { 0,5 });
	shape.setPoint(1, { 10,5 });
	shape.setPoint(2, { 8,10 });
	shape.setPoint(3, { 8,15 });
	shape.setPoint(4, { 20,20 });
	shape.setPoint(5, { 20,25 });
	shape.setPoint(6, { 10,28 });
	shape.setPoint(7, { 7,32 });
	shape.setPoint(8, { 3,32 });
	shape.setPoint(9, { 0,28 });
	shape.setPoint(10, { -10,25 });
	shape.setPoint(11, { -10,20 });
	shape.setPoint(12, { 2,15 });
	shape.setPoint(13, { 2,10 });

	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	if (num == 1)
		shape.setPosition(0, 50);
	if (num == 2)
		shape.setPosition(-50, 100);
	if (num == 3)
		shape.setPosition(-100, 150);
	if (num == 4)
		shape.setPosition(-150, 200);
	if (num == 5)
		shape.setPosition(-200, 250);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	horMoveSpeed = 3;

	health = 1;
}

void Red3::update(Player *player)
{
	shape.move({ horMoveSpeed, 0 });

	float dx = horMoveSpeed;
	float dy = 0;
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

#ifdef TESTING
	center.move({ dx, dy });
#endif
}

/*
	AYAKO CLASS METHODS
*/
int Ayako::type()
{
	return 12;
}
Ayako::Ayako()
{
	int x = 5;
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f(0 * x, -5 * x));
	shape.setPoint(1, sf::Vector2f(10 * x, -5 * x));
	shape.setPoint(2, sf::Vector2f(8 * x, 0 * x));
	shape.setPoint(3, sf::Vector2f(8 * x, 15 * x));
	shape.setPoint(4, sf::Vector2f(40 * x, 20 * x));
	shape.setPoint(5, sf::Vector2f(40 * x, 25 * x));
	shape.setPoint(6, sf::Vector2f(10 * x, 28 * x));
	shape.setPoint(7, sf::Vector2f(7 * x, 32 * x));
	shape.setPoint(8, sf::Vector2f(3 * x, 32 * x));
	shape.setPoint(9, sf::Vector2f(0 * x, 28 * x));
	shape.setPoint(10, sf::Vector2f(-30 * x, 25 * x));
	shape.setPoint(11, sf::Vector2f(-30 * x, 20 * x));
	shape.setPoint(12, sf::Vector2f(2 * x, 15 * x));
	shape.setPoint(13, sf::Vector2f(2 * x, 0 * x));

	shape.setOrigin(5 * x, 20 * x);
	shape.setFillColor(sf::Color(13, 74, 6, 255));
	shape.setPosition(280, 640);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	startTime1 = clock();
	startTime2 = clock() - 500;
	startTime3 = clock() - 1000;
	startTime4 = clock() - 1500;

	verMoveSpeed = -2;
	turnPos1 = 100;
	turnPos2 = 400;

	health = 40;
}
void Ayako::shoot(Player *player, float randomDeviation, sf::Vector2f spawnPos)
{
	sf::Vector2f curPos = spawnPos;
	sf::Vector2f position = player->getPosition();
	sf::Vector2f aimDir = position - curPos;
	aimDir.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	aimDir.y += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm,
		3));
}
void Ayako::update(Player *player)
{
	shape.move({ 0, verMoveSpeed });

#ifdef TESTING
	center.move({ 0, verMoveSpeed });
#endif

	float dx = 0;
	float dy = verMoveSpeed;
	const float PI = 3.14159265;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;
	shape.setRotation(rotation);

	nextMove();

	sf::Vector2f shootPoint1 = shape.getPosition(); // center (just postion)
	sf::Vector2f shootPoint2 = shootPoint1; // left wing
	shootPoint2.x -= 50;
	sf::Vector2f shootPoint3 = shootPoint1; // right wing
	shootPoint3.x += 50;
	sf::Vector2f shootPoint4 = shootPoint1; // tail
	shootPoint4.y += 50;

	if (float(clock() - startTime1) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		startTime1 = clock();
		shoot(player, randomDeviation, shootPoint1);
		shoot(player, randomDeviation - 100, shootPoint1);
		shoot(player, randomDeviation + 100, shootPoint1);
	}
	else if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		startTime2 = clock();
		shoot(player, randomDeviation, shootPoint2);
		shoot(player, randomDeviation - 100, shootPoint2);
		shoot(player, randomDeviation + 100, shootPoint2);
	}
	else if (float(clock() - startTime3) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		startTime3 = clock();
		shoot(player, randomDeviation, shootPoint3);
		shoot(player, randomDeviation - 100, shootPoint3);
		shoot(player, randomDeviation + 100, shootPoint3);
	}
	else if (float(clock() - startTime4) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		startTime4 = clock();
		shoot(player, randomDeviation, shootPoint4);
		shoot(player, randomDeviation - 100, shootPoint4);
		shoot(player, randomDeviation + 100, shootPoint4);
	}

}

void Ayako::nextMove()
{
	if (shape.getPosition().y <= turnPos1 && up)
	{
		up = false;
		down = true;
		verMoveSpeed = -verMoveSpeed;
		return;
	}
	if (shape.getPosition().y >= turnPos2 && down)
	{
		down = false;
		up = true;
		verMoveSpeed = -verMoveSpeed;
		return;
	}
}
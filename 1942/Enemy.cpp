/**
Program: 1942
Filename: Enemy.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File: Enemy.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Enemy.h"

//#define TESTING

/*
					ENEMY CLASS METHODS
*/
/*
	CONSTRUCTOR FOR THE BASE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Enemy::Enemy()
{
	// CREATE A NEW SHAPE
	shape.setPointCount(4);
	// SET THE VERTEXES OF THE SHAPE
	shape.setPoint(0, { 0,0 });
	shape.setPoint(1, { 10,0 });
	shape.setPoint(2, { 10,10 });
	shape.setPoint(3, { 0,10 });
	// SET THE ORGIN / POSITION OF THE SHAPE
	shape.setOrigin({ 20 / 2, 20 / 2 });
	shape.setPosition(10,10);

	// SET THE DEFAULT VALUE OF THE PLAYERS HEALTH
	health = 1;
}

/*
	REMOVE HEALTH FROM THE ENEMY AND IF THE HEALTH IS LESS THAN 0 THEN DESTROY THE ENEMY
*/
void Enemy::removeHealth()
{
	// TAKE 1 OF THE HEALTH OF THE ENEMY
	health -= 1;
	// IF THE HEALTH IS LESS THAN 0
	if (health <= 0)
	{
		// SET DIE TO BE TRUE
		die = true;
	}
}

/*
	UPDATE FUNCTION FOR THE ENEMY
*/
void Enemy::update(Player *player)
{

}

/*
	RENDER FUNCTION WILL HANDLE DRAWING ALL COMPONENTS OF THE ENEMY TO THE SCREEN
*/
void Enemy::render(sf::RenderTarget *target)
{
	// DRAW THE SHAPE AND CENTER TO THE RENDER TARGET
	target->draw(shape);
	target->draw(center);	// FOR TESTING
}

/*
	RETURNS THE TYPE OF ENEMY (VIRTUAL FUNCTION THAT IS OVERIDDEN BY THE ENEMY SUBCLASSES)
*/
int Enemy::type()
{
	return 0;
}

/*
	SHOOT FUNCTION WILL FIRE A BULLET TOWARDS THE PLAYER ADDING SOME RANDOM DEVIATION TO THE SHOT
*/
void Enemy::shoot(Player *player, float randomDeviation)
{
	// GET THE CURRENT POSITION OF THE ENEMY AND THE PLAYER TO CALCULATE THE AIM DIRECTION
	sf::Vector2f curPos = shape.getPosition();
	sf::Vector2f position = player->getPosition();
	sf::Vector2f aimDir = position - curPos;

	// ADD RANDOM DEVIATION TO THE SHOT
	aimDir.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	aimDir.y += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));

	// CALCULATE THE NORMAL OF THE AIM DIRECTION
	sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

	// INSTANTINATE A BULLET ADDING IT TO THE ENEMY BULLETS VECTOR WITH THE CURRENT POSITION
	// AND THE AIM DIRECTION JUST CALCULATED AND A SPEED OF 3
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
/*
	CONSTRUCTOR FOR THE ZERO CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Zero::Zero(float xOffset, float yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setPosition(xOffset, yOffset);
	shape.setFillColor(sf::Color(23,115,60,255));

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getOrigin().x, shape.getOrigin().y);
	center.setFillColor(sf::Color::Red);
#endif
	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	maxVertSpeed = 2;
	verMoveSpeed = maxVertSpeed;
	horMoveSpeed = 0.6f;
	rateOfChange = -0.05f;
	distanceToPlayer = 150;
	startChange = false;
	stopChange = false;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE ZERO SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Zero::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ horMoveSpeed, verMoveSpeed });
#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif
	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);
	// IF STLLL CHANIGN THE DIRECTION OF THE PLANE
	if (!stopChange)
	{
		// IF NOT STARTED YET AND THE PLANE HAS GOT CLOSE ENOUGH THE THE PLAYER
		if (!startChange && shape.getPosition().y > player->getPosition().y - distanceToPlayer)
		{
			// START CHANING THE PLANES DIRECTION
			startChange = true;
		}
		// IF CAN START CHAING THE PLANES DIRECTION
		if (startChange)
		{
			// IF THE VERTICAL MOVMENT SPEED IS CLOSE TO 0 AND NOT SHOT YET
			if (verMoveSpeed < 0.6 && once && canShoot)
			{
				// SET ONCE TO FALSE SO THE PLANE DOES NOT SHOOT AGAIN
				once = false;
				// 1 IN 3 CHANCE TO SHOOT A BULLET
				if (rand() % 3 == 0)
				{
					// SHOOT A BULLET WITH player AS THE TARGET AND RANDOM DEVIATION OF randomDeviation
					shoot(player, randomDeviation);
				}
			}
			// INCREASE THE VERTICAL MOVEMENT SPEED BY THE RATE OF CHANGE OF DIRECTION
			verMoveSpeed += rateOfChange;
			// IF THE VERTICAL MOVEMENT SPEED HAS REACHED THE MAXIMUM VALUE
			if (verMoveSpeed <= -maxVertSpeed)
			{
				// STOP CHANIGN THE SPEED AND JUST MOVE AND ROTATE THE ENEMY
				stopChange = true;
			}
		}
	}
}
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Zero::type()
{
	return 0;
}


/*
					BVD CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int BVD::type()
{
	return 1;
}
/*
	CONSTRUCTOR FOR THE BVD CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
BVD::BVD(bool onLeft, int xOffset, int yOffset)
{
	// SIZE MULTIPLIER
	int x = 3;
	// CREATE CUSTOM SHIP SHAPE
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f((float) 0*x, (float)5*x ));
	shape.setPoint(1, sf::Vector2f((float)10 * x, (float)5 * x ));
	shape.setPoint(2, sf::Vector2f((float)8 * x, (float)10 * x ));
	shape.setPoint(3, sf::Vector2f((float)8 * x, (float)15 * x ));
	shape.setPoint(4, sf::Vector2f((float)20 * x, (float)20 * x ));
	shape.setPoint(5, sf::Vector2f((float)20 * x, (float)25 * x ));
	shape.setPoint(6, sf::Vector2f((float)10 * x, (float)28 * x ));
	shape.setPoint(7, sf::Vector2f((float)7 * x, (float)32 * x ));
	shape.setPoint(8, sf::Vector2f((float)3 * x, (float)32 * x ));
	shape.setPoint(9, sf::Vector2f((float)0 * x, (float)28 * x ));
	shape.setPoint(10, sf::Vector2f((float)-10 * x, (float)25 * x ));
	shape.setPoint(11, sf::Vector2f((float)-10 * x, (float)20 * x ));
	shape.setPoint(12, sf::Vector2f((float)2 * x, (float)15 * x ));
	shape.setPoint(13, sf::Vector2f((float)2 * x, (float)10 * x ));

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin((float)5*x, (float)20*x);
	shape.setPosition((float)560 - xOffset , (float)yOffset);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	
#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif
	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	leftSide = onLeft;
	if (leftSide)
		shape.setPosition((float)xOffset, (float)yOffset);

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1f;

	moveDownDistance = 200;
	moveUpDistance = 125;
	distaneFromEdge = 150;

	// SET THE HEALTH
	health = 6;
}
/*
	UPDATE FUNCTION WILL HANDLE MOVING THE BVD SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void BVD::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;
	
	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxVerMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxVerMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLAYER SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove(player);

}

/*
	METHOD CALCULATES IF THE SHIP NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void BVD::nextMove(Player *player)
{
	// IF THE PLANE IS MOVING DOWN AND AT THE END OF PATTERN
	if (down && end)
	{
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING UP AND MAXIMUM POSITION IS REACHED
	if (up && shape.getPosition().y <= moveUpDistance)
	{
		// SET DEACREASE UP & END TO TRUE
		decUp = true;
		end = true;

		// IF THE PLANE IS ON THE LEFT SIDE OF THE PLAYABLE AREA
		if (leftSide)
		{
			// SET LEFT TO TRUE
			left = true;
		}
		else
		{
			// SET RIGHT TO TRUE
			right = true;
		}
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING RIGHT AND MAXIMUM POSITION IS REACHED
	if (right && shape.getPosition().x >= 560 - distaneFromEdge)
	{
		// SET DECREASE RIGHT TO TRUE
		decRight = true;

		// IF THE END IS REACHED
		if (end)
		{
			// SET DOWN TO TRUE
			down = true;
		}
		else
		{
			// SET UP TO TRUE
			up = true;
		}
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING LEFT AND THE MAXIMUM POSITION IS REACHED
	if (left && shape.getPosition().x <= distaneFromEdge)
	{
		// SET DECREASE LEFT TO TRUE
		decLeft = true;

		// IF THE END IS REACHED
		if (end)
		{
			// SET DOWN TO TRUE
			down = true;
		}
		else
		{
			// SET UP TO TRUE
			up = true;
		}
		// RETURN
		return;
	}
	// IF MOVING DOWN AND THE MAXIUMUM IS REACHED AND NOT DONE A TURN YET
	if (shape.getPosition().y >= moveDownDistance && !doneturn)
	{
		// SET DECREASE DOWN TO TRUE
		decDown = true;

		// IF SHOOT BULLET TOWARDS THE PLAYER THEN SHOOT BULLET
		if (canShoot)
		{
			shoot(player, randomDeviation);
		}

		// SET DONE TURN TO TRUE
		doneturn = true;
		// IF ON THE LEFT SIDE OF THE PLAYABLE AREA
		if (leftSide)
		{
			// SET RIGHT TO TRUE
			right = true;
		}
		else
		{
			// SET LEFT TO TRUE
			left = true;
		}
		// RETURN
		return;
	}
}


/*
	DEIHIRYU CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Daihiryu::type()
{
	return 2;
}
/*
	CONSTRUCTOR FOR THE DAIHIRYU CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Daihiryu::Daihiryu(int xOffset, int yOffset)
{
	// SIZE MULTIPLIER
	int x = 4;
	// CREATE CUSTOM SHIP SHAPE
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f((float)0 * x, (float)5 * x));
	shape.setPoint(1, sf::Vector2f((float)10 * x, (float)5 * x));
	shape.setPoint(2, sf::Vector2f((float)8 * x, (float)10 * x));
	shape.setPoint(3, sf::Vector2f((float)8 * x, (float)15 * x));
	shape.setPoint(4, sf::Vector2f((float)20 * x, (float)20 * x));
	shape.setPoint(5, sf::Vector2f((float)20 * x, (float)25 * x));
	shape.setPoint(6, sf::Vector2f((float)10 * x, (float)28 * x));
	shape.setPoint(7, sf::Vector2f((float)7 * x, (float)32 * x));
	shape.setPoint(8, sf::Vector2f((float)3 * x, (float)32 * x));
	shape.setPoint(9, sf::Vector2f((float)0 * x, (float)28 * x));
	shape.setPoint(10, sf::Vector2f((float)-10 * x, (float)25 * x));
	shape.setPoint(11, sf::Vector2f((float)-10 * x, (float)20 * x));
	shape.setPoint(12, sf::Vector2f((float)2 * x, (float)15 * x));
	shape.setPoint(13, sf::Vector2f((float)2 * x, (float)10 * x));

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setFillColor(sf::Color(13, 74, 6, 255));
	shape.setOrigin((float)5 * x, (float)20 * x);
	shape.setPosition((float)xOffset, (float)640 + yOffset);

#if defined(TESTING)
	center.setSize({ (float)10, (float)10 });
	center.setOrigin({ (float)5,(float)5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif
	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1f;

	moveDownDistance = 200;
	moveUpDistance = 150;
	distaneFromEdge = 150;

	// SET THE HEALTH
	health = 15;
}

/*
	THE SHOOT FUNCTION WILL HANDEL SHOOTING BULLETS TOWARDS THE PLAYER
*/
void Daihiryu::shoot(Player *player, float randomDeviation)
{
	// GET THE CURRENT POSITION OF THE ENEMY AND THE PLAYER
	sf::Vector2f curPos = this->shape.getPosition();
	sf::Vector2f position1 = curPos;
	sf::Vector2f position2;
	sf::Vector2f position3;

	// DOWN
	position1.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	position1.y += 10;

	// IF THE PLAYER IS TO THE RIGHT OF THE ENEMY
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
	// THE PLAYER IS TO THE LEFT OF THE ENEMY
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
	// CALCULATE EACH THE 3 AIM DIRECTIONS
	sf::Vector2f aimDir1 = position1 - curPos;
	sf::Vector2f aimDir2 = position2 - curPos;
	sf::Vector2f aimDir3 = position3 - curPos;

	// CALCULATE THE NORMALISED VALUE FOR EACH OF THE AIM DIRECTIONS
	sf::Vector2f aimDirNorm1 = aimDir1 / sqrt(pow(aimDir1.x, 2) + pow(aimDir1.y, 2));
	sf::Vector2f aimDirNorm2 = aimDir2 / sqrt(pow(aimDir2.x, 2) + pow(aimDir2.y, 2));
	sf::Vector2f aimDirNorm3 = aimDir3 / sqrt(pow(aimDir3.x, 2) + pow(aimDir3.y, 2));

	// CREATE 3 ENEMY BULLETS FOR EACH OF THE DIFFRENT AIM DIRECTIONS AND ADD
	// THEM TO THE ENEMY BULLETS VECTOR
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

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE DAIHIRYU SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Daihiryu::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			// IF CAN SHOOT AT PLAYER
			if (canShoot)
			{
				// SHOOT AT THE PLAYER
				shoot(player, randomDeviation);
			}
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			// IF CAN SHOOT AT PLAYER
			if (canShoot)
			{
				// SHOOT AT THE PLAYER
				shoot(player, randomDeviation);
			}
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			// IF CAN SHOOT AT PLAYER
			if (canShoot)
			{
				// SHOOT AT THE PLAYER
				shoot(player, randomDeviation);
			}

			decLeft = false;
			left = false;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			// IF CAN SHOOT AT PLAYER
			if (canShoot)
			{
				// SHOOT AT THE PLAYER
				shoot(player, randomDeviation);
			}

			// INCREASE THE CURRENT LOOP BY 1
			currentLoop++;
			decRight = false;
			right = false;
		}
	}
	
	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;

	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLANE SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove(player);
}

/*
	METHOD CALCULATES IF THE PLANE NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Daihiryu::nextMove(Player *player)
{
	// THE ENEMYS Y POSITION IS LESS THAN MAXIMUM AND MOVING UPWARDS AND NOT AT THE END
	if (shape.getPosition().y <= moveUpDistance && up && !end)
	{
		// SET DECREASE UP & LEFT TO TRUE AND RETURN
		decUp = true;
		left = true;
		return;
	}
	// IF THE ENEMYS X POSITION IS LESS THAN MAXIUMUM AND MOVING LEFT
	if (shape.getPosition().x <= distaneFromEdge && left)
	{
		// SET DECREASE LEFT AND DOWN TO TRUE AND RETURN
		decLeft = true;
		down = true;
		return;
	}
	// IF THE ENEMYS Y POSITION IS GREATER THAN THE MAXIMUM AND MOVING DOWN
	if (shape.getPosition().y >= moveDownDistance && down)
	{
		// SET DECREASE DOWN AND RIGHT TO TRUE AND RETURN
		decDown = true;
		right = true;
		return;
	}
	// CHECK IF THE FINAL AND STOP EALIER IF IT IS
	if (currentLoop >= maxLoops)
	{
		// IF THE ENEMYS X POSITION IS GREATER THAN 350 AND MOVING RIGHT
		if (shape.getPosition().x >= 250 && right)
		{
			// SET DEREASE RIGHT, UP, END TO TRUE AND RETURN
			decRight = true;
			up = true;
			end = true;
			return;
		}
	}
	// ELSE IF THERE ARE MORE LOOPS TO DO
	else
	{
		// IF THE ENEMYS X POSITION IS GREATER THAN MAXDISTANCE AND MOVING RIGHT
		if (shape.getPosition().x >= 560 - distaneFromEdge && right)
		{
			// SET DEACREASING RIGHT AND UP TO TRUE AND RETURN
			decRight = true;
			up = true;
			return;
		}
	}
}


/*
	AKAMIZU CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Akamizu::type()
{
	return 3;
}

/*
	CONSTRUCTOR FOR THE AKAMIZU CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Akamizu::Akamizu(bool shipMovingLeft, int xOffset, int yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin((float)5, (float)20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	if (!shipMovingLeft)
		shape.setPosition((float)560 - xOffset, (float)yOffset);
	else
		shape.setPosition((float)xOffset, (float)yOffset);

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.03f;
	movingLeft = shipMovingLeft;
	if (!movingLeft)
		left = true;
	else
		right = true;

	moveDownDistance = 250;
	moveUpDistance = 300;
	distaneFromEdge = 250;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE AKAMIZU SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Akamizu::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;

	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif
	
	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLAYER SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove(player);
}

/*
	METHOD CALCULATES IF THE SHIP NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Akamizu::nextMove(Player *player)
{
	/*
	RIGHT/LEFT
	LOOP
		DOWN,LEFT,UP,RIGHT / DOWN,RIGHT,UP,LEFT 
	*/
	// IF THE PLANE IS MOVING LEFT
	if (movingLeft)
	{
		// IF THE PLANES X POSITION IS GREATER THAN THE MAX AND MOVING RIGHT AND NOT 
		// AT THE END
		if (shape.getPosition().x >= 560 - distaneFromEdge && right && !end)
		{
			// IF FIRST TIME AND 1 IN 3 CHANCE AND CAN SHOOT THE PLAYER
			if (once&& rand() % 3 == 0 && canShoot)
			{
				// SHOOT THE PLAYER
				shoot(player, randomDeviation);
			}
			// SET ONCE TO FALSE
			once = false;
			// SET DECREASE RIGHT AND DOWN TO TRUE THEN RETURN
			decRight = true;
			down = true;
			return;
		}
		// IF THE PLANES Y POSITION IS GREATER THAN THE MAX AND MOVING DOWN
		if (shape.getPosition().y >= moveDownDistance && down)
		{
			// SET DECREASE DOWN AND LEFT TO TRUE THEN RETURN
			decDown = true;
			left = true;
			return;
		}
		// IF THE PLANES X IS LESS THAN THE MIN AND MOVIGN LEFT 
		if (shape.getPosition().x <= distaneFromEdge && left)
		{
			// SET DECREASE LEFT AND UP TO TRUE THEN RETURN
			decLeft = true;
			up = true;
			return;
		}
		// IF THE PLANES Y IS LESS THAN THE MIN AND MOVING UP
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			// SET DECREASE UP RIGHT AND END TO TRUE THEN RETURN
			decUp = true;
			right = true;
			end = true;
			return;
		}
	}
	// THE PLANE IS MOVING RIGHT
	else
	{
		// IF THE PLANES X POSITION IS LESS THAN THE MIN AND MOVING LEFT AND NOT THE END
		if (shape.getPosition().x <= distaneFromEdge && left && !end)
		{
			// IF FIRST TIME AND 1 IN 3 CHANCE AND CAN SHOOT
			if (once && rand() % 3 == 0 && canShoot)
			{
				// SHOOT A BULLET TOWARDS THE PLAYER
				shoot(player, randomDeviation);
			}
			// SET ONCE TO FALSE
			once = false;
			// SET DECREASE LEFT AND DOWN TO TRUE THEN RETURN
			decLeft = true;
			down = true;
			return;
		}
		// IF THE PLANES Y POSITION IS GREATER THAN THE MAX AND MOVING DOWN
		if (shape.getPosition().y >= moveDownDistance && down)
		{
			// SET DECREASEING DOWN AND RIGHT TO TRUE THEN RETURN
			decDown = true;
			right = true;
			return;
		}
		// IF THE PLANES X POSITION IS GREATER THAN THE MAX AND MOVING RIGHT
		if (shape.getPosition().x >= 560 - distaneFromEdge && right)
		{
			// SET DECREASE RIGHT AND UP TO TRUE AND RETURN
			decRight = true;
			up = true;
			return;
		}
		// IF THE PLANES Y POSITION IS LESS THAN THE MIN AND MOVING UP
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			// SET DECREAS UP AND LEFT AND END TO TRUE THEN RETURN
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
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Raizan::type()
{
	return 4;
}
/*
	CONSTRUCTOR FOR THE RAIZAN CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Raizan::Raizan(int xOffset, int yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition((float)xOffset, (float)yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	maxHorSpeed = 2;
	verMoveSpeed = 2;
	horMoveSpeed = 0;
	rateOfChange = 0.05f;
	distanceToPlayer = 250;
	startChange = false;
	stopChange = false;

	left = true;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE RAIZAN SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Raizan::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ horMoveSpeed, verMoveSpeed });
#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// IF THE PLANES Y POSUTION IS GREATER THAN MAX (DEPENDENT IN THE PLAYER) AND FIRST TIME
	if (shape.getPosition().y > player->getPosition().y - shootDistance && once)
	{
		// IF FIRST TIME AND 1 IN 2 CHANGE AND CAN SHOOT
		if (once && rand() % 2 == 0 && canShoot)
		{
			// FIRE ABULLET IN THE DIRECTION OF THE PLAYER
			shoot(player, randomDeviation);
		}
		// SET ONCE TO FALSE
		once = false;
	}

	// IF STLLL CHANIGN THE DIRECTION OF THE PLANE
	if (!stopChange)
	{
		// IF NOT STARTED YET AND THE PLANE HAS GOT CLOSE ENOUGH THE THE PLAYER
		if (!startChange && shape.getPosition().y > player->getPosition().y - distanceToPlayer)
		{
			// IF THE ENEMY IS ON THE RIGHT OF THE PLAYER
			if (shape.getPosition().x <= player->getPosition().x)
			{
				// SET LEFT TO TRUE
				left = false;
			}
			// SET START CHANGE TO TRUE AND SET THE INITIAL SPEED TO 3
			startChange = true;
			verMoveSpeed = 3;
		}
		// IF CHANGING DIRECTION
		if (startChange)
		{
			// IF MOVING LEFT
			if (left)
			{
				// DECREASE HORIZONTAL MOVEMENT SPEED
				horMoveSpeed -= rateOfChange;
			}
			else
			{
				// INCREASE HORZONTAL MOVMENT SPEED
				horMoveSpeed += rateOfChange;
			}

			// IF THE HORIZONTAL MOVEMENT SPEED IS GREATER THAN THE MAX
			if (horMoveSpeed >= maxHorSpeed || horMoveSpeed <= -maxHorSpeed)
			{
				// STOP CHANIGN THE HORIZONTAL MOVEMENT SPEED
				stopChange = true;
			}
		}
	}
}


/*
	RED CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Red::type()
{
	return 5;
}
/*
	CONSTRUCTOR FOR THE RED CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Red::Red(int num, int yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	// SET THE POSITION OF THE PLANE DEPENDENT ON THE NUMBER IN THE LIST
	if (num == 1)
		shape.setPosition((float)0, (float)yOffset);
	if (num == 2)
		shape.setPosition((float)-50, (float)yOffset);
	if (num == 3)
		shape.setPosition((float)-100, (float)yOffset);
	if (num == 4)
		shape.setPosition((float)-150, (float)yOffset);
	if (num == 5)
		shape.setPosition((float)-200, (float)yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.05f;

	moveDownDistance = 150;
	moveUpDistance = 200;
	turnPos1 = 150;
	turnPos2 = 400;
	turnPos3 = 150;
	turnPos4 = 400;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE RED SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Red::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			currentLoop++;
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;

	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);
	
	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLAYER SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove();
}

/*
	METHOD CALCULATES IF THE SHIP NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Red::nextMove()
{
	// IF THERE IS NOT ANOTHER LOOP
	if (!nextLoop)
	{
		// IF THE PLANES X POSITION IS GREATER THAN MAX AND MOVING RIGHT AND NOT AT THE END
		if (shape.getPosition().x >= turnPos1 && right && !end)
		{
			// SET DECREASE RIGHT AND DOWN TO TRUE AND REUTRN
			decRight = true;
			down = true;
			return;
		}
	}
	// MORE LOOPS
	else
	{
		// IF THE PLANES X POSITION IS GREATER THAN MAX AND MOVING RIGHT AND NOT AT END
		if (shape.getPosition().x >= turnPos2 && right && !end)
		{
			// SET DECREASE RIGHT AND DOWN TO TRUE THEN RETURN
			decRight = true;
			down = true;
			return;
		}
	}
	// IF THE PLANES Y POSITION IS GREATER THAN THE MAX AND MOVING DOWN
	if (shape.getPosition().y >= moveDownDistance && down)
	{
		// SET DECREASING DOWN AND LEFT TO TRUE THEN RETURN
		decDown = true;
		left = true;
		return;
	}
	// IF NO MORE LOOPS
	if (!nextLoop)
	{
		// IF PLANES X POSITION IS LESS THAN MIN AND MOVING LEFT 
		if (shape.getPosition().x <= turnPos3 && left)
		{
			// SET DECREASE LEFT AND UP TO TRUE THEN RETURN
			decLeft = true;
			up = true;
			return;
		}
	}
	// MORE LOOPS LEFT
	else
	{
		// IF PLANES X POSITION IS LESS THAN MIN AND MOVING LEFT
		if (shape.getPosition().x <= turnPos4 && left)
		{
			// SET DECREASE LEFT AND UP TO TRUE THEN RETURN
			decLeft = true;
			up = true;
			return;
		}
	}
	// IF THE PLANES Y POSITION IS LESS THAN MIN AND MOVING UP
	if (shape.getPosition().y <= moveUpDistance && up)
	{
		// SET DECREASE UP AND RIGHT AND NEXTLOOP TO TRUE
		decUp = true;
		right = true;
		nextLoop = true;
		// IF THE CURRENT IS EUQAL TO MAX THEN SET END TO TRUE
		if (currentLoop == 1)
		{
			end = true;
		}
		// RETURN
		return;
	}
}


/*
	SHORYU CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Shoryu::type()
{
	return 6;
}
/*
	CONSTRUCTOR FOR THE SHORYU CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Shoryu::Shoryu(bool onLeft, int xOffset, int yOffset)
{
	// SIZE MULTIPLIER
	int x = 3;
	// CREATE CUSTOM SHIP SHAPE
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f((float)0 * x, (float)5 * x));
	shape.setPoint(1, sf::Vector2f((float)10 * x, (float)5 * x));
	shape.setPoint(2, sf::Vector2f((float)8 * x, (float)10 * x));
	shape.setPoint(3, sf::Vector2f((float)8 * x, (float)15 * x));
	shape.setPoint(4, sf::Vector2f((float)20 * x, (float)20 * x));
	shape.setPoint(5, sf::Vector2f((float)20 * x, (float)25 * x));
	shape.setPoint(6, sf::Vector2f((float)10 * x, (float)28 * x));
	shape.setPoint(7, sf::Vector2f((float)7 * x, (float)32 * x));
	shape.setPoint(8, sf::Vector2f((float)3 * x, (float)32 * x));
	shape.setPoint(9, sf::Vector2f((float)0 * x, (float)28 * x));
	shape.setPoint(10, sf::Vector2f((float)-10 * x, (float)25 * x));
	shape.setPoint(11, sf::Vector2f((float)-10 * x, (float)20 * x));
	shape.setPoint(12, sf::Vector2f((float)2 * x, (float)15 * x));
	shape.setPoint(13, sf::Vector2f((float)2 * x, (float)10 * x));

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin((float)5 * x, (float)20 * x);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition((float)560 - xOffset, (float)yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	leftSide = onLeft;
	if (leftSide)
		shape.setPosition((float)xOffset, (float)yOffset);

	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = 0;
	verMoveSpeed = maxVerMoveSpeed;
	rateOfChange = 0.1f;

	moveDownDistance = 200;
	moveUpDistance = 125;
	distaneFromEdge = 150;

	// SET THE HEALTH
	health = 6;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE SHORYU SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Shoryu::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			decLeft = false;
			left = false;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			decRight = false;
			right = false;
		}
	}

	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;

	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxHorMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxHorMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLAYER SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove(player);
}

/*
	METHOD CALCULATES IF THE SHIP NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Shoryu::nextMove(Player *player)
{
	// IF THE PLANE IS MOVING DOWN AND AT THE END OF PATTERN
	if (down && end)
	{
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING UP AND MAXIMUM POSITION IS REACHED
	if (up && shape.getPosition().y <= moveUpDistance)
	{
		// SET DEACREASE UP & END TO TRUE
		decUp = true;
		end = true;

		// IF THE PLANE IS ON THE LEFT SIDE OF THE PLAYABLE AREA
		if (leftSide)
		{
			// SET LEFT TO TRUE
			left = true;
		}
		else
		{
			// SET RIGHT TO TRUE
			right = true;
		}
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING RIGHT AND MAXIMUM POSITION IS REACHED
	if (right && shape.getPosition().x >= 560 - distaneFromEdge)
	{
		// SET DECREASE RIGHT TO TRUE
		decRight = true;

		// IF THE END IS REACHED
		if (end)
		{
			// SET DOWN TO TRUE
			down = true;
		}
		else
		{
			// SET UP TO TRUE
			up = true;
		}
		// RETURN
		return;
	}
	// IF THE PLANE IS MOVING LEFT AND THE MAXIMUM POSITION IS REACHED
	if (left && shape.getPosition().x <= distaneFromEdge)
	{
		// SET DECREASE LEFT TO TRUE
		decLeft = true;

		// IF THE END IS REACHED
		if (end)
		{
			// SET DOWN TO TRUE
			down = true;
		}
		else
		{
			// SET UP TO TRUE
			up = true;
		}
		// RETURN
		return;
	}
	// IF MOVING DOWN AND THE MAXIUMUM IS REACHED AND NOT DONE A TURN YET
	if (shape.getPosition().y >= moveDownDistance && !doneturn)
	{
		// SET DECREASE DOWN TO TRUE
		decDown = true;

		// IF SHOOT BULLET TOWARDS THE PLAYER THEN SHOOT BULLET
		if (canShoot)
		{
			shoot(player, randomDeviation);
		}

		// SET DONE TURN TO TRUE
		doneturn = true;
		// IF ON THE LEFT SIDE OF THE PLAYABLE AREA
		if (leftSide)
		{
			// SET RIGHT TO TRUE
			right = true;
		}
		else
		{
			// SET LEFT TO TRUE
			left = true;
		}
		// RETURN
		return;
	}
}


/*
	BOUNSFIGHTER CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int BounsFighter::type()
{
	return 7;
}
/*
	CONSTRUCTOR FOR THE BONUSFIGHTER CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
BounsFighter::BounsFighter(bool left, int xOffset, int yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(217, 165, 46, 255));

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	if (left)
	{
		moveLeft = true;
		shape.setPosition((float)560 + xOffset, (float)640 + yOffset);
		horMoveSpeed = -1;
	}
	else
	{
		moveLeft = false;
		shape.setPosition((float)-xOffset, (float)640 + yOffset);
		horMoveSpeed = 1;
	}

	verMoveSpeed = -2;
	rateOfChange = 0.007f;
	increaseInSpeed = -0.01f;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE DAIHIRYU SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void BounsFighter::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ horMoveSpeed, verMoveSpeed });

#ifdef TESTING
	center.move({ horMoveSpeed, verMoveSpeed });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	float dx = horMoveSpeed;
	float dy = verMoveSpeed;
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// INCREASE THE VERTICAL SPEED OF THE PLANE
	verMoveSpeed += increaseInSpeed;

	// IF MOVING LEFT
	if (moveLeft)
	{
		// IF THE HORIZONTAL MOVE SPEED IS LESS THAN 0
		if (horMoveSpeed <= 0)
		{
			// INCREASE THE HORIZONTAL MOVMENT SPEED
			horMoveSpeed += rateOfChange;
		}
	}
	// MOVING RIGHT
	else
	{
		// IF THE HORIZONTAL MOVE SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed -= rateOfChange;
		}
	}
}

/*
	QING CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Qing::type()
{
	return 8;
}
/*
	CONSTRUCTOR FOR THE QING CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Qing::Qing(int xOffset, int yOffset)
{
	// SIZE MULTIPLIER
	int x = 3;
	// CREATE CUSTOM SHIP SHAPE
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f((float)0 * x, (float)5 * x));
	shape.setPoint(1, sf::Vector2f((float)10 * x, (float)5 * x));
	shape.setPoint(2, sf::Vector2f((float)8 * x, (float)10 * x));
	shape.setPoint(3, sf::Vector2f((float)8 * x, (float)15 * x));
	shape.setPoint(4, sf::Vector2f((float)20 * x, (float)20 * x));
	shape.setPoint(5, sf::Vector2f((float)20 * x, (float)25 * x));
	shape.setPoint(6, sf::Vector2f((float)10 * x, (float)28 * x));
	shape.setPoint(7, sf::Vector2f((float)7 * x, (float)32 * x));
	shape.setPoint(8, sf::Vector2f((float)3 * x, (float)32 * x));
	shape.setPoint(9, sf::Vector2f((float)0 * x, (float)28 * x));
	shape.setPoint(10, sf::Vector2f((float)-10 * x, (float)25 * x));
	shape.setPoint(11, sf::Vector2f((float)-10 * x, (float)20 * x));
	shape.setPoint(12, sf::Vector2f((float)2 * x, (float)15 * x));
	shape.setPoint(13, sf::Vector2f((float)2 * x, (float)10 * x));

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin((float)5 * x, (float)20 * x);
	shape.setFillColor(sf::Color(23, 115, 60, 255));
	shape.setPosition((float)xOffset, (float)yOffset);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	verMoveSpeed = 1.5;

	// SET THE HEALTH
	health = 4;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE QING SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Qing::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ 0, -verMoveSpeed });
#ifdef TESTING
	center.move({ 0, -verMoveSpeed });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	float dx = 0;
	float dy = -verMoveSpeed;
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);
}


/*
	FUKUSUKE CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Fukusuke::type()
{
	return 9;
}
/*
	CONSTRUCTOR FOR THE FUKUSUKE CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Fukusuke::Fukusuke(bool shipMovingLeft, int xOffset, int yOffset)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color(23, 115, 60, 255));

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Green);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	if (!shipMovingLeft)
		shape.setPosition((float)560 - xOffset, (float)yOffset);
	else
		shape.setPosition((float)xOffset, (float)yOffset);
	maxHorMoveSpeed = 3;
	maxVerMoveSpeed = 3;
	horMoveSpeed = maxVerMoveSpeed;
	verMoveSpeed = 0;
	rateOfChange = 0.07f;
	movingLeft = shipMovingLeft;
	if (!movingLeft)
		left = true;
	else
		right = true;
	moveUpDistance = 300;
	turnPos1 = 150;
	turnPos2 = 150;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE FUKUSUKE SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Fukusuke::update(Player *player)
{
	// IF THE PLANE IS DECREASING DOWN OR UP (SLOWING DOWN VERTICALLY)
	if (decDown || decUp)
	{
		// IF THE VERTICAL MOVEMENT SPEED IS GREATER THAN 0
		if (verMoveSpeed >= 0)
		{
			// DECREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed -= rateOfChange;
		}
		// IF DECREASEING DOWN THEN STOP MOVING DOWN
		else if (decDown)
		{
			decDown = false;
			down = false;
		}
		// IF DECREASING UP STOP MOVING UP
		else if (decUp)
		{
			decUp = false;
			up = false;
		}
	}
	// IF THE PLANE IS DECREASING LEFT OR RIGHT (SLOWING DOWN HORISZONTALLY)
	if (decLeft || decRight)
	{
		// IF THE HORIZONTAL SPEED IS GREATER THAN 0
		if (horMoveSpeed >= 0)
		{
			// DECREASE THE HORIZONTAL SPEED
			horMoveSpeed -= rateOfChange;
		}
		// IF DECREASING LEFT THEN STOP MOVING LEFT
		else if (decLeft)
		{
			decLeft = false;
			left = false;
			verMoveSpeed = 4;
			right = true;
			horMoveSpeed = 0.2f;
		}
		// IF DECREASING RIGHT THEN STOP MOVING RIGHT
		else if (decRight)
		{
			decRight = false;
			right = false;
			verMoveSpeed = 4;
			left = true;
			horMoveSpeed = 0.2f;
		}
	}

	// VALUES TO CALCULATE THE ROTATION OF THE SHIP
	float dx = 0;
	float dy = 0;

	// IF THE PLANE IS MOVING DOWN CURRENTLY
	if (down)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING DOWN
		if (verMoveSpeed <= maxVerMoveSpeed && !decDown)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE VERTICAL MOVEMENT SPEED
		shape.move({ 0, verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE VERTICAL MOVEMENT SPEED
		dy = verMoveSpeed;
	}
	// IF THE PLANE IS MOVING LEFT CURRENTLY
	if (left)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING LEFT
		if (horMoveSpeed <= maxHorMoveSpeed && !decLeft)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -HORIZONTAL MOVEMENT SPEED
		shape.move({ -horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE -HORIZONTAL MOVEMENT SPEED
		dx = -horMoveSpeed;
	}
	// IF THE PLANE IS MOVING RIGHT CURRENTLY
	if (right)
	{
		// IF THE HORIZONTAL SPEED IS LESS THAN THE MAX AND NOT DECREASING RIGHT
		if (horMoveSpeed <= maxHorMoveSpeed && !decRight)
		{
			// INCREASE THE HORIZONTAL MOVEMENT SPEED
			horMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE HORIZONTAL MOVEMENT SPEED
		shape.move({ horMoveSpeed, 0 });
		// SET THE X COMPONENT OF THE ROTATION TO THE HORIZONTAL MOVEMENT SPEED
		dx = horMoveSpeed;
	}
	// IF THE PLANE IS MOVING UP CURRENTLY
	if (up)
	{
		// IF THE VERTICAL SPEED IS LESS THAN THE MAX AND NOT DECREASING UP
		if (verMoveSpeed <= maxVerMoveSpeed && !decUp)
		{
			// INCREASE THE VERTICAL MOVEMENT SPEED
			verMoveSpeed += rateOfChange;
		}
		// MOVE THE SHAPE BY THE -VERTICAL MOVEMENT SPEED
		shape.move({ 0, -verMoveSpeed });
		// SET THE Y COMPONENT OF THE ROTATION TO THE -VERTICAL MOVEMENT SPEED
		dy = -verMoveSpeed;
	}

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLAYER SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove(player);
}


/*
	METHOD CALCULATES IF THE SHIP NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Fukusuke::nextMove(Player *player)
{
	/*
	RIGHT/LEFT
	LOOP
		UP,LEFT,DOWN & RIGHT / UP,RIGHT,DOWN & LEFT
	*/
	// IF MOVING LEFT
	if (movingLeft)
	{
		// IF THE PLANES X POSITION IS GREATER THAN THE MAX AND MOVING RIGHT AND NOT THE END
		if (shape.getPosition().x >= turnPos1 && right && !end)
		{
			// SET DEACREASE UP & UP TO TRUE THEN RETURN
			decRight = true;
			up = true;
			return;
		}
		// IF THE PLANES Y POSITION IS LESS THAN THE MIN AND MOVING UP
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			// SET DECREASE UP AND LEFT TO TRUE THEN RETURN
			decUp = true;
			left = true;
			return;
		}
		// IF THE PLANES X POSITION IS LESS THAN MIN AND MING LEFT
		if (shape.getPosition().x <= turnPos2 && left)
		{
			// SET DECREASE LEFT AND DOWN AND END TO TRUE
			decLeft = true;
			down = true;
			end = true;
			// IF FIRST TIME AND CAN SHOOT
			if (once && canShoot)
			{
				// FIRE A BULLET TOWARDS THE PLAYER
				shoot(player, randomDeviation);
			}
			// SET ONCE TO FALSE AND RETURN
			once = false;
			return;
		}
	}
	// MOVING RIGHT
	else
	{
		// IF THE PLANES X POSITION IS LESS THAN MIN AND MOVING LEFT AND NOT AT END
		if (shape.getPosition().x <= 560 - turnPos1 && left && !end)
		{
			// SET DECREASE LEFT AND UP TO TRUE THEN RETURN
			decLeft = true;
			up = true;
			return;
		}
		// IF THE PLANES Y POSITION IS LESS THAN MIN AND MOVING UP
		if (shape.getPosition().y <= moveUpDistance && up)
		{
			// SET DECREASE UP AND RIGHT TO TRUE THEN RETURN 
			decUp = true;
			right = true;
			return;
		}
		// IF THE PLAYERS X POSITION IS MORE THAN MAX AND MOVING RIGHT
		if (shape.getPosition().x >= 560 - turnPos2 && right)
		{
			// SET DECREASE TIGHT AND DOWN AND END TO TRUE
			decRight = true;
			down = true;
			end = true;
			// IF FIRST TIME AND CAN SHOOT
			if (once && canShoot)
			{
				// FIRE A BULLET TOWARDS THE PLAYER
				shoot(player, randomDeviation);
			}
			// SET ONCE TO FALSE AND RETURN
			once = false;
			return;
		}
	}
}


/*
	RED2 CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Red2::type()
{
	return 10;
}
/*
	CONSTRUCTOR FOR THE RED2 CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Red2::Red2(int num)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	// SET THE POSITION BASED ON THE ORDER OF SPAWN
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

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	horMoveSpeed = 3;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE RED2 SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Red2::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ horMoveSpeed, 0 });

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	float dx = horMoveSpeed;
	float dy = 0;
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);
}

/*
	RED3 CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Red3::type()
{
	return 11;
}
/*
	CONSTRUCTOR FOR THE RED3 CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Red3::Red3(int num)
{
	// CREATE CUSTOM SHIP SHAPE
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

	// SET THE ORIGIN / COLOUR OF THE SHIP
	shape.setOrigin(5, 20);
	shape.setFillColor(sf::Color::Red);

	// SET THE POSITION BASED ON THE ORDER OF SPAWN
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

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	horMoveSpeed = 3;

	// SET THE HEALTH
	health = 1;
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE RED3 SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Red3::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ horMoveSpeed, 0 });

#ifdef TESTING
	center.move({ dx, dy });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	float dx = horMoveSpeed;
	float dy = 0;
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);
}

/*
	AYAKO CLASS METHODS
*/
/*
	REUTRN THE TYPE (INT) THAT THIS ENEMY IS
*/
int Ayako::type()
{
	return 12;
}
/*
	CONSTRUCTOR FOR THE RED2 CLASS WHICH EXTENDS THE ENEMY CLASS (USED TO INITALISE ALL OF THE VARIABLES)
*/
Ayako::Ayako()
{
	// SIZE MULTIPLIER
	int x = 5;
	// CREATE CUSTOM SHIP SHAPE
	shape.setPointCount(14);
	shape.setPoint(0, sf::Vector2f((float)0 * x, (float)-5 * x));
	shape.setPoint(1, sf::Vector2f((float)10 * x, (float)-5 * x));
	shape.setPoint(2, sf::Vector2f((float)8 * x, (float)0 * x));
	shape.setPoint(3, sf::Vector2f((float)8 * x, (float)15 * x));
	shape.setPoint(4, sf::Vector2f((float)40 * x, (float)20 * x));
	shape.setPoint(5, sf::Vector2f((float)40 * x, (float)25 * x));
	shape.setPoint(6, sf::Vector2f((float)10 * x, (float)28 * x));
	shape.setPoint(7, sf::Vector2f((float)7 * x, (float)32 * x));
	shape.setPoint(8, sf::Vector2f((float)3 * x, (float)32 * x));
	shape.setPoint(9, sf::Vector2f((float)0 * x, (float)28 * x));
	shape.setPoint(10, sf::Vector2f((float)-30 * x, (float)25 * x));
	shape.setPoint(11, sf::Vector2f((float)-30 * x, (float)20 * x));
	shape.setPoint(12, sf::Vector2f((float)2 * x, (float)15 * x));
	shape.setPoint(13, sf::Vector2f((float)2 * x, (float)0 * x));

	// SET THE ORIGIN / POSITION / COLOUR OF THE SHIP
	shape.setOrigin((float)5 * x, (float)20 * x);
	shape.setFillColor(sf::Color(13, 74, 6, 255));
	shape.setPosition((float)280, (float)640);

#if defined(TESTING)
	center.setSize({ 10, 10 });
	center.setOrigin({ 5,5 });
	center.setPosition(shape.getPosition().x, shape.getPosition().y);
	center.setFillColor(sf::Color::Red);
#endif

	// SET ALL OF THE DEFAULT MOVEMENT VARIABLES TO THERE VALUES
	startTime1 = clock();
	startTime2 = clock() - (time_t)500;
	startTime3 = clock() - (time_t)1000;
	startTime4 = clock() - (time_t)1500;

	verMoveSpeed = -2;
	turnPos1 = 100;
	turnPos2 = 400;

	// SET THE HEALTH
	health = 40;
}

/*
	THE SHOOT FUNCTION WILL HANDEL SHOOTING BULLETS TOWARDS THE PLAYER
*/
void Ayako::shoot(Player *player, float randomDeviation, sf::Vector2f spawnPos)
{
	// GET THE CURRENT POSITION OF THE ENEMY AND THE PLAYER
	sf::Vector2f curPos = spawnPos;
	sf::Vector2f position = player->getPosition();
	sf::Vector2f aimDir = position - curPos;

	// ADD RANDOM DEVIATION TO THE SHOT
	aimDir.x += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));
	aimDir.y += -randomDeviation + (float(rand()) / float((RAND_MAX)) * (randomDeviation * 2));

	// CALCULATE THE NORMAL OF THE AIM DIRECTION
	sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

	// INSTANTINATE A BULLET ADDING IT TO THE ENEMY BULLETS VECTOR WITH THE CURRENT POSITION
	// AND THE AIM DIRECTION JUST CALCULATED AND A SPEED OF 3
	player->enemyBullets.push_back(new Bullet(curPos.x,
		curPos.y,
		aimDirNorm,
		3));
}

/*
	UPDATE FUNCTION WILL HANDLE MOVING THE AYAKO SHIP AND ROTATING IT TO FACE THE DIRECITON
	IT IS CURRENTLY MOVING IN
*/
void Ayako::update(Player *player)
{
	// MOVE THE SHIP BY THE HORIZONTAL MOVEMENT SPEED AND BY THE VERTICAL MOVEMENT SPEED
	shape.move({ 0, verMoveSpeed });

#ifdef TESTING
	center.move({ 0, verMoveSpeed });
#endif

	// CALCULATE THE ANGLE TO FACE TO BE ROTATING THE IN THE DIRECTION THAT ARE CURRENTLY MOVING IN
	float dx = 0;
	float dy = verMoveSpeed;
	const float PI = 3.14159265f;
	float rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	// SET THE ROTATION OF THE PLANE TO BE THE CALCULATED ROTATION
	shape.setRotation(rotation);

	// CALL THE NEXT MOVE METHOD TO CALCUALTE OF THE PLANE SHOULD TURN LEFT/RIGHT/UP/DOWN OR DO NOTHING
	nextMove();


	// CENTER
	sf::Vector2f shootPoint1 = shape.getPosition(); 
	// LEFT WING
	sf::Vector2f shootPoint2 = shootPoint1; 
	shootPoint2.x -= 50;
	// RIGHT WING
	sf::Vector2f shootPoint3 = shootPoint1;
	shootPoint3.x += 50;
	// TAIL
	sf::Vector2f shootPoint4 = shootPoint1; 
	shootPoint4.y += 50;

	// IF ENOUGH TIME HAS PASSED TO SHOOT AOUT OF FIRE POINT 1 AGAIN
	if (float(clock() - startTime1) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		// RESTART TIMER
		startTime1 = clock();
		// FIRE 3 BULLETS WITH SLIGHTLY DIFFRENT OFFSETS TOWARDS THE PLAYER
		shoot(player, randomDeviation, shootPoint1);
		shoot(player, randomDeviation - 100, shootPoint1);
		shoot(player, randomDeviation + 100, shootPoint1);
	}
	// IF ENOUGH TIME HAS PASSED TO SHOOT AOUT OF FIRE POINT 2 AGAIN
	else if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		// RESTART TIMER
		startTime2 = clock();
		// FIRE 3 BULLETS WITH SLIGHTLY DIFFRENT OFFSETS TOWARDS THE PLAYER
		shoot(player, randomDeviation, shootPoint2);
		shoot(player, randomDeviation - 100, shootPoint2);
		shoot(player, randomDeviation + 100, shootPoint2);
	}
	// IF ENOUGH TIME HAS PASSED TO SHOOT AOUT OF FIRE POINT 3 AGAIN
	else if (float(clock() - startTime3) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		// RESTART TIMER
		startTime3 = clock();
		// FIRE 3 BULLETS WITH SLIGHTLY DIFFRENT OFFSETS TOWARDS THE PLAYER
		shoot(player, randomDeviation, shootPoint3);
		shoot(player, randomDeviation - 100, shootPoint3);
		shoot(player, randomDeviation + 100, shootPoint3);
	}
	// IF ENOUGH TIME HAS PASSED TO SHOOT AOUT OF FIRE POINT 4 AGAIN
	else if (float(clock() - startTime4) / CLOCKS_PER_SEC * 1000 >= timeToWait && canShoot)
	{
		// RESTART TIMER
		startTime4 = clock();
		// FIRE 3 BULLETS WITH SLIGHTLY DIFFRENT OFFSETS TOWARDS THE PLAYER
		shoot(player, randomDeviation, shootPoint4);
		shoot(player, randomDeviation - 100, shootPoint4);
		shoot(player, randomDeviation + 100, shootPoint4);
	}

}

/*
	METHOD CALCULATES IF THE PLANE NEEDS TO CHANGE DIRECTION DEPENDNT ON THE CURRENT
	POSITION OF THE ENEMY
*/
void Ayako::nextMove()
{
	// IF THE PLANES Y POSITION IS LESS THAN THE MIN AND MOVING UP
	if (shape.getPosition().y <= turnPos1 && up)
	{
		// SET UP TO FALSE AND DOWN TO TRUE
		up = false;
		down = true;
		// DECREASE VERTICAL MOVEMENT SPEED 
		verMoveSpeed = -verMoveSpeed;
		// RETURN
		return;
	}
	// IF THE PLANES Y POSITION IS GREATER THAN THE MAX AND MOVING DOWN
	if (shape.getPosition().y >= turnPos2 && down)
	{
		// SET DOWN TO FALSE AND UP TO TRUE
		down = false;
		up = true;
		// INCREASE THE VERTICAL MOVEMENT SPEED
		verMoveSpeed = -verMoveSpeed;
		// RETURN
		return;
	}
}
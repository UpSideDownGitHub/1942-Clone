#include "StartScreens.h"

/*
	CONSTRUCTOR FOR "StartScreens" CLASS
*/
StartScreens::StartScreens()
{
	// CALL "initGUI()"
	initGUI();
}

/*
	THIS METHOD CHECKS IF THE BUTTONS IN THE MAIN MENU'S HAVE BEEN PRESSED
*/
bool StartScreens::checkButtonPress(sf::RenderWindow* win)
{
	if (doOnce)
	{
		doOnce = false;
		startTime = clock();
	}
	if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
	{
		input.pollEvents(win);
		if (input.spacePressed)
		{
			doOnce = true;
			return true;
		}
		return false;
	}
	return false;
}

/*
	RENDER METHODS FOR "StartScreens" CLASS THAT HANDLES DRAWING EACH ELEMENT TO THE SCREEN
*/
void StartScreens::render(sf::RenderTarget* target)
{
	target->draw(highScoreLabel);
	target->draw(highScoreText);
	target->draw(gameNameText);
	target->draw(insertCoinText);
	target->draw(copyrightText);	
}

/*
	INILISES THE GUI OF THE MAIN MENU'S
*/
void StartScreens::initGUI()
{
	// LOAD THE FONT
	arial.loadFromFile("Assets/arial.ttf");

	//			MENU 1
	// HIGHSCORE
	highScoreLabel.setCharacterSize(30);
	highScoreLabel.setPosition({ 220, 5 });
	highScoreLabel.setFont(arial);
	highScoreLabel.setString("High-Score");

	saveData.loadFile();
	int highScore = saveData.getHighScore();

	ssHighscore.str("");
	ssHighscore << highScore;

	highScoreText.setCharacterSize(20);
	highScoreText.setPosition({ 290, 55 });
	highScoreText.setFont(arial);
	highScoreText.setString(ssHighscore.str());
	highScoreText.setOrigin(highScoreText.getLocalBounds().width / 2, highScoreText.getLocalBounds().height / 2);


	// GAME NAME
	gameNameText.setCharacterSize(175);
	gameNameText.setPosition({ 80,120 });
	gameNameText.setFont(arial);
	gameNameText.setString("1942");


	// INSERT COIN
	insertCoinText.setCharacterSize(50);
	insertCoinText.setPosition({ 160,350 });
	insertCoinText.setFont(arial);
	insertCoinText.setString("Insert Coin");


	// COPYRIGHT
	copyrightText.setCharacterSize(20);
	copyrightText.setPosition({ 190,600});
	copyrightText.setFont(arial);
	copyrightText.setString("© 2022 Reuben Miller");
	/*
	highScoreLabel
	highScoreText
	ssHighscore
	gameNameText
	insertCoinText
	copyrightText
	*/
}
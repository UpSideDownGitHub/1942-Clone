/*
Program: 1942
Filename: HighScoreScreen.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: HighScoreScreen.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "HighScoreScreen.h"

/*
	CONSTRUCTOR FOR "HighScoreScreen" CLASS
*/
HighScoreScreen::HighScoreScreen()
{
	// INITIALISE CLOCKS
	startTime = clock();
	startTime2 = clock();
	
	// INITALISE THE GUI
	initGUI();
}

/*
	INITILISES THE HIGHSCORE SCREEN TO SHOW THE CORRECT INFORMATION FOR THE CORREECT GAME MODE
*/
void HighScoreScreen::initilise(int score, int lives)
{
	close = false;
	// LOAD THE SAVE DATA
	saveData.loadFile();
	SaveData::PlayerInfo* leaderboard;
	// SET WHICH GAME MODE HAS BEEN USED THEN FETCH THE LEADERBOARD FOR THAT GAMEMODE
	if (endless)
	{
		leaderboard = saveData.getLeaderboardEndless();
	}
	else if (noPowerUps)
	{
		leaderboard = saveData.getLeaderboardNoPowerUps();
	}
	else if (insane)
	{
		leaderboard = saveData.getLeaderboardInsane();
	}
	else if (random)
	{
		leaderboard = saveData.getLeaderboardRandom();
	}
	else
	{
		leaderboard = saveData.getLeaderboard();
	}
	
	// FOR EACH POSITION IN THE LEADERBAORD
	for (int i = 0; i < 5; i++)
	{
		// IF THE CURRENT SCORE IS HIGHER THAN THE POSITION IN THE LEADERBOARD
		if (leaderboard[i].Score < score)
		{
			// UPDATE THE LEADERBOARD TO SHOW THIS NEW SCORE
			currentSelectScoreToChange = i;
			// MOVE ALL OTHER OBEJCTS DOWN IN THE LEADERBOARD TO ALLOW FOR THE NEW ITEM
			for (int j = 4; j > i; j--)
			{
				leaderboard[j] = leaderboard[j - 1];
			}
			// UPDATE THE NEW LEADERBOARD ITEM TO SHOW THE NEW SCORE
			leaderboard[i].Score = score;
			leaderboard[i].LivesUsed = lives;
			leaderboard[i].Name = "";
			break;
		}
	}

	currentCharacters = 0;

	//			LEADERBOARD UI
	// POS 1
	ssTopName.str("");
	ssTopName << leaderboard[0].Name;
	topName.setString(ssTopName.str());
	ssTopScore.str("");
	ssTopScore << leaderboard[0].Score;
	topScore.setString(ssTopScore.str());
	ssTopLives.str("");
	ssTopLives << leaderboard[0].LivesUsed;
	topLives.setString(ssTopLives.str());
	// POS 2
	ssSecondName.str("");
	ssSecondName << leaderboard[1].Name;
	secondName.setString(ssSecondName.str());
	ssSecondScore.str("");
	ssSecondScore << leaderboard[1].Score;
	secondScore.setString(ssSecondScore.str());
	ssSecondLives.str("");
	ssSecondLives << leaderboard[1].LivesUsed;
	secondLives.setString(ssSecondLives.str());
	// POS 3
	ssThirdName.str("");
	ssThirdName << leaderboard[2].Name;
	thirdName.setString(ssThirdName.str());
	ssThirdScore.str("");
	ssThirdScore << leaderboard[2].Score;
	thirdScore.setString(ssThirdScore.str());
	ssThirdLives.str("");
	ssThirdLives << leaderboard[2].LivesUsed;
	thirdLives.setString(ssThirdLives.str());
	// POS 4
	ssForthName.str("");
	ssForthName << leaderboard[3].Name;
	forthName.setString(ssForthName.str());
	ssForthScore.str("");
	ssForthScore << leaderboard[3].Score;
	forthScore.setString(ssForthScore.str());
	ssForthLives.str("");
	ssForthLives << leaderboard[3].LivesUsed;
	forthLives.setString(ssForthLives.str());
	// POS 5
	ssFithName.str("");
	ssFithName << leaderboard[4].Name;
	fithName.setString(ssFithName.str());
	ssFithScore.str("");
	ssFithScore << leaderboard[4].Score;
	fithScore.setString(ssFithScore.str());
	ssFithLives.str("");
	ssFithLives << leaderboard[4].LivesUsed;
	fithLives.setString(ssFithLives.str());
	
	// SAVE THE SAVE DATA WITH THE NEW EDITIED LEADERBOARD
	saveData.saveFile();
}

/*
	THIS METHOD WILL CHECK FOR INPUT AND THEN CHANGE THE BUTTON SELECTED
*/
void HighScoreScreen::update(sf::RenderWindow* win)
{
	// CHECK FOR INPUT USING THE INPUT CLASS
	input.pollEvents(win);

	// IF ENOUGH TIME HAS PASSED TO PRESS ANOTHER BUTTON
	if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
	{
		// LEFT
		if (input.buttonPresses[0])
		{
			// RESET CLOCK
			startTime = clock();
			// IF CAN MOVE THE CURRENTLY SELECTED LEFT
			if (currentlySelected != 0 && currentlySelected != 10 && currentlySelected != 20)
			{
				// MOVE CURRENTLY SELECTED LEFT
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected--;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
		// DOWN
		else if (input.buttonPresses[1])
		{
			// RESET CLOCK
			startTime = clock();
			// IF CAN MOVE THE CURRENTLY SELECTED DOWN FIRST LAYER
			if (currentlySelected >= 0 && currentlySelected <= 9)
			{
				// MOVE CURRENTLY SELECTED DOWN FIRST LAYER
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected += 10;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
			// IF CAN MOVE THE CURRENTLY SELECTED DOWN SECOND LAYER
			else if (currentlySelected >= 12 && currentlySelected <= 17)
			{
				// MOVE CURRENTLY SELECTED DOWN SECOND LAYER
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected += 8;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
		// UP
		else if (input.buttonPresses[2])
		{
			// RESET CLOCK
			startTime = clock();
			// IF CAN MOVE THE CURRENTLY SELECTED UP FIRST LAYER
			if (currentlySelected >= 10 && currentlySelected <= 19)
			{
				// MOVE CURRENTLY SELECTED DOWN FIRST LAYER
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected -= 10;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
			// IF CAN MOVE THE CURRENTLY SELECTED UP SECOND LAYER
			else if (currentlySelected >= 20 && currentlySelected <= 25)
			{
				// MOVE CURRENTLY SELECTED DOWN SECOND LAYER
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected -= 8;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
		// RIGHT
		else if (input.buttonPresses[3])
		{
			// RESET CLOCK
			startTime = clock();
			// IF CAN MOVE THE CURRENTLY SELECTED LEFT
			if (currentlySelected != 9 && currentlySelected != 19 && currentlySelected != 25)
			{
				// MOVE CURRENTLY SELECTED LEFT
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected++;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
	}

	// IF ENOUGH TIME HAS PASSED TP PRESS ANOTHER BUTTON
	if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait2)
	{
		// Z - ADD
		if (input.buttonPresses[4] && currentCharacters < maxCharacters)
		{
			// RESET CLOCK
			startTime2 = clock();
			// SELECTED LEADERBOARD IS 1
			if (currentSelectScoreToChange == 0)
			{
				// ADD CHARACTER
				currentCharacters++;
				ssTopName << currentLetter;
				topName.setString(ssTopName.str());
			}
			// SELECTED LEADERBOARD IS 2
			else if (currentSelectScoreToChange == 1)
			{
				// ADD CHARACTER
				currentCharacters++;
				ssSecondName << currentLetter;
				secondName.setString(ssSecondName.str());
			}
			// SELECTED LEADERBOARD IS 3
			else if (currentSelectScoreToChange == 2)
			{
				// ADD CHARACTER
				currentCharacters++;
				ssThirdName << currentLetter;
				thirdName.setString(ssThirdName.str());
			}
			// SELECTED LEADERBOARD IS 4
			else if (currentSelectScoreToChange == 3)
			{
				// ADD CHARACTER
				currentCharacters++;
				ssForthName << currentLetter;
				forthName.setString(ssForthName.str());
			}
			// SELECTED LEADERBOARD IS 5
			else if (currentSelectScoreToChange == 4)
			{
				// ADD CHARACTER
				currentCharacters++;
				ssFithName << currentLetter;
				fithName.setString(ssFithName.str());
			}
		}
		// X - REMOVE
		else if (input.buttonPresses[5] && currentCharacters > 0)
		{
			// RESET CLOCK
			startTime2 = clock();
			// IF SELECTED LEADERBOARD IS 1
			if (currentSelectScoreToChange == 0)
			{
				// REMOVE A CHARACTER
				currentCharacters--;
				std::string temp = ssTopName.str();
				temp.pop_back();
				ssTopName.str("");
				ssTopName << temp;
				topName.setString(ssTopName.str());
			}
			// IF SELECTED LEADERBOARD IS 2
			else if (currentSelectScoreToChange == 1)
			{
				// REMOVE A CHARACTER
				currentCharacters--;
				std::string temp = ssSecondName.str();
				temp.pop_back();
				ssSecondName.str("");
				ssSecondName << temp;
				secondName.setString(ssSecondName.str());
			}
			// IF SELECTED LEADERBOARD IS 3
			else if (currentSelectScoreToChange == 2)
			{
				// REMOVE A CHARACTER
				currentCharacters--;
				std::string temp = ssThirdName.str();
				temp.pop_back();
				ssThirdName.str("");
				ssThirdName << temp;
				thirdName.setString(ssThirdName.str());
			}
			// IF SELECTED LEADERBOARD IS 4
			else if (currentSelectScoreToChange == 3)
			{
				// REMOVE A CHARACTER
				currentCharacters--;
				std::string temp = ssForthName.str();
				temp.pop_back();
				ssForthName.str("");
				ssForthName << temp;
				forthName.setString(ssForthName.str());
			}
			// IF SELECTED LEADERBOARD IS 5
			else if (currentSelectScoreToChange == 4)
			{
				// REMOVE A CHARACTER
				currentCharacters--;
				std::string temp = ssFithName.str();
				temp.pop_back();
				ssFithName.str("");
				ssFithName << temp;
				fithName.setString(ssFithName.str());
			}
		}
	}
	// SPACE
	if (input.spacePressed)
	{
		// LOAD THE SAVE DATA
		saveData.loadFile();
		SaveData::PlayerInfo* leaderboard;
		//			LOAD THE LEADERBOARD FOR TO CORRECT GAME MODE THAT IS BEING PLAYED
		// GAME MODE - ENDLESS
		if (endless)
		{
			leaderboard = saveData.getLeaderboardEndless();
		}
		// GAME MODE - NO POWER UPS
		else if (noPowerUps)
		{
			leaderboard = saveData.getLeaderboardNoPowerUps();
		}
		// GAME MODE - INSANE
		else if (insane)
		{
			leaderboard = saveData.getLeaderboardInsane();
		}
		// GAME MODE - RANDOM
		else if (random)
		{
			leaderboard = saveData.getLeaderboardRandom();
		}
		// GAME MODE - REGULAR
		else
		{
			leaderboard = saveData.getLeaderboard();
		}

		// SELECT THE SCORE TO CHANGE FROM THE LEADERBOARD
		std::string temp;
		if (currentSelectScoreToChange == 0)
		{
			temp = topName.getString();
		}
		else if (currentSelectScoreToChange == 1)
		{
			temp = secondName.getString();
		}
		else if (currentSelectScoreToChange == 2)
		{
			temp = thirdName.getString();
		}
		else if (currentSelectScoreToChange == 3)
		{
			temp = forthName.getString();
		}
		else if (currentSelectScoreToChange == 4)
		{
			temp = fithName.getString();
		}

		// CHANGE THE NAME IN THE LEADERBOARD AND SAVE THE SAVE DATA FILE
		leaderboard[currentSelectScoreToChange].Name = temp;
		saveData.saveFile();

		// CLOSE THE HIGHSCORE SCREEN
		close = true;
	}
}

/*
	RENDER METHODS FOR "StartScreens" CLASS THAT HANDLES DRAWING EACH ELEMENT TO THE SCREEN
*/
void HighScoreScreen::render(sf::RenderTarget* target)
{
	// DRAW ALL OF THE LETTER BUTTONS TO THE SCREEN
	for (sf::RectangleShape shape : letterButtons)
	{
		target->draw(shape);
	}
	// DRAW ALL OF THE LETTER TEXT TO THE SCREEN
	for (sf::Text text : letterText)
	{
		target->draw(text);
	}
	target->draw(topFiveMessage);

	// DRAW POS 1 UI
	target->draw(top);
	target->draw(topScore);
	target->draw(topName);
	// IF ENDLESS THEN DONT DRAW THE AMMOUNT OF LIVES
	if (!endless)
	{
		target->draw(topLives);
		target->draw(secondLives);
		target->draw(thirdLives);
		target->draw(forthLives);
		target->draw(fithLives);
	}

	// DRAW POS 2 UI
	target->draw(second);
	target->draw(secondScore);
	target->draw(secondName);
	
	// DRAW POS 3 UI
	target->draw(third);
	target->draw(thirdScore);
	target->draw(thirdName);
	
	// DRAW POS 4 UI
	target->draw(forth);
	target->draw(forthScore);
	target->draw(forthName);

	// DRAW POS 5 UI
	target->draw(fith);
	target->draw(fithScore);
	target->draw(fithName);
}

/*
	INILISES THE GUI OF THE MAIN MENU'S
*/
void HighScoreScreen::initGUI()
{
	// LOAD THE FONT
	arial.loadFromFile("Assets/arial.ttf");

	// INITILISE THE ALPHABET SO THE PLAYER CAN CHOOSE THERE NAME
	float xOffset = 50;
	float yOffset = 70;
	float xMultiplier = 50;
	float yMultiplier = 50;

	float xSize = 40;
	float ySize = 40;

	int characterSize = 30;
	int characterXOffset = -8;

	// FOR EACH OF THE LETTERS IN THE ALPHABET
	for (int i = 0; i < 26; i++)
	{
		// CREATE BUTTON AND TEXT
		sf::RectangleShape tempShape = sf::RectangleShape();
		sf::Text tempText = sf::Text();

		// BUTTON
		tempShape.setSize({xSize, ySize});
		tempShape.setOrigin({ xSize / 2, ySize / 2 });
		tempShape.setFillColor(sf::Color::Red);

		// TEXT
		tempText.setCharacterSize(characterSize);
		tempText.setOrigin(tempShape.getOrigin().x + characterXOffset, tempShape.getOrigin().y);
		tempText.setFont(arial);
		tempText.setString(letters[i]);

		// FIRST LAYER
		if (i < 10)
		{
			tempShape.setPosition(xMultiplier * i + xOffset, yMultiplier * 1 + yOffset);
			tempText.setPosition({ xMultiplier * i + xOffset, yMultiplier * 1 + yOffset });
		}
		// SCOND LAYER
		else if (i < 20)
		{
			tempShape.setPosition(xMultiplier * (i - 10) + xOffset, yMultiplier * 2 + yOffset);
			tempText.setPosition({ xMultiplier * (i - 10) + xOffset, yMultiplier * 2 + yOffset });
		}
		// THIRD LAYER
		else
		{
			tempShape.setPosition(xMultiplier * (i - 18) + xOffset, yMultiplier * 3 + yOffset);
			tempText.setPosition({ xMultiplier * (i - 18) + xOffset, yMultiplier * 3 + yOffset });
		}
		// ADD TO LIST OF BUTTONS/TEXT
		letterButtons.push_back(tempShape);
		letterText.push_back(tempText);
	}

	// TOP 5 RANKING SCORE TEXT
	topFiveMessage.setCharacterSize(40);
	topFiveMessage.setPosition({ 80,280});
	topFiveMessage.setFont(arial);
	topFiveMessage.setString("Top 5 Ranking Score!!");

	// Top Score
	top.setCharacterSize(30);
	top.setPosition({ 10,400 });
	top.setFont(arial);
	top.setString("Top");

	ssTopScore.str("");
	ssTopScore << 99999999;
	topScore.setCharacterSize(30);
	topScore.setPosition({ 80, 400 });
	topScore.setFont(arial);
	topScore.setString(ssTopScore.str());

	ssTopName.str("");
	ssTopName << "";
	topName.setCharacterSize(30);
	topName.setPosition({ 230, 400 });
	topName.setFont(arial);
	topName.setString(ssTopName.str());

	ssTopLives.str("");
	ssTopLives << 100;
	topLives.setCharacterSize(30);
	topLives.setPosition({ 470, 400 });
	topLives.setFont(arial);
	topLives.setString(ssTopLives.str());

	// 2ND	
	second.setCharacterSize(30);
	second.setPosition({ 10,450 });
	second.setFont(arial);
	second.setString("2ND");

	ssSecondScore.str("");
	ssSecondScore << 99999999;
	secondScore.setCharacterSize(30);
	secondScore.setPosition({ 80, 450 });
	secondScore.setFont(arial);
	secondScore.setString(ssSecondScore.str());

	ssSecondName.str("");
	ssSecondName << "WWWWWWWW";
	secondName.setCharacterSize(30);
	secondName.setPosition({ 230, 450 });
	secondName.setFont(arial);
	secondName.setString(ssSecondName.str());

	ssSecondLives.str("");
	ssSecondLives << 100;
	secondLives.setCharacterSize(30);
	secondLives.setPosition({ 470, 450 });
	secondLives.setFont(arial);
	secondLives.setString(ssSecondLives.str());

	// 3RD
	third.setCharacterSize(30);
	third.setPosition({ 10,500 });
	third.setFont(arial);
	third.setString("3RD");

	ssThirdScore.str("");
	ssThirdScore << 99999999;
	thirdScore.setCharacterSize(30);
	thirdScore.setPosition({ 80, 500 });
	thirdScore.setFont(arial);
	thirdScore.setString(ssThirdScore.str());

	ssThirdName.str("");
	ssThirdName << "WWWWWWWW";
	thirdName.setCharacterSize(30);
	thirdName.setPosition({ 230, 500 });
	thirdName.setFont(arial);
	thirdName.setString(ssThirdName.str());

	ssThirdLives.str("");
	ssThirdLives << 100;
	thirdLives.setCharacterSize(30);
	thirdLives.setPosition({ 470, 500 });
	thirdLives.setFont(arial);
	thirdLives.setString(ssThirdLives.str());

	// 4TH
	forth.setCharacterSize(30);
	forth.setPosition({ 10,550 });
	forth.setFont(arial);
	forth.setString("4TH");

	ssForthScore.str("");
	ssForthScore << 99999999;
	forthScore.setCharacterSize(30);
	forthScore.setPosition({ 80, 550 });
	forthScore.setFont(arial);
	forthScore.setString(ssForthScore.str());

	ssForthName.str("");
	ssForthName << "WWWWWWWW";
	forthName.setCharacterSize(30);
	forthName.setPosition({ 230, 550 });
	forthName.setFont(arial);
	forthName.setString(ssForthName.str());

	ssForthLives.str("");
	ssForthLives << 100;
	forthLives.setCharacterSize(30);
	forthLives.setPosition({ 470, 550 });
	forthLives.setFont(arial);
	forthLives.setString(ssForthLives.str());
	// 5TH
	fith.setCharacterSize(30);
	fith.setPosition({ 10,600 });
	fith.setFont(arial);
	fith.setString("5TH");

	ssFithScore.str("");
	ssFithScore << 99999999;
	fithScore.setCharacterSize(30);
	fithScore.setPosition({ 80, 600 });
	fithScore.setFont(arial);
	fithScore.setString(ssFithScore.str());

	ssFithName.str("");
	ssFithName << "WWWWWWWW";
	fithName.setCharacterSize(30);
	fithName.setPosition({ 230, 600 });
	fithName.setFont(arial);
	fithName.setString(ssFithName.str());

	ssFithLives.str("");
	ssFithLives << 100;
	fithLives.setCharacterSize(30);
	fithLives.setPosition({ 470, 600 });
	fithLives.setFont(arial);
	fithLives.setString(ssFithLives.str());

	// CURENTLY SELECT BUTTON
	letterButtons[currentlySelected].setFillColor(sf::Color::Green);
	currentLetter = letterText[currentlySelected].getString();
	
	// INTILISE CLOCKS
	startTime = clock();
	startTime2 = clock();
}
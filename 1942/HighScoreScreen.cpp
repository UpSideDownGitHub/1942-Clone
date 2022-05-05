#include "HighScoreScreen.h"

/*
	CONSTRUCTOR FOR "HighScoreScreen" CLASS
*/
HighScoreScreen::HighScoreScreen()
{
	startTime = clock();
	startTime2 = clock();
	// CALL "initGUI()"
	initGUI();
}
void HighScoreScreen::initilise(int score, int lives)
{
	close = false;
	saveData.loadFile();
	SaveData::PlayerInfo* leaderboard;
	if (endless)
		leaderboard = saveData.getLeaderboardEndless();
	else if (noPowerUps)
		leaderboard = saveData.getLeaderboardNoPowerUps();
	else if (insane)
		leaderboard = saveData.getLeaderboardInsane();
	else if (random)
		leaderboard = saveData.getLeaderboardRandom();
	else
		leaderboard = saveData.getLeaderboard();
	
	for (int i = 0; i < 5; i++)
	{
		if (leaderboard[i].Score < score)
		{
			currentSelectScoreToChange = i;
			for (int j = 4; j > i; j--)
			{
				leaderboard[j] = leaderboard[j - 1];
			}
			leaderboard[i].Score = score;
			leaderboard[i].LivesUsed = lives;
			leaderboard[i].Name = "";
			break;
		}
	}

	currentCharacters = 0;

	ssTopName.str("");
	ssTopName << leaderboard[0].Name;
	topName.setString(ssTopName.str());
	ssTopScore.str("");
	ssTopScore << leaderboard[0].Score;
	topScore.setString(ssTopScore.str());
	ssTopLives.str("");
	ssTopLives << leaderboard[0].LivesUsed;
	topLives.setString(ssTopLives.str());

	ssSecondName.str("");
	ssSecondName << leaderboard[1].Name;
	secondName.setString(ssSecondName.str());
	ssSecondScore.str("");
	ssSecondScore << leaderboard[1].Score;
	secondScore.setString(ssSecondScore.str());
	ssSecondLives.str("");
	ssSecondLives << leaderboard[1].LivesUsed;
	secondLives.setString(ssSecondLives.str());

	ssThirdName.str("");
	ssThirdName << leaderboard[2].Name;
	thirdName.setString(ssThirdName.str());
	ssThirdScore.str("");
	ssThirdScore << leaderboard[2].Score;
	thirdScore.setString(ssThirdScore.str());
	ssThirdLives.str("");
	ssThirdLives << leaderboard[2].LivesUsed;
	thirdLives.setString(ssThirdLives.str());

	ssForthName.str("");
	ssForthName << leaderboard[3].Name;
	forthName.setString(ssForthName.str());
	ssForthScore.str("");
	ssForthScore << leaderboard[3].Score;
	forthScore.setString(ssForthScore.str());
	ssForthLives.str("");
	ssForthLives << leaderboard[3].LivesUsed;
	forthLives.setString(ssForthLives.str());

	ssFithName.str("");
	ssFithName << leaderboard[4].Name;
	fithName.setString(ssFithName.str());
	ssFithScore.str("");
	ssFithScore << leaderboard[4].Score;
	fithScore.setString(ssFithScore.str());
	ssFithLives.str("");
	ssFithLives << leaderboard[4].LivesUsed;
	fithLives.setString(ssFithLives.str());
	
	
	saveData.saveFile();
}

/*
	THIS METHOD WILL CHECK FOR INPUT AND THEN CHANGE THE BUTTON SELECTED
*/
void HighScoreScreen::update(sf::RenderWindow* win)
{
	input.pollEvents(win);
	if (input.buttonPresses[0]) // LEFT
	{
		if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
		{
			startTime = clock();
			if (currentlySelected != 0 && currentlySelected != 10 && currentlySelected != 20)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected--;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
	}
	else if (input.buttonPresses[1]) // DOWN
	{
		if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
		{
			startTime = clock();
			if (currentlySelected >= 0 && currentlySelected <= 9)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected += 10;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
			else if (currentlySelected >= 12 && currentlySelected <= 17)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected += 8;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
	}
	else if (input.buttonPresses[2]) // UP
	{
		if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
		{
			startTime = clock();
			if (currentlySelected >= 10 && currentlySelected <= 19)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected -= 10;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
			else if (currentlySelected >= 20 && currentlySelected <= 25)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected -= 8;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
	}
	else if (input.buttonPresses[3]) // RIGHT
	{
		if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
		{
			startTime = clock();
			if (currentlySelected != 9 && currentlySelected != 19 && currentlySelected != 25)
			{
				letterButtons[currentlySelected].setFillColor(sf::Color::Red);
				currentlySelected++;
				letterButtons[currentlySelected].setFillColor(sf::Color::Green);
				currentLetter = letterText[currentlySelected].getString();
			}
		}
	}


	if (input.buttonPresses[4]) // add a leter
	{
		if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait2)
		{
			startTime2 = clock();
			if (currentSelectScoreToChange == 0 && currentCharacters < maxCharacters)
			{
				currentCharacters++;
				ssTopName << currentLetter;
				topName.setString(ssTopName.str());
			}
			else if (currentSelectScoreToChange == 1 && currentCharacters < maxCharacters)
			{
				currentCharacters++;
				ssSecondName << currentLetter;
				secondName.setString(ssSecondName.str());
			}
			else if (currentSelectScoreToChange == 2 && currentCharacters < maxCharacters)
			{
				currentCharacters++;
				ssThirdName << currentLetter;
				thirdName.setString(ssThirdName.str());
			}
			else if (currentSelectScoreToChange == 3 && currentCharacters < maxCharacters)
			{
				currentCharacters++;
				ssForthName << currentLetter;
				forthName.setString(ssForthName.str());
			}
			else if (currentSelectScoreToChange == 4 && currentCharacters < maxCharacters)
			{
				currentCharacters++;
				ssFithName << currentLetter;
				fithName.setString(ssFithName.str());
			}
		}
	}
	else if (input.buttonPresses[5]) // remove a letter
	{
		if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait2)
		{
			startTime2 = clock();
			if (currentSelectScoreToChange == 0 && currentCharacters > 0)
			{
				currentCharacters--;
				std::string temp = ssTopName.str();
				temp.pop_back();
				ssTopName.str("");
				ssTopName << temp;
				topName.setString(ssTopName.str());
			}
			else if (currentSelectScoreToChange == 1 && currentCharacters > 0)
			{
				currentCharacters--;
				std::string temp = ssSecondName.str();
				temp.pop_back();
				ssSecondName.str("");
				ssSecondName << temp;
				secondName.setString(ssSecondName.str());
			}
			else if (currentSelectScoreToChange == 2 && currentCharacters > 0)
			{
				currentCharacters--;
				std::string temp = ssThirdName.str();
				temp.pop_back();
				ssThirdName.str("");
				ssThirdName << temp;
				thirdName.setString(ssThirdName.str());
			}
			else if (currentSelectScoreToChange == 3 && currentCharacters > 0)
			{
				currentCharacters--;
				std::string temp = ssForthName.str();
				temp.pop_back();
				ssForthName.str("");
				ssForthName << temp;
				forthName.setString(ssForthName.str());
			}
			else if (currentSelectScoreToChange == 4 && currentCharacters > 0)
			{
				currentCharacters--;
				std::string temp = ssFithName.str();
				temp.pop_back();
				ssFithName.str("");
				ssFithName << temp;
				fithName.setString(ssFithName.str());
			}
		}
	}

	if (input.spacePressed)
	{
		saveData.loadFile();
		SaveData::PlayerInfo* leaderboard;
		if (endless)
		{
			std::cout << "ENDLESS MODE\n";
			leaderboard = saveData.getLeaderboardEndless();
		}
		else if (noPowerUps)
		{
			std::cout << "NO POWER UPS MODE\n";
			leaderboard = saveData.getLeaderboardNoPowerUps();
		}
		else if (insane)
		{
			std::cout << "INSANE MODE\n";
			leaderboard = saveData.getLeaderboardInsane();
		}
		else if (random)
		{
			std::cout << "RANDOM MODE\n";
			leaderboard = saveData.getLeaderboardRandom();
		}
		else
		{
			std::cout << "NORMAL MODE\n";
			leaderboard = saveData.getLeaderboard();
		}
		std::string temp;
		if (currentSelectScoreToChange == 0)
			temp = topName.getString();
		else if (currentSelectScoreToChange == 1)
			temp = secondName.getString();
		else if (currentSelectScoreToChange == 2)
			temp = thirdName.getString();
		else if (currentSelectScoreToChange == 3)
			temp = forthName.getString();
		else if (currentSelectScoreToChange == 4)
			temp = fithName.getString();


		leaderboard[currentSelectScoreToChange].Name = temp;
		saveData.saveFile();

		close = true;
	}
}

/*
	RENDER METHODS FOR "StartScreens" CLASS THAT HANDLES DRAWING EACH ELEMENT TO THE SCREEN
*/
void HighScoreScreen::render(sf::RenderTarget* target)
{
	for (sf::RectangleShape shape : letterButtons)
	{
		target->draw(shape);
	}
	for (sf::Text text : letterText)
	{
		target->draw(text);
	}
	target->draw(topFiveMessage);

	target->draw(top);
	target->draw(topScore);
	target->draw(topName);
	if (!endless)
	{
		target->draw(topLives);
		target->draw(secondLives);
		target->draw(thirdLives);
		target->draw(forthLives);
		target->draw(fithLives);
	}

	target->draw(second);
	target->draw(secondScore);
	target->draw(secondName);
	

	target->draw(third);
	target->draw(thirdScore);
	target->draw(thirdName);

	target->draw(forth);
	target->draw(forthScore);
	target->draw(forthName);

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

	for (int i = 0; i < 26; i++)
	{
		sf::RectangleShape tempShape = sf::RectangleShape();
		sf::Text tempText = sf::Text();

		tempShape.setSize({xSize, ySize});
		tempShape.setOrigin({ xSize / 2, ySize / 2 });
		//tempShape.setPosition(xMultiplier * i + xOffset, yMultiplier * 1 + yOffset);
		tempShape.setFillColor(sf::Color::Red);

		tempText.setCharacterSize(characterSize);
		tempText.setOrigin(tempShape.getOrigin().x + characterXOffset, tempShape.getOrigin().y);
		//tempText.setPosition({ xMultiplier * i + xOffset, yMultiplier * 1 + yOffset });
		tempText.setFont(arial);
		tempText.setString(letters[i]);

		if (i < 10)
		{
			tempShape.setPosition(xMultiplier * i + xOffset, yMultiplier * 1 + yOffset);
			tempText.setPosition({ xMultiplier * i + xOffset, yMultiplier * 1 + yOffset });
		}
		else if (i < 20)
		{
			tempShape.setPosition(xMultiplier * (i - 10) + xOffset, yMultiplier * 2 + yOffset);
			tempText.setPosition({ xMultiplier * (i - 10) + xOffset, yMultiplier * 2 + yOffset });
		}
		else
		{
			tempShape.setPosition(xMultiplier * (i - 18) + xOffset, yMultiplier * 3 + yOffset);
			tempText.setPosition({ xMultiplier * (i - 18) + xOffset, yMultiplier * 3 + yOffset });
		}
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



	letterButtons[currentlySelected].setFillColor(sf::Color::Green);
	currentLetter = letterText[currentlySelected].getString();
	startTime = clock();
	startTime2 = clock();
}
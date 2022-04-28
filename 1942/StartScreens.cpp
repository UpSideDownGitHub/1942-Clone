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
void StartScreens::checkButtonPress(sf::RenderWindow* win)
{
	if (doOnce)
	{
		play = false;
		doOnce = false;
		startTime = clock();
		startTime2 = clock();

		saveData.loadFile();
		SaveData::PlayerInfo* leaderboard = saveData.getLeaderboard();

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
	}
	if (float(clock() - startTime) / CLOCKS_PER_SEC * 1000 >= timeToWait)
	{
		input.pollEvents(win);
		if (!leaderboard)
		{
			if (input.buttonPresses[1]) // DOWN
			{
				if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait)
				{
					startTime2 = clock();
					if (selected < 6)
					{
						options[selected].setFillColor(sf::Color::White);
						selected++;
						options[selected].setFillColor(sf::Color::Yellow);
					}
				}
			}
			else if (input.buttonPresses[2]) // UP
			{
				if (float(clock() - startTime2) / CLOCKS_PER_SEC * 1000 >= timeToWait2)
				{
					startTime2 = clock();
					if (selected > 0)
					{
						options[selected].setFillColor(sf::Color::White);
						selected--;
						options[selected].setFillColor(sf::Color::Yellow);
					}
				}
			}
		}
		if (input.spacePressed)
		{
			if (leaderboard)
			{
				doOnce = true;
				leaderboard = false;
			}
			else
			{
				doOnce = true;
				selectMode(win);
			}
		}
	}
}

void StartScreens::selectMode(sf::RenderWindow* win)
{
	if (selected == 0)
	{
		play = true;
		normal = true;
	}
	else if (selected == 1)
	{
		play = true;
		endless = true;
	}
	else if (selected == 2)
	{
		play = true;
		noPowerUp = true;
	}
	else if (selected == 3)
	{
		play = true;
		insane = true;
	}
	else if (selected == 4)
	{
		play = true;
		random = true;
	}
	else if (selected == 5)
	{
		leaderboard = true;
	}
	else if (selected == 6)
	{

		win->close();
	}
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
	for (sf::Text text : options)
	{
		target->draw(text);
	}
	
	if (leaderboard)
	{
		target->draw(box);
		target->draw(topFiveMessage);

		target->draw(top);
		target->draw(topScore);
		target->draw(topName);
		target->draw(topLives);
		target->draw(second);
		target->draw(secondScore);
		target->draw(secondName);
		target->draw(secondLives);

		target->draw(third);
		target->draw(thirdScore);
		target->draw(thirdName);
		target->draw(thirdLives);

		target->draw(forth);
		target->draw(forthScore);
		target->draw(forthName);
		target->draw(forthLives);

		target->draw(fith);
		target->draw(fithScore);
		target->draw(fithName);
		target->draw(fithLives);
	}
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
	insertCoinText.setPosition({ 160,330 });
	insertCoinText.setFont(arial);
	insertCoinText.setString("Insert Coin");

	int xOffset = 280;
	int yOffset = 400;
	int yMulti = 30;
	for (int i = 0; i < 7; i++)
	{
		sf::Text temp;
		temp.setCharacterSize(30);
		temp.setPosition( xOffset, yOffset + i * yMulti);
		temp.setFont(arial);
		temp.setString(gameModes[i]);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);
		options.push_back(temp);
	}

	// COPYRIGHT
	copyrightText.setCharacterSize(20);
	copyrightText.setPosition({ 190,600});
	copyrightText.setFont(arial);
	copyrightText.setString("© 2022 Reuben Miller");
	

	options[selected].setFillColor(sf::Color::Yellow);



	// TOP 5 RANKING SCORE TEXT
	topFiveMessage.setCharacterSize(40);
	topFiveMessage.setPosition({ 80,30 });
	topFiveMessage.setFont(arial);
	topFiveMessage.setString("Top 5 Ranking Scores");

	box.setFillColor(sf::Color::Blue);
	box.setPosition(10, 10);
	box.setSize({ 540, 620 });

	// Top Score
	top.setCharacterSize(30);
	top.setPosition({ 20,150 });
	top.setFont(arial);
	top.setString("Top");

	ssTopScore.str("");
	ssTopScore << 99999999;
	topScore.setCharacterSize(30);
	topScore.setPosition({ 90, 150 });
	topScore.setFont(arial);
	topScore.setString(ssTopScore.str());

	ssTopName.str("");
	ssTopName << "";
	topName.setCharacterSize(30);
	topName.setPosition({ 240, 150 });
	topName.setFont(arial);
	topName.setString(ssTopName.str());

	ssTopLives.str("");
	ssTopLives << 100;
	topLives.setCharacterSize(30);
	topLives.setPosition({ 480, 150 });
	topLives.setFont(arial);
	topLives.setString(ssTopLives.str());

	// 2ND	
	second.setCharacterSize(30);
	second.setPosition({ 20,200 });
	second.setFont(arial);
	second.setString("2ND");

	ssSecondScore.str("");
	ssSecondScore << 99999999;
	secondScore.setCharacterSize(30);
	secondScore.setPosition({ 90, 200 });
	secondScore.setFont(arial);
	secondScore.setString(ssSecondScore.str());

	ssSecondName.str("");
	ssSecondName << "WWWWWWWW";
	secondName.setCharacterSize(30);
	secondName.setPosition({ 240, 200 });
	secondName.setFont(arial);
	secondName.setString(ssSecondName.str());

	ssSecondLives.str("");
	ssSecondLives << 100;
	secondLives.setCharacterSize(30);
	secondLives.setPosition({ 480, 200 });
	secondLives.setFont(arial);
	secondLives.setString(ssSecondLives.str());

	// 3RD
	third.setCharacterSize(30);
	third.setPosition({ 20,250 });
	third.setFont(arial);
	third.setString("3RD");

	ssThirdScore.str("");
	ssThirdScore << 99999999;
	thirdScore.setCharacterSize(30);
	thirdScore.setPosition({ 90, 250 });
	thirdScore.setFont(arial);
	thirdScore.setString(ssThirdScore.str());

	ssThirdName.str("");
	ssThirdName << "WWWWWWWW";
	thirdName.setCharacterSize(30);
	thirdName.setPosition({ 240, 250 });
	thirdName.setFont(arial);
	thirdName.setString(ssThirdName.str());

	ssThirdLives.str("");
	ssThirdLives << 100;
	thirdLives.setCharacterSize(30);
	thirdLives.setPosition({ 480, 250 });
	thirdLives.setFont(arial);
	thirdLives.setString(ssThirdLives.str());

	// 4TH
	forth.setCharacterSize(30);
	forth.setPosition({ 20,300 });
	forth.setFont(arial);
	forth.setString("4TH");

	ssForthScore.str("");
	ssForthScore << 99999999;
	forthScore.setCharacterSize(30);
	forthScore.setPosition({ 90, 300 });
	forthScore.setFont(arial);
	forthScore.setString(ssForthScore.str());

	ssForthName.str("");
	ssForthName << "WWWWWWWW";
	forthName.setCharacterSize(30);
	forthName.setPosition({ 240, 300 });
	forthName.setFont(arial);
	forthName.setString(ssForthName.str());

	ssForthLives.str("");
	ssForthLives << 100;
	forthLives.setCharacterSize(30);
	forthLives.setPosition({ 480, 300 });
	forthLives.setFont(arial);
	forthLives.setString(ssForthLives.str());
	// 5TH
	fith.setCharacterSize(30);
	fith.setPosition({ 20,350 });
	fith.setFont(arial);
	fith.setString("5TH");

	ssFithScore.str("");
	ssFithScore << 99999999;
	fithScore.setCharacterSize(30);
	fithScore.setPosition({ 90, 350 });
	fithScore.setFont(arial);
	fithScore.setString(ssFithScore.str());

	ssFithName.str("");
	ssFithName << "WWWWWWWW";
	fithName.setCharacterSize(30);
	fithName.setPosition({ 240, 350 });
	fithName.setFont(arial);
	fithName.setString(ssFithName.str());

	ssFithLives.str("");
	ssFithLives << 100;
	fithLives.setCharacterSize(30);
	fithLives.setPosition({ 480, 350 });
	fithLives.setFont(arial);
	fithLives.setString(ssFithLives.str());
}
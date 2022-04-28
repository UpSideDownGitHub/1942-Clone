#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>

class SaveData
{
public:
	// CONSTRUCTOR
	SaveData();
	
	// VARIABLES
	struct PlayerInfo
	{
		std::string Name;
		int Score;
		int LivesUsed;
	};

	//			METHODS
	void loadFile();
	void saveFile();

	// GET METHODS
	int getHighScore();
	int getDailyHighestPercent();
	PlayerInfo* getLeaderboard();

	// SET METHODS
	void setHighScore(int score);
	void setDailyHighestPercent(int percent);
	void setLeaderbaord(PlayerInfo info[5]);

private:
	// VARIABLES
	struct gameSaveData
	{
		int highScore;
		int dailyHighestPercent;
		PlayerInfo leaderboard[5];
	};
	gameSaveData savedata;
};


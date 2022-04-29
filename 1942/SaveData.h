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
	PlayerInfo* getLeaderboardEndless();
	PlayerInfo* getLeaderboardNoPowerUps();
	PlayerInfo* getLeaderboardInsane();
	PlayerInfo* getLeaderboardRandom();

	// SET METHODS
	void setHighScore(int score);
	void setDailyHighestPercent(int percent);
	void setLeaderbaord(PlayerInfo info[5]);
	void setLeaderboardEndless(PlayerInfo info[5]);
	void setLeaderboardNoPowerUps(PlayerInfo info[5]);
	void setLeaderboardInsane(PlayerInfo info[5]);
	void setLeaderboardRandom(PlayerInfo info[5]);

private:
	// VARIABLES
	struct gameSaveData
	{
		int highScore;
		int dailyHighestPercent;
		PlayerInfo leaderboard[5];
		PlayerInfo leaderboardEndless[5];
		PlayerInfo leaderboardNoPowerUps[5];
		PlayerInfo leaderboardInsane[5];
		PlayerInfo leaderboardRandom[5];
	};
	gameSaveData savedata;
};


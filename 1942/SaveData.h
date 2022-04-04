#pragma once
#include <iostream>
#include <fstream>
#include <Map>

class SaveData
{
public:
	// CONSTRUCTOR
	SaveData();

	//			METHODS
	void loadFile();
	void saveFile();

	// GET METHODS
	int getHighScore();
	int getDailyHighestPercent();
	std::map<std::string, int> getLeaderboard();

	// SET METHODS
	void setHighScore(int score);
	void setDailyHighestPercent(int percent);
	void setLeaderbaord(std::map<std::string, int> map);

private:
	// VARIABLES
	struct gameSaveData
	{
		int highScore;
		int dailyHighestPercent;
		std::map<std::string, int> leaderboard;
	};
	gameSaveData savedata;
};


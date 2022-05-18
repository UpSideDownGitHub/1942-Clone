/*
Program: 1942
Filename: SaveData.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 18/05/22
*/
/*
File: SaveData.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "SaveData.h"

/*
	CONSTRUCTOR FOR THE "SaveData" CLASS
*/
SaveData::SaveData()
{
	// LOAD THE SAVE DATA
	loadFile();
}

/*
	METHODS LOADS THE DATA FROM THE SAVE FILE AND SAVES IT TO A STRUCT
*/
void SaveData::loadFile()
{
	// READ THE FILE
	std::ifstream readFile("Assets/SAVE/Save.dat", std::ios::out | std::ios::binary);

	// IF THE FILE READ INCORRECTLY
	if (!readFile)
	{
		saveFile();
		std::cout << "Cannot open file\n";
		return;
	}

	// READ THE FILE INTO THE STRUCT
	readFile.read((char *)&savedata, sizeof(gameSaveData));

	// CLOSE THE FILE
	readFile.close();

	// IF THE FILE RED CORRECTLY
	if (!readFile.good())
	{
		std::cout << "Error during reading\n";
		return;
	}
}

/*
	MOETHODS LOADS THE DATA FROM THE STRUCT AND SAVES IT TO A FILE
*/
void SaveData::saveFile()
{
	// CREATES A WRITE FILE OBJECT
	std::ofstream writeFile("Assets/SAVE/Save.dat", std::ios::out | std::ios::binary);
	// IF THE FILE DID NOT OPEN CORRECTLY
	if (!writeFile)
	{
		std::cout << "Cannot open file\n";
		return;
	}
	// WRITE THE STRUCT TO THE FILE
	writeFile.write((char *)&savedata, sizeof(gameSaveData));
	// CLOSE THE FILE
	writeFile.close();
}


/*
	GET METHODS FOR DATA IN THE STRUCT
*/
int SaveData::getHighScore()
{
	return savedata.highScore;
}
int SaveData::getDailyHighestPercent()
{
	return savedata.dailyHighestPercent;
}
SaveData::PlayerInfo* SaveData::getLeaderboard()
{
	return savedata.leaderboard;
}
SaveData::PlayerInfo* SaveData::getLeaderboardEndless()
{
	return savedata.leaderboardEndless;
}
SaveData::PlayerInfo* SaveData::getLeaderboardNoPowerUps()
{
	return savedata.leaderboardNoPowerUps;
}
SaveData::PlayerInfo* SaveData::getLeaderboardInsane()
{
	return savedata.leaderboardInsane;
}
SaveData::PlayerInfo* SaveData::getLeaderboardRandom()
{
	return savedata.leaderboardRandom;
}


/*
	SET METHODS FOR DATA IN THE STRUCT
*/
void SaveData::setHighScore(int score)
{
	savedata.highScore = score;
}
void SaveData::setDailyHighestPercent(int percent)
{
	savedata.dailyHighestPercent = percent;
}
void SaveData::setLeaderbaord(PlayerInfo info[5])
{
	savedata.leaderboard[0] = info[0];
	savedata.leaderboard[1] = info[1];
	savedata.leaderboard[2] = info[2];
	savedata.leaderboard[3] = info[3];
	savedata.leaderboard[4] = info[4];
}
void SaveData::setLeaderboardEndless(PlayerInfo info[5])
{
	savedata.leaderboardEndless[0] = info[0];
	savedata.leaderboardEndless[1] = info[1];
	savedata.leaderboardEndless[2] = info[2];
	savedata.leaderboardEndless[3] = info[3];
	savedata.leaderboardEndless[4] = info[4];
}
void SaveData::setLeaderboardNoPowerUps(PlayerInfo info[5])
{
	savedata.leaderboardNoPowerUps[0] = info[0];
	savedata.leaderboardNoPowerUps[1] = info[1];
	savedata.leaderboardNoPowerUps[2] = info[2];
	savedata.leaderboardNoPowerUps[3] = info[3];
	savedata.leaderboardNoPowerUps[4] = info[4];
}
void SaveData::setLeaderboardInsane(PlayerInfo info[5])
{
	savedata.leaderboardInsane[0] = info[0];
	savedata.leaderboardInsane[1] = info[1];
	savedata.leaderboardInsane[2] = info[2];
	savedata.leaderboardInsane[3] = info[3];
	savedata.leaderboardInsane[4] = info[4];
}
void SaveData::setLeaderboardRandom(PlayerInfo info[5])
{
	savedata.leaderboardRandom[0] = info[0];
	savedata.leaderboardRandom[1] = info[1];
	savedata.leaderboardRandom[2] = info[2];
	savedata.leaderboardRandom[3] = info[3];
	savedata.leaderboardRandom[4] = info[4];
}


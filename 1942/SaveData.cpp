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
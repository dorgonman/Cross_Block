#include "ScoreData.h"
#include "GameDB.h"
#include <algorithm> 
#ifndef PERSONALDATA
#define PERSONALDATA
class PersonalData{
public:
	PersonalData(string _dbPath);
public:
	void loadScore(char* folderPath, char* fileType  = "*.txt");
	void printAllScore();
	void printScore(vector<ScoreData*> scoreDatas);

public:
	vector<ScoreData*> sortbyDifficulty(int filter, vector<ScoreData*> s);
	vector<GameState*> getState(vector<ScoreData*> s);


public:
	enum eSort{
		DIFFICULTY,
		RESCORED_DIFFICULTY
	};
private:
	vector<string> getAllFile(char* folderPath, char* fileType);
	void currentDirectory();
public:
	GameDB* puzzleDB;//釋出給玩家玩，未經排序的遊戲
	vector<vector<ScoreData*>> datas;
	string dbFilePath;//從哪個檔案拿出來的，debug用
};


#endif
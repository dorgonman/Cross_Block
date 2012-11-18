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
	GameDB* puzzleDB;//���X�����a���A���g�ƧǪ��C��
	vector<vector<ScoreData*>> datas;
	string dbFilePath;//�q�����ɮ׮��X�Ӫ��Adebug��
};


#endif
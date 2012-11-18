
#include "vector"
#include "GameState.h"
#include "PersonalData.h"
#include "GameParameter.h"
#ifndef GAME_STATISTIC
#define GAME_STATISTIC
class Statistic{
public:
	Statistic(){};
public:
	float mean(int filter, vector<GameState*> states);
	
	float MAX(int filter, vector<GameState*> states);
	float MIN(int filter, vector<GameState*> states);
	float variance(int filter, vector<GameState*> states);
public:
	void calculateComplexity(vector<GameState*> states);
	void calculateComplexity(GameParameter* parameter, vector<GameState*> states);
public:

	vector<GameState*> meanAndvariance(int filter,  PersonalData* personalData);
	float similarityOfRank(vector<GameState*> listA, vector<ScoreData*> listB);//計算二種不同puzzle set排序的相似度
	float similarityOfRank(vector<ScoreData*> listA, vector<ScoreData*> listB);//計算二種不同puzzle set排序的相似度
	float similarityOfRank(vector<GameState*> listA, vector<GameState*> listB);//計算二種不同puzzle set排序的相似度

	float matchOfRank(vector<GameState*> listA, vector<GameState*> listB);//計算二種不同puzzle set排序的相似度，需丟進排序過後的
	float matchOfRank(vector<ScoreData*> listA, vector<ScoreData*> listB);//計算二種不同puzzle set排序的相似度，需丟進排序過後的
	float matchOfRank(vector<GameState*> listA, vector<ScoreData*> listB);//計算二種不同puzzle set排序的相似度，需丟進排序過後的
private:
	vector<GameState*> mean(int filter, PersonalData* personalData);//將人們的難度塞到complexity裡回傳

public:
	enum eFilter{
		BRANCH,
		DEADEND,
		COMPLEXITY,
		DIFFICULTY,
		RESCORED_DIFFICULTY
	};


};


#endif
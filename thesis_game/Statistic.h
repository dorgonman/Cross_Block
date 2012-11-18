
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
	float similarityOfRank(vector<GameState*> listA, vector<ScoreData*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ���
	float similarityOfRank(vector<ScoreData*> listA, vector<ScoreData*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ���
	float similarityOfRank(vector<GameState*> listA, vector<GameState*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ���

	float matchOfRank(vector<GameState*> listA, vector<GameState*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ��סA�ݥ�i�ƧǹL�᪺
	float matchOfRank(vector<ScoreData*> listA, vector<ScoreData*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ��סA�ݥ�i�ƧǹL�᪺
	float matchOfRank(vector<GameState*> listA, vector<ScoreData*> listB);//�p��G�ؤ��Ppuzzle set�ƧǪ��ۦ��סA�ݥ�i�ƧǹL�᪺
private:
	vector<GameState*> mean(int filter, PersonalData* personalData);//�N�H�̪����׶��complexity�̦^��

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
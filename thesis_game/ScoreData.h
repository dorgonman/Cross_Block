#include "GameState.h"

#ifndef SCOREDATA
#define SCOREDATA
class ScoreData{
public:
	ScoreData(GameState* _state){
		difficulty = 0;
		rescoredDifficulty = 0;
		state = _state;
		rank = -1;
	};
public:
	int rank;
	float difficulty;
	float rescoredDifficulty;
	GameState* state;
	string filePath;//�q�����ɮ׮��X�Ӫ��Adebug��
};


#endif
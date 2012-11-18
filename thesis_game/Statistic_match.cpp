
#include "Statistic.h"



float Statistic::matchOfRank(std::vector<GameState*> listA, std::vector<GameState*> listB){
	float result = 0;
	float maxSize = max(listA.size(), listB.size());
	for(int i = 0; i < listA.size(); i++){
		GameState* A = listA[i];
		for(int j = 0; j < listB.size(); j++){
			GameState* B = listB[j];
			if(A->isSame(B)){
				if(A->rank == B->rank){
					result++;
				}
			}
		}
	}
	return result / maxSize;
}


float Statistic::matchOfRank(std::vector<ScoreData*> listA, std::vector<ScoreData*> listB){
	float result = 0;
	float maxSize = max(listA.size(), listB.size());
	for(int i = 0; i < listA.size(); i++){
		ScoreData* A = listA[i];
		for(int j = 0; j < listB.size(); j++){
			ScoreData* B = listB[j];
			if(A->state->isSame(B->state)){
				if(A->rank == B->rank){
					result++;
				}
			}
		}
	}
	return result / maxSize;
}




float Statistic::matchOfRank(std::vector<GameState*> listA, std::vector<ScoreData*> listB){
	float result = 0;

	float maxSize = max(listA.size(), listB.size());
	for(float i = 0; i < listA.size(); i++){
		GameState* A = listA[i];
		for(float j = 0; j < listB.size(); j++){
			ScoreData* B = listB[j];
			if(A->isSame(B->state)){
				if(A->rank == B->rank){
					result = result + 1;
				}
			}
		}
	}
	return result / maxSize;
}




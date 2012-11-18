#include "Statistic.h"


float Statistic::similarityOfRank(std::vector<GameState*> listA, std::vector<ScoreData*> listB){
	float result = 0;

	float maxSize = max(listA.size(), listB.size());
	for(float i = 0; i < listA.size(); i++){
		GameState* A = listA[i];
		for(float j = 0; j < listB.size(); j++){
			ScoreData* B = listB[j];
			if(A->isSame(B->state)){
				if(A->rank == B->rank){
					result = result + 1;
				}else{
					float diff = abs(A->rank - B->rank) / (maxSize - 1);
					result = result + ( 1 -  diff);
				}
			}
		}
	}
	return result / maxSize;
}




float Statistic::similarityOfRank( std::vector<ScoreData*> listA, std::vector<ScoreData*> listB){
	float result = 0;

	float maxSize = max(listA.size(), listB.size());
	for(float i = 0; i < listA.size(); i++){
		ScoreData* A = listA[i];
		for(float j = 0; j < listB.size(); j++){
			ScoreData* B = listB[j];
			if(A->state->isSame(B->state)){
				if(A->rank == B->rank){
					result = result + 1;
				}else{
					float diff = abs(A->rank - B->rank) / (maxSize - 1);
					result = result + ( 1 -  diff);
				}
			}
		}
	}
	return result / maxSize;
}






float Statistic::similarityOfRank(std::vector<GameState*> listA, std::vector<GameState*> listB){
	float result = 0;
	float maxSize = max(listA.size(), listB.size());
	for(float i = 0; i < listA.size(); i++){
		GameState* A = listA[i];
		for(float j = 0; j < listB.size(); j++){
			GameState* B = listB[j];
			if(A->isSame(B)){
				if(A->isSame(B)){
					if(A->rank == B->rank){
						result = result + 1;
					}else{
						float diff = abs(A->rank - B->rank) / (maxSize - 1);
						result = result + ( 1 -  diff);
					}
				}
			}
		}
	}
	return result / maxSize; //normalize
}

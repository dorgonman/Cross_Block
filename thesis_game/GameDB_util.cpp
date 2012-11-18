
#include <algorithm> 
#include "GameDB.h"



bool GameDB::exist(std::vector<GameState*> dbStates, GameState *s){
	for(int i = 0; i < dbStates.size(); i++){
		if(dbStates[i]->isSame(s)){
			return true;
		}
	}
	return false;
}


vector<GameState*> GameDB::merge(vector<GameState*> s1, vector<GameState*> s2){

	vector<GameState*> result;
	for(int i = 0; i < s1.size(); i++){
		result.push_back(s1[i]);
	}
	for(int i = 0; i < s2.size(); i++){
		result.push_back(s2[i]);
	}

	return result;
}
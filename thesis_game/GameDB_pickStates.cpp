#include "GameDB.h"




vector<GameState*> GameDB::pickStates(std::vector<GameState*> db, std::vector<GameState*> s){

	vector<GameState*> result;//從db中挑出相同的puzzle出來
	for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
		GameState* state = *it;

		for(vector<GameState*>::iterator it2 = s.begin(); it2 != s.end(); it2++){
			GameState* state2 = *it2;
			if(state->isSame(state2)){
				result.push_back(state);
			}
		}

	}

	return result;
}


vector<GameState*> GameDB::pickStates(std::vector<GameState*> db, GameState* s){
	
	vector<GameState*> result;//從db中挑出相同的puzzle出來
	for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
		GameState* state = *it;
		if(state->isSame(s)){
			result.push_back(state); //這樣做可以知道我們的db裡是不是有重覆
		}
	}

	return result;
}



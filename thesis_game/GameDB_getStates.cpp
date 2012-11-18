#include "GameDB.h"




extern HGE* hge;
vector<GameState*> GameDB::getStates(int filter, float threshold){
	return getStates(states, filter, threshold);

}
vector<GameState*> GameDB::getStates(vector<GameState*> db, int filter, float threshold){
	vector<GameState*> result;
	switch(filter){
		case STEP_EQUAL:
			for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
				GameState* state = *it;
				if(state->solvedStep == threshold){
					result.push_back(state);
				}
			}
			break;
		case CROSS_OUT_EQUAL:
			for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
				GameState* state = *it;
				if(state->crossOut == threshold){
					result.push_back(state);
				}
			}
			break;
		case COMPLEXITY_BELOW:
			for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
				GameState* state = *it;
				if(state->complexity <= threshold){
					result.push_back(state);
				}
			}
			break;
		case COMPLEXITY_ABOVE:
			for(vector<GameState*>::iterator it = db.begin(); it != db.end(); it++){
				GameState* state = *it;
				if(state->complexity > threshold || state->complexity == 0){
					result.push_back(state);
				}
			}
			break;

		case ALL:
			result = db;
			break;
	}
	return result;
}


vector<GameState*> GameDB::getRandomStates(int n){
	return getRandomStates(n, states);
}


vector<GameState*> GameDB::getRandomStates(int n, vector<GameState*> dbStates){
	vector<GameState*> result;

	if(dbStates.size() < n){
		cout << "error: dbStates.size() < n" << endl;
		return result;
	}

	//hge->Random_Seed(200);
	int i = 0;
	while(i < n){
		int r = hge->Random_Int(0, (int)states.size() - 1);
		GameState* state = dbStates[r];
		if(!exist(result, state)){
			result.push_back(state);
			i++;
		}
	}


	return result;
}



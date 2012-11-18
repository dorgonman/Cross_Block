#include "GameControl.h"
#include <algorithm> 
#include "Statistic.h"


bool descentComplexity(GameState* s1,GameState* s2){

	return  s1->complexity > s2->complexity;
}
bool ascentComplexity(GameState* s1,GameState* s2){
	return   s1->complexity < s2->complexity;
}


vector<GameState*> GameControl::sortbyComplexity(int sortMode, vector<GameState*> s){

	switch(sortMode){
		case ASCENT:
			sort(s.begin(), s.end(), ascentComplexity); 
			break;
		case DESCENT:
			sort(s.begin(), s.end(), descentComplexity); 
			break;
	}


	float score = - 1;
	for(int i = 0; i < s.size(); i++){
		if(score < s[i]->complexity){
			s[i]->rank = i;
			score = s[i]->complexity;
		}else{
			s[i]->rank = s[i - 1]->rank;
		}
	}
	return s;
}


vector<GameState*> GameControl::sortbyComplexity(int sortMode){
	return sortbyComplexity(sortMode, states);
}


bool descentSolveStep(GameState* s1,GameState* s2){return (s1->solvedStep > s2->solvedStep);}
bool ascentSolveStep(GameState* s1,GameState* s2){return (s1->solvedStep  < s2->solvedStep);}

vector<GameState*> GameControl::sortbySolvedStep(int sortMode){
		switch(sortMode){
		case ASCENT:
			sort(states.begin(), states.end(), ascentSolveStep); 
			break;
		case DESCENT:
			sort(states.begin(), states.end(), descentSolveStep); 
			break;
	
	}
	return states;
}


//======================================

bool ascentGrid(Grid g1,Grid g2){
	if(g1.x == g2.x){
		return (g1.y < g2.y);
	}else{
		return (g1.x < g2.x);
	}
}
vector<GameState*> GameControl::sortSolvedSequence(){

	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
	    GameState* state = *it;
		std::reverse(state->solvedSequence.begin(), state->solvedSequence.end());//反轉成正確的解題步驟=>因為在產生的時候是倒著產生的

		for(vector<vector<Grid>>::iterator it2 = state->solvedSequence.begin(); it2 != state->solvedSequence.end(); it2++){
			vector<Grid>& line = *it2;
			sort(line.begin(), line.end(), ascentGrid); 
		}
	}
	return states;

}


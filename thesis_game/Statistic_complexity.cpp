#include "Statistic.h"
#include <algorithm> 


//======================================================================

void Statistic::calculateComplexity(GameParameter* parameter, std::vector<GameState*> states){
	//cout << "recalculate complexity, please waiting" << endl;
     for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
	    GameState* state = *it;
		state->complexity = parameter->B * (state->nBranch / MAX(Statistic::BRANCH, states)) +
			                parameter->D * (state->nDeadEnd / MAX(Statistic::DEADEND, states));
	}

	//normalize complexity to 0 ~ 1
	float maxC = MAX(COMPLEXITY, states);
	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
	    GameState* state = *it;
		state->complexity = state->complexity / maxC;
	}
	


}


void Statistic::calculateComplexity(std::vector<GameState*> states){
	GameParameter p(1);
	calculateComplexity(&p, states);
}


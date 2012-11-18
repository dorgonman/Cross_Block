#include "Statistic.h"
#include <algorithm> 


float Statistic::mean(int filter, vector<GameState*> states){
	float result = 0;
	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
		GameState* s = *it;
		switch(filter){
			case BRANCH:
				result += s->nBranch;
			break;
			case DEADEND:
				result += s->nDeadEnd;
			break;
			case COMPLEXITY:
				result += s->complexity;
				break;
		}
	}
	result = result / (float)states.size();
	return result;
}



float Statistic::MAX(int filter, vector<GameState*> states){
	float result = -1;
	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
		GameState* s = *it;
		switch(filter){
			case BRANCH:
				if(result < s->nBranch){
					result = s->nBranch;
				}
			break;
			case DEADEND:
				if(result < s->nDeadEnd){
					result = s->nDeadEnd;
				}
			break;
			case COMPLEXITY:
				if(result < s->complexity){
					result = s->complexity;
				}
			    break;
		}
	}
	
	return result;
}


#define INF 999999999999999;
float Statistic::MIN(int filter, vector<GameState*> states){
	float result = INF;

	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
		GameState* s = *it;
		switch(filter){
			case BRANCH:
				if(result > s->nBranch){
					result = s->nBranch;
				}
			break;
			case DEADEND:
				if(result > s->nDeadEnd){
					result = s->nDeadEnd;
				}
			break;
			case COMPLEXITY:
				if(result > s->complexity){
					result = s->complexity;
				}
			break;
		}
	}
	
	return result;
}


float Statistic::variance(int filter, std::vector<GameState*> states){
	float result = 0;
	float m = mean(filter, states);

	for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
		GameState* s = *it;
		switch(filter){
			case BRANCH:
				result = result + (s->nBranch - m) * (s->nBranch - m) ;
			break;
			case DEADEND:
				result = result + (s->nDeadEnd - m) * (s->nDeadEnd - m) ;
			break;
			case COMPLEXITY:
				result = result + (s->nDeadEnd - m) * (s->nDeadEnd - m) ;
				break;

		}
	}
	result = result / ((float)states.size() - 1);

	return result;

}



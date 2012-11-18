#include "GameControl.h"

#include "GameState.h"


bool GameControl::isGoal(){
	return currentState->isGoal();
}

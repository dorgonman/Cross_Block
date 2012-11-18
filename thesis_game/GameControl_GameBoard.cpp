#include "GameControl.h"






GameState* GameControl::getCurrentState(){
	return currentState;
}





void GameControl::setStateIndex(int index){




	if(index < 0){
		index = states.size() - 1;
	}

	if(index >= (int)states.size()){
		index = 0;

	}

	if(currentState != NULL){
		delete currentState;
		currentState = NULL;
	}
	stateIndex = index;
	currentState = states[stateIndex]->clone();


}

int GameControl::getStateIndex(){
	return stateIndex;
}


#include "GameState.h"
#include "GameControl.h"


GameState::GameState(int _sizex, int _sizey){
	id = -1;
	crossOut = 2;
	sizex = _sizex;
	sizey = _sizey;
	//+ 1 個(額外一個是用來記錄資訊用的) 0行及0列
	board.resize(sizex + 1, vector<int>(sizey + 1));
	solvedStep = 0;
	nLiveRoad = 0;
	nDeadEnd = 0;
	nNode = 0;
	nBranch = 0;
	nbacktrace = 0;
	complexity = 0;

	rank = -1;
}


GameState::~GameState(){
   for(int j = 0; j < board.size(); j++){
	   board[j].clear();
   }
   	for(int j = 0; j < solvedSequence.size(); j++){
		solvedSequence[j].clear();

	}
   board.clear();
   solvedSequence.clear();

}



bool GameState::isGoal(){
	for(int j = 1; j < board.size(); j++){
		for(int i = 1; i < board[0].size(); i++){
			if(board[j][i]){
				return false;
			}
		
		}
	}
	return true;

}
bool GameState::isSame(GameState *state){
	//if(board == state->board){
		//return true;
	//}
	
	
	if(crossOut != state->crossOut){ //不同crossOut就不同
		return false;
	}

	if(board.size() != state->board.size()){//不同的y size就不同
		return false;
	}

	if(board[0].size() != state->board[0].size()){//不同的x size就不同
		return false;
	}

	for(int j = 1; j < board.size() ;j++){//檢查上面的方塊是否都一樣，都一樣的話就是相同
		for(int i = 1; i < board[0].size(); i++){
			if(board[j][i] != state->board[j][i]){
				return false;
			}
		}
	
	} 

	return true;



}




int GameState::countBoard(){
	int totalNum = 0;
		//橫行
	for(int y = 1; y != board.size(); ++y){
		int num = 0;

		for(int x = 1; x != board[0].size(); ++x) {
			if(board[y][x]){
				num++;
				totalNum++;
			}
		}

		board[y][0] = num;
	}


	//直行
	for(int x = 1; x != board.size(); ++x){
		int num = 0;

		for(int y = 1; y != board[0].size(); ++y) {
			if(board[y][x]){
				num++;
			}
		}

		board[0][x] = num;
	}

	board[0][0] = totalNum;//在此格將數值記錄下來
	return totalNum;

}

bool GameState::isDead(){


	int totalNum = countBoard();


	int count = 0;
	for(int x = 1; x !=  board.size(); ++x){
		for(int y = 1; y != board[0].size(); ++y) {

			if(board[y][x]){//如果有子，就看直行跟橫行是否都死了，死的話就是死路
				if(board[y][0] <  crossOut){
					count++;
				}


				if(board[0][x] < crossOut){
						count++;
				}

				if(count == 2){
					return true;
				}
			}

			count = 0;


		}
	}

	return false;
}




GameState* GameState::clone(){
	GameState* cloneState = new GameState(sizex, sizey);
	cloneState->id = id;
	cloneState->board = board;
	cloneState->crossOut = crossOut;
	cloneState->solvedStep = solvedStep;
	cloneState->nDeadEnd = nDeadEnd;
	cloneState->nLiveRoad = nLiveRoad;
	cloneState->nNode = nNode;
	cloneState->nbacktrace = nbacktrace;
	cloneState->solvedSequence = solvedSequence;
	cloneState->nBranch = nBranch;
	cloneState->complexity = complexity;
	cloneState->rank = rank;
	return cloneState;

}
#include "GameControl.h"



//消除方塊
bool GameControl::operation(Grid g1, Grid g2){
	if(operation(currentState, g1, g2)){
		return true;
	}
	return false;
}


bool GameControl::operation(GameState* state, Grid g1, Grid g2){

	if(isValidOperation(state, g1, g2)){
		
		//消直行
		if(g2.x == g1.x){
			for(int j = g1.y; j <= g2.y; j++){
				if(j >= state->board.size()){
					break;
				}
				state->board[j][g1.x] = 0;
			}
		}


		//消橫行
		if( g2.y == g1.y){
			for(int i = g1.x; i <= g2.x; i++){
				if(i >= state->board[0].size()){
					break;
				}
				state->board[g1.y][i] = 0;
			}
		}
		return true;
	}

	return false;

}




//將數值總合較高的operation調整順序一下(高的是g1，低的是g2)
void GameControl::generalizeOperation(Grid& g1, Grid& g2){
	int n1 = g1.x + g1.y;
	int n2 = g2.x + g2.y;

	if(n1 > n2){
		Grid tmpGrid = g1;
		g1 = g2;
		g2 = tmpGrid;
	}
}


//g1為grid的起點，g2為grid的終點
bool GameControl::isValidOperation(GameState* state, Grid& g1, Grid& g2){

	generalizeOperation(g1, g2);

	if(g1.x >= state->board[0].size()){
		g1.x = state->board[0].size() - 1;
	}

	if(g1.x == 0){
		g1.x = 1;
	}

	if(g1.y >= state->board.size()){
		g1.y = state->board.size() - 1;

	}

	if(g1.y == 0){
		g1.y = 1;
	}

	if(g2.x == g1.x){
		if(abs(g2.y - g1.y) + 1 >= state->crossOut ){
			int numSquare = 0;//cross之間存在多少個方塊
			for(int i = g1.y; i <= g2.y; i++){

				//超過陣列大小，跳開，之後不處理
				if(i >= state->board.size()){
					break;
				}

				if(state->board[i][g1.x]){
					numSquare++;
				}
			}
			if(numSquare == state->crossOut){
				return true;
			}
		}
	}

	
	if( g2.y == g1.y){
		if(abs(g2.x - g1.x) + 1 >= state->crossOut){
			int numSquare = 0;//cross之間存在多少個方塊
			for(int i = g1.x; i <= g2.x; i++){;
				//超過陣列大小，跳開，之後不處理
				if(i >= state->board[0].size()){
					break;
				}

				if(state->board[g1.y][i]){
					numSquare++;
				}
			}
			if(numSquare == state->crossOut){
				return true;
			}
		}
	}
	return false;

}
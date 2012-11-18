#include "SearchTree.h"


int SearchTree::heuristic(Node* node){
	int N = node->state->board[0][0] / node->state->crossOut;//至少還要幾步才能解

	int count = 0; //找看看是否有能一次就消掉的直、橫行

	//橫行
	for(int j = 1; j < node->state->board.size(); j++){
		if(node->state->board[j][0] == node->state->crossOut){
			count++;
		}
	}

	//直行
	for(int i = 1; i < node->state->board.size(); i++){
		if(node->state->board[0][i] == node->state->crossOut){
			count++;
		}
	}

	if(count >= N){
		count = N;
	}


	return N-count;//至少還要try幾步才能看到一直線下去，能一直線畫下去的先試
}

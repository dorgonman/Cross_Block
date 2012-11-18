#include "SearchTree.h"



SearchTree::SearchTree(){

}

bool SearchTree::isGoal(Node* node){
	for(int j = 1; j <= node->state->sizey ;j++){
		for(int i = 1; i <= node->state->sizex; i++){
			if(node->state->board[j][i]){
				return false;
			}
		}
	} 
	return true;
}


bool SearchTree::isCircle(Node *node, vector<Node*> closed){
	
	for(vector<Node*>::iterator it = closed.begin(); it != closed.end(); it++){
		Node* n = *it;
		if(n->state->isSame(node->state)){
			return true;
		}
	}


	return false;

}


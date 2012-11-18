#include "SearchTree.h"
#include "GameControl.h"

void SearchTree::calculateBranchAndDeadEnds(vector<GameState*> states){
		int j = 0;
		for(vector<GameState*>::iterator it = states.begin(); it != states.end(); it++){
				GameState* state = *it;
				j++;
				cout << j << "/" << states.size() << endl;
				GameState* cloneState = state->clone();
				for(int i = 0; i < state->solvedStep; i++){
					Node* node = new Node(cloneState->clone());

					vector<Node*> leaf = this->expand(node);
					state->nBranch += leaf.size();
					state->nNode += 1;
					state->nDeadEnd += node->state->nDeadEnd;
					for(vector<Node*>::iterator it2 = leaf.begin(); it2 != leaf.end(); it2++){
						Node* n = *it2;
						delete n;
						n = NULL;
					}


					delete node;
					node = NULL;


					int step = (state->solvedStep - (cloneState->countBoard() / state->crossOut));
					Grid a1 = state->solvedSequence[step][0];
					Grid a2 = state->solvedSequence[step][state->crossOut - 1];
					GameControl::getInstance()->operation(cloneState, a1, a2);
		
					
				}
				delete cloneState;
				cloneState = NULL;
		}
}
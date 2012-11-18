#include "SearchTree.h"
#include "GameControl.h"

#include <queue>
struct cmp{    
	bool operator()(Node* a,Node* b){        

		return a->f > b->f;   
	}
};
void SearchTree::astar(GameState *initState){
	vector<Node*> closed;
	priority_queue<Node* ,vector<Node*>, cmp> fringe;

	fringe.push(new Node(initState->clone()));


	//greedy-heuristic


	while(true){

		if(fringe.empty()){
			break;
		}
		Node* node = fringe.top();
		fringe.pop();

		if(isGoal(node)){
			initState->nLiveRoad++;
			break;
		}

		//cout << "f:" << node->f << ", g:" << node->g  << ", h:" << node->h << endl;



		if(!isCircle(node, closed)){
			closed.push_back(node);
			//insert all
			vector<Node*> leaf = expand(node);
			initState->nNode += 1;
			initState->nBranch += (float)leaf.size();
			for(vector<Node*>::iterator it = leaf.begin(); it != leaf.end(); it++){
				Node* node = *it;
				node->h = heuristic(node);
				node->f = node->g + node->h;
				fringe.push(node);
			}
		}else{
			delete node;
			node = NULL;
		
		}



	}

	
	for(vector<Node*>::iterator it = closed.begin(); it != closed.end(); it++){
			Node* node = *it;
			delete node;
			node = NULL;
	}

	//return initState; //找到死路及活路的多寡
}


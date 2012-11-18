#include "SearchTree.h"
#include "GameControl.h"


void SearchTree::bfs(GameState *initState){
	vector<Node*> closed;
	vector<Node*> fringe;
	fringe.push_back(new Node(initState->clone()));
	

	cout << "processing bfs, please waiting:" << endl;

	while(true){

		if(fringe.empty()){
			break;
		}
		Node* node = fringe.front();
		fringe.erase(fringe.begin());

		if(isGoal(node)){
			initState->nLiveRoad++;
			break;
		}

		cout << "cost:" << node->f << endl;



		if(!isCircle(node, closed)){
			closed.push_back(node);
			//insert all
			vector<Node*> leaf = expand(node);
			initState->nNode += 1;
			initState->nBranch += (float)leaf.size();
			for(vector<Node*>::iterator it = leaf.begin(); it != leaf.end(); it++){
				Node* node = *it;
				node->h = 0;
				node->f = node->g + node->h;
				initState->nDeadEnd += node->state->nDeadEnd;
				fringe.push_back(node);
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


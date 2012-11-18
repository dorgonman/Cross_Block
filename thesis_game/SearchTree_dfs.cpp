#include "SearchTree.h"
#include "GameControl.h"

bool SearchTree::dfs(GameState *initState){
	return dfs(initState->solvedStep, initState);
}


bool SearchTree::dfs(int maxDepth, GameState *initState){
	vector<Node*> closed;
	vector<Node*> fringe;
	fringe.push_back(new Node(initState->clone()));

	
	int beforeF = -1;//在拿出節點時上一個的cost是多少，預設-1
	while(true){

		if(fringe.empty()){
			break;
		}
		Node* node = fringe.back();
		fringe.pop_back();

		if(beforeF >= node->f){
			initState->nbacktrace++;//計算找到活路之前，總共back trace了幾次
		}

		beforeF = node->f;

		if(isGoal(node)){
			initState->nLiveRoad++;
			break;
		}

		if(node->f == maxDepth){//當成本f大於某個深度時就不繼續往下展開
			delete node;
			node = NULL;
			continue;
		}
		//cout << "f:" << node->f << "g:" << node->g  << "h:" << node->h << endl;

		if(!isCircle(node, closed)){
			closed.push_back(node);
			//insert all
			vector<Node*> leaf = expand(node);
			initState->nNode += 1;
			initState->nBranch += (float)leaf.size();
			initState->nDeadEnd += node->state->nDeadEnd;
			for(vector<Node*>::iterator it = leaf.begin(); it != leaf.end(); it++){
				Node* node = *it;
				node->h = 0; //dfs沒有heuristic
				node->f = node->g + node->h;		
			
				fringe.push_back(node);
			}
		}else{
			delete node;
			node = NULL;
		
		}

	}

	bool bfringe = (bool)fringe.size();//非0即真

	//release resource
	for(vector<Node*>::iterator it = fringe.begin(); it != fringe.end(); it++){
			Node* node = *it;
			delete node;
			node = NULL;
	}

	for(vector<Node*>::iterator it = closed.begin(); it != closed.end(); it++){
			Node* node = *it;
			delete node;
			node = NULL;
	}
	fringe.clear();
	closed.clear();
	return bfringe;


}
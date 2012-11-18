#include "SearchTree.h"
#include "GameControl.h"
#include "hge.h"

extern HGE* hge;

//計算F(cost)在fringe裡有多少個=>用來亂數選擇的依據
int SearchTree::countFAmount(int F, vector<Node*> fringe){
	int count = 0;
	for(vector<Node*>::iterator it = fringe.begin(); it != fringe.end(); it++){
		Node* node = *it;
		if(node->f == F){
			count++;
		}
	}

	return count;

}

void SearchTree::randomDFS(GameState *initState){
	vector<Node*> closed;
	vector<Node*> fringe;
	fringe.push_back(new Node(initState->clone()));

	

	int beforeF = -1;//在拿出節點時上一個的cost是多少
	while(true){

		if(fringe.empty()){
			break;
		}

		int nextF = beforeF + 1;
		int count = countFAmount(nextF, fringe);//下一層有幾個子節點
	

		Node* node = NULL;
		if(beforeF == -1){//beforeF = -1 => root
			node = fringe.back();
			fringe.pop_back();
		}else if(count == 0){//往下鑽沒有路了，backtrace
			initState->nbacktrace++;//計算找到活路之前，總共back trace了幾次=>要看死路的長短
			node = fringe.back();
			fringe.pop_back();
		}else{//亂數往下鑽
			int r = hge->Random_Int(1, count);
	    	int indexF = 0;//往下鑽時，下一層
			for(vector<Node*>::iterator it = fringe.begin(); it != fringe.end(); it++){
				Node* n = *it;

				if(n->f == nextF){//找出下一層的節點
					indexF++;
					if(r == indexF){
						node = n;
						fringe.erase(it);
						break;
					}
			
				}
			}

			/*if(count == 0){//back trace
				node = fringe.back();
				fringe.pop_back();
			
			}*/
		}

		beforeF = node->f;

		if(isGoal(node)){
			initState->nLiveRoad++;
			break;
		}

		//cout << "f:" << node->f << "g:" << node->g  << "h:" << node->h << endl;



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
	//return initState; //找到死路及活路的多寡
}


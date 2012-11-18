#include "SearchTree.h"
#include "GameControl.h"
#include "hge.h"

extern HGE* hge;

//�p��F(cost)�bfringe�̦��h�֭�=>�ΨӶüƿ�ܪ��̾�
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

	

	int beforeF = -1;//�b���X�`�I�ɤW�@�Ӫ�cost�O�h��
	while(true){

		if(fringe.empty()){
			break;
		}

		int nextF = beforeF + 1;
		int count = countFAmount(nextF, fringe);//�U�@�h���X�Ӥl�`�I
	

		Node* node = NULL;
		if(beforeF == -1){//beforeF = -1 => root
			node = fringe.back();
			fringe.pop_back();
		}else if(count == 0){//���U�p�S�����F�Abacktrace
			initState->nbacktrace++;//�p���쬡�����e�A�`�@back trace�F�X��=>�n�ݦ��������u
			node = fringe.back();
			fringe.pop_back();
		}else{//�üƩ��U�p
			int r = hge->Random_Int(1, count);
	    	int indexF = 0;//���U�p�ɡA�U�@�h
			for(vector<Node*>::iterator it = fringe.begin(); it != fringe.end(); it++){
				Node* n = *it;

				if(n->f == nextF){//��X�U�@�h���`�I
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
	//return initState; //��즺���ά������h��
}


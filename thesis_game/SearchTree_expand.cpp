#include "SearchTree.h"
#include "GameControl.h"

vector<Node*> SearchTree::expand(Node* node){
	vector<Node*> leaf;
	node->state->nNode++;
	//���
	for(int j = 1; j <= node->state->sizey ;j++){

		int num = 0;//�g�L�F�X��crossOut���ƥ�
		Grid g1;   
		Grid g2;
		
	
		bool firstFlag = false;//mark�Ĥ@�ӸI�쪺�l

		for(int i = 1; i <= node->state->sizex; i++){
			if(node->state->board[j][i]){
				num++;
			}

			if(!firstFlag){
				if(num == 1){
					g1.set(i, j);//�Ĥ@�Ӥl����l
					firstFlag = true;//���F�Ĥ@���l
				}
			}

			if(num == node->state->crossOut){
				g2.set(i, j);//�̫�@�Ӥl����l
				GameState* newState = node->state->clone();
				//GameControl::getInstance()->setGameBoard(newState);
				GameControl::getInstance()->operation(newState, g1, g2);//�i��@���������ʧ@
				if(!newState->isDead()){
					Node* newNode = new Node(newState);
					newNode->g = node->g + 1;
					leaf.push_back(newNode);//�s�J�ݮi��
		
				}else{
					node->state->nDeadEnd++;
					delete newState;
				}
		
				//newState = node->state->clone();//�^�Ш�����e�����A
				num = 0;//�p�ƾ�reset
			    firstFlag = false;//���s�h��Ĥ@�Ӥl
				i = g1.x;
				g1.set(0, 0);
				g2.set(0, 0);
			
			}
		}
	}

	//����A��W�����{���X�X�G�@�Ҥ@��
	for(int i = 1; i <= node->state->sizex ;i++){

		int num = 0;//�g�L�F�X��crossOut���ƥ�
		Grid g1;   
		Grid g2;

		bool flag = false;//mark�Ĥ@�ӸI�쪺�l

		for(int j = 1;  j <= node->state->sizey; j++){
			if(node->state->board[j][i]){
				num++;
			}

			if(!flag){
				if(num == 1){
					g1.set(i, j);//�Ĥ@�Ӥl����l
					flag = true;//���F�Ĥ@���l
				}
			}

			if(num == node->state->crossOut){
				g2.set(i, j);//�̫�@�Ӥl����l
				GameState* newState = node->state->clone();
			//	GameControl::getInstance()->setGameBoard(newState);
				GameControl::getInstance()->operation(newState, g1, g2);//�i��@���������ʧ@
				//GnewState->board = GameControl::getInstance()->getGameBoard();//�N�����᪺�ѽL���A���^
				if(!newState->isDead()){
					Node* newNode = new Node(newState);
					newNode->g = node->g + 1;
					leaf.push_back(newNode);//�s�J�ݮi��
				}else{
					node->state->nDeadEnd++;
					delete newState;
				}
				num = 0;//�p�ƾ�reset
				j = g1.y;
			    flag = false;//���s�h��Ĥ@�Ӥl
				g1.set(0, 0);
				g2.set(0, 0);


			}
		}


	}

	return leaf;



}
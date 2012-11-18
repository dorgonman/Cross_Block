#include "SearchTree.h"


int SearchTree::heuristic(Node* node){
	int N = node->state->board[0][0] / node->state->crossOut;//�ܤ��٭n�X�B�~���

	int count = 0; //��ݬݬO�_����@���N���������B���

	//���
	for(int j = 1; j < node->state->board.size(); j++){
		if(node->state->board[j][0] == node->state->crossOut){
			count++;
		}
	}

	//����
	for(int i = 1; i < node->state->board.size(); i++){
		if(node->state->board[0][i] == node->state->crossOut){
			count++;
		}
	}

	if(count >= N){
		count = N;
	}


	return N-count;//�ܤ��٭ntry�X�B�~��ݨ�@���u�U�h�A��@���u�e�U�h������
}

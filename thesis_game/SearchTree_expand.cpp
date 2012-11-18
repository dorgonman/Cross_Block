#include "SearchTree.h"
#include "GameControl.h"

vector<Node*> SearchTree::expand(Node* node){
	vector<Node*> leaf;
	node->state->nNode++;
	//橫行
	for(int j = 1; j <= node->state->sizey ;j++){

		int num = 0;//經過了幾個crossOut的數目
		Grid g1;   
		Grid g2;
		
	
		bool firstFlag = false;//mark第一個碰到的子

		for(int i = 1; i <= node->state->sizex; i++){
			if(node->state->board[j][i]){
				num++;
			}

			if(!firstFlag){
				if(num == 1){
					g1.set(i, j);//第一個子的位子
					firstFlag = true;//找到了第一顆子
				}
			}

			if(num == node->state->crossOut){
				g2.set(i, j);//最後一個子的位子
				GameState* newState = node->state->clone();
				//GameControl::getInstance()->setGameBoard(newState);
				GameControl::getInstance()->operation(newState, g1, g2);//進行一次消除的動作
				if(!newState->isDead()){
					Node* newNode = new Node(newState);
					newNode->g = node->g + 1;
					leaf.push_back(newNode);//存入待展區
		
				}else{
					node->state->nDeadEnd++;
					delete newState;
				}
		
				//newState = node->state->clone();//回覆到消除前的狀態
				num = 0;//計數器reset
			    firstFlag = false;//重新去找第一個子
				i = g1.x;
				g1.set(0, 0);
				g2.set(0, 0);
			
			}
		}
	}

	//直行，跟上面的程式碼幾乎一模一樣
	for(int i = 1; i <= node->state->sizex ;i++){

		int num = 0;//經過了幾個crossOut的數目
		Grid g1;   
		Grid g2;

		bool flag = false;//mark第一個碰到的子

		for(int j = 1;  j <= node->state->sizey; j++){
			if(node->state->board[j][i]){
				num++;
			}

			if(!flag){
				if(num == 1){
					g1.set(i, j);//第一個子的位子
					flag = true;//找到了第一顆子
				}
			}

			if(num == node->state->crossOut){
				g2.set(i, j);//最後一個子的位子
				GameState* newState = node->state->clone();
			//	GameControl::getInstance()->setGameBoard(newState);
				GameControl::getInstance()->operation(newState, g1, g2);//進行一次消除的動作
				//GnewState->board = GameControl::getInstance()->getGameBoard();//將消掉後的棋盤狀態取回
				if(!newState->isDead()){
					Node* newNode = new Node(newState);
					newNode->g = node->g + 1;
					leaf.push_back(newNode);//存入待展區
				}else{
					node->state->nDeadEnd++;
					delete newState;
				}
				num = 0;//計數器reset
				j = g1.y;
			    flag = false;//重新去找第一個子
				g1.set(0, 0);
				g2.set(0, 0);


			}
		}


	}

	return leaf;



}
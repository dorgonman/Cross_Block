#include "GameState.h"
#include "GameControl.h"


extern HGE* hge;



//�üƲ������d


void GameState::randomGenerate(int _crossOut, int step){
	crossOut = _crossOut;
	int y = board.size() - 1;
	int x = board[0].size() - 1;

	GameControl::getInstance()->file << "[cross number]" << endl;
	GameControl::getInstance()->file <<  crossOut <<  endl;

	GameControl::getInstance()->file << "[sizex]" << endl;
	GameControl::getInstance()->file <<  sizex <<  endl;

	GameControl::getInstance()->file << "[sizey]" << endl;
	GameControl::getInstance()->file <<  sizey <<  endl;

    GameControl::getInstance()->file << "[game state]" << endl;


	vector<vector<int> > tmpBoard  = board;
	int information = 0;

	while(solvedStep < step){

		//�Ҧ��ѽL���񤣤U����N����
		if(!checkBoard(board, crossOut)){
			break;
		}
	

		solvedStep++;
		bool flag = false;
		while(!flag){

			tmpBoard  = board;
			//random�U�h�Ĥ@���l
			int k = crossOut;
			int rx = hge->Random_Int(1, x);
			int ry = hge->Random_Int(1, y);
			int direct = hge->Random_Int(0, 1) % 2;

			//�p�G�ӱ��u�Ψ�U�쪺�s��϶������Uk���l�A�N���s�üƲ��ͤ@�� 
			if(!checkLine(board, direct, crossOut, rx, ry)){
				continue;
			}
		


			if(!tmpBoard[ry][rx]){//�S��������
				tmpBoard[ry][rx] = true; //��@�Ӥ���b�ѽL�W
				GameControl::getInstance()->file << "(" << rx << "," << ry << ")";
				k = k - 1;
			}else{
				continue;//��������ܡA�N���s�üƲ���
			}
			



			//�@���ncross out�X�ӡA�ݭn�O�P�@�Ӥ�V
			while(k > 0){
					if(direct == UPDOWN){//�T�wx
						//ry = hge->Random_Int(1, y);
						int fy =  hge->Random_Int(1, y);
						if(!tmpBoard[fy][rx]){//�S��������
							if(checkLineFollow(board, direct,rx, ry, rx, fy)){
								tmpBoard[fy][rx] = true; //��@�Ӥ���b�ѽL�W
								GameControl::getInstance()->file << "(" << rx << "," << fy << ")";
								k = k - 1;
							
							}
						}

					}else if(direct == CROSS){ //�T�wy
						int fx = hge->Random_Int(1, x);
						if(!tmpBoard[ry][fx]){//�S��������
							if(checkLineFollow(board, direct, rx, ry, fx, ry)){
								tmpBoard[ry][fx] = true; //��@�Ӥ���b�ѽL�W
								GameControl::getInstance()->file << "(" << fx << "," << ry << ")";
								k = k - 1;
							}
						}
					}
					if(k == 0){
						flag = true;
					}
			}


			//GameControl::getInstance()->printTwoDimDynamicArray(tmpBoard);
		}
		GameControl::getInstance()->file  << endl;
		board = tmpBoard;
		//GameControl::getInstance()->search.expand(Node(this));
	}

//	static int i =1;
	//cout << i  << "information:" << information << endl;
	//i++;

	GameControl::getInstance()->file << "[solved step]" << endl;
	GameControl::getInstance()->file << solvedStep << endl;

	//checkBoard(board, crossOut);

	//GameControl::getInstance()->printTwoDimDynamicArray(board);
	//cout << endl;

}

bool GameState::checkLineFollow(vector<vector<int>> arr, int direct, int x, int y, int fx, int fy){
	
	bool flag = false;//�ݬݬO�_���g�L�üƲ��ͪ��I�A�A�ݬݸ��I�O�_���b�����j���϶��W 
	bool flag2 = false;

	if(direct == UPDOWN){//�T�wx�Ay�ܰ�

			for(int j = 1; j !=  arr.size(); ++j) {
				if(arr[j][x]){//�I�����
					flag = false;
					flag2 = false;
				}


				if(j == y){
					flag = true;
				}
				if(j == fy){
					flag2 = true;
				}

				if(flag && flag2){
					//�ݬݱ��U�ӶüƲ��ͪ��I�O�_���b�Ĥ@���I���i�����d��
						return true;
				}
			}

	}else if(direct == CROSS){ //�T�wy�Ax�ܰ�
			for(int i = 1; i !=  arr[0].size(); ++i) {
				if(arr[y][i]){//�I�����
					flag = false;
					flag2 = false;
				}



				if(i == x){
					flag = true;
				}

				if(i == fx){
					flag2 = true;
				}

				if(flag && flag2){
					//�ݬݱ��U�ӶüƲ��ͪ��I�O�_���b�Ĥ@���I���i�����d��
					return true;
				}
			}
	}
	return false;


}


bool GameState::checkLine(vector<vector<int>> arr, int direct, int crossOut, int x, int y){
	
	
	
	bool flag = false;//�ݬݬO�_���g�L�üƲ��ͪ��I�A�A�ݬݸ��I�O�_���b�����j���϶��W 

	if(direct == UPDOWN){//�T�wx�Ay�ܰ�
		if(arr[0][x]){//�i�H�U
			int num = 0;//�Ů�
			for(int j = 1; j !=  arr.size(); ++j) {
				if(arr[j][x]){//�I�����
					num = 0;
					flag = false;
				}else{

					num++;
				}

				if(j == y){
					flag = true;

				}

				if(flag && num >= crossOut){
					return true;
				}
			}
		}
	}else if(direct == CROSS){ //�T�wy
		if(arr[y][0]){
			int num = 0;//�Ů�
			for(int i = 1; i !=  arr[0].size(); ++i) {
				if(arr[y][i]){//�I�����
					num = 0;
					flag = false;
				}else{

					num++;
				}

				if(i == x){
					flag = true;
				}


				if(flag && num >= crossOut){
					return true;
				}
			}
		}
	}
	return false;
}

//�ݴѽL�W���u�O�_�ٯ��WcrossOut�Ӥl
bool GameState::checkBoard(vector<vector<int>>& arr, int crossOut){

  //�������]�������
  for(int y = 0; y !=  arr.size(); ++y) {
	  arr[y][0] = false;
  }

  for(int x = 0; x !=  arr[0].size(); ++x) {
	  arr[0][x] = false;
  }

  //GameControl::getInstance()->printTwoDimDynamicArray(arr);

  int flag = false;

  for(int y = 1; y !=  arr.size(); ++y) {
	 int ky = 0;//�T�wy
     for(int x = 1; x != arr[0].size(); ++x) {

			if(arr[y][x]){//���������ܭn���s�p��
				ky = 0;
			}else{
				ky++;
			}

			if(ky >= crossOut){
				arr[y][0] = true;
				flag = true;
				break;
			}
		}
  }


  
  for(int x = 1; x !=  arr[0].size(); ++x) {
	  int kx = 0;//�T�wx
	  for(int y = 1; y != arr.size(); ++y) {

				if(arr[y][x]){//���������ܭn���s�p��
					kx = 0;
				}else{
					kx++;
				}
	
				if(kx >= crossOut){
					arr[0][x] = true;
					flag = true;
					break;
				}
		}
   }

	if(flag){
	   return true;
	}
	return false;//�S���u�i�H��F
}
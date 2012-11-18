#include "GameState.h"
#include "GameControl.h"


extern HGE* hge;



//亂數產生關卡


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

		//所有棋盤都放不下之後就停止
		if(!checkBoard(board, crossOut)){
			break;
		}
	

		solvedStep++;
		bool flag = false;
		while(!flag){

			tmpBoard  = board;
			//random下去第一顆子
			int k = crossOut;
			int rx = hge->Random_Int(1, x);
			int ry = hge->Random_Int(1, y);
			int direct = hge->Random_Int(0, 1) % 2;

			//如果該條線及其下到的連續區塊不能放下k顆子，就重新亂數產生一次 
			if(!checkLine(board, direct, crossOut, rx, ry)){
				continue;
			}
		


			if(!tmpBoard[ry][rx]){//沒放方塊的話
				tmpBoard[ry][rx] = true; //放一個方塊在棋盤上
				GameControl::getInstance()->file << "(" << rx << "," << ry << ")";
				k = k - 1;
			}else{
				continue;//有方塊的話，就重新亂數產生
			}
			



			//一次要cross out幾個，需要是同一個方向
			while(k > 0){
					if(direct == UPDOWN){//固定x
						//ry = hge->Random_Int(1, y);
						int fy =  hge->Random_Int(1, y);
						if(!tmpBoard[fy][rx]){//沒放方塊的話
							if(checkLineFollow(board, direct,rx, ry, rx, fy)){
								tmpBoard[fy][rx] = true; //放一個方塊在棋盤上
								GameControl::getInstance()->file << "(" << rx << "," << fy << ")";
								k = k - 1;
							
							}
						}

					}else if(direct == CROSS){ //固定y
						int fx = hge->Random_Int(1, x);
						if(!tmpBoard[ry][fx]){//沒放方塊的話
							if(checkLineFollow(board, direct, rx, ry, fx, ry)){
								tmpBoard[ry][fx] = true; //放一個方塊在棋盤上
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
	
	bool flag = false;//看看是否有經過亂數產生的點，再看看該點是否落在足夠大的區塊上 
	bool flag2 = false;

	if(direct == UPDOWN){//固定x，y變動

			for(int j = 1; j !=  arr.size(); ++j) {
				if(arr[j][x]){//碰到牆壁
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
					//看看接下來亂數產生的點是否都在第一個點的可消除範圍內
						return true;
				}
			}

	}else if(direct == CROSS){ //固定y，x變動
			for(int i = 1; i !=  arr[0].size(); ++i) {
				if(arr[y][i]){//碰到牆壁
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
					//看看接下來亂數產生的點是否都在第一個點的可消除範圍內
					return true;
				}
			}
	}
	return false;


}


bool GameState::checkLine(vector<vector<int>> arr, int direct, int crossOut, int x, int y){
	
	
	
	bool flag = false;//看看是否有經過亂數產生的點，再看看該點是否落在足夠大的區塊上 

	if(direct == UPDOWN){//固定x，y變動
		if(arr[0][x]){//可以下
			int num = 0;//空格
			for(int j = 1; j !=  arr.size(); ++j) {
				if(arr[j][x]){//碰到牆壁
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
	}else if(direct == CROSS){ //固定y
		if(arr[y][0]){
			int num = 0;//空格
			for(int i = 1; i !=  arr[0].size(); ++i) {
				if(arr[y][i]){//碰到牆壁
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

//看棋盤上的線是否還能放上crossOut個子
bool GameState::checkBoard(vector<vector<int>>& arr, int crossOut){

  //先全部設為不能放
  for(int y = 0; y !=  arr.size(); ++y) {
	  arr[y][0] = false;
  }

  for(int x = 0; x !=  arr[0].size(); ++x) {
	  arr[0][x] = false;
  }

  //GameControl::getInstance()->printTwoDimDynamicArray(arr);

  int flag = false;

  for(int y = 1; y !=  arr.size(); ++y) {
	 int ky = 0;//固定y
     for(int x = 1; x != arr[0].size(); ++x) {

			if(arr[y][x]){//有放方塊的話要重新計算
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
	  int kx = 0;//固定x
	  for(int y = 1; y != arr.size(); ++y) {

				if(arr[y][x]){//有放方塊的話要重新計算
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
	return false;//沒有線可以放了
}
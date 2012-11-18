#include "iostream"
#include "stdlib.h"
#include "vector"
#include <fstream>
#include "iostream"
#include "math.h"
#include "bitset"
#include "Grid.h"
using namespace std;

/*void printTwoDimDynamicArray(vector<vector<int> > ivec) {
  for(int y = 0; y != ivec.size(); ++y) {
    for(int x = 0; x != ivec[0].size(); ++x) {
      cout << ivec[y][x] << " ";
    }
    cout << endl;
  }
}

int main() {
  const int sizex = 3;
  const int sizey = 2;
  
  
  for(int y = 0; y != sizey; ++y) {
    for(int x = 0; x != sizex; ++x) {
      ivec[y][x] = y + x;
    }
  }
  
  printTwoDimDynamicArray(ivec);*/


#ifndef GAME_STATE
#define GAME_STATE
 

class GameState{
public:
	GameState(int sizex, int sizey);
	~GameState();


public:
	bool isSame(GameState* state);
	bool isDead();
	bool isGoal();
	int countBoard();
public:
 //vector<vector<int> > board(11, vector<bool>(11));//為方便程式處理，0行0列不使用


public:
  int id;//unique id
  int crossOut;//每次消除幾個
  int solvedStep;//幾步能解開該局
  int sizex;
  int sizey;


  float nLiveRoad;
  float nDeadEnd;
  float nBranch;//共看到了多少個分枝

  float nNode;//展開了幾個結點才找到活路
  float nbacktrace;

  float complexity;
  //棋盤，為方便程式處理，0行0列是用來儲存其他有用資訊用的
  //在亂數產生時期是當作是否可放下去該行的mark
  //在計算死路活路時期是用來存放該行有多少個方塊
  vector<vector<int> > board;
  vector<vector<Grid>> solvedSequence;
  int rank;//該state的rank

public:
  void randomGenerate(int crossOut, int step);
  GameState* clone();


private:
	bool checkLine(vector<vector<int>> arr, int direct, int crossOut, int x, int y);//看看下在該條線的子是否能擺上
	bool checkLineFollow(vector<vector<int>> arr, int direct, int x, int y, int fx, int fy);//看看接下來的子是否都能跟第一顆子一起
	bool checkBoard(vector<vector<int>>& arr, int crossOut);//看看整個棋盤是否還有位子擺

private:
	enum eDirection{//亂數產生的方向
		UPDOWN = 0,
		CROSS = 1
	};



};




#endif
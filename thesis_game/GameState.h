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
 //vector<vector<int> > board(11, vector<bool>(11));//����K�{���B�z�A0��0�C���ϥ�


public:
  int id;//unique id
  int crossOut;//�C�������X��
  int solvedStep;//�X�B��Ѷ}�ӧ�
  int sizex;
  int sizey;


  float nLiveRoad;
  float nDeadEnd;
  float nBranch;//�@�ݨ�F�h�֭Ӥ��K

  float nNode;//�i�}�F�X�ӵ��I�~��쬡��
  float nbacktrace;

  float complexity;
  //�ѽL�A����K�{���B�z�A0��0�C�O�Ψ��x�s��L���θ�T�Ϊ�
  //�b�üƲ��ͮɴ��O��@�O�_�i��U�h�Ӧ檺mark
  //�b�p�⦺�������ɴ��O�ΨӦs��Ӧ榳�h�֭Ӥ��
  vector<vector<int> > board;
  vector<vector<Grid>> solvedSequence;
  int rank;//��state��rank

public:
  void randomGenerate(int crossOut, int step);
  GameState* clone();


private:
	bool checkLine(vector<vector<int>> arr, int direct, int crossOut, int x, int y);//�ݬݤU�b�ӱ��u���l�O�_���\�W
	bool checkLineFollow(vector<vector<int>> arr, int direct, int x, int y, int fx, int fy);//�ݬݱ��U�Ӫ��l�O�_�����Ĥ@���l�@�_
	bool checkBoard(vector<vector<int>>& arr, int crossOut);//�ݬݾ�ӴѽL�O�_�٦���l�\

private:
	enum eDirection{//�üƲ��ͪ���V
		UPDOWN = 0,
		CROSS = 1
	};



};




#endif
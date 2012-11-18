#include "GameState.h"
#include "hgeresource.h"
#include "hge.h"
#include "hgegui.h"
#include "hgefont.h"
#include "hgeguictrls.h"
#include "SearchTree.h"
#ifndef GAME_CONTROL
#define GAME_CONTROL

#define SQUARE 50//方塊的大小



class GameControl{
private:
	GameControl();
	~GameControl();
public:
	static GameControl* getInstance();

public:
	//沒有傳入state的話，就代表使用currentState來進行操作
	bool isGoal();//檢查state棋盤上的方塊是否已全部消除，是的話就是贏
	bool isDead();
	bool isDead(GameState* state);
public:
	bool operation(Grid g1, Grid g2);
	bool operation(GameState* state, Grid g1, Grid g2);//消除方塊
public:
	void setGameBoard(GameState* state);
	
public:
	void render();
	void setStateIndex(int index);
	int getStateIndex();
	GameState* getCurrentState();
	void printTwoDimDynamicArray();
	void printTwoDimDynamicArray(vector<vector<int>> board);
	void printSolvedSequence();
	void printComplexity(vector<GameState*> states);

public:
	vector<GameState*> sortbyComplexity(int sortMode);
	vector<GameState*> sortbyComplexity(int sortMode, vector<GameState*> s);
	vector<GameState*> sortbyDifficulty(int sortMode, vector<GameState*> s);
	vector<GameState*> sortSolvedSequence();
	vector<GameState*> sortbySolvedStep(int sortMode);
	enum eSort{//要排序的方式
		ASCENT = 0,
		DESCENT = 1,
	};
private:
	bool isValidOperation(GameState* state, Grid& g1, Grid& g2);//g1為grid的起點，g2為grid的終點
	void generalizeOperation(Grid& g1, Grid& g2);//將數值總合較高的operation調整順序一下(高的是g1，低的是g2)

public:
		hgeResourceManager* rm;
		hgeSprite* squareSpr;
		vector<GameState*> states;
		GameState* currentState;
		int stateIndex;
		//vector<vector<int>> board;//棋盤，為方便程式處理，0行0列不使用
		ofstream file;

private:
	static GameControl* instance;

	//GameState* currentState;;

	




};

#endif

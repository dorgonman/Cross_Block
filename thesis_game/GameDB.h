//#include "GameState.h"
#include "vector"
#include "stdlib.h"
#include "vector"
#include "math.h"
#include "bitset"
#include "iostream"
#include <fstream>
#include "hge.h"

using namespace std;

#include "GameState.h"

#ifndef GAME_DB
#define GAME_DB
class GameDB{
public:
	GameDB(){
		sizex = sizey = 10;
	};
	GameDB(int sizex, int sizey);
	~GameDB();


public:
	//傳入每款遊戲在每個solvedStep想要產生幾個關卡n
	void buildAllDatabase(int _nGame, int _maxStep);
	void buildDatabase(int _nGame, int _maxStep, int crossOut);


	vector<GameState*> getStates(int filter, float threshold = -1);
	vector<GameState*> getStates(vector<GameState*> dbStates, int filter, float threshold = -1); //從db中挑出符合條件的puzzle
	vector<GameState*> getRandomStates(int n, vector<GameState*> dbStates);//從db中亂數挑出n個puzzle出來
	vector<GameState*> getRandomStates(int n);//從db中亂數挑出n個puzzle出來
public:
	vector<GameState*> merge(vector<GameState*> s1, vector<GameState*> s2);//將二個狀態中的state結合成一個
	vector<GameState*> pickStates(vector<GameState*> dbStates, vector<GameState*> s);//從db中挑出跟s相同的puzzle
	vector<GameState*> pickStates(vector<GameState*> dbStates, GameState* s);//從db中挑出跟s相同的puzzle
	bool exist(vector<GameState*> dbStates, GameState* s);
public:
	void calculateComplexity();
public:
	bool loadGames(string filePath);
	void saveGames(string filePath);
	void saveGames(string filePath, vector<GameState*> s);
	vector<GameState*> removeSamePuzzle(vector<GameState*> s);
	
private:

	//a是斜率，b是位移
	float sigmoid(float x, float a, float b);
	float Gaussian1D(float x, float mean, float std);
public:
	vector<GameState*> states;
	enum eSort{
		ASCENT = 0,
		DESCENT = 1,
	};
	enum eFilter{
		STEP_BELOW,
		STEP_UP,
		STEP_EQUAL,
		CROSS_OUT_EQUAL,
		COMPLEXITY_BELOW,
		COMPLEXITY_ABOVE,
		ALL
	};
private:
	int sizex;
	int sizey;
	int nGame;
	int maxStep;

};


#endif
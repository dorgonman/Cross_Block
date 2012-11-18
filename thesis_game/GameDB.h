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
	//�ǤJ�C�ڹC���b�C��solvedStep�Q�n���ʹX�����dn
	void buildAllDatabase(int _nGame, int _maxStep);
	void buildDatabase(int _nGame, int _maxStep, int crossOut);


	vector<GameState*> getStates(int filter, float threshold = -1);
	vector<GameState*> getStates(vector<GameState*> dbStates, int filter, float threshold = -1); //�qdb���D�X�ŦX����puzzle
	vector<GameState*> getRandomStates(int n, vector<GameState*> dbStates);//�qdb���üƬD�Xn��puzzle�X��
	vector<GameState*> getRandomStates(int n);//�qdb���üƬD�Xn��puzzle�X��
public:
	vector<GameState*> merge(vector<GameState*> s1, vector<GameState*> s2);//�N�G�Ӫ��A����state���X���@��
	vector<GameState*> pickStates(vector<GameState*> dbStates, vector<GameState*> s);//�qdb���D�X��s�ۦP��puzzle
	vector<GameState*> pickStates(vector<GameState*> dbStates, GameState* s);//�qdb���D�X��s�ۦP��puzzle
	bool exist(vector<GameState*> dbStates, GameState* s);
public:
	void calculateComplexity();
public:
	bool loadGames(string filePath);
	void saveGames(string filePath);
	void saveGames(string filePath, vector<GameState*> s);
	vector<GameState*> removeSamePuzzle(vector<GameState*> s);
	
private:

	//a�O�ײv�Ab�O�첾
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